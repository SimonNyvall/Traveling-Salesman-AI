#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#pragma region Globals Varibles
// Globals Varibles

const int arraySize = 5;

std::vector<vector<int>> permuntations(0);

int order[arraySize] = {
    0, 1, 2, 3, 4};

int globalPoints[arraySize][2] = {
    {20, 45},
    {30, 55},
    {40, 60},
    {55, 60},
    {65, 55}
};

int bestEver = 999999;
int bestRoute[arraySize];

#pragma endregion

//---------------------------------------------------------------

class CalcPermuntations{

private:
    int row = 0, gen = 0;

public:
void permute(int (&permuteArray)[arraySize], int l, int r)
{

    if (l == r)
    {
        for (int i = 0; i < arraySize; i++)
        {

            permuntations[row].push_back(permuteArray[i]); // Populates the vector with permuntations
            // Check if the row is correct
            if (gen == 2)
            {
                gen = 0;
                row++;
            }
            else
            {
                gen++;
            }
        }
    }
    // Swaps the elements
    int temp;
    for (int i = l; i <= r; i++)
    {

        // swap(a[l], a[i]);
        temp = permuteArray[l];
        permuteArray[l] = permuteArray[i];
        permuteArray[i] = temp;

        // permute(a, l+1, r);
        permute(permuteArray, l + 1, r);

        // swap(a[l], a[i]);
        temp = permuteArray[l];
        permuteArray[l] = permuteArray[i];
        permuteArray[i] = temp;
    }

    return;
}
};

// Resizes the vector to permin! 
void vectorResize(int permin){
    int sum = 1;
    for (int i = permin; i > 0; i--){
        sum *= i;
    }
    permuntations.resize(sum);
    return;
}

// Calculate the sum of distance
double calcDistace(int (&populationOrder)[arraySize]) {

	int cityA[2];
	int cityB[2];


	double sum = 0;

	for (int i = 0; i < arraySize - 1; i++) {

		int cityAIndex = populationOrder[i];
		for (int j = 0; j < 2; j++) {
			cityA[j] = globalPoints[cityAIndex][j];
		}

		int cityBIndex = populationOrder[i + 1];
		for (int q = 0; q < 2; q++) {
			cityB[q] = globalPoints[cityBIndex][q];
		}

		//Distace ekvation
		int dPoint1 = pow((cityA[0] - cityB[0]), 2);
		int dPoint2 = pow((cityB[1] - cityA[1]), 2);
		int d = sqrt(dPoint1 + dPoint2);

		sum += d;
	}
	return sum;
}



int main()
{
    // Permutation state
    vectorResize(arraySize);
    CalcPermuntations calcPermuntations;
    calcPermuntations.permute(order, 0, arraySize - 1);

    //--------------------------------------------------------

    // Calculate distace state
    int a [arraySize];
    for (int i = 0; i < permuntations.size(); i++){
        for (int j = 0; j < arraySize; j++){
            a[j] = permuntations[i][j];
        }
    double routeValue = calcDistace(a);
    if (bestEver > routeValue){
        bestEver = routeValue;
        for (int q = 0; q < arraySize; q++){
            bestRoute[q] = a[q];
        }
    }
    }

    // Prints the results
   for (int i = 0; i < arraySize; i++){
       cout << bestRoute[i];
   }
   cout << endl << bestEver << endl;

    return 0;
}
