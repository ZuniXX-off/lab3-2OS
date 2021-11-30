#include <iostream>
#include <omp.h>
#include <iomanip>
#include <windows.h>

const uint64_t blockSize = 10 * 11;
const uint64_t N = 100'000'000;
const long double invN = 1.0 / N;

int main()
{
    system("chcp 1251");
    system("cls");
    int numThreads;
    long double pi = 0;
    long double xi = 0;

    std::cout << " Введите количество потоков: ";
    std::cin >> numThreads;

    int startTime = GetTickCount();

#pragma omp parallel for schedule(dynamic, blockSize) private(xi) num_threads(numThreads) reduction (+:pi)

    for (long long i = 0; i < N; i++) {
        xi = (0.5 + i) * invN;
        pi += (4.0 / (1.0 + xi * xi));
    }

    pi *= invN;
    int endTime = GetTickCount();

    std::cout << " Время вычислений: " << endTime - startTime << std::endl
        << " Результат работы: " << std::setprecision(15) << pi;

    return 0;
}
