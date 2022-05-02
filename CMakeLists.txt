CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

PROJECT(Coding VERSION 1.0)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)
IF(CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_CXX_FLAGS "-Wall -Werror ${CMAKE_CXX_FLAGS}")
ENDIF()
SET(CMAKE_BUILD_TYPE "RelWithDebInfo")
MESSAGE("[+] The build type is ${CMAKE_BUILD_TYPE}.")

INCLUDE_DIRECTORIES(include)

# Find all the main.cpp and store them in to a list `executable`
# make each of them a executable file
FILE(GLOB_RECURSE executable RELATIVE "${CMAKE_SOURCE_DIR}" "*main.cpp")
FOREACH(file_path IN LISTS executable)
	# pick out the main.cpp in the third library
	STRING(FIND ${file_path} "third/" is_third)
	IF(${is_third} EQUAL -1)
		# build executable file
		GET_FILENAME_COMPONENT(dir_name ${file_path} DIRECTORY)
		STRING(REPLACE "src/" "" exe_name ${dir_name})
		MESSAGE("[+] Find `${file_path}`, and `${exe_name}` is configured")
		ADD_EXECUTABLE(${exe_name} ${dir_name}/main.cpp)
	ENDIF()
ENDFOREACH()

