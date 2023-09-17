#include <iostream>
#include <memory>


// 尽可能避免使用裸指针传递给 std::shared_ptr 的构造函数
class Entity {};
auto Del = [](Entity* pw) { delete pw; };
int main_1() {
    auto pw = new Entity;
    std::shared_ptr<Entity> sharedptr1(pw,Del);
    std::shared_ptr<Entity> sharedptr2(pw,Del);


// 如果使用自定义析构器就无法使用 std::make_shared
    std::shared_ptr<Entity> sharedptr3(new Entity,Del);
    std::shared_ptr<Entity> sharedptr4(sharedptr3);

// 这样就会尽可能避免 double free
    return 0;
}



