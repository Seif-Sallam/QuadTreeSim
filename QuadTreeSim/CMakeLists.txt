cmake_minimum_required(VERSION 3.16)

FILE(GLOB SOURCES ./src/*.cpp)

FILE(GLOB HEADERS ./headers/*.h)

add_executable(
    QuadTreeSim
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(
    QuadTreeSim
    PRIVATE
    ./headers/
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(QuadTreeSim PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()


set(OS_LIBRARIES
    opengl32
)

if (UNIX)
    set(OS_LIBRARIES
        GL
    )
endif()

target_link_libraries(QuadTreeSim
    PRIVATE
    ${OS_LIBRARIES}
    imgui
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

target_compile_definitions(QuadTreeSim
    PRIVATE
    RSC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/rsc/"
)