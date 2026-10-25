#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

using Json = nlohmann::json;

namespace AP {

class KeyFrame {
 public:
    KeyFrame();
    explicit KeyFrame(const Json& json);

    sf::Time time() const;
    KeyFrame tween(KeyFrame alt, sf::Time t) const;
    void transform(sf::Transform& state) const;

 private:
    float t_;
    float x_;
    float y_;
    float scale_x_;
    float scale_y_;
    float theta_;
};

}  // namespace AP
