gcc -o main.o -c main.c;
gcc -o memory.o -c memory.c;
gcc -o driver main.o memory.o;

gcc main.c memory.c -o driver;

gcc -c -fpic plugin1.c;
gcc plugin1.o memory.o -shared -o libplugin1.so;

exit $@;
