#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct command_pair {
    std::string command;
    int value = 0;
} com;

struct position {
    int horizontal_pos = 0;
    int depth = 0;
    int aim = 0;
} pos_sub;

position execute_commands(const std::vector<command_pair>& commands)
{
    position pos;
    for (const auto & command : commands) {
        if (command.command == "forward"){
           pos.horizontal_pos += command.value;
           pos.depth += pos.aim * command.value;
        }

        if (command.command == "up")
            pos.aim -= command.value;
        if (command.command == "down")
            pos.aim += command.value;
    }
    return pos;
}
int main() {
    std::ifstream input_data;
    input_data.open("/home/nicholas/advent_of_code/input2.data");
    if (input_data.is_open())
        std::cout << "File succesfully opened" << std::endl;
    else {
        std::cout << "File  Error" << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    while (input_data.good())
    {
        std::string line;
        getline(input_data, line);
        lines.push_back(line);
    }
    std::cout << "File read" << std::endl;
    std::vector<command_pair> commands;

    for (auto & line : lines) {
        char delimiter = ' ';
        command_pair current_command;
        std::string value_string;

        size_t pos = 0;
        while (line[pos] != delimiter)
        {
            current_command.command.push_back(line[pos]);
            pos++;
        }
        for (pos++; pos < line.size(); ++pos) {
            value_string.push_back(line[pos]);
        }
        std::stringstream conv_stream;
        conv_stream << value_string;
        conv_stream >> current_command.value;
        commands.push_back(current_command);
    }
    position return_pos = execute_commands(commands);
    int result = return_pos.depth * return_pos.horizontal_pos;
    std::cout << result << std::endl;
    return 0;
}
