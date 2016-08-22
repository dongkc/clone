#include <iostream>


#include "Network/HttpClient.h"
#include "Network/Url.h"
#include "Network/HttpRequest.h"
#include "Network/HttpResponseHeader.h"

#include "Download/SingleFileDownloader.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        std::cout << "Format is: \r\n"
                  << "./Clone URL noOfThreads\r\n";
        exit(0);
    }
    std::string urlString(argv[1]);
    Clone::Network::Url url(urlString);
    int noOfThreads = std::stoi(argv[2]);
    Clone::Download::SingleFileDownloader singleFileDownloader(urlString, 
                                                               noOfThreads);
    singleFileDownloader.download();
    return 0;
}
