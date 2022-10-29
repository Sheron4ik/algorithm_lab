#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;
const int step = 2;

int** generate_1(int n, int m) {
    int** arr = new int*[n];
    for (size_t i = 0; i < n; ++i)
        arr[i] = new int[m];

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            arr[i][j] = (m/n * i + j) * 2;

    return arr;
}

int** generate_2(int n, int m) {
    int** arr = new int*[n];
    for (size_t i = 0; i < n; ++i)
        arr[i] = new int[m];

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            arr[i][j] = (m/n * i*j) * 2;

    return arr;
}

void print_array(int** arr, const int& n, const int& m) {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            cout << arr[i][j] << "\t";
        cout << '\n';
    }
}

void delete_array(int** arr, const int& n) {
    for (size_t i = 0; i < n; ++i)
        delete[] arr[i];
    delete[] arr;
}

bool jump_search(int** arr, const int& n, const int& m, const int& target) {
    int i = 0, j = m - 1;
    while ((j > -1) && (i < n)) {
        if (arr[i][j] == target)
            return true;
        if (arr[i][j] > target)
            --j;
        else
            ++i;
    }
    return false;
}

bool binary_search(int** arr, const int& n, const int& m, const int& target) {
    int left, right, middle;
    for (size_t i = 0; i < n; ++i) {
        left = 0; right = m - 1;
        while (left < right) {
            middle = (left + right) / 2;
            if (arr[i][middle] == target)
                return true;
            if (arr[i][middle] < target)
                left = middle + 1;
            else
                right = middle;
        }
    }
    return false;
}

bool exp_search(int** arr, const int& n, const int& m, const int& target) {
    int j = m - 1, i = 0;
    int up_index, down_index, middle;
    while (j > -1) {
        if (arr[i][j] == target)
            return true;
        if (arr[i][j] > target)
            --j;
        else {
            down_index = 1;
            while (((i + down_index) < n) && (arr[i + down_index][j] < target))
                down_index *= step;
            up_index = i + down_index / step;
            if ((i + down_index) >= n)
                down_index = n - 1;
            else
                down_index += i;
            if (up_index == down_index)
                return false;
            while (up_index < down_index) {
                middle = (up_index + down_index) / 2;
                if (arr[middle][j] == target)
                    return true;
                if (arr[middle][j] < target)
                    up_index = middle + 1;
                else
                    down_index = middle;
            }
            i = up_index;
        }
    }
    return false;
}

int main() {
    int n, m, target, rep;
    m = 2;
    n = 8192;
//  Три алгоритма на 1х данных
    while (m <= 8192) {
        cout << "size: " << m << "\t\t\t" << n << '\n';

        auto t0 = chrono::high_resolution_clock::now();
        int** a = generate_1(m, n);
        target = 2*(n/m)*(m-1) + 1;
        //target = 2*n + 1;
        auto t1 = chrono::high_resolution_clock::now();
        long long ta = 0;

        rep = 0;
        while (rep != 100) {
            t0 = chrono::high_resolution_clock::now();
            jump_search(a, m, n, target);
            t1 = chrono::high_resolution_clock::now();
            ta += chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
            ++rep;
        }
        cout << "jump: " << ta/100   << '\n';

        rep = 0; ta = 0;
        while (rep != 100) {
            t0 = chrono::high_resolution_clock::now();
            binary_search(a, m, n, target);
            t1 = chrono::high_resolution_clock::now();
            ta += chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
            ++rep;
        }
        cout << "binary: " << ta/100 << '\n';

        rep = 0; ta = 0;
        while (rep != 100) {
            t0 = chrono::high_resolution_clock::now();
            exp_search(a, m, n, target);
            t1 = chrono::high_resolution_clock::now();
            ta += chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
            ++rep;
        }
        cout << "exp: " << ta/100 << "\n\n";

        delete_array(a, m);

        m *= 2;
    }
//  exp на обоих данных
    /*while (m <= 8192) {
        cout << "size: " << m << "\t\t\t" << n << '\n';

        auto t0 = chrono::high_resolution_clock::now();
        int** a = generate_1(m, n);
        //target = 2*(n/m)*(m-1) + 1;
        target = 2*n + 1;
        auto t1 = chrono::high_resolution_clock::now();
        long long ta = 0;

        rep = 0;
        while (rep != 100) {
            t0 = chrono::high_resolution_clock::now();
            exp_search(a, m, n, target);
            t1 = chrono::high_resolution_clock::now();
            ta += chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
            ++rep;
        }
        cout << "exp_gen1: " << ta/100 << "\n";

        delete_array(a, m);
        //==================================================
        a = generate_2(m, n);
        //target = 2*(n/m)*(m-1) - 1;
        target = 16*n + 1;

        rep = 0; ta = 0;
        while (rep != 100) {
            t0 = chrono::high_resolution_clock::now();
            exp_search(a, m, n, target);
            t1 = chrono::high_resolution_clock::now();
            ta += chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
            ++rep;
        }
        cout << "exp_gen2: " << ta/100 << "\n\n";

        delete_array(a, m);

        m *= 2;
    }*/

    return 0;
}