#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

void printTab(int *tab);
void print_x(vector<pair<int, int>> x);
void print_A(vector<pair<vector<pair<int, int>>, vector<int>>> A);
void problem_init(string input_file, int objectif_number, int costs[32][8]);
vector<int> eval_x(vector<pair<int, int>> x);
vector<pair<int, int>> generate_random_solution();
bool dominate(vector<int> obj1, vector<int> obj_prime);
vector<vector<pair<int, int>>> vertical_neighborhood(vector<pair<int, int>> x);
bool equal_obj(vector<int> obj, vector<int> obj_prime);
bool update(vector<pair<vector<pair<int, int>>, vector<int>>> A, vector<pair<int, int>> x_prime);

const int problem_size = 8;
const int objectif_number = 2;
int costs[problem_size * 4][problem_size];

int main()
{
    string input_file = "input/LAP_8x8_2_obj_SOL.txt";

    problem_init(input_file, objectif_number, costs);

    vector<pair<vector<pair<int, int>>, vector<int>>> A; // Archive de solutions
    vector<pair<vector<pair<int, int>>, vector<int>>> P;
    vector<pair<vector<pair<int, int>>, vector<int>>> P_a;

    // Generation aleatoire de l archive
    for (int i = 0; i < 5; i++)
    {
        vector<pair<int, int>> x = generate_random_solution();
        vector<int> y = eval_x(x);
        A.push_back(make_pair(x, y));
    }

    // Pareto Local Search Algorithm
    cout << "Pareto Local Search Algorithm ..." << endl;
    P = A;
    P_a.clear();
    while (!P.empty())
    { 
        cout << "A size : " << P.size() << endl;
        for (int i = 0; i < P.size(); i++) // P[i].first est la solution courante x
        {
            vector<pair<int, int>> x = P[i].first;
            vector<int> y = P[i].second;

            vector<vector<pair<int, int>>> N = vertical_neighborhood(P[i].first);

            for (int j = 0; j < N.size(); j++) // N[j] est la solution courante x_prime
            {
                vector<pair<int, int>> x_prime = N[j];
                vector<int> y_prime = eval_x(N[j]);

                if (!dominate(y, y_prime) && !equal_obj(y, y_prime))
                {
                    if (update(A, x_prime))
                    {
                        P_a.push_back(make_pair(x_prime, y_prime));
                    }
                }
            }
        }
        P = P_a;
        P_a.clear();
    };

    cout << "end" << endl;
    return 1;
}


bool update(vector<pair<vector<pair<int, int>>, vector<int>>> A, vector<pair<int, int>> x_prime)
{
    // x_prime est-il dominé par une solution de l archive
    // Si oui, on ne fait rien
    for(int i = 0; i < A.size(); i++) 
    {
        vector<int> y = A[i].second;
        vector<int> y_prime = eval_x(x_prime);
        if (dominate(y, y_prime))
        {
            return false;
        }
    }

    // Si non, l'ajoute a l archive
    // Et on supprime toutes les solutions de l archive qui sont dominées par x_prime
    for (int i = A.size() - 1; i >= 0; i--)
    {
        vector<int> y = A[i].second;
        vector<int> y_prime = eval_x(x_prime);
        if (dominate(y_prime, y))
        {
            A.erase(A.begin() + i);
        }
    }
    A.push_back(make_pair(x_prime, eval_x(x_prime)));

    return true; //return true si x_prime est ajouté dans l archive
}

vector<vector<pair<int, int>>> vertical_neighborhood(vector<pair<int, int>> x)
{
    vector<vector<pair<int, int>>> neighborhood;

    for (int i = 0; i < x.size(); i++)
    {
        int temp = x[i].second;
        for (int j = 0; j < x.size(); j++)
        {
            if (i != j)
            {
                vector<pair<int, int>> x_prime = x;
                x_prime[i].second = x_prime[j].second;
                x_prime[j].second = temp;
                neighborhood.push_back(x_prime);
            }
        }
        break;
    }
    return neighborhood;
}

bool equal_obj(vector<int> obj, vector<int> obj_prime)
{
    for (int i = 0; i < obj.size(); i++)
    {
        if (obj[i] != obj_prime[i])
        {
            return false;
        }
    }
    return true;
}

bool dominate(vector<int> obj, vector<int> obj_prime){

    /*
    Definition : x domine x_prime SSI
    1. x est meilleur ou egale sur tout les objectifs
    2. x est strictement meilleur sur au moins un objectif
    */

    bool stricly_inf_found = false;

    for (int i = 0; i < objectif_number; i++)
    {
        if (obj[i] > obj_prime[i])
        {
            return false; // x ne domine pas x_prime
        }
        else if (!stricly_inf_found && obj[i] < obj_prime[i])
        {
            stricly_inf_found = true; // x est strictement meilleur sur un objectif
        }
    }

    if (stricly_inf_found)
    {
        return true; // return true if x dominate x_prime
    }
    return false;
}

vector<pair<int, int>> generate_random_solution()
{
    int shuffle_1[problem_size];
    int shuffle_2[problem_size];
    for (int i = 0; i < problem_size; i++)
    {
        shuffle_1[i] = i;
        shuffle_2[i] = i;
    }
    random_shuffle(shuffle_1, shuffle_1 + problem_size);
    random_shuffle(shuffle_2, shuffle_2 + problem_size);

    vector<pair<int, int>> x;

    for (int i = 0; i < problem_size; i++)
    {
        x.push_back(make_pair(shuffle_1[i], shuffle_2[i]));
    }

    return x;
}

vector<int> eval_x(vector<pair<int, int>> x)
{
    vector<int> obj(objectif_number, 0);

    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < objectif_number; j++)

            // obj[0] += costs[x[i].first][x[i].second];
            // obj[1] += costs[x[i].first + 8][x[i].second];
            // obj[2] += costs[x[i].first + 16][x[i].second];
            // obj[3] += costs[x[i].first + 24][x[i].second];

            obj[j] += costs[x[i].first + (problem_size * (j))][x[i].second];
    }

    return obj;
}


void print_A(vector<pair<vector<pair<int, int>>, vector<int>>> A)
{
    cout << "Archive : " << endl;
    for (int i = 0; i < A.size(); i++)
        print_x(A[i].first);
}

void print_x(vector<pair<int, int>> x)
{
    cout << "x : ";
    for (int i = 0; i < x.size(); i++)
        cout << "(" << x[i].first << ", " << x[i].second << ") ";
    cout << endl;
}

void problem_init(string input_file, int objectif_number, int costs[32][8])
{
    int problem_size;
    ifstream inFile(input_file);
    inFile >> problem_size;

    // Cost matrices
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < problem_size; j++)
        {
            inFile >> costs[i][j];
        }
    }

    int optimal_solution_number;
    inFile >> optimal_solution_number;
}