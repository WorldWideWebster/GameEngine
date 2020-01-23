//
// Created by Sean on 1/23/2020.
//

#include "NoiseMapViewer.h"


// 3. Show another simple window.
// TODO move to separate file

/*        if (noise_map_viewer)
        {

			ImGui::Begin("Noise Map Viewer", &noise_map_viewer);       // Create a window called "Hello, world!" and append into it.

            if (ImGui::Button("GenNoise"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            {
				int rando = rand()%100;
				nm->reSeed(rando);
				std::cout << rando << std::endl;
				//tri->setHeightMap(nm->getData(), nm->getWidth(), nm->getHeight());
				//m = new Mesh(tri);
			}
            // Set render window position
            ImGui::SetWindowPos("Image Viewer", ImVec2(RENDER_WINDOW_DEFAULT_X, 0), ImGuiCond_FirstUseEver);
            // Set render window size
            ImGui::SetWindowSize("Image Viewer", ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y),
                                 ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y), ImGuiCond_FirstUseEver);
            // Window for rendering scene
            // FIXME: texture doesn't move with window
            ImGui::Image((void *)(uintptr_t)  nm->getTexID(), ImVec2(nm->getWidth(), nm->getHeight()),
                    ImVec2(0,1), ImVec2(1,0), ImColor(255,255,255,255), ImColor(255,255,255,128));
            ImGui::End();
        }*/


// TODO: move terrain to special entity
// Terrain Generation
// Create Noise map
/*
 * FIXME: Texture from this somehow overwrites other textures
	NoiseMap *nm = new NoiseMap;
	// Create texture from noise map
	Texture tx = TextureFromNoiseMap(*nm);
*/