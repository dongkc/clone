
#include "Network/Url.h"
#include "Network/HttpClient.h"

namespace Clone { namespace Download 
{
    class SingleFileDownloader
    {
    public:

        SingleFileDownloader(const std::string& urlString_,
                             int noOfThreads_);
        void download();
  
    protected:
        bool confirmServerHasRangeHeaderSupport();
        void downloadWithSingleThread() const;
        Network::HttpClient                _httpClient;
        Network::Url                       _url;
        unsigned long long int             _fileSize;
        int                                _noOfThreads;
    };


}}


