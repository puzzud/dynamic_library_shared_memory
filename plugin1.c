#include "plugin.h"

#include <stdio.h>

char (*GetByteSystemMemory)(unsigned int);
void (*SetByteSystemMemory)(unsigned int, char);

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
