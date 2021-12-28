#include "includes.h"
#include "testreader.h"
#include "structures.h"
#include "alhoritms.h"
#include <iomanip>

#define TESTS_FILE_PATH "test.txt"

void printInput(iMatrixes ms);

int main()
{
    iMatrixes ms = getMatrixesFromFile(TESTS_FILE_PATH);

    Graph G(ms[0]);
    cycle result = ApproxDoubleTree(G);

    for (auto &&i : result)
    {
        std::cout << std::setw(3) << i;
    }
    

    return 0;
}

void printInput(iMatrixes ms)
{
    for (int z = 0; z < ms.size(); z++)
    {
        for (int i = 0; i < ms[z].size(); i++)
        {
            for (int j = 0; j < ms[z].size(); j++)
            {
                std::cout << std::setw(3) << ms[z][i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
