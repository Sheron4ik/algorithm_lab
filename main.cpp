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
    int left, right, middle;
    while (i < n) { //(j > -1) {
        if (arr[i][j] == target)
            return true;
        if (arr[i][j] < target)
            ++i;
        else {
            left = 1;
            while (((j - left) > -1) && (arr[i][j - left] > target))
                left *= step;
            right = j - left / step;
            if ((j - left) < 0)
                left = 0;
            else
                left = j - left;
            if (left == right)
                return false;

            while (left < right) {
                middle = (left + right + 1) / 2;
                if (arr[i][middle] == target)
                    return true;
                if (arr[i][middle] < target)
                    left = middle;
                else
                    right = middle - 1;
            }
            j = left;

        }
    }
    return false;
}

int main() {
    int n, m, target, rep;
    m = 2;
    n = 8192;
//  Три алгоритма на 1х данных
    cout << "jump\tbinary\texp\n";
    auto t0 = chrono::high_resolution_clock::now();
    auto t1 = chrono::high_resolution_clock::now();
    auto ta = chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
    int** a;
    while (m <= 8192) {
        //cout << "size: " << m << "\t\t\t" << n << '\n';
        ta = 0;
        a = generate_1(m, n);
        //target = 2*(n/m)*(m-1) + 1;
        target = 2*n + 1;

        rep = 0;
        while (rep != 10000) {
            t0 = chrono::high_resolution_clock::now();
            jump_search(a, m, n, target);
            t1 = chrono::high_resolution_clock::now();
            ta += chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
            ++rep;
        }
        cout << ta/10000 << ' ';

        rep = 0; ta = 0;
        while (rep != 10000) {
            t0 = chrono::high_resolution_clock::now();
            binary_search(a, m, n, target);
            t1 = chrono::high_resolution_clock::now();
            ta += chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
            ++rep;
        }
        cout << ta/10000 << ' ';

        rep = 0; ta = 0;
        while (rep != 10000) {
            t0 = chrono::high_resolution_clock::now();
            exp_search(a, m, n, target);
            t1 = chrono::high_resolution_clock::now();
            ta += chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
            ++rep;
        }
        cout << ta/10000 << '\n';

        delete_array(a, m);

        m *= 2;
    }
//  exp на обоих данных
    m = 2;
    cout << "exp_gen2\n";
    while (m <= 8192) {
        //cout << "size: " << m << "\t\t\t" << n << '\n';
        a = generate_2(m, n);
        //target = 2*(n/m)*(m-1) - 1;
        target = 16*n + 1;

        rep = 0; ta = 0;
        while (rep != 10000) {
            t0 = chrono::high_resolution_clock::now();
            exp_search(a, m, n, target);
            t1 = chrono::high_resolution_clock::now();
            ta += chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
            ++rep;
        }
        cout << ta/10000 << "\n";

        delete_array(a, m);

        m *= 2;
    }

    return 0;
}