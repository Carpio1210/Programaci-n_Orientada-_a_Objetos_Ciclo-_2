cmake_minimum_required(VERSION 3.16)
project(Reto_1_Biblioteca LANGUAGES CXX)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Ejecutable principal ---
add_executable(Reto_1_Biblioteca
        Reto_1_Biblioteca.cpp
)

# --- nlohmann::json ---
# Opción A: usas el header único en ./include/nlohmann/json.hpp
#   (crea la carpeta "include/nlohmann" y coloca "json.hpp" ahí)
target_include_directories(Reto_1_Biblioteca PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

# Opción B: si tienes el paquete instalado (vcpkg/conan/system), se enlaza solo.
# (no pasa nada si no está; A seguirá funcionando)
find_package(nlohmann_json QUIET CONFIG)
if(nlohmann_json_FOUND)
    target_link_libraries(Reto_1_Biblioteca PRIVATE nlohmann_json::nlohmann_json)
endif()

# --- Copiar el archivo de datos JSON junto al ejecutable tras compilar ---
add_custom_command(TARGET Reto_1_Biblioteca POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/Reto_1.json
        $<TARGET_FILE_DIR:Reto_1_Biblioteca>/Reto_1.json
)

# --- (Opcional) que todos los binarios caigan en una carpeta bin/ ---
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- (Opcional) en Visual Studio, fija el working dir al del ejecutable ---
if(MSVC)
    set_property(TARGET Reto_1_Biblioteca
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            "$<TARGET_FILE_DIR:Reto_1_Biblioteca>")
endif()

include(FetchContent)
FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

target_link_libraries(TU_TARGET_PRIVADO PRIVATE nlohmann_json::nlohmann_json)