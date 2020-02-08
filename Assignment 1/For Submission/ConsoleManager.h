/*** AARON ARMSTRONG***/

#pragma once
#include <string>
#include <vector>

using namespace std;

class ConsoleManager
{
public:
    string prompt;
    vector<string> answer_list = vector<string>();
    int answer;
    bool valid_answer;
    void reset();
    void set_prompt(string arg_prompt);
    void add_answer(string arg_answer);
    int get_answer();
    void run();
    void write_prompt();
    void write_answers();
    void input_answer();
    void stall();
    void clear();
};
