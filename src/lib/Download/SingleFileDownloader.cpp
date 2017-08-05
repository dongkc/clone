
#include "SingleFileDownloader.h"

#include "Network/HttpResponseHeader.h"
#include "Network/HttpRequest.h"

#include "SegmentManager.h"
#include "File/FileManager.h"

namespace viveketic { namespace Download 
{
    SingleFileDownloader::
    SingleFileDownloader(const std::string& urlString_,
                         int noOfThreads_)
        :_url(urlString_),
         _noOfThreads(noOfThreads_)
    {
    }

    void SingleFileDownloader::download()
    {
        if(_noOfThreads == 1)
        {
            downloadWithSingleThread();
        }
        else if(confirmServerHasRangeHeaderSupport())
        {
            std::cout << "Confirmed that server has multi-part download support"
                      << "\r\n";

            SegmentManager segmentManager(_url.toString(),
                                          _fileSize,
                                          _noOfThreads);

            segmentManager.createFilesToStoreSegments();
            segmentManager.download();
            segmentManager.mergeFilesAndCleanUp();
        }
        else
        {
            std::cout << "Seems server has no muli-part download support."
                      << "\r\n"
                      << "Going with single part download"
                      << "\r\n";
            downloadWithSingleThread();
        }
    }

    bool SingleFileDownloader::confirmServerHasRangeHeaderSupport() 
    {

        // 1. First check server has range header support
        // 2. Second confirm by sending open ended range request 
        // and get response as 206 and Content-Range header element

        int connectionStatus = _httpClient.connectTo(_url.getHostName(), 80);
        if(connectionStatus >= 0)
        {
            std::cout << "Connected to server "
                      << _url.getHostName()
                      << " at port "
                      << 80
                      << "\r\n";
                          
        }
        Network::HttpRequest httpRequest("HEAD",
                                         "HTTP/1.0",
                                         _url.toString());


        httpRequest.addRangeRequest(" ");
        int noOfBytesSend = 
            _httpClient.sentMessage(httpRequest.toString());
        if(noOfBytesSend > 0)
        {
            std::cout << "Send "
                      << noOfBytesSend
                      << " bytes to server."
                      << "\r\n";
        }
      
        Network::HttpResponseHeader httpResponseHeader;
        _httpClient.getResponse(httpResponseHeader);
        _httpClient.closeConnection();
        _fileSize = httpResponseHeader._contentLength;

        std::string httpResponseHeaderAsString;
        httpResponseHeader.toString(httpResponseHeaderAsString);
        std::cout << httpResponseHeaderAsString;        
        
        if(httpResponseHeader._acceptRanges &&
           "bytes" == *httpResponseHeader._acceptRanges)
        {
            std::cout << "here";
            _httpClient.connectTo(_url.getHostName(), 80);
            httpRequest.addRangeRequest(" bytes=0-");
            _httpClient.sentMessage(httpRequest.toString());
            _httpClient.getResponse(httpResponseHeader);
            _httpClient.closeConnection();

            std::cout << httpResponseHeader._statusCode;
            if((206 == httpResponseHeader._statusCode) && 
               (httpResponseHeader._contentRange->_totalNumberOfBytes > 0))
            {
                _fileSize = httpResponseHeader._contentRange->_totalNumberOfBytes;
                return true;
            }
        }
        return false;
    }

    void SingleFileDownloader::downloadWithSingleThread() const
    {
        Network::HttpClient httpClient;
        httpClient.connectTo(_url.getHostName(), 80);

        Network::HttpRequest httpRequest("GET",
                                         "HTTP/1.0",
                                         _url.toString());

        httpClient.sentMessage(httpRequest.toString());
        std::string message;
        //File::FileManager fileManager(_url.getFileName());
        //std::shared_ptr<std::fstream> fileHandlePtr;
        std::fstream fileHandle;
        fileHandle.open(_url.getFileName(),
                        std::fstream::out|
                        std::ios::binary);
        //fileManager.createFile(fileHandle);
        httpClient.getResponse(message, fileHandle);
        //fileHandlePtr->close();
        std::cout << message;
        fileHandle.close();
        httpClient.closeConnection();
    }

}}
