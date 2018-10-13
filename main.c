#include "memory.h"
#include "plugin.h"

#include <stdio.h>

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
  PluginInterface pluginInterface;
  LoadPlugin("libplugin1.so", &pluginInterface);
  
  if (Initialize() != 0)
  {
    printf("Failed to initialize system.");
    printf("\n");
    
    return 1;
  }
  
  // Run test
  SetByteSystemMemory(0xd1ef, 25);
  MemoryCheckTest(0xd1ef);
  
  pluginInterface.receiveSystemMemoryFunction(SystemMemory);
  pluginInterface.executeCommandFunction();
  MemoryCheckTest(0xd1ef);
  
  UnloadPlugin(&pluginInterface);
  
  Shutdown();
  
  return 0;
}
