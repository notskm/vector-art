#ifndef VECART_WIDGETS_HPP
#define VECART_WIDGETS_HPP

#include <SFML/Graphics/PrimitiveType.hpp>
#include <string_view>

namespace sf {
    class Color;
    class Vertex;
} // namespace sf

namespace vecart {
    auto color_edit4(std::string_view label, sf::Color& color) -> bool;
    void vertex_edit(sf::Vertex& vertex);
    auto list_box(std::string_view label, sf::PrimitiveType& primitive_type)
        -> bool;
} // namespace vecart

#endif // VECART_WIDGETS_HPP
