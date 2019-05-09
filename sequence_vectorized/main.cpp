#include <iostream>
#include <math.h>
#include <string>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <map>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <chrono>
#include <omp.h>

typedef unsigned long long T_NUM;
typedef std::vector<T_NUM> T_NUM_VEC;
typedef std::vector<T_NUM_VEC> T_NUM_VEC_VEC;
typedef std::string T_STR;

bool isPrime(T_NUM num);

/**
 * Simple get true if number is primary
 * @param num
 * @return
 */
bool isPrime(T_NUM num) {
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (T_NUM i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

int charToInt(char c) {
    int result = c;
    switch (result) {
        case 48:
            return 0;
        case 49:
            return 1;
        case 50:
            return 2;
        case 51:
            return 3;
        case 52:
            return 4;
        case 53:
            return 5;
        case 54:
            return 6;
        case 55:
            return 7;
        case 56:
            return 8;
        case 57:
            return 9;
        default:
            return 0;
    }
}

std::ofstream fileData;

const T_NUM NUM_THREADS = 12;
std::chrono::system_clock::time_point timeLast = std::chrono::high_resolution_clock::now();

void printLine(T_STR content) {
    printf("%s\n", content.c_str());
}

double getPercent(T_NUM threadNum) {
    switch (threadNum) {
        case 0:
            return 0.35;
        case 1:
            return 0.11;
        case 2:
            return 0.09;
        case 3:
            return 0.08;
        case 4:
            return 0.07;
        case 5:
            return 0.06;
        case 6:
            return 0.05;
        case 7:
            return 0.04;
        case 8:
            return 0.04;
        case 9:
            return 0.04;
        case 10:
            return 0.04;
        case 11:
            return 0.03;
    }
}

T_NUM getStart(T_NUM threadNum, T_NUM base) {
    T_NUM result = 0;
    for (T_NUM i = 0; i < threadNum; i++) {
        result += ((T_NUM) ceil(getPercent(i) * base));
    }
    return result;
}

T_NUM getEnd(T_NUM threadNum, T_NUM base) {
    if (threadNum + 1 == NUM_THREADS) {
        return base;
    }
    T_NUM result = 0;
    for (T_NUM i = 0; i < threadNum + 1; i++) {
        result += ((T_NUM) ceil(getPercent(i) * base));
    }
    return result;
}

int main() {
    /*for (T_NUM i = 0; i < NUM_THREADS; i += 1) {
        T_NUM start = getStart(i, 1000);
        T_NUM end = getEnd(i, 1000);
        std::cout << "start: " << start << " end: " << end << std::endl;
    }

    return 0;*/

    /*double _base = 0.9;
    double sum = 0;
    for (T_NUM i = 0; i < NUM_THREADS; i += 1) {
        sum += _base;
        _base /= 10;
    }

    printLine(std::to_string(sum));
    return 0;*/

    std::chrono::system_clock::time_point timeStart = std::chrono::high_resolution_clock::now();

    printLine("Starting");
    omp_set_num_threads(NUM_THREADS);

    T_NUM_VEC numbers;

    fileData.open("./numbers.txt");

    numbers.push_back(3);
    numbers.push_back(5);
    numbers.push_back(7);

    T_NUM_VEC_VEC vec((size_t) NUM_THREADS);
    T_NUM base = 4096 * 4096 * 64;

    T_NUM _currentPercent = 0;

    printLine("Generating");

#pragma omp parallel
    {
        int threadNum = omp_get_thread_num();

        T_NUM_VEC found;
        std::chrono::system_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
        T_NUM _lastPercent = 0;

        for (T_NUM i = (base * threadNum), current = 0; i < ((threadNum + 1) * base); i += 1, current += 1) {
            T_NUM two = i * 2;
            T_NUM firstNum = 5 + i;
            T_NUM secondNum = 4 + i;

            T_NUM num = firstNum + secondNum + (2 * two) + 2;
            T_STR numSTR = std::to_string(num);
            T_NUM sum = 0;

            for (T_NUM j = 0; j < numSTR.length(); j++) {
                sum += charToInt(numSTR[j]);
            }

            if (charToInt(numSTR[numSTR.length() - 1]) != charToInt('5') && sum % 3 != 0 && num % 7 != 0 &&
                num % 11 != 0) {
                vec[threadNum].push_back(num);
            }

            _currentPercent = (T_NUM) (double(current) / double(base) * 100.0);
            if (_currentPercent != _lastPercent) {
                _lastPercent = _currentPercent;
                printLine("THREAD: " + std::to_string((int) threadNum) + ", PERCENT: " +
                          std::to_string((int) _lastPercent));
            }
        }

#pragma omp critical
        {
            printLine("Merging... (" + std::to_string(threadNum) + ")");
            numbers.insert(numbers.end(), vec[threadNum].begin(), vec[threadNum].end());
            printLine("Merged... (" + std::to_string(threadNum) + ")");
        };
    };

    std::sort(numbers.begin(), numbers.end());

    T_NUM numbersSize = numbers.size();
    T_NUM_VEC numbers2;

    auto base2 = (T_NUM) numbersSize / NUM_THREADS;

    printLine("Checking");

#pragma omp parallel
    {
        auto threadNum = (T_NUM) omp_get_thread_num();

        T_NUM_VEC found;
        T_NUM _lastPercent = 0;

        std::chrono::system_clock::time_point timeStart = std::chrono::high_resolution_clock::now();

        T_NUM start = getStart(threadNum, base2);
        T_NUM end = getEnd(threadNum, base2);

        for (T_NUM i = start, current = 0; i < end; i += 1, current += 1) {
            if (i < numbersSize) {
                bool _isPrime = true;
                for (size_t j = 0; j < numbersSize; j += 1) {
                    if (numbers[j] * 2 < numbers[i]) {
                        if (numbers[i] % numbers[j] == 0) {
                            _isPrime = false;
                            break;
                        }
                    } else {
                        break;
                    }
                }
                if (_isPrime) {
                    found.push_back(numbers[i]);
                }
            }

            _currentPercent = (T_NUM) (double(current) / double(end - start) * 100.0);
            if (_currentPercent != _lastPercent) {
                _lastPercent = _currentPercent;
                T_STR buffer = "THREAD: " + std::to_string((int) threadNum) + ", PERCENT: " +
                               std::to_string((int) _lastPercent);
                printLine(buffer);
            }
        }

#pragma omp critical
        {
            std::chrono::system_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
            long seconds = std::chrono::duration_cast<std::chrono::seconds>(timeEnd - timeStart).count();

            std::cout << "SECONDS (" << threadNum << "): " << seconds << std::endl;

            printLine("Merging... (" + std::to_string(threadNum) + ")");
            numbers2.insert(numbers2.end(), found.begin(), found.end());
            printLine("Merged... (" + std::to_string(threadNum) + ")");
            printLine("Seconds: " + std::to_string(seconds) + " (" + std::to_string(threadNum) + ")");
        };
    };

    std::chrono::system_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
    long minutes = std::chrono::duration_cast<std::chrono::minutes>(timeEnd - timeStart).count();

    printLine("DURATION: " + std::to_string(minutes));

    std::sort(numbers2.begin(), numbers2.end());

    T_NUM notPrimeCount = 0;
    for (size_t i = 0; i < numbers2.size(); i += 1) {
        fileData << numbers2[i] << "\n";
        if (!isPrime(numbers2[i])) {
            notPrimeCount++;
        }
    }
    fileData.close();

    printLine("NOT PRIME COUNT: " + std::to_string((int) notPrimeCount));


    return 0;
}