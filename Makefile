CC = g++
CFLAGS = -Wall
DEPS = vector.h ray.h scene.h sample.h sampler.h color.h film.h camera.h raytracer.h light.h BRDF.h localgeo.h intersection.h aggregateprimitive.h material.h primitive.h
OBJ = vector.o ray.o scene.o sample.o sampler.o color.o film.o camera.o raytracer.o light.o BRDF.o localgeo.o intersection.o aggregateprimitive.o material.o primitive.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

exec: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -rf *o main