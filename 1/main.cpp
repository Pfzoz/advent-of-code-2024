#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

std::array<std::vector<int>, 2> read_input(std::string file_path)
{
    std::array<std::vector<int>, 2> columns;
    std::fstream input_file(file_path, std::ios_base::in);
    int buffer, counter = 0;
    while (input_file >> buffer) {
        columns[counter++ % 2].push_back(buffer);
    }
    return columns;
}

int main()
{
    std::string file_path = "input.txt"; // Insert the input file_path here
    std::array<std::vector<int>, 2> columns = read_input(file_path);
    std::vector<int> distances;
    std::sort(columns[0].begin(), columns[0].end());
    std::sort(columns[1].begin(), columns[1].end());
    int distances_sum = 0;
    for (int i = 0; i < columns[0].size(); i++) {
        distances_sum += std::abs(columns[0][i] - columns[1][i]);
    }

    std::cout << "Summed distance: " << distances_sum << '\n';
    return 0;
}
