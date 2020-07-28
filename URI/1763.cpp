// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1763
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
unordered_map<string,string> mapa;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	mapa["brasil"] = "Feliz Natal!";
	mapa["alemanha"] = "Frohliche Weihnachten!";
	mapa["austria"] = "Frohe Weihnacht!";
	mapa["coreia"] = "Chuk Sung Tan!";
	mapa["espanha"] = "Feliz Navidad!";
	mapa["grecia"] = "Kala Christougena!";
	mapa["estados-unidos"] = "Merry Christmas!";
	mapa["inglaterra"] = "Merry Christmas!";
	mapa["australia"] = "Merry Christmas!";
	mapa["portugal"] = "Feliz Natal!";
	mapa["suecia"] = "God Jul!";
	mapa["turquia"] = "Mutlu Noeller";
	mapa["argentina"] = "Feliz Navidad!";
	mapa["chile"] = "Feliz Navidad!";
	mapa["mexico"] = "Feliz Navidad!";
	mapa["antardida"] = "Merry Christmas!";
	mapa["canada"] = "Merry Christmas!";
	mapa["irlanda"] = "Nollaig Shona Dhuit!";
	mapa["belgica"] = "Zalig Kerstfeest!";
	mapa["italia"] = "Buon Natale!";
	mapa["libia"] = "Buon Natale!";
	mapa["siria"] = "Milad Mubarak!";
	mapa["marrocos"] = "Milad Mubarak!";
	mapa["japao"] = "Merii Kurisumasu!";
	string entrada;
	while(cin >> entrada){
		if(mapa.count(entrada)){
			cout << mapa[entrada] << '\n';
		}
		else{
			cout << "--- NOT FOUND ---\n";
		}
	}
	return 0;
}
