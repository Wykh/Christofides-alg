#include "testreader.h"

iMatrixes getMatrixesFromStream()
{
    int mCnt; // count of matrixes
    std::cin >> mCnt;

    iMatrixes ms; // vector of marixes
    for (int i = 0; i < mCnt; i++)
    {
        int mSize; // size of matrix
        std::cin >> mSize;

        iMatrix m(mSize, std::vector<int>(mSize, 0)); // matrix
        for (int i = 0; i < mSize; i++)
        {
            for (int j = i; j < mSize; j++)
            {
                int elem;
                std::cin >> elem;

                m[i][j] = m[j][i] = elem;
            }
        }

        ms.push_back(m);
    }
    return ms;
}

iMatrixes getMatrixesFromFile(std::string path)
{
    std::fstream f(path);

    int mCnt; // count of matrixes
    f >> mCnt;

    iMatrixes ms; // vector of marixes
    for (int i = 0; i < mCnt; i++)
    {
        int mSize; // size of matrix
        f >> mSize;

        iMatrix m(mSize, std::vector<int>(mSize, 0)); // matrix
        for (int i = 0; i < mSize; i++)
        {
            for (int j = i; j < mSize; j++)
            {
                int elem;
                f >> elem;

                m[i][j] = m[j][i] = elem;
            }
        }

        ms.push_back(m);
    }
    f.close();
    return ms;
}

iMatrixes getMatrixesFromStreamFullMatrix()
{
    int mCnt; // count of matrixes
    std::cin >> mCnt;

    iMatrixes ms; // vector of marixes
    for (int i = 0; i < mCnt; i++)
    {
        int mSize; // size of matrix
        std::cin >> mSize;

        iMatrix m(mSize, std::vector<int>(mSize, 0)); // matrix
        for (int i = 0; i < mSize; i++)
        {
            for (int j = 0; j < mSize; j++)
            {
                int elem;
                std::cin >> elem;

                m[i][j] = elem;
            }
        }

        ms.push_back(m);
    }
    return ms;
}

iMatrixes getMatrixesFromFileFullMatrix(std::string path)
{
    std::fstream f(path);

    int mCnt; // count of matrixes
    f >> mCnt;

    iMatrixes ms; // vector of marixes
    for (int i = 0; i < mCnt; i++)
    {
        int mSize; // size of matrix
        f >> mSize;

        iMatrix m(mSize, std::vector<int>(mSize, 0)); // matrix
        for (int i = 0; i < mSize; i++)
        {
            for (int j = 0; j < mSize; j++)
            {
                int elem;
                f >> elem;

                m[i][j] = elem;
            }
        }

        ms.push_back(m);
    }
    f.close();
    return ms;
}
