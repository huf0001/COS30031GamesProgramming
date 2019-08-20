
#include "pch.h"
#include <iostream>
#include <array>
#include <vector>
#include <stack>
#include <deque>
#include <queue>
#include <list>
#include <algorithm>

using namespace std;


// NOTE: this example code uses C++11 extensions ("auto" in particular)
// so you may need to tell your compiler to use these with a flag
// For example, -std=C++11 or similar.
struct Particle {
    int x, y;
};

class ParticleClass {
    public:
        int x, y;
        // ParticleClass(); // works, but random (not set) initial values
        ParticleClass() { x = 0; y = 0; }; // default, called by collections
        ParticleClass(int x, int y) { this->x = x; this->y = y; }
        void show() {
            cout <<  " - ParticleClass: (" << x << ", " << y << ")" << endl;
        }
};

void showParticleArray(const array<int, 3> &arr)
{
    // #TODO: apparently const prevents a copy - quicker performance. true? ref/url?
    cout << " - array<int, 3> contents: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//TODO (self): read through array demo
void array_demo()
{
    // std::array
    // A templated class for "fixed size" arrays (with known internal buffer)
    // - prevents "decay" usage into a pointer (unlike [] types)
    // - maintains array size for us (fixed)
    // - bounds checking
    // - C++ container operations size, begin, end ...
    //   (except size-changing push/pop etc)
    // - can be passed *by value* to a function (others can't)
    //
    // methods?
    //  - iterators: begin, end, rbegin, fend
    //  - capacity: size, max_size, empty
    //  - access: front, back, [], at()
    //  - modifiers: swap

    cout << " << std:array demos!>>" << endl;
    // simple quick array example
    array<int, 3> a1 = {8, 77, -50}; // initialiser list
    cout << "a1 address: " << hex << &a1 << endl;
    cout << dec; // put back to decimal mode (after being in hex)
    cout << "a1 size: " << a1.size() << endl;
    // array size is fixed, so max_size == size
    cout << "a1 max_size: " << a1.max_size() << endl;

    // access of elements? using []
    cout << "alterning a1[0]: " << a1[0];
    a1[0] = 42; // the answer
    cout << " is now " << a1[0] << endl;

    // show all the contents?
    cout << "a1 contents: ";
    for (int i = 0; i < a1.size(); i++) {
        cout << a1[i] << " ";
        //printf("%d ", a1[i]); // or, good 'ole printf ... shorter eh?
    }
    cout << endl;

    // pass to a function (by value, using const to ensure it is not copied)
    showParticleArray(a1);

    // access of array by [index] is not range protected (BAD)
    //cout << "What is at [3]? (out of bounds) " << a1[3] << endl;
    // the at(index) is range protected (but slower due to getter)
    //TODO - try this and note what happens.
    if (false)
        cout << "What is at(3)? (out of range exception) " << a1.at(3) << endl;

    // let's use some other container methods
    cout << "front() == " << a1.front() << endl;
    cout << "back() == " << a1.back() << endl;
    cout << "empty() == " << a1.empty() << endl; // #TODO empty() work? try

    // #TODO: (optional). create examples of swap() and fill()
    // a1.swap(s2) and a1.fill(value) also.
	array<int, 3> s2 = { 5, 10, 32 };
	a1.swap(s2);
	cout << "swap()" << endl;
	cout << "a1 contents (originally 42, 77, -50):";

	for (int i = 0; i < a1.size(); i++)
	{
		cout << " " << a1[i];
	}

	cout << endl;
	cout << "s2 contents (originally 5, 10, 32):";

	for (int i = 0; i < s2.size(); i++)
	{
		cout << " " << s2[i];
	}

	cout << endl;
	cout << "fill()" << endl;
	s2.fill(394);
	cout << "s2 contents:";

	for (int i = 0; i < s2.size(); i++)
	{
		cout << " " << s2[i];
	}

	cout << endl;
	

    // iterator for loop
    // #TODO: auto is awesome. What is the actual type of v that it works out for us?
    cout << "Using for with iterator ... " << endl;
    for (auto v = a1.begin(); v != a1.end(); v++)
        cout << " " << *v;
    cout << endl;

    // iterator for-each loop
    // #TODO: auto is still awesome. What is the actual type of v here?
    cout << "Using for-each (ranged) iterator ... " << endl;
    for (auto &v : a1)
        cout << " " << v;
    cout << endl;

    // sort?
    sort(a1.rbegin(), a1.rend());
    cout << "Reverse Sort() on a1, now ..." << endl;
    showParticleArray(a1);
    // #TODO: do a forward (not reverse) sort?
	sort(a1.begin(), a1.end());
	cout << "Forward Sort() on a1, now ..." << endl;
	showParticleArray(a1);

    // multidimensional array (note the dimension order)
    array<array<int,2>,4> a_2d = { {{1,2}, {3,4}, {5,6}, {7,8}} };
    cout << "2d array access a_2d[2][0] == " << a_2d[2][0] << endl;
    // #TODO: vote - are multi-dimensinal arrays pretty to create?

    // section end
    cout << " done." << endl;

    // a1 etc will be cleaned up (deleted) when out of scope
    // #TODO: how could you confirm this?


    if (true) {
        // array of 5 ints, must state size
        array<int, 5> a1;
        array<int, 4> a2 = {-4, 2, 7, -100};

        cout << "a1 " << hex << &a1 << " " << a1.size() << endl;
        cout << "a2 " << hex << &a2 << " " << a2.size() << endl;

        // new array via copy
        auto a3 = a2; // this is a copy
        // if auto doesn't work (C++11 extension) either configure your compiler
        // or state the type explicitly. (VS2010+ should support it, etc)
        // - array<int, 4> a3 = a2; // equivalent to auto
        // - array<int, 4> z1 = a1; // compile error - different length

        cout << "a3 " << hex << &a3 << " " << a3.size() << endl;
        auto a4(a1); // this works too
        cout << "a4 " << hex << &a4 << " " << a4.size() << endl;

        cout << endl;
        // the at() supports bounds checking, [] does not

    }


    if (true) {
        // Array of struct Particles
        // We cam reuse 'a1' etc because scope was contained eariler with {...}
        array<Particle, 3> a1; // random/not initialised values
        array<Particle, 3> a2 {}; // initialised values to 0, can write = {} also

        // old school for loop (clear, simple, quick)
        // note: initial values may be random - struct has no default initialiser
        cout << "a1 array of Particles ..." << endl;
        for (int i = 0; i < a1.size(); i++)
            cout << " - Particle: " << i << " (" << a1[i].x << ", " << a1[i].y << ")" << endl;

        cout << "a2 array of Particles, initialised, using for-each ..." << endl;
        for(auto &p: a2)
            cout << " - Particle: (" << p.x << ", " << p.y << ")" << endl;

    }

    if (true) {
        array<ParticleClass, 3> a1;

        cout << "Show a1 array of ParticleClass instance details ... " << endl;
        for(auto &p: a1)
            cout << " - ParticleClass: (" << p.x << ", " << p.y << ")" << endl;

        cout << "Show a1 array of ParticleClass instance details using show() ... " << endl;
        for(auto &p: a1)
            p.show();

    }
}

//TODO (self): read through stack demo
void stack_demo()
{
    // stack (LIFO, container adaptor)
    // - empty, size, back, push_back, pop_back (standard container)
    // - top, push, pop (no [] or at() ...)
    // - will use a deque if container type not specified
    stack<int> s1;
    // push some values onto the stack, last on top()
    cout << "Stack (LIFO) ... " << endl;
    for (int i=0; i<5; ++i) s1.push(i);

    cout << "Removing stack elements with pop() ...";
    while (!s1.empty()) {
        cout << ' ' << s1.top(); // last added (newest)
        s1.pop();
    }
    cout << endl;
}

//TODO (self): read through queue demo
void queue_demo()
{
    // queue (FIFO, container adaptor)
    // - empty, size, back, push_back, pop_back (standard container)
    // - front, back, push, pop (no [] or at() ...)
    // - will use a deque if container type not specified
    queue<int> q1;
    // push some values onto the stack, last on top()
    cout << "Queue (FIFO) ... " << endl;
    for (int i=0; i<5; ++i) q1.push(i);

    cout << "Removing queue elements with pop() ...";
    while (!q1.empty()) {
        cout << ' ' << q1.front();
        q1.pop(); // front (first, or oldest), not last
    }
    cout << endl;
}

//TODO (self): read through list demo
void list_demo()
{
    // std::list
    // A sequence container (internally, a doubly-linked list)
    // - specialised for constant time insert/erase at any position
    // - good at insert, extract, move but uses iterator (not uint index)
    // - house-keeping overhead (link details)
    // - iteration in either direction
    list<int> l1;
    list<int>::iterator it;

    // set some initial values:
    cout << "List (double-linked list) ... " << endl;
    for (int i=1; i<=5; ++i) l1.push_back(i); // 1 2 3 4 5

    cout << " - list contains:";
    for(auto &i: l1) cout << " " << i;
    cout << endl;

    // modify
    cout << "Insert using iterator access (end() - 1)" << endl;
    it = l1.end();
    --it;
    l1.insert(it, 77);

    // show inserted element
    cout << " - list contains:";
    for(auto &i: l1) cout << " " << i;
    cout << endl;

    // sort?
    cout << "Sort list (using default compare) ... " << endl;
    l1.sort();
    cout << " - list contains:";
    for(auto &i: l1) cout << " " << i;
    cout << endl;
}

//TODO (self): read through vector demo
void vector_demo()
{
    // std::vector
    // A templated class for "dynamic size" arrays
    // - maintains array size for us, (can use pointer offset still)
    // - bounds checking and resize/memory management (+overhead cost)
    // - C++ container operations (size, begin, end ... )

    // methods?
    //  - iterators: begin, end, rbegin, rend (+const iterators)
    //  - capacity: size, max_size, empty, resize, shrink_to_fit, capacity, reserve
    //  - access: front, back, [], at()
    //  - modifiers: assign, emplace*, insert, erase, emplace_back*,
    //               push_back, pop_back, clear, swap

    if (true) {
        // simple quick vector example
        vector<int> v1 = {8, 77, -50}; // initialiser list
        cout << "v1 address: " << hex << &v1 << endl;
        cout << dec; // put back to decimal mode (after being in hex)
        cout << "v1 size: " << v1.size() << endl;
        // vector size is not fixed, so max_size <> size (typically)
        cout << "v1 max_size: " << v1.max_size() << endl;

    }

    if (true) {
        vector<ParticleClass> v1;

        v1.push_back(ParticleClass(1,2));
        v1.push_back(ParticleClass(3,4));
        v1.push_back(ParticleClass(5,6));

        cout << "Show v1 vector of ParticleClass instance details using show() ... " << endl;
        for(auto &p: v1)
            p.show();
    }

}


int main()
{
    array_demo();

    stack_demo();

    queue_demo();

    list_demo();

	vector_demo();

    return 0;
}

