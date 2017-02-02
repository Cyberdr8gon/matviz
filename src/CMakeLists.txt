set(SOURCES main.cpp matrix.cpp )

 set(INCLUDES matrix.h ) 
 list(APPEND SOURCES ${INCLUDES})

add_executable( matviz ${SOURCES} )
