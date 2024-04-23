#include "ComplexPlane.h"

using namespace sf;
using namespace std;

int main() {
	
	VideoMode vm(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);
	ComplexPlane cp(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);

	//Font and text objects
	Text text;
	Font font;
	font.loadFromFile("./fonts/opensans.ttf");
	text.setFont(font);
	text.setString("");
	text.setCharacterSize(16);
	text.setFillColor(Color::White);
	stringstream ss;

	while (window.isOpen()) {

		//Handle input
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					cp.zoomOut();
					cp.setCenter(Vector2i((float)event.mouseButton.x, (float)event.mouseButton.y));
				}
				else if (event.mouseButton.button == sf::Mouse::Left) {
					cp.zoomIn();
                                        cp.setCenter(Vector2i((float)event.mouseButton.x, (float)event.mouseButton.y));
				}
                        }
			if (event.type == sf::Event::MouseMoved) {
				cp.setMouseLocation(Vector2i((float)event.mouseButton.x, (float)event.mouseButton.y));
			}
		}
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                        window.close();
                }

		//Update
		cp.updateRender();
		text.setString(ss.str());
		cp.loadText(text);

		//Draw
		window.clear();

		window.draw(cp);
		window.draw(text);

		window.display();

	}

}
