//by hyea
#include<bits/stdc++.h>
using namespace std;
const long long MAXK = 1e12;
vector<long long> ones;
void init()
{
    for(long long n=0;;++n)
    {
        ones.push_back(3*n*n+3*n+1);
        if(3*n*n+3*n+1>MAXK) break;
    }
}
int solve(long long x)
{
    if(x%6>=3) return x%6;
    if(x%6==0) return 6;
    if(x%6==1)
    {
        if(binary_search(ones.begin(), ones.end(), x))
            return 1;
        else
            return 7;
    }
    long long left = 0;
    long long right = ones.size()-1;
    while(left<=right)
    {
        long long val = ones[left]+ones[right];
        if(val>x) --right;
        else if(val<x) ++left;
        else return 2;
    }
    return 8;
}
int main()
{
    init();
    while(true)
    {
        long long T;
        scanf("%lld", &T);
        if(T==0) return 0;
        printf("%d\n", solve(T));
    }
}
