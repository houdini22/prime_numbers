
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

int charToInt(char c);

T_STR getNumbersFromTri(double d_num, T_STR s_num, T_NUM d_step, unsigned int ommit, unsigned long length);

T_NUM sumVector(T_NUM_VEC vec);

T_NUM_VEC createVectorFromTri(T_STR sinus, T_STR cosinus, T_STR tangens, T_STR itangens);

bool isPrime(T_NUM num);


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
            result[(unsigned long) row][(unsigned long) col].resize(3);

            result[(unsigned long) row][(unsigned long) col][0] = 2;
            result[(unsigned long) row][(unsigned long) col][1] = 2;
            result[(unsigned long) row][(unsigned long) col][2] = 2;
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

std::ofstream fileData;
std::ofstream fileSymmetry;

void writeDataToFile(T_STRUCT arr) {
    T_NUM sum = 0;

    fileData << "___angle___\n";
    fileData << std::to_string(arr.angle) << '\n';
    fileData << "___is_prime___\n";
    fileData << (isPrime(arr.angle) ? "true\n" : "false\n");

    for (size_t i = 0; i < arr.splitted.size(); i++) {
        for (size_t j = 0; j < arr.splitted[i].size(); j++) {
            for (size_t k = 0; k < arr.splitted[i][j].size(); k++) {
                sum += arr.splitted[i][j][k];
            }
        }
    }

    T_NUM sum1 = 0;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < arr.splitted[i].size(); j++) {
            for (size_t k = 0; k < arr.splitted[i][j].size(); k++) {
                sum1 += arr.splitted[i][j][k];
            }
        }
    }

    T_NUM sum2 = 0;
    for (size_t i = 2; i < arr.splitted.size(); i++) {
        for (size_t j = 0; j < arr.splitted[i].size(); j++) {
            for (size_t k = 0; k < arr.splitted[i][j].size(); k++) {
                sum2 += arr.splitted[i][j][k];
            }
        }
    }

    fileData << "___table___\n";

    for (size_t row = 0; row < arr.splitted.size(); row++) {
        for (size_t col = 0; col < arr.splitted[row].size(); col++) {
            for (size_t number = 0; number < arr.splitted[row][col].size(); number++) {
                fileData << arr.splitted[row][col][number];
            }
            for (size_t k = arr.splitted[row][col].size(); k < 10; k++) {
                fileData << " ";
            }
        }
        fileData << "\n";
    }

    fileData << "___table_sum___\n";
    fileData << (int) sum << "\n";
    fileData << "___sum1___\n";
    fileData << (int) sum1 << "\n";
    fileData << "___sum2___\n";
    fileData << (int) sum2 << "\n";
    fileData << "___is_sum_prime___\n";
    fileData << (isPrime(sum) ? "true" : "false") << "\n";

    fileData << "\n--------------------\n\n";
}

void writeSymmetryToFile(T_STRUCT arr) {
    fileSymmetry << createCell(2, std::to_string(arr.angle));
    fileSymmetry << createCell(1, "  | ");
    fileSymmetry << createCell(2, std::to_string(((int) floor(abs(arr.angle) / 90.0) % 4) + 1));
    fileSymmetry << createCell(1, "  | ");
    fileSymmetry << createCell(2, std::to_string((int) floor(arr.angle / 90)));
    fileSymmetry << createCell(1, "  | ");
    fileSymmetry << createCell(140, arr.comparison) << "\n";
}

const T_NUM ___BEGIN___ = 250;

int main() {
    // initialize
    std::cout.precision(20);

    fileData.open("./data.txt");
    fileSymmetry.open("./symmetry.txt");

    // start
    T_NUM_VEC allFound;
    T_STRUCTURE_VECTOR arr; // main data container

    // from angle -___BEGIN___ (degree) -> + ___BEGIN___ (degree)
    for (T_NUM step = -___BEGIN___; step <= ___BEGIN___; step += 1) {
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

        for (size_t k = 0; k < s1.splitted.size(); k++) {
            for (size_t l = 0; l < s1.splitted[k].size(); l++) {
                for (size_t m = 0; m < s1.splitted[k][l].size(); m++) {
                    s1.splitted_sum += s1.splitted[k][l][m];
                }
            }
        }


        for (T_NUM j = -7; j <= 7; j++) {
            if (isPrime(s1.sum + j)) {
                s1.vec.push_back(std::make_pair(j, s1.sum + j));
            }
        }

        arr.push_back(s1);
    }

    // sort all primary numbers
    std::sort(arr.begin(), arr.end(), T_SORT_STRUCT());

    // debug
    for (T_NUM i = 0; i < arr.size(); i++) {
        writeDataToFile(arr[i]);
    }

    // SYMMETRY ALGORITHM
    for (T_NUM base = -___BEGIN___, start = 0; base <= ___BEGIN___; base += 1, start++) {
        if (base == -___BEGIN___) { // not smallest angle
            continue;
        }

        T_NUM range = 0;
        bool lastComparison = false;
        T_STR comparisons;
        T_NUM comparisonsTRUE = 0;
        T_NUM comparisonsFALSE = 0;

        while (true) {
            if (start - range == 0 || start + range == arr.size()) {
                break;
            }

            // select ranges
            T_STRUCT currentUpper = arr[start + range];
            T_STRUCT currentBelow = arr[start - range];

            // compare symmetry
            T_STR compareUpper;
            T_STR compareBelow;

            // sum splits
            T_NUM sumUpper = currentUpper.splitted_sum;
            T_NUM sumBelow = currentBelow.splitted_sum;

            // create comparisons
            for (T_NUM j = -2; j <= 2; j++) {
                for (T_NUM k = -1; k <= 1; k += 2) {
                    if (j + k == 0) continue;

                    if (isPrime(sumUpper + j + k)) {
                        compareUpper.append(std::to_string(j)).append(std::to_string(k));
                    }
                }
            }

            for (T_NUM j = -2; j <= 2; j++) {
                for (T_NUM k = -1; k <= 1; k += 2) {
                    if (j + k == 0) continue;

                    if (isPrime(sumBelow + j + k)) {
                        compareBelow.append(std::to_string(j)).append(std::to_string(k));
                    }
                }
            }

            // if symmetry broken
            if (strcmp(compareBelow.c_str(), compareUpper.c_str()) != 0) {
                // append last
                if (comparisonsTRUE > 0) {
                    comparisons.append(std::to_string(comparisonsTRUE)).append("T ");
                } else if (comparisonsFALSE > 0) {
                    comparisons.append(std::to_string(comparisonsFALSE)).append("F ");
                }
                break;
            }

            bool comp = isPrime(sumUpper);                              // is prime sum of split
            if (range == 0) {                                           // first loop (i.e. 90 + 0)
                if (comp) {
                    comparisonsTRUE++;
                } else {
                    comparisonsFALSE++;
                }
            } else {                                                    // second+ loop (i.e. 90 + 1, 90 - 1)
                if (lastComparison == comp) {                           // keep adding
                    if (comp) {
                        comparisonsTRUE++;
                    } else {
                        comparisonsFALSE++;
                    }
                } else if (!comp) {                                     // difference
                    comparisons.append(std::to_string(comparisonsTRUE)).append("T ");
                    comparisonsFALSE = 1;
                    comparisonsTRUE = 0;
                } else {                                                // difference
                    comparisons.append(std::to_string(comparisonsFALSE)).append("F ");
                    comparisonsFALSE = 0;
                    comparisonsTRUE = 1;
                }
            }
            lastComparison = comp;

            range++;
        }

        arr[start].comparison = comparisons;
        writeSymmetryToFile(arr[start]);
    }

    fileData.close();
    fileSymmetry.close();

    return 0;
}