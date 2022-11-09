if(DEFINED __ADD_UNINSTALL_TARGET_INCLUDED)
  return()
endif()
set(__ADD_UNINSTALL_TARGET_INCLUDED TRUE)


set(cmake_uninstall_file ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# The install manifest contains the list of files to delete.
set(install_manifest ${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt)

file(WRITE ${cmake_uninstall_file} [[
if(NOT EXISTS "]] ${install_manifest} [[")
    message(FATAL_ERROR "Cannot find \"]] ${install_manifest} [[\"")
    return()
endif()

file(READ "]] ${install_manifest} [[" files)
string(STRIP "${files}" files)
string(REGEX REPLACE "\n" ";" files "${files}")
list(REVERSE files)
foreach(file ${files})
    message(STATUS "Uninstalling: $ENV{DESTDIR}${file}")
    if(EXISTS "$ENV{DESTDIR}${file}")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E remove "$ENV{DESTDIR}${file}"
            OUTPUT_VARIABLE rm_out
            RESULT_VARIABLE rm_retval)
        if(NOT "${rm_retval}" EQUAL 0)
            message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
        endif()
    else()
        message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
    endif()
endforeach(file)
]])

if("${CMAKE_GENERATOR}" MATCHES "^(Visual Studio|Xcode)")
    set(_uninstall "UNINSTALL")
else()
    set(_uninstall "uninstall")
endif()
add_custom_target(${_uninstall} COMMAND "${CMAKE_COMMAND}" -P "${cmake_uninstall_file}")
set_property(TARGET ${_uninstall} PROPERTY FOLDER "CMakePredefinedTargets")
