
using namespace std;

class Time
{

private:
    int hours, min, second;

public:
    Time() : hours(0), min(0), second(0) {}
    Time(int hours, int min, int second)
    {
        this->hours = hours;
        this->min = min;
        this->second = second;
    }

    void Display() const
    {
        cout << hours << ":" << min << ":" << second << endl;
    }

    int getHours() { return this->hours; }
    int getMin() { return this->min; }
    int getSec() { return this->second; }

    void Add(Time t1, Time t2)
    {
        int H, M, S;
        H = M = S = 0;

        M += (t1.second + t2.second) / 60;
        S += (t1.second + t2.second) % 60;

        H += (t1.min + t2.min) / 60;
        M += (t1.min + t2.min) % 60;

        H += t1.hours + t2.hours;

        this->hours = H, this->min = M, this->second = S;
    }
};
