cmake_minimum_required(VERSION 3.8)
project(package_compare)
# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Поиск библиотеки jsoncpp
find_package(jsoncpp CONFIG REQUIRED)

# Поиск библиотеки CURL
find_package(CURL REQUIRED)

include_directories(${jsoncpp_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})
add_library(package_compare_shared SHARED "src/PackageCompare.cpp" "include/PackageCompare.h")
target_link_libraries(package_compare_shared PRIVATE jsoncpp_lib CURL::libcurl)
add_executable(pkgcompare_cli main.cpp)
target_link_libraries(pkgcompare_cli PRIVATE package_compare_shared)
# Установка библиотеки package_compare_shared
install(TARGETS package_compare_shared
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

# Установка исполняемого файла pkgcompare_cli
install(TARGETS pkgcompare_cli
        RUNTIME DESTINATION bin)
target_include_directories(package_compare_shared PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_include_directories(pkgcompare_cli PRIVATE "${PROJECT_SOURCE_DIR}/include")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  #set_property(TARGET package_compare PROPERTY CXX_STANDARD 20)
  set_property(TARGET package_compare_shared PROPERTY CXX_STANDARD 20)
  set_property(TARGET pkgcompare_cli PROPERTY CXX_STANDARD 20)
endif()