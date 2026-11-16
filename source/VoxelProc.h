#pragma once

#include "Math/SurfaceGeneration/Voxels/src/Aligned.h"
#include "Math/SurfaceGeneration/Voxels/include/VoxelSurface.h"

namespace Voxels
{

struct ProceduralParams
{
    float DimensionFactor;
    float ScaleFactor;

};



class VoxelProc : public VoxelSurface, public Aligned<16>
{
public:
    VoxelProc(const glm::vec3& normal, float d, const ProceduralParams& params);
    virtual ~VoxelProc();

    void GetSurface(float xStart, float xEnd, float xStep,
                            float yStart, float yEnd, float yStep,
                            float zStart, float zEnd, float zStep,
                            float* output,
                            unsigned char* materialId,
                            unsigned char* blend) override;
private:
    glm::vec4 m_plane;
    ProceduralParams m_params;
};
}
