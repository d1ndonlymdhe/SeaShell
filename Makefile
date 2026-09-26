FUNCS := $(notdir $(wildcard funcs/*))
FUNC_OBJS := $(foreach f, $(FUNCS), funcs/$(f)/$(f).o)

all: fs/fs.o fs/fs_object.o $(FUNC_OBJS) registry/func_registry.o utils/string_utils.o libseashell.a main

clean:
	rm -f fs/fs.o fs/fs_object.o $(FUNC_OBJS) registry/func_registry.o utils/string_utils.o libseashell.a main

fs/fs.o: fs/fs.c fs/fs.h
	echo "Compiling fs.c"
	cc -c -fPIC fs/fs.c -o fs/fs.o

fs/fs_object.o: fs/fs_object.c fs/fs_object.h
	echo "Compiling fs_object.c"
	cc -c -fPIC fs/fs_object.c -o fs/fs_object.o

registry/func_registry.o: registry/func_registry.c registry/func_registry.h
	echo "Compiling func_registry.c"
	cc -c -fPIC registry/func_registry.c -o registry/func_registry.o

utils/string_utils.o: utils/string_utils.c utils/string_utils.h
	echo "Compiling string_utils.c"
	cc -c -fPIC utils/string_utils.c -o utils/string_utils.o

libseashell.a: fs/fs.o fs/fs_object.o $(FUNC_OBJS) registry/func_registry.o utils/string_utils.o
	echo "Creating static library libseashell.a"
	ar rcs libseashell.a fs/fs.o fs/fs_object.o $(FUNC_OBJS) registry/func_registry.o utils/string_utils.o

main: main.c libseashell.a
	echo "Compiling main.c"
	cc -I . -c main.c
	cc main.o -L. -lseashell -o main

$(FUNC_OBJS): funcs/%.o: funcs/%.c funcs/%.h
	echo "Compiling $<"
	cc -c -fPIC $< -o $@