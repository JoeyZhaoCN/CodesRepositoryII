OBJS = main.o sysui.o
SOURCE = $(wildcard ../MAIN/*.c)  $(wildcard ../UI/*.c)
HEADER = $(wildcard ../MAIN/*.h)  $(wildcard ../UI/*.h)

Demo:$(OBJS)
	gcc -o Demo $(OBJS)

$(OBJS):$(SOURCE) $(HEADER)
	gcc -c $(SOURCE)

run:
	Demo $(ARGS)
