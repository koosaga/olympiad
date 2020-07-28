// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1295
#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#define X second
#define Y first
#define MP make_pair
using namespace std;
typedef pair<double,double> point;
int comp(point A, point B){
	return A.X < B.X;
}
double closest_pair(vector<point> P){
	int n = P.size();
	sort(P.begin(),P.end(),comp);
	double best = 100000.0;
	set<point> box;
	box.insert(P[0]);
	int left = 0;
	for(int i=1;i<n;i++){
		while(left < i && P[i].X - P[left].X > best) box.erase(P[left++]);
		for(set<point>::iterator it = box.lower_bound(MP(P[i].Y-best,P[i].X-best));it != box.end() && P[i].Y + best >= (*it).Y;it++){
			best = min(best,hypot(P[i].X-(*it).X,P[i].Y-(*it).Y));
		}
		box.insert(P[i]);
	}
	return best;
}
int main(){
	int quantidade;
	while(scanf("%d",&quantidade) && quantidade){
		vector<point> entrada;
		for(int i=0;i<quantidade;i++){
			double x1,y1;
			scanf("%lf %lf",&x1,&y1);
			entrada.push_back(MP(y1,x1));
		}
		double resultado = closest_pair(entrada);
		if (resultado > 10000.0 && fabs(resultado-10000.0) > 1e-5) printf("INFINITY\n");
		else printf("%.4lf\n",resultado);
	}
	return 0;
}
