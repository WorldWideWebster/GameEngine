//
// Created by Sean on 4/19/2019.
//

#include "HeightMap.h"




/******* EXTERNAL LIBRARIES ********/
// STBI
#include "stb_image.h"


HeightMap::HeightMap(const char *path)
{
    this->read(path);
}


void HeightMap::read(const char *path)
{
    image = stbi_load(path, &width, &height, &nrComponents, 1);
    if (image)
    {
        for(int gy = 0; gy < height; gy++)
        {
            std::vector<unsigned char> heightMapRow;
            for(int gx = 0; gx < width; gx++)
            {
                heightMapRow.push_back(image[width * gy + gx]);
            }
            heights.push_back(heightMapRow);
        }
    }
    else
    {
        fprintf(stderr, "%s\n", stbi_failure_reason());
    }
}