#include <iostream>


void GetLastDuplicate(int arr[],int n){
     for(int i = n-1;i>0;i--){
        if(arr[i] == arr[i-1]){
        std::cout << "Index:"<<i<<"Numb:"<<arr[i];
        return; 
        }
    }
    std::cout << "NULL Duplicate Numb" << std::endl;
}
int main(){
    int arr[] = {1, 5, 5, 6, 6, 7, 9};
    int range = sizeof(arr)/sizeof(arr[0]);
    GetLastDuplicate(arr, range);

}
