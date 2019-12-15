﻿#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <cstring>
#include "Controller.h"
#include "ShapesHeader.h"
#include "AppSettings.h"

#ifdef _DEBUG
#include <vld.h>
#endif

void setMenu(Controller*, tgui::MenuBar::Ptr);

int main()
{
	sf::Image icon;
	if (!icon.loadFromFile("../assets/icon.png")) return EXIT_FAILURE;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	tgui::Gui* gui = new tgui::Gui{ *window };
	
	Controller* CTR = new Controller();

	tgui::MenuBar::Ptr menu = tgui::MenuBar::create();
	menu->setSize(static_cast<float>((*window).getSize().x), 25.f);
	menu->setTextSize(13);
	setMenu(CTR, menu);

	gui->add(menu);
	CTR->refreshView(window, gui);

	while (window->isOpen())
	{
		sf::Event event;
		sf::Cursor cursor;
		while (window->pollEvent(event))
		{
			if (gui->handleEvent(event) ==  1) CTR->refreshView(window, gui);
			if (event.type) window->clear(sf::Color::Black);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (cursor.loadFromSystem(sf::Cursor::Cross)) window->setMouseCursor(cursor);
				auto shape = CTR->getShapeController()->generate(CTR->getActiveCanvas(), sf::Mouse::getPosition(*window));
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					shape->update(sf::Mouse::getPosition(*window), CTR->getShapeProperites());
					CTR->refreshView(window, gui);
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				if (cursor.loadFromSystem(sf::Cursor::Cross)) window->setMouseCursor(cursor);
				CTR->reverseColors();
				auto shape = CTR->getShapeController()->generate(CTR->getActiveCanvas(), sf::Mouse::getPosition(*window));
				while (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					shape->update(sf::Mouse::getPosition(*window), CTR->getShapeProperites());
					CTR->refreshView(window, gui);
				}
				CTR->reverseColors();
			}
			if (event.type == sf::Event::Closed) window->close();
			if (cursor.loadFromSystem(sf::Cursor::Arrow)) window->setMouseCursor(cursor);
		}
	}

	delete CTR;
	CTR = nullptr;
	delete gui;
	gui = nullptr;
	delete window;
	window = nullptr;
	return EXIT_SUCCESS;
}

void setMenu(Controller* CTR, tgui::MenuBar::Ptr menu)
{
	// --------------------------------------------FILE SECTION----------------------------------------------------------
	menu->addMenuItem({ "File", "Load" });
	menu->connectMenuItem({ "File", "Load" }, [&, CTR] { CTR->loadFromFile(); });
	menu->addMenuItem({ "File", "Save" });
	menu->connectMenuItem({ "File", "Save" }, [&, CTR] { CTR->saveToFile(); });

	// --------------------------------------------GEOMETRIC SECTION-----------------------------------------------------
	menu->addMenuItem({ "Geometric", "Shape", "Line" });
	menu->connectMenuItem({ "Geometric", "Shape", "Line" }, [&, CTR] { CTR->setShape<Shapes::Line>(); });
	menu->addMenuItem({ "Geometric", "Shape", "Triangle" });
	menu->connectMenuItem({ "Geometric", "Shape", "Triangle" }, [&, CTR] { CTR->setShape<Shapes::Triangle>(); });
	menu->addMenuItem({ "Geometric", "Shape", "Trapeze" });
	menu->connectMenuItem({ "Geometric", "Shape", "Trapeze" }, [&, CTR] { CTR->setShape<Shapes::Trapeze>(); });
	menu->addMenuItem({ "Geometric", "Shape", "Rectangle" });
	menu->connectMenuItem({ "Geometric", "Shape", "Rectangle" }, [&, CTR] { CTR->setShape<Shapes::Rectangle>(); });
	menu->addMenuItem({ "Geometric", "Shape", "Diamond" });
	menu->connectMenuItem({ "Geometric", "Shape", "Diamond" }, [&, CTR] { CTR->setShape<Shapes::Diamond>(); });
	menu->addMenuItem({ "Geometric", "Shape", "Pentagon" });
	menu->connectMenuItem({ "Geometric", "Shape", "Pentagon" }, [&, CTR] { CTR->setShape<Shapes::Pentagon>(); });
	menu->addMenuItem({ "Geometric", "Shape", "Hexagon" });
	menu->connectMenuItem({ "Geometric", "Shape", "Hexagon" }, [&, CTR] { CTR->setShape<Shapes::Hexagon>(); });
	menu->addMenuItem({ "Geometric", "Shape", "Ellipse" });
	menu->connectMenuItem({ "Geometric", "Shape", "Ellipse" }, [&, CTR] { CTR->setShape<Shapes::Ellipse>(); });

	// --------------------------------------------GEOMETRIC OUTLINE SECTION--------------------------------------------
	menu->addMenuItem({ "Geometric", "Outline", "0" });
	menu->connectMenuItem({ "Geometric", "Outline", "0" }, [&, CTR] { CTR->setOutlineSize(0); });
	menu->addMenuItem({ "Geometric", "Outline", "3" });
	menu->connectMenuItem({ "Geometric", "Outline", "3" }, [&, CTR] { CTR->setOutlineSize(3); });
	menu->addMenuItem({ "Geometric", "Outline", "6" });
	menu->connectMenuItem({ "Geometric", "Outline", "6" }, [&, CTR] { CTR->setOutlineSize(6); });
	menu->addMenuItem({ "Geometric", "Outline", "9" });
	menu->connectMenuItem({ "Geometric", "Outline", "9" }, [&, CTR] { CTR->setOutlineSize(9); });

	// --------------------------------------------GEOMETRIC TEXTURE SECTION--------------------------------------------
	menu->addMenuItem({ "Geometric", "Texture", "-" });
	menu->connectMenuItem({ "Geometric", "Texture", "-" }, [&, CTR] { CTR->clearTexture(); });
	menu->addMenuItem({ "Geometric", "Texture", "Style 1" });
	menu->connectMenuItem({ "Geometric", "Texture", "Style 1" }, [&, CTR] {CTR->setTexture("../assets/textures/style-1.png"); });
	menu->addMenuItem({ "Geometric", "Texture", "Style 2" });
	menu->connectMenuItem({ "Geometric", "Texture", "Style 2" }, [&, CTR] { CTR->setTexture("../assets/textures/style-2.png"); });

	// --------------------------------------------COLOR PRIMARY SECTION-------------------------------------------------
	menu->addMenuItem({ "Color", "Primary", "Red" });
	menu->connectMenuItem({ "Color", "Primary", "Red" }, [&, CTR] { CTR->setFillColor(sf::Color::Red); });
	menu->addMenuItem({ "Color", "Primary", "Green" });
	menu->connectMenuItem({ "Color", "Primary", "Green" }, [&, CTR] { CTR->setFillColor(sf::Color::Green); });
	menu->addMenuItem({ "Color", "Primary", "Blue" });
	menu->connectMenuItem({ "Color", "Primary", "Blue" }, [&, CTR] { CTR->setFillColor(sf::Color::Blue); });
	menu->addMenuItem({ "Color", "Primary", "White" });
	menu->connectMenuItem({ "Color", "Primary", "White" }, [&, CTR] { CTR->setFillColor(sf::Color::White); });
	menu->addMenuItem({ "Color", "Primary", "Black" });
	menu->connectMenuItem({ "Color", "Primary", "Black" }, [&, CTR] { CTR->setFillColor(sf::Color::Black); });

	// --------------------------------------------COLOR SECONDARY SECTION------------------------------------------
	menu->addMenuItem({ "Color", "Secondary", "Red" });
	menu->connectMenuItem({ "Color", "Secondary", "Red" }, [&, CTR] { CTR->setOutlineColor(sf::Color::Red); });
	menu->addMenuItem({ "Color", "Secondary", "Green" });
	menu->connectMenuItem({ "Color", "Secondary", "Green" }, [&, CTR] { CTR->setOutlineColor(sf::Color::Green); });
	menu->addMenuItem({ "Color", "Secondary", "Blue" });
	menu->connectMenuItem({ "Color", "Secondary", "Blue" }, [&, CTR] { CTR->setOutlineColor(sf::Color::Blue); });
	menu->addMenuItem({ "Color", "Secondary", "White" });
	menu->connectMenuItem({ "Color", "Secondary", "White" }, [&, CTR] { CTR->setOutlineColor(sf::Color::White); });
	menu->addMenuItem({ "Color", "Secondary", "Black" });
	menu->connectMenuItem({ "Color", "Secondary", "Black" }, [&, CTR] { CTR->setOutlineColor(sf::Color::Black); });

	// --------------------------------------------UTILITY SECTION------------------------------------------
	menu->addMenuItem({ "Utility", "Pencil" });
	menu->connectMenuItem("Utility", "Pencil", [&, CTR] { CTR->setShape<Shapes::Pencil>(); });
	menu->addMenuItem({ "Utility", "Clear" });
	menu->connectMenuItem("Utility", "Clear", [&, CTR] { CTR->resetCanvas(); });

	menu->setMenuItemEnabled({ "File", "Load" }, false);
}
