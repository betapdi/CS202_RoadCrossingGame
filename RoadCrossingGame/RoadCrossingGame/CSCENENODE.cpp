#include "CSCENENODE.h"
#include "CFOREACH.h"
#include <algorithm>
#include <cassert>

CSCENENODE::CSCENENODE()
	: mChildren()
	, mParent(nullptr)
{
}

void CSCENENODE::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

CSCENENODE::Ptr CSCENENODE::detachChild(const CSCENENODE& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) { return p.get() == &node; });
	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void CSCENENODE::update(float deltaTime)
{
	updateCurrent(deltaTime);
	updateChildren(deltaTime);
}

void CSCENENODE::clear() {
	FOREACH(Ptr & child, mChildren) {
		child->clear();
	}

	mChildren.clear();
	mParent = nullptr;
}

void CSCENENODE::updateCurrent(float deltaTime)
{
	// Do nothing by default
}

void CSCENENODE::updateChildren(float deltaTime)
{
	FOREACH(Ptr & child, mChildren)
		child->update(deltaTime);
}

void CSCENENODE::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);
}

void CSCENENODE::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

void CSCENENODE::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	FOREACH(const Ptr & child, mChildren)
		child->draw(target, states);
}

sf::Vector2f CSCENENODE::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform CSCENENODE::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const CSCENENODE* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;
}