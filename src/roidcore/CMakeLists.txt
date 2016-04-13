project(roidcore)

find_package(Boost COMPONENTS system program_options chrono date_time REQUIRED)

add_executable(roidcore main.cpp)
target_link_libraries(roidcore
	${Boost_LIBRARIES}
	${msgpack_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT})

list(APPEND roidcore_INCLUDE_DIRS ${msgpack_INCLUDE_DIRS})

include_directories(SYSTEM ${roidcore_INCLUDE_DIRS})
set(roidcore_INCLUDE_DIRS ${roidcore_INCLUDE_DIRS} PARENT_SCOPE)
