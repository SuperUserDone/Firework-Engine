set(GUNPOWDER_SOURCE 
    "src/main.cpp"
    "src/WindowMain.cpp"
)

set(GUNPOWDER_LIBRARIES
    FireworkEngine
    tracy
)

pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})

include_directories("src")

add_executable(gunpowder ${GUNPOWDER_SOURCE})
target_link_libraries(gunpowder ${GUNPOWDER_LIBRARIES} ${GTKMM_LIBRARIES})