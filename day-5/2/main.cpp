#include <algorithm>
#include <cctype>
#include <ios>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Rule {
    int x;
    int y;
};

bool contains_all(std::vector<int> a, std::vector<int> b) {
    for (int i = 0; i < b.size(); i++) {
        if (std::find(a.begin(), a.end(), b[i]) == a.end()) return false;
    }
    return true;
}

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

    int correctly_ordered_middle_numbers_sum = 0;
    int all_middle_numbers_sum = 0;
    int incorrectly_ordered_middle_numbers_sum = 0;
    int correctly_ordered = 0, incorrectly_ordered = 0;
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
            correctly_ordered_middle_numbers_sum += updates[i][updates[i].size() / 2];
            correctly_ordered++;
            all_middle_numbers_sum += updates[i][updates[i].size() / 2];
            continue;
        }
        incorrectly_ordered++;
        std::map<int, std::vector<int>> precendence_map;
        std::vector<int> keys;
        for (int j = 0; j < updates[i].size(); j++) {
            std::vector<int> precedences;
            for (int k = 0; k < rules.size(); k++) {
                if (rules[k].x == updates[i][j] && std::find(updates[i].begin(), updates[i].end(), rules[k].y) != updates[i].end()) {
                    precedences.push_back(rules[k].y);
                }
            }
            precendence_map[updates[i][j]] = precedences;
            keys.push_back(updates[i][j]);
        }
        std::vector<int> correctly_ordered;
        while (keys.size()) {
            for (int j = 0; j < keys.size(); j++) {
                if (contains_all(correctly_ordered, precendence_map[keys[j]])) {
                    correctly_ordered.push_back(keys[j]);
                    keys.erase(keys.begin() + j);
                    break;
                }
            }
        }
        incorrectly_ordered_middle_numbers_sum += correctly_ordered[correctly_ordered.size() / 2];
        all_middle_numbers_sum += correctly_ordered[correctly_ordered.size() / 2];
    }

    std::cout << "Correctly ordered: " << correctly_ordered << std::endl;
    std::cout << "Incorrectly ordered: " << incorrectly_ordered << std::endl;
    std::cout << "Correctly ordered middle numbers' sum: " << correctly_ordered_middle_numbers_sum << std::endl;
    std::cout << "Incorrectly ordered middle numbers' sum: " << incorrectly_ordered_middle_numbers_sum << std::endl;
    std::cout << "All middle numbers' sum: " << all_middle_numbers_sum << std::endl;
    return 0;
}
