#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void printTab(int *tab);
void printX(int n, int X[8][2]);
void problem_init(string input_file, int objectif_number, int costs[32][8], int opt_sol[8][2]);

int main()
{
    // Problem parameters
    const int problem_size = 8;
    const int objectif_number = 2;
    int costs[32][8];
    int opt_sol[8][2];
    string input_file = "input/LAP_8x8_2_obj_SOL.txt";

    // Problem init to get cost matrcies and optimal solutions
    problem_init(input_file, objectif_number, costs, opt_sol);

    // Pareto Local Serach Init
    vector<int> A; // Archive de solutions
    vector<int> P;
    vector<int> P_a;

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // Generation d'une solution admissible aléatoire
    int shuffle_1[problem_size];
    int shuffle_2[problem_size];
    for (int i = 0; i < problem_size; i++) 
    {
        shuffle_1[i] = i;
        shuffle_2[i] = i;
    }
    random_shuffle(shuffle_1, shuffle_1 + problem_size);
    random_shuffle(shuffle_2, shuffle_2 + problem_size);
    int x[problem_size][2];
    for (int i = 0; i < problem_size; i++)
    {
        x[i][1] = shuffle_1[i];
        x[i][2] = shuffle_2[i];
    }
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    // ----------------------------------------------
    // Pareto Local Search
    P = A;
    P_a.clear();
    while (!P.empty())
    {
        for(int i = 0; i < P.size(); i++)
        {
            // Recherche du voisinage de la solution P[i]
            // Bouble sur tout le voisinage
            // Si non x' non dominé par x
            // Et si l'objectif de x' différent de l'objectif de x
            // Update(A, x')
        }
    };
    // ----------------------------------------------

    return 1;
}

// sol -> [(i,j), ()]
// func evaluer entrer tab[i][j] et boucler sur tous les objectifs
// recherche locale inverser les i ou les j
// Algo ->
// dominance si la solution est dominée ou pas dans l'archive

void printTab(int *tab)
{
    cout << "printing " << endl;
    for (int i = 0; i < sizeof(tab); i++)
    {
        cout << tab[i] << ' ';
    }
}

void printX(int n, int X[8][2])
{
    cout << "printing X" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << X[i][1] << ' ' << X[i][2] << endl;
    }
}

void problem_init(string input_file, int objectif_number, int costs[32][8], int opt_sol[8][2])
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

    // Optimal solution
    for (int i = 0; i < optimal_solution_number; i++)
    {
        inFile >> opt_sol[0][0];
        for (int j = 0; j < objectif_number; j++)
        {
            inFile >> opt_sol[i][j];
            cout << opt_sol[i][j] << ' ';
        }
        cout << endl;
    }
}