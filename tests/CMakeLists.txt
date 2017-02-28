#function that makes a new executable target for test
function(new_EduDS_test target_name)
    add_executable(${target_name} EXCLUDE_FROM_ALL ${target_name}.c)
    target_include_directories(${target_name} PUBLIC "${PROJECT_SOURCE_DIR}/lib/src")
    target_link_libraries(${target_name} EduDS)

    if(NOT BUILD_SHARED_LIBS)
        target_compile_definitions(${target_name} PRIVATE EXPORT_API_EduDS_STATIC)
    endif(NOT BUILD_SHARED_LIBS)

    set_property(TARGET ${target_name} PROPERTY C_STANDARD 99)
    add_test(${target_name} ${target_name})
endfunction(new_EduDS_test)


#list that holds all filenames with their extensions (eg test1.c test2.c test3.c)
file(GLOB EduDS_TEST_SRC *.c)

#list that holds all filenames without their extensions (eg test1 test2 test3)
set(EduDS_TESTS "")


#strip filenames from their extensions
foreach(curr ${EduDS_TEST_SRC})
    get_filename_component(tmp_var ${curr} NAME_WE)
    list(APPEND EduDS_TESTS ${tmp_var})
endforeach(curr ${EduDS_TEST_SRC})

#create a new executable target for each test
foreach(curr ${EduDS_TESTS})
    new_EduDS_test(${curr})
endforeach(curr ${EduDS_TESTS})
