#include <iostream>
#include "exercise.hpp"
#define endl '\n'

using namespace std;

int print_usage()
{
    cout << "./create-exercise " << endl;
    cout << "./create-exercise [exercise_number]'" << endl;
    cout << "./create-exercise [from] [to]" << endl;
    return 0;
}

int main(int argc, char **argv)
{

    if (argc > 3)
        return print_usage();

    Exercise exercise(argc >= 2 ? atoi(argv[1]) : -1, argc == 3 ? atoi(argv[2]) : -1);
    exercise.create();
    return 0;
}