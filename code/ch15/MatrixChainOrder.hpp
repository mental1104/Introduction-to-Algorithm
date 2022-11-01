#include "./LinAlg.h"
#include <cassert>
#include <climits>
#include <vector>
#include <memory>
#include <cstdio>
#include <cfloat>

using std::vector;
using std::shared_ptr;
using std::make_shared;

using namespace::LinAlg;

class MatrixChainOrder {
public:
    MatrixChainOrder(const vector<double>& p);
    ~MatrixChainOrder(){}
    LinAlg::Matrix multiply(const LinAlg::Matrix& A, const LinAlg::Matrix& B);
    void printOptimalParens(size_t i, size_t j);
    void M();
    void S();

private:
    LinAlg::Matrix m;
    LinAlg::Matrix s;
    vector<double> p;
};

MatrixChainOrder::MatrixChainOrder(const vector<double>& p):p(p){
    size_t n = p.size();
    
    m.resize(n+1, n+1);
    s.resize(n+1, n+1);
    for(int i = 1; i <= n; i++)
        m.at(i, i) = 0;//Initialize the diagonal.
    
    for(int l = 2; l < n; l++){
        for(int i = 1; i <= n-l+1; i++){
            int j = i+l-1; 
            m.at(i, j) = DBL_MAX;
            for(int k = i; k <= j-1; k++){
                double q = m.at(i, k) + m.at(k+1, j) + p[i-1]*p[k]*p[j];
                if(q < m.at(i,j) || m.at(i,j) == -1){
                    m.at(i, j) = q;
                    s.at(i, j) = k;
                }
            }
        }
    }
    
}

LinAlg::Matrix
MatrixChainOrder::multiply(const LinAlg::Matrix &A, const LinAlg::Matrix &B){
    assert(A.getColSize() == B.getRowSize());

    LinAlg::Matrix C(A.getRowSize(), B.getColSize());
    for(int i = 0; i < A.getRowSize(); i++){
        for(int j = 0; j < B.getColSize(); j++){
            C.at(i,j) = 0;
            for(int k = 0; k < A.getColSize(); k++){
                C.at(i,j) = C.at(i,j) + A.at(i,k) * B.at(k,j);
            }
        }
    }
    return C;
}


void 
MatrixChainOrder::M(){
    for(int i = 1; i < p.size(); i++){
        for(int j = 1; j < p.size(); j++){
            printf("%8.2f ", m.at(i,j));
        }
        putchar('\n');
    }
}

void
MatrixChainOrder::S(){
    for(int i = 1; i < p.size()-1; i++){
        for(int j = 2; j < p.size(); j++){
            printf("%8.2f ", s.at(i, j));
        }
        putchar('\n');
    }
}

void 
MatrixChainOrder::printOptimalParens(size_t i, size_t j){
    if(i==j)
		printf("A%lu",i);
	else{
		printf("(");
		printOptimalParens(i, s.at(i,j));
		printOptimalParens(s.at(i,j)+1, j);
		printf(")");
	}
}
