#include "GridNode.h"

GridNode::GridNode(sf::Vector2i grid_size, sf::Color color) :
    mGridSize(grid_size)
{
    int num_vert = 1920/mGridSize.x;
    int num_hor = 1080/mGridSize.y;

    mLines = sf::VertexArray(sf::Lines, 2*num_vert + 2*num_hor);
    for (int i = 0; i < num_vert; ++i) {
        mLines[2*i].position = sf::Vector2f(i*mGridSize.x, 0);
        mLines[2*i].color = color;
        mLines[2*i + 1].position = sf::Vector2f(i*mGridSize.x, 1079);
        mLines[2*i + 1].color = color;
    }
    for (int i = num_hor; i < num_vert + num_hor; ++i) {
        int i_corr = i - num_hor;
        mLines[2*i].position = sf::Vector2f(0, i_corr*mGridSize.y);
        mLines[2*i].color = color;
        mLines[2*i + 1].position = sf::Vector2f(1919, i_corr*mGridSize.y);
        mLines[2*i + 1].color = color;
    }
}

void GridNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mLines, states);
}
