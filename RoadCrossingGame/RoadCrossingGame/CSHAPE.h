#ifndef CSHAPE_H
#define CSHAPE_H

#include <SFML/Graphics/Shape.hpp>
#include "SFML/Graphics.hpp"

namespace sf {
    class RoundedRectangleShape : public sf::Shape {
    public:
        explicit RoundedRectangleShape(const Vector2f& size = Vector2f(0, 0), float radius = 0, unsigned int cornerPointCount = 0);
        void setSize(const Vector2f& size);
        const Vector2f& getSize() const;
        void setCornersRadius(float radius);
        float getCornersRadius() const;
        void setCornerPointCount(unsigned int count);
        virtual std::size_t getPointCount() const;
        virtual sf::Vector2f getPoint(std::size_t index) const;
        void draw(sf::RenderWindow* window) {
            window->draw(*this);
        }
    private:
        Vector2f mySize;
        float myRadius;
        unsigned int myCornerPointCount;
    };
}
#endif // !CSHAPE_H