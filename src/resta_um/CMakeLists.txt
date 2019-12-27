find_package(Qt5Core)
find_package(Qt5Concurrent)
find_package(Qt5Qml)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5QuickControls2)

add_executable(resta_um
        model/model.cpp
        main.cpp
        qt/qmodel.cpp
    )

set_target_properties(resta_um
    PROPERTIES
        AUTOMOC YES
    )

target_link_libraries(resta_um
        immer
        zug
        lager
        Qt5::Core
        Qt5::Concurrent
        Qt5::Gui
        Qt5::Widgets
        Qt5::Qml
        Qt5::QuickControls2
    )

target_include_directories(resta_um
    PRIVATE
        ${Boost_INCLUDE_DIRS}
    )

target_compile_definitions(resta_um
    PRIVATE
        LAGER_RESTA_UM_QML_DIR="${CMAKE_SOURCE_DIR}/src/resta_um/qt/qml"
    )