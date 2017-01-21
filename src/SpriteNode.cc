#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture) : 
    mSize(texture.getSize()),
    mSprite(texture) {
    Utils::centerOrigin(mSprite);
}


SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect) 
: mSprite(texture, textureRect) {
    Utils::centerOrigin(mSprite);
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

void SpriteNode::setSize(sf::Vector2u desiredSize){
    float scalex, scaley;
    scalex = scaley = 0.0;
    scalex = float(desiredSize.x)/mSprite.getTexture()->getSize().x;
    scaley = float(desiredSize.y)/mSprite.getTexture()->getSize().y;
    setScale(scalex, scaley);
    mSize = sf::Vector2f(desiredSize.x, desiredSize.y);
}

void SpriteNode::setColor(sf::Color color){
    mSprite.setColor(color);
}

sf::Color SpriteNode::getColor(){
    return mSprite.getColor();
}

void SpriteNode::updateCurrent(sf::Time /*dt*/) {
}

sf::IntRect SpriteNode::getBounds() {
    sf::Vector2f pos = getWorldPosition();
    sf::Vector2i newPos = sf::Vector2i(pos.x-mSize.x/2, pos.y-mSize.y/2);
    sf::Vector2i size = sf::Vector2i(mSize.x, mSize.y);
    return sf::IntRect(newPos, size);
}
