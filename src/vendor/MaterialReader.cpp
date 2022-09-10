//
// Created by cboy on 2022/9/8.
//

#include <fstream>
#include "MaterialReader.h"
#include "iostream"


void Tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters)
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

namespace Reader{
    MaterialReader::MaterialReader(const char * filePath){
        ma = std::map<std::string,std::vector<float>>();
        std::ifstream fin;
        fin.open(filePath, std::ios::in);
        if (!fin.is_open())
        {
            std::cout << "can't find file！" << std::endl;
            return;
        }
        std::string buff;
        int i1 = 0;
        while (getline(fin, buff))
        {
            std::cout << buff<< std::endl;
            std::vector<std::string>tokens;
            Tokenize(buff, tokens, "\t");
            auto tmp  = std::vector<float>();
            for( int i = 1; i < tokens.size() ; i++ )
            {
                auto v = std::stof(tokens[i]);
                tmp.push_back(v);
            }
            maIndex[i1] = tokens[0].c_str();
            ma[tokens[0]] = tmp;
            i1++ ;
        }
        fin.close();
    }

    glm::vec3 MaterialReader::GetAmbient(const char * materialName) const {
        auto iter = ma.find(materialName);
        if (iter == ma.end())
            assert(0);
        return glm::vec3(iter->second[0],iter->second[1],iter->second[2]);
    }

    glm::vec3 MaterialReader::GetDiffuse(const char * materialName) const {
        auto iter = ma.find(materialName);
        if (iter == ma.end())
            assert(0);
        return glm::vec3(iter->second[3],iter->second[4],iter->second[5]);
    }

    glm::vec3 MaterialReader::GetSpecular(const char * materialName) const {
        auto iter = ma.find(materialName);
        if (iter == ma.end())
            assert(0);
        return glm::vec3(iter->second[6],iter->second[7],iter->second[8]);
    }

    glm::mediump_float_t MaterialReader::GetShininess(const char * materialName) const {
        auto iter = ma.find(materialName);
        if (iter == ma.end())
            assert(0);
        return iter->second[9];
    }
}