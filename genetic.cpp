#define INF 2147483647
#include "useful.cpp"
using namespace std;

int numOfEpochs = 400;
int generationSize = 2000;
int tournamentSize = 50;
double mutationRate = 0.006;
bool elitism = true;
vector<int> theBestEver;
vector<double> fitness;
vector<vector<double>> e;
vector<vector<int>> generation;

void startGeneration() {
  vector<int> chromosome;
  for (int j = 0; j < e.size(); ++j) chromosome.push_back(j);
  for (int i = 0; i < generationSize; ++i) {
    random_shuffle(chromosome.begin(), chromosome.end());
    generation.push_back(chromosome);
  }
}

void calcFitness() {
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
}

void normalizeFitness() {
  double sum = 0;
  for (int i = 0; i < fitness.size(); ++i) sum += fitness[i];
  for (int i = 0; i < fitness.size(); ++i) fitness[i] /= sum;
}

vector<int> pickOne() {
  int index;
  double r = rand() / RAND_MAX;
  normalizeFitness();
  for (index = 0; r > 0; ++index) r -= fitness[index];
  return generation[index];
}

vector<int> tournament() {
  vector<int> contestans;
  double winnerFitness = 0;
  int winner = 0;
  int r;
  for (int i = 0; i < tournamentSize; ++i) {
    r = rand() % (int)generation.size();
    contestans.push_back(r);
  }
  for (int i = 0; i < contestans.size(); ++i) {
    double tmp = fitness[i];
    if (tmp > winnerFitness) {
      winner = i;
      winnerFitness = tmp;
    }
  }
  return generation[winner];
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

void mutate(vector<int> &v) {
  for (int i = 0; i < e.size(); ++i)
    if (rand() / (double)RAND_MAX < mutationRate) {
      int a = rand() % (int)e.size();
      swap(v[i], v[a]);
    }
}

void nextGeneration() {
  vector<vector<int>> newGeneration;
  if (elitism) newGeneration.push_back(theBestEver);
  while (newGeneration.size() < generationSize) {
    vector<int> a = tournament();
    vector<int> b = tournament();
    vector<int> ab = crossover(a, b);
    mutate(ab);
    newGeneration.push_back(ab);
  }
  generation = newGeneration;
}

int main(int argc, char const *argv[]) {
  std::ios_base::sync_with_stdio(false);
  srand(int(time(NULL))); rand();
  readInputFile(argv[1], e);
  startGeneration();
  theBestEver = generation[0];
  for (int epoch = 0; epoch < numOfEpochs; ++epoch) {
    calcFitness();
    cout << "epoch " << epoch << ", best ever: " << result(e, theBestEver)
         << endl;
    nextGeneration();
  }
  return 0;
}