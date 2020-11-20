set(bullet_interface_source_files
        PhysicsIntegration.cpp)
set(bullet_interface_header_files
        CommonRigidBodyBase.h
        PhysicsInterface.h
        PhysicsIntegration.h)

add_library(bullet_interface ${bullet_interface_source_files} ${bullet_interface_header_files})