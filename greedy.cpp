#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define ROF(i,a,b) for(int i=a; i>b; --i)
#define REP(i,n) FOR(i,0,n)
#define INF 2147483647
#define MAX 1000
#include"useful.cpp"
using namespace std;

vector<vector<double>> e;

int main(){
	std::ios_base::sync_with_stdio(false);
	//std::cin.tie(nullßtr);
	wczytaj(e);
	bool vis[MAX] = {false};
	vector<int> sequence;
	vector<int> v;
	double mini;
	int a, b;
	//zaczynam algorytm
	vis[0] = 1;
	a = 0;
	sequence.push_back(1);
	mini = INF;
	for (int i = 1; i < e.size(); ++i){
		for (int j = 0; j < e.size(); ++j){
			if(!vis[j] and (e[a][j]) < mini) 
				b = j, mini = e[a][j];
		}
			sequence.push_back(b+1);
			vis[b] = true;
			a = b;
			mini = INF;
	}
	cout<<"wynik: "<<wynik(e, sequence)<<endl;
	return 0;
}