#include <iostream> // used for input and output streams
#include <conio.h> // used for getch()
#include <limits> // used for clearing out "garbage" input

#include "quiz_helper.h" // include the quiz helper in the main.cpp file

#define STRING std::string // used to make readability of this file easier
#define TEN_SECONDS 10 // used to make readability of this file easier

const int TOTAL_QUIZ_QUESTIONS = 9; // defines the total questions
const bool TIMED_QUESTION = true; // used to make readability of this file easier 

using std::cout; // shortens std::cout -> cout
using std::cin; // shortens std::cin -> cin

// Create a class named Questions so that we can create new questions easily.
class Question
{
	private:
		int option_size = 0;  // since this is a private variable, this cannot be directly changed from outside the class
	public:
		// Instantiating the necessary variables
		STRING question_text; // holds the question itself
		STRING* options = nullptr; // declaring a pointer for dynamic memory allocation, temporarily setting the pointer to a "nullptr"
		char correctAnswer; // holds the correct answer
		bool timedQuestion; // defines if this is a timed question or not
		int timer; // defines the time for a timed question
		
		// When this class is going to be instantiated, we will force ourselves to supply it with values.
		Question(STRING text, STRING options[], int optionSize, char correctAnswer, bool timedQuestion, int timer = 0)
		{
			// defining the variables given by the constructor
			question_text = text;
			option_size = optionSize;
			
			// using dynamic memory allocation to make an array with a custom size
			this->options = new STRING[option_size];
			
			// defining all the variables inside the options array
			for(int i =0; i < option_size; i++)
			{
				this->options[i] = options[i];
			}
			
			this->correctAnswer = correctAnswer;
			this->timedQuestion = timedQuestion;
			this->timer = timer;
		}
		
		// GETTERS
		int getOptionSize()
		{
			return option_size; // when this integer is called, we will return what option_size is. this is so we can still access the VALUE of it, however we still cannot change it
		}
		
		// Deconstructor to remove the memory when the object is out of scope/removed.
		~Question()
		{
			delete[] options;
		}
};

int main()
{
	// Instantiating the necessary variables:
	bool running = true; // for the game loop
	unsigned int score = 0; // holds the score for the quiz
	int number_input = 0; // holds the raw input for the number
	char playerOption; // holds the players choice
	unsigned int *total_questions = nullptr; // declaring a pointer, for now set it to a nullptr
	
    // Create all the options for the questions
    STRING question1_options[] = {"var x = 10;", "int x = \"10\";", "x := 10", "declare x = 10"}; // create all options for question 1
    STRING question2_options[] = {"string", "object", "int", "class"}; // create all options for question 2
    STRING question3_options[] = {"The variable cannot change", "The method or variable belongs to the class itself", "The method is private", "The method cannot return a value"}; // create all options for question 3
    STRING question4_options[] = {"for", "switch", "if", "Both a and b"}; // create all options for question 4
    STRING question5_options[] = {"func", "define", "method", "void"}; // create all options for question 5
	STRING question6_options[] = {"True", "False"}; // create all options for question 6
	STRING question7_options[] = {"True", "False"}; // create all options for question 7
	STRING question8_options[] = {"True", "False"}; // create all options for question 8
	STRING question9_options[] = {"override", "sealed", "virtual"}; // create all options for question 9
	
	// Create an array of questions depending on the amount of total quiz questions
	Question questions[TOTAL_QUIZ_QUESTIONS] = 
	{
		Question("What is the correct way to declare a variable in C#?: ", question1_options, 4, 'a', !TIMED_QUESTION), // Question 1
		Question("Which of the following is a value type in C#?: ", question2_options, 4, 'c', !TIMED_QUESTION), // Question 2
		Question("What does the static keyword mean in C#?: ", question3_options, 4, 'd', TIMED_QUESTION, TEN_SECONDS), // Question 3
		Question("Which statement is used to make decisions based on different cases in C#?: ", question4_options, 4, 'b', !TIMED_QUESTION), // Question 4
		Question("Which keyword is used to define a method in C#?: ", question5_options, 4, 'd', TIMED_QUESTION, TEN_SECONDS), // Question 5
		Question("The foreach loop is used to iterate over elements in a collection in C#: ", question6_options, 2, 'a', !TIMED_QUESTION), // Question 6
		Question("The const keyword defines a constant whose value cannot change at runtime in C#: ", question7_options, 2, 'a', !TIMED_QUESTION), // Question 7
		Question("You can inherit from multiple classes in C#: ", question8_options, 2, 'b', TIMED_QUESTION, TEN_SECONDS), // Question 8
		Question("Which keyword allows a method in a base class to be overridden in a derived class?: ", question9_options, 3, 'c', TIMED_QUESTION, TEN_SECONDS), // Question 9
	};
	
	// STARTING MAIN GAME LOOP -----------
	do{
		// Through dynamic memory allocation, ask the user how much questions they want to use.
		do{
			cout << "How many questions do you want (1-" << TOTAL_QUIZ_QUESTIONS << ")?" << '\n'; // display how much questions the user wants to answer
			cin >> number_input; // store the users input into number_input
			
			std::cin.clear(); // clear any error flags at cin.
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip to new line and proceed with the program for no further issues.
		}while(number_input < 1 || number_input > TOTAL_QUIZ_QUESTIONS); // continue this loop until number_input is a value between "1" and the total number of quiz questions.
		
		cout << "-------\n";
		
		total_questions = new unsigned int(number_input); // store the correct input of the user 
		
		// Display each question
		for(unsigned int i = 0; i < *total_questions; i++)
		{
			// Display question text
			cout << i + 1 << ") "<< questions[i].question_text << '\n';
			
			// Display all the options for the question
			for(int j = 0; j < questions[i].getOptionSize(); j++)
			{
				cout << char(97 + j) << ") " << questions[i].options[j] << '\n'; // char(97 + j), please refer to ASCII table : essentially when the loop runs it goes from 'a' -> 'b' -> 'c' -> ... https://www.ascii-code.com/
			}
			
			// CHECK IF QUESTION IS TIMED, then ask for user input
			if(questions[i].timedQuestion == true)
			{
				// IF QUESTION IS TIMED:
				clearInputBuffer(); // clears if there's any left over input from the previous timed question
				
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
	
	cout << "Thanks for playing!";
	
	getch(); // pauses the program ending until the user types on the keyboard
	return 0;
}