@echo on

g++ -m64 -Wall -O2 -std=c++17 -c main.cpp
g++ -m64 -Wall -O2 -std=c++17 -c quiz_helper.cpp
g++ -m64 -Wall -O2 -std=c++17 quiz_helper.o main.o -o pt_3

pause
exit