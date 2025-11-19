add_library(SimplexLib
    Simplex.h
    Simplex.cpp
    FractionalNumbers.h
    FractionalNumbers.cpp
)

target_include_directories(SimplexLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})