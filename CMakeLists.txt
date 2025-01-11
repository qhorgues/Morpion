cmake_minimum_required (VERSION 3.20)

project (Morpion LANGUAGES C VERSION 1.2.1)

#include(CTest)
#enable_testing()

include(${CMAKE_SOURCE_DIR}/cmake/option.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/CompilerWarnings.cmake)

set_choice (CMAKE_BUILD_TYPE "Debug;Release;MinSizeRel;RelWithDebInfo" "Debug" "Choose type of build")

configure_file(${CMAKE_SOURCE_DIR}/src/Divers/Version.h.in ${CMAKE_SOURCE_DIR}/src/Divers/Version.h)

set (SRCS
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${CMAKE_SOURCE_DIR}/src/Text/Text.c
    ${CMAKE_SOURCE_DIR}/src/Test/Test.c
    ${CMAKE_SOURCE_DIR}/src/SetingFile/SetingFile.c
    ${CMAKE_SOURCE_DIR}/src/Player/Player.c
    ${CMAKE_SOURCE_DIR}/src/Image/Image.c
    ${CMAKE_SOURCE_DIR}/src/IA/Score.c
    ${CMAKE_SOURCE_DIR}/src/IA/IA.c
    ${CMAKE_SOURCE_DIR}/src/Grille/Grille.c
    ${CMAKE_SOURCE_DIR}/src/Graphic/pop_up.c
    ${CMAKE_SOURCE_DIR}/src/Graphic/Menu.c
    ${CMAKE_SOURCE_DIR}/src/Graphic/Menu_Level.c
    ${CMAKE_SOURCE_DIR}/src/Graphic/In_Game.c
    ${CMAKE_SOURCE_DIR}/src/Graphic/End_Game.c
    ${CMAKE_SOURCE_DIR}/src/Graphic/DrawLineWinner.c
    ${CMAKE_SOURCE_DIR}/src/Game/Game.c
    ${CMAKE_SOURCE_DIR}/src/Divers/Version.c
    ${CMAKE_SOURCE_DIR}/src/Divers/Color.c
    ${CMAKE_SOURCE_DIR}/src/Button/Button.c
    ${CMAKE_SOURCE_DIR}/src/bool/bool.c
)

set (HEADERS
    ${CMAKE_SOURCE_DIR}/src/constante.h
    ${CMAKE_SOURCE_DIR}/src/Text/Text.h
    ${CMAKE_SOURCE_DIR}/src/Test/Test.h
    ${CMAKE_SOURCE_DIR}/src/SetingFile/SetingFile.h
    ${CMAKE_SOURCE_DIR}/src/Player/Player.h
    ${CMAKE_SOURCE_DIR}/src/Image/Image.h
    ${CMAKE_SOURCE_DIR}/src/IA/IA.h
    ${CMAKE_SOURCE_DIR}/src/Grille/Grille.h
    ${CMAKE_SOURCE_DIR}/src/Graphic/Graphic.h
    ${CMAKE_SOURCE_DIR}/src/Game/Game.h
    ${CMAKE_SOURCE_DIR}/src/Divers/Divers.h
    ${CMAKE_SOURCE_DIR}/src/Divers/Version.h
    ${CMAKE_SOURCE_DIR}/src/Button/Button.h
    ${CMAKE_SOURCE_DIR}/src/bool/bool.h
)

set (ASSETS
    ${CMAKE_SOURCE_DIR}/assets/calibrib.ttf
    ${CMAKE_SOURCE_DIR}/assets/imprisha.ttf
    ${CMAKE_SOURCE_DIR}/assets/Bad.png
    ${CMAKE_SOURCE_DIR}/assets/Croix.png
    ${CMAKE_SOURCE_DIR}/assets/Rond.png
    ${CMAKE_SOURCE_DIR}/assets/Victory.png
    ${CMAKE_SOURCE_DIR}/assets/XO.png
)

set_sanitizer()

option(BUILD_DOC "Build documentation" ON)
if (BUILD_DOC)
    add_subdirectory(${CMAKE_SOURCE_DIR}/docs)
endif()

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)


if (WIN32)
    set(ICONE Morpion.rc)

    # Win32 SDL2 dll

    # SDL2pp only for C++
    # set_option(SDL2PP_DLL_DIR "SDL2PP_BINARY_DIR NOT FOUND" PATH "Path to SDL2pp.dll directory")
    # configure_file(${SDL2PP_DLL_DIR}/libSDL2pp.dll libSDL2pp.dll COPYONLY)
    # install(FILES ${SDL2PP_DLL_DIR}/libSDL2pp.dll DESTINATION .)

    # SDL2
    set_option(SDL2_DLL_DIR "SDL2_BINARY_DIR NOT FOUND" PATH "Path to SDL2.dll directory")
    configure_file(${SDL2_DLL_DIR}/SDL2.dll SDL2.dll COPYONLY)
    install(FILES ${SDL2_DLL_DIR}/SDL2.dll DESTINATION .)

    # SDL2 ttf
    set_option(SDL2_TTF_DLL_DIR "SDL2_TTF_BINARY_DIR NOT FOUND" PATH "Path to SDL2_ttf.dll directory")
    configure_file(${SDL2_TTF_DLL_DIR}/SDL2_ttf.dll SDL2_ttf.dll COPYONLY)
    install(FILES ${SDL2_TTF_DLL_DIR}/SDL2_ttf.dll DESTINATION .)

    set_option(SDL2_IMAGE_DLL_DIR "SDL2_IMAGE_BINARY_DIR NOT FOUND" PATH "Path to SDL2_image.dll directory")
    configure_file(${SDL2_IMAGE_DLL_DIR}/SDL2_image.dll SDL2_image.dll COPYONLY)
    install(FILES ${SDL2_IMAGE_DLL_DIR}/SDL2_image.dll DESTINATION .)

    # set_option(SDL2_MIXER_DLL_DIR "SDL2_MIXER_BINARY_DIR NOT FOUND" PATH "Path to SDL2_mixer.dll directory")
    # configure_file(${SDL2_MIXER_DLL_DIR}/SDL2_mixer.dll SDL2_mixer.dll COPYONLY)
    # install(FILES ${SDL2_MIXER_DLL_DIR}/SDL2_mixer.dll DESTINATION .)

    foreach(df ${ASSETS})
        configure_file(${CMAKE_SOURCE_DIR}/${df} ${CMAKE_BINARY_DIR}/${df} COPYONLY)
    endforeach()


else ()
    # linux .desktop file
    set (MORPION_DESKTOP_DIR     "/usr/share/applications/")
    set (MORPION_PIXMAPS_DIR     "/usr/share/icons/")

    configure_file(Morpion.desktop.in Morpion.desktop)

    install (FILES ${CMAKE_BINARY_DIR}/Morpion.desktop DESTINATION ${MORPION_DESKTOP_DIR})
    install(FILES ${CMAKE_SOURCE_DIR}/Morpion.svg DESTINATION ${MORPION_PIXMAPS_DIR})
endif()

add_executable ( ${PROJECT_NAME} ${SRCS} ${HEADERS} ${ICONE})
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2main SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image)
set_target_warnings(${PROJECT_NAME})

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME} DESTINATION .)
install(DIRECTORY assets/ DESTINATION assets)

foreach(df ${ASSETS})
    file(COPY ${df} DESTINATION ${CMAKE_BINARY_DIR}/assets)
endforeach()

install(TARGETS ${PROJECT_NAME} RUNTIME)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_NAME ${PROJECT_NAME})
set (CPACK_PACKAGE_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}")
set (CPACK_PACKAGE_VENDOR "Quentin Horgues")
set (CPACK_SOURCE_GENERATOR "TGZ")
set (CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set (CPACK_SOURCE_IGNORE_FILES ${CPACK_IGNORE_FILES})
set (CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})

# Debian
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "quentin.horgues@outlook.fr")
set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE "x86")
set (CPACK-DEBIAN-PACKAGE-DESCRIPTION "Le jeu du Morpion")
set (CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 libsdl2 libsdl2-ttf libsdl2-image")

# RPM
set (CPACK-RPM-PACKAGE-ARCHITECTURE "x86")
set (CPACK_RPM_PACKAGE_REQUIRES "SDL2 SDL2_ttf SDL2_image")
# NSIS
set (CPACK_NSIS_MODIFY_PATH OFF)
set (CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/Morpion.ico")
set (CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/2048_uninstaler.ico")
set (CPACK_CREATE_DESKTOP_LINK ON)
set (CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
    CreateShortCut \\\"$DESKTOP\\\\${PROJECT_NAME}.lnk\\\" \\\"$INSTDIR\\\\bin\\\\${PROJECT_NAME}.exe\\\"
")

set (CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
    Delete \\\"$DESKTOP\\\\${PROJECT_NAME}.lnk\\\"
")

include(CPack)
