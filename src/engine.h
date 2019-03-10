//
// Created by Sean on 12/4/2018.
//

#ifndef ENGINE_H
#define ENGINE_H



class Engine
{
private:
    bool isRunning;

    Engine();
    void run();
    void render();
public:
    void start();
    void stop();
    void main();
};


#endif //ENGINE_H
