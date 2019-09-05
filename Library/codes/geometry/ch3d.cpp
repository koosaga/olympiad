struct vec3{
	ll x, y, z;
	vec3(): x(0), y(0), z(0) {}
	vec3(ll a, ll b, ll c): x(a), y(b), z(c) {}
	vec3 operator*(const vec3& v) const{ return vec3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
	vec3 operator-(const vec3& v) const{ return vec3(x-v.x, y-v.y, z-v.z); }
	vec3 operator-() const{ return vec3(-x, -y, -z); }
	ll dot(const vec3 &v) const{ return x*v.x+y*v.y+z*v.z; }
};

struct twoset {
	int a, b;
	void insert(int x) { (a == -1 ? a : b) = x; }
	bool contains(int x) { return a == x || b == x; }
	void erase(int x) { (a == x ? a : b) = -1; }
	int size() { return (a != -1) + (b != -1); }
} E[MAXN][MAXN]; // i < j

struct face{
	vec3 norm;
	ll disc;
	int I[3];
};

face make_face(int i, int j, int k, int ii, vector<vec3> &A){ // p^T * norm < disc
	E[i][j].insert(k); E[i][k].insert(j); E[j][k].insert(i);
	face f; f.I[0]=i, f.I[1]=j, f.I[2]=k;
	f.norm = (A[j]-A[i])*(A[k]-A[i]);
	f.disc = f.norm.dot(A[i]);
	if(f.norm.dot(A[ii])>f.disc){
		f.norm = -f.norm;
		f.disc = -f.disc;
	}
	return f;
}

vector<face> get_hull(vector<vec3> &A){
	int N = A.size();
	vector<face> faces; memset(E, -1, sizeof(E));
	faces.push_back(make_face(0,1,2,3,A));
	faces.push_back(make_face(0,1,3,2,A));
	faces.push_back(make_face(0,2,3,1,A));
	faces.push_back(make_face(1,2,3,0,A));
	for(int i=4; i<N; ++i){
		for(int j=0; j<faces.size(); ++j){
			face f = faces[j];
			if(f.norm.dot(A[i])>f.disc){
				E[f.I[0]][f.I[1]].erase(f.I[2]);
				E[f.I[0]][f.I[2]].erase(f.I[1]);
				E[f.I[1]][f.I[2]].erase(f.I[0]);
				faces[j--] = faces.back();
				faces.pop_back();
			}
		}
		int nf = faces.size();
		for(int j=0; j<nf; ++j){
			face f=faces[j];
			for(int a=0; a<3; ++a) for(int b=a+1; b<3; ++b){
				int c=3-a-b;
				if(E[f.I[a]][f.I[b]].size()==2) continue;
				faces.push_back(make_face(f.I[a], f.I[b], i, f.I[c], A));
			}
		}
	}
	return faces;
}
