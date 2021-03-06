//
// Created by Sean on 3/7/2019.
//

/*
 * MAIN DEFINITIONS FILE - divide as needed
 *
 */
#ifndef GAMEENGINE_MAIN_DEFS_H
#define GAMEENGINE_MAIN_DEFS_H


// Max light definitions - these must remain the same across all files
#define MAX_POINT_LIGHTS 100
#define MAX_SPOT_LIGHTS 100
#define MAX_DIR_LIGHT 10

// Screen Size
#define SCR_WIDTH  3840
#define SCR_HEIGHT 2160

// Render Distance
#define RENDER_DISTANCE_NEAR 0.1f
#define RENDER_DISTANCE_FAR 3000.0f

// Render Window default sizes
#define  RENDER_WINDOW_DEFAULT_X 1920
#define  RENDER_WINDOW_DEFAULT_Y 1080

// Shadow Defines
#define SHADOW_WIDTH  	8192
#define SHADOW_HEIGHT   8192
//#define SHADOW_WIDTH  	1024
//#define SHADOW_HEIGHT   1024

//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
#define STB_IMAGE_IMPLEMENTATION
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#endif //GAMEENGINE_MAIN_DEFS_H
