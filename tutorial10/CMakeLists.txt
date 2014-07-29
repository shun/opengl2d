CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(tutorial10)

FIND_PACKAGE(OpenGL REQUIRED)
FIND_LIBRARY(OpenGL_LIBRARY OpenGL )

#----------------------------------------------------------------                                          
INCLUDE_DIRECTORIES(
)

LINK_DIRECTORIES(
  /usr/local/lib
  )

LINK_LIBRARIES(
  )

#----------------------------------------------------------------                                          
SET(OUTPUTNAME ${PROJECT_NAME}.out)

SET(SRC_FILES
	src/main.cpp
)

SET(HDR_FILES
)


ADD_EXECUTABLE(
  ${OUTPUTNAME}
  ${SRC_FILES}
  )

target_link_libraries(
    ${OUTPUTNAME}
	glfw
	${OPENGL_LIBRARIES}
)

#----------------------------------------------------------------                                          

#----------------------------------------------------------------                                          
INSTALL(

    FILES
        ${PROJECT_BINARY_DIR}/${OUTPUTNAME}
    DESTINATION
        ${CMAKE_SOURCE_DIR}/bin
    PERMISSIONS
        OWNER_READ
        OWNER_EXECUTE
        GROUP_READ
        GROUP_EXECUTE
        WORLD_READ
        WORLD_EXECUTE
        )

