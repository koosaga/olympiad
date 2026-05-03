#include<bits/stdc++.h>
using namespace std;
long long xt[10101], a[10101], b[10101], c[10101];
long long maxv[10101], maxi[10101];
long long max2v[10101], max2i[10101];
int main()
{
    freopen("generators.in", "r", stdin);
    freopen("generators.out", "w", stdout);
    memset(maxv, -1, sizeof(maxv));
    memset(max2v, -1, sizeof(max2v));
    int N; long long K;
    scanf("%d%lld",&N,&K);
    for(int i=0; i<N; ++i)
    {
        scanf("%lld%lld%lld%lld", xt+i, a+i, b+i, c+i);
        long long x = xt[i];
        for(int t=0; t<1100; ++t)
        {
            if(maxv[i]<x)
            {
                maxv[i] = x;
                maxi[i] = t;
            }
            x = (a[i]*x+b[i])%c[i];
        }
        x = xt[i];
        for(int t=0; t<1100; ++t)
        {
            if(max2v[i] < x && (maxv[i]-x)%K!=0)
            {
                max2v[i] = x;
                max2i[i] = t;
            }
            x = (a[i]*x+b[i])%c[i];
        }
    }
    long long ans = 0;
    for(int i=0; i<N; ++i)
        ans += maxv[i];
    if(ans%K!=0)
    {
        printf("%lld\n", ans);
        for(int i=0; i<N; ++i) printf("%lld ", maxi[i]);
    }
    else
    {
        int mini = -1, minv = 99999;
        for(int i=0; i<N; ++i)
        {
            if(max2v[i] == -1) continue;
            if(minv > maxv[i] - max2v[i])
            {
                minv = maxv[i] - max2v[i];
                mini = i;
            }
        }
        if(mini==-1) printf("-1");
        else
        {
            printf("%lld\n",ans-minv);
            for(int i=0; i<N; ++i)
            {
                if(i == mini) printf("%lld ", max2i[i]);
                else printf("%lld ",maxi[i]); 
            }
        }
    }
    puts("");
    return 0;
}







