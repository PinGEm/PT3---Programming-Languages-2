#include <iostream>
#include <chrono>
#include <thread>
#include "quiz_helper.h"

bool retry()
{
	std::string rawInput;
	char input;
	
	std::cout << "Type 'R' to retry the quiz: ";
	std::cin >> rawInput;
	std::cout << "--------\n";
	
	if(!rawInput.empty())
	{
		input = toupper(rawInput.at(0));
	}
	else
	{
		input = '\0'; // null
	}
	
	if(input == 'R')
	{
		return true;
	}
	else
	{
		return false;
	}
};

void scoreChange(unsigned int* score, bool succeed)
{
	if(succeed)
	{
		*score = *score + 1;
		std::cout << "You've answered correctly!";
	}
	else
	{
		std::cout << "You've answered incorrectly!";
	}
}

bool timedInput(char& input, int timeoutSeconds)
{
	using namespace std::chrono;

    std::cout.flush();
    auto start = steady_clock::now();

    while (true)
    {
        if (std::cin.peek() != EOF)
        {
            std::cin >> input;

            // Clear the rest of the line to avoid leftover input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            return true;
        }

        auto now = steady_clock::now();
        auto elapsed = duration_cast<seconds>(now - start).count();

        if (elapsed >= timeoutSeconds)
        {
            return false;
        }

        std::this_thread::sleep_for(milliseconds(100)); // Avoid busy wait
    }
};