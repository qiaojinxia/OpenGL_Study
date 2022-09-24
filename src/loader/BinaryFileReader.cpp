//
// Created by cboy on 2022/9/24.
//

#include <fstream>
#include <iostream>
#include <vector>
#include "BinaryFileReader.h"
namespace OpenGl_3D{
    std::vector<char> BinaryFileReader::open_file(const std::string &filePath) {
        auto res = std::vector<char>();
        char buffer[1024];
        std::ifstream ifs(filePath, std::ios::binary);
        if (!ifs.is_open())
        {
            std::cout << "read fail." << std::endl;
            return res;
        }
        while (!ifs.eof())
        {
            ifs.read(buffer , sizeof(char) * 1024);
            for(int i = 0; i < sizeof(buffer); i++){
                res.push_back(buffer[i]);
            }
        }
        ifs.close();
        return res;
    }
}