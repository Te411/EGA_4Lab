#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <locale.h>
#include <vector>
#include <sstream>
#include <bitset>
#include <iomanip>
#include <cmath>
using namespace std;

const int L = 7; // размерность пространства поиска
string RandomCode(int L);
double Function(string binaryCode);
vector<string> getNeighborhood(const string binaryCode);
void Monte_Carlo(int N, vector <string>& code, vector <double>& prisb, string& maxSPoint, double& maxPoint);
void depth_first_search(int N, vector <string>& code, vector <double>& prisb, string& maxSPoint, double& maxPoint);
void Breadth_first_search(int N, vector <string>& code, vector <double>& prisb, string& maxSPoint, double& maxPoint);
void Landscape(vector <string>& code, vector <double>& prisb);

