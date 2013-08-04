/* test_Plugin - for licensing and copyright see license.txt */

#pragma once

#include <Game.h>

#include <IPluginManager.h>
#include <IPluginBase.h>
#include <CPluginBase.hpp>
#include <IPluginD3D.h>
#include <d3d9.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>

#include <IPlugintest.h>
#include <CGPUMesh.h>

#define PLUGIN_NAME "test"
#define PLUGIN_CONSOLE_PREFIX "[" PLUGIN_NAME " " PLUGIN_TEXT "] " //!< Prefix for Logentries by this plugin

namespace testPlugin
{
    /**
    * @brief Provides information and manages the resources of this plugin.
    */
    class CPlugintest :
        private D3DPlugin::ID3DEventListener,
        public PluginManager::CPluginBase,
        public IPlugintest
    {
        protected:
            bool bDX9;
            bool bDX11;
            bool bExecuted;
            bool bMeshCanBeCreated;
            bool bDone;

            union device    // Declare union type
            {
                void* ptr;
                IDirect3DDevice9*   dx9;
                ID3D11Device*       dx11;
            } m_pDevice;

            PluginManager::IPluginBase* m_pD3DPlugin;
            D3DPlugin::IPluginD3D* m_pD3DSystem;
            IDirect3DStateBlock9* m_pStateBlock;

        public:
            CPlugintest();
            ~CPlugintest();

            // IPluginBase
            bool Release( bool bForce = false );

            int GetInitializationMode() const
            {
                return int( PluginManager::IM_Default );
            };

            bool Init( SSystemGlobalEnvironment& env, SSystemInitParams& startupParams, IPluginBase* pPluginManager, const char* sPluginDirectory );

            bool RegisterTypes( int nFactoryType, bool bUnregister );

            const char* GetVersion() const
            {
                return "1.0.0.0";
            };

            const char* GetName() const
            {
                return PLUGIN_NAME;
            };

            const char* GetCategory() const
            {
                return "Other";
            };

            const char* ListAuthors() const
            {
                return "Firstname 'alias' Lastname <mail at ? dot ?>";
            };

            const char* ListCVars() const;

            const char* GetStatus() const;

            const char* GetCurrentConcreteInterfaceVersion() const
            {
                return "1.0";
            };

            void* GetConcreteInterface( const char* sInterfaceVersion )
            {
                return static_cast < IPlugintest* > ( this );
            };

            // IPlugintest
            IPluginBase* GetBase()
            {
                return static_cast<IPluginBase*>( this );
            };

            void Update();

            // D3D Plugin interfaces
            void OnPrePresent();
            void OnPostPresent();
            void OnPreReset();
            void OnPostReset();
            void OnPostBeginScene();

            // TODO: Add your concrete interface implementation
        private:
            int m_frameNum;
            CGPUMesh m_GPUMesh;
            bool m_fExecuted;


    };

    extern CPlugintest* gPlugin;
}

/**
* @brief This function is required to use the Autoregister Flownode without modification.
* Include the file "CPlugintest.h" in front of flownode.
*/
inline void GameWarning( const char* sFormat, ... ) PRINTF_PARAMS( 1, 2 );
inline void GameWarning( const char* sFormat, ... )
{
    va_list ArgList;
    va_start( ArgList, sFormat );
    testPlugin::gPlugin->LogV( ILog::eWarningAlways, sFormat, ArgList );
    va_end( ArgList );
};
