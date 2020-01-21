add_executable(
    ${PROJECT_NAME}
    main.cpp
    nlohmann/external_types.hpp
    nlohmann/external_types.cpp
    vecart/widgets.hpp
    vecart/widgets.cpp
)

find_package(
    nlohmann_json
    CONFIG
    REQUIRED
)

find_package(
    fmt
    CONFIG
    REQUIRED
)

target_link_libraries(
    ${PROJECT_NAME}
    imgui
    nlohmann_json::nlohmann_json
    fmt::fmt
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

include(warnings)
target_enable_warnings(${PROJECT_NAME})
