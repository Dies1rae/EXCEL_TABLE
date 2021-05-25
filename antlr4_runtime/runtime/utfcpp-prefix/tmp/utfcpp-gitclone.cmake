
if(NOT "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-stamp/utfcpp-gitinfo.txt" IS_NEWER_THAN "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-stamp/utfcpp-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-stamp/utfcpp-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E remove_directory "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/runtime/thirdparty/utfcpp"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/runtime/thirdparty/utfcpp'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout "git://github.com/nemtrif/utfcpp" "utfcpp"
    WORKING_DIRECTORY "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/runtime/thirdparty"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'git://github.com/nemtrif/utfcpp'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout v3.1.1 --
  WORKING_DIRECTORY "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/runtime/thirdparty/utfcpp"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v3.1.1'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/runtime/thirdparty/utfcpp"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/runtime/thirdparty/utfcpp'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-stamp/utfcpp-gitinfo.txt"
    "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-stamp/utfcpp-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-stamp/utfcpp-gitclone-lastrun.txt'")
endif()

