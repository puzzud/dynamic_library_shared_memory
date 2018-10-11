gcc -o main.o -c main.c;
gcc -o memory.o -c -fpic memory.c;
gcc -o driver main.o memory.o -ldl;

gcc -o plugin1.o -c -fpic plugin1.c;
gcc -o libplugin1.so plugin1.o memory.o -shared;

exit $@;
