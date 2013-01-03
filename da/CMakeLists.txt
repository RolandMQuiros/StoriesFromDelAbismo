include_directories(include)
link_libraries(sfml-graphics sfml-audio sfml-window sfml-system)
add_definitions(-std=c++0x)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

set(da_sources      
    src/da/Attribute.cpp
    src/da/Behavior.cpp
    src/da/ContentManager.cpp
    src/da/DAException.cpp
    src/da/Depth.cpp
    src/da/Entity.cpp
    src/da/EntityBehavior.cpp
    src/da/EntityManager.cpp
    src/da/Game.cpp
    src/da/MathHelper.cpp
    src/da/RenderBehavior.cpp
    src/da/Spatial.cpp
    src/da/SpatialRenderer.cpp
    src/da/StringHelper.cpp
    src/da/XmlHelper.cpp
)

add_library(delabismo SHARED ${da_sources})
