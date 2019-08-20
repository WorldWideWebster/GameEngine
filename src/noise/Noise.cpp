//
// Created by Sean on 5/9/2019.
//


float generateNoiseMap(int mapWidth, int mapHeight, float scale)
{
    if(scale <= 0)
    {
        scale = 0.0001f;
    }


    float **noiseMap = new float*[mapHeight];
    for(int i = 0; i < mapHeight; ++i)
    {
        noiseMap[i] = new float[mapWidth];
    }

    for(int y = 0; y < mapHeight; y++)
    {
        for(int x = 0; x < mapWidth; x++)
        {
            float sampleX = x/scale;
            float sampleY = y/scale;

        }
    }
}