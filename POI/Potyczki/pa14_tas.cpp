#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101010;
int a[MAXN];
int L[4], R[4];
int N, K;
void solve(int x)
{
    vector<int> nn;
    for(int i=0; i<=N; ++i)
        if(abs(a[i]-a[i+1])>1) nn.push_back(i);
    if(nn.size() == 0)
    {
        puts("TAK");
        for(int i=K; i>x; --i)
        {
            printf("%d %d\n", L[i], R[i]);
        }
        for(int i=x; i>0; --i)
            puts("1 1");
        exit(0);
    }
    if(nn.size() > 2*x)
        return;
    for(int y: nn)
    {
        for(int i=y+1; i<=N; ++i)
        {
            if(a[i] == a[y]+1 || a[i] == a[y]-1)
            {
                reverse(a+y+1, a+i+1);
                L[x] = y+1;
                R[x] = i;
                solve(x-1);
                reverse(a+y+1, a+i+1);
            }
        }
        for(int i=y; i>=1; --i)
        {
            if(a[i] == a[y+1]+1 || a[i] == a[y+1]-1)
            {
                reverse(a+i, a+y+1);
                L[x] = i;
                R[x] = y;
                solve(x-1);
                reverse(a+i, a+y+1);
            }
        }
    }
    return;
}
int main()
{
    scanf("%d%d", &N, &K);
    for(int i=1; i<=N; ++i)
        scanf("%d", a+i);
    a[N+1] = N+1;
    solve(K);
    puts("NIE");
}