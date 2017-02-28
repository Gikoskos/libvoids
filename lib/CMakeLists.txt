
file(GLOB EduDS_SRC src//*.c)
file(GLOB EduDS_INC src//*.h)

add_library(EduDS SHARED ${EduDS_SRC} ${EduDS_INC})

target_compile_definitions(EduDS PRIVATE EXPORT_API_EduDS_DLL)

set_property(TARGET EduDS PROPERTY C_STANDARD 99)
