#pragma once
#include "../FavSettings.h"

namespace FavLibrary
{
	RefEnum ColorMode
	{
		None,
		Grayscale,
		Grayscale16,
		RGB,
		RGBA,
		CMYK,
	};

	RefClass ColorBase
	{
	public:
		ColorBase();
		~ColorBase();

		ColorMode colorMode;

	protected:

#ifdef DotNet
		ColorBase^ pColorBase;
#endif
	};

	RefClass ColorRGB : public ColorBase
	{
	public:
		ColorRGB();
        ColorRGB(unsigned char r_, unsigned char g_, unsigned char b_){r = r_; g = g_; b = b_;};
		~ColorRGB();

		ColorMode colorMode = ColorMode::RGB;//ここconstにするとcompile errorが出てた。要確認

		unsigned char getR();
		void setR(unsigned char r);

		unsigned char getG();
		void setG(unsigned char g);

		unsigned char getB();
		void setB(unsigned char b);

		void setColorRBG(unsigned char r, unsigned char g, unsigned char b);

	protected:
		unsigned char r;
		unsigned char g;
		unsigned char b;

#ifdef DotNet
		ColorRGB^ pColorRGB;
#endif
	};

	RefClass ColorRGBA : public ColorRGB
	{
	public:
		ColorRGBA();
        ColorRGBA(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_){r = r_; g = g_; b = b_; a=a_;};
		~ColorRGBA();

		ColorMode colorMode = ColorMode::RGBA;

		unsigned char getA();
		void setA(unsigned char a);

		void setColorRBGA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	private:
		unsigned char a;

#ifdef DotNet
		ColorRGBA^ pColorRGBA;
#endif
	};

	RefClass ColorGrayscale : public ColorBase
	{
	public:
		ColorGrayscale();
		~ColorGrayscale();

		ColorMode colorMode = ColorMode::Grayscale;

		unsigned char getGray();
		void setGray(unsigned char gray);

	protected:
		unsigned char gray;

#ifdef DotNet
		ColorGrayscale^ pColorGrayscale;
#endif
	};

	RefClass ColorGrayscale16 : public ColorGrayscale
	{
	public:
		ColorGrayscale16();
		~ColorGrayscale16();

		ColorMode colorMode = ColorMode::Grayscale16;

		unsigned short getGray();
		void setGray(unsigned short gray);

	private:
		unsigned short gray;

#ifdef DotNet
		ColorGrayscale16^ pColorGrayscale16;
#endif
	};

	RefClass ColorCMYK : public ColorBase
	{
	public:
		ColorCMYK();
		~ColorCMYK();

		ColorMode colorMode = ColorMode::CMYK;

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

#ifdef DotNet
		ColorCMYK^ pColorCMYK;
#endif
	};

}