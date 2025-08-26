#include <iostream>
#include <conio.h>
#include <limits>

#include "quiz_helper.h" // include the quiz helper in the main.cpp file

#define STRING std::string // used to make readability of this file easier
#define TEN_SECONDS 10 // used to make readability of this file easier

const bool TIMED_QUESTION = true; // used to make readability of this file easier
const int TOTAL_QUIZ_QUESTIONS = 5;

using std::cout; // shortens std::cout -> cout
using std::cin; // shortens std::cin -> cin

// Create a class named Questions so that we can create new questions easily.
class Question
{
	public:
		// Instantiating the necessary variables
		STRING question_text;
		STRING options[4];
		char correctAnswer;
		bool timedQuestion;
		int timer;
		
		// When this class is trying to be instantiated, we will force ourselves to supply it with values.
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

int main()
{
	// Instantiating the necessary variables:
	bool running = true;
	unsigned int score = 0;
	int number_input = 0;
	char playerOption;
	unsigned int *total_questions;
	
    // Create all the options for the questions
    STRING question1_options[] = {"var x = 10;", "int x = \"10\";", "x := 10", "declare x = 10"};
    STRING question2_options[] = {"string", "object", "int", "class"};
    STRING question3_options[] = {"The variable cannot change", "The method or variable belongs to the class itself", "The method is private", "The method cannot return a value"};
    STRING question4_options[] = {"for", "switch", "if", "Both a and b"};
    STRING question5_options[] = {"func", "define", "method", "void"};
	
	// Create an array of questions
	Question questions[TOTAL_QUIZ_QUESTIONS] = 
	{
		Question("What is the correct way to declare a variable in C#?: ", question1_options, 'a', !TIMED_QUESTION), // Question 1
		Question("Which of the following is a value type in C#?: ", question2_options, 'c', !TIMED_QUESTION), // Question 2
		Question("What does the static keyword mean in C#?: ", question3_options, 'd', TIMED_QUESTION, TEN_SECONDS), // Question 3
		Question("Which statement is used to make decisions based on different cases in C#?: ", question4_options, 'b', !TIMED_QUESTION), // Question 4
		Question("Which keyword is used to define a method in C#?: ", question5_options, 'd', TIMED_QUESTION, TEN_SECONDS) // Question 5
	};
	
	// STARTING MAIN GAME LOOP -----------
	do{
		// Through dynamic memory allocation, ask the user how much questions they want to use.
		do{
			cout << "How much questions do you want (1-5)?" << '\n'; // display how much questions the user wants to answer
			cin >> number_input; // store the users input into number_input
			
			std::cin.clear(); // clear any error flags at cin.
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}while(number_input < 1 || number_input > TOTAL_QUIZ_QUESTIONS); // continue this loop until number_input is a value between "1-5".
		total_questions = new unsigned int(number_input); // store the correct input of the user 
		
		// Display each question
		for(unsigned int i = 0; i < *total_questions; i++)
		{
			// Display each option
			cout << questions[i].question_text << '\n';
			for(int j = 0; j < 4; j++)
			{
				cout << char(97 + j) << ") " << questions[i].options[j] << '\n'; 
			}
			
			// CHECK IF QUESTION IS TIMED, then ask for user input
			if(questions[i].timedQuestion == true)
			{
				// IF QUESTION IS TIMED:
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
				// IF QUESTION IS UN-TIMED:
				cout << "Type the corresponding letter: ";
				cin >> playerOption;
			}
			
			// If the user's input matches the correct answer, add 1 to the score; otherwise it is false.
			playerOption == questions[i].correctAnswer ? scoreChange(&score, true) : scoreChange(&score, false);
			
			cout << "\n--------\n";
		}
		
		// Once all the questions have been sorted through, display the final score; then do the following cleanup code.
		cout << "Final score: " << score << "/" << *total_questions << '\n';
		delete total_questions;  // cleans up the memory taken by the total_questions
		score = 0; // set score back to 0
		
		// Ask the player if they want to retry
		if(!retry())
		{
			running = false;
		}
	}while(running);
	// END OF MAIN GAME LOOP -----------
	
	getch();
	return 0;
}