#include <iostream>
#include <unordered_map>

int main(){
	std::unordered_map<std::string,int> my_map;
	my_map["YuanFang"] = 18;
	my_map["Math"] = 99;
	my_map["yuanfang"] = 18;
	my_map["awa	"] = 66;
	my_map["dhwuahgdwa"] = 64164;
	for(auto x: my_map ){
		std::cout << x.first<< std::endl;
	}

}
