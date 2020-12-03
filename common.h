#ifndef __COMMON_H__
#define __COMMON_H__

#include <assert.h>

#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "const.h"
#include "util.h"

class TuringException : public exception
{
private:
    int m_type;
    int m_position;
    std::string m_what;

public:
    TuringException(int type, int position, std::string what = std::string()) : m_type(type), m_what(what), m_position(position) {}
    const char* what() const throw()
    {
        return err_msg[m_type].c_str();
    }
    const char* what_verbose() const throw()
    {
        std::string temp = m_what;
        if (!temp.empty())
            temp = ": " + temp;
        return (err_msg[m_type] + temp).c_str();
    }
};

#endif