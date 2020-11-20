//
// Created by Sean on 6/11/2019.
//

#ifndef GAMEENGINE_IMAGE_H
#define GAMEENGINE_IMAGE_H

/**
 * @brief Image class to serve as a base class for image storage/manipulation
 */
class Image
{
public:
	Image(unsigned int wid, unsigned int len);
	void clearWhite(void);
	unsigned int getWidth(void);
	unsigned int getLength(void);
	unsigned char *getData(void);
private:
	unsigned int width, length;
	unsigned char *data;
	unsigned int format;
};


#endif //GAMEENGINE_IMAGE_H
