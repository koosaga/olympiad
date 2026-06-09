#include<bits/stdc++.h>
using namespace std;

vector<int> arr[300010];
int b[300010];

long long p[300010];
long long q[300010];

bool chk[300010];
int dis[300010];

void f(int x)
{
    chk[x] = 1;
    for(int &y : arr[x])
    {
        if(!chk[y])
        {
            dis[y] = dis[x] + 1;
            f(y);
        }
    }
}

int main()
{
    int n, x, y, i;
    scanf("%d", &n);
    for(i=0;i<n-1;i++)
    {
        scanf("%d%d", &x, &y);
        arr[x].push_back(y);
        arr[y].push_back(x);    
    }
    for(i=1;i<=n;i++)
        scanf("%d", &b[i]);
    
    for(i=1;i<=n;i++)
    {
        p[i] = -((int)arr[i].size() - 2);
        for(int &y : arr[i])
            q[i] += b[y] - b[i];
    }
    
    f(1);
    
    __int128 psum, qsum;
    psum = 0;
    qsum = 0;
    
    for(i=1;i<=n;i++)
    {
        psum += dis[i] * p[i];
        qsum += dis[i] * q[i];
    }
    
    long long sum = (2 * b[1] - qsum) / psum;
    
    for(i=1;i<=n;i++)
        printf("%lld ", (p[i]*sum + q[i])/2);
    
    return 0;
}
