#include <cctype>
#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define SPACE '.'
#define OBSTACLE '#'
#define GUARD '^'

const int DIRECTIONS[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

struct Position {
    int line;
    int column;
};

bool position_equals(Position a, Position b) {
    return a.line == b.line && a.column == b.column;
}

struct Obstacle_Found_Struct {
    Position position;
    int direction;
};

class Map {
    private:
    std::vector<std::vector<char>> map_matrix;
    Position guard_position;
    int guard_direction;

    bool guard_on_exit() {
        if (guard_position.line == 0 || guard_position.column == 0) {
            return true;
        }
        if (guard_position.line == (map_matrix.size() - 1) || guard_position.column == (map_matrix[0].size() - 1)) {
            return true;
        }
        return false;
    }

    bool check_for_loop(Position obstruction_position, int direction) {
        std::vector<Obstacle_Found_Struct> obstacles_found;
        const int *walking_vector = DIRECTIONS[direction % 4];
        map_matrix[obstruction_position.line][obstruction_position.column] = OBSTACLE;
        Position current_position = {obstruction_position.line - walking_vector[1], obstruction_position.column - walking_vector[0]};
        obstacles_found.push_back({obstruction_position, direction});
        direction++;
        bool is_loop = false;
        while (current_position.line != 0
            && current_position.column != 0
            && current_position.line != (map_matrix.size() - 1)
            && current_position.column != (map_matrix[0].size() - 1)
            && !is_loop) {
            walking_vector = DIRECTIONS[direction % 4];
            Position new_position = {current_position.line + walking_vector[1], current_position.column + walking_vector[0]};
            if (map_matrix[new_position.line][new_position.column] == OBSTACLE) {
                bool already_found = false;
                for (int i = 0; i < obstacles_found.size() && !is_loop; i++) {
                    is_loop = position_equals(obstacles_found[i].position, new_position) && obstacles_found[i].direction % 4 == direction % 4;
                    already_found = is_loop;
                }
                if (!already_found) {
                    obstacles_found.push_back({new_position, direction});
                }
                direction++;
            } else {
                current_position = new_position;
            }
        }
        map_matrix[obstruction_position.line][obstruction_position.column] = SPACE;
        return is_loop;
    }

    public:
    Map(std::vector<std::vector<char>> map_matrix) {
        this->map_matrix = map_matrix;
        bool found_guard = false;
        for (int i = 0; i < map_matrix.size() && !found_guard; i++) {
            for (int j = 0; j < map_matrix[0].size() && !found_guard; j++) {
                if ((found_guard = (map_matrix[i][j] == GUARD))) {
                    guard_position = {i, j};
                    map_matrix[i][j] = SPACE;
                }
            }
        }
    }



    std::vector<Position> get_positions_visited(std::vector<Position> &possible_obstructions)
    {
        std::vector<Position> positions_visited;
        positions_visited.push_back(guard_position);
        possible_obstructions.clear();
        while (!guard_on_exit()) {
            const int *current_walking_vector = DIRECTIONS[guard_direction % 4];
            Position new_position = {guard_position.line + current_walking_vector[1], guard_position.column + current_walking_vector[0]};
            char new_position_tile = map_matrix[new_position.line][new_position.column];
            if (new_position_tile == OBSTACLE) {
                guard_direction++;
            } else if (new_position_tile == SPACE) {
                int already_visited = false;
                for (int i = 0; i < positions_visited.size() && !already_visited; i++) {
                    already_visited = position_equals(positions_visited[i], new_position);
                }
                if (!already_visited) {
                    positions_visited.push_back(new_position);
                    if (check_for_loop(new_position, guard_direction)) {
                        possible_obstructions.push_back(new_position);
                    }
                }
                guard_position = new_position;

            }
        }
        return positions_visited;
    }
};

std::vector<std::vector<char>> read_input(std::fstream &input_file)
{
    std::vector<std::vector<char>> matrix;
    std::string line_buffer;
    while (std::getline(input_file, line_buffer)) {
        std::stringstream line_stream(line_buffer);
        char char_buffer;
        std::vector<char> vector;
        while (line_stream >> char_buffer) {
            vector.push_back(char_buffer);
        }
        matrix.push_back(vector);
    }
    return matrix;
}

// First argument after file name is input file's path.
int main (int argc, char** args) {
    if (argc < 2) {
        std::cout << "Missing input file's input\n";
        return 1;
    }
    std::fstream input_file(args[1], std::ios_base::in);
    std::vector<std::vector<char>> map_matrix = read_input(input_file);
    Map map(map_matrix);
    std::vector<Position> possible_obstructions;
    std::vector<Position> positions_visited = map.get_positions_visited(possible_obstructions);
    std::cout << "Positions visited: " << positions_visited.size() << std::endl;
    std::cout << "Possible obstructions: " << possible_obstructions.size() << std::endl;
    input_file.close();
    return 0;
}
