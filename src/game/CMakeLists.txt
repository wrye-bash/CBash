
add_subdirectory(Oblivion)
add_subdirectory(Skyrim)
add_subdirectory(FalloutNewVegas)


add_library(libgame STATIC game.cpp)
target_link_libraries(libgame libgame_oblivion libgame_skyrim libgame_falloutnv)
