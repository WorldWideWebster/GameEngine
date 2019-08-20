//
// Created by Sean on 6/11/2019.
//
#include <algorithm>
#include "Image.h"


Image::Image(unsigned int wid, unsigned int len)
{
	this->width = wid;
	this->length = len;
	data = new unsigned char[width * length * 3];
	clearWhite();
}

void Image::clearWhite(void)
{
	std::fill_n(this->data, width * length * 3, 255);
}

unsigned int Image::getWidth(void)
{
	return this->width;
}

unsigned int Image::getLength(void)
{
	return this->length;
}

unsigned char* Image::getData(void)
{
	return this->data;
}