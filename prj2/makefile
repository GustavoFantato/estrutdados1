# Makefile para compilar 
CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic
LDFLAGS :=
LDLIBS :=
TARGET := prj2
OBJS := prj2.o bigint.o listaencad.o

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

# Regras de compilação 
%.o: %.c listaencad.h BigInt.h
	$(CC) $(CFLAGS) -c $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)