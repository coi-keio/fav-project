#pragma once

enum ColorMode
{
    None,
	Grayscale,
	Grayscale16,
	RGB,
	RGBA,
	CMYK,
};

class ColorBase
{
public:
	ColorBase();
	~ColorBase();

	ColorMode colorMode;
};

class ColorRGB : public ColorBase
{
public:
	const ColorMode colorMode = RGB;

	unsigned char getR() { return this->r; }
	void setR(unsigned char r) { this->r = r; }

	unsigned char getG() { return this->g; }
	void setG(unsigned char g) { this->g = g; }

	unsigned char getB() { return this->b; }
	void setB(unsigned char b) { this->b = b; }

	void setColorRBG(unsigned char r, unsigned char g, unsigned char b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

private:
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class ColorRGBA : public ColorRGB
{
public:
	const ColorMode colorMode = RGBA;

	unsigned char getA() { return this->a; }
	void setA(unsigned char a) { this->a = a; }

	void setColorRBGA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		setColorRBG(r, g, b);
		this->a = a;
	}

private:
	unsigned char a;
};

class ColorGrayscale : public ColorBase
{
public:
	const ColorMode colorMode = Grayscale;

	unsigned char getGray() { return this->gray; }
	void setGray(unsigned char gray) { this->gray = gray; }

private:
	unsigned char gray;
};

class ColorGrayscale16 : public ColorGrayscale
{
public:
	const ColorMode colorMode = Grayscale16;

	unsigned short getGray() { return this->gray; }
	void setGray(unsigned short gray) { this->gray = gray; }

private:
	unsigned short gray;
};

class ColorCMYK : public ColorBase
{
public:
	const ColorMode colorMode = CMYK;

	unsigned char getC() { return this->c; }
	void setC(unsigned char c) { this->c = c; }

	unsigned char getM() { return this->m; }
	void setM(unsigned char m) { this->m = m; }

	unsigned char getY() { return this->y; }
	void setY(unsigned char y) { this->y = y; }

	unsigned char getK() { return this->k; }
	void setK(unsigned char k) { this->k = k; }

	void setColorCMYK(unsigned char c, unsigned char m, unsigned char y, unsigned char k)
	{
		this->c = c;
		this->m = m;
		this->y = y;
		this->k = k;
	}

private:
	unsigned char c;
	unsigned char m;
	unsigned char y;
	unsigned char k;
};

