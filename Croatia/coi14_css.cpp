#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

char buf[5005];

vector<string> readline_split(){
	fgets(buf, 5005, stdin);
	int n = strlen(buf);
	while(n > 0 && (isspace(buf[n-1]) || !isprint(buf[n-1]))) n--;
	buf[n] = 0;
	vector<string> ret;
	string cur;
	for(int i=0; i<n; i++){
		if(buf[i] == ' '){
			if(!cur.empty()) ret.push_back(cur);
			cur.clear();
		}
		else cur.push_back(buf[i]);
	}
	if(!cur.empty()) ret.push_back(cur);
	return ret;
}

struct docline{
	int is_end;
	string name;
	vector<string> classes;
};

int n;

docline read_docline(){
	n--;
	auto l = readline_split();
	docline ret;
	if(l.size() == 1){
		assert(l[0] == "</div>");
		ret.is_end = 1;
		return ret;
	}
	ret.is_end = 0;
	ret.name = l[1].substr(4, l[1].size() - 5);
	if(l.size() == 3){
		ret.classes.push_back(l[2].substr(7, l[2].size() - 9));
	}
	else{
		ret.classes.push_back(l[2].substr(7, l[2].size() - 7));
		for(int i=3; i+1<l.size(); i++) ret.classes.push_back(l[i]);
		ret.classes.push_back(l.back().substr(0, l.back().size() - 2));
	}
	return ret;
}

map<string, int> class_to_num;
string num_to_name[5005];
vector<int> class_node[100005];
int tree_nodes, class_count, par[5005], dout[5005];

void make_tree(){
	stack<int> stk;
	stk.push(0);
	while(n && !stk.empty()){
		int x = stk.top();
		docline in = read_docline();
		if(in.is_end == 1){
			dout[x] = tree_nodes;
			stk.pop();
		}
		else{
			tree_nodes++;
			for(auto &i : in.classes){
				if(class_to_num.find(i) == class_to_num.end()){
					class_to_num[i] = ++class_count;
				}
				class_node[class_to_num[i]].push_back(tree_nodes);
			}
			par[tree_nodes] = x;
			num_to_name[tree_nodes] = in.name;
			stk.push(tree_nodes);
		}
	}
	assert(class_count <= 100000);
	assert(tree_nodes <= 5000);
	assert(n == 0);
}

vector<int> parse_brj(string s){
	vector<int> v;
	int ok = 0;
	for(int i=0; i<s.size(); ){
		int nxt = i+1;
		while(nxt < s.size() && s[nxt] != '.') nxt++;
		int x = class_to_num[s.substr(i + 1, nxt - i - 1)];
		ok++;
		for(auto &j : class_node[x]){
			v.push_back(j);
		}
		i = nxt;
	}
	sort(v.begin(), v.end());
	vector<int> ans;
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[e] == v[i]) e++;
		if(e - i == ok) ans.push_back(v[i]);
		i = e;
	}
	return ans;
}

vector<int> query(vector<string> &s){
	auto v = parse_brj(s[0]);
	for(int i=1; i<s.size(); i++){
		if(s[i] == ">"){
			auto r = parse_brj(s[++i]);
			vector<int> ans;
			for(auto &i : r){
				if(binary_search(v.begin(), v.end(), par[i])) ans.push_back(i);
			}
			v = ans;
		}
		else{
			auto r = parse_brj(s[i]);
			vector<int> ans;
			int pnt = 0;
			for(auto &i : v){
				pnt = max(pnt, (int)(upper_bound(r.begin(), r.end(), i) - r.begin()));
				while(pnt < r.size() && r[pnt] <= dout[i]){
					ans.push_back(r[pnt++]);
				}
			}
			v = ans;
		}
	}
	return v;
}

int main(){
	scanf("%d\n",&n);
	make_tree();
	int m;
	scanf("%d\n", &m);
	while(m--){
		auto in = readline_split();
		auto ret = query(in);
		printf("%d ", ret.size());
		for(auto &i : ret){
			printf("%s ", num_to_name[i].c_str());
		}
		puts("");
	}
}
