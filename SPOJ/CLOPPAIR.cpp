// Ivan Carvalho
// Solution to https://www.spoj.com/problems/CLOPPAIR/
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#define MP make_pair
#define X second.first
#define Y first
#define ID second.second
using namespace std;
typedef long long ll;
typedef pair<ll, pair<ll,ll> > point;
int comp(point A, point B){
	return A.X < B.X;
}
int main(){
	vector<point> P;
	set<point> C;
	ll n;
	scanf("%lld",&n);
	for(ll i=0;i<n;i++){
		ll x1,y1;
		scanf("%lld %lld",&x1,&y1);
		P.push_back(MP(y1,MP(x1,i)));
	}
	sort(P.begin(),P.end(),comp);
	double best = hypot(P[0].X - P[1].X,P[0].Y - P[1].Y);
	ll melhor1 = P[0].ID, melhor2 = P[1].ID,left=0;
	C.insert(P[0]);
	for(int i=1;i<n;i++){
		while (left < i && P[i].X - P[left].X > best) C.erase(P[left++]);
		for(set<point>::iterator it = C.lower_bound(MP(P[i].Y - best,MP(P[i].X - best,0))); it != C.end() && P[i].Y + best >=  (*it).Y;it++){
			double tentativa = hypot(P[i].X - (*it).X , P[i].Y - (*it).Y);
			if (tentativa < best){
				best = tentativa;
				melhor1 = P[i].ID;
				melhor2 = (*it).ID;
			}
		}
		C.insert(P[i]);
	}
	if (melhor1 > melhor2) swap(melhor1,melhor2);
	printf("%lld %lld %.6lf\n",melhor1,melhor2,best);
	return 0;
}