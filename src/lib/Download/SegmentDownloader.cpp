#include <thread>
#include <sstream>

#include "Network/HttpClient.h"
#include "Network/HttpRequest.h"
#include "Network/HttpResponseHeader.h"
#include "SegmentDownloader.h"

namespace Clone { namespace Download
{
    SegmentDownloader::SegmentDownloader(const std::string& urlString_,
                                         unsigned long long int startByte_,
                                         unsigned long long int endByte_)
        :_url(urlString_),
         _startByte(startByte_),
         _endByte(endByte_)
    {
    }

    void SegmentDownloader::downloadImpl(std::fstream& fileHandle_)
    {
        Network::HttpClient httpClient;
        httpClient.connectTo(_url.getHostName(), 80);

        Network::HttpRequest httpRequest("GET",
                                         "HTTP/1.0",
                                         _url.toString());

        std::ostringstream osStream;
        osStream << "bytes=" 
                 << _startByte
                 << "-"
                 << _endByte;

        std::string rangeRequest = osStream.str();

        httpRequest.addRangeRequest(rangeRequest);
        std::cout << httpRequest.toString();
        httpClient.sentMessage(httpRequest.toString());
        std::string message;
        httpClient.getResponse(message, fileHandle_);
        httpClient.closeConnection();
    }
}}
