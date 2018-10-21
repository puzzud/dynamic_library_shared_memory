mkdir -p bin;
gcc -o bin/main.o -c main.c;
gcc -o bin/memory.o -c -fpic memory.c;
gcc -o bin/plugin.o -c plugin.c;
gcc -o bin/driver bin/main.o bin/memory.o bin/plugin.o -ldl;

gcc -o bin/plugin1.o -c -fpic plugin1.c;
gcc -o bin/libplugin1.so bin/plugin1.o -shared;

exit $@;
