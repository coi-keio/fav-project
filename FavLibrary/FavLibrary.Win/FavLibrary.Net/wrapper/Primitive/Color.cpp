#include "Stdafx.h"
#include "../../../../FavLibrary/Primitive/Color.h"

namespace FavLibrary
{
	ColorBase::ColorBase() { pColorBase = gcnew FavLibrary::ColorBase(); }
	ColorBase::~ColorBase() { delete pColorBase; }

	ColorRGB::ColorRGB() { pColorRGB = gcnew FavLibrary::ColorRGB(); }
	ColorRGB::~ColorRGB() { delete pColorRGB; }

	unsigned char ColorRGB::getR() { return pColorRGB->getR(); }
	void ColorRGB::setR(unsigned char r) { pColorRGB->setR(r); }

	unsigned char ColorRGB::getG() { return pColorRGB->getG(); }
	void ColorRGB::setG(unsigned char g) { pColorRGB->setG(g); }

	unsigned char ColorRGB::getB() { return pColorRGB->getB(); }
	void ColorRGB::setB(unsigned char b) { pColorRGB->setB(b); }

	void ColorRGB::setColorRBG(unsigned char r, unsigned char g, unsigned char b)
	{
		pColorRGB->setR(r);
		pColorRGB->setG(g);
		pColorRGB->setB(b);
	}

	ColorRGBA::ColorRGBA() { pColorRGBA = gcnew FavLibrary::ColorRGBA(); }
	ColorRGBA::~ColorRGBA() { delete pColorRGBA; }

	unsigned char ColorRGBA::getA() { return pColorRGBA->getA(); }
	void ColorRGBA::setA(unsigned char a) { pColorRGBA->setA(a); }

	void ColorRGBA::setColorRBGA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		pColorRGBA->setColorRBG(r, g, b);
		pColorRGBA->setA(a);
	}

	ColorGrayscale::ColorGrayscale() { pColorGrayscale = gcnew FavLibrary::ColorGrayscale(); }
	ColorGrayscale::~ColorGrayscale() { delete pColorGrayscale; }

	unsigned char ColorGrayscale::getGray() { return pColorGrayscale->getGray(); }
	void ColorGrayscale::setGray(unsigned char gray) { pColorGrayscale->setGray(gray); }

	ColorGrayscale16::ColorGrayscale16() { pColorGrayscale16 = gcnew FavLibrary::ColorGrayscale16(); }
	ColorGrayscale16::~ColorGrayscale16() { delete pColorGrayscale16; }

	unsigned short ColorGrayscale16::getGray() { return pColorGrayscale16->getGray(); }
	void ColorGrayscale16::setGray(unsigned short gray) { pColorGrayscale16->setGray(gray); }

	ColorCMYK::ColorCMYK() { pColorCMYK = gcnew FavLibrary::ColorCMYK(); }
	ColorCMYK::~ColorCMYK() { delete pColorCMYK; }

	unsigned char ColorCMYK::getC() { return pColorCMYK->getC(); }
	void ColorCMYK::setC(unsigned char c) { pColorCMYK->setC(c); }

	unsigned char ColorCMYK::getM() { return pColorCMYK->getM(); }
	void ColorCMYK::setM(unsigned char m) { pColorCMYK->setM(m); }

	unsigned char ColorCMYK::getY() { return pColorCMYK->getY(); }
	void ColorCMYK::setY(unsigned char y) { pColorCMYK->setY(y); }

	unsigned char ColorCMYK::getK() { return pColorCMYK->getK(); }
	void ColorCMYK::setK(unsigned char k) { pColorCMYK->setK(k); }

	void ColorCMYK::setColorCMYK(unsigned char c, unsigned char m, unsigned char y, unsigned char k)
	{
		pColorCMYK->setC(c);
		pColorCMYK->setM(m);
		pColorCMYK->setY(y);
		pColorCMYK->setK(k);
	}
}