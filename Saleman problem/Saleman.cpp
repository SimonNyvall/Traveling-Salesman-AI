#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

// Global Varibles.
const int populationSize = 10;
const int citySize = 5;


int _population[populationSize][citySize];
int fitness[populationSize];
int recordDistance = 0;
int bestEver[citySize];


int order[citySize] = { 0,1,2,3,4 };
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

void setRandomCityPoint(int cityIndex) {
    // map of 100x100 points
    for (int i = 0; i <= citySize; i++) {
        for (int j = 0; j < 2; j++) {
            cityPoints[i][j] = (rand() % 100 + 1);
        }
    }
}

int cityA[2];
int cityB[2];

int calcDistace(int points[][2], int populationOrder[]) {
    int sum = 0;

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
        
        int d = calcDistace(cityPoints, _population[i]);

        if (d > recordDistance) {
            recordDistance = d;

            for (int j = 0; j < citySize; j++) {
                bestEver[j] = _population[i][j];
            }
        }
        fitness[i] = d;
    }

    
    // Print result for debuging
    for (int i = 0; i < citySize; i++) {
        std::cout << bestEver[i] << std::endl;
    }
    
}


