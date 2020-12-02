#include "common.h"
#include "component.h"

int main()
{
    Tape t;
    for (int i = 0; i < 20; i++) {
        if (i < 10)
            t.write('A'+i, STAY);
        else
            t.write('A'+i, LEFT);
        cout << t.head << t.tape << endl;
    }
    return 0;
}