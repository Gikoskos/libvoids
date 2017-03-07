
#EduDS_SRC is all the .c modules
file(GLOB_RECURSE EduDS_SRC src//*.c)
#EduDS_INC is all the .h header files
file(GLOB_RECURSE EduDS_INC src//*.h)


#if we're building a windows .dll, we add the resource file
#with the DLL versioning information, to the EduDS_SRC modules
if(BUILD_SHARED_LIBS AND WIN32)
    list(APPEND EduDS_SRC src//EduDS_DLLversion.rc)
endif(BUILD_SHARED_LIBS AND WIN32)

add_library(EduDS ${EduDS_SRC} ${EduDS_INC})

#if we're building a dynamic library we want to export all symbols
if(BUILD_SHARED_LIBS)
    target_compile_definitions(EduDS PRIVATE EXPORT_API_EduDS_DLL)
endif(BUILD_SHARED_LIBS)

#set gcc specific flags
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    #maximum gcc warnings
    target_compile_options(EduDS PRIVATE -Wall -Wextra -pedantic)
    #add debugging flags for GCC if we're building the debug build
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_options(EduDS BEFORE PRIVATE -gdwarf)
    endif(CMAKE_BUILD_TYPE MATCHES Debug)
#set cl.exe specific flags
elseif(MSVC)
    #set maximum warning levels for cl.exe
    target_compile_options(EduDS PRIVATE /W4)
    #no need to enable explicitly debugging symbols on the visual studio debug build
endif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)





set_property(TARGET EduDS PROPERTY C_STANDARD 99)
