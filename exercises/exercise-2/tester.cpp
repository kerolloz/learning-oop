#include <iostream>
#include "solution.cpp"
using namespace std;

int main() {

    Time t1(2, 30, 35), t2(1, 59, 25);
    Time t3;

    t3.Add(t1, t2);
    
    if(t3.getHours() == 4 && t3.getMin()  == 30 && !t3.getSec()) 
        return 0;
    else
         return 1;
}