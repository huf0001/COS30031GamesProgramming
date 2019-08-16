#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

class ParticleClassA {
    public:
        int x, y;
        ParticleClassA() { x = 0; y = 0; }; 
        void show() { cout <<  "(" << x << ", " << y << ")" << endl; }
};

class ParticleClassB {
    private:
        int _x, _y;
    public:
        void do_stuff(int value) { _y = value + _x; }
        ParticleClassB() { _x = 0; _y = 0; }; 
        void show() { cout <<  "(" << x << ", " << y << ")" << endl; }
};

void exp_rampup_test(int steps)
{
    cout << " << Particle Ramp-up Test >> " << endl;
    uint size = 1;
    for (auto step = 1; step <= steps; step++) 
    {
        // 1. get start time
        auto start = steady_clock::now();
        // 2. do some work 
        vector<ParticleClassA> v(size);
        // ... do other stuff here on all the particles (in loop)?
        // 3. show duration time
        auto end = steady_clock::now();
        auto _dur = duration_cast<nanoseconds>( end - start ).count();
        cout << " - size: " << size << ", time: " << _dur << " ns"; 
        cout << " (ns/count): " << _dur/size<< endl;

        size = size * 10;
    }  
    cout << "done." << endl;
}

void exp_rampdown_test(int steps, bool do_more)
{
    cout << " << Particle Ramp-down Test >> " << endl;
    // Find top exponent size value, so we can work down. 
    // No in-built int power() for C++/std, so ... roll our own.
    uint size = 1;
    for (int i = 1; i < steps; i++) size = size * 10;

    // Do the test of vector creation, work on vector objects ...
    for (auto step = steps; step > 0; step--) 
    {
        // 1. get start time
        auto start = steady_clock::now();
        // 2. do some work 
        vector<ParticleClassA> v(size);
        // if (do_more) 
        // {
        //     for (auto &p: v) 
        //     {
        //         p.do_stuff(step);
        //     }
        // }
        // 3. show duration time
        auto end = steady_clock::now();
        auto _dur = duration_cast<nanoseconds>( end - start ).count();
        cout << " - size: " << size << ", time: " << _dur << " ns"; 
        cout << " (ns/count): " << _dur/size<< endl;
        // work down (by factors of 10 ...)
        size = size / 10;
    }  
    cout << "done." << endl;
}

int main()
{
    exp_rampup_test(5);
    exp_rampdown_test(5, false);
    exp_rampdown_test(5, true);
}

