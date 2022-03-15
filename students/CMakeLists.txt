cmake_minimum_required(VERSION 3.15)
project(goose_game C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall")

add_executable(goose_game_p3_static
        src/headers/common.h
        src/headers/board.h
        src/sources/utils.c src/headers/utils.h
        src/sources/square.c src/headers/square.h
        src/sources/board_static.c src/headers/board_static.h
        src/sources/file_manager.c src/headers/file_manager.h
        src/sources/player.c src/headers/player.h
        src/sources/state.c src/headers/state.h
        src/sources/board_utils.c src/headers/board_utils.h
        src/sources/sequence.c src/headers/sequence.h
        src/sources/game.c src/headers/game.h
        src/sources/menu.c src/headers/menu.h
        src/sources/main.c)

add_custom_command(TARGET goose_game_p3_static POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources/
        $<TARGET_FILE_DIR:goose_game_p3_static>/resources/)


add_executable(goose_game_p3_dynamic
        src/headers/common.h
        src/headers/board.h
        src/sources/utils.c src/headers/utils.h
        src/sources/square.c src/headers/square.h
        src/sources/board_dynamic.c src/headers/board_dynamic.h
        src/sources/file_manager.c src/headers/file_manager.h
        src/sources/player.c src/headers/player.h
        src/sources/state.c src/headers/state.h
        src/sources/board_utils.c src/headers/board_utils.h
        src/sources/game.c src/headers/game.h
        src/sources/menu.c src/headers/menu.h
        src/sources/sequence.c src/headers/sequence.h
        src/sources/main.c)

add_custom_command(TARGET goose_game_p3_dynamic POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources/
        $<TARGET_FILE_DIR:goose_game_p3_dynamic>/resources/)
