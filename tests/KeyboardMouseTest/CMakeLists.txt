set(DEPENDS
    ${GAME_SRC}/KeyboardMouseInput.cpp
)
    
add_executable(KeyboardMouseTest ${DEPENDS} KeyboardMouseTest.cpp)
add_test(KeyboardMouseTest KeyboardMouseTest)
