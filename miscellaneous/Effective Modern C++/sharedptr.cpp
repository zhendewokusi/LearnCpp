#include <memory>
#include <vector>
class Widget{
};
auto customDeleter1 = [](Widget * pw){};
auto customDeleter2 = [](Widget * pw){};

//自定义析构器不会改变shared_ptr的尺寸
std::shared_ptr<Widget> pw1(new Widget,customDeleter1);
std::shared_ptr<Widget> pw2(new Widget,customDeleter2);

std::vector<std::shared_ptr<Widget>> vpw{pw1,pw2};
