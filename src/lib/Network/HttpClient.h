#ifndef CLONE_MESSAGECLIENT_H
#define CLONE_MESSAGECLIENT_H

#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <string>
#include <sstream>
#include <iostream>
#include <map>

#include "HttpResponseHeader.h"

namespace viveketic { namespace Network
{

    class HttpClient
    {
        
    public:
        int connectTo(const std::string& hostName_, int port_);
        int sentMessage(const std::string& message_) const;

        void getResponse(HttpResponseHeader& httpResponseHeader_) const;
        int getResponse(std::string& responseHeaderAsString_, 
                        std::fstream& fileHandle_);

        int closeConnection() const { close(_socketDescriptor);}
    private:

        int getResponse(std::string& responseHeaderAsString_) const;
        int findIndexOfTwoNewLines(char buffer_[]) const;

        int                                 _socketDescriptor;        
    };
}}


#endif
