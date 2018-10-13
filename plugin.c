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
    dlsym(pluginInterface->libraryHandle, "ExecuteCommand");
  
  if (pluginInterface->executeCommandFunction == NULL)
  {
    printf("Failed to load function from library.");
    printf("\n");
    
    return 1;
  }
  
  *(void**)(&pluginInterface->receiveSystemMemoryFunction) =
    dlsym(pluginInterface->libraryHandle, "ReceiveSystemMemory");
  
  if (pluginInterface->receiveSystemMemoryFunction == NULL)
  {
    printf("Failed to load function from library.");
    printf("\n");
    
    return 1;
  }
  
  return 0;
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
