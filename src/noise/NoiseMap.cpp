//
// Created by Sean on 6/8/2019.
//

#include "NoiseMap.h"
#include "PerlinNoise.h"
#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
NoiseMap::NoiseMap()
{

	// FIXME: large image causes crash, artifacts at beginning
	this->width = 200;
	this->height = 200;
	this->data = new unsigned char[this->width * this->height * 3];
	// TODO: Move all of this into the perlin noise class
	PerlinNoise pn(rand());

	doNoise(pn);
	createTexture();
}

NoiseMap::NoiseMap(unsigned int type)
{

}

void NoiseMap::reSeed(int seed)
{
	PerlinNoise pn(seed);
	GLenum format = GL_RGB;
	doNoise(pn);

	glBindTexture(GL_TEXTURE_2D, this->texID);

	glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, this->data);

}

unsigned char* NoiseMap::getData(void)
{
	return this->data;
}

unsigned int NoiseMap::getWidth(void)
{
	return this->width;
}

unsigned int NoiseMap::getHeight(void)
{
	return this->height;
}

unsigned int NoiseMap::getTexID(void)
{
	return this->texID;
}

void NoiseMap::createTexture(void)

{
	GLenum format = GL_RGB;


	glBindTexture(GL_TEXTURE_2D, this->texID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, this->data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR
	);

}

void NoiseMap::doNoise(PerlinNoise pn)
{
	unsigned int kk = 0;
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for(unsigned int i = 0; i < this->height; i++)
	{     // y
		for(unsigned int j = 0; j < this->width; j++)
		{  // x
			double x = (double)j/((double)this->width);
			double y = (double)i/((double)this->height);

			// Typical Perlin noise
			double n = pn.noise(10 * x, 10 * y, 0.8);;

			// Wood like structure
			//n = 20 * pn.noise(x, y, 0.8);
			//n = n - floor(n);
//
			// Map the values to the [0, 255] interval, for simplicity we use
			// tones of grey
			this->data[kk] = floor(255 * n);
			this->data[kk+1] = floor(255 * n);
			this->data[kk+2] = floor(255 * n);
			kk+=3;
		}
	}
}