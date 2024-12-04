#include <cctype>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int check_for_x_mas(std::vector<std::vector<char>> &x_mas_matrix, int line, int column)
{
    if (line > (x_mas_matrix.size() - 3) || column > (x_mas_matrix[0].size() - 3)) {
        return 0;
    }
    if (x_mas_matrix[line + 1][column + 1] != 'A') return 0;
    if (x_mas_matrix[line][column] == x_mas_matrix[line+2][column+2]) return 0;
    int m = 0, s = 0;
    if (x_mas_matrix[line][column] == 'M') m++;
    if (x_mas_matrix[line][column] == 'S') s++;
    if (x_mas_matrix[line+2][column] == 'M') m++;
    if (x_mas_matrix[line+2][column] == 'S') s++;
    if (x_mas_matrix[line][column+2] == 'M') m++;
    if (x_mas_matrix[line][column+2] == 'S') s++;
    if (x_mas_matrix[line+2][column+2] == 'M') m++;
    if (x_mas_matrix[line+2][column+2] == 'S') s++;
    return m == 2 && s == 2 ? 1 : 0;
}

// First argument after file name is input file's path.
int main (int argc, char** args) {
    if (argc < 2) {
        std::cout << "Missing input file's input\n";
        return 1;
    }
    std::fstream input_file(args[1], std::ios_base::in);
    std::vector<std::vector<char>> x_mas_matrix;
    std::string line;
    while (std::getline(input_file, line)) {
        std::vector<char> x_mas_line;
        for (char c : line) {
            x_mas_line.push_back(c);
        }
        x_mas_matrix.push_back(x_mas_line);
    }
    int x_mas_found_amount = 0;
    for (int i = 0; i < x_mas_matrix.size(); i++) {
        for (int j = 0; j < x_mas_matrix[0].size(); j++) {
            if (x_mas_matrix[i][j] != 'M' && x_mas_matrix[i][j] != 'S') {
                continue;
            }
            x_mas_found_amount += check_for_x_mas(x_mas_matrix, i, j);
        }
    }
    std::cout << "X-MASs Found: " << x_mas_found_amount << std::endl;
    return 0;
}
