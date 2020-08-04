set(GUNPOWDER_SOURCE 
    "src/main.cpp"
    "src/WindowMain.cpp"
)

set(GUNPOWDER_LIBRARIES
    FireworkEngine
    tracy
)

include_directories("src")

add_executable(gunpowder ${GUNPOWDER_SOURCE})
target_link_libraries(gunpowder ${GUNPOWDER_LIBRARIES})