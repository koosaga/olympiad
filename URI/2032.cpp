// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2032
#include <cstdio>
#include <queue>
#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
#define MP make_pair
using namespace std;
typedef pair<string, vector<string> > svs;
unordered_set<string> visitado;
inline void exibe(string s){
	printf("%c%c%c\n",s[0],s[1],s[2]);
	printf("%c%c%c\n",s[3],s[4],s[5]);
	printf("%c%c%c\n",s[6],s[7],s[8]);
}
int main(){
	string referencia = "123456780";
	char entrada[3][3];
	while(scanf("%s",entrada[0]) != EOF){
		int possivel = 0;
		scanf("%s",entrada[1]);
		scanf("%s",entrada[2]);
		visitado.clear();
		string ini;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				ini.push_back(entrada[i][j]);
			}
		}
		queue<svs> bfs;
		vector<string> vazio;
		bfs.push(MP(ini,vazio));
		while(!bfs.empty()){
			svs davez = bfs.front();
			bfs.pop();
			string jogo = davez.first;
			vector<string> vetor = davez.second;
			if(visitado.count(jogo)) continue;
			visitado.insert(jogo);
			if(jogo == referencia){
				possivel = 1;
				printf("Quantidade minima de passos = %d\n",(int)vetor.size());
				for(int i=0;i<vetor.size()-1;i++){
					exibe(vetor[i]);
					printf("\n");
				}
				exibe(vetor[vetor.size()-1]);
				break;
			}
			if(jogo[0] == '0'){
				string copia1 = jogo;
				copia1[3] = jogo[0];
				copia1[0] = jogo[3];
				vetor.push_back(copia1);
				if(!visitado.count(copia1)) bfs.push(MP(copia1,vetor));
				vetor.pop_back();
				string copia2 = jogo;
				copia2[0] = jogo[1];
				copia2[1] = jogo[0];
				vetor.push_back(copia2);
				if(!visitado.count(copia2)) bfs.push(MP(copia2,vetor));
				vetor.pop_back();
			}
			if(jogo[1] == '0'){
				string copia1 = jogo;
				copia1[1] = jogo[4];
				copia1[4] = jogo[1];
				vetor.push_back(copia1);
				if(!visitado.count(copia1)) bfs.push(MP(copia1,vetor));
				vetor.pop_back();
				string copia3 = jogo;
				copia3[2] = jogo[1];
				copia3[1] = jogo[2];
				vetor.push_back(copia3);
				if(!visitado.count(copia3)) bfs.push(MP(copia3,vetor));
				vetor.pop_back();
				string copia4 = jogo;
				copia4[0] = jogo[1];
				copia4[1] = jogo[0];
				vetor.push_back(copia4);
				if(!visitado.count(copia4)) bfs.push(MP(copia4,vetor));
				vetor.pop_back();
			}
			if(jogo[2] == '0'){
				string copia1 = jogo;
				copia1[5] = jogo[2];
				copia1[2] = jogo[5];
				vetor.push_back(copia1);
				if(!visitado.count(copia1)) bfs.push(MP(copia1,vetor));
				vetor.pop_back();
				string copia2 = jogo;
				copia2[1] = jogo[2];
				copia2[2] = jogo[1];
				vetor.push_back(copia2);
				if(!visitado.count(copia2)) bfs.push(MP(copia2,vetor));
				vetor.pop_back();
			}
			if(jogo[3] == '0'){
				string copia1 = jogo;
				copia1[3] = jogo[0];
				copia1[0] = jogo[3];
				vetor.push_back(copia1);
				if(!visitado.count(copia1)) bfs.push(MP(copia1,vetor));
				vetor.pop_back();
				string copia2 = jogo;
				copia2[3] = jogo[6];
				copia2[6] = jogo[3];
				vetor.push_back(copia2);
				if(!visitado.count(copia2)) bfs.push(MP(copia2,vetor));
				vetor.pop_back();
				string copia3 = jogo;
				copia3[3] = jogo[4];
				copia3[4] = jogo[3];
				vetor.push_back(copia3);
				if(!visitado.count(copia3)) bfs.push(MP(copia3,vetor));
				vetor.pop_back();
			}
			if(jogo[4] == '0'){
				string copia1 = jogo;
				copia1[1] = jogo[4];
				copia1[4] = jogo[1];
				vetor.push_back(copia1);
				if(!visitado.count(copia1)) bfs.push(MP(copia1,vetor));
				vetor.pop_back();
				string copia2 = jogo;
				copia2[7] = jogo[4];
				copia2[4] = jogo[7];
				vetor.push_back(copia2);
				if(!visitado.count(copia2)) bfs.push(MP(copia2,vetor));
				vetor.pop_back();
				string copia3 = jogo;
				copia3[5] = jogo[4];
				copia3[4] = jogo[5];
				vetor.push_back(copia3);
				if(!visitado.count(copia3)) bfs.push(MP(copia3,vetor));
				vetor.pop_back();
				string copia4 = jogo;
				copia4[3] = jogo[4];
				copia4[4] = jogo[3];
				vetor.push_back(copia4);
				if(!visitado.count(copia4)) bfs.push(MP(copia4,vetor));
				vetor.pop_back();
			}
			if(jogo[5] == '0'){
				string copia1 = jogo;
				copia1[5] = jogo[2];
				copia1[2] = jogo[5];
				vetor.push_back(copia1);
				if(!visitado.count(copia1)) bfs.push(MP(copia1,vetor));
				vetor.pop_back();
				string copia2 = jogo;
				copia2[5] = jogo[8];
				copia2[8] = jogo[5];
				vetor.push_back(copia2);
				if(!visitado.count(copia2)) bfs.push(MP(copia2,vetor));
				vetor.pop_back();
				string copia3 = jogo;
				copia3[5] = jogo[4];
				copia3[4] = jogo[5];
				vetor.push_back(copia3);
				if(!visitado.count(copia3)) bfs.push(MP(copia3,vetor));
				vetor.pop_back();
			}
			if(jogo[6] == '0'){
				string copia1 = jogo;
				copia1[3] = jogo[6];
				copia1[6] = jogo[3];
				vetor.push_back(copia1);
				if(!visitado.count(copia1)) bfs.push(MP(copia1,vetor));
				vetor.pop_back();
				string copia2 = jogo;
				copia2[6] = jogo[7];
				copia2[7] = jogo[6];
				vetor.push_back(copia2);
				if(!visitado.count(copia2)) bfs.push(MP(copia2,vetor));
				vetor.pop_back();
			}
			if(jogo[7] == '0'){
				string copia1 = jogo;
				copia1[7] = jogo[4];
				copia1[4] = jogo[7];
				vetor.push_back(copia1);
				if(!visitado.count(copia1)) bfs.push(MP(copia1,vetor));
				vetor.pop_back();
				string copia3 = jogo;
				copia3[8] = jogo[7];
				copia3[7] = jogo[8];
				vetor.push_back(copia3);
				if(!visitado.count(copia3)) bfs.push(MP(copia3,vetor));
				vetor.pop_back();
				string copia4 = jogo;
				copia4[6] = jogo[7];
				copia4[7] = jogo[6];
				vetor.push_back(copia4);
				if(!visitado.count(copia4)) bfs.push(MP(copia4,vetor));
				vetor.pop_back();
			}
			if(jogo[8] == '0'){
				string copia1 = jogo;
				copia1[5] = jogo[8];
				copia1[8] = jogo[5];
				vetor.push_back(copia1);
				if(!visitado.count(copia1)) bfs.push(MP(copia1,vetor));
				vetor.pop_back();
				string copia2 = jogo;
				copia2[8] = jogo[7];
				copia2[7] = jogo[8];
				vetor.push_back(copia2);
				if(!visitado.count(copia2)) bfs.push(MP(copia2,vetor));
				vetor.pop_back();
			}
		}
		if(!possivel) printf("Problema sem solucao\n");
	}
	return 0;
}
