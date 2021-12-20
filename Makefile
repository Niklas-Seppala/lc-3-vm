CC=gcc
DEBUG=-g -DDEBUG
OFLAGS=-Wall -Wshadow -c
HEADERS=-Iinclude
PROJECT_NAME=lc3vm

COMPLETE_PRINT = \033[1;32mBuild Complete\033[0m
MODULE_PRINT = \033[0;34m$@\033[0m

OBJ_DIR=./obj/
OUT_DIR=./out/
SRC_DIR := ./src/

SRC_FILES := $(wildcard ${SRC_DIR}*.c)
SRC := $(SRC_FILES:${SRC_DIR}%=%)
OBJS := $(SRC:%.c=%.o)
BINS := $(SRC:%.c=%)


build: ${BINS}
	@echo "Linking..."
	@${CC} ${OBJS} ${RAYLIB} -o ${OUT_DIR}${PROJECT_NAME}
	@mv ./*.o ${OBJ_DIR}
	@echo "$(COMPLETE_PRINT)"

%.o: ${SRC_DIR}%.c
	@echo "Compiling module $(MODULE_PRINT)"
	@${CC} ${OFLAGS} ${HEADERS} ${DEBUG} $< -o $@

%: %.o
	

clean:
	@rm $(OBJ_DIR)* $(OUT_DIR)* *.o 2>/dev/null || true

run:
	@./out/${PROJECT_NAME}