CC  	= gcc -o
LINK	= gcc -c
# -MM自动找寻源文件中的头文件包含关系，且不包括标准库

OBJS	= main.obj
LIB 	= dtastc.obj
# 连接库出了问题，我在这里直接使用了obj文件，发现可行

SOURCE	= $(wildcard ../MAIN/*.c)

HEADER	= $(wildcard ../MAIN/*.h) \
$(wildcard F:/workspace/libs/data.struct.lib/*.h)

# -L 后跟库所在目录
# -l 后跟库明
# 注意：-L -l 之间不要有空格

#LIBS	= -L/F:/workspace/libs/data.struct.lib-lDataStruct
# 这里我在尝试连接库时出了问题，不知道是不是vs生成的lib文件与gcc不兼容？

# $@ 表示当前生成目标
# $^ 表示所有依赖项
# $< 表示第一个依赖项
Demo : $(OBJS) $(LIB)
	$(CC) $@ $^
#$(LIBS)

$(OBJS) : $(SOURCE) $(HEADER)
	$(LINK) $< -o $@

run:
	Demo $(ARGS)

.PHONY : clean
clean:
	-rm *.obj
