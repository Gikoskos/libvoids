
#EduDS_SRC is all the .c modules
file(GLOB EduDS_SRC src//*.c)
#EduDS_INC is all the .h header files
file(GLOB EduDS_INC src//*.h)

#if we're building a windows .dll, we add the resource file
#with the DLL versioning information, to the EduDS_SRC modules
if(BUILD_SHARED_LIBS AND WIN32)
    list(APPEND EduDS_SRC src//EduDS_DLLversion.rc)
endif(BUILD_SHARED_LIBS AND WIN32)

add_library(EduDS ${EduDS_SRC} ${EduDS_INC})

if(BUILD_SHARED_LIBS)
    target_compile_definitions(EduDS PRIVATE EXPORT_API_EduDS_DLL)
else(BUILD_SHARED_LIBS)
    target_compile_definitions(EduDS PRIVATE EXPORT_API_EduDS_STATIC)
endif(BUILD_SHARED_LIBS)




set_property(TARGET EduDS PROPERTY C_STANDARD 99)
