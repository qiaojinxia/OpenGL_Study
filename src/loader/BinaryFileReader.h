//
// Created by cboy on 2022/9/24.
//

#ifndef OPENGL_STUDY_BINARYFILEREADER_H
#define OPENGL_STUDY_BINARYFILEREADER_H

#include <string>

namespace OpenGl_3D {
    class BinaryFileReader {
    public:
        static std::vector<char> open_file(const std::string &filePath);
    };
}

#endif //OPENGL_STUDY_BINARYFILEREADER_H
