#include <cctype>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool boundary_check(int line, int column, int line_size, int column_size)
{
    return line < line_size && line > -1 && column > -1 && column < column_size;
}

int search_direction(std::vector<std::vector<char>> &xmas_matrix, int line, int column, int line_increment, int column_increment)
{
    line += line_increment;
    column += column_increment;
    if (!boundary_check(line, column, xmas_matrix.size(), xmas_matrix[0].size())) {
        return 0;
    }
    if (xmas_matrix[line][column] != 'M') {
        return 0;
    }
    line += line_increment;
    column += column_increment;
    if (!boundary_check(line, column, xmas_matrix.size(), xmas_matrix[0].size())) {
        return 0;
    }
    if (xmas_matrix[line][column] != 'A') {
        return 0;
    }
    line += line_increment;
    column += column_increment;
    if (!boundary_check(line, column, xmas_matrix.size(), xmas_matrix[0].size())) {
        return 0;
    }
    if (xmas_matrix[line][column] != 'S') {
        return 0;
    }
    return 1;
}

// First argument after file name is input file's path.
int main (int argc, char** args) {
    if (argc < 2) {
        std::cout << "Missing input file's input\n";
        return 1;
    }
    std::fstream input_file(args[1], std::ios_base::in);
    std::vector<std::vector<char>> xmas_matrix;
    std::string line;
    while (std::getline(input_file, line)) {
        std::vector<char> xmas_line;
        for (char c : line) {
            xmas_line.push_back(c);
        }
        xmas_matrix.push_back(xmas_line);
    }
    int xmas_found_amount = 0;
    for (int i = 0; i < xmas_matrix.size(); i++) {
        for (int j = 0; j < xmas_matrix[0].size(); j++) {
            if (xmas_matrix[i][j] != 'X') continue;
            xmas_found_amount += search_direction(xmas_matrix, i, j, 1, 0);
            xmas_found_amount += search_direction(xmas_matrix, i, j, -1, 0);
            xmas_found_amount += search_direction(xmas_matrix, i, j, 0, 1);
            xmas_found_amount += search_direction(xmas_matrix, i, j, 0, -1);
            xmas_found_amount += search_direction(xmas_matrix, i, j, 1, 1);
            xmas_found_amount += search_direction(xmas_matrix, i, j, 1, -1);
            xmas_found_amount += search_direction(xmas_matrix, i, j, -1, 1);
            xmas_found_amount += search_direction(xmas_matrix, i, j, -1, -1);
        }
    }
    std::cout << "XMASs Found: " << xmas_found_amount << std::endl;
    return 0;
}
