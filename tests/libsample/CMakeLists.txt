set(EXECUTABLE_NAME unit_MathUtils)
add_executable( ${EXECUTABLE_NAME}
    unit_MathUtils.cpp
)

create_test(${EXECUTABLE_NAME})

target_link_libraries(${EXECUTABLE_NAME}
  PUBLIC
    Custom::libsample
)
