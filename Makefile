CC=gcc
DEBUG=-g -DDEBUG -DRT_ASSERT
D_OUT=DEBUG_OUTSTREAM=\"debug.log\" 
WARN=-Wall -Wshadow
STD=-std=gnu99
HEADERS=-Iinclude
PROJECT_NAME=lc3vm

COMPLETE_PRINT = \033[1;32mBuild Complete\033[0m\n\nBinary location: ${OUT_DIR}${PROJECT_NAME}\n----------------\n
MODULE_PRINT = \033[0;34m$@\033[0m

OBJ_DIR:=./obj/
OUT_DIR:=./out/
SRC_DIR:=./src/

SRC_FILES := $(wildcard ${SRC_DIR}*.c)
SRC := $(SRC_FILES:${SRC_DIR}%=%)
OBJS := $(SRC:%.c=%.o)
BINS := $(SRC:%.c=%)

build: ${BINS}
	@${CC} ${OBJS} -o ${OUT_DIR}${PROJECT_NAME}
	@mv ./*.o ${OBJ_DIR}
	@echo "$(COMPLETE_PRINT)"

%.o: ${SRC_DIR}%.c
	@${CC} -c ${STD} ${WARN} ${HEADERS} ${DEBUG} $< -o $@

%: %.o
	@echo "$(MODULE_PRINT)"

run:
	@./out/${PROJECT_NAME}

clean:
	@rm $(OBJ_DIR)* $(OUT_DIR)* *.o 2>/dev/null || true

compiler:
	gcc compiler/main.c -o ./out/compiler