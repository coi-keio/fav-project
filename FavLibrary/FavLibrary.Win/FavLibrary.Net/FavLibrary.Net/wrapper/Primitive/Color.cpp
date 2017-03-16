#include "../../../../../FavLibrary/Primitive/Color.h"

namespace FavLibrary
{
	ColorBase::ColorBase() { ColorBase_c = new FavLibrary::ColorBase(); }
	ColorBase::~ColorBase() { this->!ColorBase(); }
	ColorBase::!ColorBase() { delete ColorBase_c; }

	ColorRGB::ColorRGB() { ColorRGB_c = new FavLibrary::ColorRGB(); }
	ColorRGB::~ColorRGB() { this->!ColorRGB(); }
	ColorRGB::!ColorRGB() { delete ColorRGB_c; }

	unsigned char ColorRGB::getR() { return ColorRGB_c->getR(); }
	void ColorRGB::setR(unsigned char r) { ColorRGB_c->setR(r); }

	unsigned char ColorRGB::getG() { return ColorRGB_c->getG(); }
	void ColorRGB::setG(unsigned char g) { ColorRGB_c->setG(g); }

	unsigned char ColorRGB::getB() { return ColorRGB_c->getB(); }
	void ColorRGB::setB(unsigned char b) { ColorRGB_c->setB(b); }

	void ColorRGB::setColorRBG(unsigned char r, unsigned char g, unsigned char b)
	{
		ColorRGB_c->setR(r);
		ColorRGB_c->setG(g);
		ColorRGB_c->setB(b);
	}

	ColorRGBA::ColorRGBA() { ColorRGBA_c = new FavLibrary::ColorRGBA(); }
	ColorRGBA::~ColorRGBA() { this->!ColorRGBA(); }
	ColorRGBA::!ColorRGBA() { delete ColorRGBA_c; }

	unsigned char ColorRGBA::getA() { return ColorRGBA_c->getA(); }
	void ColorRGBA::setA(unsigned char a) { ColorRGBA_c->setA(a); }

	void ColorRGBA::setColorRBGA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		ColorRGBA_c->setColorRBG(r, g, b);
		ColorRGBA_c->setA(a);
	}

	ColorGrayscale::ColorGrayscale() { ColorGrayscale_c = new FavLibrary::ColorGrayscale(); }
	ColorGrayscale::~ColorGrayscale() { this->!ColorGrayscale(); }
	ColorGrayscale::!ColorGrayscale() { delete ColorGrayscale_c; }

	unsigned char ColorGrayscale::getGray() { return ColorGrayscale_c->getGray(); }
	void ColorGrayscale::setGray(unsigned char gray) { ColorGrayscale_c->setGray(gray); }

	ColorGrayscale16::ColorGrayscale16() { ColorGrayscale16_c = new FavLibrary::ColorGrayscale16(); }
	ColorGrayscale16::~ColorGrayscale16() { this->!ColorGrayscale16(); }
	ColorGrayscale16::!ColorGrayscale16() { delete ColorGrayscale16_c; }

	unsigned short ColorGrayscale16::getGray() { return ColorGrayscale16_c->getGray(); }
	void ColorGrayscale16::setGray(unsigned short gray) { ColorGrayscale16_c->setGray(gray); }

	ColorCMYK::ColorCMYK() { ColorCMYK_c = new FavLibrary::ColorCMYK(); }
	ColorCMYK::~ColorCMYK() { this->!ColorCMYK(); }
	ColorCMYK::!ColorCMYK() { delete ColorCMYK_c; }

	unsigned char ColorCMYK::getC() { return ColorCMYK_c->getC(); }
	void ColorCMYK::setC(unsigned char c) { ColorCMYK_c->setC(c); }

	unsigned char ColorCMYK::getM() { return ColorCMYK_c->getM(); }
	void ColorCMYK::setM(unsigned char m) { ColorCMYK_c->setM(m); }

	unsigned char ColorCMYK::getY() { return ColorCMYK_c->getY(); }
	void ColorCMYK::setY(unsigned char y) { ColorCMYK_c->setY(y); }

	unsigned char ColorCMYK::getK() { return ColorCMYK_c->getK(); }
	void ColorCMYK::setK(unsigned char k) { ColorCMYK_c->setK(k); }

	void ColorCMYK::setColorCMYK(unsigned char c, unsigned char m, unsigned char y, unsigned char k)
	{
		ColorCMYK_c->setC(c);
		ColorCMYK_c->setM(m);
		ColorCMYK_c->setY(y);
		ColorCMYK_c->setK(k);
	}
}