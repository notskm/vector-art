#include "nlohmann/external_types.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>

void nlohmann::adl_serializer<sf::Color>::to_json(json& j, const sf::Color& c)
{
    j = json{{"r", c.r}, {"g", c.g}, {"b", c.b}, {"a", c.a}};
}

void nlohmann::adl_serializer<sf::Color>::from_json(const json& j, sf::Color& c)
{
    c.r = j.at("r").get<sf::Uint8>();
    c.g = j.at("g").get<sf::Uint8>();
    c.b = j.at("b").get<sf::Uint8>();
    c.a = j.at("a").get<sf::Uint8>();
}

void nlohmann::adl_serializer<sf::Vertex>::to_json(json& j, const sf::Vertex& v)
{
    j = json{{"position", v.position},
             {"color", v.color},
             {"texCoords", v.texCoords}};
}

void nlohmann::adl_serializer<sf::Vertex>::from_json(
    const json& j, sf::Vertex& v)
{
    v.position = j.at("position").get<sf::Vector2f>();
    v.color = j.at("color").get<sf::Color>();
    v.texCoords = j.at("texCoords").get<sf::Vector2f>();
}

void nlohmann::adl_serializer<sf::VertexArray>::to_json(
    json& j, const sf::VertexArray& v)
{
    auto j2 = json{};
    j2["primitiveType"] = v.getPrimitiveType();
    for (auto i = std::size_t{0}; i < v.getVertexCount(); ++i) {
        j2["vertices"][i] = v[i];
    }
    j = j2;
}

void nlohmann::adl_serializer<sf::VertexArray>::from_json(
    const json& j, sf::VertexArray& v)
{
    v.setPrimitiveType(j.at("primitiveType").get<sf::PrimitiveType>());

    auto vertices = j.at("vertices");
    for (auto i = std::size_t{0}; i < vertices.size(); ++i) {
        v.append(vertices.at(i).get<sf::Vertex>());
    }
}
