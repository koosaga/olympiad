#include <bits/stdc++.h>
using namespace std;

priority_queue<int> pq;
using real_t = double;

int main()
{
    int n, i;
    scanf("%d", &n);
    for(i=0;i<n;i++)
    {
        int a;
        scanf("%d", &a);
        pq.push(a);
    }
    
    real_t res = 0;
    real_t p = 1;
    int t = 0;
    while(1)
    {
        int a = pq.top();
        pq.pop();
        
        if(a == 0)
        {
            if(t == 0)
                res += p;
            break;
        }
        
        if(t == 0)
        {
            res += p / (a + 1);
            p *= 1.0 * a / (a + 1);
        }
        else
        {
            p *= 1.0 * a / (a + 1);
        }
        
        t = 1-t;
        pq.push(a - 1);
    }
    
    printf("%.15lf", 1 - res);
    return 0;
}
