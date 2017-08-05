#ifndef CLONE_NETWORK_HTTPREQUEST_H
#define CLONE_NETWORK_HTTPREQUEST_H

#include <string>

namespace viveketic { namespace Network 
{

class HttpRequest
{
public:


    HttpRequest();
    HttpRequest(const std::string& method_,
                const std::string& version_,
                const std::string& path_);
    
    void addRangeRequest(const std::string& rangeRequest_);
    std::string toString() const;
protected:
    std::string                      _method;
    std::string                      _version;
    std::string                      _path;
    std::string                      _rangeRequest;


};


}}

#endif
