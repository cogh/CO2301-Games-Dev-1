#include "ConsoleManager.h"
#include <string>
#include <iostream>
#include <vector>

void ConsoleManager::reset()
{
    clear();
    prompt = "";
    answer_list.clear();
    answer = 0;
    valid_answer = false;
}

void ConsoleManager::set_prompt(string arg_prompt)
{
    prompt = arg_prompt;
}

void ConsoleManager::add_answer(string arg_answer)
{
    answer_list.push_back(arg_answer);
}

int ConsoleManager::get_answer()
{
    return answer;
}

void ConsoleManager::run()
{
    write_prompt();
    write_answers();
    input_answer();
    system("CLS");
}

void ConsoleManager::write_prompt()
{
    cout << prompt << endl;
}

void ConsoleManager::write_answers()
{
    for (int i = 0; i < answer_list.size(); i++) 
    {
        cout << i + 1 << ": " << answer_list[i] << endl;
    }
}

void ConsoleManager::input_answer()
{
    answer = 0;
    bool valid_answer = false;
    string input;
    // Check is numeric
    while (valid_answer == false) 
    {
        cin >> answer;
        if (answer > 0 && answer <= answer_list.size())
        {
            valid_answer = true;
        }
        else 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void ConsoleManager::stall()
{
    system("pause");
}

void ConsoleManager::clear()
{
    system("CLS");
}