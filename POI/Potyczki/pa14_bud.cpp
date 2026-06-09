#include<bits/stdc++.h>
using namespace std;

vector<int> chi[1001];
int arr[1001];

int f(int x)
{
    if(arr[x] <= 0)
        return arr[x];
    
    int cnt2 = 0, cnt1 = 0;
    for(auto &y : chi[x])
    {
        int t = f(y);
        if(t == -2)
            cnt2++;
        else if(t == -1)
            cnt1++;
    }
    
    if(cnt1 == cnt2)
        arr[x] = 0;
    else if(cnt2 > cnt1)
        arr[x] = -2;
    else
        arr[x] = -1;
    
    return arr[x];
}

vector<int> res;

int main()
{
    int n, i, j;
    scanf("%d", &n);
    for(i=1;i<=n;i++)
        arr[i] = 1;
    for(i=1;i<=n;i++)
    {
        int t;
        scanf("%d", &t);
        if(t <= 0)
            arr[i] = t;
        else
        {
            for(j=0;j<t;j++)
            {
                int a;
                scanf("%d", &a);
                chi[i].push_back(a);
            }
        }
    }
    
    bool ok = 0;
    bool tak = 0;
    for(i=1;i<=n;i++)
    {
        if(chi[i].size() != 0 || arr[i] != 0)
            continue;
        
        ok = 1;
        for(j=1;j<=n;j++)
            if(chi[j].size() != 0)
                arr[j] = 1;
        
        arr[i] = -2;
        
        int r = f(1);
        
        arr[i] = 0;
        
        if(r == -2)
        {
            tak = 1;
            res.push_back(i);
        }
    }
    
    if(!ok)
    {
        for(j=1;j<=n;j++)
            if(chi[j].size() != 0)
                arr[j] = 1;
        
        int r = f(1);
        
        if(r == -2)
            tak = 1;
    }
    
    if(!tak)
    {
        printf("NIE\n");
        return 0;
    }
    
    sort(res.begin(), res.end());
    
    printf("TAK %d\n", res.size());
    for(int &t : res)
        printf("%d ", t);
    printf("\n");
    return 0;
}

