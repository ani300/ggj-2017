#pragma once

#include "SceneNode.h"
#include <unordered_map>


class Tooltip {
public:
	Tooltip();
	~Tooltip();

	void fadeIn();
	void fadeOut();

	void draw(sf::RenderTarget *rt);

	std::string title;
	sf::Vector2f position;

	bool shown;
protected:

};


class TooltipSystem {
public:
	static void addTooltip(std::string, Tooltip*);
	static void showTooltip(std::string);
	static void hideTooltip(std::string);
	static void removeTooltip(std::string);

	static std::unordered_map<std::string, Tooltip*> tooltips;

	static void draw(sf::RenderTarget *rt);
};
