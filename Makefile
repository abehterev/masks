CC = gcc

TARGET = masks

SRCS=$(TARGET).c
OBJS=$(SRCS:.c=.o)

all: $(TARGET)

debug: CC += -DDEBUG
debug:	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -O3 -o $@ $^ $(LIBS)

$(TARGET).o: Makefile

clean:
	rm -rf *.o

distclean: clean
	rm -f $(TARGET)
