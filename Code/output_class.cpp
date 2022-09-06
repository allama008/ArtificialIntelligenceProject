/*
 * Author: Allama Hossain
 * Output Class for Morris Variant Game
 */


#include<iostream>
#include<vector>
#include<string>
using namespace std;

class output_class
{
    public:
        int estimate;
        int no_of_moves;
        string board_state;

        output_class()
        {
            estimate = 0;
            no_of_moves = 0;
            board_state = "";
        }

        output_class(int estimate, int no_of_moves, string board_state)
        {
            this->estimate = estimate;
            this->no_of_moves = no_of_moves;
            this->board_state = board_state;
        }
};