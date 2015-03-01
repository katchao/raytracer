CC = g++
CFLAGS = -Wall
DEPS = vector.h ray.h scene.h
OBJ = vector.o ray.o scene.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

exec: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -rf *o main