set(imgui_source_files
        imgui.cpp
        imgui_widgets.cpp
        imgui_impl_opengl3.cpp
        imgui_draw.cpp
        imgui_demo.cpp
        imgui_impl_glfw.cpp
        imconfig.h
        imgui.h
        imgui_internal.h
        imgui_impl_opengl3.h
        imgui_impl_glfw.h
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h ../Primitive.cpp ../Primitive.h)

add_library(imgui ${imgui_source_files})