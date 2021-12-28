#include "includes.h"
#include "testreader.h"
#include "structures.h"
#include "alhoritms.h"
#include "Traveling_Salesman.h"
#include "Traveling_Salesman_BF.h"
#include <iomanip>

#define TESTS_FILE_PATH "test.txt"

void printInput(iMatrixes ms);

void mainChristofides();

int main()
{
    // Christofides
    std::cout << "Christofides" << std::endl;
    mainChristofides();

    // std::cout << std::endl;

    // std::cout << "Brute force" << endl;
    // mainBrute();

    // std::cout << std::endl;

    // std::cout << "Gridy algorithm" << endl;
    // mainGridy();

    return 0;
}

void mainChristofides()
{
    iMatrixes ms = getMatrixesFromFile(TESTS_FILE_PATH);
    Graph G(ms[0]);

    for (auto &&m : ms)
    {
        Graph G(m);

        auto t_start = std::chrono::high_resolution_clock::now();
        cycle hamiltCycle = ApproxDoubleTree(G);
        auto t_end = std::chrono::high_resolution_clock::now();

        int len = 0;
        int i = 0;

        // std::cout << "Way: " << hamiltCycle[i] + 1;
        // calc lenth of cycle
        for (int i = 0, j = 1; j < hamiltCycle.size(); i++, j++)
        {
            int from = hamiltCycle[i];
            int to = hamiltCycle[j];

            // std::cout << "-" << to + 1;
            len += G.m[from][to];
        }
        // std::cout << std::endl;
        // std::cout << "Length: " << len << std::endl;
        
        std::cout << len << std::endl;
        std::cout << std::chrono::duration<double, std::milli>(t_end - t_start).count() << std::endl;
        std::cout << std::endl;
    }
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
