#include <ext/rope>
using namespace __gnu_cxx;

char buf[1000005];

crope r[50005];

int main(){
	int q; scanf("%d",&q);
	int ccnt = 0;
	int ver = 0;
	for(int i=1; i<=q; i++){
		int t, x; scanf("%d %d",&t,&x);
		if(t == 1){
			scanf("%s", buf);
			x -= ccnt;
			ver++;
			r[ver] = r[ver - 1];
			r[ver].insert(x, buf);
		}
		if(t == 2){
			int y; scanf("%d",&y);
			x -= ccnt; y -= ccnt;
			x--;
			ver++;
			r[ver] = r[ver-1].substr(0, x) + r[ver-1].substr(x + y, sz(r[ver-1]) - x - y);
		}
		if(t == 3){
			int y, z; scanf("%d %d",&y,&z);
			x -= ccnt; y -= ccnt; z -= ccnt;
			y--;
			string ans = r[x].substr(y, z).c_str();
			printf("%s\n", r[x].substr(y, z).c_str());
			ccnt += count(ans.begin(), ans.end(), 'c');
		}
	}
}
