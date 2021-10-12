#include "LinAlg.h"
#include "MatrixChainOrder.hpp"  
#include <vector>

using std::vector;
using namespace::LinAlg;

int main(){
    Matrix m({
		 {1,1,1,1},
		 {2,2,2,2},
		 {1,1,1,1},
	});

    Matrix n({
		{1,1,1},
		{1,1,1},
		{1,1,1},
		{1,1,1},
	});

	MatrixChainOrder elem{{30.0, 35.0, 15.0, 5.0, 10.0, 20.0, 25.0}};
	elem.M();
	std::cout << "------------------------" << std::endl;
	elem.S();
	elem.printOptimalParens(1,6);
	putchar('\n');
    return 0;
}