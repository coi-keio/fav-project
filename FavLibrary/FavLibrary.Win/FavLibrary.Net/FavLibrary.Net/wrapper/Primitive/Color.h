#pragma once

#include "../../FavLibrary/Primitive/Color.h"
using namespace System;
using ColorBase_c = FavLibrary::ColorBase;

namespace FavLibraryDotNet
{
	public ref class ColorBase
	{
	public:
		ColorBase();
		~ColorBase();
		!ColorBase();
	private:
	};

	public ref class ColorRGB : public ColorBase
	{
	public:
		ColorRGB();
		~ColorRGB();
		!ColorRGB();

		unsigned char getR();
		void setR(unsigned char r);

		unsigned char getG();
		void setG(unsigned char g);

		unsigned char getB();
		void setB(unsigned char b);

		void setColorRBG(unsigned char r, unsigned char g, unsigned char b);

	private:
		FavLibrary::ColorRGB* ColorRGB_c;
	};

	public ref class ColorRGBA : public ColorRGB
	{
	public:
		ColorRGBA();
		~ColorRGBA();
		!ColorRGBA();

		unsigned char getA();
		void setA(unsigned char a);

		void setColorRBGA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	private:
		FavLibrary::ColorRGBA* ColorRGBA_c;
	};

	public ref  class ColorGrayscale : public ColorBase
	{
	public:
		ColorGrayscale();
		~ColorGrayscale();
		!ColorGrayscale();

		unsigned char getGray();
		void setGray(unsigned char gray);

	private:
		FavLibrary::ColorGrayscale* ColorGrayscale_c;
	};

	public ref  class ColorGrayscale16 : public ColorGrayscale
	{
	public:
		ColorGrayscale16();
		~ColorGrayscale16();
		!ColorGrayscale16();

		unsigned short getGray();
		void setGray(unsigned short gray);

	private:
		FavLibrary::ColorGrayscale16* ColorGrayscale16_c;
	};

	public ref  class ColorCMYK : public ColorBase
	{
	public:
		ColorCMYK();
		~ColorCMYK();
		!ColorCMYK();

		unsigned char getC();
		void setC(unsigned char c);

		unsigned char getM();
		void setM(unsigned char m);

		unsigned char getY();
		void setY(unsigned char y);

		unsigned char getK();
		void setK(unsigned char k);

		void setColorCMYK(unsigned char c, unsigned char m, unsigned char y, unsigned char k);

	private:
		FavLibrary::ColorCMYK* ColorCMYK_c;
	};

}