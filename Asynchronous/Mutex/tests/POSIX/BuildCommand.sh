g++ -Wall -Wextra -pedantic -g -Og -std=c++17 -DDEBUG -o MutexTests.test ../../../LibraryMeta/LibraryMeta.cpp ../../../Debugging/Logging/Log.cpp ../../../Debugging/Debugging.cpp ../POSIXMutex.cpp -pthread *.cpp 