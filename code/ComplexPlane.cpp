#include "ComplexPlane.h"
#include <thread>

/********************************
        VertexArray m_vArray;
        State m_state;
        Vector2f m_mouseLocation;
        Vector2i m_pixel_size;
        Vector2f m_plane_center;
        Vector2f m_plane_size;
        int m_zoomCount;
        float m_aspectRatio;
********************************/

/********************************
	Constructor
********************************/

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
	m_pixel_size = Vector2i(pixelWidth, pixelHeight);
	m_aspectRatio = (double)pixelWidth / (double)pixelHeight;
	m_plane_center = Vector2f(0.0, 0.0);
	m_plane_size = Vector2f(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	m_vArray = VertexArray(sf::Points, pixelWidth * pixelHeight);
}

/********************************
	Private Functions
********************************/

int ComplexPlane::countIterations(Vector2f coord) {
	complex<double> z(0.0, 0.0);
	complex<double> c(coord.x, coord.y);
	unsigned int count = 0;
	while (count < MAX_ITER && abs(z) < 2.0) {
		z = z * z + c;
		count++;
	}
	return count;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {
	r = 0;
	g = 0;
	b = 0;
	if (count == 0) {        // Black
		return;
	} else if (count < 16) { // Purple
		r = 255;
		b = 255;
	} else if (count < 32) { // Blue
		b = 255;
	} else if (count < 48) { // Green
                g = 255;
        } else if (count < 64) { // Red
                r = 255;
        }
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {
	// map value n from range [a,b] into range [c,d]
	// [ax,bx] = [0,m_pixel_size.x]
	// [ay,by] = [m_pixel_size.y,0]
	// [cx,dx] = [m_plane_center.x - m_plane_size.x / 2,m_plane_center.x + m_plane_size.x / 2]
	// [cy,dy] = [m_plane_center.y + m_plane_size.y / 2,m_plane_center.y - m_plane_size.y / 2]
	// ((n - a) / (b - a)) * (m_plane_size.(x/y)) + c

	double cx = (double)m_plane_center.x - (double)m_plane_size.x / 2.0;
	double cy = (double)m_plane_center.y - (double)m_plane_size.y / 2.0;

	double resultX = ((double)mousePixel.x / (double)m_pixel_size.x) * (double)m_plane_size.x + cx;
	double resultY = (((double)mousePixel.y - (double)m_pixel_size.y) / (0.0 - (double)m_pixel_size.y)) * (double)m_plane_size.y + cy;

	return Vector2f(resultX, resultY);
}

/********************************
	Public Functions
********************************/

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {
	target.draw(m_vArray);
}

void ComplexPlane::zoomIn() {
	m_zoomCount++;
	double localX = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	double localY = BASE_HEIGHT * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = Vector2f(localX, localY);
	m_state = State::CALCULATING;
}

void ComplexPlane::zoomOut() {
        m_zoomCount--;
        double localX = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
        double localY = BASE_HEIGHT * (pow(BASE_ZOOM, m_zoomCount));
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
	stringstream ss;
	ss << "Mandelbrot Set" << endl;
	ss << "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")" << endl;
	ss << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl;
	ss << "Left-click to Zoom In" << endl;
	ss << "Right-click to Zoom Out" << endl;
	text.setString(ss.str());
}

void ComplexPlane::updateRender() {
	if (m_state == State::CALCULATING) {
		vector<thread> threads;
		unsigned int numThreads = thread::hardware_concurrency();
		unsigned int rowsPerThread = m_pixel_size.y / numThreads;

		for (unsigned int t = 0; t < numThreads; ++t) {
			unsigned int startRow = t * rowsPerThread;
			unsigned int endRow = (t == numThreads - 1) ? m_pixel_size.y : startRow + rowsPerThread;
			threads.emplace_back(std::thread([&](unsigned int start, unsigned int end) {
				for (unsigned int i = start; i < end; ++i) {
					for (int j = 0; j < m_pixel_size.x; ++j) {
						m_vArray[j + i * m_pixel_size.x].position = {(float)j, (float)i};
						Vector2f complexCoord = mapPixelToCoords(Vector2i((double)j, (double)i));
						int iterations = countIterations(complexCoord);
						Uint8 r, g, b;
						iterationsToRGB(iterations, r, g, b);
						m_vArray[j + i * m_pixel_size.x].color = {r, g, b};
					}
				}
			}, startRow, endRow));
		}
		for (auto& thread : threads) {
			thread.join();
		}
	m_state = State::DISPLAYING;
	}
}
