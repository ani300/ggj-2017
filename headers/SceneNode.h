#pragma once

#include "Utils.h"

class SceneNode: public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
	public:
		typedef std::unique_ptr<SceneNode> Ptr;

		SceneNode();

		void attachChild(Ptr child);
		Ptr	detachChild(const SceneNode& node);
		
		void update(sf::Time dt);

		sf::Vector2f getWorldPosition() const;
		sf::Transform getWorldTransform() const;
		void getAllChildren(std::vector<SceneNode*>& v);
		//Hover is over but without moving the mouse some time
		virtual void onHover();
		virtual void onHoverOut();
		virtual void onMouseOver();
		virtual void onMouseOut();
	private:
		void updateChildren(sf::Time dt);
		virtual void updateCurrent(sf::Time dt);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		SceneNode* mParent;
		std::vector<Ptr> mChildren;
};
