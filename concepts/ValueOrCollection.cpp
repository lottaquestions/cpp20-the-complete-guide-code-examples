#include "ValueOrCollection.hpp"
#include <vector>


int main(){
    ValueOrCollection o1 = 42;
    o1.print();

    ValueOrCollection o2 = std::vector{1, 2, 3, 4, 5};
    o2.print();

    return 0;
}