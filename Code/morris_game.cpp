/*
 * Author: Allama Hossain
 * Miscellaneous functions for Morris Variant Game
 */

#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

// Function declaration begin
vector<string> generate_add(string board_position);
vector<string> generate_hopping(string board_position);
vector<string> generate_move(string board_position);
vector<string> generate_remove(string board_position, vector<string> board_vector);
vector<int> neighbors(int loc);
bool close_mill(int loc, string board_position, char value);
// Function declaration end


vector<string> generate_moves_opening(string board_position)
{
    return generate_add(board_position);
}

vector<string> generate_moves_midendgame(string board_position)
{
    if(count(board_position.begin(), board_position.end(), 'W') == 3)
        return generate_hopping(board_position);
    else
        return generate_move(board_position);
}

vector<string> generate_add(string board_position)
{
    vector<string> board_vector;
    for(int idx = 0; idx < board_position.size(); idx++)
        if(board_position[idx] == 'x')
        {
            string temp_board = board_position;
            temp_board[idx] = 'W';
            if(close_mill(idx, temp_board, 'q'))
                board_vector = generate_remove(temp_board, board_vector);
            else 
                board_vector.push_back(temp_board);
        }
    return board_vector;
}

vector<string> generate_hopping(string board_position)
{
    vector<string> board_vector;
    for(int idx = 0; idx < board_position.size(); idx++)
        if(board_position[idx] == 'W')
        {
            for(int jdx = 0; jdx < board_position.size(); jdx++)
                if(board_position[jdx] == 'x')
                {
                    string temp_board = board_position;
                    temp_board[idx] = 'x';
                    temp_board[jdx] = 'W';
                    if(close_mill(jdx, temp_board, 'q'))
                        board_vector = generate_remove(temp_board, board_vector);
                    else 
                        board_vector.push_back(temp_board);
                }
        }
    return board_vector;
}

vector<string> generate_move(string board_position)
{
    vector<string> board_vector;
    for(int idx = 0; idx < board_position.size(); idx++)
        if(board_position[idx] == 'W')
        {
            vector<int> neighbor_loc = neighbors(idx);
            for(auto jdx : neighbor_loc)
                if(board_position[jdx] == 'x')
                {
                    string temp_board = board_position;
                    temp_board[idx] = 'x';
                    temp_board[jdx] = 'W';
                    if(close_mill(jdx, temp_board, 'q'))
                        board_vector = generate_remove(temp_board, board_vector);
                    else 
                        board_vector.push_back(temp_board);
                }
        }
    return board_vector;
}

vector<string> generate_remove(string board_position, vector<string> board_vector)
{
    for(int idx = 0; idx < board_position.size(); idx++)
        if(board_position[idx] == 'B')
            if(!close_mill(idx, board_position, 'q'))
            {
                string temp_board = board_position;
                temp_board[idx] = 'x';
                board_vector.push_back(temp_board);
            }
    return board_vector;
}

string flip_board(string board_position)
{
    string flipped_board;
    for(auto &loc : board_position)
        if(loc == 'B')
            loc = 'W';
        else if(loc == 'W')
            loc = 'B';
        else
            loc = 'x';
    return board_position;
}

vector<string> generate_moves_opening_black(string board_position)
{
    vector<string> reversed_moves;
    string black_board_temp = flip_board(board_position);
    vector<string> black_moves = generate_add(black_board_temp);
    for(int idx = 0; idx < black_moves.size(); idx++)
        reversed_moves.insert(reversed_moves.begin() + idx, flip_board(black_moves[idx]));
    return reversed_moves;
}

vector<string> generate_moves_midendgame_black(string board_position)
{
    vector<string> reversed_moves;
    string black_board_temp = flip_board(board_position);
    vector<string> black_moves = generate_moves_midendgame(black_board_temp);
    for(int idx = 0; idx < black_moves.size(); idx++)
        reversed_moves.insert(reversed_moves.begin() + idx, flip_board(black_moves[idx]));
    return reversed_moves;
}

vector<int> neighbors(int loc)
{
    vector<int> neighbors_vector;
    if(loc == 0)
    {
        neighbors_vector.push_back(1); neighbors_vector.push_back(2); neighbors_vector.push_back(15);
    }
    else if(loc == 1)
    {
        neighbors_vector.push_back(0); neighbors_vector.push_back(3); neighbors_vector.push_back(8);
    }
    else if(loc == 2)
    {
        neighbors_vector.push_back(0); neighbors_vector.push_back(3); neighbors_vector.push_back(4); neighbors_vector.push_back(12);
    }
    else if(loc == 3)
    {
        neighbors_vector.push_back(1); neighbors_vector.push_back(2); neighbors_vector.push_back(5); neighbors_vector.push_back(7);
    }
    else if(loc == 4)
    {
        neighbors_vector.push_back(2); neighbors_vector.push_back(5); neighbors_vector.push_back(9);
    }
    else if(loc == 5)
    {
        neighbors_vector.push_back(3); neighbors_vector.push_back(4); neighbors_vector.push_back(6);
    }
    else if(loc == 6)
    {
        neighbors_vector.push_back(5); neighbors_vector.push_back(7); neighbors_vector.push_back(11);
    }
    else if(loc == 7)
	{
        neighbors_vector.push_back(3); neighbors_vector.push_back(6); neighbors_vector.push_back(8); neighbors_vector.push_back(14);
    }    
    else if(loc == 8)
    {
        neighbors_vector.push_back(1); neighbors_vector.push_back(7); neighbors_vector.push_back(17);
    }   
    else if(loc == 9)
    {
        neighbors_vector.push_back(4); neighbors_vector.push_back(10); neighbors_vector.push_back(12);
    } 
    else if(loc == 10)
    {
        neighbors_vector.push_back(9); neighbors_vector.push_back(11); neighbors_vector.push_back(13);
    }    
    else if(loc == 11)
    {
        neighbors_vector.push_back(6); neighbors_vector.push_back(10); neighbors_vector.push_back(14);
    }    
    else if(loc == 12)
    {
        neighbors_vector.push_back(2); neighbors_vector.push_back(9); neighbors_vector.push_back(13); neighbors_vector.push_back(15);
    }   
    else if(loc == 13)
    {
        neighbors_vector.push_back(10); neighbors_vector.push_back(12); neighbors_vector.push_back(14); neighbors_vector.push_back(16);   
    } 
    else if(loc == 14)
    {
        neighbors_vector.push_back(7); neighbors_vector.push_back(11); neighbors_vector.push_back(13); neighbors_vector.push_back(17);
    }    
    else if(loc == 15)
    {
        neighbors_vector.push_back(0); neighbors_vector.push_back(12); neighbors_vector.push_back(16);
    }    
    else if(loc == 16)
    {
        neighbors_vector.push_back(13); neighbors_vector.push_back(15); neighbors_vector.push_back(17);
    }    
    else if(loc == 17)
    {
        neighbors_vector.push_back(8); neighbors_vector.push_back(14); neighbors_vector.push_back(16);
    }
    return neighbors_vector;
}

bool close_mill(int loc, string board_position, char value)
{
    if(value == 'q')
        value = board_position[loc];
    if(value == 'x')
        return false;

	if(loc == 0)
    {
        if(board_position[2] == value && board_position[4] == value)
            return true;
        return false;
    }
    else if(loc == 1)
    {
        if((board_position[3] == value && board_position[5] == value) || (board_position[8] == value && board_position[17] == value))
            return true;
        return false;
    }
    else if(loc == 2)
    {
        if(board_position[0] == value && board_position[4] == value)
            return true;
        return false;
    }
    else if(loc == 3)
    {
        if((board_position[7] == value && board_position[14] == value) || (board_position[1] == value && board_position[5] == value))
            return true;
        return false;
    }
    else if(loc == 4)
    {
        if(board_position[0] == value && board_position[2] == value)
            return true;
        return false;
    }
    else if(loc == 5)
    {
        if((board_position[1] == value && board_position[3] == value) || (board_position[6] == value && board_position[11] == value))
            return true;
        return false;    
    }
    else if(loc == 6)
    {
        if((board_position[5] == value && board_position[11] == value) || (board_position[7] == value && board_position[8] == value))
            return true;
        return false; 
    }
    else if(loc == 7)
    {
        if((board_position[6] == value && board_position[8] == value) || (board_position[3] == value && board_position[14] == value))
            return true;
        return false;
    }
    else if(loc == 8)
    {
        if((board_position[6] == value && board_position[7] == value) || (board_position[1] == value && board_position[17] == value))
            return true;
        return false;
    }
    else if(loc == 9)
    {
        if((board_position[15] == value && board_position[12] == value) || (board_position[10] == value && board_position[11] == value))
            return true;
        return false;
    }
    else if(loc == 10)
    {
        if((board_position[9] == value && board_position[11] == value) || (board_position[13] == value && board_position[16] == value))
            return true;
        return false; 
    }
    else if(loc == 11)
    {
        if((board_position[9] == value && board_position[10] == value) || (board_position[5] == value && board_position[6] == value) || (board_position[14] == value && board_position[17] == value))
            return true;
        return false;
    }
    else if(loc == 12)
    {
        if((board_position[15] == value && board_position[9] == value) || (board_position[13] == value && board_position[14] == value))
            return true;
        return false;
    }
    else if(loc == 13)
    {
        if((board_position[10] == value && board_position[16] == value) || (board_position[14] == value && board_position[12] == value))
            return true;
        return false;    
    }
    else if(loc == 14)
    {
        if((board_position[12] == value && board_position[13] == value) || (board_position[11] == value && board_position[17] == value) || (board_position[3] == value && board_position[7] == value))
            return true;
        return false; 
    }
    else if(loc == 15)
    {
        if((board_position[12] == value && board_position[9] == value) || (board_position[16] == value && board_position[17] == value))
            return true;
        return false;
    }
    else if(loc == 16)
    {
        if((board_position[15] == value && board_position[17] == value) || (board_position[13] == value && board_position[10] == value))
            return true;
        return false;
    }
    else if(loc == 17)
    {
        if((board_position[15] == value && board_position[16] == value) || (board_position[1] == value && board_position[8] == value) || (board_position[14] == value && board_position[11] == value))
            return true;
        return false;
    }
    return false;
}