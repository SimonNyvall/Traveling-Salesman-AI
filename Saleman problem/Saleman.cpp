#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>
#include <memory>
using namespace std;

class Timer
{ // returns a long long
public:
	Timer()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		Stop();
	}
	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		auto duration = end - start;

		std::cout << duration << "us\n";
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};

#pragma region Global Varibles

const int stopTimer = 10;

const int populationSize = 5;
const int citySize = 10;

int _population[populationSize][citySize];
double fitness[populationSize];
int recordDistance = 9999999;
int bestEver[citySize];
//double mutationrate = 0.1;

int order[citySize];
//int cityPoints[citySize][2]; // [0]city -> [1]point x, y


int cityPoints[citySize][2] = {
	 {3, 96},
    {76, 50},
    {83, 69},
    {43, 77},
    {47, 5},
    {4, 90},
    {77, 55},
    {55, 63},
    {47, 66},
    {43, 2}
};


#pragma endregion

//--------------------------------------------------------------

#pragma region population and city initialization

void populateOrder(){
	for (int i = 0; i < citySize; i++){
		order[i] = i;
	}
}

// shuffle function
void shuffle(int deck[])
{
	int temp = 0;
	int randomIndex = 0;
	for (int i = 0; i < citySize; i++)
	{
		randomIndex = rand() % citySize;
		temp = deck[i];
		deck[i] = deck[randomIndex];
		deck[randomIndex] = temp;
	}
}

// Platns the citys
void setRandomCityPoint(int cityIndex)
{
	// map of 100x100 points
	for (int i = 0; i <= citySize; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cityPoints[i][j] = (rand() % 100 + 1);
		}
	}
	return;
}

#pragma endregion

// Calculate the sum of distance
double calcDistace(int points[][2], int ie)
{
	int populationOrder[citySize];

	for (int i = 0; i < citySize; i++){
		populationOrder[i] = _population[ie][i];
	}

	int cityA[2];
	int cityB[2];

	double sum = 0;

	for (int i = 0; i < citySize - 1; i++)
	{

		int cityAIndex = populationOrder[i];
		for (int j = 0; j < 2; j++)
		{
			cityA[j] = cityPoints[cityAIndex][j];
		}

		int cityBIndex = populationOrder[i + 1];
		for (int q = 0; q < 2; q++)
		{
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

// Normalize the fitness values
void normalize()
{
	double sum = 0;

	for (int i = 0; i < populationSize; i++)
	{
		sum += fitness[i];
	}

	for (int j = 0; j < populationSize; j++)
	{
		fitness[j] = fitness[j] / sum;
	}
	return;
}

#pragma region Mutation

// Swaping for the mutation function
int swapMutatedOrder[citySize];
void swap(int (&mutatedOrder)[citySize], int indexA, int indexB)
{
	int temp1 = mutatedOrder[indexA];
	int temp2 = mutatedOrder[indexB];
	mutatedOrder[indexB] = temp1;
	mutatedOrder[indexA] = temp2;

	for (int i = 0; i < citySize; i++)
	{
		swapMutatedOrder[i] = mutatedOrder[i];
	}
	return;
}

// Mutate an array, by swiching two index points
void mutate(int (&mutatedOrder)[citySize])
{
	int indexA = floor(rand() % citySize);
	int indexB = floor(rand() % citySize); 
	
	swap(mutatedOrder, indexA, indexB);
}

int listOfPopulationArray[citySize];
void pickOne(int (&listOfPopulation)[populationSize][citySize], double (&prob)[populationSize])
{
	int index = 0;

	//srand(time(NULL)); // Seed

	// Picking one array of elemants
	double r = (rand() % 10);
	r = r / 10;

	while (r > 0)
	{
		r = r - prob[index];
		index++;
	}
	index--;

	for (int i = 0; i < citySize; i++)
	{
		listOfPopulationArray[i] = listOfPopulation[index][i];
	}
	return;
}

#pragma endregion

void nextGeneration()
{
	int new_population[populationSize][citySize];

	// pick one array (one elemnt of the population array) and mutate it.
	for (int FisrtIndexi = 0; FisrtIndexi < populationSize; FisrtIndexi++)
	{
		pickOne(_population, fitness);
		mutate(listOfPopulationArray);
		for (int v = 0; v < citySize; v++)
		{
			if (FisrtIndexi == 3){
				//cout << "test" << endl;
			}


			new_population[FisrtIndexi][v] = swapMutatedOrder[v];
		}
	}

	for (int j = 0; j < populationSize; j++)
	{
		for (int q = 0; q < citySize; q++)
		{
			_population[j][q] = new_population[j][q];
		}
	}
	return;
}

int main()
{
{
	Timer timer;

	srand(time(NULL)); // Seeds the random number generator

	populateOrder(); // Populates the order

	// Populate the population with an array from 0..5 according to the city size
	for (int i = 0; i <= populationSize; i++)
	{
		for (int j = 0; j < citySize; j++)
		{
			_population[i][j] = order[j];
		}
	}

	// Shuffle an array (population) shuffle
	for (int arrayCount = 0; arrayCount < populationSize; arrayCount++)
	{
		shuffle(_population[arrayCount]);
	}

	/*
	// Sets random points for the cities.
	for (int i = 0; i < citySize; i++) {
		setRandomCityPoint(i);
	}
*/
double d;
	int generation = 0;
	while (generation < stopTimer)
	{

		// Calculate the fitness and set the best fitness to bestEver
		for (int ie = 0; ie < populationSize; ie++)
		{
			 d = calcDistace(cityPoints, ie);

			if (d < recordDistance)
			{
				recordDistance = d;

				for (int j = 0; j < citySize; j++)
				{
					bestEver[j] = _population[ie][j];
				}
			}
			fitness[ie] = 1 / (d + 1);
		}

		// Normalize the fitness, so the best can be picked more often
		normalize();

		// Sets upp the nexr generation, with mutation
		nextGeneration();

		generation++;
	}
}
	// Print result for debuging
	std::cout << "Fastest path: ";
	for (int i = 0; i < citySize; i++)
	{
		std::cout << bestEver[i] << ", ";
	}
	std::cout << endl;
	return 0;
}