#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<fs::directory_entry> findFiles(std::string path, std::string ext)
{
    std::vector<fs::directory_entry> res;
    for (auto& p : fs::recursive_directory_iterator(path))
    {
        if (p.path().extension() == ext)
            res.push_back(p);
    }
    return res;
}

