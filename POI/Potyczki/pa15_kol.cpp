#include<bits/stdc++.h>
using namespace std;

vector<int> arr[200010];
int bea[200010];
int sma[200010];
int chk[200010];

int xsum[200010];
int cnt[200010];
int stk[200010];

mt19937 rng(0x9801);
int randint(int a, int b)
{
    return uniform_int_distribution<int>(a, b)(rng);
}

int main()
{
    int n, m, k, x, y, i;
    scanf("%d%d%d", &n, &m, &k);
    for(i=0; i<m; i++)
    {
        scanf("%d%d", &x, &y);
        //arr[x].push_back(y);
        //arr[y].push_back(x);
    }
    
    for(i=1;i<=n;i++)
        scanf("%d", &bea[i]);
    for(i=1;i<=n;i++)
        scanf("%d", &sma[i]);
    
    int c = 0;
    for(i=1;i<=n;i++)
        if(!chk[sma[i]])
            chk[sma[i]] = ++c;
    
    if(c <= k)
    {
        printf("TAK\n");
        for(i=1;i<=n;i++)
            printf("%d ", chk[sma[i]]);
        return 0;
    }
    
    for(i=1;i<=n;i++)
    {
        cnt[bea[i]]++;
        xsum[bea[i]] ^= i;
        arr[sma[i]].push_back(i);
    }
    
    int s = 0;
    for(i=1;i<=k;i++)
        if(cnt[i] == 1)
            stk[s++] = xsum[i];
    
    int endtime = CLOCKS_PER_SEC * 1.95;
    while(s && clock() < endtime)
    {
        int t = randint(0, s-1);
        swap(stk[t], stk[s-1]);
        
        x = stk[s-1];
        
        do
        {
            t = randint(0, arr[sma[x]].size() - 1);
            y = arr[sma[x]][t];
        }
        while(x == y);
        
        cnt[bea[x]]++;
        xsum[bea[x]] ^= y;
        
        cnt[bea[y]]--;
        xsum[bea[y]] ^= y;
        
        s--;
        
        if(cnt[bea[y]] == 1)
            stk[s++] = xsum[bea[y]];
        
        bea[y] = bea[x];
    }
    
    if(s)
        printf("NIE");
    else
    {
        printf("TAK\n");
        for(i=1;i<=n;i++)
            printf("%d ", bea[i]);
    }
    
    return 0;
}
