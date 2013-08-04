test Plugin for CryEngine SDK
=====================================
TODO: Describe where you tested it.

TODO: Describe the purpose of your plugin

TODO: Describe where the latest version of your plugin can be found.

Installation / Integration
==========================
Use the installer or extract the files to your CryEngine SDK Folder so that the Code and BinXX/Plugins directories match up.

The plugin manager will automatically load up the plugin when the game/editor is restarted or if you directly load it.

In Game.cpp:
* Includes:
```C++
	#include <IPluginManager_impl.h>
	#include <IPluginManager.h>
	#include "../Plugin_test/inc/IPlugintest.h"
```
* Update func:
```C++
	testPlugin::IPlugintest* pPlugintest = 0;
	pPlugintest = PluginManager::safeGetPluginConcreteInterface<testPlugin::IPlugintest*>("test");
	pPlugintest->Update();
```

CVars / Commands
================
* ```prefix_samplecvar```
  TODO: Describe the cvar

Flownodes
=========
TODO: Describe the flownodes inside your plugin

Objects
=======
TODO: Describe custom object classes inside your plugin

...