cmake_minimum_required(VERSION 3.8)
project(package_compare)

# Проверка операционной системы
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  # Поиск CXX
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_PREFIX_PATH "/путь/к/установленному/каталогу/CURL" ${CMAKE_PREFIX_PATH})

endif()


# Проверка операционной системы
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
# Путь к vcpkg
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};$ENV{VCPKG_ROOT}/installed/x64-windows")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};$ENV{VCPKG_ROOT}/installed/x64-windows/share")
set(CMAKE_TOOLCHAIN_FILE "C:/Users/Agenteec/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
set(CMAKE_PREFIX_PATH "C:/Users/Agenteec/vcpkg/installed/x64-windows" ${CMAKE_PREFIX_PATH})
endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()



# Поиск библиотеки jsoncpp
find_package(jsoncpp CONFIG REQUIRED)
# Поиск библиотеки CURL
find_package(CURL CONFIG REQUIRED)

# Создание статической и динамической библиотеки package_compare
add_library(package_compare STATIC src/PackageCompare.cpp)
add_library(package_compare_shared SHARED src/PackageCompare.cpp)

target_link_libraries(package_compare PRIVATE JsonCpp::JsonCpp CURL::libcurl)
target_link_libraries(package_compare_shared PRIVATE JsonCpp::JsonCpp CURL::libcurl)

# Создание CLI утилиты для библиотеки
add_executable(pkgcompare_cli main.cpp)
target_link_libraries(pkgcompare_cli package_compare)

# Указание пути к заголовочным файлам
target_include_directories(package_compare PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_include_directories(package_compare_shared PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_include_directories(pkgcompare_cli PRIVATE "${PROJECT_SOURCE_DIR}/include")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET package_compare PROPERTY CXX_STANDARD 20)
  set_property(TARGET package_compare_shared PROPERTY CXX_STANDARD 20)
endif()