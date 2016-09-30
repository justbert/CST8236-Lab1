#include <SFML/Graphics.hpp>
#include "TransformNode.h"

int main(int argc, char *argv)
{
	//Initial Values
	sf::Vector2<float> bodySize(100.0f, 400.0f);
	sf::Vector2<float> armSize(100.0f, 20.0f);
	sf::Vector2<float> neckSize(50.0f, 25.0f);
	float headSize = 75.0f;
	std::size_t headPoints = 60;

	//Create Window	
  sf::RenderWindow window(sf::VideoMode(600, 600), "WackyInflatableMan", sf::Style::Titlebar | sf::Style::Close);

  //create shapes
  sf::RectangleShape bodyRect(bodySize);
  sf::RectangleShape leftUpperArmRect(armSize);
  sf::RectangleShape leftLowerArmRect(armSize);
  sf::RectangleShape rightUpperArmRect(armSize);
  sf::RectangleShape rightLowerArmRect(armSize);
  sf::RectangleShape neckRect(neckSize);
  sf::CircleShape headCircle(headSize, headPoints);

  //Set bodys properties
  bodyRect.setPosition(window.getSize().x / 2.0f, window.getSize().y);
  bodyRect.setOrigin(bodyRect.getSize().x / 2.0f, bodyRect.getSize().y);

  //Set left arms position
  leftUpperArmRect.setOrigin(leftUpperArmRect.getSize().x, leftUpperArmRect.getSize().y / 2.0f);
  leftUpperArmRect.setPosition(-bodyRect.getLocalBounds().width/2.0f,-(bodyRect.getLocalBounds().height *0.8f));
  leftUpperArmRect.setFillColor(sf::Color::Cyan);

  leftLowerArmRect.setOrigin(leftLowerArmRect.getSize().x, leftLowerArmRect.getSize().y / 2.0f);
  leftLowerArmRect.setPosition(-leftUpperArmRect.getSize().x, 0);

  //Set right arms properties
  rightUpperArmRect.setOrigin(0, rightUpperArmRect.getSize().y / 2.0f);
  rightUpperArmRect.setPosition(bodyRect.getLocalBounds().width/2.0f,-(bodyRect.getLocalBounds().height * 0.8f));
  rightUpperArmRect.setFillColor(sf::Color::Blue);
  
  rightLowerArmRect.setOrigin(0, rightLowerArmRect.getSize().y / 2.0f);
  rightLowerArmRect.setPosition(rightLowerArmRect.getSize().x, 0);
  
  //Create Nodes
  TransformNode bodyNode(&bodyRect);
  TransformNode	leftUpperArmNode(&leftUpperArmRect);
  TransformNode rightUpperArmNode(&rightUpperArmRect);
  TransformNode leftLowerArmNode(&leftLowerArmRect);
  TransformNode rightLowerArmNode(&rightLowerArmRect);

  leftUpperArmNode.AddChild(&leftLowerArmNode);

  rightUpperArmNode.AddChild(&rightLowerArmNode);

  bodyNode.AddChild(&leftUpperArmNode);
  bodyNode.AddChild(&rightUpperArmNode);

  sf::Event evt;
  sf::Clock appTimer;
  while (window.isOpen()) {
    float deltaTime = appTimer.restart().asSeconds();

    while (window.pollEvent(evt)) {
      if (evt.type == sf::Event::Closed) {
        window.close();
      }
    }

    // do stuff.
    window.clear();

    //draw stuff
	bodyNode.Draw(&window);
	rightUpperArmNode.Draw(&window);
    window.display();
  }

  return 0;
}