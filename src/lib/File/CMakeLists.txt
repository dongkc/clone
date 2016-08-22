set(File_SRCS
FileManager.cpp
)


add_library(File STATIC ${File_SRCS})
target_link_libraries(File)
