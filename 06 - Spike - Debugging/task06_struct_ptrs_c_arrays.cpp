/******************************************************************************

Simple examples of interesting things as a debugging exercise

Search for #TODO marks and then do ... :)

*******************************************************************************/
#include <iostream>

using namespace std;

// #TODO - What is the difference betweent a struct and a class?
struct Particle
{
    unsigned int age;
    int x;
    int y;
};

// Function declarations. Details later ...
void showParticle(Particle);

// #TODO - Why are variable names not needed?
Particle getParticleWith(int, int, int);

void setParticleWith(Particle, int, int, int);

void showParticleArray(Particle *, int);

void showParticleArray2(Particle arr[], int size);

// Main loop. Stuff happens here ...
int main()
{
    // 1. Warm up. Create a particle, set values, show to screen
    cout << " << Section 1 >>" << endl;
    Particle a;
    showParticle(a);  // #TODO - un-intitalise values? what did it show/why?
    a.age = 0;
    a.x = 10;
    a.y = 20;
    showParticle(a); // #TODO - worked as expected?

    // Note: uses of an initialisation list. (quicker then setting each as above!)
    // #TODO - Do you know about them? If not, find out and make a note in your report.
    Particle b = {0,0,0};
    cout << "b with initalised values 0,0,0 ... ";
    showParticle(b);

    // 2. Get a particle with the values we pass to the function
    //    (When you are up to this section, change false to true. Keeps things compact)
    if (false) {
        cout << " << Section 2 >>" << endl;
        b = getParticleWith(1,2,3);
        cout << "b with 1,2,3 ... ";
        showParticle(b); // #TODO Should show age=1, x=1, y=2. Does it?

        b = getParticleWith(-1,2,3);
        cout << "b with -1,2,3 ... ";
        showParticle(b); // #TODO. Something odd here. Why?
        // hint: debug, inspect and look at data type details ...
    }

    // 3. Set values in a particle that we already have
    if (false) {
        cout << " << Section 3 >>" << endl;
        // This compiles/runs, but ...
        setParticleWith(b, 5,6,7);
        cout << "b with 5,6,7 ... ";
        showParticle(b); // #TODO: showParticle(b) doesn't show 5,6,7 ... Why?
        // hint: step-into function and inspect values (and addresses)...
    }

    // 4. Use a pointer to an existing particle
    if (false) {
        cout << " << Section 4 >>" << endl;
        Particle *p1_ptr;
        // set b to be something sensible
        b = getParticleWith(5,5,5);
        cout << "new values of b ... ";
        showParticle(b);
        // get address of b, keep it ...
        p1_ptr = &b;

        // Note that (*p1_ptr).age gets the b.age values
        if ((*p1_ptr).age == b.age) cout << "TRUE!" << endl;
        // Note that (*p1_ptr).age is the same as p1_ptr->age
        if ((*p1_ptr).age == p1_ptr->age) cout << "TRUE!" << endl;
        // does that make sense?

        // pass the dereferenced pointer as argument
        cout << "b via dereferenced pointer ... ";
        showParticle((*p1_ptr));
        // #TODO: what is a dereferenced pointer (from the example)?

        // update b, ...
        // #TODO: pointer still what we expect? (or something new?)
        b = getParticleWith(7,7,7);
        cout << "new values of b ... ";
        showParticle(b);
        cout << "show particle pointer (same still?) ... ";
        showParticle((*p1_ptr));
        // #TODO: if they are the same, what does this this imply?
        // #TODO: if they are different, what does this this imply?

    }

    // 5. Array of structs
    if (false) {
        cout << " << Section 5 >>" << endl;

        Particle p_array1[3]; // NOTE: plain old array - not a fancy std::array
        p_array1[0] = getParticleWith(1,2,3);
        p_array1[1] = getParticleWith(4,5,6);
        p_array1[2] = getParticleWith(7,8,9);

        // show that we can access one element of the array
        cout << "p_array[2] with 4,5,6 ... ";
        showParticle(p_array1[1]);
        // Array of pointers to structs
        showParticleArray(p_array1, 3); // #TODO: MAGIC NUMBER BAD!! What is it and why bad?

        // Can we work out the length? Yes, but ...
        cout << "Array length?" << endl;
        cout << " - sizeof entire array? " << sizeof(p_array1) << endl;
        cout << " - sizeof array element? " << sizeof(p_array1[0]) << endl;
        cout << " - array size n is: " << (sizeof(p_array1) / sizeof(p_array1[0])) << endl;
        // #TODO: explain in your own words how the array size is worked out.

        // Easy initialisation approach ... (note, it's not a 2-D array!)
        cout << "easy (~nested) initialiation ... " << endl;
        Particle p_array2[] = {{1,1,1}, {2,2,2}, {3,3,3}};
        showParticleArray(p_array2, 3); // works fine

        // #TODO: uncomment this - does it work the same?
        //showParticleArray2(p_array2, 3); // alternative signature

        // read (access) more then we should ... size 4 (but it's only 3)
        cout << "array position overrun ... " << endl;
        showParticleArray(p_array2, 4); // #TODO: HMM! What is the issue here??
        // #TODO: would you expect that same output all the time?
    }

    // 6. Struct pointer with new and delete for memory
    if (false) {
        cout << " << Section 6 >>" << endl;
        // Some pointer warm-up ideas. What you expect?
        Particle *p2_ptr; // points to nothing
        cout << "pointer address " << hex << p2_ptr << endl;
        Particle c = {9,9,9}; // a real and initialised Particle variable
        cout << "pointer address " << hex << &c << endl;
        p2_ptr = &c; // copy the point to the same particle
        cout << "pointer address " << hex << p2_ptr << endl;
        // #TODO: what is hex and what does it do? ref/url?

        // Now lets create a Particle that we only access via a pointers
        p2_ptr = new Particle(); // #TODO: what is new and what did it do?
        cout << "pointer address " << hex << p2_ptr << endl;
        showParticle((*p2_ptr));
        cout << "show via dereferenced pointer ... ";
        showParticle((*p2_ptr));
        cout << "set a value via pointer" << endl;
        p2_ptr->age = 99;
        showParticle((*p2_ptr));

        // Clean up!
        delete p2_ptr; // #TODO: what is delete and what did it do?
        cout << "pointer address " << hex << p2_ptr << endl;
        // #TODO: what happens if you try this? Explain
        cout << "Can we still show value at pointer address? (It was deleted, so ...) ";
        showParticle((*p2_ptr));

        // house keeping - if a pointer isn't valid, set it to nullptr/NULL
        p2_ptr = nullptr; // we used to use NULL (== 0)
        cout << "pointer address " << hex << p2_ptr << endl;
        // Zero test?
        if (p2_ptr == 0) { cout << "pointer == 0" << endl; }
        // #TODO: So, what is the difference between NULL and nullptr and 0?

        // TODO: what happens if you try this? (Zero address now, so ...)
        if (false) {
            showParticle((*p2_ptr));
        }
    }


    // 7. Array of pointers to structs
    if (false) {
        cout << " << Section 7 >>" << endl;
        int n = 5;
        Particle *ptr_array[n]; // contains pointers to nowhere so far!
        // #TODO: what is the pointer value? (Is it empty?/nullptr?) Can you trust it?
        cout << "pointer address " << hex << ptr_array[0] << endl;

        // initialise all the pointers with created Particles
        for (int i = 0; i < n; i++) {
            ptr_array[i] = new Particle();
            //ptr_array[i]->age = i; // #TODO: uncomment this to confirm it's working
        }
        // show each particle value
        cout << "Show each particle pointed to in the pointer array ..." << endl;
        for (int i = 0; i < n; i++) {
            showParticle((*ptr_array[i]));
            // #TODO: why is (*ptr_array[i]) needed?
        }
        // cleanup! Can you see what happens if you DON'T do this?
        if (false) {
            for (int i = 0; i < n; i++) {
                delete ptr_array[i];
                ptr_array[i] = nullptr; // Not always needed but good habit! #TODO: agree? why?
            }
        }
        // Note: if we dynamically created the array (with new), we should clean that up too.
    }

    return 0;
}

// Function details - each matches the function declarations at the top

void showParticle(Particle p)
{
    cout << "Particle: ";
    cout << "(age=" << p.age << "), ";
    cout << "(x,y)=(" << p.x << "," << p.y << ")" << endl;
}

Particle getParticleWith(int age, int x, int y)
{
    Particle result;
    result.age = age;
    result.x = x;
    result.y = y;
    return result;
}

void setParticleWith(Particle p, int age, int x, int y)
{
    p.age = age;
    p.x = x;
    p.y = y;
}

void showParticleArray(Particle * p_array, int size)
{
    // We can't ~actually~ pass an array, so ...
    // we pass a pointer to the first element of the array!
    // ... and the length. Which might be wrong.
    for (int i = 0; i < size; i++) {
        cout << " - pos=" << i << " ";
        showParticle(p_array[i]);
    }
}

void showParticleArray2(Particle arr[], int size)
{
    // #TODO - uncomment this. Does it work?
    // if (true) { // this does NOT work here. why?
    //     cout << "Array as arr[] ..." << endl;
    //     cout << " - sizeof entire array? " << sizeof(arr) << endl;
    //     cout << " - sizeof array element? " << sizeof(arr) << endl;
    //     cout << " - array size n is: " << (sizeof(arr) / sizeof(arr[0])) << endl;
    // }
    // #TODO: The above might get warnings (good!). Not all compilers though. Why?

    for (int i = 0; i < size; i++) {
        cout << " - pos=" << i << " ";
        showParticle(arr[i]);
    }
}