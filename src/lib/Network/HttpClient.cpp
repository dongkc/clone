#include "HttpClient.h"

#include "HttpResponseHeaderExtractor.h"

namespace viveketic { namespace Network
{
    int HttpClient::connectTo(const std::string& hostName_, int port_)
    {
        struct addrinfo hostSerivceType;
        struct addrinfo *hostInformationList;

        memset(&hostSerivceType, 0, sizeof(hostSerivceType));
        hostSerivceType.ai_family = AF_INET;
        hostSerivceType.ai_socktype = SOCK_STREAM;
    
        std::stringstream ssPort;
        ssPort  << port_;
        int status = getaddrinfo(hostName_.c_str(), 
                                 (ssPort.str()).c_str(),
                                 &hostSerivceType,
                                 &hostInformationList);

        if(status != 0)
        {
            std::cout << "Failed to get informtion about host."
                      << "\r\n"
                      << "Connection Failed."
                      << "\r\n";
            exit(0);
        }

        _socketDescriptor = socket(hostInformationList->ai_family, 
                                   hostInformationList->ai_socktype,
                                   hostInformationList->ai_protocol);
        if(_socketDescriptor < 0)
        {
            std::cout << "Failed creating socket." 
                      << "\r\n"
                      << "Connection Failed."
                      << "\r\n";
            exit(0);
        }

        int connectStatus = connect(_socketDescriptor,
                                    hostInformationList->ai_addr,
                                    hostInformationList->ai_addrlen);
        return connectStatus;
    }

    int HttpClient::sentMessage(const std::string& message_) const
    {
        int bytesSent = send(_socketDescriptor,
                             message_.c_str(),
                             message_.length(),
                             0);
        
        if(0 == bytesSent)
        {
            std::cout << "Message sent error."
                      << "\r\n";
            exit(0);
        }
        return bytesSent;
    }

    int HttpClient::
    getResponse(std::string& responseHeaderAsString_) const
    {
         char recieveBuffer[8192];
         int noOfBytesRead = 0;
         int totalNoOfBytesRead = 0;
         int locationOfNewLine = 0;
         int headerLength = 0;
         int recieveBufferRefillCount = 0;
         int indexOfDoubleNewLineInRepsonse = 0;
         std::stringstream ssResponseHeader;

         while(true)
         {
             std::fill_n(recieveBuffer, sizeof(recieveBuffer), 0);
             noOfBytesRead = recv(_socketDescriptor,
                                  recieveBuffer,
                                  sizeof(recieveBuffer),
                                  0);
             
             ++recieveBufferRefillCount;
             totalNoOfBytesRead += noOfBytesRead;
             
             if(noOfBytesRead)
             {
                 if(!indexOfDoubleNewLineInRepsonse)
                 {
                     indexOfDoubleNewLineInRepsonse = findIndexOfTwoNewLines(recieveBuffer);
/*
                     std::cout << "Response header Length:"
                               << indexOfDoubleNewLineInRepsonse
                               << "\r\n";
*/
                     std::string temp(recieveBuffer);
                     if(0 == indexOfDoubleNewLineInRepsonse)
                     {
                         responseHeaderAsString_ += temp;
                     }
                     else
                     {
                         std::string temp2(temp, 
                                           0,
                                           indexOfDoubleNewLineInRepsonse);

                         responseHeaderAsString_ += temp2;
                     }
                 }
             }
             else if(0 == noOfBytesRead|| noOfBytesRead == -1)
             {
                 break;
             }
         }
    }

    int HttpClient::getResponse(std::string& responseHeaderAsString_, 
                                std::fstream& fileHandle_)
     {
         char recieveBuffer[8192];
         int noOfBytesRead = 0;
         int indexofTwoNewLines = 0;
         bool twoNewLinesFound = false;

         while(true)
         {
             std::fill_n(recieveBuffer, sizeof(recieveBuffer), 0);
             noOfBytesRead = recv(_socketDescriptor,
                                  recieveBuffer,
                                  sizeof(recieveBuffer),
                                  0);
             
             if(noOfBytesRead == 0 || noOfBytesRead == 1)
             {
                 break;
             }

             if(!twoNewLinesFound)
             {
                 indexofTwoNewLines = findIndexOfTwoNewLines(recieveBuffer);
                 std::string temp(recieveBuffer);
                 if(indexofTwoNewLines == 0)
                 {
                     responseHeaderAsString_ += temp;
                 }
                 else
                 {
                     twoNewLinesFound = true;
                     std::string temp2(temp, 0, indexofTwoNewLines);
                     responseHeaderAsString_ += temp2;
                     std::string temp3(temp, indexofTwoNewLines+4, noOfBytesRead-indexofTwoNewLines-4);
                     fileHandle_.write(recieveBuffer+indexofTwoNewLines+4, 
                                       noOfBytesRead-indexofTwoNewLines-4);
                 }
             }
             else
             {
                 fileHandle_.write(recieveBuffer, noOfBytesRead);
             }
         }
    }

    int HttpClient::findIndexOfTwoNewLines(char buffer_[]) const     //\r\n\r\n
    {
        std::string temp(buffer_);
        int endOfHeader = temp.find("\r\n\r\n");
        if(endOfHeader == std::string::npos)
        {
            endOfHeader = temp.find("\n\n");
        }
        if(endOfHeader != std::string::npos)
        {
            return endOfHeader;
        }
        return 0;
    }

    void HttpClient::getResponse(HttpResponseHeader& httpResponseHeader_) const 
    {
        std::string httpResponseHeaderAsString;
        getResponse(httpResponseHeaderAsString);

        HttpResponseHeaderExtractor httpResponseHeaderExtractor;
        httpResponseHeaderExtractor.getElementsFromString(httpResponseHeaderAsString,
                                                          httpResponseHeader_);
    }
}}
