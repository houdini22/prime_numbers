#include <iostream>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <map>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <chrono>
#include <omp.h>
#include "BigIntegerLibrary.h"

typedef BigInteger T_NUM;
typedef std::vector<T_NUM> T_NUM_VEC;
typedef std::vector<T_NUM_VEC> T_NUM_VEC_VEC;
typedef std::string T_STR;
typedef std::vector<T_STR> T_STR_VEC;
struct RET_TYPE {
    T_NUM_VEC allPrimes;
    T_NUM lastCycle;
};

bool isPrime(T_NUM num) {
    if (num < 2) return false;
    if (num == 2) return true;

    for (T_NUM i = 2; i * i <= num; i = i + 1) {
        if (num % i == 0) return false;
    }
    return true;
}

T_NUM NUM_THREADS = 12;

RET_TYPE execute(T_NUM rangeStart, T_NUM_VEC allPrimes, T_NUM_VEC_VEC multiplePrimes) {

    T_NUM last = allPrimes[allPrimes.size() - 1];
    T_NUM limit = last * last;
    T_NUM block = (limit - rangeStart) / T_NUM(6) + 1;
    T_NUM lastCycle = rangeStart;

    printf("\tRANGE START = %s\tLIMIT: %s\n", bigIntegerToString(rangeStart).c_str(), bigIntegerToString(limit).c_str());

#pragma omp parallel
    {
        T_NUM threadNum = T_NUM(omp_get_thread_num());
        T_NUM blockStart = rangeStart + (block / NUM_THREADS) * (threadNum * 6);
        T_NUM blockEnd = rangeStart + (block / NUM_THREADS) * ((threadNum + 1) * 6);
        if (threadNum == (NUM_THREADS - T_NUM(1))) {
            blockEnd = limit;
        }

        T_NUM rangeEnd = blockStart + 6;
        T_NUM_VEC found;

        //printf("START %i\t\tEND %i\n", (int) blockStart, (int) blockEnd);

        for (T_NUM i = T_NUM(0);
             blockStart < blockEnd;
             blockStart = blockStart + 6, rangeEnd = rangeEnd + T_NUM(6), i = i + T_NUM(1)
                ) {
            for (
                    T_NUM num = blockStart + T_NUM(2);
                    num <= rangeEnd - T_NUM(2);
                    num = num + T_NUM(2)
                    ) {
                bool _isPrime = true;

                for (size_t p = 0; p < allPrimes.size(); p += 1) {
                    T_NUM prime = allPrimes[p];

                    if (num % prime == T_NUM(0)) {
                        _isPrime = false;
                        break;
                    }
                }

                if (_isPrime) {
                    found.push_back(num);
                }

                if (!_isPrime && isPrime(num)) {
                    printf("ERR: %s\n", bigIntegerToString(num).c_str());
                }
            }
        }

#pragma omp critical
        {
            if (threadNum == T_NUM(0)) {
                printf("Merging thread...\n");
            }

            multiplePrimes.at((size_t) threadNum.toLong()).insert(multiplePrimes.at((size_t) threadNum.toLong()).end(), found.begin(), found.end());
            if (rangeEnd - T_NUM(6) > lastCycle) {
                lastCycle = rangeEnd - T_NUM(6);
            }

            if (threadNum == T_NUM(0)) {
                printf("Thread merged...\n");
            }
        };
    };
#pragma omp barrier

    printf("Global merge...\n");

    // merge and clear
    for (T_NUM i = T_NUM(0); i < NUM_THREADS; i = i + T_NUM(1)) {
        allPrimes.insert(allPrimes.end(), multiplePrimes[(size_t) i.toLong()].begin(), multiplePrimes[(size_t) i.toLong()].end());
        multiplePrimes[(size_t) i.toLong()].empty();
    }

    printf("Global sort...\n");

    // sort
    std::sort(allPrimes.begin(), allPrimes.end());

    printf("Global unique...\n");

    // unique
    auto it = std::unique(allPrimes.begin(), allPrimes.end());
    allPrimes.resize(std::distance(allPrimes.begin(), it));

    printf("Done.\n");

    // result
    RET_TYPE result;
    result.allPrimes = allPrimes;
    result.lastCycle = lastCycle;

    return result;
}

std::ofstream file;

int main() {
    omp_set_num_threads(NUM_THREADS.toInt());

    auto start = std::chrono::system_clock::now();

    T_NUM_VEC_VEC multiplePrimes((size_t) NUM_THREADS.toLong());

    T_NUM_VEC allPrimes;
    allPrimes.push_back(T_NUM(2));
    allPrimes.push_back(T_NUM(3));

    T_NUM lastCycle = T_NUM(3);
    T_NUM rangeStart = lastCycle;
    T_NUM block;
    T_NUM limit;

    for (T_NUM cycle = T_NUM(0); cycle < T_NUM(3); cycle = cycle + T_NUM(1)) {
        T_NUM last = allPrimes[allPrimes.size() - 1];
        T_NUM limit = last * last;
        rangeStart = lastCycle;
        block = (limit - rangeStart) / T_NUM(6) + 1;

        printf("\tRANGE START = %s\tLIMIT: %s\n", bigIntegerToString(rangeStart).c_str(), bigIntegerToString(limit).c_str());

        if (block < NUM_THREADS) {
            for (
                    T_NUM rangeEnd = rangeStart + 6;
                    rangeStart < limit;
                    rangeStart = rangeStart + 6, rangeEnd = rangeEnd + 6
                    ) {
                for (
                        T_NUM num = T_NUM(rangeStart) + T_NUM(2);
                        num <= T_NUM(rangeEnd) - T_NUM(2);
                        num = num + T_NUM(2)
                        ) {
                    bool _isPrime = true;

                    for (size_t p = 0; p < allPrimes.size(); p += 1) {
                        T_NUM prime = allPrimes[p];

                        if (num % prime == T_NUM(0)) {
                            _isPrime = false;
                            break;
                        }
                    }

                    if (_isPrime) {
                        allPrimes.push_back(num);
                    }

                    lastCycle = rangeEnd;
                }
            }

            std::sort(allPrimes.begin(), allPrimes.end());
            auto it = std::unique(allPrimes.begin(), allPrimes.end());
            allPrimes.resize(std::distance(allPrimes.begin(), it));
        } else {
            break;
        }

        printf("CYCLE: %s\tFOUND: %i\n", bigIntegerToString(lastCycle).c_str(), (int) allPrimes.size());
    }

    RET_TYPE result;

    result = execute(rangeStart, allPrimes, multiplePrimes);
    allPrimes = result.allPrimes;
    rangeStart = result.lastCycle;

    printf("CYCLE: %s\tFOUND: %i\n", bigIntegerToString(lastCycle).c_str(), (int) allPrimes.size());

    result = execute(rangeStart, allPrimes, multiplePrimes);
    allPrimes = result.allPrimes;
    rangeStart = result.lastCycle;

    printf("CYCLE: %s\tFOUND: %i\n", bigIntegerToString(lastCycle).c_str(), (int) allPrimes.size());

    result = execute(rangeStart, allPrimes, multiplePrimes);
    allPrimes = result.allPrimes;
    rangeStart = result.lastCycle;

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    printf("ELAPSED: %i\n", (int) elapsed);
    printf("GENERATED: %i\n", (int) allPrimes.size());

    file.open("./numbers.txt");
    for (size_t i = 0; i < allPrimes.size(); i = i + 1) {
        file << allPrimes[i] << "\n";
    }
    file.close();

    return 0;
}