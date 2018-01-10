
#LIBVOIDS_SRC is all the .c modules
file(GLOB_RECURSE LIBVOIDS_SRC src//*.c external//SFMT//*.c)
#LIBVOIDS_INC is all the .h header files
file(GLOB_RECURSE LIBVOIDS_INC include//*.h)

include_directories(include external//xxHash)
include_directories(include external//SFMT)
include_directories(include include//voids)

#if we're building a windows .dll, we add the resource file
#with the DLL versioning information, to the LIBVOIDS_SRC modules
if(BUILD_SHARED_LIBS AND WIN32)
    list(APPEND LIBVOIDS_SRC src//libvoids_DLLversion.rc)
endif(BUILD_SHARED_LIBS AND WIN32)

add_library(voids ${LIBVOIDS_SRC} ${LIBVOIDS_INC})

#if we're building a dynamic library we want to export all symbols
if(BUILD_SHARED_LIBS)
    target_compile_definitions(voids PRIVATE EXPORT_API_VOIDS_DLL)
endif(BUILD_SHARED_LIBS)

target_compile_definitions(voids PRIVATE BUILD_VOIDS_LIB)

#set gcc specific flags
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    #maximum gcc warnings
    target_compile_options(voids PRIVATE -Wall -Wextra -pedantic)
    #add debugging flags for GCC if we're building the debug build
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_options(voids BEFORE PRIVATE -g)
    else(CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_options(voids BEFORE PRIVATE -O3)
    endif(CMAKE_BUILD_TYPE MATCHES Debug)
    #link to math library (for gcc on linux mostly)
    target_link_libraries(voids m)
#set cl.exe specific flags
elseif(MSVC)
    #set maximum warning levels for cl.exe
    target_compile_options(voids PRIVATE /W4)
    #no need to enable explicitly debugging symbols on the visual studio debug build
endif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

set_property(TARGET voids PROPERTY C_STANDARD 99)
