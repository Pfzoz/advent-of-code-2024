#include <cctype>
#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Rule {
    int x;
    int y;
};

// First argument after file name is input file's path.
int main (int argc, char** args) {
    if (argc < 2) {
        std::cout << "Missing input file's input\n";
        return 1;
    }
    std::fstream input_file(args[1], std::ios_base::in);

    std::string line_buffer;
    std::vector<Rule> rules;
    std::vector<std::vector<int>> updates;
    int section = 0;
    while (std::getline(input_file, line_buffer)) {
        if (line_buffer == "") {
            section = 1;
        } else if (section == 0) {
            int separator_position = line_buffer.find("|");
            Rule rule = {std::stoi(line_buffer.substr(0, separator_position)), std::stoi(line_buffer.substr(separator_position + 1, line_buffer.size() - separator_position))};
            rules.push_back(rule);
        } else {
            std::stringstream line_stream(line_buffer);
            std::vector<int> update;
            std::string number;
            while (std::getline(line_stream, number, ',')) {
                update.push_back(std::stoi(number));
            }
            updates.push_back(update);
        }
    }

    int middle_numbers_sum = 0;
    int incorrectly_ordered_middle_numbers_sum = 0;
    int correctly_ordered = 0;
    for (int i = 0; i < updates.size(); i++) {
        bool correct_order = true;
        for (int j = 0; j < rules.size(); j++) {
            int x_pos = -1;
            int y_pos = -1;
            for (int k = 0; k < updates[i].size(); k++) {
                if (updates[i][k] == rules[j].x) {
                    x_pos = k;
                } else if (updates[i][k] == rules[j].y) {
                    y_pos = k;
                }
            }
            if (x_pos > y_pos && x_pos != -1 && y_pos != -1) {
                correct_order = false;
                break;
            }
        }
        if (correct_order) {
            middle_numbers_sum += updates[i][updates[i].size() / 2];
            correctly_ordered++;
        }
    }

    std::cout << "Correctly ordered: " << correctly_ordered << std::endl;
    std::cout << "Middle numbers' sum: " << middle_numbers_sum << std::endl;
    return 0;
}
