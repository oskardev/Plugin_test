#include <StdAfx.h>
#include "CGPUMesh.h"
#include <IGameObject.h>
#include <Actor.h>

extern "C"
{
    void cuda_modifyMesh( float a_fpTime, float* a_pfpMesh );
}

namespace testPlugin
{
    CGPUMesh::CGPUMesh()
    {
        m_fpTimer = 0.0f;
        m_pRenderMesh = 0;
        m_pEntity = 0;
        m_frame = 0;
    }

    CGPUMesh::~CGPUMesh()
    {

    }

    bool CGPUMesh::init()
    {
        bool fRes = true;

        m_pObject = gEnv->p3DEngine->CreateStatObj();
        m_pObject->AddRef();
        m_pObject->Refresh( FRO_GEOMETRY );

        m_pIndexedMesh = m_pObject->GetIndexedMesh( true );
        m_oMesh.SetVertexCount( 3 );
        m_oMesh.SetFacesCount( 1 );
        m_oMesh.SetIndexCount( 3 );

        /********* Option 1: using pointers to CMesh for assigning vetices, normals and indices **********/
        Vec3* vertices  = m_oMesh.GetStreamPtr<Vec3>( CMesh::POSITIONS );
        Vec3* normals   = m_oMesh.GetStreamPtr<Vec3>( CMesh::NORMALS );
        uint16* indices = m_oMesh.GetStreamPtr<uint16>( CMesh::INDICES );

        vertices[0] = Vec3( 1.0f, 1.0f, 0.0f );
        vertices[1] = Vec3( 0.0f, 5.0f, 0.0f );
        vertices[2] = Vec3( 5.0f, 1.0f, 0.0f );

        normals[0] = Vec3( 1, 0, 0 );
        normals[1] = Vec3( 1, 0, 0 );
        normals[2] = Vec3( 1, 0, 0 );

        indices[0] = 2;
        indices[1] = 1;
        indices[2] = 0;

        //m_oSubset

        m_oSubset.nFirstIndexId = 0;
        m_oSubset.nFirstVertId = 0;
        m_oSubset.nNumIndices = 3;
        m_oSubset.nNumVerts = 3;

        m_oMesh.m_subsets.push_back( m_oSubset );

        m_oMesh.m_bbox = m_pObject->GetAABB();

        const char* ppErrorDesc;
        assert( m_oMesh.Validate( &ppErrorDesc ) );

        m_pIndexedMesh->SetMesh( m_oMesh );
        m_pIndexedMesh->Invalidate();

        m_pRenderMesh = m_pObject->GetRenderMesh();
        m_pRenderMesh->SetMesh( m_oMesh );

        CryLog( "wtf1 Test Mesh Created %d", 0 );
        //IEntity* m_pEntity;// = GetEntity();
        //CActor *pActor = gEnv->pGame->GetIGameFramework()->GetClientActor();//static_cast<CActor *>(gEnv->pGame->GetIGameFramework()->GetClientActor());

        CryLog( "wtf1 gEnv %p", gEnv );
        CryLog( "wtf1 gEnv->pGame %p", gEnv->pGame );
        //gEnv->pGame 0000000000000000

        CryLog( "wtf1 gEnv->pGame->GetIGameFramework() %p", gEnv->pGame->GetIGameFramework() );
        CryLog( "wtf1 gEnv->pGame->GetIGameFramework()->GetClientActor() %p", gEnv->pGame->GetIGameFramework()->GetClientActor() );
        CryLog( "wtf1 gEnv->pGame->GetIGameFramework()->GetClientActor()->GetEntity() %p", gEnv->pGame->GetIGameFramework()->GetClientActor()->GetEntity() );


        m_pEntity = gEnv->pGame->GetIGameFramework()->GetClientActor()->GetEntity();//pActor->GetEntity();
        m_pEntity->Activate ( true );

        int slotCount = m_pEntity->GetSlotCount();
        int slotId = m_pEntity->SetStatObj( m_pObject, -1, false );
        int slotCount2 = m_pEntity->GetSlotCount();
        CryLog( "wtf1 Test Mesh Created %d", 0 );

        return fRes;
    }

    bool CGPUMesh::modifyMesh()
    {
        m_frame++;
        m_fpTimer += 0.01f;

        if ( ( 0 != m_pRenderMesh ) && ( m_frame % 100 == 0 ) )
        {
            CryLog( "zomg lock", 0 );
            m_pRenderMesh->LockForThreadAccess();
            CryLog( "zomg locked", 0 );
            /*m_fpTimer += 0.01f;
            CryLog( "zomg wtf1 modifyMesh %f, %p, %p", m_fpTimer, m_pRenderMesh, m_pEntity );
            m_pEntity ? m_pEntity->UnphysicalizeSlot(0) : 0;
            //strided_pointer<Vec3> spVtx;//m_spVtx
            //m_pRenderMesh->Release();
            CryLog( "zomg ok", 0 );
            //strided_pointer<float> spVtx;
            int     vtxCount    = m_pRenderMesh->GetVerticesCount();
            CryLog( "zomg vtxCount %d", vtxCount );
            int     vtxStride   = 0;*///ok
            //byte*   vtxData     = m_pRenderMesh->GetPosPtr(vtxStride, FSL_SYSTEM_UPDATE);

            //spVtx = strided_pointer<Vec3>((Vec3*)vtxData, vtxStride);
            //float* vtPtr = m_pRenderMesh->GetPosPtr(vtxStride, FSL_SYSTEM_UPDATE);
            //LOG_PTR_VALID(vtxData);

            //CryLog("wtf sizeof Vec3 %i", sizeof(Vec3));
            //CryLog("wtf vtxStride %i", vtxStride);
            /*
            //spVtx = strided_pointer<Vec3>((Vec3*)vtxData, vtxStride);
            spVtx = strided_pointer<float>((float*)vtxData, vtxStride);

            float* pfpData = (float*)m_pRenderMesh->GetPosPtr(vtxStride, FSL_SYSTEM_UPDATE);//spVtx;

            cuda_modifyMesh(m_fpTimer, pfpData);*/

            //m_pEntity->UpdateSlotPhysics(0);


            CryLog( "zomg wtf1 modifyMesh %f, %p, %p, frame %d", m_fpTimer, m_pRenderMesh, m_pEntity, m_frame );
            m_pEntity ? m_pEntity->UnphysicalizeSlot( 0 ) : 0;
            //strided_pointer<Vec3> spVtx;//m_spVtx
            //m_pRenderMesh->Release();
            CryLog( "zomg ok", 0 );
            //strided_pointer<float> spVtx;

            int     vtxCount    = m_pRenderMesh->GetVerticesCount();
            CryLog( "zomg vtxCount %d", vtxCount );
            int     vtxStride   = 0;
            //byte*   vtxData     = m_pRenderMesh->GetPosPtr(vtxStride, FSL_SYSTEM_UPDATE);
            //float*   vtxData     = (float*)m_pRenderMesh->GetPosPtr(vtxStride, FSL_SYSTEM_UPDATE);



            //spVtx = strided_pointer<Vec3>((Vec3*)vtxData, vtxStride);
            //float* vtPtr = m_pRenderMesh->GetPosPtr(vtxStride, FSL_SYSTEM_UPDATE);
            //LOG_PTR_VALID(vtxData);

            //CryLog("wtf sizeof Vec3 %i", sizeof(Vec3));
            //CryLog("wtf vtxStride %i", vtxStride);

            //spVtx = strided_pointer<Vec3>((Vec3*)vtxData, vtxStride);
            //float* spVtx = strided_pointer<float>((float*)vtxData, vtxStride);

            //float* pfpData = (float*)m_pRenderMesh->GetPosPtr(vtxStride, FSL_SYSTEM_UPDATE);//spVtx;

            //cuda_modifyMesh(m_fpTimer, vtxData);//pfpData);

            //m_pEntity->UpdateSlotPhysics(0);
            m_pRenderMesh->UnLockForThreadAccess();
        }

        return true;
    }
}