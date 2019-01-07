#include "useful.cpp"
#define pdvi pair<double, vector<int> >
using namespace std;

enum selectionType{tourSel, rankSel, propSel};
enum mutationType{swapMut, revMut};

int numOfEpochs = 1000;
int generationSize = 5000;
int tournamentSize = 2;
double mutationRate = 0.001;
bool elitism = 1;
selectionType st = tourSel;
mutationType mt = swapMut;

int instanceSize;
vector<int> theBestEver;
double theBestResult;
vector<vector<double>> e;
multimap<double,vector<int>> generation;

void startrandomGeneration() {
  vector<int> chromosome;
  for (int j = 0; j < e.size(); ++j) chromosome.push_back(j);
  while (generation.size() < generationSize) {
    random_shuffle(chromosome.begin(), chromosome.end());
    generation.emplace(result(e, chromosome), chromosome);
  }
}

void swapMutate(vector<int> &v) {
  for (int i = 0; i < v.size(); ++i)
    if (rand() / (double)RAND_MAX < mutationRate) {
      int a = rand() % (int)v.size();
      swap(v[i], v[a]);
    }
}

void reverseMutate(vector<int> &v) {
  if (rand() / (double)RAND_MAX < mutationRate) {
    int a = rand() % (int)v.size();
    int b = rand() % (int)v.size();
    if(a > b) swap(a, b);
    for (int i = 0; i <= (b-a)/2; ++i){
      swap(v[a+i], v[b-i]);
    }
  }
}

void startGreedyGeneration(){
  vector<int> seq;
  for (int i = 0; i < e.size(); ++i){
    seq = greedy(e, i);
    generation.emplace(result(e, seq), seq);
  }
  vector<int> chromosome;
  for (int j = 0; j < e.size(); ++j) chromosome.push_back(j);
  while (generation.size() < generationSize) {
    random_shuffle(chromosome.begin(), chromosome.end());
    generation.emplace(result(e,chromosome),chromosome);
  }
}

double sumOfFitnesses(){
  double sum = 0;
  auto ptr = generation.begin();
  for (; ptr != generation.end(); ++ptr){
    sum += ptr->first;
  }
  return sum;
}

vector<int> proportional() {
  double sum;
  double r = rand() / RAND_MAX;
  sum = sumOfFitnesses();
  auto ptr = generation.begin();
  for (; r > 0; ++ptr) r -= ptr->first / sum;
  return ptr->second;
}

vector<int> tournament() {
  auto item = generation.begin();
  auto minitem = generation.begin();
  for (int i = 0; i < tournamentSize; ++i) {
    item = generation.begin();
    advance(item, rand() % (int)generation.size()); //przesun do przodu o r el.
    if(item->first < minitem->first)
      minitem = item;
  }
  return minitem->second;
}

vector<int> rankBased() {
  double base = 1 / (((generationSize+1) * generationSize) / 2);
  double r = rand() / (double)RAND_MAX;
  for (int i = 0; i < generationSize; ++i){
    r -= base * (generationSize-i);
    if(r <= 0){
      auto ptr = generation.begin();
      advance(ptr,i);
      return ptr->second;
    }
  }
  return generation.begin()->second;
}

vector<int> crossover(vector<int> &a, vector<int> &b) {
  vector<int> newChromosome;
  int start = rand() % (int)e.size();
  int end = rand() % (int)e.size();
  for (int i = start; i != end; ++i, i %= (int)e.size())
    newChromosome.push_back(a[i]);
  for (int i = 0; i < b.size(); ++i)
    if (find(newChromosome.begin(), newChromosome.end(), b[i]) ==
        newChromosome.end())
      newChromosome.push_back(b[i]);
  return newChromosome;
}

void nextGeneration() {
  multimap<double, vector<int>> newGeneration;
  vector<int> a, b, ab;
  if (elitism) newGeneration.insert(*generation.begin());
  while (newGeneration.size() < generationSize) {
    if (st == tourSel)
      a = tournament(), b = tournament();
    else if (st == rankSel)
      a = rankBased(), b = rankBased();
    else if (st == propSel)
      a = proportional(), b = proportional();

    ab = crossover(a, b);

    if (mt == swapMut)
      swapMutate(ab);
    else if(mt == revMut)
      reverseMutate(ab);
    newGeneration.emplace(result(e, ab), ab);
  }
  generation = newGeneration;
  if(generation.begin()->first < theBestResult){
    theBestResult = generation.begin()->first;
    theBestEver = generation.begin()->second;
  }

}

void partialBrute(){
  int n = 9; //maksymalnie 11 ma jakis sens
  int step = 1; // TODO: naprawic
  int count = 1000;
  vector<int> tmpvec;
  for (int i = 0; i < n; ++i) tmpvec.push_back(theBestEver[i]);
  for (int i = 0; i < count; i+=step){
    if(i%5 == 0)
      cout<<(double)i/count * 100<<"%"<<endl;
    bruteforce(e, tmpvec);
    for (int j = 0; j < n; ++j) theBestEver[(j+i) % instanceSize] = tmpvec[j];
    tmpvec.erase(tmpvec.begin());
    tmpvec.push_back(theBestEver[(i+n) % instanceSize]);
  }
  theBestResult = result(e, theBestEver);
}

void sigint(int a) {
  partialBrute();
  cout<<"najlepszy: "<<endl;
  for (int i = 0; i < instanceSize; ++i)
    cout<<theBestEver[i] + 1<<" ";
  cout<<endl;
  cout<<"best ever: "<<theBestResult<<endl;
  cout<<"NoE: "<<numOfEpochs<<endl;
  cout<<"genSize: "<<generationSize<<endl;
  cout<<"tourSize: "<<tournamentSize<<endl;
  cout<<"mutRate: "<<mutationRate<<endl;
  cout<<"elitism: "<<elitism<<endl;
  cout<<"selType: "<<st<<endl;
  cout<<"mutType: "<<mt<<endl;
  exit(0);
}

int main(int argc, char const *argv[]) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  signal(SIGINT, sigint);
  srand(int(time(NULL))); rand();
  instanceSize = readInputFile(argv[1], e);
  // startrandomGeneration();
  startGreedyGeneration();
  theBestEver = generation.begin()->second;
  theBestResult = generation.begin()->first;
  cout<<theBestResult<<endl;
  for (int epoch = 0; epoch < numOfEpochs; ++epoch) {
    cout << epoch << "-> best in generation: " << result(e, generation.begin()->second) << endl;
    nextGeneration();
  }
  sigint(0);
  
  return 0;
}
