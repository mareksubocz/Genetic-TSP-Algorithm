#include"useful.cpp"
// #include "tqdm/tqdm.h"
using namespace std;

int main(int argc, char * argv[]){
	std::ios_base::sync_with_stdio(false);
	vector<vector<double>> e;
	vector<int> sequence;
	readInputFile(argv[1], e);
	sequence = greedy(e, 0);
	cout<<"wynik: "<<result(e, sequence)<<endl;
	if(argc > 2){
		vector<int> optimalSequence = readSolutionFile(argv[2]);
		cout<<"optim: "<<result(e, optimalSequence)<<endl;
		double cost = (result(e, sequence) / result(e, optimalSequence)) - 1;
		cout<<"cost: "<<setprecision(4)<<cost*100<<"%"<<endl;
	}
	return 0;
}