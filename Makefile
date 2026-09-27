FUNCS := $(notdir $(wildcard funcs/*))
FUNC_LIBS := $(foreach f, $(FUNCS), funcs/$(f)/$(f).so)

all: libfs.so libregistry.so libutils.so $(FUNC_LIBS) main

clean:
	rm -f fs/fs.o fs/fs_object.o $(FUNC_LIBS) registry/func_registry.o utils/string_utils.o libfs.so libregistry.so libutils.so main lib_registry.txt

core_libs: libutils.so libregistry.so libfs.so
func_libs: core_libs $(FUNC_LIBS)


$(FUNC_LIBS): funcs/%.so: funcs/%.c funcs/%.h
	echo "Creating shared library $@"
	cc -shared -L. -lfs -lregistry -lutils -fPIC $< -o $@

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

libutils.so: utils/string_utils.o
	echo "Creating shared library libutils.so"
	cc -shared -o libutils.so utils/string_utils.o

libregistry.so: registry/func_registry.o
	echo "Creating shared library libregistry.so"
	cc -shared -o libregistry.so registry/func_registry.o

libfs.so: fs/fs.o fs/fs_object.o
	echo "Creating shared library libfs.so"
	cc -shared -o libfs.so fs/fs.o fs/fs_object.o

main: main.c loader/loader.c loader/loader.h
	echo "Compiling main.c"
	cc main.c loader/loader.c -L. -lfs -lregistry -lutils -o main

exec: main
	./main

