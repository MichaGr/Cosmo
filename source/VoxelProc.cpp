#include "Math/SurfaceGeneration/Voxels/src/stdafx.h"
#include "VoxelProc.h"

#include "glm/glm.hpp"
#include "glm/gtc/noise.hpp"

namespace Voxels
{

VoxelProc::VoxelProc(const glm::vec3& normal, float d, const ProceduralParams& params)
    : m_plane(glm::vec4(normal.x,normal.y,normal.z,d)),
      m_params(params)
{
    m_plane = glm::normalize(m_plane);
}

VoxelProc::~VoxelProc()
{

}

void VoxelProc::GetSurface(float xStart, float xEnd, float xStep,
                           float yStart, float yEnd, float yStep,
                           float zStart, float zEnd, float zStep,
                           float *output,
                           unsigned char *materialId,
                           unsigned char *blend)
{
    auto id = 0;
    static const int DFACT = 2;

    for (auto z = zStart / DFACT; z < zEnd / DFACT; z += zStep / DFACT)
    {
        for (auto y = yStart / DFACT; y < yEnd / DFACT; y += yStep / DFACT)
        {
            for (auto x = xStart / DFACT; x < xEnd / DFACT; x += xStep / DFACT)
            {
                glm::vec4 point = glm::vec4(x, y, z, 1);
//				auto density = XMVectorGetX(XMPlaneDot(m_plane, point));
                //TODO: suche plane dot equ aus directx in glm, oder selbst schreiben
                auto density = glm::dot(m_plane,point);
                density += glm::perlin(glm::vec3(
                    x * m_params.DimensionFactor,
                    y * m_params.DimensionFactor,
                    z * m_params.DimensionFactor)) * m_params.ScaleFactor * 4;

                output[id] = density;
                if (materialId != nullptr)
                {
                    materialId[id] = 0;
                    blend[id] = 0;
                }
                ++id;
            }
        }
    }
}

}
