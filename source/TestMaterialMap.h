#pragma once

#include "../Voxels/include/MaterialMap.h"

// Implements a MaterialMap for the voxel grid.
// The textures are loaded from JSON descriptions
#include <vector>
#include <string>
class MaterialTable : public Voxels::MaterialMap
{
public:
    typedef std::vector<std::string> TextureNames;

    struct TextureProperties
    {
        TextureProperties()
            : UVScale(1)
        {}
        float UVScale;
    };
    typedef std::vector<TextureProperties> TexturePropertiesVec;

    bool Load(const std::string& filename);

    const TextureNames& GetDiffuseTextureList() const;
    const TexturePropertiesVec& GetDiffuseTextureProperties() const;

    virtual Material* GetMaterial(unsigned char id) const override;
    unsigned GetMaterialsCount() const;

private:
    typedef std::vector<Material> MaterialsVec;

    TextureNames m_DiffuseTextures;
    TexturePropertiesVec m_TextureProperties;
    MaterialsVec m_Materials;
};

class TestMaterialTable : public Voxels::MaterialMap
{
public:
    TestMaterialTable();

    virtual Material* GetMaterial(unsigned char id) const override;

private:

    Material* material;
};
