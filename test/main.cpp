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

/*
 * DATA TYPES
 */
typedef long long T_NUM;
typedef std::vector<T_NUM> T_NUM_VEC;
typedef std::string T_STR;
typedef std::vector<T_STR> T_STR_VEC;
typedef std::pair<T_NUM, T_NUM> T_PAIR;
typedef std::vector<T_PAIR> T_PAIR_VEC;
typedef std::vector<std::vector<std::vector<T_NUM>>> T_3D_NUM_VEC;
struct T_STRUCT {
    T_NUM angle;
    T_NUM angleSize;
    T_NUM sum;
    T_PAIR_VEC vec;
    T_3D_NUM_VEC splitted;
    T_NUM splitted_sum = 0;
    T_STR comparison;
};
typedef std::vector<T_STRUCT> T_STRUCTURE_VECTOR;

struct T_SORT_STRUCT {
    inline bool operator()(const T_STRUCT &s1, const T_STRUCT &s2) {
        return (s1.angle < s2.angle);
    }
};

struct T_HISTOGRAM_SORT_STRUCT {
    inline bool operator()(const T_PAIR &s1, const T_PAIR &s2) {
        return (s1.first < s2.first);
    }
};

/*
 * CONFIG
 */
T_STR output = "std::cout";

/*
 * FUNCTIONS
 */
T_NUM sumVector(T_NUM_VEC vec);

void debugVector(T_STR title, T_NUM_VEC vec, bool sum);

void debugPairVector(T_PAIR_VEC vec);

void debug3dVector(T_3D_NUM_VEC vec);

int charToInt(char c);

T_STR getNumbersFromTri(double d_num, T_STR s_num, T_NUM d_step, unsigned int ommit, unsigned long length);

T_NUM sumVector(T_NUM_VEC vec);

T_NUM_VEC createVectorFromTri(T_STR sinus, T_STR cosinus, T_STR tangens, T_STR itangens);

bool isPrime(T_NUM num);

T_3D_NUM_VEC splitVector(T_NUM_VEC vec, size_t length);

T_NUM_VEC createPrimaryNumberFromSplits(T_3D_NUM_VEC vec, T_NUM multiplier);

T_STR_VEC splitString(T_STR str);

/*
 * TRIGONOMETRY
 */
const double PI = std::acos(-1);

double degreeToRadian(double degree) {
    return degree * PI / 180.0;
}

double radianToDegree(double radians) {
    return radians * 180 / PI;
}

double _sin(double x) {
    return std::sin(degreeToRadian(x));
}

double _cos(double x) {
    return std::cos(degreeToRadian(x));
}

double _tan(double x) {
    return std::tan(degreeToRadian(x));
}

double _itan(double x) {
    return radianToDegree(std::atan(x));
}

/*
 * HELPERS
 */

/**
 * it prints content of the 1D T_NUM vector
 * @param vec
 */
void debugVector(T_STR title, T_NUM_VEC vec, bool sum = false) {
    std::cout << "\t___" << title << "___";
    if (sum) {
        std::cout << ": " << sumVector(vec);
    }
    std::cout << std::endl;

    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl << std::endl;
}

/**
 * it prints content of the T_PAIR vector
 * @param vec
 */
void debugPairVector(T_PAIR_VEC vec) {
    std::cout << "\t___map___" << std::endl;
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i].first << ":" << vec[i].second;
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl << std::endl;
}

/**
 * it prints content of the 3D T_NUM vector
 * @param vec
 */
void debug3dVector(T_3D_NUM_VEC vec) {
    std::cout << "\t___splitted___" << std::endl;

    for (size_t i = 0; i < vec.size(); i++) {
        for (size_t j = 0; j < vec[i].size(); j++) {
            for (size_t k = 0; k < vec[i][j].size(); k++) {
                std::cout << vec[i][j][k];
            }
            std::cout << '\t' << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

/**
 * It converts string ASCII char [0-9] to integer in C++
 * @param c
 * @return
 */
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

/**
 * it converts TRIgonometry numbers to a string (2 number angle -> 2 sized string, 3 number angle -> 3 sized string)
 * @param d_num
 * @param s_num
 * @param d_step
 * @param ommit
 * @param length
 * @return
 */
T_STR getNumbersFromTri(double d_num, T_STR s_num, T_NUM d_step, unsigned int ommit, unsigned long length) {
    T_STR result = "";
    if (ommit == 0) {
        for (size_t i = s_num[0] == '-' ? ommit + 1 : ommit; i < s_num.length(); i++) {
            if (s_num[i] != '.') {
                result += s_num[i];
            }
        }
        result = result.substr(0, length);
    } else if (d_num < 0) {
        ommit += 1; // comma
        result = s_num.substr(ommit, length);
    } else if (d_num > 0) {
        result = s_num.substr(ommit, length);
    }
    return result;
}

/**
 * Get sum from T_NUM vector
 * @param vec
 * @return
 */
T_NUM sumVector(T_NUM_VEC vec) {
    T_NUM result = 0;
    for (size_t i = 0; i < vec.size(); i++) {
        result += vec.at(i);
    }
    return result;
}

/**
 * it creates T_NUM vector from TRInity numbers
 * @param sinus
 * @param cosinus
 * @param tangens
 * @param s4
 * @return
 */
T_NUM_VEC createVectorFromTri(T_STR sinus, T_STR cosinus, T_STR tangens, T_STR itangens) {
    T_NUM_VEC result = T_NUM_VEC();
    for (int i = 0; i < sinus.length(); i++) {
        result.push_back(charToInt(sinus.at(i)));
    }
    for (int i = 0; i < cosinus.length(); i++) {
        result.push_back(charToInt(cosinus.at(i)));
    }
    for (int i = 0; i < tangens.length(); i++) {
        result.push_back(charToInt(tangens.at(i)));
    }
    for (int i = 0; i < itangens.length(); i++) {
        result.push_back(charToInt(itangens.at(i)));
    }
    return result;
}

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

/**
 * It converts T_NUM_VEC to splited vector (extended examples)
 * @param vec
 * @param length
 * @return
 */
T_3D_NUM_VEC splitVector(T_NUM_VEC vec, T_NUM length) {
    T_3D_NUM_VEC result;
    result.resize(vec.size() / length);

    T_NUM row = 0;
    T_NUM col = 0;

    for (T_NUM i = 0; i < vec.size(); i++) {
        result[row].resize(length);

        if (vec[i] == 7 || vec[i] == 5 || vec[i] == 3 || vec[i] == 2 || vec[i] == 1 || vec[i] == 0) {
            result[(unsigned long) row][(unsigned long) col].resize(1);

            result[(unsigned long) row][(unsigned long) col][0] = vec[i];
        } else if (vec[i] == 8) {
            result[(unsigned long) row][(unsigned long) col].resize(4);

            result[(unsigned long) row][(unsigned long) col][0] = 2;
            result[(unsigned long) row][(unsigned long) col][1] = 2;
            result[(unsigned long) row][(unsigned long) col][2] = 2;
            result[(unsigned long) row][(unsigned long) col][3] = 2;
        } else if (vec[i] == 6) {
            result[(unsigned long) row][(unsigned long) col].resize(2);

            result[(unsigned long) row][(unsigned long) col][0] = 3;
            result[(unsigned long) row][(unsigned long) col][1] = 3;
        } else if (vec[i] == 4) {
            result[(unsigned long) row][(unsigned long) col].resize(2);

            result[(unsigned long) row][(unsigned long) col][0] = 2;
            result[(unsigned long) row][(unsigned long) col][1] = 2;
        } else if (vec[i] == 9) {
            result[(unsigned long) row][(unsigned long) col].resize(3);

            result[(unsigned long) row][(unsigned long) col][0] = 3;
            result[(unsigned long) row][(unsigned long) col][1] = 3;
            result[(unsigned long) row][(unsigned long) col][2] = 3;
        }

        if (((i + 1) % length) == 0) {
            row++;
            col = 0;
        } else {
            col++;
        }
    }

    return result;
}

T_NUM_VEC createPrimaryNumberFromSplits(T_3D_NUM_VEC vec, T_NUM multiplier = 1) {
    T_NUM_VEC result;

    result.resize(vec.size());

    for (T_NUM row = 0; row < vec.size(); row++) {
        for (T_NUM number = 0; number < vec[row][0].size(); number++) {
            T_NUM _result = 0;
            for (size_t i = 1; i < vec[row].size(); i++) {
                _result += (T_NUM) pow(vec[row][0][number], vec[row][i].size() * multiplier);
            }

            result[row] += _result;
        }
    }

    return result;
}

T_STR createCell(T_NUM tabLength, T_STR content) {
    T_NUM subtract = (tabLength * 4) - (T_NUM) content.length();
    auto numTabs = (T_NUM) ceil((int) subtract / (int) 4);

    if (((int) subtract) % 4 != 0) {
        numTabs++;
    }

    for (T_NUM i = 0; i < numTabs; i++) {
        content.append("\t");
    }

    return content;
}

std::ofstream fileTest;
std::ofstream fileSums;
std::ofstream fileHistogram;
std::ofstream fileSymmetry;
std::ofstream filePython;

void writeSumsToFile(T_STRUCT arr) {
    fileSums << std::to_string(arr.angle) << ":\t";
    if (arr.angleSize == 2 || arr.angleSize == 1) {
        fileSums << "\t";
    }

    T_NUM sum = 0;
    for (size_t i = 0; i < arr.splitted.size(); i++) {
        for (size_t j = 0; j < arr.splitted[i].size(); j++) {
            for (size_t k = 0; k < arr.splitted[i][j].size(); k++) {
                sum += arr.splitted[i][j][k];
            }
        }
    }

    fileSums << std::to_string(sum) << "\t\t";
    fileSums << (isPrime(sum) ? "true" : "false") << "\t\t";

    for (T_NUM j = -2; j <= 2; j++) {
        T_STR cell;
        for (T_NUM k = -1; k <= 1; k += 2) {
            if (j + k == 0) continue;

            if (isPrime(sum + j + k)) {
                cell.append(createCell(1, "|"));
                cell.append(createCell(1, std::to_string(sum + j + k)));
                cell.append(createCell(1, ":"));
                cell.append(createCell(1, std::to_string(j)));
                cell.append(createCell(1, std::to_string(k)));
                cell.append(createCell(2, "|"));

                fileSums << cell;
            }
        }
    }

    fileSums << "\n";
}

void writeDataToFile(T_STRUCT arr) {
    fileTest << "___angle___\n";
    fileTest << std::to_string(arr.angle) << '\n';
    fileTest << "___splitted___\n";

    T_NUM sum1 = 0;
    T_NUM sum2 = 0;
    T_NUM sum3 = 0;
    T_NUM sum4 = 0;

    T_NUM num1 = 0;
    T_NUM num2 = 0;
    T_NUM num3 = 0;
    T_NUM num4 = 0;

    T_NUM after1 = 0;
    T_NUM after2 = 0;
    T_NUM after3 = 0;
    T_NUM after4 = 0;

    for (size_t row = 0; row < arr.splitted.size(); row++) {
        for (size_t col = 0; col < arr.splitted[row].size(); col++) {
            for (size_t number = 0; number < arr.splitted[row][col].size(); number++) {
                fileTest << arr.splitted[row][col][number];
            }
            for (size_t k = arr.splitted[row][col].size(); k < 10; k++) {
                fileTest << " ";
            }
        }
        fileTest << "\n";
    }

    for (size_t row = 0; row < arr.splitted.size(); row++) {
        for (size_t col = 0; col < arr.splitted[row].size(); col++) {
            for (size_t number = 0; number < arr.splitted[row][col].size(); number++) {
                sum1 += arr.splitted[row][col][number];
                sum2 += (T_NUM) pow(arr.splitted[row][col][number], arr.splitted[row][col].size());
                sum3 += (T_NUM) pow(arr.splitted[row][col][number], number + 1);
                sum4 += (T_NUM) pow(arr.splitted[row][col][number], (number + 1) * 2);
            }
        }
    }

    fileTest << "___sum1___\n";
    fileTest << createCell(4, std::to_string(sum1)) << " " << createCell(4, (isPrime(sum1) ? "true" : "false")) << '\n';

    for (T_NUM i = 0; i < 100; i++) {
        if (isPrime(sum1 + i)) {
            num1 = i;
            after1 = sum1 + i;
            break;
        }
    }
    fileTest << createCell(4, "ingredient") << createCell(3, std::to_string(num1)) << " after: " << createCell(3, std::to_string(after1)) << '\n';

    fileTest << "___sum2___\n";
    fileTest << createCell(4, std::to_string(sum2)) << " " << createCell(4, (isPrime(sum2) ? "true" : "false")) << '\n';

    for (T_NUM i = 0; i < 100; i++) {
        if (isPrime(sum2 + i)) {
            num2 = i;
            after2 = sum2 + i;
            break;
        }
    }
    fileTest << createCell(4, "ingredient") << createCell(3, std::to_string(num2)) << " after: " << createCell(3, std::to_string(after2)) << '\n';

    fileTest << "___sum3___\n";
    fileTest << createCell(4, std::to_string(sum3)) << " " << createCell(4, (isPrime(sum3) ? "true" : "false")) << '\n';

    for (T_NUM i = 0; i < 100; i++) {
        if (isPrime(sum3 + i)) {
            num3 = i;
            after3 = sum3 + i;
            break;
        }
    }
    fileTest << createCell(4, "ingredient") << createCell(3, std::to_string(num3)) << " after: " << createCell(3, std::to_string(after3)) << '\n';

    fileTest << "___sum4___\n";
    fileTest << createCell(4, std::to_string(sum4)) << " " << createCell(4, (isPrime(sum4) ? "true" : "false")) << '\n';

    for (T_NUM i = 0; i < 100; i++) {
        if (isPrime(sum4 + i)) {
            num4 = i;
            after4 = sum4 + i;
            break;
        }
    }
    fileTest << createCell(4, "ingredient") << createCell(3, std::to_string(num4)) << " after: " << createCell(3, std::to_string(after4)) << '\n';

    fileTest << "\n--------------------\n\n";
}

const T_NUM ___BEGIN___ = 18000;

int main() {
    // initialize
    std::cout.precision(20);

    // open files
    fileTest.open("./test.txt");

    // start
    T_NUM_VEC allFound;
    T_STRUCTURE_VECTOR arr; // main data container

    // from angle -___BEGIN___ (degree) -> + ___BEGIN___ (degree)
    for (T_NUM step = 0; step < 1000; step += 1) {
        T_NUM_VEC vec1 = createVectorFromTri(
                getNumbersFromTri(_sin(step), std::to_string(_sin(step)), step, 2, std::to_string(step).length()),
                getNumbersFromTri(_cos(step), std::to_string(_cos(step)), step, 2, std::to_string(step).length()),
                getNumbersFromTri(_tan(step), std::to_string(_tan(step)), step, 0, std::to_string(step).length()),
                getNumbersFromTri(_itan(step), std::to_string(_itan(step)), step, 0, std::to_string(step).length()));

        // create data
        T_STRUCT s1;
        s1.angle = step;
        s1.angleSize = (T_NUM) std::to_string(step).length();
        s1.sum = sumVector(vec1);
        s1.splitted = splitVector(vec1, s1.angleSize);

        arr.push_back(s1);
    }

    // sort all primary numbers
    std::sort(arr.begin(), arr.end(), T_SORT_STRUCT());

    // debug
    for (T_NUM i = 0; i < arr.size(); i++) {
        writeDataToFile(arr[i]);
    }

    fileTest.close();
    fileSums.close();

    return 0;
}