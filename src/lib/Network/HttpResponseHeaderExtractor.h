
#include <string>

#include "HttpResponseHeader.h"

namespace viveketic { namespace Network 
{

    class HttpResponseHeaderExtractor
    {
    public:

    void getElementsFromString(const std::string& httpResponseHeaderAsString_,
                               Network::HttpResponseHeader& httpResponseHeader_);
    private:


    };
}}
