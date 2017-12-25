OBJS = main.o sysui.o stuifo.o

SOURCE = $(wildcard ../MAIN/*.c)  $(wildcard ../UI/*.c)\
$(wildcard ../INFO/*.c)

HEADER = $(wildcard ../MAIN/*.h)  $(wildcard ../UI/*.h)\
$(wildcard ../INFO/*.h)

Demo:$(OBJS)
	gcc -o Demo $(OBJS)

$(OBJS):$(SOURCE) $(HEADER)
	gcc -c $(SOURCE)

run:
	Demo $(ARGS)
