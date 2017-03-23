#pragma once
#include "../FavSettings.h"
#include "../Metadata.h"
#include "FavPrimitive.h"

namespace FavLibrary
{
	enum class __declspec(dllexport) ColorMode
	{
		None,
		Grayscale,
		Grayscale16,
		RGB,
		RGBA,
		CMYK,
	};

	class __declspec(dllexport) ColorBase : public MetadataObject, FavPrimitive
	{
	public:
		ColorBase();
		~ColorBase();

		ColorMode colorMode;

	private:
	};

	class __declspec(dllexport) ColorRGB : public ColorBase
	{
	public:
		ColorRGB();
		~ColorRGB();

		ColorMode colorMode = ColorMode::RGB;//ここconstにするとcompile errorが出てた。要確認

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

	class __declspec(dllexport) ColorRGBA : public ColorRGB
	{
	public:
		ColorRGBA();
		~ColorRGBA();

		ColorMode colorMode = ColorMode::RGBA;

		unsigned char getA();
		void setA(unsigned char a);

		void setColorRBGA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	private:
		unsigned char a;
	};

	class __declspec(dllexport) ColorGrayscale : public ColorBase
	{
	public:
		ColorGrayscale();
		~ColorGrayscale();

		ColorMode colorMode = ColorMode::Grayscale;

		unsigned char getGray();
		void setGray(unsigned char gray);

	private:
		unsigned char gray;
	};

	class __declspec(dllexport) ColorGrayscale16 : public ColorGrayscale
	{
	public:
		ColorGrayscale16();
		~ColorGrayscale16();

		ColorMode colorMode = ColorMode::Grayscale16;

		unsigned short getGray();
		void setGray(unsigned short gray);

	private:
		unsigned short gray;
	};

	class __declspec(dllexport) ColorCMYK : public ColorBase
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
	};

}