#pragma once

#include "Utils.h"
#include "SceneNode.h"

class WaveGenerator;

class WavePatternNode: public SceneNode {
    public:
        explicit WavePatternNode(const std::string& shader_file, const std::vector<WaveGenerator*>& generator_list,
            sf::Color color1, sf::Color color2, sf::Color color3);
        explicit WavePatternNode(const std::string& shader_file, const std::vector<WaveGenerator*>& generator_list);


    protected:
        std::vector<WaveGenerator*> const& mGeneratorList;
        sf::RectangleShape mRect;
        sf::Color mColor1;
        sf::Color mColor2;
        sf::Color mColor3;
        sf::Shader mShader;
        sf::Time mElapsedTime;
        bool mRGB;

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void updateCurrent(sf::Time dt) override;
};
