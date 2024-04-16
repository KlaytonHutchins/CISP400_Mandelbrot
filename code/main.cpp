#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

using namespace sf;
using namespace std;

int main() {
	
	VideoMode vm(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);
	ComplexPlane cp;

	//Font and text objects
	Text text;
	Font font;
	font.loadFromFile("./fonts/opensans.ttf");
	text.setFont(font);
	text.setString("");
	text.setCharacterSize(16);
	text.setFillColor(Color::White);

	while (window.isOpen()) {

	//Handle input
	//Update
	//Draw

	}

}
