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
  
  const char executeCommandFunctionName[] = "ExecuteCommand";
  
  *(void**)(&pluginInterface->executeCommandFunction) =
    dlsym(pluginInterface->libraryHandle, executeCommandFunctionName);
  
  if (pluginInterface->executeCommandFunction == NULL)
  {
    printf("Failed to load symbol '%s' from library '%s'.",
      executeCommandFunctionName,
      pluginInterface->fileName);
    printf("\n");
    
    return 1;
  }
  
  const char receiveSystemMemoryFunctionName[] = "ReceiveSystemMemory";
  
  *(void**)(&pluginInterface->receiveSystemMemoryFunction) =
    dlsym(pluginInterface->libraryHandle, receiveSystemMemoryFunctionName);
  
  if (pluginInterface->receiveSystemMemoryFunction == NULL)
  {
    printf("Failed to load function from library.");
    printf("Failed to load symbol '%s' from library '%s'.",
      receiveSystemMemoryFunctionName,
      pluginInterface->fileName);
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
