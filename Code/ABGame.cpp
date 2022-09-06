/*
 * Author: Allama Hossain
 * Alpha Beta Game Functionality for Morris Variant Game
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

int static_estimation_midend(string board_position)
{
    int num_white_pieces = count(board_position.begin(), board_position.end(), 'W');
    int num_black_pieces = count(board_position.begin(), board_position.end(), 'B');
    vector<string> black_midend_pos = generate_moves_midendgame_black(board_position);
    int num_black_moves = black_midend_pos.size();

    if(num_black_pieces <= 2)
        return 10000;
    else if(num_white_pieces <= 2)
        return -10000;
    else if(num_black_moves == 0)
        return 10000;
    else
        return 10000*(num_white_pieces - num_black_pieces) - num_black_moves;
}

output_class alpha_beta_game(string board_position, int height, string flag, int alpha, int beta)
{
    output_class curr_node;
    output_class child_node;
    vector<string> board_vector;

    if(height == 0)
        return output_class(static_estimation_midend(board_position), curr_node.no_of_moves + 1, board_position);
    
    board_vector = flag == "max" ? generate_moves_midendgame(board_position) : generate_moves_midendgame_black(board_position);

    for(auto boards : board_vector)
    {
        if(flag == "max")
        {
            child_node = alpha_beta_game(boards, height - 1, "min", alpha, beta);
            if(child_node.estimate > alpha)
            {
                alpha = child_node.estimate;
                curr_node.board_state = boards;
            }
            curr_node.no_of_moves = curr_node.no_of_moves + child_node.no_of_moves;
        }
        else
        {
            child_node = alpha_beta_game(boards, height - 1, "max", alpha, beta);
            if(child_node.estimate < beta)
            {
                beta = child_node.estimate;
                curr_node.board_state = boards;
            }
            curr_node.no_of_moves = curr_node.no_of_moves + child_node.no_of_moves;
        }
        if(alpha >= beta)
            break;
    }

    curr_node.estimate = flag == "max" ? alpha : beta;

    return curr_node;
}

int main(int argc, char *argv[])
{
   string input_board_path = argv[1];
   string output_board_path = argv[2];
   int height = stoi(argv[3]);

    string input_string = input_board_position(input_board_path);
    output_class opc_obj = alpha_beta_game(input_string, height, "max", INT_MIN, INT_MAX);
    cout<<"Board Position: "<<opc_obj.board_state<<endl;
    cout<<"Positions evaluated by static estimation: "<<opc_obj.no_of_moves<<endl;
    cout<<"AB estimate: "<<opc_obj.estimate<<endl;
    output_board_position(opc_obj.board_state, output_board_path);
    return 0;
}