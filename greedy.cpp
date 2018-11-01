#define INF 2147483647
#include"useful.cpp"
// #include "tqdm/tqdm.h"
using namespace std;

int main(int argc, char * argv[]){
	std::ios_base::sync_with_stdio(false);
	vector<vector<double>> e;
	vector<bool> vis;
	vector<int> sequence;
	double mini = INF;
	int a = 0, b;
	readInputFile(argv[1], e);
	vis.resize(e.size(), 0);
	sequence.push_back(1); vis[0] = 1;	//dodajemy pierwszy wierzcholek
	//************* algorytm zachlanny: 
	for (int i = 1; i < e.size(); ++i){
		for (int j = 0; j < e.size(); ++j){
			if(!vis[j] and e[a][j] < mini) 
				b = j, mini = e[a][j];
		}
			sequence.push_back(b+1);
			vis[b] = true;
			a = b;
			mini = INF;
	}
	//************* wypisywanie wyniku:
	cout<<"wynik: "<<result(e, sequence)<<endl;
	if(argc > 2){
		vector<int> optimalSequence = readSolutionFile(argv[2]);
		cout<<"optim: "<<result(e, optimalSequence)<<endl;
		double cost = (result(e, sequence) / result(e, optimalSequence)) - 1;
		cout<<"cost: "<<setprecision(4)<<cost*100<<"%"<<endl;
	}
	return 0;
}