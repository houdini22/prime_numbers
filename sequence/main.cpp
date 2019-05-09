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

typedef long long T_NUM;
typedef std::vector<T_NUM> T_NUM_VEC;
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

void debugPrime(T_NUM num) {
    for (T_NUM i = 3; i * i <= num; i += 2) {
        if (num % i == 0) {
            std::cout << i << std::endl;
        }
    }

    std::cout << std::endl;
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

int main() {
    T_NUM firstNum = 5;
    T_NUM secondNum = 4;
    T_NUM two = 0;
    T_NUM_VEC numbers;

    fileData.open("./data/numbers.txt");

    numbers.push_back(3);
    numbers.push_back(5);
    numbers.push_back(7);

    T_NUM current = 0;
    double lastPercent = 0;
    T_NUM all = 100000000;

    auto timeStart = std::chrono::system_clock::now();

    for (T_NUM i = 1; i < all; i += 1) {
        T_NUM num = firstNum + secondNum + 2 * two;

        two += 2;

        T_NUM readyNum = num + 2;
        T_STR readyNumStr = std::to_string(readyNum);

        if (charToInt(readyNumStr[readyNumStr.length() - 1]) != charToInt('5')) {
            bool isPrime = true;
            for (int j = 0; j < numbers.size() / 4 + 1; j++) {
                if (readyNum % numbers[j] == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                numbers.push_back(readyNum);
            }
        }

        firstNum += 1;
        secondNum += 1;

        current += 1;

        double currentPercent = floor((double(current) / double(all)) * 100);
        if (currentPercent != lastPercent) {
            lastPercent = currentPercent;
            printf("%i\n", (int) lastPercent);
        }
    }

    auto timeEnd = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(timeEnd - timeStart).count();

    printf("comp end\n");
    printf("elapsed: %i\n", (int) elapsed);

    for (size_t i = 0; i < numbers.size(); i += 1) {
        fileData << numbers[i] << "\n";
    }
    fileData.close();

    T_NUM _isPrime = 0;

    for (size_t i = 0; i < numbers.size(); i += 1) {
        bool _isPrime = isPrime(numbers[i]);
        if (!_isPrime) {
            _isPrime++;
        }
    }

    printf("%i\n", (int) _isPrime);



    /*printf("prime\n");
    for (size_t i = 0; i < numbers.size(); i += 1) {
        if (isPrime(numbers[i])) {
            printf("%i %i %s\n", (int) i, (int) numbers[i], (isPrime(numbers[i]) ? "true" : "false"));
        }
    }*/

    return 0;
}