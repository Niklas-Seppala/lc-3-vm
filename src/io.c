#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "io.h"

struct termios orig_terminal;

static inline uint16_t swap16(uint16_t bytes) { return (bytes << 8) | (bytes >> 8); }

static void handle_interrupt(int signal)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_terminal);
    printf("\n");
    exit(EXIT_SUCCESS);
}

void init_io(void)
{
#ifdef DEBUG
    printf("DEBUG MODE                  \033[1;32mactive\033[0m\n");
#ifdef RT_ASSERT
    printf("   * RUNTIME MEMORY SAFETY  \033[1;32mactive\033[0m\n");
#endif
    printf("\n");
#endif

    signal(SIGINT, handle_interrupt);

    // Store original configs.
    tcgetattr(STDIN_FILENO, &orig_terminal);
    // Disable buffering.
    struct termios new_tio = orig_terminal;
    new_tio.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void clean_io(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_terminal);
}

int read_img(const char *path, uint16_t *memory)
{
    FILE *file = fopen(path, "rb");
    if (!file)
        return 0;

    uint16_t ORIGIN;
    fread(&ORIGIN, sizeof(uint16_t), 1, file);
    ORIGIN = swap16(ORIGIN);

    uint16_t *p = memory + ORIGIN;
    size_t read = fread(p, sizeof(uint16_t), UINT16_MAX - ORIGIN, file);
    while (read-- > 0)
    {
        *p = swap16(*p);
        p++;
    }

    fclose(file);
    return 1;
}

void parse_args(const char **argv, const int argc, struct args *args)
{
    if (argc > 1) {
        args->filepath = argv[1];
    }
}
