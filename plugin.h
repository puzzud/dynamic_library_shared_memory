#ifndef PLUGIN_H

typedef struct
{
  void* libraryHandle;
  
  void (*receiveSystemMemoryFunction)(char*);
  void (*executeCommandFunction)(void);
}
PluginInterface;

int LoadPlugin(char pluginFileName[], PluginInterface* pluginInterface);
void UnloadPlugin(PluginInterface* pluginInterface);

#endif
