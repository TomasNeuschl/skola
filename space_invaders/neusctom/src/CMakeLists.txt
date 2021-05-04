cmake_minimum_required(VERSION 3.10)
project(Projekt)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-lncurses")

find_package(Curses REQUIRED)

include_directories($(CURSES_INCLUDE_DIR))

add_executable(Projekt main.cpp Game.cpp Game.h Enemy.h Laser.h Player.cpp Player.h Character.cpp Character.h Enemy.cpp Display.cpp Display.h Laser.cpp EnemyFlock.cpp EnemyFlock.h Bonus.cpp Bonus.h)

target_link_libraries(Projekt $(CURSES_LIBRARIES))

