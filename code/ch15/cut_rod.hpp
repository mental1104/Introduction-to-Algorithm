#ifndef CLRS_CUT_ROD
#define CLRS_CUT_ROD

#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>

enum class Method : int{
    NAIVE,
    MEMOIZED,
    BOTTOMUP,
};

class CutRod{
public:
    static int calculate(const std::vector<int>& p, const int n, Method m);
private:
    static int naive(const std::vector<int>& p, const int n);
    static int memoized(const std::vector<int>& p, const int n);
    static int memoizedAux(const std::vector<int>& p, const int n, std::vector<int>& r);
    static int bottomUp(const std::vector<int>& p, const int n);
};

int 
CutRod::calculate(const std::vector<int>& p, const int n, Method m){
    int res = 0;
    switch(m){
        case Method::MEMOIZED:
            #ifdef DEBUG
            std::cout << "MEMOIZED incurred." << std::endl;
            #endif
            res = memoized(p, n);
            break;
        case Method::NAIVE:
            #ifdef DEBUG
            std::cout << "NAIVE incurred." << std::endl;
            #endif
            res = naive(p, n);
            break;
        case Method::BOTTOMUP:
            #ifdef DEBUG
            std::cout << "BOTTOMUP incurred." << std::endl;
            #endif
            res = bottomUp(p, n);
            break;
        default:
            std::cerr << "Error: No such method. " << std::endl;
            break;
    }
    return res;
}

int
CutRod::naive(const std::vector<int>& p, const int n){
    if(n == 0)
        return 0;

    int q = INT_MIN; 
    for(int i = 1; i <= n; ++i)
        q = std::max(q, p[i]+naive(p, n-i));
    return q;
}

int 
CutRod::memoized(const std::vector<int>& p, const int n){
    std::vector<int> r(n+1, INT_MIN);
    return memoizedAux(p, n, r);
}  

int 
CutRod::memoizedAux(const std::vector<int>& p, const int n, std::vector<int>& r){
    if(r[n]>=0)
        return r[n];

    int q = 0;
    if(n != 0){
        q == INT_MIN;
    
        for(int i = 1; i <= n; ++i)
            q = std::max(q, p[i] + memoizedAux(p, n-i, r));
    }
    r[n] = q;
    return q;
}

int 
CutRod::bottomUp(const std::vector<int>& p, const int n){
    std::vector<int> r;
    r.reserve(n+1);
    r[0] = 0;
    for(int j = 1; j<=n; ++j){
        int q = INT_MIN;
        for(int i = 1; i<=j; ++i)
            q = std::max(q, p[i]+r[j-i]);//j-i == 0 corner case.
        r[j] = q;
    }
    return r[n];
}


#endif