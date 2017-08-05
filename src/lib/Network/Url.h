#ifndef CLONE_NETWORK_URL_H
#define CLONE_NETWORK_URL_H

#include <string>
#include <algorithm>
#include <iostream>

namespace viveketic { namespace Network 
{
    class Url
    {
    public:

        Url(const std::string& url_);
        const std::string& getProtocol() const { return _protocol;};
        const std::string& getHostName() const { return _hostName;}
        const std::string& getPath() const {return _path;}
        const std::string& getFileName() const { return _fileName;}
        std::string toString() const;
    protected:
        int extractUrlElements(const std::string& url_);
        std::string         _protocol;
        std::string         _hostName;
        std::string         _path;
        std::string         _fileName;
    };

}}


#endif
