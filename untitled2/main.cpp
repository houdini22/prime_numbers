#include <iostream>
#include <math.h>
#include <string>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <map>
#include <fstream>
#include "omp.h"

/*
 * DATA TYPES
 */
typedef long long T_NUM;
typedef std::vector<T_NUM> T_NUM_VEC;
typedef std::string T_STR;
typedef std::pair<T_NUM, T_NUM> T_PAIR;
typedef std::vector<T_PAIR> T_PAIR_VEC;
typedef std::vector<std::vector<std::vector<T_NUM>>> T_3D_NUM_VEC;
struct T_STRUCT {
    T_NUM angle;
    T_NUM angleSize;
    T_NUM sum;
    T_STR sum_str;
    T_NUM_VEC ingredients;
    T_PAIR_VEC vec;
    T_3D_NUM_VEC splitted;
    T_NUM splitted_sum;
    T_NUM_VEC extended_vector_1;
    T_NUM_VEC extended_vector_2;
    T_NUM_VEC extended_vector_3;
    T_NUM_VEC extended_vector_4;
};
typedef std::vector<T_STRUCT> T_STRUCTURE_VECTOR;

struct T_SORT_STRUCT {
    inline bool operator()(const T_STRUCT &s1, const T_STRUCT &s2) {
        return (s1.angle < s2.angle);
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

T_NUM_VEC createVectorFromTri(T_STR s1, T_STR s2, T_STR s3, T_STR s4);

bool isPrime(T_NUM num);

T_3D_NUM_VEC splitVector(T_NUM_VEC vec, size_t length);

T_NUM_VEC createPrimaryNumberFromSplits(T_3D_NUM_VEC vec, T_NUM multiplier);

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
 * @param s1
 * @param s2
 * @param s3
 * @param s4
 * @return
 */
T_NUM_VEC createVectorFromTri(T_STR s1, T_STR s2, T_STR s3, T_STR s4) {
    T_NUM_VEC result = T_NUM_VEC();
    for (int i = 0; i < s1.length(); i++) {
        result.push_back(charToInt(s1.at(i)));
    }
    for (int i = 0; i < s2.length(); i++) {
        result.push_back(charToInt(s2.at(i)));
    }
    for (int i = 0; i < s3.length(); i++) {
        result.push_back(charToInt(s3.at(i)));
    }
    for (int i = 0; i < s4.length(); i++) {
        result.push_back(charToInt(s4.at(i)));
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

T_STR getFilename(T_NUM angle) {
    T_STR result = "./";
    result.append(std::to_string((int) angle)).append(".txt");
    return result;
}

void saveToFile(T_STRUCT arr) {
    std::ofstream file;
    file.open(getFilename(arr.angle));
    file << std::to_string(arr.angle);
    file.close();
}

int main() {
    T_NUM_VEC allFound;

    T_STRUCTURE_VECTOR arr; // main data container

    // from angle 1 (degree) -> 9999 (degree)
    for (T_NUM step = 1; step < 100; step += 1) {
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
        s1.sum_str = std::to_string(s1.sum);
        s1.ingredients = vec1;
        s1.splitted = splitVector(vec1, s1.angleSize);
        s1.extended_vector_1 = createPrimaryNumberFromSplits(s1.splitted);
        s1.extended_vector_2 = createPrimaryNumberFromSplits(s1.splitted, 2);
        s1.extended_vector_3 = createPrimaryNumberFromSplits(s1.splitted, 3);
        s1.extended_vector_4 = createPrimaryNumberFromSplits(s1.splitted, 4);
        s1.splitted_sum = sumVector(s1.extended_vector_1);

        arr.push_back(s1);
    }

    // sort all primary numbers
    std::sort(arr.begin(), arr.end(), T_SORT_STRUCT());

    T_NUM allPrimesSearch = ((T_NUM) arr.size()) * 4;
    T_NUM foundPrimesSearch = 0;

    T_NUM_VEC counter;
    for (T_NUM i = 0; i < arr.size(); i++) {
        counter.push_back(arr[i].angle);
    }

    // debug
    for (T_NUM i = 0; i < arr.size(); i++) {
        //printf("\t___number___: %i\t(%i / %i)\n", (int) arr[i].angle, (int) i + 1, (int) arr.size());

        /*debug3dVector(arr[i].splitted);
        debugVector("extended_vector_1", arr[i].extended_vector_1, true);
        debugVector("extended_vector_2", arr[i].extended_vector_2, true);
        debugVector("extended_vector_3", arr[i].extended_vector_3, true);
        debugVector("extended_vector_4", arr[i].extended_vector_4, true);
        debugPairVector(arr[i].vec);*/

        saveToFile(arr[i]);

        T_NUM sum1 = sumVector(arr[i].extended_vector_1);
        T_NUM sum2 = sumVector(arr[i].extended_vector_2);
        T_NUM sum3 = sumVector(arr[i].extended_vector_3);
        T_NUM sum4 = sumVector(arr[i].extended_vector_4);

        counter.erase(std::remove(counter.begin(), counter.end(), arr[i].angle), counter.end());
        std::cout << "\t\t" << counter.size() << " / " << arr.size() << std::endl;

        for (T_NUM j = -(49 * 49 * 49); j <= (49 * 49 * 49); j++) {
            if (isPrime(sum1 + j)) {
                allFound.push_back(sum1 + j);
                foundPrimesSearch++;
            }

            if (isPrime(sum2 + j)) {
                allFound.push_back(sum2 + j);
                foundPrimesSearch++;
            }

            if (isPrime(sum3 + j)) {
                allFound.push_back(sum3 + j);
                foundPrimesSearch++;
            }

            if (isPrime(sum4 + j)) {
                allFound.push_back(sum4 + j);
                foundPrimesSearch++;
            }
        }
    }

    std::cout << "ALL: " << allPrimesSearch << ", FOUND: " << foundPrimesSearch << std::endl;
    std::cout << foundPrimesSearch / allPrimesSearch << std::endl;

    std::sort(allFound.begin(), allFound.end());
    auto it = std::unique(allFound.begin(), allFound.end());
    allFound.resize(std::distance(allFound.begin(), it));

    std::cout << allFound.size() << std::endl;

    std::ofstream file;
    file.open("./dictionary.txt");
    for (T_NUM i = 0; i < allFound.size(); i++) {
        file << allFound[i] << '\n';
    }
    file.close();

    return 0;
}