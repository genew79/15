#pragma once
#include <SFML/Graphics.hpp>

class Element : public sf::Drawable, public sf::Transformable
{
protected:
	int value;
public:
	Element(int val);
	~Element();
	void SetPosition();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

