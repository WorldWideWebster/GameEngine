set(bullet_interface_source_files
        SimplePhysicsIntegration.cpp
#        PhysicsIntegration.cpp

        )
set(bullet_interface_header_files
        SimplePhysicsIntegration.h
#        CommonRigidBodyBase.h
#        PhysicsInterface.h
#        PhysicsIntegration.h

        )

add_library(bullet_interface ${bullet_interface_source_files} ${bullet_interface_header_files})
target_link_libraries(bullet_interface ${BULLET_DYNAMICS_LIBRARY} ${BULLET_COLLISION_LIBRARY} ${BULLET_MATH_LIBRARY})