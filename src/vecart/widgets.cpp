#include "vecart/widgets.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <array>
#include <imgui.h>

auto vecart::color_edit4(std::string_view label, sf::Color& color) -> bool
{
    auto col = std::array<float, 4>{static_cast<float>(color.r) / 255.F,
                                    static_cast<float>(color.g) / 255.F,
                                    static_cast<float>(color.b) / 255.F,
                                    static_cast<float>(color.a) / 255.F};

    auto ret = ImGui::ColorEdit4(label.data(), col.data());

    if (ret) {
        color.r = static_cast<sf::Uint8>(col[0] * 255);
        color.g = static_cast<sf::Uint8>(col[1] * 255);
        color.b = static_cast<sf::Uint8>(col[2] * 255);
        color.a = static_cast<sf::Uint8>(col[3] * 255);
    }

    return ret;
}

auto vecart::vertex_edit(sf::Vertex& vertex) -> void
{
    const auto spacing = ImGui::GetStyle().ItemInnerSpacing.x;
    const auto width = ImGui::GetContentRegionAvailWidth();
    const auto half_width = width / 2.F;

    ImGui::SetNextItemWidth(half_width);
    ImGui::DragFloat("##X", &vertex.position.x, 1.F, 0.F, 0.F, "X:%.0f");

    ImGui::SameLine(0.F, spacing);

    ImGui::SetNextItemWidth(half_width - spacing);
    ImGui::DragFloat("##Y", &vertex.position.y, 1.F, 0.F, 0.F, "Y:%.0f");

    ImGui::SetNextItemWidth(width);
    color_edit4("##Color", vertex.color);
}

auto vecart::list_box(std::string_view label, sf::PrimitiveType& primitive_type)
    -> bool
{
    auto items = std::array<const char*, 7>{
        "Points",        "Lines",       "LineStrip", "Triangles",
        "TriangleStrip", "TriangleFan", "Quads"};

    const auto size = static_cast<int>(items.size());
    auto type = static_cast<int>(primitive_type);

    const auto ret = ImGui::ListBox(label.data(), &type, items.data(), size, 3);

    primitive_type = static_cast<sf::PrimitiveType>(type);

    return ret;
}
