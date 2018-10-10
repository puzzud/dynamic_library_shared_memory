#ifndef MEMORY_H

#define SYSTEM_MEMORY_SIZE  0x10000
#define SYSTEM_MEMORY_HIGHEST_ADDRESS  0xffff

extern char* SystemMemory;

extern int InitializeSystemMemory();
extern void FreeSystemMemory();

extern char GetByteSystemMemory(unsigned int address);
extern void SetByteSystemMemory(unsigned int address, char value);
 
#endif
