#include "memory.h"
#include "plugin.h"

#include <stdio.h>
#include <string.h>

int InitializePlugin(PluginInterface* pluginInterface);

int Initialize(PluginInterface* pluginInterface)
{
  printf("*Initialize*");
  printf("\n");
  
  if (InitializeSystemMemory() != 0)
  {
    return 1;
  }
  
  if (InitializePlugin(pluginInterface) != 0)
  {
    return 1;
  }
  
  return 0;
}

int InitializePlugin(PluginInterface* pluginInterface)
{
  if (pluginInterface == NULL)
  {
    // TODO: Error condition.
    return 1;
  }
  
  strcpy(pluginInterface->fileName, "libplugin1.so");
  
  return LoadPlugin(pluginInterface);
}

void Shutdown(PluginInterface* pluginInterface)
{
  UnloadPlugin(pluginInterface);
  
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
  
  if (Initialize(&pluginInterface) != 0)
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
  
  Shutdown(&pluginInterface);
  
  return 0;
}
