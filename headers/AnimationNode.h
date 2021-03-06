#pragma once

#include "Utils.h"
#include "SpriteNode.h"

class AnimationNode: public SpriteNode {
    struct AnimFrame {
        int mIndex;
        float mTime;
    };

    public:
        explicit AnimationNode(const sf::Texture& texture, const std::string& file);
        AnimationNode(const sf::Texture& texture, const sf::IntRect& textureRect, const std::string& file);
        void setSize(sf::Vector2u desiredSize) override;
        void setAnimation(const std::string& animation);
        void resetAnimation();
        float getElapsedTime() const;


    protected:
        void updateCurrent(sf::Time dt) override;
        
    private:
        void load(const std::string& filename);
        void updateTextureRect();

        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;      

        std::map<std::string, std::vector<AnimFrame>> mAnimations;
        std::map<std::string, unsigned int> mAnimationCycles;
        sf::Vector2i mUnitSize;
        unsigned int mCurrentFrame;
        unsigned int mCurrentCycle;
        std::string mCurrentAnim;
        float mCurrentTime;
        float mTotalTime;
};
