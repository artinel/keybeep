include ./make.config

CSOURCES = $(shell find src -type f -name "*.c")

all: compile

compile:
	$(CC) $(CFLAGS) $(CSOURCES) -o $(TARGET)

clean:
	rm $(TARGET)

run:
	./$(TARGET)
