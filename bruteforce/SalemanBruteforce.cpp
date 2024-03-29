#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <memory>
using namespace std;


class Timer{ // returns a long long
    public:
        Timer(){
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }
        ~Timer(){
            Stop();
        }
        void Stop(){
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            auto start = std::chrono::time_point_cast < std::chrono::microseconds > (m_StartTimepoint).time_since_epoch().count();
            auto end = std::chrono::time_point_cast < std::chrono::microseconds > (endTimepoint).time_since_epoch().count();

            auto duration = end - start;

            std::cout << duration << "us\n";
        }
    private:
        std::chrono:: time_point < std::chrono::high_resolution_clock > m_StartTimepoint;
};



#pragma region Globals Varibles
// Globals Varibles

const int arraySize = 10;

std::vector<vector<int>> permuntations(0);

int order[arraySize];

int globalPoints[arraySize][2] = {
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

int bestEver = 999999;
int bestRoute[arraySize];

#pragma endregion

//---------------------------------------------------------------

void populateOrder(){
	for (int i = 0; i < arraySize; i++){
		order[i] = i;
	}
}

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
            if (gen == arraySize - 1)
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
    {
        Timer timer;
        populateOrder();

        // Permutation state
        vectorResize(arraySize);
        CalcPermuntations calcPermuntations;
        calcPermuntations.permute(order, 0, arraySize - 1);

        //--------------------------------------------------------

        // Calculate distace state
        int a[arraySize];
        for (int i = 0; i < permuntations.size(); i++)
        {
            for (int j = 0; j < arraySize; j++)
            {
                a[j] = permuntations[i][j];
            }
            double routeValue = calcDistace(a);
            if (bestEver > routeValue)
            {
                bestEver = routeValue;
                for (int q = 0; q < arraySize; q++)
                {
                    bestRoute[q] = a[q];
                }
            }
        }
    }
    // Prints the results
    cout << "Fastest path: ";
    for (int i = 0; i < arraySize; i++)
    {
        cout << bestRoute[i];
    }
    cout << endl
         << bestEver << " a.u  traveld" << endl;

    return 0;
}
