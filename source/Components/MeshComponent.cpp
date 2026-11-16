#include "MeshComponent.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "../config.h"
namespace Cosmo
{
namespace Components
{

//------------------------------------------------------------------------------

Mesh::Mesh()
{}

//------------------------------------------------------------------------------

bool Mesh::loadMesh(const std::string &filepath)
{
    clear();

    std::string filename = MODEL_DIR;
    filename += filepath;
    bool ret = false;
    Assimp::Importer importer;

    const aiScene* pScene = importer.ReadFile(filename.c_str(),
                                              aiProcess_Triangulate |
                                              aiProcess_GenSmoothNormals |
                                              aiProcess_FlipUVs |
                                              aiProcess_JoinIdenticalVertices);

    if(pScene)
    {
        ret = initFromScene(pScene,filename);
    }
    else
    {
        std::cout << "Error parsing: " << filename << " " << importer.GetErrorString() << std::endl;
    }


    return ret;
}

//------------------------------------------------------------------------------

bool Mesh::initFromScene(const aiScene *pScene,
                         const std::string &filepath)
{
    m_entries.resize(pScene->mNumMeshes);
    m_textures.resize(pScene->mNumMaterials);

    for(unsigned int i = 0; i < m_entries.size();++i)
    {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        initMesh(i,paiMesh);
    }

    return initMaterials(pScene, filepath);
}

//------------------------------------------------------------------------------

void Mesh::initMesh(unsigned int index,
                    const aiMesh *paiMesh)
{
    m_entries[index].materialIndex = paiMesh->mMaterialIndex;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    const aiVector3D zero(0.0f,0.0f,0.0f);

    for(unsigned int i = 0; i < paiMesh->mNumVertices;++i)
    {
        const aiVector3D* pPos = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal = paiMesh->mNormals ? &(paiMesh->mNormals[i]) : &zero;
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &zero;

        Vertex v;
        v.position = glm::vec3(pPos->x,pPos->y,pPos->z);
        v.texCoords = glm::vec2(pTexCoord->x,pTexCoord->y);
        v.normal = glm::vec3(pNormal->x,pNormal->y,pNormal->z);
        v.color = glm::vec3(1.0f,1.0f,1.0f);

        vertices.push_back(v);
    }

    for(unsigned int i = 0; i < paiMesh->mNumFaces;++i)
    {
        const aiFace& face = paiMesh->mFaces[i];
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }

    std::cout << index << std::endl;
    m_entries[index].init(vertices,indices);
}

//------------------------------------------------------------------------------

bool Mesh::initMaterials(const aiScene *pScene,
                         const std::string &filepath)
{
    return true;
    //            std::string::size_type SlashIndex = filepath.find_last_of("/");
    //            std::string dir;

    //            if (SlashIndex == std::string::npos) {
    //                dir = ".";
    //            }
    //            else if (SlashIndex == 0) {
    //                dir = "/";
    //            }
    //            else {
    //                dir = filepath.substr(0, SlashIndex);
    //            }

    //            bool Ret = true;

    //            for(unsigned int i = 0; i < pScene->mNumMaterials;++i)
    //            {
    //                const aiMaterial* pMaterial = pScene->mMaterials[i];

    //                m_textures[i] = 0;

    //                if(pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    //                {
    //                    aiString path;

    //                    if(pMaterial->GetTexture(aiTextureType_DIFFUSE,
    //                                             0,
    //                                             &path,
    //                                             nullptr,
    //                                             nullptr,
    //                                             nullptr,
    //                                             nullptr,
    //                                             nullptr) == AI_SUCCESS)
    //                    {
    //                        std::string fullpath = dir + "/" + path.data;

    ////                        m_textures[i] = new Texture(GL_TEXTURE_2D, fullpath.c_str());
    //                    }
    //                }
    //            }
}

//------------------------------------------------------------------------------

void Mesh::render()
{
    for (unsigned int i = 0 ; i < m_entries.size() ; i++)
    {

        glBindVertexArray(m_entries[i].VAO);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
//        glBindBuffer(GL_ARRAY_BUFFER, m_entries[i].VB);

//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_entries[i].IB);

        //                const unsigned int MaterialIndex = m_entries[i].MaterialIndex;

        //                if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) {
        //                    m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
        //                }

        glDrawElements(GL_TRIANGLES, m_entries[i].numIndices, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }


}

//------------------------------------------------------------------------------

void Mesh::clear()
{
    m_entries.clear();
    m_textures.clear();
}

//------------------------------------------------------------------------------

Mesh::MeshEntry::MeshEntry()
{
    VB = 0;
    IB = 0;
    numIndices  = 0;
    materialIndex = INVALID_MATERIAL;

}

//------------------------------------------------------------------------------

Mesh::MeshEntry::~MeshEntry()
{
    if(VB)
    {
        glDeleteBuffers(1,&VB);
    }
    if(IB)
    {
        glDeleteBuffers(1,&IB);
    }
}

//------------------------------------------------------------------------------

bool Mesh::MeshEntry::init(const std::vector<Vertex> &vertices,
                           const std::vector<unsigned int> &indices)
{
    std::cout << "init "<< std::endl;
    numIndices = indices.size();

    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VB);
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)32);

    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);
    glBindVertexArray(0);

    std::cout << "end init" << std::endl;
    return true;
}

//------------------------------------------------------------------------------

} //namespace Components
} //namespace Cosmo
