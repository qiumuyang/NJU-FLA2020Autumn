#include "common.h"
#include "turing.h"

using namespace std;

void invalid_args()
{
    cerr << "invalid arguments" << endl;
    cerr << usage << endl;
}

int main(int argc, char *argv[])
{
    bool verbose = false;
    string tm_path, input;
    for (int i = 1; i < argc; i++)
    {
        string arg = string(argv[i]);
        if (arg == "-v" || arg == "--verbose")
        {
            verbose = true;
        }
        else if (arg == "-h" || arg == "--help")
        {
            cout << usage << endl;
            return 0;
        }
        else if (tm_path.empty())
        {
            tm_path = arg;
        }
        else if (input.empty())
        {
            input = arg;
        }
        else
        {
            invalid_args();
            return -1;
        }
    }
    if (tm_path.empty())
    {
        invalid_args();
        return -1;
    }

    Turing turing(tm_path, input);
    int ret = turing.execute(verbose);
    return ret;
}