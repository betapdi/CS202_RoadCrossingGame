#ifndef CSCENENODE_H
#define CSCENENODE_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <memory>
#include <vector>

class CSCENENODE : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
	typedef std::unique_ptr<CSCENENODE> Ptr;
public:
	CSCENENODE();

	void attachChild(Ptr child);
	Ptr detachChild(const CSCENENODE& node);

	void update(float deltaTime);

	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;
private:
	virtual void updateCurrent(float deltaTime);
	void updateChildren(float deltaTime);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	std::vector<Ptr> mChildren;
	CSCENENODE* mParent;
};

#endif // !CSCENENODE_H