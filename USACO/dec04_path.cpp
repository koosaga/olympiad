    #include <cstdio>  
    #include <cstring>  
    #include <algorithm>  
    using namespace std;  
    int a[1000005],n,l,p,q;  
    int dp[1000005];  
      
    struct rmq{  
        int tree[1050000], lim;  
        void init(int n){  
            memset(tree,0x3f,sizeof(tree));  
            for(lim = 1; lim <= n; lim <<= 1);  
        }  
        void add(int x, int v){  
            x += lim;  
            tree[x] = v;  
            while(x>1){  
                x >>= 1;  
                tree[x] = min(tree[2*x],tree[2*x+1]);  
            }  
        }  
        int q(int s, int e){  
            s = max(s,0);  
            e = max(e,0);  
            s += lim;  
            e += lim;  
            int r = 1e9;  
            while(s < e){  
                if(s%2 == 1) r = min(r,tree[s++]);  
                if(e%2 == 0) r = min(r,tree[e--]);  
                s >>= 1;  
                e >>= 1;  
            }  
            if(s == e) r = min(r,tree[s]);  
            return r;  
        }  
    }rmq;  
      
    int main(){  
        scanf("%d %d %d %d",&n,&l,&p,&q);  
        for (int i=0; i<n; i++) {  
            int x,y;  
            scanf("%d %d",&x,&y);  
            a[x+1]++;  
            a[y]--;  
        }  
        for (int i=1; i<=l; i++) {  
            a[i] += a[i-1];  
        }  
        rmq.init(l/2);  
        rmq.add(0,0);  
        for (int i=min(p,q); i<=l/2; i++) {  
            if(a[i*2]) continue;  
            dp[i] = rmq.q(i-q,i-p) + 1;  
            rmq.add(i,dp[i]);  
        }  
        printf("%d",dp[l/2] > 1e9 ? -1 : dp[l/2]);  
    }  