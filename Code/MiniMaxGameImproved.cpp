/*
 * Author: Allama Hossain
 * Mini Max Game Improved Functionality for Morris Variant Game
 */

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include "output_class.cpp"
#include "morris_game.cpp"
using namespace std;

string input_board_position(string input_board_path)
{
    ifstream input_file(input_board_path);
    if (!input_file.is_open()) 
    {
        cerr<<"Could not open the file - '"<<input_board_path<<"'"<<endl;
        exit(EXIT_FAILURE);
    }
    return string((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
}

void output_board_position(string output_string, string output_filename)
{
    ofstream out(output_filename);
    out<<output_string;
    out.close();
}

int static_estimation_game_improved(string board_position)
{
    int num_white_pieces = count(board_position.begin(), board_position.end(), 'W');
    int num_black_pieces = count(board_position.begin(), board_position.end(), 'B');
    vector<string> black_midend_pos = generate_moves_midendgame_black(board_position);
    int num_black_moves = black_midend_pos.size();

    int counter = 0;
    for(int idx = 0; idx < board_position.size(); idx++)
        if(board_position[idx] == 'x' && close_mill(idx, board_position, 'W'))
            counter++;

    if(num_black_pieces <= 2)
        return 10000;
    else if(num_white_pieces <= 2)
        return -10000;
    else if(num_black_moves == 0)
        return 10000;
    else
        return 10000*(num_white_pieces - num_black_pieces + 2 * counter) - num_black_moves;
}

output_class minimax_game_improved(string board_position, int height, string flag)
{
    output_class curr_node;
    output_class child_node;
    vector<string> board_vector;

    if(height == 0)
        return output_class(static_estimation_game_improved(board_position), curr_node.no_of_moves + 1, board_position);

    if(flag == "max")
    {
        board_vector = generate_moves_midendgame(board_position);
        curr_node.estimate = INT_MIN;
    }
    else
    {
        board_vector = generate_moves_midendgame_black(board_position);
        curr_node.estimate = INT_MAX;
    }

    for(auto boards : board_vector)
        if(flag == "max")
        {
            child_node = minimax_game_improved(boards, height - 1, "min");
            if(child_node.estimate > curr_node.estimate)
            {
                curr_node.estimate = child_node.estimate;
                curr_node.board_state = boards;
            }
            curr_node.no_of_moves = curr_node.no_of_moves + child_node.no_of_moves;
        }
        else
        {
            child_node = minimax_game_improved(boards, height - 1, "max");
            if(child_node.estimate < curr_node.estimate)
            {
                curr_node.estimate = child_node.estimate;
                curr_node.board_state = boards;
            }
            curr_node.no_of_moves = curr_node.no_of_moves + child_node.no_of_moves;
        }

    return curr_node;
}

int main(int argc, char *argv[])
{
    string input_board_path = argv[1];
    string output_board_path = argv[2];
    int height = stoi(argv[3]);

    string input_string = input_board_position(input_board_path);
    output_class opc_obj = minimax_game_improved(input_string, height, "max");
    cout<<"Board Position: "<<opc_obj.board_state<<endl;
    cout<<"Positions evaluated by static estimation: "<<opc_obj.no_of_moves<<endl;
    cout<<"MINIMAX estimate: "<<opc_obj.estimate<<endl;
    output_board_position(opc_obj.board_state, output_board_path);
    return 0;
}