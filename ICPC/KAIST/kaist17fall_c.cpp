#include<bits/stdc++.h>
using namespace std;

int N, K, A;
int solve(int a, int b)
{
    int m1 = K/a;
    int m2 = K%a;
    int ans = 0;
    if(m2==0) ans = m1*(a+b) - b;
    else ans = m1*(a+b)+m2;
    return ans;
}
int main()
{
    scanf("%d%d%d",&N,&K,&A); K/= A;
    int ans = 0x3f3f3f3f;
    for(int i=0; i<N; ++i)
    {
        int p1, p2; scanf("%d%d",&p1,&p2);
        ans = min(ans, solve(p1, p2));
    }
    printf("%d\n", ans);    
    return 0;
}
