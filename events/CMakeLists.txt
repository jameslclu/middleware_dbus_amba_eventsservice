# set minimum cmake version
cmake_minimum_required(VERSION 3.10)

set(modulename fxnevents)

project(${modulename} 
  LANGUAGES C CXX
  DESCRIPTION "Events service"
  VERSION 0.0.1
)
set(CMAKE_CXX_STANDARD 11)

### search libary required
find_package(PkgConfig REQUIRED)
pkg_check_modules(GIO REQUIRED gio-2.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GIO_UNIX REQUIRED IMPORTED_TARGET gio-unix-2.0)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)
#################

list(APPEND common_src
../common/source/JsonUtility.cpp
../common/source/popen_noshell.cpp
../common/source/ShellUtility.cpp
)

list(APPEND common_inc
		../common/include
		)

# System
list(APPEND system_proxy_src
		../system/source/misc/MISCServiceProxy.cpp)

list(APPEND system_proxy_inc
		../system/include
		../system/include/common
		../system/include/misc
		../system/include/storage
		../system/include/battery
		../system/include/controller)

# AI
list(APPEND ai_proxy_src
		../ai/source/AIServiceProxy.cpp)

list(APPEND ai_proxy_inc
		../ai/include
		../ai/include/common)

# Recording
list(APPEND recording_proxy_src
		../recording/source/RecordingServiceProxy.cpp)

list(APPEND ai_proxy_inc
		../recording/include)


add_executable(${modulename}
	${common_src}
	${system_proxy_src}
	${ai_proxy_src}
	${recording_proxy_src}
	source/Main.cpp
	source/EventsService.cpp
	source/EventsRepository.cpp
	source/EventsServiceStub.cpp
	source/LocalDataSource.cpp)
	
target_include_directories(${modulename} 
	PUBLIC 
		${GIO_INCLUDE_DIRS} 
		${GLIB_INCLUDE_DIRS} 
		${GIO_UNIX_INCLUDE_DIRS} 
		${JSONCPP_INCLUDE_DIRS}
		${common_inc}
		${system_proxy_inc}
		${ai_proxy_inc}
		${recording_proxy_inc}
		source)

target_link_libraries(${modulename} 
	PUBLIC ${GIO_LIBRARIES} 
		${GLIB_LIBRARIES} 
		${GIO_UNIX_LIBRARIES} 
		${JSONCPP_LIBRARIES}
		-lpthread -lm)
