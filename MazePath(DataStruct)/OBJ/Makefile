CC  	= gcc -o
LINK	= gcc -c -o

OBJS	= main.obj maze.obj
LIB 	= dtastc.obj

SOURCE	= $(wildcard ../MAIN/*.c) $(wildcard ../MAZE/*.c)

HEADER	= $(wildcard ../MAIN/*.h) $(wildcard ../MAZE/*.h) \
$(wildcard F:/workspace/libs/data.struct.lib/*.h)

MazePath : $(OBJS) $(LIB)
	$(CC) $@ $^

$(OBJS) : $(SOURCE) $(HEADER)
	$(LINK) $@ $<

run :
	MazePath $(ARGS)

.PHONY : clean
clean:
	-rm *.obj
