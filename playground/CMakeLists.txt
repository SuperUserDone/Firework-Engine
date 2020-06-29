set(PLAYGROUND_SOURCE 
    "src/main.cpp"
)

set(PLAYGROUND_LIBRARIES
    "FireworkEngine"
    tracy
)

add_executable(Playground ${PLAYGROUND_SOURCE})

target_link_libraries(Playground ${PLAYGROUND_LIBRARIES})