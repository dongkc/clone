
set(Network_SRCS
HttpClient.cpp
Url.cpp
HttpRequest.cpp
HttpResponseHeader.cpp
HttpResponseHeaderExtractor.cpp
)


add_library(Network STATIC ${Network_SRCS})
target_link_libraries(Network)
