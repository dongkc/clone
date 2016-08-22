set(Utils_SRCS
NameGenerator.cpp
)


add_library(Utils STATIC ${Utils_SRCS})
target_link_libraries(Utils)
