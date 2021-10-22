#include <math.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>

#define MHz 3600.000

using namespace std;
using namespace std::chrono;

struct Comma final : std::numpunct<char> {     char do_decimal_point() const override { return ','; } };

int64_t fact(int64_t a);

int main(int argc, char* argv[]) {
	srand(time(NULL));
	setlocale(LC_ALL, "EN");
	double RealError = 0.0, TaskPerf = 0.0;
	int64_t n = 1 + (rand() % 20);
	float f_n = n + 0.1;
	int i = 1;
	if (argc > 1)
		i = atoi(argv[1]);
	auto start_temp = high_resolution_clock::now();
	auto stop_temp = high_resolution_clock::now();
	auto start = high_resolution_clock::now();
	while (i-- > 1) {
		start_temp = high_resolution_clock::now();
		fact(n);
		stop_temp = high_resolution_clock::now();
	}
	auto stop = high_resolution_clock::now();
	duration<double> duration_temp = duration_cast<microseconds>(stop_temp - start_temp);
	duration<double> duration_t = duration_cast<microseconds>(stop - start);
	i = 1;
	if (argc > 1)
		i = atoi(argv[1]);
	cout.precision(8);
	cout.imbue(std::locale(std::locale::classic(), new Comma));
	cout << fixed << "Task:;factorial" << endl;
	cout << "OpType:;int64_t (long lnog)" << endl;
	cout << "Opt:;None" << endl;
	cout << "InsCount:;" << i << endl;
	cout << "Timer:;now(), lib chrono" << endl;
	cout << "Time:;" << duration_temp.count() << endl;
	cout << "LNum:;1" << endl;
	cout << "AllTime:;" << duration_t.count() << endl;
	cout << "AvgTime:;" << duration_t.count() / i << endl;
	cout << "AbsError:;" << abs(i / (MHz * 1000 * 1000000) - duration_t.count() / i) << endl;
	if ((i / (MHz * 1000 * 1000000) > duration_t.count() / i)) {
		RealError = ((i / (MHz * 1000 * 1000000)) / (duration_t.count() / i));
	} else {
		RealError = ((duration_t.count() / i) / (i / (MHz * 1000 * 1000000)));
	}
	cout << "RelError:;" << RealError << "%" << endl;
	TaskPerf = 100.0 - RealError;
	cout << "TaskPerf:;" << TaskPerf << endl;
	start = high_resolution_clock::now();
	while (i-- > 1) {
		start_temp = high_resolution_clock::now();
		log(n);
		stop_temp = high_resolution_clock::now();
	}
	stop = high_resolution_clock::now();
	duration_temp = std::chrono::microseconds::zero();
	duration_t = std::chrono::microseconds::zero();
	duration_temp = duration_cast<microseconds>(stop_temp - start_temp);
	duration_t = duration_cast<microseconds>(stop - start);
	i = 1;
	if (argc > 1)
		i = atoi(argv[1]);
	cout << endl << "Task:;log" << endl;
	cout << "OpType:;int64_t (long lnog)" << endl;
	cout << "Opt:;None" << endl;
	cout << "InsCount:;" << i << endl;
	cout << "Timer:;now(), lib chrono" << endl;
	cout << "Time:;" << duration_temp.count() << endl;
	cout << "LNum:;2" << endl;
	cout << "AllTime:;" << duration_t.count() << endl;
	cout << "AvgTime:;" << duration_t.count() / i << endl;
	cout << "AbsError:;" << abs(i / (MHz * 1000 * 1000000) - duration_t.count() / i) << endl;
	if ((i / (MHz * 1000 * 1000000) > duration_t.count() / i)) {
		RealError = ((i / (MHz * 1000 * 1000000)) / (duration_t.count() / i));
	} else {
		RealError = ((duration_t.count() / i) / (i / (MHz * 1000 * 1000000)));
	}
	cout << "RelError:;" << RealError << "%" << endl;
	TaskPerf = 100.0 - RealError;
	cout << "TaskPerf:;" << TaskPerf << endl;
	start = high_resolution_clock::now();
	while (i-- > 1) {
		start_temp = high_resolution_clock::now();
		powf(f_n, f_n);
		stop_temp = high_resolution_clock::now();
	}
	stop = high_resolution_clock::now();
	duration_temp = std::chrono::microseconds::zero();
	duration_t = std::chrono::microseconds::zero();
	duration_temp = duration_cast<microseconds>(stop_temp - start_temp);
	duration_t = duration_cast<microseconds>(stop - start);
	i = 1;
	if (argc > 1)
		i = atoi(argv[1]);
	cout << endl << "Task:;powf" << endl;
	cout << "OpType:;float" << endl;
	cout << "Opt:;None" << endl;
	cout << "InsCount:;" << i << endl;
	cout << "Timer:;now(), lib chrono" << endl;
	cout << "Time:;" << duration_temp.count() << endl;
	cout << "LNum:;3" << endl;
	cout << "AllTime:;" << duration_t.count() << endl;
	cout << "AvgTime:;" << duration_t.count() / i << endl;
	cout << "AbsError:;" << abs(i / (MHz * 1000 * 1000000) - duration_t.count() / i) << endl;
	if ((i / (MHz * 1000 * 1000000) > duration_t.count() / i)) {
		RealError = ((i / (MHz * 1000 * 1000000)) / (duration_t.count() / i));
	} else {
		RealError = ((duration_t.count() / i) / (i / (MHz * 1000 * 1000000)));
	}
	cout << "RelError:;" << RealError << "%" << endl;
	TaskPerf = 100.0 - RealError;
	cout << "TaskPerf:;" << TaskPerf << endl;
	return 0;
}

int64_t fact(int64_t a) {
	int64_t s = 1;
	while (a > 0) {
		s *= a;
		a--;
	}
	return s;
}
