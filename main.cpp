#include <iostream>
#include <conio.h>
#include <limits>
#include <chrono>
#include <thread>
#include <atomic>

#define STRING std::string
#define TEN_SECONDS 10

const bool TIMED_QUESTION = true;

std::atomic<bool> inputReceived(false);

using std::cout;
using std::cin;

class Question
{
	public:
		STRING question_text;
		STRING options[4];
		char correctAnswer;
		bool timedQuestion;
		int timer;
	Question(STRING text, STRING options[4], char correctAnswer, bool timedQuestion, int timer = 0)
	{
		question_text = text;
        
		for(int i = 0; i < 4; i++)
        {
        	this->options[i] = options[i];
        };
        
		this->correctAnswer = correctAnswer;
		this->timedQuestion = timedQuestion;
		this->timer = timer;
	}
};

char userInput = '\0';

void getInput()
{
    cin >> userInput;
    inputReceived = true;
}

bool timedInput(char& input, int timeoutSeconds);
void scoreChange(unsigned int* score, bool succeed);

int main()
{
	bool running = true;
	unsigned int score = 0;
	int number_input = 0;
	char playerOption;
	unsigned int *total_questions;
	
    // Question Options
    STRING question1_options[] = {"var x = 10;", "int x = \"10\";", "x := 10", "declare x = 10"};
    STRING question2_options[] = {"string", "object", "int", "class"};
    STRING question3_options[] = {"The variable cannot change", "The method or variable belongs to the class itself", "The method is private", "The method cannot return a value"};
    STRING question4_options[] = {"for", "switch", "if", "Both a and b"};
    STRING question5_options[] = {"func", "define", "method", "void"};
	
	Question questions[5] = 
	{
		Question("What is the correct way to declare a variable in C#?: ", question1_options, 'a', !TIMED_QUESTION), // Question 1
		Question("Which of the following is a value type in C#?: ", question2_options, 'c', !TIMED_QUESTION), // Question 2
		Question("What does the static keyword mean in C#?: ", question3_options, 'd', TIMED_QUESTION, TEN_SECONDS), // Question 3
		Question("Which statement is used to make decisions based on different cases in C#?: ", question4_options, 'b', !TIMED_QUESTION), // Question 4
		Question("Which keyword is used to define a method in C#?: ", question5_options, 'd', TIMED_QUESTION, TEN_SECONDS) // Question 5
	};
	
	do{
		do{
			cout << "How much questions do you want (1-5)?" << '\n';
			cin >> number_input;
			
			std::cin.clear(); // clear any error flags at cin.
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}while(number_input < 1 || number_input > 5);
		total_questions = new unsigned int(number_input);
		
		// display each question
		for(unsigned int i = 0; i < *total_questions; i++)
		{
			cout << questions[i].question_text << '\n';
			for(int j = 0; j < 4; j++)
			{
				cout << char(97 + j) << ") " << questions[i].options[j] << '\n'; 
			}
			
			// CHECK IF QUESTION IS TIMED, then ask for user input
			if(questions[i].timedQuestion == true)
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				
				cout << "You have " << questions[i].timer << " seconds to answer the question." << '\n';
				cout << "Type the corresponding letter: ";
				
				bool gettingInput = timedInput(playerOption, questions[i].timer);
				if(!gettingInput)
				{
					cout << "\nTime's up! No answer recorded.\n";
                    playerOption = '\0';  // mark invalid input
				}
			}
			else
			{
				cout << "Type the corresponding letter: ";
				cin >> playerOption;
			}
			
			playerOption == questions[i].correctAnswer ? scoreChange(&score, true) : scoreChange(&score, false);
			
			cout << "\n--------\n";
		}
		
		running = false;
		
		cout << "Final score: " << score << "/" << *total_questions;
		delete total_questions; 
		
	}while(running);
	
	getch();
	return 0;
}

void scoreChange(unsigned int* score, bool succeed)
{
	if(succeed)
	{
		*score = *score + 1;
		cout << "You've answered correctly!";
	}
	else
	{
		cout << "You've answered incorrectly!";
	}
}

bool timedInput(char& input, int timeoutSeconds)
{
	using namespace std::chrono;

    cout.flush();
    auto start = steady_clock::now();

    while (true)
    {
        if (cin.peek() != EOF)
        {
            cin >> input;

            // Clear the rest of the line to avoid leftover input
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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