CC = g++
CFLAGS = -Wall
DEPS = vector.h ray.h scene.h film.h
OBJ = vector.o ray.o scene.o film.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

exec: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -rf *o main