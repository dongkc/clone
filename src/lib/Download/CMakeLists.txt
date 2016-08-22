
set(Download_SRCS
SingleFileDownloader.cpp
SegmentDownloader.cpp
SegmentManager.cpp
)


add_library(Download STATIC ${Download_SRCS})
target_link_libraries(Download)
