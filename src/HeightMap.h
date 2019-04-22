//
// Created by Sean on 4/19/2019.
//

#ifndef OPENGLSETUP_HEIGHTMAP_H
#define OPENGLSETUP_HEIGHTMAP_H
// STD Library Includes
#include <string>
#include <vector>



class HeightMap
{
public:
    /*************CONSTRUCTORS****************/
    HeightMap(const char *path = "../resources/heightmapc.png");


    /************UTILITY FUNCTIONS***********/
    void read(const char *path);

    /***************GETTERS******************/
    inline int getHeight(void){return this->height;}
    inline std::vector<std::vector<unsigned char>> getHeights(void){return this->heights;}

private:
    int width, height;
    int nrComponents;
    unsigned char *image;
    std::vector<std::vector<unsigned char>> heights;
};


#endif //OPENGLSETUP_HEIGHTMAP_H
