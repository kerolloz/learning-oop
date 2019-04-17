#include <stdlib.h>
#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd // stupid MSFT "deprecation" warning
#else
    #include <unistd.h>
#endif
#include "flags.hpp"

using namespace std;

class Checker{
    private:
        string tester;
        string compilerExecutable;
        string cwd;
        std::string get_cwd(){
            // returns current working directory
            char temp[1000];
            return ( getcwd(temp, sizeof(temp)) ? std::string( temp ) : std::string("") );
        }
    public:

        explicit Checker(string test) {
            tester = move(test);
            cwd = get_cwd();
            compilerExecutable = "g++";
        }

        Compilation compile(){
            std::string command = compilerExecutable + " " + cwd + "/" + tester + " -o " + cwd + "/test";
            int compilationState = system(command.c_str());
            return (compilationState)? Compilation::FAILED : Compilation::SUCCESS ;
        }

        Test test(){
            std::string command = "./test";
            int returnValue = system(command.c_str());
            system("rm ./test"); // remove the test binary after testing
            return (returnValue == 0)? Test::SUCCESS : Test::FAILED; 
                
        }

};