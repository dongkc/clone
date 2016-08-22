#include "Url.h"


namespace Clone { namespace Network
{
    Url::Url(const std::string& url_)
    {
        extractUrlElements(url_);


    }

    int Url::extractUrlElements(const std::string& url_)
    {
        int locationOfFirstColon = -1;
        locationOfFirstColon = url_.find(":");
        if(locationOfFirstColon)
        {
            _protocol = url_.substr(0, locationOfFirstColon);
        }

        int locationOfFirstForwardSlash = -1;
        int locationOfThirdForwardSlash = -1;
        locationOfFirstForwardSlash = url_.find("/");
        locationOfThirdForwardSlash = url_.find("/",
                                                locationOfFirstForwardSlash+2);

        if(locationOfFirstForwardSlash &&
           locationOfThirdForwardSlash)
        {
            _hostName = url_.substr(locationOfFirstForwardSlash+2,
                                    locationOfThirdForwardSlash-locationOfFirstForwardSlash-2);
        }

        if(locationOfThirdForwardSlash)
        {
            _path = url_.substr(locationOfThirdForwardSlash);
        }

        std::string reversedUrl = url_;
        std::reverse(reversedUrl.begin(), reversedUrl.end());
        int locationOfLastForwardSlash = reversedUrl.find("/");
        if(locationOfLastForwardSlash)
        {
            _fileName = reversedUrl.substr(0, 
                                           locationOfLastForwardSlash);
            std::reverse(_fileName.begin(), _fileName.end());
        }
        else if(0 == locationOfLastForwardSlash)
        {
            int locationOfSecondLastForwardSlash = reversedUrl.find("/", locationOfLastForwardSlash+1);

            _fileName = reversedUrl.substr(1, 
                                           locationOfSecondLastForwardSlash-1);
            std::reverse(_fileName.begin(), _fileName.end());           
        }
    }
    
    std::string Url::toString() const
    {
        std::string url  = _protocol + "://" +
                           _hostName +
                           _path;
        return url;
    }
}}
