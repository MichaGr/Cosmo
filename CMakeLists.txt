cmake_minimum_required(VERSION 3.1)

project(CosmoLib)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(glm-0.9.9.3)
add_subdirectory(external)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/libs/glew")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/libs/glew/lib/Release/x64")

set(CMAKE_CONFIGURATION_TYPES  "Debug;Release")

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

find_package(GLEW REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(BULLET COMPONENTS LinearMath REQUIRED)

include_directories(${BULLET_INCLUDE_DIR})

#set(SFML_STATIC_LIBRARIES TRUE)
#set(SFML_DIR "C:/libs/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window audio system REQUIRED)
find_package(OpenMP)

#set path to shader FILES
set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets/" CACHE PATH "Path to assets")

if(WIN32)
        string(REPLACE "/" "\\\\" ASSETS_DIR ${ASSETS_DIR})
endif(WIN32)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/config.h"
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/Components")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/EntitySpawner")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/Systems")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/EventManager")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/EventManager/Events")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualMarchingCubes/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/Math/Voxels/include")
include_directories("${ASSETS_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/glm-0.9.9.3")
include_directories(${ASSIMP_INCLUDE_DIRS})

include_directories(${GLEW_INCLUDE_DIRS})

set(header_files "${CMAKE_CURRENT_SOURCE_DIR}/source/Forward.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Constants.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/utils.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Game.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/World.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/SpatialDivision.h"
		         "${CMAKE_CURRENT_SOURCE_DIR}/source/VoxelProc.h"
                 "${CMAKE_CURRENT_SOURCE_DIR}/source/TestMaterialMap.h"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Terrain/Chunk.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Terrain/ChunkReducer.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Terrain/ChunkMeshCreator.h"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Terrain/utils.h"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Memory/BasePool.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Memory/Pool.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Memory/PoolManager.h"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/Program.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/Uniform.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/utils.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/GBuffer.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/Buffer.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/Pipeline.h"


				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/Lighting/BaseLight.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/Lighting/DirectionalLight.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/Lighting/PointLight.h"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/Component.h"
				# "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/ActiveComponent.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/ColorComponent.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/PositionComponent.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/ScaleComponent.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/ForwardComponent.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/CameraComponent.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/ViewComponent.h"
				 #"${CMAKE_CURRENT_SOURCE_DIR}/source/Components/RenderableComponent.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/RotationComponent.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/VelocityComponent.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/OnGroundComponent.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/ColliderComponent.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/MeshComponent.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/TransformationMatrixComponent.h"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/Noise/PerlinNoise.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/Noise/SimplexNoise.h"

                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualMarchingCubes/dualmc.h"

                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/include/Declarations.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/include/Grid.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/include/Library.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/include/MaterialMap.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/include/Polygonizer.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/include/Structs.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/include/Version.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/include/Voxels.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/include/VoxelSurface.h"

                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/src/Aligned.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/src/Logger.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/src/Memory.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/src/stdafx.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/src/StdAllocatorAligned.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/src/TransVoxelImpl.h"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/src/VoxelGrid.h"

                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualContouring/catch.hpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualContouring/Settings.hpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualContouring/math/Int.hpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualContouring/math/Math.hpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualContouring/math/Solver.hpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualContouring/math/Vec2.hpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualContouring/math/Vec3.hpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualContouring/util/Array3D.hpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualContouring/vol/Contouring.hpp"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/System.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/InputSystem.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/PhysicsSystem.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/RenderSystem.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/ViewSystem.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/MoveForwardSystem.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/CollisionSystem.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/CollisionHandlerSystem.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/UpdateBoundingBoxesSystem.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/TerrainSpawnerSystem.h"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/EntitySpawner/EntitySpawner.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/EntitySpawner/PlayerSpawner.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/EntitySpawner/TerrainSpawner.h"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/EventManager/EventQueue.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/EventManager/EventHandler.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/EventManager/Events/Event.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/EventManager/Events/CollisionEvent.h")

set(source_files    "${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/source/utils.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/source/Game.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/source/World.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/source/SpatialDivision.cpp"

                    "${CMAKE_CURRENT_SOURCE_DIR}/source/VoxelProc.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/source/TestMaterialMap.cpp"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Terrain/Chunk.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Terrain/ChunkReducer.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Terrain/ChunkMeshCreator.cpp"

                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Memory/BasePool.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Memory/Pool.cpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Memory/PoolManager.cpp"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/Program.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/Uniform.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/utils.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/GBuffer.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/Buffer.cpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Rendering/Pipeline.cpp"

        #                        "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/ActiveComponent.cpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/ColorComponent.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/PositionComponent.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/ScaleComponent.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/ForwardComponent.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/CameraComponent.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/ViewComponent.cpp"
        #                        "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/RenderableComponent.cpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/RotationComponent.cpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/VelocityComponent.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/OnGroundComponent.cpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/ColliderComponent.cpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Components/MeshComponent.cpp"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/Noise/PerlinNoise.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/Noise/SimplexNoise.cpp"


                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualContouring/math/Math.cpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualContouring/math/Solver.cpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/DualContouring/vol/Contouring.cpp"

                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/src/Memory.cpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/src/stdafx.cpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/src/TransVoxelImpl.cpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/src/VoxelGrid.cpp"
                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Math/SurfaceGeneration/Voxels/src/Voxels.cpp"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/EntitySpawner/PlayerSpawner.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/EntitySpawner/TerrainSpawner.cpp"

                                 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/System.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/InputSystem.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/PhysicsSystem.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/RenderSystem.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/ViewSystem.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/CollisionSystem.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/CollisionHandlerSystem.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/UpdateBoundingBoxesSystem.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/MoveForwardSystem.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/Systems/TerrainSpawnerSystem.cpp"

				 "${CMAKE_CURRENT_SOURCE_DIR}/source/EventManager/EventQueue.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/EventManager/EventHandler.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/EventManager/Events/Event.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/source/EventManager/Events/CollisionEvent.cpp")

if(MSVC)
macro(GroupSources curdir)

    file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

    foreach(child ${children})

           if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})

                   GroupSources(${curdir}/${child})

           else()

                   string(REPLACE "/" "\\" groupname ${curdir})

           # I would like to call the src root folder in a different name,
 #only in visual studio 
# (not mandatory requirement)

                    string(REPLACE "src" "Common" groupname ${groupname})

             source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})

           endif()

    endforeach()

endmacro()

GroupSources(source)
endif(MSVC)

include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
        unset(flag_supported CACHE)
    endif()
endfunction()

# example usage
enable_cxx_compiler_flag_if_supported("-Wall")
enable_cxx_compiler_flag_if_supported("-Wextra")
enable_cxx_compiler_flag_if_supported("-pedantic")
enable_cxx_compiler_flag_if_supported("-O3")

add_executable(${PROJECT_NAME} config.h.in ${header_files} ${source_files})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} GLEW::GLEW sfml-graphics sfml-audio sfml-system sfml-window OpenMP::OpenMP_CXX ${ASSIMP_LIBRARIES} ${BULLET_LIBRARIES})
