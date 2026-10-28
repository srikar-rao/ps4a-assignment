#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
using Json = nlohmann::json;

namespace AP {
class KeyFrame {
 public:
    /**
     * Default constructs this KeyFrame
     */
    KeyFrame();
    /**
     * Constructs this KeyFrame by extracting data from a Json object
     * @param json A Json object containing KeyFrame data
     */
    explicit KeyFrame(const Json& json);

    /**
     * Gets the time at this KeyFrame
     */
    sf::Time time() const;

    /**
     * Computes the frame between this frame and the other one using linear interpolation
     * @param alt Another KeyFrame
     * @param t The time between the two KeyFrames to tween to
     */
    KeyFrame tween(KeyFrame alt, sf::Time t) const;  // For part B
    /**
     * Applies the transform information in this keyframe to the given Transform.
     * @param state A Transform object that will be modified
     */
    void transform(sf::Transform& state) const;
 private:
    // Fields go here
};
}  // namespace NP
