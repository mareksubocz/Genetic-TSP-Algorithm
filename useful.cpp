#include<bits/stdc++.h>

using namespace std;


struct point{
	double x;
	double y;
};

void readInputFile(string path, vector<vector<double>> & v){
	fstream in;
	in.open(path);
	int no;
	double a, b;
	vector<point> p;
	while(in>>no>>a>>b)
		p.push_back(point{a,b});
	v.resize(p.size(),vector<double>(p.size(), 0));
	// wyliczenie odległości:
	for (int i = 0; i < p.size(); ++i)
		for (int j = i+1; j < p.size(); ++j)
			v[i][j]=v[j][i]=(sqrt(pow(p[i].x - p[j].x,2) + pow(p[i].y - p[j].y,2)));
	in.close();
}

vector<int> readSolutionFile(string path){
	fstream in; in.open(path);
	vector<int> v;
	int a;
	while (in>>a) v.push_back(a-1);
	in.close();
	return v;
}

//indeksujemy od 0
double result(vector<vector<double>> & e, vector<int> & seq){
	double res = 0;
	for (int i = 0; i < seq.size()-1; ++i)
		res += e[seq[i]][seq[i+1]];
	res += e[seq[seq.size()-1]][seq[0]];	//dodajemy powrot do poczatku
	return res;
}

