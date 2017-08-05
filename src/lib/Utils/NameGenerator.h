#ifndef CLONE_UTILS_NAMEGENERATOR_H
#define CLONE_UTILS_NAMEGENERATOR_H


#include <string>

namespace viveketic { namespace Utils
{

    class NameGenerator
    {
    public:
        NameGenerator();
        std::string createNameAppendedWithThreeDigitNumber(const std::string& name_);

    protected:
        int                                  _counter;
    };

}}


#endif
