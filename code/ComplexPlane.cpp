#include "ComplexPlane.h"

/*
        VertexArray m_vArray;
        State m_state;
        Vector2f m_mouseLocation;
        Vectori m_pixel_size;
        Vector2f m_plane_center;
        Vector2f m_plane_size;
        int m_zoomCount;
        float m_aspectRatio;
*/

//Constructor

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
	// Assign m_pixelWidth with the parameter values
	m_aspectRatio = (float)pixelWidth / (float)pixelHeight;
	m_plane_center = Vector2f(0, 0);
	m_plane_size = Vector2f(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	// Initialize VertexArray
}

//Private Functions

int ComplexPlane::countIterations(Vector2f coord) {}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {}

//Public Functions

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {
	target.draw(m_vArray);
}
void ComplexPlane::zoomIn() {
	m_zoomCount++;
	int localX = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	int localY = BASE_HEIGHT * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = Vector2f(localX, localY);
	m_state = State::CALCULATING;
}
void ComplexPlane::zoomOut() {
        m_zoomCount--;
        int localX = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
        int localY = BASE_HEIGHT * (pow(BASE_ZOOM, m_zoomCount));
        m_plane_size = Vector2f(localX, localY);
        m_state = State::CALCULATING;
}
void ComplexPlane::setCenter(Vector2i mousePixel) {
	m_plane_center = ComplexPlane::mapPixelToCoords(mousePixel);
	m_state = State::CALCULATING;
}
void ComplexPlane::setMouseLocation(Vector2i mousePixel) {
	m_mouseLocation = ComplexPlane::mapPixelToCoords(mousePixel);
}
void ComplexPlane::loadText(Text& text) {
	//Use stringstream to create output text
}
void ComplexPlane::updateRender() {
	if (m_state == State::CALCULATING) {
		for () {
			for () {
				
			}
		}
	m_state = State::DISPLAYING;
	}
}
