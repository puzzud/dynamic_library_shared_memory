#include <stdio.h>
#include <dlfcn.h>

#include "memory.h"

int Initialize()
{
  printf("*Initialize*");
  printf("\n");
  
  if (InitializeSystemMemory() != 0)
  {
    return 1;
  }
  
  return 0;
}

void Shutdown()
{
  FreeSystemMemory();
  
  printf("*Shutdown*");
  printf("\n");
}

void MemoryCheckTest(unsigned int address)
{
  char value = GetByteSystemMemory(address);
  
  printf("Value at 0x%x is %u.", address, value);
  printf("\n");
}

int main()
{
  void* libraryHandle = NULL;
  void (*receiveSystemMemoryFunction)(char*);
  void (*executeCommandFunction)(void);
  
  libraryHandle = dlopen("libplugin1.so", RTLD_LAZY);
  
  if (libraryHandle == NULL)
  {
    printf("Failed to load library.");
    printf("\n");
    
    return 1;
  }
  
  *(void**)(&executeCommandFunction) = dlsym(libraryHandle, "ExecuteCommand");
  
  if (executeCommandFunction == NULL)
  {
    printf("Failed to load function from library.");
    printf("\n");
    
    return 1;
  }
  
  *(void**)(&receiveSystemMemoryFunction) = dlsym(libraryHandle, "ReceiveSystemMemory");
  
  if (receiveSystemMemoryFunction == NULL)
  {
    printf("Failed to load function from library.");
    printf("\n");
    
    return 1;
  }
  
  if (Initialize() != 0)
  {
    printf("Failed to initialize system.");
    printf("\n");
    
    return 1;
  }
  
  // Run test
  SetByteSystemMemory(0xd1ef, 25);
  MemoryCheckTest(0xd1ef);
  
  receiveSystemMemoryFunction(SystemMemory);
  executeCommandFunction();
  MemoryCheckTest(0xd1ef);
  
  dlclose(libraryHandle);
  
  Shutdown();
  
  return 0;
}
