add_subdirectory(lib)

set(Clone_SRCS Clone.cpp)

add_executable(Clone ${Clone_SRCS} )

target_link_libraries(Clone
Download
Network
File
Utils
)
