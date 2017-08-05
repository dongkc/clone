#include "SegmentManager.h"

#include <fstream>
#include <thread>
#include "File/FileManager.h"
#include "Network/Url.h"

namespace viveketic { namespace Download 
{
    SegmentManager::SegmentManager(const std::string& urlString_,
                                   unsigned long long int fileSize_,
                                   int noOfThread_)
        :_fileSize(fileSize_),
         _noOfSegments(noOfThread_),
         _urlString(urlString_)
    {
        calculateSegmentDetails();
    }
    
    void SegmentManager::calculateSegmentDetails()
    {
        /*
          Logic of last segment
          We assume here no of segments won't exceed more than 
          100 bytes so maximum difference between normal segment 
          and last segment will be 100 bytes.
          So it doesn't matter if last segment download 100 more bytes
        */
        std::cout << "Hwere";
        std::cout << "Filesize: " 
                  << _fileSize
                  << "\r\n"
                  << "No Of Segments: "
                  << _noOfSegments
                  << "\r\n";

        _segmentSize = _fileSize/_noOfSegments;
        _lastSegmentSize = _segmentSize + _fileSize%_noOfSegments;

        std::cout << "Segment Size: "
                  << _segmentSize
                  << "\r\n"
                  << "Last Segment Size: "
                  << _lastSegmentSize
                  << "\r\n";



    }

    void SegmentManager::createFilesToStoreSegments()
    {
        Network::Url url(_urlString);
        File::FileManager fileManager(url.getFileName());

        fileManager.createFiles(_noOfSegments, 
                                _fileHandles);
    }

    void SegmentManager::download()
    {
        int j = 0;
        int i = 0;
        for(i= 0; i < _fileSize-_lastSegmentSize; i+=_segmentSize)
        {

            std::cout << "Segment Size: " 
                      << _segmentSize
                      << "\r\n"
                      << "Value of i: " << i
                      << "\r\n"
                      << "Value of i+_segmentSize-1: "
                      << i+_segmentSize-1
                      << "\r\n";

            SegmentDownloader segmentDownloader(_urlString,
                                                i, 
                                                i+_segmentSize-1);

            _segmentDownloaderList.push_back(segmentDownloader);
            j++;
        }

            std::cout << "Segment Size: " 
                      << _segmentSize
                      << "\r\n"
                      << "Value of i: " << i
                      << "\r\n"
                      << "Value of i+_segmentSize-1: "
                      << i+_lastSegmentSize-1
                      << "\r\n";

            SegmentDownloader segmentDownloader(_urlString,
                                                i, 
                                                i+_lastSegmentSize-1);

            std::cout << "Value of j is :" << j
                      << "\r\n";
            _segmentDownloaderList.push_back(segmentDownloader);

            std::vector<std::thread> downloaderThreads;
            for(int k = 0; k <= j; k++)
            {
                downloaderThreads.push_back(
                    std::thread(&SegmentDownloader::downloadImpl,
                                _segmentDownloaderList[k],
                                std::ref(*_fileHandles[k])));
                std::cout << "Thread "
                          << k 
                          << " spawned."
                          << "\r\n";
            }

            for(int u = 0; u <= j; u++)
            {
                downloaderThreads[u].join();
            }
    }

    void SegmentManager::mergeFilesAndCleanUp()
    {
        Network::Url url(_urlString);
        File::FileManager fileManager(url.getFileName());
        fileManager.mergeFiles(_fileHandles);
        fileManager.closeFiles(_fileHandles);
        fileManager.renameFile(url.getFileName()+"000", url.getFileName());
        fileManager.deleteFiles(_fileHandles);
    }

    unsigned long long int SegmentManager::getTotalDownloadedSize()
    {
        unsigned long long int totalDownloadedSize = 0;
        for(std::vector<SegmentDownloader>::iterator iter = _segmentDownloaderList.begin();
            iter != _segmentDownloaderList.end();
            ++iter)
        {
            totalDownloadedSize += iter->getDownloadedSize();
        }
        return totalDownloadedSize;
    }
}}
