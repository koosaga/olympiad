#include<bits/stdc++.h>
using namespace std;

char buf[256];
long long __lcm(long long x, long long y)
{
    return x*(y/__gcd(x, y));
}
pair<long long, long long> solve(long long N)
{
    scanf("%s", buf);
    if(strcmp(buf, "NWD") == 0)
    {
        auto v1 = solve(N);
        auto v2 = solve(N);
        return make_pair(__gcd(v1.first, v2.first),
                         __gcd(v1.second, v2.second));
    }
    if(strcmp(buf, "NWW") == 0)
    {
        auto v1 = solve(N);
        auto v2 = solve(N);
        return make_pair(__lcm(v1.first, v2.first),
                         __lcm(v1.second, v2.second));
    }
    if('0' <= buf[0] && buf[0] <= '9')
    {
        long long x; sscanf(buf, "%lld", &x);
        return make_pair(x, x);
    }
    return make_pair(1ll, N);
    
}
bool tmain()
{
    long long int N; scanf("%lld", &N);
    auto res = solve(N);
    return res.first == res.second;
}
int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
        puts(tmain()?"TAK":"NIE");
}
