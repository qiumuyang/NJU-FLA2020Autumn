#include "component.h"

int Tape::getHead() const
{
    return head;
}

string Tape::getTape() const
{
    return tape;
}

char Tape::read()
{
    return charAt(head);
}

char Tape::charAt(int target)
{
    int end = front + tape.length();
    int pos = target - front;
    if (front <= target && target < end)  // target within tape_string
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
    string idx = to_string(tape_index);
    int width = to_string(tape_cnt - 1).length() + INDEX.length() + 1;
    stringstream ss_index;
    stringstream ss_tape;
    stringstream ss_head;
    ss_index << setiosflags(ios::left);
    ss_index << setw(width) << INDEX + idx << ":";
    ss_tape << setiosflags(ios::left);
    ss_tape << setw(width) << TAPE + idx << ":";
    ss_head << setiosflags(ios::left);
    ss_head << setw(width) << HEAD + idx << ":";
    int st, ed;
    int end = front + tape.length();
    if (front <= head && head < end)
    {
        st = front;
        ed = end;
    }
    else if (head < front)
    {
        st = head;
        ed = end;
    }
    else
    {
        st = front;
        ed = head + 1;
    }
    for (int i = st; i < ed; i++)
    {
        string i_str = to_string(abs(i));
        string head_pivot;
        if (i == head)
            head_pivot += "^";
        width = i_str.length();
        ss_index << ' ' << setw(width) << i_str;
        ss_tape << ' ' << setw(width) << charAt(i);
        ss_head << ' ' << setw(width) << head_pivot;
    }
    string index_ln = ss_index.str();
    string tape_ln = ss_tape.str();
    string head_ln = ss_head.str();
    return index_ln + "\n" + tape_ln + "\n" + head_ln + "\n";
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