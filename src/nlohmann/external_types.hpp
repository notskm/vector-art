#ifndef VECART_EXTERNAL_TYPES_HPP
#define VECART_EXTERNAL_TYPES_HPP

#include <nlohmann/json.hpp>

namespace sf {
    class Color;
    class Vertex;
    class VertexArray;

    template <typename T>
    class Vector2;
} // namespace sf

namespace nlohmann {
    template <>
    struct adl_serializer<sf::Color> {
        static void to_json(json& j, const sf::Color& c);
        static void from_json(const json& j, sf::Color& c);
    };

    template <typename T>
    struct adl_serializer<sf::Vector2<T>> {
        static void to_json(json& j, const sf::Vector2<T>& vec);
        static void from_json(const json& j, sf::Vector2<T>& vec);
    };

    template <>
    struct adl_serializer<sf::Vertex> {
        static void to_json(json& j, const sf::Vertex& v);
        static void from_json(const json& j, sf::Vertex& v);
    };

    template <>
    struct adl_serializer<sf::VertexArray> {
        static void to_json(json& j, const sf::VertexArray& v);
        static void from_json(const json& j, sf::VertexArray& v);
    };

} // namespace nlohmann

template <typename T>
void nlohmann::adl_serializer<sf::Vector2<T>>::to_json(
    json& j, const sf::Vector2<T>& vec)
{
    j = json{{"x", vec.x}, {"y", vec.y}};
}

template <typename T>
void nlohmann::adl_serializer<sf::Vector2<T>>::from_json(
    const json& j, sf::Vector2<T>& vec)
{
    vec.x = j.at("x").get<T>();
    vec.y = j.at("y").get<T>();
}

#endif // VECART_EXTERNAL_TYPES_HPP
