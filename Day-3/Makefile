CC = g++
OUTPUT = build

OBJS = \
		$(OUTPUT)/main.o

$(OUTPUT)/main: $(OBJS)
	$(CC) $(OBJS) -o $(OUTPUT)/main

clean:
	del $(OUTPUT)\*.o

$(OUTPUT)/%.o: %.cpp
	$(CC) -Wall -c $< -o $@