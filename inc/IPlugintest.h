/* test_Plugin - for licensing and copyright see license.txt */

#include <IPluginBase.h>

#pragma once

/**
* @brief test Plugin Namespace
*/
namespace testPlugin
{
    /**
    * @brief plugin test concrete interface
    */
    struct IPlugintest
    {
        /**
        * @brief Get Plugin base interface
        */
        virtual PluginManager::IPluginBase* GetBase() = 0;

        virtual void Update() = 0;

        // TODO: Add your concrete interface declaration here
    };
};