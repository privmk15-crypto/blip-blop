cmake_minimum_required(VERSION 3.15)

project(blipblop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_library(SDL2_LIBRARIES SDL2)
find_library(SDL2MIXER_LIBRARIES SDL2_mixer)
find_path(SDL2_INCLUDE_DIRS SDL2/SDL.h)

aux_source_directory(. SRC)
aux_source_directory(menus MENUS_SRC)
# Note: an "Engine" source subdirectory was referenced here previously, but it
# does not exist anywhere in this repository (verified during Etap 1 audit).
# It has been removed as dead configuration. If an Engine/ split is introduced
# in a later stage, re-add aux_source_directory(Engine ENGINE_SRC) then.

if(WIN32)
    # WIN32 here tells add_executable to link as a GUI (WinMain) subsystem
    # app instead of a console app. This flag was previously (incorrectly)
    # placed in the else() branch below, which meant a Windows build linked
    # as a console app and showed a console window behind the game. Fixed as
    # part of the Etap 1 audit; no gameplay or architecture change.
    #
    # Consequence of a real WIN32 subsystem target: SDL2's SDL_main.h
    # `#define`s main to SDL_main on Windows (pulled in transitively via
    # SDL.h), so the actual WinMain entry point must come from the SDL2main
    # static library, or the link fails with an unresolved WinMain symbol.
    # vcpkg's sdl2 port always installs SDL2main alongside SDL2, so find and
    # link it explicitly rather than relying on it being pulled in
    # implicitly. SDL2main must be linked before SDL2 in the library list.
    find_library(SDL2MAIN_LIBRARIES SDL2main)
    if(NOT SDL2MAIN_LIBRARIES)
        message(FATAL_ERROR
            "SDL2main library not found. It is required to provide the "
            "WinMain entry point for this WIN32-subsystem target. If SDL2 "
            "was installed via vcpkg, this should be installed alongside "
            "SDL2 automatically; check the vcpkg toolchain/triplet setup.")
    endif()

    add_executable(blipblop WIN32 ${SRC} ${MENUS_SRC})
    target_link_libraries(blipblop PUBLIC ${SDL2MAIN_LIBRARIES} ${SDL2_LIBRARIES})

    target_link_libraries(blipblop PUBLIC ${SDL2MIXER_LIBRARIES})

    target_include_directories(blipblop SYSTEM PUBLIC ${SDL2_INCLUDE_DIRS})

    set(CMAKE_INSTALL_UCRT_LIBRARIES true)
    include(InstallRequiredSystemLibraries)
    install(DIRECTORY
        "${CMAKE_CURRENT_BINARY_DIR}/\${CMAKE_INSTALL_CONFIG_NAME}/"
        DESTINATION .
        FILES_MATCHING PATTERN "*.dll")
else()
    add_executable(blipblop ${SRC} ${MENUS_SRC})
    target_link_libraries(blipblop SDL2)
    target_link_libraries(blipblop SDL2_mixer)
endif()

install(DIRECTORY ./data DESTINATION .)
install(TARGETS blipblop RUNTIME DESTINATION .)

set(CPACK_PACKAGE_NAME "BlipnBlop")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Blip & Blop revamped")
set(CPACK_PACKAGE_VENDOR "Loaded Studios")
set(CPACK_DEBIAN_PACKAGE_NAME "blipnblop")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libSDL2, libSD2-mixer")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Blip & Blop revamped")
set(CPACK_PACKAGE_EXECUTABLES "blipblop" "BlipnBlop")

if(WIN32)
    set(CPACK_NSIS_DISPLAY_NAME "Blip & Blop")
    set(CPACK_NSIS_EXECUTABLES_DIRECTORY ".")
endif()

include(CPack)

