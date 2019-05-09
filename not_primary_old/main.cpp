#include <iostream>
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

    T_NUM _i(T_NUM(0));
    T_NUM _max(T_NUM(100));

    T_NUM_VEC vec;
    while (_i < _max) {
        if (isPrime(_i)) {
            vec.push_back(_i);
        }
        _i++;
    }

    for (int __i = 0; __i < vec.size(); __i += 1) {
        printf("PRIME: %s\n", vec[__i].toStrDec().c_str());
    }

    T_NUM i(T_NUM(0));
    T_NUM max(T_NUM(200));

    T_NUM_VEC allPrimes;

    T_STR_VEC notPrimes;
    notPrimes.push_back(T_NUM(9).toStrDec());

    T_NUM correctPrimesDetected = T_NUM(0);
    T_NUM wrongPrimesDetected = T_NUM(0);

    T_NUM correctPrimesComputed = T_NUM(0);
    T_NUM wrongPrimesComputed = T_NUM(0);

    while (i < max) {
        T_NUM firstNum = i + 3;
        T_NUM secondNum = i + 4;
        T_NUM four = i * 4;
        T_NUM num = firstNum + secondNum + four;

        //printf("NUM:   %s\t\t", num.toStrDec().c_str());

        bool _isPrime = false;
        bool _couldBePrime = true;

        if (isPrime(num)) {
            correctPrimesComputed += T_NUM(1);
            _isPrime = true;
        } else {
            wrongPrimesComputed += T_NUM(1);
        }

        if (std::find(notPrimes.begin(), notPrimes.end(), (num).toStrDec()) != notPrimes.end() || charToNUM(num.toStrDec()[num.toStrDec().length() - 1]) == charToNUM('5')) {
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
        }

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

        notPrimes.push_back((four + firstNum + secondNum).toStrDec());

        i++;
    }
/*
#pragma omp critical
        {
        };
    };*/

    //printf("DETECTED: correct: %s\t wrong: %s\n", correctPrimesDetected.toStrDec().c_str(), wrongPrimesDetected.toStrDec().c_str());
    //printf("COMPUTED: correct: %s\t wrong: %s\n", correctPrimesComputed.toStrDec().c_str(), wrongPrimesComputed.toStrDec().c_str());

    return 0;
}