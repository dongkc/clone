#ifndef CLONE_DOWNLOAD_SEGMENTMANAGER_H
#define CLONE_DOWNLOAD_SEGMENTMANAGER_H

#include <vector>
#include <memory>

#include "SegmentDownloader.h"
#include "File/FileManager.h"

namespace Clone { namespace Download 
{
    class SegmentManager
    {
    public:
        SegmentManager(const std::string& urlString_,
                       unsigned long long int fileSize_,
                       int noOfThreads_);
        
        unsigned long long int getTotalDownloadedSize();
        void createFilesToStoreSegments();
        void download();
        void mergeFilesAndCleanUp();
    protected:
        void  calculateSegmentDetails();

        unsigned long long int                         _fileSize;
        unsigned long long int                         _segmentSize;
        unsigned long long int                         _lastSegmentSize;
        unsigned int                                   _noOfSegments;
        std::string                                    _urlString;
        std::vector<std::shared_ptr<std::fstream> >    _fileHandles;
        std::vector<SegmentDownloader>                 _segmentDownloaderList;
    };



}}

#endif
