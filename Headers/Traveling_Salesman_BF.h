#include <iostream>
#include <fstream>
#include <locale.h>
#include <ctime>
#include <climits>

using namespace std;

void check_min(int *ver, int dist, int n, int *path, int &path_length)
{

    if (dist < path_length)
    {
        for (int i = 0; i < n; i++)
            path[i] = ver[i];
        path_length = dist;
    }
}

int distance(int *ver, int **dist, int n)
{
    int d = dist[0][ver[0]] + dist[ver[n - 1]][0]; // начало и конец
    for (int i = 1; i < n; i++)
        d += dist[ver[i - 1]][ver[i]]; // между ver[i-1] и ver[i]
    return d;                          // длина пути перестановки ver
}

void perm(int *ver, int n, int cur, int **dist, int *path, int &path_length)
{
    if (cur >= n)
    {                                                                 // перестановки окончены
        check_min(ver, distance(ver, dist, n), n, path, path_length); // смотрим перестановку
        return;
    }

    perm(ver, n, cur + 1, dist, path, path_length); // перестановки элементов справа от cur

    for (int i = cur + 1; i < n; i++)
    {                                                   // теперь каждый элемент ver[i], i > cur
        swap(ver[i], ver[cur]);                         // меняем местами с ver[cur]
        perm(ver, n, cur + 1, dist, path, path_length); // и снова переставляем всё справа
        swap(ver[i], ver[cur]);                         // возвращаем элемент ver[i] назад
    }
}

void bf_alg(int **dist, int n)
{

    int *ver = new int[n];
    for (int i = 0; i < n; i++)
        ver[i] = i;

    int path_length = INT_MAX;
    int *path = new int[n];
    for (int i = 0; i < n; i++)
        path[i] = i;

    perm(ver, n, 0, dist, path, path_length);

    // cout << "Путь: ";
    // for (int i = 0; i < n; i++)
    //     cout << path[i] + 1 << "-";
    // cout << "1\n";
    // cout << "Длина: " << path_length << "\n";
    cout << path_length << endl;
    delete[] ver;
    delete[] path;
}

void mainBrute()
{
    setlocale(LC_ALL, "Russian");

    int kol = 0;
    int n = 0;
    fstream f;
    f.open("test.txt", ios::in);

    f >> kol;

    for (int i = 0; i < kol; i++)
    {

        f >> n;

        int **dist = new int *[n];
        for (int i = 0; i < n; i++)
            dist[i] = new int[n];

        // Fill array using full adjacency matrix
        // for (int i = 0; i < n; i++)
        //     for (int j = 0; j < n; j++)
        //         f >> dist[i][j];

        // Fill array using upper trianble of adjacency matrix
        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++)
            {
                float inputValue;
                f >> inputValue;
                dist[i][j] = dist[j][i] = inputValue;
            }

        auto t_start = std::chrono::high_resolution_clock::now();
        bf_alg(dist, n);
        auto t_end = std::chrono::high_resolution_clock::now();
        cout << std::chrono::duration<double, std::milli>(t_end - t_start).count() << endl;
        cout << endl;

        // cout << "Время: " << std::chrono::duration<double, std::milli>(t_end - t_start).count() << " ms\n";

        for (int i = 0; i < n; i++)
            delete[] dist[i];
        delete[] dist;
    }

    f.close();
}
