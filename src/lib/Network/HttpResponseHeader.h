#ifndef CLONE_NETWORK_HTTPRESPONSEHEADER_H
#define CLONE_NETWORK_HTTPRESPONSEHEADER_H

#include <string>
#include <boost/optional.hpp>

namespace viveketic { namespace Network
{


    struct ContentRange
    {
/*
        ContentRange()
           :_startByte(0),
            _endByte(0),
            _totalNumberOfBytes(0)
        {
        }

*/
        unsigned long long int             _startByte;
        unsigned long long int             _endByte;
        unsigned long long int             _totalNumberOfBytes;
    };

    struct HttpResponseHeader
    {
        HttpResponseHeader(){}
        
        void toString(std::string& httpResponseHeaderAsString_) const;

        int                                     _statusCode;
        unsigned long long int                  _contentLength;
        std::string                             _server;
        std::string                             _contentType;
        std::string                             _version;
        boost::optional<std::string>            _acceptRanges;
        boost::optional<ContentRange>           _contentRange;
    };
    
}}


#endif


//http://stackoverflow.com/questions/8293687/sample-http-range-request-session
