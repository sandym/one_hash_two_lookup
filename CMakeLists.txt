cmake_minimum_required(VERSION 4.3)
project(one_hash_two_lookup)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

find_package(Threads REQUIRED)

add_subdirectory(3rdParty/abseil-cpp)

add_executable(one_hash_two_lookup)
target_sources(one_hash_two_lookup PRIVATE
	main.cpp
)

target_link_libraries(one_hash_two_lookup PRIVATE
	Threads::Threads
	absl::flat_hash_map
)
