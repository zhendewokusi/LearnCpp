cmake_minimum_required(VERSION 3.10)
project(mylib VERSION 1.0)

# Create the library target
add_library(mylib SHARED mylib_base.cpp)

# Set the library version
set_target_properties(mylib PROPERTIES VERSION ${PROJECT_VERSION})

# Install the library and header files
install(TARGETS mylib DESTINATION lib)
install(FILES mylib_base.h DESTINATION include)
