#include <Windows.h>  
#include <iostream>
#include <functional>
#include <string> 
#include "unzip.h"

bool unZip(std::string strZipName,std::string path, std::function<void (int,int)> func)
{
	std::string strZipPath = path + "\\" + strZipName;
	int iUnicode = MultiByteToWideChar(CP_ACP, 0, strZipPath.c_str(), strZipPath.length(), NULL, 0);
	WCHAR* pwUnicode = new WCHAR[iUnicode + 2];
	if (pwUnicode)
	{
		ZeroMemory(pwUnicode, iUnicode + 2);
	}

	MultiByteToWideChar(CP_ACP, 0, strZipPath.c_str(), strZipPath.length(), pwUnicode, iUnicode);

	pwUnicode[iUnicode] = '\0';
	pwUnicode[iUnicode + 1] = '\0';

	SetCurrentDirectoryA(path.c_str());

	HZIP hz = OpenZip(pwUnicode, 0);
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
