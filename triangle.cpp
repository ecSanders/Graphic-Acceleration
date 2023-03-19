#include <iostream>
#include <vector>

// #define SIZE 100

// define a subblock & outerblock type
// typedef std::vector<std::vector<std::vector<int>>> subBlock;
// typedef std::vector<std::vector<std::vector<subBlock>>> outerBlock;

// subBlock createSubBlock(){
//     subBlock block;
//     for (size_t i = 0; i < SIZE; i++)
//     {
//         for (size_t j = 0; i < SIZE; j++)
//         {
//             for (size_t k = 0; i < SIZE; k++)
//             {
//                 block[i][j][k] = i + j + k;
//             }

//         }

//     }
//     return block;

// }


// outerBlock createOuterBlock(){
//     outerBlock block;
//     for (size_t i = 0; i < 2; i++)
//     {
//         for (size_t j = 0; i < 2; j++)
//         {
//             for (size_t k = 0; i < 2; k++)
//             {
//                 block[i][j][k]= createSubBlock();
//             }

//         }

//     }

//     return block;
// }

int main(int argc, char const* argv[])
{
    // cudaMalloc(), cudaFree(), cudaMemcpy()
    // outerBlock cudaCube;

    // cudaCube = createOuterBlock();


    return 0;
}
