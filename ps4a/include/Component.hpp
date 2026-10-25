// Copyright 2026 AniPlayer project authors.

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include "KeyFrame.hpp"

using Json = nlohmann::json;

namespace AP {

class Component : public sf::Drawable {
 public:
    ~Component() override = default;

    virtual void tween(sf::Time time);
    static std::unique_ptr<Component> fromJson(const Json& data);

 protected:
    explicit Component(const Json& data);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

    KeyFrame currFrame() const;
    sf::Color color() const;

 protected:
    std::string shape_;
    std::vector<KeyFrame> keyframes_;
    KeyFrame current_frame_;
    sf::Color color_;
};

class CircleComponent : public Component {
 public:
    explicit CircleComponent(const Json& data);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    float radius_;
    std::size_t sides_;
};

class RectangleComponent : public Component {
 public:
    explicit RectangleComponent(const Json& data);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    float width_;
    float height_;
};

class ImageComponent : public Component {
 public:
    explicit ImageComponent(const Json& data);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    std::string file_;
    std::shared_ptr<sf::Texture> texture_;
};

class TextComponent : public Component {
 public:
    explicit TextComponent(const Json& data);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    std::string text_;
    std::string font_file_;
    sf::Font font_;
    std::uint32_t character_size_;
};

class CompositeComponent : public Component {
 public:
    explicit CompositeComponent(const Json& data);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    std::vector<std::unique_ptr<Component>> children_;
};

}  // namespace AP
