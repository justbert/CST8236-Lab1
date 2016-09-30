#include <SFML/Graphics.hpp>
#include "TransformNode.h"

int main(int argc, char *argv)
{
	//Initial Values
	sf::Vector2<float> bodySize(100.0f, 325.0f);
	sf::Vector2<float> armSize(150.0f, 20.0f);
	sf::Vector2<float> neckSize(35.0f, 25.0f);
	float headSize = 75.0f;
	std::size_t headPoints = 60;

	//Create Window	
  sf::RenderWindow window(sf::VideoMode(1000, 600), "WackyInflatableMan", sf::Style::Titlebar | sf::Style::Close);

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
  bodyRect.setFillColor(sf::Color::Magenta);

  //Set left arms position
  leftUpperArmRect.setOrigin(leftUpperArmRect.getSize().x, leftUpperArmRect.getSize().y / 2.0f);
  leftUpperArmRect.setPosition(-bodyRect.getLocalBounds().width/2.0f,-(bodyRect.getLocalBounds().height *0.8f));
  leftUpperArmRect.setFillColor(sf::Color::Cyan);

  leftLowerArmRect.setOrigin(leftLowerArmRect.getSize().x, leftLowerArmRect.getSize().y / 2.0f);
  leftLowerArmRect.setPosition(-leftUpperArmRect.getSize().x, 0);
  leftLowerArmRect.setFillColor(sf::Color::Cyan);

  //Set right arms properties
  rightUpperArmRect.setOrigin(0, rightUpperArmRect.getSize().y / 2.0f);
  rightUpperArmRect.setPosition(bodyRect.getLocalBounds().width/2.0f,-(bodyRect.getLocalBounds().height * 0.8f));
  rightUpperArmRect.setFillColor(sf::Color::Cyan);
  
  rightLowerArmRect.setOrigin(0, rightLowerArmRect.getSize().y / 2.0f);
  rightLowerArmRect.setPosition(rightLowerArmRect.getSize().x, 0);
  rightLowerArmRect.setFillColor(sf::Color::Cyan);

  //Set necks properties
  neckRect.setPosition(0, -bodyRect.getSize().y);
  neckRect.setOrigin(neckRect.getSize().x / 2.0f, neckRect.getSize().y);
  neckRect.setFillColor(sf::Color::Magenta);

  //Set head properties
  headCircle.setOrigin(headCircle.getLocalBounds().width / 2.0f, headCircle.getLocalBounds().height * 0.95f);
  headCircle.setPosition(0, -neckRect.getSize().y);
  headCircle.setFillColor(sf::Color::Blue);
  
  //Create Nodes
  TransformNode bodyNode(&bodyRect);
  TransformNode	leftUpperArmNode(&leftUpperArmRect);
  TransformNode rightUpperArmNode(&rightUpperArmRect);
  TransformNode leftLowerArmNode(&leftLowerArmRect);
  TransformNode rightLowerArmNode(&rightLowerArmRect);
  TransformNode neckNode(&neckRect);
  TransformNode headNode(&headCircle);

  leftUpperArmNode.AddChild(&leftLowerArmNode);

  rightUpperArmNode.AddChild(&rightLowerArmNode);

  neckNode.AddChild(&headNode);

  bodyNode.AddChild(&leftUpperArmNode);
  bodyNode.AddChild(&rightUpperArmNode);
  bodyNode.AddChild(&neckNode);

  //AngleStuff
  int bodyMaxAngle = 40;
  float bodyCurrAngle = bodyMaxAngle / 2.0f;
  float bodyTargAngle = rand() % bodyMaxAngle;

  int headMaxAngle = 60;
  float headCurrAngle = headMaxAngle / 2.0f;
  float headTargAngle = rand() % headMaxAngle;

  int neckMaxAngle = 60;
  float neckCurrAngle = neckMaxAngle / 2.0f;
  float neckTargAngle = rand() % neckMaxAngle;
  
  int rightUpArmMaxAngle = 140;
  float rightUpArmCurrAngle = rightUpArmMaxAngle / 2.0f;
  float rightUpArmTargAngle = rand() % rightUpArmMaxAngle;
  
  int leftUpArmMaxAngle = 140;
  float leftUpArmCurrAngle = leftUpArmMaxAngle / 2.0f;
  float leftUpArmTargAngle = rand() % leftUpArmMaxAngle;

  int rightLowArmMaxAngle = 140;
  float rightLowArmCurrAngle = rightUpArmMaxAngle / 2.0f;
  float rightLowArmTargAngle = rand() % rightUpArmMaxAngle;

  int leftLowArmMaxAngle = 140;
  float leftLowArmCurrAngle = leftUpArmMaxAngle / 2.0f;
  float leftLowArmTargAngle = rand() % leftUpArmMaxAngle;

  //Angles "speeds"
  float bodySpeed = rand() % 10 + 10;
  float neckSpeed = rand() % 20 + 20;
  float headSpeed = rand() % 20 + 20;
  float leftUpperArmSpeed = rand() % 50 + 40;
  float leftLowerArmSpeed = rand() % 50 + 40;
  float rightUpperArmSpeed = rand() % 50 + 40;
  float rightLowerArmSpeed = rand() % 50 + 40;

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
	//Rotate the head
	if (headCurrAngle < headTargAngle)
	{
		float currentRotate = headSpeed * deltaTime;
		headCircle.rotate(currentRotate);
		headCurrAngle += currentRotate;
		if (headCurrAngle > headTargAngle)
		{
			headTargAngle = rand() % headMaxAngle;
			headSpeed = rand() % 20 + 20;
		}
	}
	else if (headCurrAngle > headTargAngle)
	{
		float currentRotate = -(headSpeed * deltaTime);
		headCircle.rotate(currentRotate);
		headCurrAngle += currentRotate;
		if (headCurrAngle < headTargAngle)
		{
			headTargAngle = rand() % headMaxAngle;
			headSpeed = rand() % 20 + 20;
		}

	}
	else
	{
		headTargAngle = rand() % headMaxAngle;
		headSpeed = rand() % 20 + 20;
	}

	//Rotate the body
	if (bodyCurrAngle < bodyTargAngle)
	{
		float currentRotate = bodySpeed * deltaTime;
		bodyRect.rotate(currentRotate);
		bodyCurrAngle += currentRotate;
		if (bodyCurrAngle > bodyTargAngle)
		{
			bodyTargAngle = rand() % bodyMaxAngle;
			bodySpeed = rand() % 10 + 10;
		}
	}
	else if (bodyCurrAngle > bodyTargAngle)
	{
		float currentRotate = -(bodySpeed * deltaTime);
		bodyRect.rotate(currentRotate);
		bodyCurrAngle += currentRotate;
		if (bodyCurrAngle < bodyTargAngle)
		{
			bodyTargAngle = rand() % bodyMaxAngle;
			bodySpeed = rand() % 10 + 10;
		}

	}
	else
	{
		bodyTargAngle = rand() % bodyMaxAngle;
		bodySpeed = rand() % 10 + 10;
	}

	//Rotate the neck
	if (neckCurrAngle < neckTargAngle)
	{
		float currentRotate = neckSpeed * deltaTime;
		neckRect.rotate(currentRotate);
		neckCurrAngle += currentRotate;
		if (neckCurrAngle > neckTargAngle)
		{
			neckTargAngle = rand() % neckMaxAngle;
			neckSpeed = rand() % 20 + 20;
		}
	}
	else if (neckCurrAngle > neckTargAngle)
	{
		float currentRotate = -(neckSpeed * deltaTime);
		neckRect.rotate(currentRotate);
		neckCurrAngle += currentRotate;
		if (neckCurrAngle < neckTargAngle)
		{
			neckTargAngle = rand() % neckMaxAngle;
			neckSpeed = rand() % 20 + 20;
		}

	}
	else
	{
		neckTargAngle = rand() % neckMaxAngle;
		neckSpeed = rand() % 20 + 20;
	}

	//Rotate Right Upper Arm
	if(rightUpArmCurrAngle < rightUpArmTargAngle)
	{
		float currentRotate = rightUpperArmSpeed * deltaTime;
		rightUpperArmRect.rotate(currentRotate);
		rightUpArmCurrAngle += currentRotate;
		if(rightUpArmCurrAngle > rightUpArmTargAngle)
		{
			rightUpArmTargAngle = rand() % rightUpArmMaxAngle;
			rightUpperArmSpeed = rand() % 50 + 40;
		}
	} else if(rightUpArmCurrAngle > rightUpArmTargAngle)
	{
		float currentRotate = -(rightUpperArmSpeed * deltaTime);
		rightUpperArmRect.rotate(currentRotate);
		rightUpArmCurrAngle += currentRotate;
		if (rightUpArmCurrAngle < rightUpArmTargAngle)
		{
			rightUpArmTargAngle = rand() % rightUpArmMaxAngle;
			rightUpperArmSpeed = rand() % 50 + 40;
		}

	} else
	{
		rightUpArmTargAngle = rand() % rightUpArmMaxAngle;
		rightUpperArmSpeed = rand() % 50 + 40;
	}

	//Rotate Right Lowper Arm
	if (rightLowArmCurrAngle < rightLowArmTargAngle)
	{
		float currentRotate = rightLowerArmSpeed * deltaTime;
		rightLowerArmRect.rotate(currentRotate);
		rightLowArmCurrAngle += currentRotate;
		if (rightLowArmCurrAngle > rightLowArmTargAngle)
		{
			rightLowArmTargAngle = rand() % rightLowArmMaxAngle;
			rightLowerArmSpeed = rand() % 50 + 40;
		}
	}
	else if (rightLowArmCurrAngle > rightLowArmTargAngle)
	{
		float currentRotate = -(rightLowerArmSpeed * deltaTime);
		rightLowerArmRect.rotate(currentRotate);
		rightLowArmCurrAngle += currentRotate;
		if (rightLowArmCurrAngle < rightLowArmTargAngle)
		{
			rightLowArmTargAngle = rand() % rightLowArmMaxAngle;
			rightLowerArmSpeed = rand() % 50 + 40;
		}

	}
	else
	{
		rightLowArmTargAngle = rand() % rightLowArmMaxAngle;
		rightLowerArmSpeed = rand() % 50 + 40;
	}

	//Rotate Left Upper Arm
	if (leftUpArmCurrAngle < leftUpArmTargAngle)
	{
		float currentRotate = leftUpperArmSpeed * deltaTime;
		leftUpperArmRect.rotate(currentRotate);
		leftUpArmCurrAngle += currentRotate;
		if (leftUpArmCurrAngle > leftUpArmTargAngle)
		{
			leftUpArmTargAngle = rand() % leftUpArmMaxAngle;
			leftUpperArmSpeed = rand() % 50 + 40;
		}
	}
	else if (leftUpArmCurrAngle > leftUpArmTargAngle)
	{
		float currentRotate = -(leftUpperArmSpeed * deltaTime);
		leftUpperArmRect.rotate(currentRotate);
		leftUpArmCurrAngle += currentRotate;
		if (leftUpArmCurrAngle < leftUpArmTargAngle)
		{
			leftUpArmTargAngle = rand() % leftUpArmMaxAngle;
			leftUpperArmSpeed = rand() % 50 + 40;
		}

	}
	else
	{
		leftUpArmTargAngle = rand() % leftUpArmMaxAngle;
		leftUpperArmSpeed = rand() % 50 + 40;
	}

	//Rotate Left Lowper Arm
	if (leftLowArmCurrAngle < leftLowArmTargAngle)
	{
		float currentRotate = leftLowerArmSpeed * deltaTime;
		leftLowerArmRect.rotate(currentRotate);
		leftLowArmCurrAngle += currentRotate;
		if (leftLowArmCurrAngle > leftLowArmTargAngle)
		{
			leftLowArmTargAngle = rand() % leftLowArmMaxAngle;
			leftLowerArmSpeed = rand() % 50 + 40;
		}
	}
	else if (leftLowArmCurrAngle > leftLowArmTargAngle)
	{
		float currentRotate = -(leftLowerArmSpeed * deltaTime);
		leftLowerArmRect.rotate(currentRotate);
		leftLowArmCurrAngle += currentRotate;
		if (leftLowArmCurrAngle < leftLowArmTargAngle)
		{
			leftLowArmTargAngle = rand() % leftLowArmMaxAngle;
			leftLowerArmSpeed = rand() % 50 + 40;
		}

	}
	else
	{
		leftLowArmTargAngle = rand() % leftLowArmMaxAngle;
		leftLowerArmSpeed = rand() % 50 + 40;
	}

    window.clear();

    //draw stuff
	bodyNode.Draw(&window);
	rightUpperArmNode.Draw(&window);
    window.display();
  }

  return 0;
}