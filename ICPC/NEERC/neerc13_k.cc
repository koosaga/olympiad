#include<bits/stdc++.h>
using namespace std;

int arr[1000010];
int col[1000010];
int cnt[1000010];

int h, k;
int k0, k1, k2;

void add(int x, int v)
{
    if(x == h)
        return;
    
    if(cnt[x] >= k-1)
        k0 += v;
    if(cnt[x] >= k)
        k1 += v;
    if(cnt[x] >= k+1)
        k2 += v;
}

int main()
{
    
    int n, p, c, i;
    scanf("%d%d%d%d", &n, &p, &c, &h);
    for(i=1;i<=n;i++)
        scanf("%d", &arr[i]);
    for(i=1;i<=p;i++)
        scanf("%d", &col[i]);
    
    vector<int> res;
    
    if(n == 1)
    {
        if(col[p] == h)
            res.push_back(1);
    }
    else
    {
        vector<int> rel;
        for(i=2;i<=p;i++)
            if(col[i] != h)
                rel.push_back(col[i]);
        
        for(i=1;i<=n;i++)
            cnt[arr[i]]++;
        
        if(rel.size() < cnt[h])
        {
            for(int &t : rel)
            {
                cnt[t]++;
                cnt[h]--;
            }
            
            k = cnt[h];
            
            for(i=1;i<=c;i++)
            {
                if(i == h)
                    continue;
                
                add(i, 1);
            }
            
            for(i=1;i<=n;i++)
            {
                if(arr[i] != col[1])
                {
                    add(arr[i], -1);
                    add(col[1], -1);
                    
                    cnt[arr[i]]--;
                    cnt[col[1]]++;
                    
                    add(arr[i], 1);
                    add(col[1], 1);
                }
                
                if(cnt[h] == k-1 && !k0 || cnt[h] == k && !k1 || cnt[h] == k+1 && !k2)
                    res.push_back(i);
                
                if(arr[i] != col[1])
                {
                    add(arr[i], -1);
                    add(col[1], -1);

                    cnt[arr[i]]++;
                    cnt[col[1]]--;

                    add(arr[i], 1);
                    add(col[1], 1);
                }
            }
        }
    }
    
    printf("%d\n", res.size());
    for(int &t : res)
        printf("%d ", t);
    return 0;
}