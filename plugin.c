#include "plugin.h"
#include "memory.h"

#include <stdio.h>
#include <dlfcn.h>

int LoadPlugin(PluginInterface* pluginInterface)
{
  if (pluginInterface == NULL)
  {
    // Error condition.
    
    return 1;
  }
  
  pluginInterface->libraryHandle = dlopen(pluginInterface->fileName, RTLD_NOW);
  
  if (pluginInterface->libraryHandle == NULL)
  {
    printf("Failed to load library file '%s'.", pluginInterface->fileName);
    printf("\n");
    
    return 1;
  }
  
  if (ResolvePluginSystemMemory(pluginInterface) != 0)
  {
    UnloadPlugin(pluginInterface);
    
    printf("Failed to resolve system memory for library '%s'.",
      pluginInterface->fileName);
    printf("\n");
    
    return 1;
  }
  
  *(void**)(&pluginInterface->executeCommandFunction) =
    LoadPluginSymbol(pluginInterface, "ExecuteCommand");
  
  if (pluginInterface->executeCommandFunction == NULL)
  {
    UnloadPlugin(pluginInterface);
    
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

int ResolvePluginSystemMemory(PluginInterface* pluginInterface)
{
  if (pluginInterface == NULL)
  {
    return 1;
  }
  
  void** getByteSystemMemory = (void**)LoadPluginSymbol(pluginInterface, "GetByteSystemMemory");
  
  if (getByteSystemMemory == NULL)
  {
    return  1;
  }
  
  *getByteSystemMemory = GetByteSystemMemory;
  
  void** setByteSystemMemory = (void**)LoadPluginSymbol(pluginInterface, "SetByteSystemMemory");
  
  if (setByteSystemMemory == NULL)
  {
    return  1;
  }
  
  *setByteSystemMemory = SetByteSystemMemory;
  
  return 0;
}

void UnloadPlugin(PluginInterface* pluginInterface)
{
  if (pluginInterface == NULL)
  {
    // Error condition.
    
    return;
  }
  
  dlclose(pluginInterface->libraryHandle);
  
  pluginInterface->libraryHandle = NULL;
}
