#pragma once

#include <memory>
#include <vector>

#include <nlohmann/json.hpp>
using Json = nlohmann::json;
#include <SFML/Graphics.hpp>

#include "KeyFrame.hpp"

namespace AP {
class Component: public sf::Drawable {
 public:
    /**
     * Advances this component to the state appropriate to the given time
     * @param time The Time to move to
     */
    virtual void tween(sf::Time time); // For part B

    /**
     * Constructs a Component from the Json object
     * @param data A Json object containing Component data
     * @return A new Component
     */
    static std::unique_ptr<Component> fromJson(const Json& data); // Factory
 protected:
    /**
     * Initializes base class components from the Json object
     * @param data A Json object containing Component data
     */
    explicit Component(const Json& data); // Abstract class

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const = 0; // Defined in subclasses
    /**
     * Gets the current frame for the time set in tween(t)
     * @return The current frame
     */
    KeyFrame currFrame() const; // For part B

    /**
     * Gets this Component's color
     * @return The color
     */
    sf::Color color() const;
 private:
    // Fields go here
};
}  // namespace AP
