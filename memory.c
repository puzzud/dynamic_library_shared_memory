#include <stdlib.h>

#include "memory.h"

char* SystemMemory;

int InitializeSystemMemory()
{
  SystemMemory = calloc(SYSTEM_MEMORY_SIZE, sizeof(char) * SYSTEM_MEMORY_SIZE);
  
  if (SystemMemory == NULL)
  {
    return -1;
  }
  
  return 0;
}

void FreeSystemMemory()
{
  free(SystemMemory);
  SystemMemory = NULL;
}

char GetByteSystemMemory(unsigned int address)
{
  return SystemMemory[address & SYSTEM_MEMORY_HIGHEST_ADDRESS];
}

void SetByteSystemMemory(unsigned int address, char value)
{
  SystemMemory[address & SYSTEM_MEMORY_HIGHEST_ADDRESS] = value;
}
