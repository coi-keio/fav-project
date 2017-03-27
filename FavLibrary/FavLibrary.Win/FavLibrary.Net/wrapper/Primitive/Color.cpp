#include "Stdafx.h"
#include "Color.h"

using namespace FavLibrary;

namespace FavLibraryDotNet
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ColorRGB::ColorRGB() { pColorRGB = new FavLibrary::ColorRGB(); }
	ColorRGB::ColorRGB(unsigned char r, unsigned char g, unsigned char b) 
	{
		pColorRGB = new FavLibrary::ColorRGB();
		pColorRGB->setColorRBG(r, g, b);
	}
	ColorRGB::~ColorRGB() { delete pColorRGB; }

	void ColorRGB::setColorRBG(ColorRGB color)
	{
		pColorRGB->setColorRBG(color.R, color.G, color.B);
	}
	void ColorRGB::setColorRBG(unsigned char r, unsigned char g, unsigned char b)
	{
		pColorRGB->setColorRBG(r, g, b);
	}

	unsigned char ColorRGB::R::get() { return pColorRGB->getR(); }
	void ColorRGB::R::set(unsigned char value) { return pColorRGB->setR(value); }

	unsigned char ColorRGB::G::get() { return pColorRGB->getG(); }
	void ColorRGB::G::set(unsigned char value) { return pColorRGB->setG(value); }

	unsigned char ColorRGB::B::get() { return pColorRGB->getB(); }
	void ColorRGB::B::set(unsigned char value) { return pColorRGB->setB(value); }

	ColorMode ColorRGB::ColorMode::get() { return FavLibraryDotNet::ColorMode::RGB; }

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ColorRGBA::ColorRGBA() { pColorRGBA = new FavLibrary::ColorRGBA(); }
	ColorRGBA::ColorRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) 
	{
		pColorRGBA = new FavLibrary::ColorRGBA();
		pColorRGBA->setColorRBGA(r, g, b, a);
	}
	ColorRGBA::~ColorRGBA() { delete pColorRGBA; }

	unsigned char ColorRGBA::A::get() { return pColorRGBA->getA(); }
	void ColorRGBA::A::set(unsigned char value) { return pColorRGBA->setA(value); }

	void ColorRGBA::setColorRBGA(ColorRGBA color)
	{
		pColorRGBA->setColorRBGA(color.R, color.G, color.B, color.A);
	}
	void ColorRGBA::setColorRBGA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		pColorRGBA->setColorRBGA(r, g, b, a);
	}

	ColorMode ColorRGBA::ColorMode::get() { return FavLibraryDotNet::ColorMode::RGBA; }

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ColorGrayscale::ColorGrayscale() { pColorGrayscale = new FavLibrary::ColorGrayscale(); }
	ColorGrayscale::ColorGrayscale(unsigned char gray) 
	{ 
		pColorGrayscale = new FavLibrary::ColorGrayscale();
		pColorGrayscale->setGray(gray);
	}
	ColorGrayscale::~ColorGrayscale() { delete pColorGrayscale; }

	unsigned char ColorGrayscale::Gray::get() { return pColorGrayscale->getGray(); }
	void ColorGrayscale::Gray::set(unsigned char value) { return pColorGrayscale->setGray(value); }

	ColorMode ColorGrayscale::ColorMode::get() { return FavLibraryDotNet::ColorMode::Grayscale; }

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ColorGrayscale16::ColorGrayscale16() { pColorGrayscale16 = new FavLibrary::ColorGrayscale16(); }
	ColorGrayscale16::ColorGrayscale16(unsigned short gray)
	{
		pColorGrayscale16 = new FavLibrary::ColorGrayscale16();
		pColorGrayscale16->setGray(gray);
	}
	ColorGrayscale16::~ColorGrayscale16() { delete pColorGrayscale16; }

	unsigned short ColorGrayscale16::Gray::get() { return pColorGrayscale16->getGray(); }
	void ColorGrayscale16::Gray::set(unsigned short value) { return pColorGrayscale16->setGray(value); }

	ColorMode ColorGrayscale16::ColorMode::get() { return FavLibraryDotNet::ColorMode::Grayscale16; }

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ColorCMYK::ColorCMYK() { pColorCMYK = new FavLibrary::ColorCMYK(); }
	ColorCMYK::ColorCMYK(unsigned char c, unsigned char m, unsigned char y, unsigned char k)
	{
		pColorCMYK = new FavLibrary::ColorCMYK();
		pColorCMYK->setColorCMYK(c, m, y, k);
	}
	ColorCMYK::~ColorCMYK() { delete pColorCMYK; }

	unsigned char ColorCMYK::C::get() { return pColorCMYK->getC(); }
	void ColorCMYK::C::set(unsigned char value) { return pColorCMYK->setC(value); }

	unsigned char ColorCMYK::M::get() { return pColorCMYK->getM(); }
	void ColorCMYK::M::set(unsigned char value) { return pColorCMYK->setM(value); }

	unsigned char ColorCMYK::Y::get() { return pColorCMYK->getY(); }
	void ColorCMYK::Y::set(unsigned char value) { return pColorCMYK->setY(value); }

	unsigned char ColorCMYK::K::get() { return pColorCMYK->getK(); }
	void ColorCMYK::K::set(unsigned char value) { return pColorCMYK->setK(value); }

	void ColorCMYK::setColorCMYK(ColorCMYK color)
	{
		pColorCMYK->setColorCMYK(color.C, color.M, color.Y, color.K);
	}
	void ColorCMYK::setColorCMYK(unsigned char c, unsigned char m, unsigned char y, unsigned char k)
	{
		pColorCMYK->setColorCMYK(c, m, y, k);
	}

	ColorMode ColorCMYK::ColorMode::get() { return FavLibraryDotNet::ColorMode::CMYK; }

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}