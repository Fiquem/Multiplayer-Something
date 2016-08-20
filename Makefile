CC = g++
SRC = src/main.c \
	src/network.c
TARGET = networking
CFLAGS = -g
INC_DIR = -I ./lib/include
LIB_DIR = -L ./lib/
LOC_LIB = 
SYS_LIB = -lws2_32 -lmswsock -ladvapi32

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INC_DIR) $(SRC) -o $(TARGET) $(LIB_DIR) $(SYS_LIB) $(LOC_LIB)

.PHONY: clean
clean:
	rm ./$(TARGET).exe