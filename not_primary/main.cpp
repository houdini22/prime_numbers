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
#include "bigInt.h"

typedef unsigned long long T_NUM;
typedef std::vector<T_NUM> T_NUM_VEC;
typedef std::string T_STR;
typedef std::vector<T_STR> T_STR_VEC;

T_NUM charToNUM(char c) {
    int result = c;
    switch (result) {
        case 48:
            return T_NUM(0);
        case 49:
            return T_NUM(1);
        case 50:
            return T_NUM(2);
        case 51:
            return T_NUM(3);
        case 52:
            return T_NUM(4);
        case 53:
            return T_NUM(5);
        case 54:
            return T_NUM(6);
        case 55:
            return T_NUM(7);
        case 56:
            return T_NUM(8);
        case 57:
            return T_NUM(9);
        default:
            return T_NUM(0);
    }
}

bool isPrime(T_NUM num) {
    if (num <= T_NUM(0)) return false;

    for (T_NUM i(3); i < num; i = i + 1) {
        if (num % i == T_NUM(0)) return false;
    }
    return true;
}

const T_NUM NUM_THREADS = T_NUM(12);

int main() {
    //T_NUM base(T_NUM(4096 * 4096) * T_NUM(4096));

/*#pragma omp parallel
    {*/
    /*int threadNum = omp_get_thread_num();
    T_NUM i(base * threadNum);
    T_NUM max(base * (threadNum + 1));
    T_NUM current(0);*/

    T_NUM _i(T_NUM(2));
    T_NUM _max(T_NUM(2208));
    T_NUM_VEC vec;
    /*while (_i < _max) {
        if (isPrime(_i)) {
            vec.push_back(_i);
        }
        _i++;
    }*/

    /*T_NUM i(T_NUM(0));
    T_NUM max(T_NUM(100));*/
    auto start = std::chrono::system_clock::now();

    T_NUM_VEC allPrimes;
    allPrimes.push_back(T_NUM(2));
    allPrimes.push_back(T_NUM(3));

    T_NUM lastCycle = T_NUM(3);

#pragma omp
    for (T_NUM cycle = T_NUM(0); cycle < T_NUM(3); cycle = cycle + T_NUM(1)) {
        T_NUM last = allPrimes[allPrimes.size() - 1];
        T_NUM limit = last * last;
        T_NUM rangeStart = lastCycle;
        T_NUM block = (limit - rangeStart) / T_NUM(6);

        printf("\tRANGE START = %i\tLIMIT: %i\tBLOCK: %i\n", (int) rangeStart, (int) limit, (int) block);

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

                        if (prime * prime > num) {
                            break;
                        }
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

#pragma omp parallel
            {
                T_NUM threadNum = T_NUM(omp_get_thread_num());
                T_NUM blockStart = rangeStart + (block / NUM_THREADS) * threadNum * 6;// + (block * 6) / NUM_THREADS * threadNum;
                T_NUM blockEnd = rangeStart + (block / NUM_THREADS) * (threadNum + 1) * 6;// + (block * 6) / NUM_THREADS * (threadNum + 1);
                T_NUM rangeEnd = blockStart + 6;

                T_NUM_VEC localPrimes;

                printf("START %i\t\tEND %i\n", (int) blockStart, (int) blockEnd);

                for (;
                        blockStart < blockEnd;
                        blockStart = blockStart + 6, rangeEnd = rangeEnd + 6
                        ) {
                    /*for (
                            T_NUM num = blockStart + T_NUM(2);
                            num <= rangeEnd - T_NUM(2);
                            num = num + T_NUM(2)
                            ) {
                        bool _isPrime = true;

                        for (size_t p = 0; p < allPrimes.size(); p += 1) {
                            T_NUM prime = allPrimes[p];

                            if (prime * prime > num) {
                                break;
                            }
                            if (num % prime == T_NUM(0)) {
                                _isPrime = false;
                                break;
                            }
                        }

                        if (_isPrime) {
                            localPrimes.push_back(num);
                        }
                    }*/
                    if (isPrime(blockStart)) {
                        printf("%i\n", (int) blockStart);
                    }
                }

#pragma omp critical
                {
                    allPrimes.insert(allPrimes.end(), localPrimes.begin(), localPrimes.end());

                    std::sort(allPrimes.begin(), allPrimes.end());
                    auto it = std::unique(allPrimes.begin(), allPrimes.end());
                    allPrimes.resize(std::distance(allPrimes.begin(), it));
                };
            };
        }
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    for (size_t i = 0; i < allPrimes.size(); i += 1) {
        if (!isPrime(allPrimes[i])) {
            printf("ERROR: %i\n", (int) allPrimes[i]);
        }
    }

    /*for (size_t i = 0; i < allPrimes.size(); i += 1) {
        printf("%i\n", (int) allPrimes[i]);
    }*/

    printf("ELAPSED: %i\n", (int) elapsed);
    printf("COMPUTED: %i\tGENERATED: %i\n", (int) vec.size(), (int) allPrimes.size());

    /*for (T_NUM i = T_NUM(0),
                 num_1_1 = i + 3, num_1_2 = i + 4, four_1 = i * 4,
                 num_1 = num_1_1 + num_1_2 + four_1 + 2,
                 num_2_1 = (i + 1) + 3, num_2_2 = (i + 1) + 4, four_2 = (i + 1) * 4,
                 num_2 = num_2_1 + num_2_2 + four_2 + 2;
         num_1 < last * last;
         i = i + 1,
         num_1_1 = i + 3, num_1_2 = i + 4, four_1 = i * 4,
         num_1 = num_1_1 + num_1_2 + four_1 + 2,
         num_2_1 = (i + 1) + 3, num_2_2 = (i + 1) + 4, four_2 = (i + 1) * 4,
         num_2 = num_2_1 + num_2_2 + four_2 + 2) {

        if (isPrime(num_1)) {
            printf("IS PRIME: %s %s\n", i.toStrDec().c_str(), num_1.toStrDec().c_str());
        } else {
            printf("\tPRIME ERROR\t: num = %s\ti = %s\tfirstNum = %s\tsecondNum = %s\tfour = %s\ttest = %s\n",
                   (num_1).toStrDec().c_str(),
                   (i + 1).toStrDec().c_str(),
                   num_1_1.toStrDec().c_str(),
                   num_1_2.toStrDec().c_str(),
                   four_1.toStrDec().c_str(),
                   last.toStrDec().c_str());
        }

        printf("------------\n");

        if (isPrime(num_2)) {
            printf("IS PRIME: %s %s\n", i.toStrDec().c_str(), num_2.toStrDec().c_str());
        } else {
            printf("\tPRIME ERROR\t: num = %s\ti = %s\tfirstNum = %s\tsecondNum = %s\tfour = %s\ttest = %s\n",
                   (num_2).toStrDec().c_str(),
                   (i + 1).toStrDec().c_str(),
                   num_1_1.toStrDec().c_str(),
                   num_1_2.toStrDec().c_str(),
                   four_1.toStrDec().c_str(),
                   last.toStrDec().c_str());
        }

        printf("\n\n\n");
    }*/

    /*while (i < max) {
        T_NUM last = allPrimes[allPrimes.size() - 1];

        T_NUM firstNum = i + 3;
        T_NUM secondNum = i + 4;
        T_NUM two = i * 4;
        T_NUM num = firstNum + secondNum + two + 2;

        if (isPrime(num)) {
            printf("IS PRIME: %s %s\n", i.toStrDec().c_str(), num.toStrDec().c_str());
        } else {
            printf("\tPRIME ERROR\t: num = %s\ti = %s\tfirstNum = %s\tsecondNum = %s\tfour = %s\ttest = %s\n",
                   (num).toStrDec().c_str(),
                   (i + 1).toStrDec().c_str(),
                   firstNum.toStrDec().c_str(),
                   secondNum.toStrDec().c_str(),
                   two.toStrDec().c_str(),
                   last.toStrDec().c_str());
        }

        if (last * last < num) {
            break;
        }

        i++;
    }*/
/*
#pragma omp critical
        {
        };
    };*/

    //printf("DETECTED: correct: %s\t wrong: %s\n", correctPrimesDetected.toStrDec().c_str(), wrongPrimesDetected.toStrDec().c_str());
    //printf("COMPUTED: correct: %s\t wrong: %s\n", correctPrimesComputed.toStrDec().c_str(), wrongPrimesComputed.toStrDec().c_str());

    return 0;
}