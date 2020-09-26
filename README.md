# unzip
qt和常规C++项目zip压缩包解压

对之前出现在qt中无法使用的问题进行简单的封装
目前只封装了zip的解压
src中有相对应的压缩的源码 readme中有对应的介绍

如下对zip的解压使用。


std::string path = "D:\\pdate_dir";
unZip("2.zip", path, [](int index, int count) {
	std::cout << index << "\t" << count << std::endl;
});
