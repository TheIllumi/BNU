#include <iostream>
using namespace std;

class ComboLock
{
private:
    int lock1{0}, lock2{0}, lock3{0};
    int entered1{0}, entered2{0}, entered3{0};
    bool lock1picked = false;

public:
    ComboLock() = default;
    ComboLock(int s1, int s2, int s3) : lock1{s1}, lock2{s2}, lock3{s3} {}

    void Reset()
    {
        entered1 = 0;
        entered2 = 0;
        entered3 = 0;
        lock1picked = false;
    }

    void TurnRight(int ticks)
    {
        if (ticks > 0 && ticks < 39)
        {
            if (lock1picked == false)
            {
                entered1 += ticks;
                lock1picked = true;
            }
            else
            {
                entered3 += ticks;
            }
        }
    }

    void TurnLeft(int ticks)
    {
        if (ticks > 0 && ticks < 39)
        {
            entered2 += ticks;
        }
    }

    bool Open()
    {
        return (entered1 == lock1 && entered2 == lock2 && entered3 == lock3);
    }
};
int main()
{
    ComboLock safe(1, 2, 3);

    safe.TurnRight(1);
    safe.TurnLeft(2);
    safe.TurnRight(3);

    if (safe.Open())
    {
        cout << "Lock opened successfully!" << endl;
    }
    else
    {
        cout << "Failed to open the lock. Try again." << endl;
    }
    return 0;
}