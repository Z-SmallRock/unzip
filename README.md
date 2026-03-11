# unzip
qt和常规C++项目zip压缩包解压

对之前出现在qt中无法使用的问题进行简单的封装
目前只封装了zip的解压
src中有相对应的压缩的源码 readme中有对应的介绍

现在新增了 `toZip` 接口，可直接将指定目录压缩为 zip。

如下对zip的解压使用。


std::string path = "D:\\pdate_dir";
unZip("2.zip", path, [](int index, int count) {
	std::cout << index << "\t" << count << std::endl;
});

toZip("2.zip", path, [](int index, int count) {
	std::cout << index << "\t" << count << std::endl;
});


## CMake 编译

项目现已支持 CMake（仅 Windows，依赖 `Windows.h`）：

```bash
cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build --config Release
```

生成动态库 `gymzip`（导出 `unZip` / `toZip`）。
