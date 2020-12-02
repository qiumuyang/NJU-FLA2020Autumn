#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        string arg = string(argv[i]);
    }
    return 0;
}