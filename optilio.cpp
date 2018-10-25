#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define ROF(i,a,b) for(int i=a; i>b; --i)
#define REP(i,n) FOR(i,0,n)
#define INF 2147483647
#define MAX 1000
#include<bits/stdc++.h>
using namespace std;

vector<vector<double> > e;
vector<bool> vis;
vector<int> converter;
vector<int> sequence;

struct point{
	double x;
	double y;
};

void readInput(){
	int no;
	int numberOfInstances;
	double a, b;
	vector<point> p;
	while(cin>>no>>a>>b){
		converter.push_back(no);
		p.push_back(point{a,b});
	}
	e.resize(p.size(),vector<double>(p.size(), 0));
	for (int i = 0; i < p.size(); ++i)
		for (int j = i; j < p.size(); ++j)
			e[i][j]=e[j][i]=(sqrt(pow(p[i].x - p[j].x,2) + pow(p[i].y - p[j].y,2)));
}

int main(int argc, char * argv[]){
	std::ios_base::sync_with_stdio(false);
	double mini;
	int a, b;
	readInput();
	vis.resize(e.size(), 0);
	vis[0] = 1;
	a = 0;
	sequence.push_back(1);
	mini = INF;
	for (int i = 1; i < e.size(); ++i){
		for (int j = 1; j < e.size(); ++j){
			if(!vis[j] and (e[a][j]) < mini) 
				b = j, mini = e[a][j];
		}
			sequence.push_back(b+1);
			vis[b] = true;
			a = b;
			mini = INF;
	}
	for (int i = 0; i < e.size(); ++i)
		cout<<converter[sequence[i]-1]<<endl;
	return 0;
}