project(ClasesPosix)
cmake_minimum_required(VERSION 2.6)



include_directories( ${CMAKE_CURRENT_BINARY_DIR})

# Sources set
SET ( SOURCES  ${SOURCES}  ClasesPosix.cpp  prueba.cpp Identificador.cpp )
# Headers set
SET ( HEADERS  ${HEADERS} ClasesPosix.h Identificador.h )


set(CMAKE_CXX_STANDARD 20)
add_definitions(-O3)

find_package(OpenMP REQUIRED)
# Specify construction and link process
ADD_EXECUTABLE( ClasesPosix ${SOURCES}  )
TARGET_LINK_LIBRARIES( ClasesPosix ${LIBS} ${STATIC_LIBS} ${SPECIFIC_LIBS} ${OpenMP_CXX_FLAGS} pthread)
INSTALL(TARGETS ClasesPosix  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE )

