/* test_Plugin - for licensing and copyright see license.txt */

#include <StdAfx.h>
#include <CPlugintest.h>
#include <IIndexedMesh.h>

extern "C"
{
    void cuda_testFunc();
}

namespace testPlugin
{
    CPlugintest* gPlugin = NULL;

    CPlugintest::CPlugintest()
    {
        gPlugin = this;
        m_frameNum = 0;
        m_fExecuted = false;
    }

    CPlugintest::~CPlugintest()
    {
        Release( true );

        gPlugin = NULL;
    }

    bool CPlugintest::Release( bool bForce )
    {
        bool bRet = true;
        bool bWasInitialized = m_bIsFullyInitialized; // Will be reset by base class so backup

        if ( !m_bCanUnload )
        {
            // Note: Type Unregistration will be automatically done by the Base class (Through RegisterTypes)
            // Should be called while Game is still active otherwise there might be leaks/problems
            bRet = CPluginBase::Release( bForce );

            if ( bRet )
            {
                if ( bWasInitialized )
                {
                    // TODO: Cleanup stuff that can only be cleaned up if the plugin was initialized
                }

                // Cleanup like this always (since the class is static its cleaned up when the dll is unloaded)
                gPluginManager->UnloadPlugin( GetName() );

                // Allow Plugin Manager garbage collector to unload this plugin
                AllowDllUnload();
            }
        }

        return bRet;
    };

    bool CPlugintest::Init( SSystemGlobalEnvironment& env, SSystemInitParams& startupParams, IPluginBase* pPluginManager, const char* sPluginDirectory )
    {
        bool fRes = false;
        gPluginManager = ( PluginManager::IPluginManager* )pPluginManager->GetConcreteInterface( NULL );
        CPluginBase::Init( env, startupParams, pPluginManager, sPluginDirectory );

        //fRes = m_GPUMesh.init();
        gEnv->pLog->LogAlways( "CPlugintest - init done" );

        return fRes;
    }

    bool CPlugintest::RegisterTypes( int nFactoryType, bool bUnregister )
    {
        // Note: Autoregister Flownodes will be automatically registered by the Base class
        bool bRet = CPluginBase::RegisterTypes( nFactoryType, bUnregister );

        using namespace PluginManager;
        eFactoryType enFactoryType = eFactoryType( nFactoryType );

        if ( bRet )
        {
            if ( gEnv && gEnv->pSystem && !gEnv->pSystem->IsQuitting() )
            {
                // CVars
                if ( gEnv->pConsole && ( enFactoryType == FT_All || enFactoryType == FT_CVar ) )
                {
                    if ( !bUnregister )
                    {
                        // TODO: Register CVars here if you have some
                        // ...
                    }

                    else
                    {
                        // TODO: Unregister CVars here if you have some
                        // ...
                    }
                }

                // CVars Commands
                if ( gEnv->pConsole && ( enFactoryType == FT_All || enFactoryType == FT_CVarCommand ) )
                {
                    if ( !bUnregister )
                    {
                        // TODO: Register CVar Commands here if you have some
                        // ...
                    }

                    else
                    {
                        // TODO: Unregister CVar Commands here if you have some
                        // ...
                    }
                }

                // Game Objects
                if ( gEnv->pGameFramework && ( enFactoryType == FT_All || enFactoryType == FT_GameObjectExtension ) )
                {
                    if ( !bUnregister )
                    {
                        // TODO: Register Game Object Extensions here if you have some
                        // ...
                    }
                }
            }
        }

        return bRet;
    }

    const char* CPlugintest::ListCVars() const
    {
        return "..."; // TODO: Enter CVARs/Commands here if you have some
    }

    const char* CPlugintest::GetStatus() const
    {
        return "OK";
    }

    void CPlugintest::Update()
    {
        //cuda_testFunc();

        //gEnv->pLog->LogAlways( "wtf - %d", m_frameNum );

        if ( false == m_fExecuted )
        {
            if ( 0 != gEnv->pGame->GetIGameFramework()->GetClientActor() )
            {
                m_GPUMesh.init();
                m_fExecuted = true;
            }
        }

        else
        {
            m_GPUMesh.modifyMesh();
        }

        m_frameNum++;
        return;
    }

    // TODO: Add your plugin concrete interface implementation
}