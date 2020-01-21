add_library(
    imgui
    # imgui
    imgui/imgui_draw.cpp
    imgui/imgui_internal.h
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp
    imgui/imgui.h
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h
    # imgui sfml
    imgui-sfml/imconfig-SFML.h
    imgui-sfml/imgui-SFML_export.h
    imgui-sfml/imgui-SFML.cpp
    imgui-sfml/imgui-SFML.h
)

target_compile_features(imgui PRIVATE cxx_std_17)

find_package(
    sfml
    CONFIG
    REQUIRED
)

target_link_libraries(imgui PUBLIC sfml::sfml)
target_compile_definitions(imgui PRIVATE IMGUI_USER_CONFIG="imconfig-SFML.h")
target_include_directories(imgui PUBLIC imgui imgui-sfml)
