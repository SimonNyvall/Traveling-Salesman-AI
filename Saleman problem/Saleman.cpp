#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

// Global Varibles.
const int populationSize = 10;
const int citySize = 5;


int _population[populationSize][citySize];
double fitness[populationSize];
int recordDistance = 9999999;
int bestEver[citySize];
double mutationrate = 0.1;


const int order[citySize] = { 0,1,2,3,4 };
int cityPoints[citySize][2]; // [0]city -> [1]point x, y


// shuffle function
void shuffle(int deck[]) {
	int temp = 0;
	int randomIndex = 0;
	for (int i = 0; i < citySize; i++) {
		randomIndex = rand() % citySize;
		temp = deck[i];
		deck[i] = deck[randomIndex];
		deck[randomIndex] = temp;
	}
}

// Platns the citys
void setRandomCityPoint(int cityIndex) {
	// map of 100x100 points
	for (int i = 0; i <= citySize; i++) {
		for (int j = 0; j < 2; j++) {
			cityPoints[i][j] = (rand() % 100 + 1);
		}
	}
}


// Calculate the sum of distance
int cityA[2];
int cityB[2];

double calcDistace(int points[][2], int populationOrder[]) {
	double sum = 0;

	for (int i = 0; i < citySize - 1; i++) {

		int cityAIndex = populationOrder[i];
		for (int j = 0; j < 2; j++) {
			cityA[j] = cityPoints[cityAIndex][j];
		}

		int cityBIndex = populationOrder[i + 1];
		for (int q = 0; q < 2; q++) {
			cityB[q] = cityPoints[cityBIndex][q];
		}

		//Distace ekvation
		int dPoint1 = pow((cityA[0] - cityB[0]), 2);
		int dPoint2 = pow((cityB[1] - cityA[1]), 2);
		int d = sqrt(dPoint1 + dPoint2);

		sum += d;
	}
	return sum;
}



void normalize() {
	double sum = 0;

	for (int i = 0; i < populationSize; i++) {
		sum += fitness[i];
	}

	for (int j = 0; j < populationSize; j++) {
		fitness[j] = fitness[j] / sum;
	}

}


void mutate(int (&mutatedOrder)[citySize]) {
	
}

int listOfPopulationArray[citySize];
void pickOne(int (&listOfPopulation)[populationSize][citySize], double (&prob)[populationSize]) {
	int index = 0;

	srand(time(NULL));
	double r = (rand() % 10);
	r = r / 10;

	while (r > 0) {
		r = r - prob[index];
		index++;
	}
	index--;

	for (int i = 0; i < citySize; i++) {
		listOfPopulationArray[i] = listOfPopulation[index][i];
	}
}

void nextGeneration() {
	int new_population[populationSize][citySize];

	for (int i = 0; i < populationSize; i++) {
		for (int v = 0; v < populationSize; v++) {
			//new_population[i][v] = _population[i][v];
			pickOne(_population, fitness);
			mutate(listOfPopulationArray);
			new_population[i][v];
		}
	}

	for (int j = 0; j < populationSize; j++) {
		for (int q = 0; q < citySize; q++) {
			_population[j][q] = new_population[j][q];
		}
	}
}

int main() {
	srand(time(NULL)); // Seeds the random number generator

	// Populate the population with an array from 0..5 according to the city size
	for (int i = 0; i <= populationSize; i++) {
		for (int j = 0; j < citySize; j++) {
			_population[i][j] = order[j];
		}
	}

	// Shuffle the array
	for (int arrayCount = 0; arrayCount < populationSize; arrayCount++) {
		shuffle(_population[arrayCount]);
	}

	// ------------------------------------------------------------------------
	for (int i = 0; i < citySize; i++) {
		setRandomCityPoint(i);
	}

	// Calculate the fitness and set the best fitness to bestEver
	for (int i = 0; i < populationSize; i++) {

		double d = calcDistace(cityPoints, _population[i]);

		if (d < recordDistance) {
			recordDistance = d;

			for (int j = 0; j < citySize; j++) {
				bestEver[j] = _population[i][j];
			}
		}
		fitness[i] = 1 / (d + 1);
	}

	normalize();
	nextGeneration();

	// Print result for debuging
	for (int i = 0; i < citySize; i++) {
		std::cout << bestEver[i] << std::endl;
	}

}


