#ifndef PLUGIN_H

typedef struct
{
  char fileName[32];
  void* libraryHandle;
  
  void (*receiveSystemMemoryFunction)(char*);
  void (*executeCommandFunction)(void);
}
PluginInterface;

int LoadPlugin(PluginInterface* pluginInterface);
void** LoadPluginSymbol(PluginInterface* pluginInterface, char symbolName[]);
void UnloadPlugin(PluginInterface* pluginInterface);

#endif
