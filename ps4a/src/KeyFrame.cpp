#include "KeyFrame.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace AP {

KeyFrame::KeyFrame()
    : t_(0.0f), x_(0.0f), y_(0.0f), scale_x_(1.0f), scale_y_(1.0f), theta_(0.0f) {}

KeyFrame::KeyFrame(const Json& json)
    : t_(json.value("t", 0.0f)),
      x_(json.value("x", 0.0f)),
      y_(json.value("y", 0.0f)),
      scale_x_(json.value("scale-x", json.value("scale_x", 1.0f))),
      scale_y_(json.value("scale-y", json.value("scale_y", 1.0f))),
      theta_(json.value("theta", 0.0f)) {}

sf::Time KeyFrame::time() const {
    return sf::seconds(t_);
}

KeyFrame KeyFrame::tween(KeyFrame alt, sf::Time t) const {
    const float delta_t = alt.t_ - t_;
    if (std::abs(delta_t) < 1e-6f) {
        return alt;
    }

    const float elapsed = std::max(0.0f, std::min(t.asSeconds(), static_cast<float>(std::abs(delta_t))));
    const float ratio = delta_t > 0.0f ? elapsed / delta_t : 1.0f;

    KeyFrame result;
    result.t_ = t_ + ratio * delta_t;
    result.x_ = x_ + (alt.x_ - x_) * ratio;
    result.y_ = y_ + (alt.y_ - y_) * ratio;
    result.scale_x_ = scale_x_ + (alt.scale_x_ - scale_x_) * ratio;
    result.scale_y_ = scale_y_ + (alt.scale_y_ - scale_y_) * ratio;
    result.theta_ = theta_ + (alt.theta_ - theta_) * ratio;
    return result;
}

void KeyFrame::transform(sf::Transform& state) const {
    state.translate({x_, y_});
    state.rotate(sf::degrees(theta_));
    state.scale({scale_x_, scale_y_});
}

}  // namespace AP
