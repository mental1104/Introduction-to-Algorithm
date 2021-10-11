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
    static long long calculate(const std::vector<int>& p, const int n, Method m);
private:
    static long long naive(const std::vector<int>& p, const int n);

    static long long memoized(const std::vector<int>& p, const int n);
    static long long memoizedAux(const std::vector<int>& p, const int n, std::vector<long long>& r);

    static long long bottomUp(const std::vector<int>& p, const int n);
};

long long 
CutRod::calculate(const std::vector<int>& p, const int n, Method m){
    unsigned long long res = 0;
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

long long
CutRod::naive(const std::vector<int>& p, const int n){
    if(n == 0)
        return 0;

    long long q = INT_MIN; 
    for(int i = 1; i <= n; ++i)
        q = std::max(q, p[i]+naive(p, n-i));
    return q;
}

long long
CutRod::memoized(const std::vector<int>& p, const int n){
    std::vector<long long> r(n+1, INT_MIN);
    return memoizedAux(p, n, r);
}  

long long
CutRod::memoizedAux(const std::vector<int>& p, const int n, std::vector<long long>& r){
    if(r[n]>=0)
        return r[n];

    long long q = 0;
    if(n != 0){
        q =  INT_MIN;
    
        for(int i = 1; i <= n; ++i)
            q = std::max(q, p[i] + memoizedAux(p, n-i, r));
    }
    r[n] = q;
    return q;
}

long long
CutRod::bottomUp(const std::vector<int>& p, const int n){
    std::vector<long long> r;
    std::vector<int> s;
    s.reserve(n+1);
    r.reserve(n+1);
    r[0] = 0;
    for(int j = 1; j<=n; ++j){
        long long q = INT_MIN;
        for(int i = 1; i<=j; ++i)
            if(q < p[i]+r[j-i]){
                q = p[i] + r[j-i];
                s[j] = i;
            }
            //q = std::max(q, p[i]+r[j-i]);//j-i == 0 corner case.
        r[j] = q;
    }

    int temp = n;
    while(temp > 0){
        std::cout << s[temp] << " ";
        temp = temp - s[temp];
    }
    std::cout << std::endl;
    return r[n];
}


#endif