// Copyright 2026 AniPlayer project authors.

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "Component.hpp"

namespace AP {

class AniPlayer : public sf::Drawable {
 public:
    explicit AniPlayer(const std::string& filename);

    void tween(sf::Time time);
    sf::Vector2u windowSize() const;

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    unsigned int width_;
    unsigned int height_;
    std::string bgm_;
    std::unique_ptr<Component> scene_;
};

}  // namespace AP
