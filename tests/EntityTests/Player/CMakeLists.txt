set(DEPENDS
    ${GAME_SRC}/CardinalDirection.cpp
    ${GAME_SRC}/ColliderBehavior.cpp
    ${GAME_SRC}/Poses.cpp
    ${GAME_SRC}/Pose.cpp
    ${GAME_SRC}/Sprite.cpp
    ${GAME_SRC}/SpriteSpatial.cpp
    ${GAME_SRC}/Walker.cpp
    ${GAME_SRC}/PlayerUpdater.cpp
    ${GAME_SRC}/PoseUpdater.cpp
    ${GAME_SRC}/TransformHistorian.cpp
    ${GAME_SRC}/VelocitiesUpdater.cpp
)
    
add_executable(PlayerTest ${DEPENDS} PlayerTest.cpp)
target_link_libraries(PlayerTest EntityFixture)

add_test(PlayerTest PlayerTest)
