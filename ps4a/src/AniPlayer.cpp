// Copyright 2026 AniPlayer project authors.

#include "AniPlayer.hpp"

#include <fstream>
#include <stdexcept>

namespace AP {

AniPlayer::AniPlayer(const std::string& filename)
    : width_(800u), height_(600u), bgm_(), scene_() {
    std::ifstream input(filename);
    if (!input) {
        throw std::runtime_error("Unable to open animation file: " + filename);
    }

    Json data = Json::parse(input);
    width_ = static_cast<unsigned int>(data.value("width", static_cast<unsigned int>(800)));
    height_ = static_cast<unsigned int>(data.value("height", static_cast<unsigned int>(600)));
    bgm_ = data.value("bgm", std::string());

    if (!data.contains("scene")) {
        throw std::invalid_argument("Animation file is missing a scene");
    }

    scene_ = Component::fromJson(data["scene"]);
    scene_->tween(sf::Time::Zero);
}

void AniPlayer::tween(sf::Time time) {
    if (scene_) {
        scene_->tween(time);
    }
}

sf::Vector2u AniPlayer::windowSize() const {
    return sf::Vector2u(width_, height_);
}

void AniPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (scene_) {
        target.draw(*scene_, states);
    }
}

}  // namespace AP
