#include <imgui-SFML.h>
#include <imgui.h>
#include <imgui_internal.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <array>
#include <exception>
#include <fstream>
#include <iostream>
#include <string_view>

#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "nlohmann/external_types.hpp"

#include "vecart/widgets.hpp"

auto undo_add_vertex(sf::VertexArray& arr) -> void
{
    auto vertex_count = arr.getVertexCount();
    if (vertex_count > 0) {
        arr.resize(vertex_count - 1);
    }
}

auto save_to_file(
    const sf::VertexArray& vertices, const std::string_view filename) -> void
{
    auto file = std::ofstream{filename.data()};

    auto verts = nlohmann::json{vertices};
    file << verts.dump(2) << '\n';
}

// NOLINTNEXTLINE(bugprone-exception-escape)
auto main() -> int
{
    auto window = sf::RenderWindow{
        sf::VideoMode{1024, 720},
        "Vector Art",
    };
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    auto camera =
        sf::View{{0.F, 0.F}, static_cast<sf::Vector2f>(window.getSize()) / 2.F};

    auto vertex_arr = sf::VertexArray{};

    auto filename = std::string{"model.json"};
    filename.resize(1024);

    auto delta_clock = sf::Clock{};
    while (window.isOpen()) {
        auto event = sf::Event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            auto imgui_io = ImGui::GetIO();

            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (imgui_io.WantCaptureKeyboard) {
                    break;
                }
                if (event.key.code == sf::Keyboard::Z && event.key.control) {
                    undo_add_vertex(vertex_arr);
                }
                if (event.key.code == sf::Keyboard::S && event.key.control) {
                    save_to_file(vertex_arr, filename);
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (imgui_io.WantCaptureMouse) {
                    break;
                }
                if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    auto [button, x, y] = event.mouseButton;
                    const auto mouse_coords = sf::Vector2i{x, y};
                    auto world_coords = window.mapPixelToCoords(mouse_coords);
                    world_coords.x = std::floor(world_coords.x);
                    world_coords.y = std::floor(world_coords.y);
                    vertex_arr.append(world_coords);
                }
                break;
            default:
                break;
            }
        }

        ImGui::SFML::Update(window, delta_clock.restart());

        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
                save_to_file(vertex_arr, filename);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) {
                undo_add_vertex(vertex_arr);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();

        ImGui::Begin("Vector Art Controls");

        ImGui::InputText("Filename", filename.data(), filename.size());

        if (auto p_type = vertex_arr.getPrimitiveType();
            vecart::list_box("PrimitiveType", p_type)) {
            vertex_arr.setPrimitiveType(p_type);
        }

        for (auto i = std::size_t{0}; i < vertex_arr.getVertexCount(); ++i) {
            const auto label = fmt::format("Vertex {}", i);

            const auto open = ImGui::CollapsingHeader(
                label.c_str(), ImGuiTreeNodeFlags_DefaultOpen);

            if (open) {
                ImGui::PushID(&vertex_arr[i]);
                vecart::vertex_edit(vertex_arr[i]);
                ImGui::PopID();
            }
        }

        ImGui::End();

        window.clear();
        window.setView(camera);

        auto center = sf::VertexArray(sf::PrimitiveType::Points);
        center.append(sf::Vertex{camera.getCenter(), sf::Color::Red});
        window.draw(center);

        window.draw(vertex_arr);

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
}
