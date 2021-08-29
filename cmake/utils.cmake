macro(add_subprojects _base_dir)
    # Find all CMakeLists.txt paths
    file(GLOB_RECURSE _cmake_files RELATIVE "${_base_dir}" CMakeLists.txt)
    # Collect all subdirectories containing CMakeLists.txt
    set(_dirs)
    foreach (file_path ${_cmake_files})
        get_filename_component(_dir_path ${file_path} PATH)
        list(APPEND _dirs ${_dir_path})
    endforeach ()

    unset(_cmake_files)
    unset(_dir_path)

    # Add all finded directories
    foreach (dir ${_dirs})
        add_subdirectory(${dir})
    endforeach ()
endmacro()

macro(configure_test_target _target_name _src_files _test_files)
    set(_src_part_lib ${_target_name}-src-part)

    # Create utility library to separate src files from test files
    add_library(${_src_part_lib} STATIC ${_src_files})

    # Rename learners main function to prevent overloading or name conflicts
    # It will rename symbols only in files from `_src_files` set
    string(SHA1 _hash _target_name)
    target_compile_definitions(${_src_part_lib} PRIVATE main=main${_hash})
    unset(_hash)

    # Create test executable target
    add_executable(${_target_name} ${_test_files})

    # Add files from `_src_files` set to target
    target_link_libraries(${_target_name} ${_src_part_lib})

    unset(_test_source)
endmacro()