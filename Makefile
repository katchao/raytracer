CC = g++
CFLAGS = -Wall
DEPS = vector.h ray.h scene.h sample.h sampler.h color.h film.h camera.h sphere.h
OBJ = vector.o ray.o scene.o sample.o sampler.o color.o film.o camera.o sphere.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

exec: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -rf *o main
