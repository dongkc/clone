#ifndef CLONE_DOWNLOAD_SEGMENTDOWNLOADER_H
#define CLONE_DOWNLOAD_SEGMENTDOWNLOADER_H


#include <fstream>

#include "Network/Url.h"

namespace Clone { namespace Download
{
    class SegmentDownloader
    {
    public:
        SegmentDownloader(const std::string& urlString_,
                          unsigned long long int startByte_,
                          unsigned long long int endByte_);

        unsigned long long int getDownloadedSize(){ return (_startByte - _endByte);}
        void downloadImpl(std::fstream& fileHandle_);
    protected:


        Network::Url                                     _url;
        unsigned long long int                           _startByte;
        unsigned long long int                           _endByte;
        unsigned long long int                           _currentByte;//
    };

}}


#endif
