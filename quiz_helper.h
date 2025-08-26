#ifndef QUIZ_HELPER
#define QUIZ_HELPER

	void getInput();
	bool retry();
	bool timedInput(char& input, int timeoutSeconds);
	void scoreChange(unsigned int* score, bool succeed);

#endif