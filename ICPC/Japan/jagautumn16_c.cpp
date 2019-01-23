#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;

map<string, pi> level_map;
map<pi, string> printer;

bool JIKJIMASIBAL = 1;

void INW(pi p){
	if(JIKJIMASIBAL) return;
	printf("%s is not working now.\n", printer[p].c_str());
}

void WHN(pi p){	
	if(JIKJIMASIBAL) return;
	printf("%s is working hard now.\n", printer[p].c_str());
}

int n;
char str[55];

int member_cnt = 0;
set<pi> high, low;

void Insert(pi p){
	member_cnt++;
	if(high.size() != member_cnt / 5){
		// jagang doocheon
		if(*low.rbegin() < p){
			WHN(p);
			high.insert(p);
		}
		else{
			INW(p);
			WHN(*low.rbegin());
			high.insert(*low.rbegin());
			low.erase(*low.rbegin());
			low.insert(p);
		}
	}
	else{
		if(!high.empty() && *high.begin() < p){
			WHN(p);
			INW(*high.begin());
			low.insert(*high.begin());
			high.erase(high.begin());
			high.insert(p);
		}
		else{
			INW(p);
			low.insert(p);
		}
	}
}

void Remove(pi p){
	member_cnt--;
	if(high.find(p) != high.end()){
		high.erase(p);
		while(high.size() < member_cnt / 5){
			WHN(*low.rbegin());
			high.insert(*low.rbegin());
			low.erase(--low.end());
		}
	}
	else{
		low.erase(p);
		while(high.size() > member_cnt / 5){
			INW(*high.begin());
			low.insert(*high.begin());
			high.erase(high.begin());
		}
	}
}

int main(){
	scanf("%d",&n);
	int lev;
	for(int i=0; i<n; i++){
		scanf("%s %d",str,&lev);
		string v = str;
		int l = lev;
		level_map[v] = pi(l, i);
		printer[pi(l, i)] = v;
		Insert(pi(l, i));
	}
	JIKJIMASIBAL = 0;
	int q; scanf("%d",&q);
	for(int i=n; i<n+q; i++){
		scanf("%s", str);
		if(*str == '+'){
			scanf("%s %d",str,&lev);
			string v = str;
			int l = lev;
			level_map[v] = pi(l, i);
			printer[pi(l, i)] = v;
			Insert(pi(l, i));
		}
		else{
			scanf("%s", str);
			string v = str;
			Remove(level_map[v]);
			printer.erase(level_map[v]);
			level_map.erase(v);
		}
	}
}
