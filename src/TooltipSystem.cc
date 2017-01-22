#include "TooltipSystem.h"



std::unordered_map<std::string, Tooltip*> TooltipSystem::tooltips = std::unordered_map<std::string, Tooltip*>();


void TooltipSystem::addTooltip(std::string name, Tooltip* t) {
	TooltipSystem::tooltips.emplace(name, t);
}

void TooltipSystem::showTooltip(std::string name) {
	TooltipSystem::tooltips[name]->fadeIn();
}

void TooltipSystem::hideTooltip(std::string name) {
	TooltipSystem::tooltips[name]->fadeOut();
}

void TooltipSystem::removeTooltip(std::string name) {
	TooltipSystem::tooltips.erase(name);

}

void TooltipSystem::draw(sf::RenderTarget* rt) {
	for(auto t: TooltipSystem::tooltips) {
		t.second->draw(rt);
	}
}


Tooltip::Tooltip() {}
Tooltip::~Tooltip() {}

void Tooltip::fadeIn() {}
void Tooltip::fadeOut() {}
void Tooltip::draw(sf::RenderTarget*) {
	
}

