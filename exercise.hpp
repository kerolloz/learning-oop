#include <string>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>
#include <filesystem>
#include <fstream>
#define EXERCISES_FOLDER_NAME "exercises"

using namespace std;
namespace fs = filesystem;

class Exercise
{
private:
    int from;
    int to;

    void create_exercise(int exercise_number)
    {
        string dir_name = to_string(exercise_number);
        if (!fs::exists(dir_name) && fs::create_directory(dir_name))
        {
            chdir(dir_name.c_str());
            fstream("solution.cpp", fstream::app);
            fstream("tester.cpp", fstream::app) << "#include \"solution.cpp\"";
            fstream("README.md", fstream::app) << "# Exercise " + dir_name;

            cout << dir_name << " created!" << endl;
            cout
                << "\tCreated solution.cpp" << endl
                << "\tCreated tester.cpp" << endl
                << "\tCreated README.md" << endl;
            chdir("..");
        }
        else
        {
            cout << dir_name + " Already exists!" << endl;
        }
    }

    int calculate_next_exercise_number()
    {
        int maxExerciseNumber = 0;
        for (const auto &entry : fs::directory_iterator(EXERCISES_FOLDER_NAME))
            maxExerciseNumber = max(stoi(entry.path().filename()), maxExerciseNumber);
        return maxExerciseNumber + 1;
    }

public:
    Exercise(int from = -1, int to = -1)
    {
        if (from + to == -2)
        {
            from = to = calculate_next_exercise_number();
        }
        else if (to == -1)
        {
            to = from;
        }
        else
        {
            if (from > to)
                swap(from, to);
        }
        this->from = from;
        this->to = to;

        if (!fs::exists(EXERCISES_FOLDER_NAME))
            fs::create_directory(EXERCISES_FOLDER_NAME);

        chdir(EXERCISES_FOLDER_NAME);
    }

    void create()
    {
        while (from <= to)
        {
            create_exercise(from);
            from++;
        }
    }
};