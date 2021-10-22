#include <iostream>
#include <ctime>
#include <chrono>
#include <pthread.h>

#define MAX_THREAD 8

using namespace std;
using namespace std::chrono;

void* dgemmBlas(void* rank);
void fillMatrix(double** a, size_t matrixSize);
void saxpyBlas(size_t matrixSize);
int local_size;
size_t matrixSize = 1;
double** firstMatrix = nullptr;
double** secondMatrix = nullptr;
double** resultMatrix = nullptr;

int main(int argc, char* argv[]) {
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    duration<double> duration_t = duration_cast<microseconds>(stop - start);
    if (argc>1)
    {
        matrixSize = atoi(argv[1]);
    }
     size_t numThread = 1;
    if (argc>2)
    {
        numThread = atoi(argv[2]);
    }
    firstMatrix = new double* [matrixSize];
    secondMatrix = new double* [matrixSize];
    resultMatrix = new double* [matrixSize];

    local_size = matrixSize / numThread;

    for (size_t i = 0; i < matrixSize; i++) {
        firstMatrix[i] = new double[matrixSize];
        secondMatrix[i] = new double[matrixSize];
        resultMatrix[i] = new double[matrixSize];
    }

    fillMatrix(firstMatrix, matrixSize);
    fillMatrix(secondMatrix, matrixSize);


    pthread_t* threads = new pthread_t[numThread];
   
    for (size_t i = 0; i < numThread; ++i)
    {
        int* p = nullptr;
        pthread_create(&threads[i], NULL, dgemmBlas, (void*)(p));
    }
    
    
    //dgemmBlas(firstMatrix, secondMatrix, resultMatrix, matrixSize);
    //saxpyBlas(matrixSize);
    start = high_resolution_clock::now();
    for (size_t i = 0; i < numThread; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    stop = high_resolution_clock::now();
    duration_t = duration_cast<microseconds>(stop - start);
    cout << matrixSize << ";" << duration_t.count() << endl;
    for (size_t i = 0; i < matrixSize; i++) {
        delete[]firstMatrix[i];
        delete[]secondMatrix[i];
        delete[]resultMatrix[i];
    }
    delete[]firstMatrix;
    delete[]secondMatrix;
    delete[]resultMatrix;
    return 0;
}

void saxpyBlas(size_t matrixSize)
{
    size_t N = matrixSize * matrixSize;
    double* vector = (double*)malloc(sizeof(double) * N);
    double* X = (double*)malloc(sizeof(double) * N);
    double* Y = (double*)malloc(sizeof(double) * N);
    for (size_t i = 0; i < N; ++i) {
        X[i] = rand() % matrixSize + 1 * 0.5;
        Y[i] = rand() % matrixSize + 1 * 0.5;
    }
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            vector[i] += 1 * X[i] + Y[j];
        }
    }
    free(vector);
    free(X);
    free(Y);
}

void* dgemmBlas(void* rank) {
    long my_rank = (long)rank;
    size_t i, j, k;
    size_t my_first_row = my_rank * local_size;
    size_t my_last_row = (my_rank + 1) * local_size - 1;
    for (i = my_first_row; i < my_last_row; i++) {
        for (j = 0; j < matrixSize; j++) {
            resultMatrix[i][j] = 0;
            for (k = 0; k < matrixSize; k++) {
                resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }
    return 0;
}

void fillMatrix(double** matrix, size_t matrixSize) {
    for (size_t i = 0; i < matrixSize; i++) {
        for (size_t j = 0; j < matrixSize; j++) {
            matrix[i][j] = rand() % matrixSize + 1 * 0.5;
        }
    }
}