#include <stdio.h>

__global__ void testFunc()
{
    //int x = blockIdx.x*blockDim.x + threadIdx.x;

    return;
}

__global__ void modifyMeshGPU(float a_fpTime, float* a_pfpMesh)
{
    int x = blockIdx.x*blockDim.x + threadIdx.x;
    if(x<9)
    {
        if(0 == x%3)
        {
            a_pfpMesh[x] = a_pfpMesh[x] + 0.5f * cos(a_fpTime);
        }
    }

    return;
}

extern "C"
void cuda_testFunc()
{
    dim3 dimBlock = dim3(16, 16);
    dim3 dimGrid = dim3(1, 1);

    testFunc<<<dimBlock,dimGrid>>>();

    printf("cuda_testFunc");

    return;
}

extern "C"
void cuda_modifyMesh(float a_fpTime, float* a_pfpMesh)
{
    dim3 dimBlock = dim3(16, 16);
    dim3 dimGrid = dim3(1, 1);

    modifyMeshGPU<<<dimBlock,dimGrid>>>(a_fpTime, a_pfpMesh);
    return;
}