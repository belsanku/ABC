#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void dgemmBlas(double **firstMatrix, double **secondMatrix, double **result, size_t matrixSize);
void fillMatrix(double **a, size_t matrixSize);
void saxpyBlas(size_t matrixSize);



int main(int argc, char* argv[]) {
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    duration<double> duration_t = duration_cast<microseconds>(stop - start);
    size_t matrixSize = 1;
    if (argc > 1) {
        matrixSize = atoi(argv[1]);
    }
    double **firstMatrix = new double*[matrixSize];
    double **secondMatrix = new double*[matrixSize];
    double **resultMatrix = new double*[matrixSize];
    for (size_t i = 0; i < matrixSize; i++) {
        firstMatrix[i] = new double[matrixSize];
        secondMatrix[i] = new double[matrixSize];
        resultMatrix[i] = new double[matrixSize];
    }
    fillMatrix(firstMatrix, matrixSize);
    fillMatrix(secondMatrix, matrixSize);
    start = high_resolution_clock::now();
    //dgemmBlas(firstMatrix, secondMatrix, resultMatrix, matrixSize);
    saxpyBlas(matrixSize);
    stop = high_resolution_clock::now();
    duration_t = duration_cast<microseconds>(stop - start);
    cout << matrixSize << ";" << duration_t.count() << endl;
    for (size_t i = 0; i < matrixSize; i++) {
        delete []firstMatrix[i];
        delete []secondMatrix[i];
        delete []resultMatrix[i];
    }
    delete []firstMatrix;
    delete []secondMatrix;
    delete []resultMatrix;
    return 0;
}

void saxpyBlas(size_t matrixSize)
{
    size_t N = matrixSize * matrixSize;
    double *vector = (double*) malloc(sizeof(double) * N);
    double *X = (double*) malloc(sizeof(double) * N);
    double *Y = (double*) malloc(sizeof(double) * N);
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

void dgemmBlas(double **firstMatrix, double **secondMatrix, double **result, size_t matrixSize) {
    for (size_t i = 0; i < matrixSize; i++) {
        for (size_t j = 0; j < matrixSize; j++) {
            result[i][j] = 0;
            for (size_t k = 0; k < matrixSize; k++) {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }
}

void fillMatrix(double **matrix, size_t matrixSize) {
    for (size_t i = 0; i < matrixSize; i++) {
        for (size_t j = 0; j < matrixSize; j++) {
            matrix[i][j] = rand() % matrixSize + 1 * 0.5;
        }
    }
}