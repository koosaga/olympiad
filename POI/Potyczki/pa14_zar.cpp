#include<bits/stdc++.h>
using namespace std;
int N, K; // N-K match
int bulb[505050];
int room[505050];
int prv[1000005], nxt[1000005];
typedef pair<int, int> pi;

vector<pi> UF;

int fl(int x){
	return prv[x] = (prv[x] == x ? x : fl(prv[x]));
}

int fr(int x){
	return nxt[x] = (nxt[x] == x ? x : fr(nxt[x]));
}

int getprv(int x){
	x++;
	if(fl(x-1) == 0) return -1;
	return fl(x-1) - 1;
}

int getnxt(int x){
	x++;
	if(fr(x+1) == UF.size() + 1) return -1;
	return fr(x+1) - 1;
}

int erase(int x){
	x++;
	prv[x] = fl(x - 1);
	nxt[x] = fr(x + 1);
}

int main()
{
    scanf("%d%d", &N, &K);
    for(int i=1; i<=N; ++i)
        scanf("%d", bulb+i);
    for(int i=1; i<=N; ++i)
        scanf("%d", room+i);
    for(int i=1; i<=N; ++i)
    {
        UF.push_back(make_pair(bulb[i], i));
        UF.push_back(make_pair(room[i], -i));
    }
    sort(UF.begin(), UF.end());
    iota(prv, prv + UF.size() + 2, 0);
    iota(nxt, nxt + UF.size() + 2, 0);
    using pii = pair<int, int>;
    priority_queue<pii,vector<pii>, greater<pii> > Q;
    for(int i=0; i+1<UF.size(); i++){
    	auto it = UF[i];
    	auto it2 = UF[i+1];
    	if(it.second < 0 && it2.second > 0){
    		Q.emplace(it2.first - it.first, -it.second);
		}
	}
    long long ans = 0;
    for(int i=1; i<=N; ++i) ans += room[i];
    int cnt = 0;
    while(!Q.empty() && cnt < N-K)
    {
        //for(auto p: S)
        //{
        //    cout << p.first << " " << p.second << endl;
        //}
        //cout << endl; //
        int cost, rno; tie(cost, rno) = Q.top(); Q.pop();
        //cout << rno << endl; //
        ans += cost;
        int it = lower_bound(UF.begin(), UF.end(), pi(room[rno], -rno)) - UF.begin();
        int it0 = getprv(it);
        int it2 = getnxt(it);
        int it3 = getnxt(it2);
        if(it0 != -1 && it3 != -1){
        	if(UF[it0].second < 0 && UF[it3].second > 0){
        		Q.emplace(UF[it3].first - UF[it0].first, -UF[it0].second);
			}
		}
		erase(it);
		erase(it2);
        ++cnt;
    }
    if(cnt<N-K)
    {
        puts("NIE");
        return 0;
    }
    printf("%lld\n", ans);
}







