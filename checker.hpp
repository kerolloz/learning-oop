#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd // stupid MSFT "deprecation" warning
#else
#include <unistd.h>
#endif
#include "flags.hpp"

using namespace std;

class Checker
{
private:
    string tester;
    string compilerExecutable;
    string cwd;
    string get_cwd()
    {
        // returns current working directory
        char temp[1000];
        return (getcwd(temp, sizeof(temp)) ? string(temp) : string(""));
    }

public:
    explicit Checker(string test)
    {
        tester = move(test);
        cwd = get_cwd();
        compilerExecutable = "make";
    }

    Compilation compile()
    {
        string command = compilerExecutable + " " + cwd + "/" + tester;
        int compilationState = system(command.c_str());
        return (compilationState) ? Compilation::FAILED : Compilation::SUCCESS;
    }

    Test test()
    {
        string command = cwd + "/" + tester;
        int returnValue = system(command.c_str());
        system(("rm " + command).c_str()); // remove the test binary after testing
        return (returnValue == 0) ? Test::SUCCESS : Test::FAILED;
    }
};