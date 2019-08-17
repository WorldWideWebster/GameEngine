//
// Created by Sean on 6/8/2019.
//

#ifndef OPENGLSETUP_NOISEMAP_H
#define OPENGLSETUP_NOISEMAP_H

#include "PerlinNoise.h"
enum noiseType
{
	PERLIN,
	NOISE_COUNTS
};

class NoiseMap
{
public:
	NoiseMap();
	NoiseMap(unsigned int type);
	unsigned char *getData(void);
	unsigned int getWidth(void);
	unsigned int getHeight(void);
	unsigned int getTexID(void);
	void reSeed(int seed);
private:
	unsigned char *data;
	unsigned int width, height;
	unsigned int texID;
	void createTexture(void);
	void doNoise(PerlinNoise pn);
};


#endif //OPENGLSETUP_NOISEMAP_H
