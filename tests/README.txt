All tests will end up in resulting an early termination once the file reaches \0.
As such ^D is executed.
All tests do not print the users input as the user did not enter it themselves, hence all
std::cin will take the answer however not show the command such as it will display '> '.
Also as we are using an input file the .gameout doesn't print a newline after '> ', however
if an actual user were to run the game it would work as intended.