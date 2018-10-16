#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define ROF(i,a,b) for(int i=a; i>b; --i)
#define REP(i,n) FOR(i,0,n)
#define INF 2147483647
#define MAX 10000
#include<bits/stdc++.h>
using namespace std;

struct point{
	double x, y;
};

int main(){
	std::ios_base::sync_with_stdio(false);
	//std::cin.tie(nullptr);
	point p[MAX];
	double e[MAX][MAX];
	ifstream in;
	in.open("in.txt")
	int n;
	int a;
	string opis, linia;
	while (!in.eof()){
		getline(in, opis);
		getline(in, linia); opis += linia;
		getline(in, linia);
		in >> linia; cin >> n;
		getline(in, linia);
		getline(in, linia);
		//wczytalem wstep
		for (int i = 0; i < n; ++i){
			cin>>a>>a;
			p[i].x = a;
			cin>>a;
			p[i].y = a;
		}
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				e[i][j] = pow((p[i].x - p[j].x),2)
			}
		}

	}
	return 0;
}