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
            	//std::cout << "in:" << (*interpolated)<< std::endl;
                if(abs((*interpolated) - target) > 0.001) {
                    (*interpolated) += (original+target)/2 * dt.asSeconds() * rate;
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
                    (*interpolated) = sf::Vector2f(
                    	interpolated->x + (interpolated->x+target.x)/2* dt.asSeconds() * rate,
                    	interpolated->y + (interpolated->y+target.y)/2* dt.asSeconds() * rate
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