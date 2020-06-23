//
//  io.h
//  countdown
//
//  Created by Ian Guest on 16/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef io_h
#define io_h

#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>
#include <vector>

class Io {

public:
    static std::string makeFilePath(const std::string& path,
                                    const std::string& fileName);
    static std::vector<char> getLetters(const std::string& path,
                                        const std::string& fileName);
    static std::vector<std::string> getWords(const std::string& path,
                                             const std::string& fileName);
};

#endif /* io_h */
