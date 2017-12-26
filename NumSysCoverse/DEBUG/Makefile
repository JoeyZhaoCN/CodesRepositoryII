CC		= gcc -o
LINK	= gcc -c -o

OBJS	= main.obj

SOURCE	= $(wildcard ../MAIN/*.c)

HEADER	= $(wildcard ../MAIN/*.h) \
$(wildcard F:/workspace/libs/data.struct.lib/*.h)

# -L 后跟库所在目录
# -l 后跟库明
# 注意：-L -l 之间不要有空格
LIBS	= \
-L/F:/workspace/libs/data.struct.lib-lDataStruct

# $@ 表示当前生成目标
# $^ 表示所有依赖项
# $< 表示第一个依赖项
Demo : $(OBJS)
	$(CC) $@ $^ $(LIBS)

$(OBJS) : $(SOURCE) $(HEADER)
	$(LINK) $@ $<

run:
	Demo $(ARGS)

.PHONY : clean
clean:
	-rm *.obj
