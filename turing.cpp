#include "turing.h"

using namespace std;

void Turing::load_file()
{
    ifstream in(file);
    if (!in)
        throw TuringException(FILE_NOT_FOUND, 0, quote(file, "open failed"));
    string line;
    int idx = 0;
    while (getline(in, line))
    {
        idx++;
        line = removeComment(line);
        line = strip(line);
        if (!line.empty())
        {
            lines.push_back(line);
            line_ids.push_back(idx);
        }
    }
}

void Turing::verify_input()
{
    for (int i = 0; i < input.length(); i++)
    {
        if (!emulator.containsInputSymbol(input[i]))
        {
            throw TuringException(ILLEGAL_INPUT, i, quote(input[i], "was not declared in the set of input symbols"));
        }
    }
}

int Turing::execute(bool verbose)
{
    if (verbose)
        cout << "Input: " << input << endl;

    try
    {
        load_file();
        for (int i = 0; i < lines.size(); i++)
        {
            current_line = lines[i];
            current_line_id = line_ids[i];
            parser.parseLine(current_line);
        }
        emulator = parser.getTuringEmulator();
        emulator.checkIntegrity();
        verify_input();
        emulator.setInput(input);
    }
    catch (const TuringException& e)
    {
        handleExceptionPrint(verbose, e);
        return -1;
    }
    catch (const exception& e)
    {
        cerr << e.what() << endl;
        return -1;
    }

    if (verbose)
        cout << STATUS_SPLITTER << " RUN " << STATUS_SPLITTER << endl;
    string ret = emulator.execute(verbose);
    if (verbose)
        cout << STATUS_SPLITTER << " END " << STATUS_SPLITTER << endl;
    else
        cout << ret << endl;

    return 0;
}

void Turing::handleExceptionPrint(bool verbose, const TuringException& e)
{
    if (verbose)
    {
        cout << STATUS_SPLITTER << " ERR " << STATUS_SPLITTER << endl;
        switch (e.type())
        {
        case FILE_NOT_FOUND:
        case INCOMPLETE_TM:
            cout << e.what_verbose() << endl;
            break;
        case ILLEGAL_INPUT:
            cout << e.what_verbose() << endl;
            cout << "Input: " << input << endl;
            cout << setw(7 + e.position() + 1) << "^" << endl;
            break;
        default:
            cout << e.what_verbose() << endl;
            string line = "Line " + to_string(current_line_id) + ": ";
            cout << line << current_line << endl;
            cout << setw(line.length() + e.position() + 1) << "^" << endl;
            break;
        }
        cout << STATUS_SPLITTER << " END " << STATUS_SPLITTER << endl;
    }
    else
    {
        cerr << e.what() << endl;
    }
}