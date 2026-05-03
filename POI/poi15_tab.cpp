#include<bits/stdc++.h>
using namespace std;

vector<pair<bitset<201>, int>> v;
int arr[1001][201];
int n, m;

bool cmp(const pair<bitset<201>, int> &a, const pair<bitset<201>, int> &b)
{
    return a.first.count() < b.first.count();
}

bool cmp2(const int &a, const int &b)
{
    for(int i=0;i<m;i++)
        if(arr[a][i] != arr[b][i] || i == m-1)
            return arr[a][i] > arr[b][i];
}

int mem[1001];
int from[1001];
int sor[1001];

int main()
{
    int i, j;
    scanf("%d%d", &n, &m);
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d", &arr[i][j]);
    
    srand(9801);
    
    int ans = 0;
    vector<int> lis;
    
    for(i=0;i<n;i++)
        sor[i] = i;
    
    random_shuffle(sor, sor+n);
    
    double endtime = 2.8 * CLOCKS_PER_SEC;
    for(int b=0;clock() < endtime && b<n; b++)
    {
        // x is right
        int x = sor[b];
        
        v.clear();
        for(i=0;i<n;i++)
        {
            int mn, mx, t;
            mn = mx = arr[x][0] - arr[i][0];
            for(j=1;j<m;j++)
            {
                t = arr[x][j] - arr[i][j];
                
                mn = min(mn, t);
                mx = max(mx, t);
                
                if(mx - mn > 1)
                    break;
            }
            
            if(mx - mn > 1)
                continue;
            
            bitset<201> bs;
            for(j=0;j<m;j++)
            {
                t = arr[x][j] - arr[i][j];
                if(t == mx)
                    bs.set(j);
            }
            
            v.push_back({bs, i});
        }
        
        if(v.empty())
            continue;
        
        sort(v.begin(), v.end(), cmp);
        
        int mx = 0;
        int pos;
        
        for(i=0;i<v.size();i++)
        {
            mem[i] = 1;
            from[i] = -1;
            for(j=0;j<i;j++)
            {
                if((v[j].first & (~ v[i].first)).none())
                {
                    if(mem[j] + 1 > mem[i])
                    {
                        mem[i] = mem[j] + 1;
                        from[i] = j;
                    }
                }
            }
            
            if(mem[i] > mx)
            {
                mx = mem[i];
                pos = i;
            }
        }
        
        if(mx > ans)
        {
            ans = mx;
            lis.clear();
            
            int t = pos;
            while(t != -1)
            {
                lis.push_back(v[t].second);
                t = from[t];
            }
        }
    }
    
    printf("%d\n", ans);
    sort(lis.begin(), lis.end(), cmp2);
    for(auto &a: lis)
        printf("%d ", a + 1);
    return 0;
}

