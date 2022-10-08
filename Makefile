SRC = src
OUT = out

CC = gcc
CFLAGS = -g -W -Wall -Wextra -O2 -D_GNU_SOURCE -std=c99 `pkg-config --cflags --libs glib-2.0`
VFLAGS =  --leak-check=full --show-leak-kinds=all --track-origins=no --verbose

FILES := $(wildcard $(SRC)/*.c)
OBJ := $(patsubst $(SRC)%,$(OUT)%,$(patsubst %.c,%.o,$(FILES)))

EXEC = program
LOG = memlog.txt

$(EXEC): $(OBJ)
	@$(CC) $(OBJ) -o $(OUT)/$@ $(CFLAGS)

$(OBJ): out/%.o : src/%.c                 
	@$(CC) -c $< -o $@ $(CFLAGS) 		 

.PHONY: clean
clean:
	-rm -f $(OBJ)
	-rm -f $(OUT)/$(EXEC)
	-rm -f $(OUT)/$(LOG)

.PHONY: run
run:
	@$(OUT)/$(EXEC)

.PHONY: $(LOG)
$(LOG):
	@valgrind $(VFLAGS) --log-file=$(OUT)/$@ $(OUT)/$(EXEC)


