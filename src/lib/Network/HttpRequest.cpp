#include "HttpRequest.h"

#include <sstream>


namespace viveketic { namespace Network 
{
    HttpRequest::HttpRequest(const std::string& method_,
                             const std::string& version_,
                             const std::string& path_)
        :_method(method_),
         _version(version_),
         _path(path_)
    {}

    std::string HttpRequest::toString() const
    {
        std::stringstream ssHttpRequest;
        ssHttpRequest << _method << " " << _path << " " << _version
                      << "\r\n"
                      << "Connection: close\r\n";

        ssHttpRequest << _rangeRequest;
        ssHttpRequest << "\r\n";

        return ssHttpRequest.str();
    }

    void HttpRequest::addRangeRequest(const std::string& range_)
    {
        _rangeRequest = "Range:" + range_ + "\r\n";
    }
}}
