//TSP SIMULATED ANNEALING
#include <bits/stdc++.h>
using namespace std;
vector<int> cities;
vector<int> finalOrder;
int arr[395];       // arr is the array that stores the City order
int dist[395][395]; //dist[i][j] stores distance b/w cities i,j
class TSP
{
public:
    double points[395][2];
    int numcities;
    int CalculateDistance(int x1, int y1, int x2, int y2)
    {
        return int(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
    }
    void input_pos()
    {
        cout << "enter no of cities";
        cin >> numcities;
        int i = 0;
        cout << "Enter cordinates of points" << endl;
        while (i < numcities)
        {
            cin >> points[i][0] >> points[i][1];
            i++;
        }
    }
    void dist_graph()
    {
        for (int i = 0; i < numcities; i++)
        {
            dist[i][i] = 0;
            for (int j = i + 1; j < numcities; j++)
            {
                dist[i][j] = CalculateDistance(points[i][0], points[i][1], points[j][0], points[j][1]);
                dist[j][i] = dist[i][j];
            }
        }
    }
};
int getTourLength(vector<int> c) //returns tour length of a given order of city
{
    vector<int>::iterator it = c.begin();
    it = c.begin();
    int pcity1 = *it, ncity;
    int tourLength = dist[0][pcity1];
    for (it = c.begin() + 1; it != c.end(); it++)
    {
        ncity = *it;
        tourLength += dist[pcity1][ncity];
        pcity1 = ncity;
    }
    tourLength += dist[pcity1][0]; //adding the distance back to the source path
    return tourLength;
}
int get_initial_tour_length(int n) // finds the initial tour length byarranging city according to nearest neighbour
{
    vector<int>::iterator it;
    int i, j;
    for (i = 0; i < n; i++)
    {
        arr[i] = i;
    }
    int best, bestIndex;
    for (i = 1; i < n; i++)
    {
        best = INT_MAX;
        for (j = i; j < n; j++)
        {
            if (dist[i - 1][j] < best)
            {
                best = dist[i][j];
                bestIndex = j;
            }
        }
        swap(i, bestIndex);
    }
    cities.clear();
    for (i = 1; i < n; i++)
    {
        cities.push_back(arr[i]);
        finalOrder.push_back(arr[i]);
    }
    int TourLength = getTourLength(cities);
    return TourLength;
}
double getProbability(int difference, double temperature) //This function finds the probability of how bad the new solution is
{
    return 1 / (1 + exp(-difference / temperature));
}
void copy(vector<int> &c, vector<int> source) //  copies the current order of cites in temp
{
    for (int i = 0; i < source.size(); i++)
    {
        c.push_back(source[i]);
    }
}
int main()
{
    TSP obj;
    vector<int>::iterator it2;
    obj.input_pos(); //imput_pos this function store the  cordinates of cities in 2 d array points[][]
    obj.dist_graph();
    int numOfCities = obj.numcities;
    int tourlength = get_initial_tour_length(obj.numcities);
    int Tm = 1000;
    int iter_max = 100000;
    for (int i = 1; i < iter_max; i++)
    {
        vector<int> pos;
        int r1 = 0;
        int r2 = 0;
        while (r1 == r2)
        {
            r1 = rand() % (numOfCities - 1);
            r2 = rand() % (numOfCities - 1);
        }
        pos.push_back(r1);
        pos.push_back(r2);
        sort(pos.begin(), pos.end());
        vector<int> temp; // to store the new order of cities
        copy(temp, cities);
        reverse(temp.begin() + pos[0], temp.begin() + pos[1]);
        int newTourLength = getTourLength(temp);
        int E = tourlength - newTourLength;
        int T = Tm / i;
        if (E > 0 or (E < 0 and (getProbability(E, T) > rand() % 2)))
        {
            finalOrder.clear();
            cities.clear();
            for (it2 = temp.begin(); it2 != temp.end(); it2++)
            {
                finalOrder.push_back(*it2);
                cities.push_back(*it2);
            }
        }
        tourlength = getTourLength(cities);
        pos.clear();
    }
    vector<int>::iterator itrt, itr1;
    itr1 = finalOrder.begin();
    int xinit = obj.points[*(itr1)][0];
    int yinit = obj.points[*(itr1)][1];
    cout << " x cordinates are--" << endl;
    for (itrt = finalOrder.begin(); itrt != finalOrder.end(); itrt++)
    {
        int x2 = obj.points[*(itrt)][0];
        int y2 = obj.points[*(itrt)][1];
        cout << x2 << ",";
    }
    cout << xinit;
    cout << endl;
    cout << " y cordinates are--" << endl;
    for (itrt = finalOrder.begin(); itrt != finalOrder.end(); itrt++)
    {
        int x2 = obj.points[*(itrt)][0];
        int y2 = obj.points[*(itrt)][1];
        cout << y2 << ",";
    }
    cout << yinit << endl;
    cout << "final order is" << endl;
    for (itrt = finalOrder.begin(); itrt != finalOrder.end(); itrt++)
    {
        cout << *itrt << "->";
    }
    cout << *itr1;
}