//
// Created by Sean on 10/8/2019.
//

#ifndef OPENGLSETUP_TEST_SCENES_H
#define OPENGLSETUP_TEST_SCENES_H

#include <memory>
#include "Scene.h"
void toggleFlashLight(void);

void setUpTestScene1(std::shared_ptr<Scene> targetScene);
void doTestScene1(std::shared_ptr<Scene> targetScene);
void setUpTestScene3(std::shared_ptr<Scene> targetScene);
void doTestScene3(std::shared_ptr<Scene> targetScene);
void setUpTestScene4(std::shared_ptr<Scene> targetScene);
void doTestScene4(std::shared_ptr<Scene> targetScene);




#endif //OPENGLSETUP_TEST_SCENES_H
