#include "ComplexPlane.h"

using namespace sf;
using namespace std;

int main() {

	VideoMode vm(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2);
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);
	ComplexPlane cp(vm.width, vm.height);

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
					cp.setCenter(Vector2i((double)event.mouseButton.x, (double)event.mouseButton.y));
					cp.zoomOut();
				}
				else if (event.mouseButton.button == sf::Mouse::Left) {
                                        cp.setCenter(Vector2i((double)event.mouseButton.x, (double)event.mouseButton.y));
					cp.zoomIn();
				}
                        }
			if (event.type == sf::Event::MouseMoved) {
				cp.setMouseLocation(sf::Mouse::getPosition(window));
			}
		}
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                        window.close();
                }

		//Update
		cp.updateRender();
		cp.loadText(text);

		//Draw
		window.clear();

		window.draw(cp);
		window.draw(text);

		window.display();

	}

}
