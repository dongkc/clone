#include "HttpResponseHeader.h"


#include <string>
#include <sstream>
#include <iostream>

namespace Clone { namespace Network
{
    void HttpResponseHeader::toString(std::string& httpResponseHeaderAsString_) const
    {
        std::stringstream ss;

        ss << "Status-Code: "
           << _statusCode  
           << "\r\n"
           << "Content-Length: "
           << _contentLength 
           << "\r\n"
           << "Server: "
           << _server
           << "\r\n"
           << "Content-Type: "
           << _contentType 
           << "\r\n";

        if(_acceptRanges)
        {
            ss << "Accept-Ranges: "
               << *_acceptRanges
               << "\r\n";
        }
        if(_contentRange)
        {
            ss << "Content-Range: ("
               << _contentRange->_startByte
               << " to "
               << _contentRange->_endByte
               << ")/"
               << _contentRange->_totalNumberOfBytes
               << "\r\n";
        }
        httpResponseHeaderAsString_ = ss.str();
    }
}}
