#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include <set>
#include <list>
#include <cmath>

#include "hungarian.h"

using namespace std;

const int problem_size = 30;
const int objectif_number = 4;
int costs[problem_size * 4][problem_size];
string input_file = "input/30_4.txt";
string fileName = "test_30_4.txt";
int number_iterations_1 = 1;
int number_iterations_2 = 1;

void printTab(int *tab);
void print_x(vector<pair<int, int>> x);
void print_sol(vector<pair<vector<pair<int, int>>, vector<int>>> A);
void print_A(vector<pair<vector<pair<int, int>>, vector<int>>> A);

void save_sol(vector<pair<vector<pair<int, int>>, vector<int>>> A);

void problem_init(string input_file, int objectif_number, int costs[problem_size * 4][problem_size]);
vector<int> eval_x(vector<pair<int, int>> x);
vector<pair<int, int>> generate_random_solution();
bool dominate(vector<int> obj1, vector<int> obj_prime);
vector<vector<pair<int, int>>> vertical_neighborhood(vector<pair<int, int>> x);
vector<vector<pair<int, int>>> horizontal_neighborhood(vector<pair<int, int>> x);
bool equal_obj(vector<int> obj, vector<int> obj_prime);
bool update(vector<pair<vector<pair<int, int>>, vector<int>>> A, vector<pair<int, int>> x_prime);
vector<pair<vector<pair<int, int>>, vector<int>>> updatingA(vector<pair<vector<pair<int, int>>, vector<int>>> A, vector<pair<int, int>> x_prime);

vector<pair<vector<pair<int, int>>, vector<int>>> generate_linear_solutions();
vector<pair<int, int>> hungarian_method(list<list<int>> matrix);

int main()
{
    problem_init(input_file, objectif_number, costs);

    vector<pair<vector<pair<int, int>>, vector<int>>> A; // Archive de solutions
    vector<pair<vector<pair<int, int>>, vector<int>>> P;
    vector<pair<vector<pair<int, int>>, vector<int>>> P_a;

    // Generation par des combinaisons lineaires
    A = generate_linear_solutions();

    // Generation aleatoire de l archive
    for (int i = 0; i < 500; i++)
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

            vector<vector<pair<int, int>>> N;
            vector<vector<pair<int, int>>> temp;
            temp = vertical_neighborhood(P[i].first);
            N.insert(N.end(), temp.begin(), temp.end());
            temp = horizontal_neighborhood(P[i].first);
            N.insert(N.end(), temp.begin(), temp.end());

            for (int j = 0; j < N.size(); j++) // N[j] est la solution courante x_prime
            {
                vector<pair<int, int>> x_prime = N[j];
                vector<int> y_prime = eval_x(N[j]);

                if (!dominate(y, y_prime) && !equal_obj(y, y_prime))
                {
                    if (update(A, x_prime))
                    {
                        A = updatingA(A, x_prime);
                        cout << "size A " << A.size() << endl;
                        P_a.push_back(make_pair(x_prime, y_prime));
                    }
                }
            }
        }
        P = P_a;
        P_a.clear();
    };

    cout << A.size() << endl;
    print_sol(A);
    save_sol(A);
    cout << "end" << endl;
    return 1;
}

bool update(vector<pair<vector<pair<int, int>>, vector<int>>> A, vector<pair<int, int>> x_prime)
{
    // x_prime est-il dominé par une solution de l archive
    // Si oui, on ne fait rien
    vector<int> y_prime = eval_x(x_prime);
    sort(x_prime.begin(), x_prime.end());
    for (int i = 0; i < A.size(); i++)
    {
        vector<int> y = A[i].second;
        sort(A[i].first.begin(), A[i].first.end());

        if (dominate(y, y_prime))
        {
            return false;
        }
        if (A[i].first == x_prime)
        {
            return false;
        }
    }
    return true;
}

vector<pair<vector<pair<int, int>>, vector<int>>> updatingA(vector<pair<vector<pair<int, int>>, vector<int>>> A, vector<pair<int, int>> x_prime)
{
    // Si non, l'ajoute a l archive
    // Et on supprime toutes les solutions de l archive qui sont dominées par x_prime
    int size_a = A.size();
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
    cout << "sizes " << size_a << " " << A.size() << endl;

    return A;
}

vector<vector<pair<int, int>>> vertical_neighborhood(vector<pair<int, int>> x)
{
    vector<vector<pair<int, int>>> neighborhood;

    vector<int> y = eval_x(x);

    for (int i = 0; i < number_iterations_1; i++)
    {
        int pi = rand() % x.size();
        int temp = x[pi].second;
        for (int j = 0; j < number_iterations_2; j++)
        {
            int pj = rand() % x.size();
            if (pi != pj)
            {
                vector<pair<int, int>> x_prime = x;
                x_prime[pi].second = x_prime[pj].second;
                x_prime[pj].second = temp;
                neighborhood.push_back(x_prime);
            }
        }
    }
    return neighborhood;
}

vector<vector<pair<int, int>>> horizontal_neighborhood(vector<pair<int, int>> x)
{
    vector<vector<pair<int, int>>> neighborhood;
    for (int i = 0; i < number_iterations_1; i++)
    {
        int pi = rand() % x.size();
        int temp = x[pi].first;
        for (int j = 0; j < number_iterations_2; j++)
        {
            int pj = rand() % x.size();
            if (pi != pj)
            {
                vector<pair<int, int>> x_prime = x;
                x_prime[pi].first = x_prime[pj].first;
                x_prime[pj].first = temp;
                neighborhood.push_back(x_prime);
            }
        }
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

void print_sol(vector<pair<vector<pair<int, int>>, vector<int>>> A)
{
    set<vector<int>> printed;
    cout << "Solutions : " << endl;
    for (int i = 0; i < A.size(); i++)
    {
        if (printed.find(A[i].second) != printed.end())
        {
            break;
        }
        for (int j = 0; j < A[i].second.size(); j++)
        {
            cout << A[i].second[j] << " ";
        }
        cout << endl;
        printed.insert(A[i].second);
    }
}

void save_sol(vector<pair<vector<pair<int, int>>, vector<int>>> A)
{
    ofstream outFile;
    outFile.open(fileName);
    set<vector<int>> printed;
    int nbSol = 0;
    for (int i = 0; i < A.size(); i++)
    {
        if (printed.find(A[i].second) != printed.end())
        {
            break;
        }
        for (int j = 0; j < A[i].second.size(); j++)
        {
            cout << A[i].second[j] << " ";
        }
        cout << endl;
        printed.insert(A[i].second);
        nbSol++;
    }

    outFile << nbSol << endl;
    printed.clear();

    for (int i = 0; i < A.size(); i++)
    {
        if (printed.find(A[i].second) != printed.end())
        {
            break;
        }
        for (int j = 0; j < A[i].second.size(); j++)
        {
            outFile << A[i].second[j] << " ";
        }
        outFile << endl;
        printed.insert(A[i].second);
    }
}

void print_x(vector<pair<int, int>> x)
{
    cout << "x : ";
    for (int i = 0; i < x.size(); i++)
        cout << "(" << x[i].first << ", " << x[i].second << ") ";
    cout << endl;
}

void problem_init(string input_file, int objectif_number, int costs[problem_size * 4][problem_size])
{
    int problem_size;
    ifstream inFile(input_file);
    inFile >> problem_size;

    // Cost matrices
    for (int i = 0; i < problem_size * 4; i++)
    {
        for (int j = 0; j < problem_size; j++)
        {
            inFile >> costs[i][j];
        }
    }

    int optimal_solution_number;
    inFile >> optimal_solution_number;
}

vector<pair<vector<pair<int, int>>, vector<int>>> generate_linear_solutions()
{
    vector<pair<vector<pair<int, int>>, vector<int>>> A;
    for (int gen = 0; gen < 5; gen++)
    {
        int tests[problem_size][problem_size] = {0};
        for (int i = 0; i < objectif_number; i++)
        {
            int coef = rand() % 20;

            for (int i = 0; i < problem_size; i++)
            {
                for (int j = 0; j < problem_size; j++)
                {
                    tests[i][j] = tests[i][j] + coef * costs[i][j];
                }
            }
        }
        list<list<int>> matrix;

        for (int i = 0; i < problem_size; i++)
        {
            list<int> mi;
            for (int j = 0; j < problem_size; j++)
            {
                mi.push_back(tests[i][j]);
            }
            matrix.push_back(mi);
        }

        vector<pair<int, int>> generated_sol;

        generated_sol = hungarian_method(matrix);

        vector<int> y = eval_x(generated_sol);

        for (int i = 0; i < A.size(); i++)
        {
            vector<int> y = A[i].second;
            sort(A[i].first.begin(), A[i].first.end());

            if (A[i].first != generated_sol)
            {
                A.push_back(make_pair(generated_sol, y));
            }
        }
    }

    return A;
}

vector<pair<int, int>> hungarian_method(list<list<int>> matrix)
{
    auto res = hungarian(matrix);

    vector<pair<int, int>> random_sol;
    for (int i = 0; i < problem_size; i++)
    {
        for (int j = 0; j < problem_size; j++)
        {
            if (res[i][j] == 1)
            {
                random_sol.push_back(make_pair(i, j));
            }
        }
    }

    return random_sol;
}