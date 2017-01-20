#pragma once

#include "Utils.h"
#include "SceneNode.h"

class SpriteNode: public SceneNode {
    public:
        explicit SpriteNode(const sf::Texture& texture);
        SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);
        virtual void setSize(sf::Vector2u desiredSize);

        void setColor(sf::Color color);
        sf::Color getColor();
        sf::IntRect getBounds();

        sf::Vector2f mSize;

    protected:
        sf::Sprite mSprite;

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void updateCurrent(sf::Time dt) override;
};
