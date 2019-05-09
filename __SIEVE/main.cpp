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

typedef BigInt::Rossi T_NUM;
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
    if (num < T_NUM(3)) return false;
    T_STR result = (num % T_NUM(2)).toStrDec();
    if (charToNUM(result[0]) == charToNUM('0')) return false;

    for (T_NUM i(3); i * i <= num; i = i + 1) {
        T_STR result = (num % i).toStrDec();
        if (charToNUM(result[0]) == charToNUM('0')) return false;
    }
    return true;
}

int main() {
    //T_NUM base(T_NUM(4096 * 4096) * T_NUM(4096));

/*#pragma omp parallel
    {*/
    /*int threadNum = omp_get_thread_num();
    T_NUM i(base * threadNum);
    T_NUM max(base * (threadNum + 1));
    T_NUM current(0);*/

    T_NUM_VEC allPrimes;
    allPrimes.push_back(T_NUM(3));
    allPrimes.push_back(T_NUM(5));
    allPrimes.push_back(T_NUM(7));

    for (T_NUM i = T_NUM(1), j = T_NUM(0); i < T_NUM(100000); i = i + T_NUM(2), j = j + T_NUM(1)) {
        if (i == T_NUM(1)) continue;

        if (j % T_NUM(1000) == T_NUM(0)) {
            printf("%s\n", j.toStrDec().c_str());
        }

        bool cont = false;
        for (size_t j = 0; j < allPrimes.size(); j++) {
            if (i % allPrimes[j] == T_NUM(0)) {
                cont = true;
                break;
            }
        }

        if (cont) {
            continue;
        }

        allPrimes.push_back(i);
    }

    for (int __i = 0; __i < allPrimes.size(); __i += 1) {
        if (isPrime(allPrimes[__i])) {
            printf("IS PRIME: %s\n", allPrimes[__i].toStrDec().c_str());
        } else {
            printf("PRIME ERROR %s\n", allPrimes[__i].toStrDec().c_str());
        }
    }
/*
    while (i < max) {*/

        /*if (i % T_NUM(2) == T_NUM(0)) {
            T_NUM num2 = num + mod2Plus;

            if (isPrime(num2)) {
            } else {
                //printf("PRIME ERROR mod 2 = 0 + 2 i = %s\tnum = %s\n", i.toStrDec().c_str(), num2.toStrDec().c_str());
                //printf("i = %s, sec = %s\n", i.toStrDec().c_str(), (i - T_NUM(2)).toStrDec().c_str());
            }
        }*/

        /*if (i > T_NUM(0)) {
            if (i % T_NUM(2) == T_NUM(0)) {
                T_NUM num2 = num + (i * i) + (i - T_NUM(2)) * T_NUM(2);

                if (isPrime(num2)) {
                    //printf("IS PRIME: %s %s\n", i.toStrDec().c_str(), num2.toStrDec().c_str());
                } else {
                    printf("PRIME ERROR mod 2 = 0 + 2 i = %s\tnum = %s\n", i.toStrDec().c_str(), num2.toStrDec().c_str());
                    printf("i = %s, sec = %s\n", i.toStrDec().c_str(), (i - T_NUM(2)).toStrDec().c_str());
                }
            }
        }*/
        /*if (i % T_NUM(3) == T_NUM(0)) {
            T_NUM num2 = num + T_NUM(4);
            if (isPrime(num2)) {
                //printf("IS PRIME: %s %s\n", i.toStrDec().c_str(), num2.toStrDec().c_str());
            } else {
                printf("PRIME ERROR mod 3 = 0 + 4\n");
            }
        }
        if (i % T_NUM(5) == T_NUM(0)) {
            T_NUM num2 = num + T_NUM(4);
            if (isPrime(num2)) {
                //printf("IS PRIME: %s %s\n", i.toStrDec().c_str(), num2.toStrDec().c_str());
            } else {
                printf("PRIME ERROR mod 5 = 0 + 4\n");
            }
        }
        if (i % T_NUM(7) == T_NUM(0)) {
            T_NUM num2 = num + T_NUM(4);
            if (isPrime(num2)) {
                //printf("IS PRIME: %s %s\n", i.toStrDec().c_str(), num2.toStrDec().c_str());
            } else {
                printf("PRIME ERROR mod 7 = 0 + 4\n");
            }
        }
        if (i % T_NUM(2) == T_NUM(1)) {
            T_NUM num2 = num + T_NUM(2);
            if (isPrime(num2)) {
                //printf("IS PRIME: %s %s\n", i.toStrDec().c_str(), num2.toStrDec().c_str());
            } else {
                printf("PRIME ERROR mod 2 = 1 + 2\n");
            }
        }*/
        /*if (std::find(notPrimes.begin(), notPrimes.end(), (num).toStrDec()) != notPrimes.end() || charToNUM(num.toStrDec()[num.toStrDec().length() - 1]) == charToNUM('5')) {
            wrongPrimesDetected += T_NUM(1);
            _couldBePrime = false;
        } else {
            correctPrimesDetected += T_NUM(1);
            allPrimes.push_back(num);
        }

        if (!_isPrime) {
            printf("PRIME ERROR\t: num = %s\ti = %s\tfirstNum = %s\tsecondNum = %s\tfour = %s\tnot = %s\n",
                   (num).toStrDec().c_str(),
                   i.toStrDec().c_str(),
                   firstNum.toStrDec().c_str(),
                   secondNum.toStrDec().c_str(),
                   four.toStrDec().c_str(),
                   (four + firstNum + secondNum).toStrDec().c_str());
        } else {
            printf("IS PRIME\t: num = %s\ti = %s\tfirstNum = %s\tsecondNum = %s\tfour = %s\tnot = %s\n",
                   (num).toStrDec().c_str(),
                   i.toStrDec().c_str(),
                   firstNum.toStrDec().c_str(),
                   secondNum.toStrDec().c_str(),
                   four.toStrDec().c_str(),
                   (four + firstNum + secondNum).toStrDec().c_str());
        }*/

        /*if ((_isPrime && !_couldBePrime) || (!_isPrime && _couldBePrime)) {
            printf("PRIME ERROR\t: num = %s\ti = %s\tfirstNum = %s\tsecondNum = %s\tfour = %s\tnot = %s\n",
                   (num).toStrDec().c_str(),
                   i.toStrDec().c_str(),
                   firstNum.toStrDec().c_str(),
                   secondNum.toStrDec().c_str(),
                   four.toStrDec().c_str(),
                   (four + firstNum + secondNum).toStrDec().c_str());
        } else {
            printf("IS PRIME\t: num = %s\ti = %s\tfirstNum = %s\tsecondNum = %s\tfour = %s\tnot = %s\n",
                   (num).toStrDec().c_str(),
                   i.toStrDec().c_str(),
                   firstNum.toStrDec().c_str(),
                   secondNum.toStrDec().c_str(),
                   four.toStrDec().c_str(),
                   (four + firstNum + secondNum).toStrDec().c_str());
        }*/

      /*  if (i % T_NUM(1000) == T_NUM(0)) {
            std::cout << i.toStrDec() << std::endl;
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