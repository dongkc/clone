#include "HttpResponseHeaderExtractor.h"

#include <sstream>
#include <iostream>
#include <string>

namespace Clone { namespace Network 
{
    void HttpResponseHeaderExtractor::
    getElementsFromString(const std::string& httpResponseHeaderAsString_,
                          Network::HttpResponseHeader& httpResponseHeader_)
    {
        std::pair<std::string, std::string> typeValuePair;
        std::string httpHeaderLine;
        std::string temp;
        std::stringstream ssHTTPResponse;
        std::stringstream ssHTTPResponseLine;

        ssHTTPResponse << httpResponseHeaderAsString_;
        
        while(std::getline(ssHTTPResponse, httpHeaderLine))
        {
            ssHTTPResponseLine.str(httpHeaderLine);
            
            if(httpHeaderLine.substr(0, 4) == "HTTP")
            {
                
                ssHTTPResponseLine >> httpResponseHeader_._version
                                   >> httpResponseHeader_._statusCode
                                   >> temp;
 
                /*
                  std::cout << "Status code:"
                          << httpResponseHeader_._statusCode 
                          << "\r\n";
                */
            }
            else if("Content-Length" == httpHeaderLine.substr(0, 14))
            {
                ssHTTPResponseLine >> temp
                                   >> httpResponseHeader_._contentLength;
                /*
                std::cout << "Content-Length:"
                          << httpResponseHeader_._contentLength
                          << "\r\n";

                */
            }
            else if("Accept-Ranges" == httpHeaderLine.substr(0, 13))
            {
                std::string temp1;
                ssHTTPResponseLine >> temp
                                   >> temp1;

                httpResponseHeader_._acceptRanges = temp1;
/*
                std::cout << "Accept-ranges:"
                          << *httpResponseHeader_._acceptRanges
                          << "\r\n";
*/

            }
            else if("Content-Range" == httpHeaderLine.substr(0, 13))
            {
                std::string contentRangeString;
                ssHTTPResponseLine >> temp
                                   >> temp
                                   >> contentRangeString;

                int positionOfHyphen = contentRangeString.find("-");
                
                unsigned long long int startByte = 0;
                
                
                startByte = std::stoi(contentRangeString.substr(0, positionOfHyphen));
                httpResponseHeader_._contentRange = Network::ContentRange();
                httpResponseHeader_._contentRange->_startByte = startByte;

                int positionOfForwardSlash = contentRangeString.find("/");
                httpResponseHeader_._contentRange->_endByte = 
                    std::stoi(contentRangeString.substr(positionOfHyphen+1, 
                                                        positionOfForwardSlash - positionOfHyphen -1),
                              nullptr);
/*
                std::cout << "Endbyte"
                          <<  httpResponseHeader_._contentRange->_endByte
                          << "\r\n";

                std::cout << contentRangeString.substr(positionOfForwardSlash)
                          << "\r\n";
*/
                httpResponseHeader_._contentRange->_totalNumberOfBytes = 
                    std::stoi(contentRangeString.substr(positionOfForwardSlash+1),
                              nullptr);
/*                                    
                std::cout << httpResponseHeader_._contentRange->_startByte;
*/
            }
        }
    }

}}
