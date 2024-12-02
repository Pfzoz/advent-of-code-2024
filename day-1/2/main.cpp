#include <array>
#include <fstream>
#include <iostream>
#include <vector>

std::array<std::vector<int>, 2> read_input(std::string file_path)
{
    std::array<std::vector<int>, 2> columns;
    std::fstream input_file(file_path, std::ios_base::in);
    int buffer, counter = 0;
    while (input_file >> buffer) {
        columns[counter++ % 2].push_back(buffer);
    }
    input_file.close();
    return columns;
}

// First argument after file name is input file's path.
int main(int argc, char** args) {
    if (argc < 2) {
        std::cout << "Missing input file's input\n";
        return 1;
    }
    std::array<std::vector<int>, 2> columns = read_input(args[1]);
    int column_size = columns[1].size();
    int similarity_score = 0;
    for (int i = 0; i < column_size; i++) {
        int left_number = columns[0][i];
        int occurence = 0;
        for (int j = 0; j < column_size; j++) {
            int right_number = columns[1][j];
            if (right_number == left_number) occurence++;
        }
        similarity_score += occurence * left_number;
    }
    std::cout << "Similarity score: " << similarity_score << '\n';
    return 0;
}
