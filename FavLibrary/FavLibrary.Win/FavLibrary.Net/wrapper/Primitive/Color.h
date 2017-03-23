#pragma once
//#include "../../FavLibrary/Metadata.h"
//#include "../../FavLibrary/Primitive/FavPrimitive.h"
#include "../../FavLibrary/Primitive/Color.h"
//#include "../../FavLibrary/FavSettings.h"

using namespace FavLibrary;

namespace FavLibraryDotNet
{
	public enum class ColorMode
	{
		None,
		Grayscale,
		Grayscale16,
		RGB,
		RGBA,
		CMYK,
	};

	public ref class ColorBase
	{
	public:
		ColorBase::ColorBase() { pColorBase = new FavLibrary::ColorBase(); }
		ColorBase::~ColorBase() { delete pColorBase; }

		ColorMode colorMode;

		FavLibrary::Metadata GetMetadata() { return pColorBase->getMetadata(); }

	private:
		FavLibrary::ColorBase* pColorBase;
	};

	//public ref class ColorRGB : public ColorBase
	//{
	//public:
	//	ColorRGB();
	//	~ColorRGB();

	//	ColorMode colorMode = ColorMode::RGB;//ここconstにするとcompile errorが出てた。要確認

	//	void setColorRBG(unsigned char r, unsigned char g, unsigned char b);

	//	//Metadata GetMetadata();
	//	//void SetMetadata(Metadata metadata);

	//	property unsigned char R { unsigned char get(); void set(unsigned char value); }
	//	property unsigned char G { unsigned char get(); void set(unsigned char value); }
	//	property unsigned char B { unsigned char get(); void set(unsigned char value); }

	//private:
	//	//FavLibrary::ColorRGB^ pColorRGB;
	//};

	//public ref class ColorRGBA : public ColorRGB
	//{
	//public:
	//	ColorRGBA();
	//	~ColorRGBA();

	//	ColorMode colorMode = ColorMode::RGBA;

	//	unsigned char getA();
	//	void setA(unsigned char a);

	//	void setColorRBGA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	//private:
	//	unsigned char a;

	//	//FavLibrary::ColorRGBA^ pColorRGBA;
	//};

	//public ref class ColorGrayscale : public ColorBase
	//{
	//public:
	//	ColorGrayscale();
	//	~ColorGrayscale();

	//	ColorMode colorMode = ColorMode::Grayscale;

	//	unsigned char getGray();
	//	void setGray(unsigned char gray);

	//private:
	//	unsigned char gray;

	//	//FavLibrary::ColorGrayscale^ pColorGrayscale;
	//};

	//public ref class ColorGrayscale16 : public ColorGrayscale
	//{
	//public:
	//	ColorGrayscale16();
	//	~ColorGrayscale16();

	//	ColorMode colorMode = ColorMode::Grayscale16;

	//	unsigned short getGray();
	//	void setGray(unsigned short gray);

	//private:
	//	unsigned short gray;

	//	//FavLibrary::ColorGrayscale16^ pColorGrayscale16;
	//};

	//public ref class ColorCMYK : public ColorBase
	//{
	//public:
	//	ColorCMYK();
	//	~ColorCMYK();

	//	ColorMode colorMode = ColorMode::CMYK;

	//	unsigned char getC();
	//	void setC(unsigned char c);

	//	unsigned char getM();
	//	void setM(unsigned char m);

	//	unsigned char getY();
	//	void setY(unsigned char y);

	//	unsigned char getK();
	//	void setK(unsigned char k);

	//	void setColorCMYK(unsigned char c, unsigned char m, unsigned char y, unsigned char k);

	//private:
	//	unsigned char c;
	//	unsigned char m;
	//	unsigned char y;
	//	unsigned char k;

	//	//FavLibrary::ColorCMYK^ pColorCMYK;
	//};

}