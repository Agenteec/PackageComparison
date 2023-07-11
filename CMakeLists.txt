# CMakeList.txt: проект CMake для PackageComparison; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


# Проверка операционной системы
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
#Поиск CXX
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
#Настройка для vcpkg
 set(CMAKE_TOOLCHAIN_FILE "$ENV{USERPROFILE}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
 endif()


project ("PackageComparison")

add_executable (PackageComparison "PackageComparison.cpp" "PackageComparison.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PackageComparison PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
