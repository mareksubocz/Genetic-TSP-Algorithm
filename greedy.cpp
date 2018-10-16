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
	cout<<e[0][1]<<" "<<e[120][111]<<endl;
	bool vis[MAX] = {false};
	double mini;
	double wynik = 0;
	for (int i = 0; i < n; ++i){
		cin>>a>>a;
		p[i].x = a;
		cin>>a;
		p[i].y = a;
		// cout<<a;
	}
	for (int i = 0; i < n; ++i)
		for (int j = i; j < n; ++j){
			e[i][j]=e[j][i]=sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x) + pow((p[i].y-p[j].y),2));
		}
	//zaczynam algorytm
	vis[0] = 1;
	cout<<1<<endl;
	a = 0;
	mini = INF;
	for (int i = 1; i < n; ++i){
		for (int j = 0; j < n; ++j){
			if(!vis[j] and (e[a][j]) < mini) 
				b = j, mini = e[a][j];
		}
			// cout<<"mini: "<<mini<<endl;
			wynik += e[a][b];
			a = b;
			mini = INF;
			cout<<b+1<<endl;
			vis[b] = true;
	}
	cout<<"wynik: "<<wynik;
	cin>>linia;
	return 0;
}