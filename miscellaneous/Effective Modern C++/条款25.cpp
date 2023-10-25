#include <alloca.h>
#include <algorithm>
#include <boost/type_index.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

class Data {};
class Entity {
   public:
    template <typename T>
    void setName(T&& newName) {
        name = std::move(newName);
    }

   private:
    std::string name;
    std::shared_ptr<Data> ptr;
};
std::string getEntityName();
int main() {
    Entity e;
    auto n = getEntityName();
    e.setName(n);
}