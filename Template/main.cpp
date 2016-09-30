#include <SFML/Graphics.hpp>
#include "TransformNode.h"

int main(int argc, char *argv)
{
	//Initial Values
	sf::Vector2<float> bodySize(100.0f, 400.0f);
	sf::Vector2<float> armSize(20.0f, 50.0f);
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

  //Set body's properties
  bodyRect.setPosition(window.getSize().x / 2, 0);
  bodyRect.setOrigin(bodyRect.getSize().x / 2, 0);

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

    window.display();
  }

  return 0;
}