#include "useful.cpp"
#define pdvi pair<double, vector<int> >
using namespace std;

int numOfEpochs = 100;
int generationSize = 1000;
int tournamentSize = 2;
double mutationRate = 0.01;
bool elitism = 1;

int instanceSize;
vector<vector<double>> e;
multimap<double,vector<int>> generation;

void startrandomGeneration() {
  vector<int> chromosome;
  for (int j = 0; j < e.size(); ++j) chromosome.push_back(j);
  for (int i = 0; i < generationSize; ++i) {
    random_shuffle(chromosome.begin(), chromosome.end());
    generation.emplace(result(e, chromosome), chromosome);
  }
}

void mutate(vector<int> &v) {
  for (int i = 0; i < e.size(); ++i)
    if (rand() / (double)RAND_MAX < mutationRate) {
      int a = rand() % (int)e.size();
      swap(v[i], v[a]);
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
  for (int i = 0; generation.size() < generationSize; ++i) {
    random_shuffle(chromosome.begin(), chromosome.end());
    generation.emplace(result(e,chromosome),chromosome);
  }
}

/*void calcFitness() {
  double res;
  double bestResult = result(e, theBestEver);
  for (int i = 0; i < generation.size(); ++i) {
    res = result(e, generation[i]);
    fitness.resize(generationSize);
    fitness[i] = 1 / (res + 1);
    if (res < bestResult) {
      theBestEver = generation[i];
      bestResult = result(e, theBestEver);
    }
  }
}*/

/*void normalizeFitness() {
  double sum = 0;
  for (int i = 0; i < fitness.size(); ++i) sum += fitness[i];
  for (int i = 0; i < fitness.size(); ++i) fitness[i] /= sum;
}*/

/*vector<int> pickOne() {
  int index;
  double r = rand() / RAND_MAX;
  // normalizeFitness();
  for (index = 0; r > 0; ++index) r -= fitness[index];
  return generation[index];
}*/

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

/*vector<int> rankBased() {
  return sequence;
}*/

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
  multimap<double, vector<int> > newGeneration;
  if (elitism) newGeneration.insert(*generation.begin());
  while (newGeneration.size() < generationSize) {
    vector<int> a = tournament(); vector<int> b = tournament();
    // vector<int> a = pickOne(); vector<int> b = pickOne();
    // vector<int> a = rankBased(); vector<int> b = rankBased();
    vector<int> ab = crossover(a, b);
    mutate(ab);
    newGeneration.emplace(result(e, ab), ab);
    cout<<newGeneration.size()<<endl;
  }
  generation = newGeneration;
}

void sigint(int a) {
  cout<<"najlepszy: "<<endl;
  for (int i = 0; i < instanceSize; ++i)
    cout<<generation.begin()->second[i] + 1<<" ";
  cout<<endl;
  cout<<"NoE: "<<numOfEpochs<<endl;
  cout<<"genSize: "<<generationSize<<endl;
  cout<<"tourSize: "<<tournamentSize<<endl;
  cout<<"mutRate: "<<mutationRate<<endl;
  cout<<"elitism: "<<elitism<<endl;
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
  for (int epoch = 0; epoch < numOfEpochs; ++epoch) {
    cout << epoch << "-> best ever: " << result(e, generation.begin()->second) << endl;
    nextGeneration();
  }

  cout<<"najlepszy: "<<endl;
  for (int i = 0; i < instanceSize; ++i)
    cout<<generation.begin()->second[i] + 1<<" ";
  return 0;
}
