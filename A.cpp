#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

void printTab(int *tab);
void print_x(vector<pair<int, int>> x);
void print_A(vector<vector<pair<int, int>>> A);
void problem_init(string input_file, int objectif_number, int costs[32][8]);
vector<int> eval_x(vector<pair<int, int>> x);
vector<pair<int, int>> generate_random_solution();
bool dominate(vector<int> obj1, vector<int> obj_prime);

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
    for (int i = 0; i < 10; i++)
    {
        vector<pair<int, int>> x = generate_random_solution();
        vector<int> y = eval_x(x);
        A.push_back(make_pair(x, y));
    }

    // Pareto Local Search Algorithm
    P = A;
    P_a.clear();

    while (P.empty())
    { // condition mauvaise
        for (int i = 0; i < P.size(); i++)
        {
            // Recherche du voisinage de la solution P[i]
            // Bouble sur tout le voisinage
            // Si non x' non dominé par x
            // Et si l'objectif de x' différent de l'objectif de x
            // Update(A, x')
        }
    };
    // ----------------------------------------------
    cout << "end" << endl;
    return 1;
}

// sol -> [(i,j), ()]
// func evaluer entrer tab[i][j] et boucler sur tous les objectifs
// recherche locale inverser les i ou les j
// Algo ->
// dominance si la solution est dominée ou pas dans l'archive

// function that return true if a solution x dominate x_prime
bool dominate(vector<int> obj, vector<int> obj_prime)
{

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
        return true;
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

void printTab(int *tab)
{
    cout << "printing " << endl;
    for (int i = 0; i < sizeof(tab); i++)
    {
        cout << tab[i] << ' ';
    }
}

void print_A(vector<vector<pair<int, int>>> A)
{
    cout << "Archive : " << endl;
    for (int i = 0; i < A.size(); i++)
        print_x(A[i]);
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
            cout << costs[i][j] << ' ';
        }
        cout << endl;
    }

    int optimal_solution_number;
    inFile >> optimal_solution_number;
}