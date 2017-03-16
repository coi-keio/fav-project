#include "Color.h"

namespace FavLibrary
{
	ColorBase::ColorBase() {}
	ColorBase::~ColorBase() {}


	ColorRGB::ColorRGB() {}
	ColorRGB::~ColorRGB() {}
	unsigned char ColorRGB::getR() { return this->r; }
	void ColorRGB::setR(unsigned char r) { this->r = r; }

	unsigned char ColorRGB::getG() { return this->g; }
	void ColorRGB::setG(unsigned char g) { this->g = g; }

	unsigned char ColorRGB::getB() { return this->b; }
	void ColorRGB::setB(unsigned char b) { this->b = b; }

	void ColorRGB::setColorRBG(unsigned char r, unsigned char g, unsigned char b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}


	ColorRGBA::ColorRGBA() {}
	ColorRGBA::~ColorRGBA() {}
	unsigned char ColorRGBA::getA() { return this->a; }
	void ColorRGBA::setA(unsigned char a) { this->a = a; }

	void ColorRGBA::setColorRBGA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		setColorRBG(r, g, b);
		this->a = a;
	}


	ColorGrayscale::ColorGrayscale() {}
	ColorGrayscale::~ColorGrayscale() {}
	unsigned char ColorGrayscale::getGray() { return this->gray; }
	void ColorGrayscale::setGray(unsigned char gray) { this->gray = gray; }


	ColorGrayscale16::ColorGrayscale16() {}
	ColorGrayscale16::~ColorGrayscale16() {}
	unsigned short ColorGrayscale16::getGray() { return this->gray; }
	void ColorGrayscale16::setGray(unsigned short gray) { this->gray = gray; }


	ColorCMYK::ColorCMYK() {}
	ColorCMYK::~ColorCMYK() {}
	unsigned char ColorCMYK::getC() { return this->c; }
	void ColorCMYK::setC(unsigned char c) { this->c = c; }

	unsigned char ColorCMYK::getM() { return this->m; }
	void ColorCMYK::setM(unsigned char m) { this->m = m; }

	unsigned char ColorCMYK::getY() { return this->y; }
	void ColorCMYK::setY(unsigned char y) { this->y = y; }

	unsigned char ColorCMYK::getK() { return this->k; }
	void ColorCMYK::setK(unsigned char k) { this->k = k; }

	void ColorCMYK::setColorCMYK(unsigned char c, unsigned char m, unsigned char y, unsigned char k)
	{
		this->c = c;
		this->m = m;
		this->y = y;
		this->k = k;
	}
}
