#include "my_shared_ptr.h"
#include <iostream>
#include <memory>

int main()
{
    my_shared_ptr<int> sp1(new int(42));
    std::cout << "sp1 use_count: " << sp1.use_count() << "\n";
    my_shared_ptr<int> sp2 = sp1;
    std::cout << "sp2 use_count: " << sp2.use_count() << "\n";
    std::cout << "sp1 use_count after sp2 goes out of scope: " << sp1.use_count() << "\n";
    return 0;
}
