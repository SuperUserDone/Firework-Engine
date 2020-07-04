set(GUNPOWDER_SOURCE 
    "src/main.cpp"
)

set(GUNPOWDER_LIBRARIES
    "FireworkEngine"
    tracy
)

include_directories("include")

add_executable(gunpowder ${GUNPOWDER_SOURCE})
target_link_libraries(gunpowder ${GUNPOWDER_LIBRARIES})