#pragma once

#include "Utils.h"
#include "SceneNode.h"

class WaveGenerator;

class WavePatternNode: public SceneNode {
    public:
        explicit WavePatternNode(const std::string& shader_file, const std::vector<WaveGenerator*>& generator_list);

    protected:
        std::vector<WaveGenerator*> const& mGeneratorList;
        sf::RectangleShape mRect;
        sf::Shader mShader;
        sf::Time mElapsedTime;

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void updateCurrent(sf::Time dt) override;
};
