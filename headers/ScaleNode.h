#pragma once

#include "Utils.h"
#include "SceneNode.h"

class ScaleNode: public SceneNode {
    public:
        explicit ScaleNode(std::string const& vertex_file, std::string const& fragment_file, const sf::Texture& texture,
            sf::Color color1, sf::Color color2, sf::Color color3);

    protected:
        sf::Sprite mOutRect;
        sf::RectangleShape mScaleRect;
        sf::Color mColor1;
        sf::Color mColor2;
        sf::Color mColor3;
        sf::Shader mShader;

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void updateCurrent(sf::Time dt) override;
};
