#pragma once

#include "../FavSettings.h"

namespace FavLibrary
{
	enum ColorMode
	{
		None,
		Grayscale,
		Grayscale16,
		RGB,
		RGBA,
		CMYK,
	};

	DllExport class ColorBase
	{
	public:
		ColorBase();
		~ColorBase();

		ColorMode colorMode;
	};

	DllExport class ColorRGB : public ColorBase
	{
	public:
		ColorMode colorMode = RGB;//ここconstにするとcompile errorが出てた。要確認

		unsigned char getR();
		void setR(unsigned char r);

		unsigned char getG();
		void setG(unsigned char g);

		unsigned char getB();
		void setB(unsigned char b);

		void setColorRBG(unsigned char r, unsigned char g, unsigned char b);

	private:
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	DllExport class ColorRGBA : public ColorRGB
	{
	public:
		ColorMode colorMode = RGBA;

		unsigned char getA();
		void setA(unsigned char a);

		void setColorRBGA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	private:
		unsigned char a;
	};

	DllExport class ColorGrayscale : public ColorBase
	{
	public:
		ColorMode colorMode = Grayscale;

		unsigned char getGray();
		void setGray(unsigned char gray);

	private:
		unsigned char gray;
	};

	DllExport class ColorGrayscale16 : public ColorGrayscale
	{
	public:
		ColorMode colorMode = Grayscale16;

		unsigned short getGray();
		void setGray(unsigned short gray);

	private:
		unsigned short gray;
	};

	DllExport class ColorCMYK : public ColorBase
	{
	public:
		ColorMode colorMode = CMYK;

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
		unsigned char c;
		unsigned char m;
		unsigned char y;
		unsigned char k;
	};

}