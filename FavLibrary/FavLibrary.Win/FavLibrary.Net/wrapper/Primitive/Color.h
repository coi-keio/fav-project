#pragma once

#include "../../FavLibrary/Primitive/Color.h"

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

	interface class IColor
	{
	public:
		property FavLibraryDotNet::ColorMode ColorMode { FavLibraryDotNet::ColorMode get(); }
	};

	public ref class ColorRGB : public IColor
	{
	public:
		ColorRGB();
		ColorRGB(unsigned char r, unsigned char g, unsigned char b);
		~ColorRGB();

		void setColorRBG(ColorRGB color);
		void setColorRBG(unsigned char r, unsigned char g, unsigned char b);

		property unsigned char R { unsigned char get(); void set(unsigned char value); }
		property unsigned char G { unsigned char get(); void set(unsigned char value); }
		property unsigned char B { unsigned char get(); void set(unsigned char value); }

		virtual property FavLibraryDotNet::ColorMode ColorMode { FavLibraryDotNet::ColorMode get(); }

	private:
		FavLibrary::ColorRGB* pColorRGB;
	};

	public ref class ColorRGBA : public ColorRGB
	{
	public:
		ColorRGBA();
		ColorRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		~ColorRGBA();

		property unsigned char A { unsigned char get(); void set(unsigned char value); }

		void setColorRBGA(ColorRGBA color);
		void setColorRBGA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

		virtual property FavLibraryDotNet::ColorMode ColorMode { FavLibraryDotNet::ColorMode get() override; }

	private:
		FavLibrary::ColorRGBA* pColorRGBA;
	};

	public ref class ColorGrayscale : public IColor
	{
	public:
		ColorGrayscale();
		ColorGrayscale(unsigned char gray);
		~ColorGrayscale();

		property unsigned char Gray { unsigned char get(); void set(unsigned char value); }

		virtual property FavLibraryDotNet::ColorMode ColorMode { FavLibraryDotNet::ColorMode get(); }

	private:
		FavLibrary::ColorGrayscale* pColorGrayscale;
	};

	public ref class ColorGrayscale16 : public IColor
	{
	public:
		ColorGrayscale16();
		ColorGrayscale16(unsigned short gray);
		~ColorGrayscale16();

		property unsigned short Gray { unsigned short get(); void set(unsigned short value); }

		virtual property FavLibraryDotNet::ColorMode ColorMode { FavLibraryDotNet::ColorMode get(); }

	private:
		FavLibrary::ColorGrayscale16* pColorGrayscale16;
	};

	public ref class ColorCMYK : public IColor
	{
	public:
		ColorCMYK();
		ColorCMYK(unsigned char c, unsigned char m, unsigned char y, unsigned char k);
		~ColorCMYK();

		property unsigned char C { unsigned char get(); void set(unsigned char value); }
		property unsigned char M { unsigned char get(); void set(unsigned char value); }
		property unsigned char Y { unsigned char get(); void set(unsigned char value); }
		property unsigned char K { unsigned char get(); void set(unsigned char value); }
		
		void setColorCMYK(ColorCMYK color);
		void setColorCMYK(unsigned char c, unsigned char m, unsigned char y, unsigned char k);

		virtual property FavLibraryDotNet::ColorMode ColorMode { FavLibraryDotNet::ColorMode get(); }

	private:
		FavLibrary::ColorCMYK* pColorCMYK;
	};

}