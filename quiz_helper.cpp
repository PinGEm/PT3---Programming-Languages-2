#include <iostream> // for all the input and output streams
#include <chrono> // used for timing
#include <thread> // used for timing
#include <conio.h> // used for timing
#include "quiz_helper.h" // used to define all the functions and to connect it to main.cpp

bool retry()
{
	std::string rawInput;
	char input;
	
	std::cout << "Type 'R' to retry the quiz: ";
	std::cin >> rawInput;
	std::cout << "--------\n";
	
	
	// Check if the input is valid
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

void scoreChange(unsigned int* score, bool succeed) // we get the pointer so we can influence the value, which is not possible if we had only done pass by value
{
	if(succeed)
	{
		*score = *score + 1; // dereference the score so we can influence it's value
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

    std::cout.flush(); // clears the input before starting the loop
    auto start = steady_clock::now(); // sets the start value to what time it is now
	
	
	// runs an infinite loop until it returns a value
    while (true)
    {
		if (_kbhit()) // Check to see if a key has been pressed
		{
			input = _getch(); // gets the character immediately, no Enter needed
			std::cout << input << '\n'; // displays the user's choice.
			return true;
		}
		
		
        auto now = steady_clock::now(); // sets the variable "now" to whatever time it is now
        auto elapsed = duration_cast<seconds>(now - start).count(); // get the actual seconds now from minusing the time NOW from the START time


        if (elapsed >= timeoutSeconds) // once we've passed the amount of seconds, return false.
        {
            return false;
        }

        std::this_thread::sleep_for(milliseconds(100)); // Avoid busy wait, saves CPU usage
    }
};

void clearInputBuffer()
{
	while(_kbhit())
	{
		_getch(); // discard characters in buffer.
	}
}