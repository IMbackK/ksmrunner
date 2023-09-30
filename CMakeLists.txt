cmake_minimum_required(VERSION 3.5)

project(ksmexec C)

set(SRC_FILES main.c)
set(LIBS)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME} ${LIBS})

set(CMAKE_INSTALL_PREFIX /usr)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
