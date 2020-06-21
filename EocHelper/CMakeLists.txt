cmake_minimum_required(VERSION 3.8)

if(NOT DEFINED EOC_HOME)
	set(EOC_HOME $ENV{EOC_HOME})
endif()
include(${EOC_HOME}/EocBuildHelper.cmake)

project(EocHelper)
add_library(EocHelper INTERFACE)
target_link_eoc_lib(EocHelper system EocSystem)
target_include_directories(EocHelper INTERFACE ${EocHelper_SOURCE_DIR}/src)