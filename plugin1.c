#include "plugin.h"
#include "memory.h"

#include <stdio.h>

void ReceiveSystemMemory(char* systemMemory)
{
  SystemMemory = systemMemory;
}

void ExecuteCommand()
{
  char value;
  
  printf("Library function called!");
  printf("\n");
  
  value = GetByteSystemMemory(0xd1ef);
  printf("Library: Before value at 0x%x is %u.", 0xd1ef, value);
  printf("\n");
  
  value = 64;
  printf("Library: Set value at 0x%x to %u.", 0xd1ef, value);
  printf("\n");
  SetByteSystemMemory(0xd1ef, value);
  
  value = GetByteSystemMemory(0xd1ef);
  printf("Library: After value at 0x%x is %u.", 0xd1ef, value);
  printf("\n");
}
