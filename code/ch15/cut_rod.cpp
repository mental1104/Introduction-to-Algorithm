#include "cut_rod.hpp"
#include <string>
using namespace::std;

int main(int argc, char** argv){
    if(argc!=2){
        printf("Usage: %s <method>(naive, memoized, bottomup)\n", argv[0]);
        return 0;
    }

    Method m;
    string method{argv[1]};

    if(method == "naive")
        m = Method::NAIVE;
    else if(method == "memoized")
        m = Method::MEMOIZED;
    else if(method == "bottomup")
        m = Method::BOTTOMUP;

    std::vector<int> p{0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
#ifdef DEBUG
    std::cout << CutRod::calculate(p, 1, m) << std::endl;
    std::cout << CutRod::calculate(p, 2, m) << std::endl;
    std::cout << CutRod::calculate(p, 3, m) << std::endl;
    std::cout << CutRod::calculate(p, 4, m) << std::endl;
    std::cout << CutRod::calculate(p, 5, m) << std::endl;
    std::cout << CutRod::calculate(p, 6, m) << std::endl;
    std::cout << CutRod::calculate(p, 7, m) << std::endl;
    std::cout << CutRod::calculate(p, 8, m) << std::endl;
    std::cout << CutRod::calculate(p, 9, m) << std::endl;
#endif
    std::cout << CutRod::calculate(p, 10, m) << std::endl;
    return 0;
}