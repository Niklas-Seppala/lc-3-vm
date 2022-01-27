#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "memory.h"
#include "trap.h"
#include "opcodes/opc.h"
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

static const uint16_t PC_START = 0x3000;

struct termios original_tio;

void restore_input_buffering()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
}

void handle_interrupt(int signal)
{
    restore_input_buffering();
    printf("\n");
    exit(-2);
}

void disable_input_buffering()
{
    tcgetattr(STDIN_FILENO, &original_tio);
    struct termios new_tio = original_tio;
    new_tio.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

static void run_vm(uint16_t offset)
{
    reg_write(R_PC, PC_START + offset);
    while (is_running())
    {
        Instruction instr = mem_read(reg_read(R_PC));
        reg_write(R_PC, reg_read(R_PC) + 1);
        exec_instr(instr);
    }
    restore_input_buffering();
}

uint16_t swap16(uint16_t x) { return (x << 8) | (x >> 8); }

void read_image_file(FILE *img)
{
}

int read_image(const char *image_path)
{
    FILE *file = fopen(image_path, "rb");
    if (!file)
        return 0;

    uint16_t ORIGIN;
    fread(&ORIGIN, sizeof(uint16_t), 1, file);
    ORIGIN = swap16(ORIGIN);

    uint16_t *p = mem_ptr(ORIGIN);
    size_t read = fread(p, sizeof(uint16_t), UINT16_MAX - ORIGIN, file);
    while (read-- > 0)
    {
        *p = swap16(*p);
        p++;
    }

    fclose(file);
    return 1;
}

int main(int argc, char const **argv)
{
#ifdef DEBUG
    printf("DEBUG MODE                  \033[1;32mactive\033[0m\n");
#ifdef RT_ASSERT
    printf("   * RUNTIME MEMORY SAFETY  \033[1;32mactive\033[0m\n");
#endif
    printf("\n");
#endif

    signal(SIGINT, handle_interrupt);
    disable_input_buffering();

    const uint16_t OFFSET = 0x0;
    const char *filename = "asd.obj";

    read_image(filename);
    run_vm(OFFSET);
    printf("\n");
    return 0;
}