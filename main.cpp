/******************************************************************
* Author: Erik Sanders
* Date: 03/18/2023
* Description:
* 
* This program attempts to apply CUDA concepts
* to a 2x2x2 cube compose of subcube that have
* 100x100x100 elements. The kernel adds all 
* the numbers together to create an output
* 
******************************************************************/


#include <iostream>
#include <vector>
#include <cmath>
#include <cuda.h>

#define SIZE 100
#define X SIZE
#define Y SIZE
#define Z SIZE

typedef std::vector<std::vector<std::vector<int>>> subBlock;
typedef std::vector<std::vector<std::vector<subBlock>>> outerBlock;

subBlock createSubBlock(){

    subBlock block(X, std::vector<std::vector<int>>(Y, std::vector<int>(Z)));

    for (int i = 0; i < block.size(); i++)
    {
        for (int j = 0; j < block[i].size(); j++)
        {
            for (int k = 0; k < block[i][j].size(); k++)
            {
                block[i][j][k] = i + j + k;
            }

        }

    }
    return block;

}

// Create a cube from the sub cubes (2x2x2)
outerBlock createOuterBlock(){
    outerBlock block(2, std::vector<std::vector<subBlock>>(2, std::vector<subBlock>(2)));
    for (int i = 0; i < block.size(); i++)
    {
        for (int j = 0; j < block[i].size(); j++)
        {
            for (int k = 0; k < block[i][j].size(); k++)
            {
                // Create sub blocks
                block[i][j][k] = createSubBlock();
            }

        }

    }

    return block;
}


// Kernel to launch on device
__global__ void destruction(outerBlock *cudaCube, int* c) {
    // Create index from threads and blocks available
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    c[index] += cudaCube[index][index][index][index][index][index];
}

int main(int argc, char const* argv[])
{

    outerBlock *cudaCube;   // Host mem
    outerBlock *d_cudaCube; // Device mem
    int *c;                 // Output host
    int *d_c;               // Output device 

    // Create the cudaCube to run the calculations on
    cudaCube = createOuterBlock();
    cudaMalloc((void**)&d_cudaCube, pow(SIZE,3) * 8);

    // Allocate host memory
    c = (int*)malloc(pow(SIZE, 3) * 8);

    // Allocate device memory
    cudaMemcpy(d_cudaCube, cudaCube, pow(SIZE, 3) * 8, cudaMemcpyHostToDevice);

    // Launch kernel block by thread
    destruction<<<SIZE / pow(SIZE,3), 8 >> > (d_cudaCube, d_c);
    
    // Copy the results from device back to host
    cudaMemcpy(c, d_c, pow(SIZE, 3) * 8, cudaMemcpyDeviceToHost);

    // Release memory 
    free(cudaCube); free(c);
    cudaFree(d_cudaCube); cudaFree(d_c);


    return 0;
}
