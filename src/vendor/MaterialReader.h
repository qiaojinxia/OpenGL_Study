//
// Created by cboy on 2022/9/8.
//

#ifndef OPENGL_STUDY_MATERIALREADER_H
#define OPENGL_STUDY_MATERIALREADER_H
#include "vector"
#include "map"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
namespace Reader{
    class MaterialReader {
    public:
        MaterialReader(const char * filePath);
        std::map<std::string,std::vector<float>> ma;
        std::map<int,std::string> maIndex;
    public:
        glm::vec3 GetAmbient(const char * materialName) const;
        glm::vec3 GetDiffuse(const char * materialName) const;
        glm::vec3 GetSpecular(const char * materialName) const;
        glm::mediump_float_t  GetShininess(const char * materialName) const;
    };


}


#endif //OPENGL_STUDY_MATERIALREADER_H
