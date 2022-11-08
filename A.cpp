#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

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

int main()
{
    int n, nbObj;
    string line;

    cout << "number of objectives" << endl;
    cin >> nbObj;

    ifstream inFile("input/LAP_8x8_2_obj_SOL.txt");
    inFile >> n;

    int tab[32][n];
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            inFile >> tab[i][j];
            cout << tab[i][j] << ' ';
        }
        cout << endl;
    }

    int nbSol;
    inFile >> nbSol;
    int sol[nbSol][nbObj];
    for (int i = 0; i < nbSol; i++)
    {
        inFile >> sol[0][0];
        for (int j = 0; j < nbObj; j++)
        {
            inFile >> sol[i][j];

            cout << sol[i][j] << ' ';
        }
        cout << endl;
    }

    // premiere solution

    vector<int> A;
    int p1[n];
    int p2[n];
    for (int i = 0; i < n; i++)
    {
        p1[i] = i;
        p2[i] = i;
    }

    random_shuffle(p1, p1 + n);
    random_shuffle(p2, p2 + n);

    int X[n][2];
    for (int i = 0; i < n; i++)
    {
        X[i][1] = p1[i];
        X[i][2] = p2[i];
    }

    return 1;
}

// sol -> [(i,j), ()]

// func evaluer entrer tab[i][j] et boucler sur tous les objectifs

// recherche locale inverser les i ou les j

// Algo ->
// dominance si la solution est dominée ou pas dans l'archive
