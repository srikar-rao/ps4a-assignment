// Copyright 2026 AniPlayer project authors.

#include "Component.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace AP {
namespace {

std::string trim(const std::string& value) {
    const auto start = value.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    const auto end = value.find_last_not_of(" \t\r\n");
    return value.substr(start, end - start + 1);
}

sf::Color parseColor(const std::string& color_text) {
    const std::string value = trim(color_text);
    if (value.empty()) {
        return sf::Color::White;
    }

    std::string hex = value;
    if (hex.size() == 6 || hex.size() == 8) {
        if (hex.size() == 6) {
            hex = hex + "FF";
        }
        if (hex.size() == 8) {
            const auto r = std::stoul(hex.substr(0, 2), nullptr, 16);
            const auto g = std::stoul(hex.substr(2, 2), nullptr, 16);
            const auto b = std::stoul(hex.substr(4, 2), nullptr, 16);
            const auto a = std::stoul(hex.substr(6, 2), nullptr, 16);
            return sf::Color(
                static_cast<unsigned char>(r),
                static_cast<unsigned char>(g),
                static_cast<unsigned char>(b),
                static_cast<unsigned char>(a));
        }
    }

    throw std::invalid_argument("Invalid color value: " + value);
}

std::string resolvePath(const std::string& original) {
    if (original.empty()) {
        return "";
    }

    const std::vector<std::filesystem::path> candidates = {
        std::filesystem::path(original),
        std::filesystem::current_path() / original,
        std::filesystem::path("../") / original,
        std::filesystem::path("../AniPlayer-starter/") / original,
        std::filesystem::path("../images/") / original,
        std::filesystem::path("../../") / original,
        std::filesystem::path("../../../") / original,
        std::filesystem::path("../../AniPlayer-starter/") / original,
    };

    for (const auto& candidate : candidates) {
        if (std::filesystem::exists(candidate)) {
            return candidate.string();
        }
    }

    return original;
}

}  // namespace

Component::Component(const Json& data)
    : shape_(data.value("shape", "")),
      keyframes_(),
      current_frame_(),
      color_(sf::Color::White) {
    if (data.contains("color")) {
        color_ = parseColor(data["color"].get<std::string>());
    } else {
        color_ = parseColor("FFFFFFFF");
    }

    if (data.contains("keyframes") && data["keyframes"].is_array()) {
        for (const auto& frame_json : data["keyframes"]) {
            keyframes_.emplace_back(frame_json);
        }
    }

    if (!keyframes_.empty()) {
        current_frame_ = keyframes_.front();
    }
}

KeyFrame Component::currFrame() const {
    return current_frame_;
}

sf::Color Component::color() const {
    return color_;
}

void Component::tween(sf::Time time) {
    if (keyframes_.empty()) {
        return;
    }

    if (keyframes_.size() == 1) {
        current_frame_ = keyframes_.front();
        return;
    }

    const float seconds = time.asSeconds();
    const auto start = keyframes_.begin();
    const auto end = keyframes_.end();

    auto before = start;
    auto after = end - 1;

    for (auto it = start; it != end; ++it) {
        if (it->time().asSeconds() <= seconds) {
            before = it;
        }
    }

    if (before == end - 1) {
        current_frame_ = *before;
        return;
    }

    after = before + 1;
    const float current_time = seconds;
    const float lower_time = before->time().asSeconds();
    const float upper_time = after->time().asSeconds();
    const float span = upper_time - lower_time;

    if (span <= 0.0f) {
        current_frame_ = *before;
        return;
    }

    const float ratio = std::clamp((current_time - lower_time) / span, 0.0f, 1.0f);
    const sf::Time delta = sf::seconds(ratio * span);
    current_frame_ = before->tween(*after, delta);
}

std::unique_ptr<Component> Component::fromJson(const Json& data) {
    const std::string shape = data.value("shape", "");
    if (shape == "circle") {
        return std::make_unique<CircleComponent>(data);
    }
    if (shape == "rect" || shape == "rectangle") {
        return std::make_unique<RectangleComponent>(data);
    }
    if (shape == "image") {
        return std::make_unique<ImageComponent>(data);
    }
    if (shape == "text") {
        return std::make_unique<TextComponent>(data);
    }
    if (shape == "composite") {
        return std::make_unique<CompositeComponent>(data);
    }

    throw std::invalid_argument("Unknown component shape: " + shape);
}

CircleComponent::CircleComponent(const Json& data)
    : Component(data),
      radius_(data.value("radius", 0.0f)),
      sides_(data.value("sides", 30u)) {}

void CircleComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::CircleShape circle(radius_, sides_);
    circle.setFillColor(color());
    circle.setOrigin({radius_, radius_});

    sf::Transform local;
    currFrame().transform(local);
    sf::RenderStates composed = states;
    composed.transform = states.transform * local;
    target.draw(circle, composed);
}

RectangleComponent::RectangleComponent(const Json& data)
    : Component(data),
      width_(data.value("width", 0.0f)),
      height_(data.value("height", 0.0f)) {}

void RectangleComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape rect(sf::Vector2f(width_, height_));
    rect.setFillColor(color());
    rect.setOrigin({width_ / 2.0f, height_ / 2.0f});

    sf::Transform local;
    currFrame().transform(local);
    sf::RenderStates composed = states;
    composed.transform = states.transform * local;
    target.draw(rect, composed);
}

ImageComponent::ImageComponent(const Json& data)
    : Component(data),
      file_(resolvePath(data.value("file", ""))) {
    if (file_.empty()) {
        throw std::invalid_argument("Image component requires a file path");
    }

    texture_ = std::make_shared<sf::Texture>();
    if (!texture_->loadFromFile(file_)) {
        throw std::runtime_error("Unable to load image: " + file_);
    }
}

void ImageComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite(*texture_);
    const auto size = texture_->getSize();
    sprite.setOrigin({
        static_cast<float>(size.x) / 2.0f,
        static_cast<float>(size.y) / 2.0f,
    });
    sprite.setColor(color());

    sf::Transform local;
    currFrame().transform(local);
    sf::RenderStates composed = states;
    composed.transform = states.transform * local;
    target.draw(sprite, composed);
}

TextComponent::TextComponent(const Json& data)
    : Component(data),
      text_(data.value("text", "")),
      font_file_(resolvePath(data.value("font", ""))),
      font_(),
      character_size_(data.value("size", 30u)) {
    if (font_file_.empty()) {
        throw std::invalid_argument("Text component requires a font file");
    }
    if (!font_.openFromFile(font_file_)) {
        throw std::runtime_error("Unable to load font: " + font_file_);
    }
}

void TextComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Text text(font_, text_, character_size_);
    text.setFillColor(color());
    text.setPosition({0.0f, 0.0f});

    sf::Transform local;
    currFrame().transform(local);
    sf::RenderStates composed = states;
    composed.transform = states.transform * local;
    target.draw(text, composed);
}

CompositeComponent::CompositeComponent(const Json& data)
    : Component(data) {
    if (data.contains("children") && data["children"].is_array()) {
        for (const auto& child_json : data["children"]) {
            children_.push_back(Component::fromJson(child_json));
        }
    }
}

void CompositeComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Transform local;
    currFrame().transform(local);
    sf::RenderStates composed = states;
    composed.transform = states.transform * local;

    for (const auto& child : children_) {
        target.draw(*child, composed);
    }
}

}  // namespace AP
