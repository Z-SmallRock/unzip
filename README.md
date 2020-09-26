# unzip
qt和常规C++项目zip压缩包解压

目前只处理了常规解压zip。


std::string path = "D:\\pdate_dir";
	unZip("2.zip", path, [](int index, int count) {
		std::cout << index << "\t" << count << std::endl;
	});
