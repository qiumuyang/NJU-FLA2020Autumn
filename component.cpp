#include "component.h"

char Tape::read()
{
    int end = front + tape.length();
    int pos = head - front;
    if (front <= head && head < end)  // head within tape_string
    {
        return tape[pos];
    }
    return SPACE;
}

void Tape::write(char symbol, char direc)
{
    int end = front + tape.length();
    int pos = head - front;
    int relative_pos = 0;
    int padding = 0;
    // judge relative position
    if (head < front)
    {
        relative_pos = TO_LEFT;
    }
    else if (head >= end)
    {
        relative_pos = TO_RIGHT;
    }
    else
    {
        relative_pos = BETWEEN;
    }
    // write tape
    if (symbol == SPACE)
    {
        switch (relative_pos)
        {
        case BETWEEN:
            tape[pos] = symbol;
            // remove spaces
            if (pos == 0)
            {
                tape = string(tape, tape.find(SPACE));
            }
            else if (pos == tape.length() - 1)
            {
                tape = string(tape, 0, tape.find(SPACE));
            }
            break;
        default:  // write SPACE out of tape_string
            // do nothing
            break;
        }
    }
    else  // normal symbol
    {
        switch (relative_pos)
        {
        case BETWEEN:
            tape[pos] = symbol;
            break;
        case TO_LEFT:
            padding = front - head - 1;
            tape = string(1, symbol) + string(padding, SPACE) + tape;
            front = head;
            break;
        case TO_RIGHT:
            padding = head - end;
            tape = tape + string(padding, SPACE) + string(1, symbol);
            break;
        default:
            break;
        }
    }
    // move head
    switch (direc)
    {
    case LEFT:
        head--;
        break;
    case RIGHT:
        head++;
        break;
    case STAY:
        break;
    default:
        assert(0);
    }
}

string Tape::verbose(int tape_index, int tape_cnt)
{
    int idx = tape_index;
}

bool TKey::operator<(const TKey &t) const
{
    if (state != t.state)
        return state < t.state;
    return symbol < t.symbol;
}

bool TKey::operator>(const TKey &t) const
{
    if (state != t.state)
        return state > t.state;
    return symbol > t.symbol;
}