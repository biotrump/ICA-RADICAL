# Define the files we need to compile
# Anything not in this list will not be compiled into the output library
set(SOURCES
	detrend.c
   radical.hpp
   radical.cpp
)

# add directory name to sources
set(DIR_SRCS)
foreach(file ${SOURCES})
  set(DIR_SRCS ${DIR_SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/${file})
endforeach()
# append sources (with directory name) to list of all MLPACK sources (used at the parent scope)
set(MLPACK_SRCS ${MLPACK_SRCS} ${DIR_SRCS} PARENT_SCOPE)

add_executable(radical
  radical_main.cpp
)
target_link_libraries(radical
  mlpack
)
install(TARGETS radical RUNTIME DESTINATION bin)
