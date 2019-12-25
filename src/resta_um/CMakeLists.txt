add_executable(resta_um
        model/model.cpp
        main.cpp
    )

target_link_libraries(resta_um
        immer
        zug
        lager
    )

target_include_directories(resta_um
    PRIVATE
        ${Boost_INCLUDE_DIRS}
    )