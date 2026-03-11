#pragma once

#include <functional>
#include <string>

bool unZip(std::string strZipName, std::string path, std::function<void(int, int)> func);
bool toZip(std::string strZipName, std::string path, std::function<void(int, int)> func);
