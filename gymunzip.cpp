#include <Windows.h>  
#include <iostream>
#include <functional>
#include <string> 
#include <vector>
#include "unzip.h"
#include "zip.h"

namespace {

struct ZipEntryInfo {
	std::string absolutePath;
	std::string zipPath;
	bool isDirectory;
};

std::wstring ansiToWide(const std::string& value)
{
	int iUnicode = MultiByteToWideChar(CP_ACP, 0, value.c_str(), static_cast<int>(value.length()), NULL, 0);
	std::wstring result(iUnicode, L'\0');
	if (iUnicode > 0)
	{
		MultiByteToWideChar(CP_ACP, 0, value.c_str(), static_cast<int>(value.length()), &result[0], iUnicode);
	}
	return result;
}

void collectEntries(const std::string& rootPath, const std::string& currentPath, std::vector<ZipEntryInfo>& entries, const std::string& zipFilePath)
{
	std::string searchPath = currentPath + "\\*";
	WIN32_FIND_DATAA findData;
	HANDLE findHandle = FindFirstFileA(searchPath.c_str(), &findData);
	if (findHandle == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do {
		const std::string name = findData.cFileName;
		if (name == "." || name == "..")
		{
			continue;
		}

		std::string absolutePath = currentPath + "\\" + name;
		if (absolutePath == zipFilePath)
		{
			continue;
		}

		std::string relativePath = absolutePath.substr(rootPath.length() + 1);
		for (char& ch : relativePath)
		{
			if (ch == '\\')
			{
				ch = '/';
			}
		}

		const bool isDirectory = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
		if (isDirectory)
		{
			entries.push_back({ absolutePath, relativePath, true });
			collectEntries(rootPath, absolutePath, entries, zipFilePath);
		}
		else
		{
			entries.push_back({ absolutePath, relativePath, false });
		}
	} while (FindNextFileA(findHandle, &findData));

	FindClose(findHandle);
}

}

bool unZip(std::string strZipName,std::string path, std::function<void (int,int)> func)
{
	std::string strZipPath = path + "\\" + strZipName;
	std::wstring wZipPath = ansiToWide(strZipPath);

	SetCurrentDirectoryA(path.c_str());

	HZIP hz = OpenZip(wZipPath.c_str(), 0);
	if (!hz)
	{
		return false;
	}

	ZIPENTRY ze; GetZipItem(hz, -1, &ze); int numitems = ze.index;
	for (int i = 0; i < numitems; i++)
	{
		GetZipItem(hz, i, &ze);
		UnzipItem(hz, i, ze.name);

		func(i, numitems);
	}
	CloseZip(hz);
	return true;
}

bool toZip(std::string strZipName, std::string path, std::function<void(int, int)> func)
{
	std::string zipFilePath = path + "\\" + strZipName;
	std::wstring wZipPath = ansiToWide(zipFilePath);

	HZIP hz = CreateZip(wZipPath.c_str(), 0);
	if (!hz)
	{
		return false;
	}

	std::vector<ZipEntryInfo> entries;
	collectEntries(path, path, entries, zipFilePath);

	const int count = static_cast<int>(entries.size());
	for (int i = 0; i < count; ++i)
	{
		const ZipEntryInfo& entry = entries[i];
		std::wstring wZipItem = ansiToWide(entry.zipPath);
		ZRESULT result = ZR_OK;
		if (entry.isDirectory)
		{
			result = ZipAddFolder(hz, wZipItem.c_str());
		}
		else
		{
			std::wstring wSrc = ansiToWide(entry.absolutePath);
			result = ZipAdd(hz, wZipItem.c_str(), wSrc.c_str());
		}

		if (result != ZR_OK)
		{
			CloseZip(hz);
			return false;
		}

		func(i, count);
	}

	CloseZip(hz);
	return true;
}

#if 0
void main()
{
	std::string path = "D:\\Myproject\\new_wuhuan\\update_dir";
	unZip("2.zip", path, [](int index, int count) {
		std::cout << index << "\t" << count << std::endl;
	});

	system("pause");
}

#endif
