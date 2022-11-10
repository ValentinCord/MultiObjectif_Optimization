#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void printTab(int *tab);
void print_x(vector<pair<int,int>> x);
void print_A(vector<vector<pair<int,int>>> A);
void problem_init(string input_file, int objectif_number, int costs[32][8], int opt_sol[8][2]);
vector<float> eval_x(vector<pair<int, int>> x);
vector<pair<int, int>> generate_random_solution();
bool dominate(vector<pair<int, int>> x, vector<pair<int, int>> x_prime);

const int problem_size = 8;
const int objectif_number = 2;
int costs[32][8];
int opt_sol[8][2];

int main(){
    string input_file = "input/LAP_8x8_2_obj_SOL.txt";

    problem_init(input_file, objectif_number, costs, opt_sol);

    vector<vector<pair<int, int>>> A; // Archive de solutions
    vector<vector<pair<int, int>>> P;
    vector<vector<pair<int, int>>> P_a;

    for(int i = 0; i < 10; i++) {
        A.push_back(generate_random_solution());
    }

    // Pareto Local Search
    P = A; // effectue une copie
    P_a.clear();

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            if (dominate(A[i], A[j])) {
                
                cout << "---------------" << endl;
                print_x(A[i]);
                vector<float> obj1 = eval_x(A[i]);
                for (int i = 0; i < obj1.size(); i++) {
                    cout << obj1[i] << " ";
                }
                cout << endl;
                print_x(A[j]);
                vector<float> obj2 = eval_x(A[j]);
                for (int i = 0; i < obj2.size(); i++) {
                    cout << obj2[i] << " ";
                }
                cout << endl;
                cout << "---------------" << endl;


            }
        }
    }

 
    while (P.empty()) { // condition mauvaise
        for (int i = 0; i < P.size(); i++) {


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

// function that return true if a solution dominate an other
bool dominate(vector<pair<int, int>> x, vector<pair<int, int>> x_prime){
    bool stricly_inf_found = false;

    vector<float> obj = eval_x(x);
    vector<float> obj_prime = eval_x(x_prime);

    for (int i = 0; i < objectif_number; i++) {
        if (obj[i] > obj_prime[i]) {
            return false; // ne domine pas
        }
        else if (!stricly_inf_found && obj[i] < obj_prime[i]) {
            stricly_inf_found = true; // est strictement meilleur sur un objectif
        }
    }
    
    if (stricly_inf_found) {
        return true;
    }
    return false;
}

vector<pair<int, int>> generate_random_solution(){
    int shuffle_1[problem_size];
    int shuffle_2[problem_size];
    for (int i = 0; i < problem_size; i++) {
        shuffle_1[i] = i;
        shuffle_2[i] = i;
    }
    random_shuffle(shuffle_1, shuffle_1 + problem_size);
    random_shuffle(shuffle_2, shuffle_2 + problem_size);
    vector<pair<int, int>> x;
    for (int i = 0; i < problem_size; i++)
        x.push_back(make_pair(shuffle_1[i], shuffle_2[i]));

    return x;
}

vector<float> eval_x(vector<pair<int, int>> x){

    vector<float> obj;

    for (int j = 0; j < objectif_number; j++)
        obj.push_back(0);

    for (int i = 0; i < x.size(); i++){
       for (int j = 0; j < objectif_number; j++)
            obj[j] += costs[x[i].first * (j + 1)][x[i].second];
    }

    return obj;
}

void printTab(int *tab){
    cout << "printing " << endl;
    for (int i = 0; i < sizeof(tab); i++)
    {
        cout << tab[i] << ' ';
    }
}

void print_A(vector<vector<pair<int,int>>> A){
    cout << "Archive : " << endl;
    for (int i = 0; i < A.size(); i++) 
        print_x(A[i]);
}

void print_x(vector<pair<int,int>> x) {
    cout << "x : ";
    for (int i = 0; i < x.size(); i++)
        cout << "("<< x[i].first << ", " << x[i].second << ") ";
    cout << endl;
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