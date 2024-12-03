#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <vector>

bool are_levels_safe(std::vector<int> levels)
{
    bool is_safe = true;
    bool increasing = false, decreasing = false;
    for (int i = 1; i < levels.size(); i++) {
        int previous_level = levels[i - 1];
        int current_level = levels[i];
        increasing = current_level < previous_level || increasing;
        decreasing = current_level > previous_level || decreasing;
        int difference = std::abs(current_level - previous_level);
        if (difference == 0 || difference > 3) {
            is_safe = false;
            break;
        }
    }
    if (increasing && decreasing) {
        is_safe = false;
    }
    return is_safe;
}

// First argument after file name is input file's path.
int main(int argc, char** args)
{
    if (argc < 2) {
        std::cout << "Missing input file's input\n";
        return 1;
    }
    int safe_levels_amount = 0;
    std::fstream input_file(args[1], std::ios_base::in);
    std::string levels_buffer;

    while (std::getline(input_file, levels_buffer)) {
        std::stringstream levels_buffer_stream(levels_buffer);
        int previous_level, level_buffer;
        std::vector<int> levels;
        while (levels_buffer_stream >> level_buffer) levels.push_back(level_buffer);
        if (are_levels_safe(levels)) safe_levels_amount++;
        else {
            for (int i = 0; i < levels.size(); i++) {
                std::vector<int> copy(levels);
                copy.erase(copy.begin() + i);
                if (are_levels_safe(copy)) {
                    safe_levels_amount++;
                    break;
                }
            }
        }
    }
    input_file.close();
    std::cout << "Safe levels amount: " << safe_levels_amount << '\n';
    return 0;
}
