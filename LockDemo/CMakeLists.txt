cmake_minimum_required(VERSION 2.8)

project(LockDemo)

set(SOURCE_PATH ${PROJECT_SOURCE_DIR}/)
aux_source_directory(${SOURCE_PATH} SRCS_LIST)

add_executable(${PROJECT_NAME} ${SRCS_LIST})
