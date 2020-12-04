#include "common.h"
#include "turing.h"

void test_tape_io()
{
    Tape t;
    cout << t.read() << endl;
    for (int i = 0; i < 20; i++)
    {
        if (i < 5)
            t.write('A' + i, STAY);
        else if (i < 15)
            t.write('A' + i, LEFT);
        else
            t.write('A' + i, RIGHT);
        cout << t.getHead() << t.getTape() << endl;
    }
    cout << t.read() << endl;
    for (int i = 0; i < 4; i++)
    {
        t.write(SPACE, RIGHT);
    }
    cout << t.getHead() << t.getTape() << endl;
    for (int i = 0; i < 4; i++)
    {
        t.write(SPACE, RIGHT);
    }
    cout << t.getHead() << t.getTape() << endl;
}

void test_tape_io2()
{
    Tape t;
    for (int i = 0; i < 5; i++)
    {
        t.write(SPACE, LEFT);
    }
    cout << t.getTape() << endl;
}

void test_tape_verbose()
{
    char usespace = '-';  // to test cumstomed space, replace it with another
    Tape t(usespace);
    for (int i = 0; i < 20; i++)
    {
        if (i < 5)
            t.write('A' + i, STAY);
        else if (i < 15)
            t.write('A' + i, LEFT);
        else
            t.write('A' + i, RIGHT);
        cout << t.verbose(0, 1);
        cout << "------------------" << endl;
    }
    for (int i = 0; i < 18; i++)
    {
        t.write(usespace, RIGHT);
        cout << t.verbose(0, 1);
        cout << "------------------" << endl;
    }
}

void test_turing()
{
    Turing turing("tm/palindrome_detector_2tapes.tm", "1001001");
    cout << turing.execute(true);
}

void test_tape_space()
{
    Tape t;
    for (int i = 0; i < 5; i++)
    {
        t.write('A' + i, RIGHT);
        cout << t.verbose(0, 1) << endl;
    }
    for (int i = 0; i < 7; i++)
    {
        t.write(SPACE, LEFT);
        cout << t.verbose(0, 1) << endl;
    }
    for (int i = 0; i < 7; i++)
    {
        t.write('A' + i, LEFT);
        cout << t.verbose(0, 1) << endl;
    }
}

int main()
{
    test_turing();
    return 0;
}