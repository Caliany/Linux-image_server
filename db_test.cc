#include "db.hpp"

// 单元测试---开发人员参与的测试方式
// C++ 的单元测试框架都有哪些? 
// 1、GTest是Goodle公司发布的一个开源的C/C++ 单元测试框架，包括Chrome Web浏览器
// 2、CppTest是一个功能全面的测试框架
// 3、CppUnit是一个基于LGPL的开源项目
// 4、CppTest是一个C++的单元测试框架
void TestImageTable() {
  // 创建一个 ImageTable 类, 去调用其中的方法, 验证结果
  Json::StyledWriter writer;
  MYSQL* mysql = image_system::MySQLInit();
  image_system::ImageTable image_table(mysql);
  bool ret = false;

  // 1. 插入数据
  Json::Value image;
  image["image_name"] = "test.png";
  image["size"] = 1024;
  image["upload_time"] = "2019/08/28";
  image["md5"] = "abcdef";
  image["type"] = "png";
  image["path"] = "data/test.png";
  ret = image_table.Insert(image);
  printf("ret = %d\n", ret);

  // 2. 查找所有图片信息
  Json::Value images;
  ret = image_table.SelectAll(&images);
  printf("ret = %d\n", ret);
  printf("%s\n", writer.write(images).c_str());

  /*
  // 3. 查找指定图片信息
  Json::Value image;
  ret = image_table.SelectOne(1, &image);
  printf("ret = %d\n", ret);
  printf("%s\n", writer.write(image).c_str());
*/
  // 4. 删除指定图片
  ret = image_table.Delete(1);
  printf("ret = %d\n", ret);

  image_system::MySQLRelease(mysql);
}

int main() {
  TestImageTable();
  return 0;
}
