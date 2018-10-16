#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define ROF(i,a,b) for(int i=a; i>b; --i)
#define REP(i,n) FOR(i,0,n)
#define INF 2147483647
#include<bits/stdc++.h>
using namespace std;

struct point{
	double x;
	double y;
};

void wczytaj( vector<vector<double>> & e){
	string no;
	for (int i = 0; i < 6; ++i)
		getline(cin, no);
	cin>>no;
	double a, b;
	vector<point> p;
	while(no != "EOF"){
		cin>>a>>b;
		p.push_back(point{a,b});
		cin>>no;
	}
	for (int i = 0; i < p.size(); ++i){
		e.push_back(vector<double> (0));
		for (int j = 0; j < p.size(); ++j){
			e[i].push_back(sqrt(pow(p[i].x - p[j].x,2) + pow(p[i].y - p[j].y,2)));
		}
	}
}

double wynik(vector<vector<double>> & e, vector<int> & sequence){
	double w = 0;
	for (int i = 0; i < sequence.size()-1; ++i)
		w += e[sequence[i]][sequence[i+1]];
	w += e[sequence[sequence.size()-1]][sequence[0]];
	return w;
}
