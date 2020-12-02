#include "common.h"
#include "component.h"

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
    Tape t;
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
        t.write(SPACE, RIGHT);
        cout << t.verbose(0, 1);
        cout << "------------------" << endl;
    }
}

int main()
{
    test_tape_verbose();
    return 0;
}