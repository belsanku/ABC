#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>

#define MB 1000000
#define RAMTIME 0.000046882325363338
#define HDDTIME 150 * 0.00000001
#define SSDTIME 1500 * 0.000000001

using namespace std;
using namespace std::chrono;

struct Comma final : std::numpunct<char> {     char do_decimal_point() const override { return ','; } };

int sizeString (string str);
void fileWriting(int *arr, size_t arrSize, string filePath);
void menu();

int main(int argc, char* argv[]) {
    srand(time(NULL));
    string memoryType = "RAM";
    string tempBlockSize = "";
    int blockSize = 1;
    int launchCount = 1;;
    int j = 0;
    double sum = 0.0;

    cout.precision(12);
    cout.imbue(std::locale(std::locale::classic(), new Comma));
	auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto launchStart = high_resolution_clock::now();
    auto launchStop = high_resolution_clock::now();



    if (argc > 1) {
        memoryType = argv[2];
    }
    if (argc > 3) {
        blockSize = atoi(argv[4]);
    }
    if (argc > 5) {
        launchCount = atoi(argv[6]);
    }
    int arrSize = blockSize / sizeof(int);
    int * arr = new int [arrSize];

    for (int i = 0; i < arrSize; i++) {
        arr[i] = rand() % arrSize + 1;
    }
    duration<double> duration_t = duration_cast<microseconds>(stop - start);
    duration<double> launchDuration_t = duration_cast<microseconds>(stop - start);

    string filePath = "";
    if (memoryType == "RAM") {
        menu();
        j = launchCount;
        double * launchDuration = new double[launchCount];
        start = high_resolution_clock::now();
        while (j > 0) {
            launchStart = high_resolution_clock::now();
            for (int i = 0; i < arrSize; i++) {
                arr[i] = rand() % arrSize + 1;
            }
            launchStop = high_resolution_clock::now();
            launchDuration_t = duration_cast<microseconds>(launchStop - launchStart);
            launchDuration[launchCount - j] = launchDuration_t.count();
            sum += launchDuration_t.count();
            j--;
        }
        stop = high_resolution_clock::now();
        duration_t = duration_cast<microseconds>(stop - start);
        for (int i = 0; i < launchCount; i++) {
            cout << "RAM;"<< blockSize 
                << ";" << "int;" << arrSize << ";" <<  i + 1 
                << ";" << "now(), lib chrono;" << launchDuration[i] 
                << ";" <<  sum / launchCount << ";" << (blockSize / (sum / launchCount)) * MB << ";" << abs(RAMTIME - duration_t.count()) << ";" 
                << ((duration_t.count() / launchCount > RAMTIME / launchCount) ? (duration_t.count() / launchCount) / (RAMTIME / launchCount * 1024) :
                 (RAMTIME / launchCount) / (duration_t.count() / launchCount * 1024)) << "%;" << endl;
        }
        delete [] launchDuration;
    } else if (memoryType == "HDD") {
        menu();
        filePath = "/mnt/d/Over/memorytest.txt";
        j = launchCount;
        double * launchDuration = new double[launchCount];
        start = high_resolution_clock::now();
        while (j > 0) {
            launchStart = high_resolution_clock::now();
            fileWriting(arr, arrSize, filePath);
            launchStop = high_resolution_clock::now();
            launchDuration_t = duration_cast<microseconds>(launchStop - launchStart);
            launchDuration[launchCount - j] = launchDuration_t.count();
            sum += launchDuration_t.count();
            j--;
        }
        stop = high_resolution_clock::now();
        duration_t = duration_cast<microseconds>(stop - start);
        for (int i = 0; i < launchCount; i++) {
            cout << "HDD;"<< blockSize 
                << ";" << "int;" << arrSize << ";" <<  i + 1 
                << ";" << "now(), lib chrono;" << launchDuration[i] 
                << ";" <<  sum / launchCount << ";" << (blockSize / (sum / launchCount)) * MB << ";" << abs(HDDTIME - duration_t.count()) << ";" 
                << ((duration_t.count() / launchCount > HDDTIME / launchCount) ? (duration_t.count() / launchCount) / (HDDTIME / launchCount * 1024000) :
                 (HDDTIME / launchCount) / (duration_t.count() / launchCount * 1024000)) << "%;" << endl;
        }
        delete [] launchDuration;
    } else if (memoryType == "SSD") {
        menu();
        filePath = "/mnt/c/Over/memorytest.txt";
        j = launchCount;
        double * launchDuration = new double[launchCount];
        start = high_resolution_clock::now();
        while (j > 0) {
            launchStart = high_resolution_clock::now();
            fileWriting(arr, arrSize, filePath);
            launchStop = high_resolution_clock::now();
            launchDuration_t = duration_cast<microseconds>(launchStop - launchStart);
            launchDuration[launchCount - j] = launchDuration_t.count();
            sum += launchDuration_t.count();
            j--;
        }
        stop = high_resolution_clock::now();
        duration_t = duration_cast<microseconds>(stop - start);
        for (int i = 0; i < launchCount; i++) {
            cout << "SSD;"<< blockSize 
                << ";" << "int;" << arrSize << ";" <<  i + 1 
                << ";" << "now(), lib chrono;" << launchDuration[i] 
                << ";" <<  sum / launchCount << ";" << (blockSize / (sum / launchCount)) * MB << ";" << abs(SSDTIME - duration_t.count()) << ";" 
                << ((duration_t.count() / launchCount > SSDTIME / launchCount) ? (duration_t.count() / launchCount) / (SSDTIME / launchCount * 10240000) :
                 (SSDTIME / launchCount) / (duration_t.count() / launchCount * 102400)) << "%;" << endl;
        }
        delete [] launchDuration;
    } else if (memoryType == "flash") {
        menu();
        filePath = "/mnt/d/Over/memorytest.txt";
        j = launchCount;
        double * launchDuration = new double[launchCount];
        start = high_resolution_clock::now();
        while (j > 0) {
            launchStart = high_resolution_clock::now();
            fileWriting(arr, arrSize, filePath);
            launchStop = high_resolution_clock::now();
            launchDuration_t = duration_cast<microseconds>(launchStop - launchStart);
            launchDuration[launchCount - j] = launchDuration_t.count();
            sum += launchDuration_t.count();
            j--;
        }
        stop = high_resolution_clock::now();
        duration_t = duration_cast<microseconds>(stop - start);
        for (int i = 0; i < launchCount; i++) {
            cout << "flash;"<< blockSize 
                << ";" << "int;" << arrSize << ";" <<  i + 1 
                << ";" << "now(), lib chrono;" << launchDuration[i] 
                << ";" <<  sum / launchCount << ";" << (blockSize / (sum / launchCount)) * MB << ";" << abs(HDDTIME - duration_t.count()) << ";" 
                << ((duration_t.count() / launchCount > HDDTIME / launchCount) ? (duration_t.count() / launchCount) / (HDDTIME / launchCount * 1024) :
                 (HDDTIME / launchCount) / (duration_t.count() / launchCount * 1024)) << "%;" << endl;
        }
        delete [] launchDuration;
    } else {
        cout << "invalid input" << endl;
        return 1;
    }
    delete [] arr;
    return 0;
}

int sizeString (string str) {
    string temp = "";
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == '|') {
            break;
        }
        temp += str[i];
    }
    return stoi(temp);
}

void fileWriting(int *arr, size_t arrSize, string filePath) {
    ofstream out;
    out.open(filePath);
    if (!out.is_open()) {
        cout << "open error" << endl;
        return;
    }
    //cout << arrSize << endl;
    for (size_t i = 0; i < arrSize; i++) {
        out << arr[i];
    }
    out.close();
}

void menu() {
    cout << "MemoryType;" << "BlockSize;" << "ElementType;" << "BufferSize;"
            << "LaunchNum;" << "Timer;" << "WriteTime;" 
            << "AverageWriteTime;" << "WriteBandwidth;" << "AbsError(write);"
            << "RelError(write);" << endl;
}