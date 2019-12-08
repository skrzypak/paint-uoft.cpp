#include "Ellipse.h"

CApp::Ellipse::Ellipse(const sf::Vector2i& s): Polygons(30)
{
#ifdef _DEBUG
	std::cout << "CApp::Ellipse::Ellipse(const sf::Vector2i& s): Polygons(30)" << std::endl;
#endif
    _startXY = s;
    this->setPosition(sf::Vector2f(static_cast<float>(s.x), static_cast<float>(s.y)));
}

void* CApp::Ellipse::getDrawable() const
{
#ifdef _DEBUG
	std::cout << "void* CApp::Ellipse::getDrawable() const" << std::endl;
#endif
	return const_cast<Ellipse*>(this);
}
