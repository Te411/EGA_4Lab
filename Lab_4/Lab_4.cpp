#include <iostream>
#include <random>
#include "Function.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	vector <string> code; // кодировки
	vector <double> prisb; // Приспособленности
	double max = 0;
	string maxS = "";
	int N = 0, n =0;
	int k = 0;
	int CurrPrisb = 0;
	int CurrCode =0;
	string maxSPoint = "";
	double maxPoint = 0;
	cout << "Введите желаемое количество шагов для метода: ";
	cin >> N;
	while (N < 2 || N > 32) {
		cout << "Количество шагов должно быть в диапазоне от 2 до 30" << endl;
		cout << "Введите количество шагов еще раз: ";
		cin >> N;
	}

	Landscape(code, prisb);
	for (int i = 0; i < N; i++) {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution <> dis(0, 2);
		k = dis(gen);
		if (k == 0) {
			cout << "\nМетод Монте-Карло:\n";
			cout << "Введите количество шагов для метода Монте-Карло:";
			cin >> n;
			while (n < 2 || n > 32) {
				cout << "Количество шагов должно быть в диапазоне от 2 до 30" << endl;
				cout << "Введите количество шагов еще раз: ";
				cin >> n;
			}
			Monte_Carlo(n, code, prisb, maxSPoint, maxPoint);
			cout << "________________________________________________________\n";
		}
		else if (k == 1) {
			cout << "\nМетод в глубину:\n";
			cout << "Введите количество шагов для метода в глубину:";
			cin >> n;
			while (n < 2 || n > 32) {
				cout << "Количество шагов должно быть в диапазоне от 2 до 30" << endl;
				cout << "Введите количество шагов еще раз: ";
				cin >> n;
			}
			depth_first_search(N, code, prisb, maxSPoint, maxPoint);
			cout << "________________________________________________________\n";
		}
		else if (k == 2) {
			cout << "\nМетод в ширину:\n";
			cout << "Введите количество шагов для метода в ширину:";
			cin >> n;
			while (n < 2 || n > 32) {
				cout << "Количество шагов должно быть в диапазоне от 2 до 30" << endl;
				cout << "Введите количество шагов еще раз: ";
				cin >> n;
			}
			Breadth_first_search(N, code, prisb, maxSPoint, maxPoint);
			cout << "________________________________________________________\n";
		}
		if (max < maxPoint) {
			max = maxPoint;
			maxS = maxSPoint;
		}
	}
	cout << "\nПосле работы всех методов: \n максимальная кодировка: " << maxS << "; максимальная приспособленность этой кодировки: " << max;
	return 0;
}