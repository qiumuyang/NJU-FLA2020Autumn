#ifndef __COMMON_H__
#define __COMMON_H__

#include <assert.h>

#include <cstring>
#include <fstream>
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
    char buf[256];

public:
    TuringException(int type, int position, std::string what = std::string()) : m_type(type), m_what(what), m_position(position) {}
    int type() const { return m_type; }
    int position() const { return m_position; }
    const char* what() const throw()
    {
        strcpy((char *)buf, err_msg[m_type].c_str());
        return buf;
    }
    const char* what_verbose() const throw()
    {
        std::string temp = m_what;
        if (!temp.empty())
            temp = ": " + temp;
        std::string ret = err_msg[m_type] + temp;
        strcpy((char *)buf, ret.c_str());
        return buf;
    }
};

#endif