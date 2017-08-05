#include "NameGenerator.h"

#include <sstream>
#include <iomanip>      // std::setfill, std::setw


namespace viveketic { namespace Utils
{

    NameGenerator::NameGenerator()
    :_counter(0)
    {
    }

    std::string NameGenerator::
    createNameAppendedWithThreeDigitNumber(const std::string& name_)
    {
        std::ostringstream oss;
        oss << name_
            << std::setfill('0')
            << std::setw(3)
            << _counter;

        _counter++;

        return oss.str();
    }

}}
