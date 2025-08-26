#ifndef QUIZ_HELPER
#define QUIZ_HELPER

	bool retry();
	bool timedInput(char& input, int timeoutSeconds);
	void scoreChange(unsigned int* score, bool succeed);
	void clearInputBuffer();

#endif