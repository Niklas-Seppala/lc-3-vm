CC=gcc
DEBUG=-g -DDEBUG
WARN=-Wall -Wshadow
STANDARD=-std=c99
HEADERS=-Iinclude
PROJECT_NAME=lc3vm

COMPLETE_PRINT = \033[1;32mBuild Complete\033[0m\n\nBinary location: ${OUT_DIR}${PROJECT_NAME}\n----------------\n
MODULE_PRINT = \033[0;34m$@\033[0m

OBJ_DIR=./obj/
OUT_DIR=./out/
SRC_DIR := ./src/

SRC_FILES := $(wildcard ${SRC_DIR}*.c)
SRC := $(SRC_FILES:${SRC_DIR}%=%)
OBJS := $(SRC:%.c=%.o)
BINS := $(SRC:%.c=%)


build: ${BINS}
	@echo "Linking ..."
	@${CC} ${OBJS} ${RAYLIB} -o ${OUT_DIR}${PROJECT_NAME}
	@mv ./*.o ${OBJ_DIR}
	@echo "$(COMPLETE_PRINT)"

%.o: ${SRC_DIR}%.c
	@echo "Module $(MODULE_PRINT)"
	@${CC} -c ${STANDARD} ${WARN} ${HEADERS} ${DEBUG} $< -o $@

%: %.o
	

clean:
	@rm $(OBJ_DIR)* $(OUT_DIR)* *.o 2>/dev/null || true

run:
	@./out/${PROJECT_NAME}