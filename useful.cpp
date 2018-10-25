#include<bits/stdc++.h>

using namespace std;


struct point{
	double x;
	double y;
};

void readInputFile(string path, vector<vector<double>> & e, vector<int> converter){
	fstream in;
	in.open(path);
	int no;
	int numberOfInstances;
	double a, b;
	vector<point> p;
	while(in>>no>>a>>b){
		converter.push_back(no);
		p.push_back(point{a,b});
	}
	e.resize(p.size(),vector<double>(p.size(), 0));
	for (int i = 0; i < p.size(); ++i)
		for (int j = i; j < p.size(); ++j)
			e[i][j]=e[j][i]=(sqrt(pow(p[i].x - p[j].x,2) + pow(p[i].y - p[j].y,2)));
	in.close();
}

vector<int> readSolutionFile(string path){
	fstream in; 
	vector<int> v;
	int a;
	in.open(path);
	while (in>>a) v.push_back(a);
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

