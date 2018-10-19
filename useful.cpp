#include<bits/stdc++.h>

using namespace std;

struct point{
	double x;
	double y;
};

void readInputFile(string path, vector<vector<double>> & e){
	fstream in;
	in.open(path);
	string no;
	int numberOfInstances;
	while(no != "NODE_COORD_SECTION") getline(in, no);
	in>>no;
	double a, b;
	vector<point> p;
	while(no != "EOF"){
		in>>a>>b;
		p.push_back(point{a,b});
		in>>no;
	}
	e.resize(p.size(),vector<double>(p.size(), 0));
	for (int i = 1; i < p.size(); ++i)
		for (int j = i; j < p.size(); ++j)
			e[i][j]=e[j][i]=(sqrt(pow(p[i].x - p[j].x,2) + pow(p[i].y - p[j].y,2)));
	in.close();
}

vector<int> readSolutionFile(string path){
	fstream in; in.open(path);
	int a;
	string line;
	vector<int> v;
	while(line != "TOUR_SECTION") getline(in, line);
	in>>a;
	while (a != -1){
		v.push_back(a);
		in>>a;
	}
	in.close();
	return v;
}

//wkladamy od 1, ale od indeksu 0
double result(vector<vector<double>> & e, vector<int> & sequence){
	double w = 0;
	for (int i = 0; i < sequence.size()-1; ++i)
		w += e[sequence[i]-1][sequence[i+1]-1];
	w += e[sequence[sequence.size()-1]-1][sequence[0]-1];
	return w;
}

