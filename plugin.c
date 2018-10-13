#include "plugin.h"

#include <stdio.h>
#include <dlfcn.h>

char* SystemMemory;

int LoadPlugin(PluginInterface* pluginInterface)
{
  if (pluginInterface == NULL)
  {
    // TODO: Error condition.
    return 1;
  }
  
  pluginInterface->libraryHandle = dlopen(pluginInterface->fileName, RTLD_NOW);
  
  if (pluginInterface->libraryHandle == NULL)
  {
    printf("Failed to load library file '%s'.", pluginInterface->fileName);
    printf("\n");
    
    return 1;
  }
  
  *(void**)(&pluginInterface->executeCommandFunction) =
    LoadPluginSymbol(pluginInterface, "ExecuteCommand");
  
  if (pluginInterface->executeCommandFunction == NULL)
  {
    return 1;
  }
  
  *(void**)(&pluginInterface->receiveSystemMemoryFunction) =
    LoadPluginSymbol(pluginInterface, "ReceiveSystemMemory");
    
  if (pluginInterface->receiveSystemMemoryFunction == NULL)
  {
    return 1;
  }
  
  return 0;
}

void** LoadPluginSymbol(PluginInterface* pluginInterface, char symbolName[])
{
  void** symbol = NULL;
  
  if (pluginInterface != NULL && pluginInterface->libraryHandle != NULL)
  {
    symbol = dlsym(pluginInterface->libraryHandle, symbolName);
  }
  
  if (symbol == NULL)
  {
    printf("Failed to load symbol '%s' from library '%s'.",
      symbolName,
      pluginInterface->fileName);
    printf("\n");
  }
  
  return symbol;
}

void UnloadPlugin(PluginInterface* pluginInterface)
{
  if (pluginInterface == NULL)
  {
    // TODO: Error condition.
    return;
  }
  
  dlclose(pluginInterface->libraryHandle);
}
