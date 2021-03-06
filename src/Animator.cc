#include "Animator.h"
#include "Utils.h"

#include <algorithm> 
#include <cmath> 
#include <iostream>

GInterpolation::GInterpolation(float r) {
	rate = r;
	easing = Easing::Linear;
	cb = [](){};
}

GInterpolation::GInterpolation(float r, std::function<void()> ca) {
	rate = r;
	easing = Easing::Linear;
	cb = ca;
}

GInterpolation::GInterpolation(float r, std::function<void()> ca, Easing e) {
	rate = r;
	easing = e;
	cb = ca;
}

bool GInterpolation::hasEnded() const{
	return ended;
}
/*
void GInterpolation::step(sf::Time dt){
	ended = true;
	cb();
}
*/

template<>
void Interpolation<float>::step(sf::Time dt){
    switch(easing){
        case GInterpolation::Easing::Linear:
            {
                if(abs((*interpolated) - target) > 0.01) {
                    alpha += std::min( std::max(dt.asSeconds() * rate, 0.f),1.f);
                    (*interpolated) = lerp(original, target, alpha);
                }
                else {
                	(*interpolated) = target;
                    ended = true;
                    cb();
                }
                
            }
        break;
        case GInterpolation::Easing::InOut:
        break;
        case GInterpolation::Easing::In:
        break;
        case GInterpolation::Easing::Out:
        break;
    }
};



template<>
void Interpolation<sf::Vector2f>::step(sf::Time dt){
    switch(easing){
        case GInterpolation::Easing::Linear:
            {
            	//std::cout << "in:" << (*interpolated)<< std::endl;
                if(Utils::distance((*interpolated), target) > 0.01) {
                    alpha += std::min( std::max(dt.asSeconds() * rate, 0.f),1.f);
                    
                    (*interpolated) = sf::Vector2f(
                    	lerp(original.x, target.x, alpha),
                    	lerp(original.y, target.y, alpha)
                    	);
                }
                else {
                	(*interpolated) = target;
                    ended = true;
                    cb();
                }
                
            }
        break;
        case GInterpolation::Easing::InOut:
        break;
        case GInterpolation::Easing::In:
        break;
        case GInterpolation::Easing::Out:
        break;
    }
};

Animator::Animator(){
	interpolations = std::vector<GInterpolation*>();
}

void Animator::interpolate(GInterpolation& i) {
	interpolations.push_back(&i);
}

void Animator::update(sf::Time dt){
	//Update interpolated values
	for(GInterpolation* i: interpolations) {
		i->step(dt);
	}
	//Clear finished
	interpolations.erase(
	   std::remove_if(
	      interpolations.begin(), interpolations.end(),
	      [](GInterpolation* i){ return i->hasEnded();}),
	interpolations.end());
	
}