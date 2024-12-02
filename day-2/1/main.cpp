#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>

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
        int previous_level,
        level_buffer;
        bool increasing = false, decreasing = false;
        if (!(levels_buffer_stream >> previous_level)) {
            continue;
        }
        bool is_safe = true;
        while (levels_buffer_stream >> level_buffer) {
            increasing = level_buffer < previous_level || increasing;
            decreasing = level_buffer > previous_level || decreasing;
            int difference = std::abs(level_buffer - previous_level);
            if (difference == 0 || difference > 3) {
                is_safe = false;
                break;
            }
            previous_level = level_buffer;
        }
        if (decreasing && increasing) {
            is_safe = false;
        }
        if (is_safe) safe_levels_amount++;
    }
    input_file.close();
    std::cout << "Safe levels amount: " << safe_levels_amount << '\n';
    return 0;
}
