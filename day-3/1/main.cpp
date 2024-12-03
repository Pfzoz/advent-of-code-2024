#include <cctype>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>

int check_text_pos_result(std::string text, int position, int &new_position) {
    new_position = position;
    if (text.substr(position, 4) != "mul(") {
        new_position++;
        return 0;
    }
    char buffer;
    position += 4;
    std::string first_number_str = "";
    if (!std::isdigit(text[position])) {
        new_position = position + 1;
        return 0;
    }
    while (std::isdigit(text[position])) {
      first_number_str.push_back(text[position]);
      position++;
    }
    if (text[position] != ',') {
        new_position = position + 1;
        return 0;
    }
    position++;
    std::string second_number_str = "";
    if (!std::isdigit(text[position])) {
        new_position = position + 1;
        return 0;
    }
    while (std::isdigit(text[position])) {
        second_number_str.push_back(text[position]);
        position++;
    }
    if (text[position] != ')') {
        new_position = position + 1;
        return 0;
    }
    int first_number = std::stoi(first_number_str);
    int second_number = std::stoi(second_number_str);
    new_position = position + 1;
    return first_number * second_number;
}

// First argument after file name is input file's path.
int main (int argc, char** args) {
    if (argc < 2) {
        std::cout << "Missing input file's input\n";
        return 1;
    }
    std::fstream input_file(args[1], std::ios_base::in);
    std::string line, text = "";
    while (std::getline(input_file, line)) text += line;
    int result = 0, position = 0;
    while (position != text.size()) {
        int new_position;
        result += check_text_pos_result(text, position, new_position);
        position = new_position;
    }
    std::cout << "Result: " << result << std::endl;
    return 0;
}
