#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

//сортировка пузырьком--------------------------------
void bubble_sort(float** dist, int n, float* sort_ver, int* sort_path) {

    float temp = 0;
    
    float* m = new float[n];
    for (int i = 0; i < n; i++)
        m[i] = dist[0][i];
    
    float* mtemp = new float[n];
    for (int i = 0; i < n; i++)
        mtemp[i] = 0;

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++) {
            if (m[j] > m[j + 1]) {
                temp = m[j];
                m[j] = m[j + 1];
                m[j + 1] = temp;

                temp = sort_ver[j];
                sort_ver[j] = sort_ver[j + 1];
                sort_ver[j + 1] = temp;

                temp = sort_path[j];
                sort_path[j] = sort_path[j + 1];
                sort_path[j + 1] = temp;

                for (int k = 0; k < n; k++)
                    mtemp[k] = dist[k][j];
                for (int k = 0; k < n; k++)
                    dist[k][j] = dist[k][j + 1];
                for (int k = 0; k < n; k++)
                    dist[k][j + 1] = mtemp[k];

                for (int k = 0; k < n; k++)
                    mtemp[k] = dist[j][k];
                for (int k = 0; k < n; k++)
                    dist[j][k] = dist[j + 1][k];
                for (int k = 0; k < n; k++)
                    dist[j + 1][k] = mtemp[k];
            }
        }

    delete[] mtemp;
    delete[] m;
}

void search_min(float** dist, int n, int* pow_check, float &min, int &i_min, int &j_min, int &p1, int &p2) {

    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (dist[i][j] < min && dist[i][j] != 0 && (i == p1 || i == p2 || j == p1 || j == p2) && (pow_check[i] < 2 && pow_check[j] < 2) && (pow_check[i] + pow_check[j] != 2))
            {
                min = dist[i][j];
                i_min = i;
                j_min = j;
            }
}

float summ(float** g, int n) {

    float s = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            s += g[i][j];
    return s;
}

void greedy_alg(float** dist, int n) {

    //вспомогательный граф G*, заполнен нулями
    float** g = new float* [n];
    for (int i = 0; i < n; i++)
        g[i] = new float[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g[i][j] = 0;

    //массив для степеней врешин
    int* pow_check = new int[n];
    for (int i = 0; i < n; i++)
        pow_check[i] = 0;

    //сортированный список расстояний
    float* sort_ver = new float[n];
    for (int i = 0; i < n; i++)
        sort_ver[i] = 0;
    //сортированный список веришин
    int* sort_path = new int[n];
    for (int i = 0; i < n; i++)
        sort_path[i] = i;

    //крайние вершины
    int p1 = 0;
    int p2 = 0;

    //переменные
    int i_min = 1;
    int j_min = 0;
    float min_weight = 3.4028235E+38;
    float distance = 0;

    //сортировка по возрастанию
    bubble_sort(dist, n, sort_ver, sort_path);    

    //цикл поиска гамильтонова цикла------------------
    for(int i = 0; i < n - 1; i++) {
        
        search_min(dist, n, pow_check, min_weight, i_min, j_min, p1, p2);

        if (g[i_min][j_min] == 0){
            
            g[i_min][j_min] = min_weight;
            g[j_min][i_min] = min_weight;
            dist[i_min][j_min] = 0;
            dist[j_min][i_min] = 0;
            
            pow_check[i_min] += 1;
            pow_check[j_min] += 1;

            int pos = 0;
            for (int i = 0; i < n; i++)
                if (pow_check[i] == 1) {
                    p1 = i;
                    pos = i;
                }
            for (int i = 0; i < pos; i++)
                if (pow_check[i] == 1) p2 = i;

            min_weight = 3.4028235E+38;
        }
    }
    g[p1][p2] = dist[p1][p2];
    g[p2][p1] = dist[p2][p1];
    dist[p1][p2] = 0;
    dist[p2][p1] = 0;

    pow_check[p1] += 1;
    pow_check[p2] += 1;

    //длина цикла-------------------------------------
    distance = summ(g, n);
    distance /= 2;
    // cout << "Длина: ";
    cout << distance << endl;

    //путь по вершинам--------------------------------
    // int* path = new int[n + 1];
    // for (int i = 0; i < n + 1; i++)
    //     path[i] = 0;

    // int cur_ver = 0;
    // int pi = 1;

    // while (summ(g, n) != 0) {
    //     int j = 0;
    //     while (g[cur_ver][j] == 0) j++;
    //     g[cur_ver][j] = 0;
    //     g[j][cur_ver] = 0;
    //     path[pi] = j;
    //     cur_ver = j;
    //     pi++;
    // }

    // for (int i = 0; i < n + 1; i++) {
    //     int j = 0;
    //     while (path[i] != j) j++;
    //     path[i] = sort_path[j];
    // }

    // cout << "Путь: ";
    // for (int i = 0; i < n; i++)
    //     cout << path[i] + 1 << "-";
    // cout << path[n] + 1 <<"\n\n";

    //очистка памяти----------------------------------
    for (int i = 0; i < n; i++)
        delete[] g[i];
    delete[] g;

    delete[] pow_check;
    delete[] sort_ver;
    delete[] sort_path;
    // delete[] path;
}

void mainGridy()
{
    setlocale(LC_ALL, "Russian");

    int kol = 0;
    int n = 0;  
    fstream f;
    f.open("test.txt", ios::in);

    f >> kol;

    for (int i = 0; i < kol; i++) {

        f >> n;

        float** dist = new float* [n];
        for (int i = 0; i < n; i++)
            dist[i] = new float[n];

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
        greedy_alg(dist, n);
        auto t_end = std::chrono::high_resolution_clock::now();
        cout << std::chrono::duration<double, std::milli>(t_end - t_start).count() << endl;
        cout << endl;

        for (int i = 0; i < n; i++)
            delete[] dist[i];
        delete[] dist;
    }
   
    f.close();
}