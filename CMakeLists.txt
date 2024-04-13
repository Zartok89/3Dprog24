# CMakeList.txt : CMake project for 3Dprog24, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("FinalCompulsory2024")

# Add the directory containing GLFW's header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

# Add source to this project's executable.
add_executable (FinalCompulsory2024 "FinalCompulsory2024.cpp" "FinalCompulsory2024.cpp" "FinalCompulsory2024.h" "glad.c"  "Shader.h" "Shader.cpp" "stb_image.h" "Camera.h" "Camera.cpp")

target_link_libraries(FinalCompulsory2024 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw3.lib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FinalCompulsory2024 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
