cmake_minimum_required(VERSION 3.10)
project(MiniDesign)

# Indique le dossier où se trouvent tes headers
include_directories(include)

# Récupère automatiquement tous les fichiers .cpp du dossier src/
file(GLOB SOURCES "src/*.cpp")

# Definition de l'executable à générer
add_executable(MiniDesign ${SOURCES})

# Optionnel : Définit le dossier de sortie pour l'exe
set_target_properties(MiniDesign PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)
