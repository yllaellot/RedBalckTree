#include "../include/set_func.h"

int main() 
{
    std::set<int> rb_tree;

    char request;

    int key;
    int key1, key2;

    while (std::cin >> request)
    {
        switch(request)
        {
            case setf::KEY : 
                            if (!(std::cin >> key)) throw "Error reading from input stream\n";

                            rb_tree.insert(key);
                            
                            break;

            case setf::QUERY :
                              if (!(std::cin >> key1 >> key2)) throw "Error reading from input stream\n";

                              std::cout << setf::range_queries(rb_tree, key1, key2) << std::endl;

                              break;

            default :
                      std::cerr << "Error input" << std::endl;
                      return EXIT_FAILURE;
        }

    }

    return EXIT_SUCCESS;
}
