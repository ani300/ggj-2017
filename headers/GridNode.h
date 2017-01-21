#pragma once

#include "Utils.h"
#include "SceneNode.h"

class GridNode: public SceneNode {
    public:
        explicit GridNode(sf::Vector2i grid_size, sf::Color color);

        sf::Vector2f mGridSize;

    protected:
        sf::VertexArray mLines;

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};
