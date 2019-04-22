//
// Created by Sean on 11/16/2018.
//

/*
 *     // world space positions of our cubes
    srand(time(NULL));
    float x = 0, y = 0, z = 0;
    int direction =0, last = 0;
    glm::vec3 cubePositions[1000];
    for(int i = 1; i < 1000; i++)
    {

        while(direction == last)
            direction = rand() % 6;

        switch(direction)
        {
            // left
            case 0:
                x -= 1.0f;
                break;
            case 1:
                x+=1.0f;
                break;
            case 2:
                y-=1.0f;
                break;
            case 3:
                y+=1.0f;
                break;
            case 4:
                z-=1.0f;
                break;
            case 5:
                z+=1.0f;
                break;
        }

        cubePositions[i] = glm::vec3(x, y, z);
        last = direction;
    }
 */