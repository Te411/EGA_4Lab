#include "Function.h"

// рандомайзер кодировки
string RandomCode(int L) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution <> dis(0, 1);

	string binaryCode = "";

	for (int i = 0; i < L; i++) {
		int number = dis(gen);
		binaryCode += to_string(number);
	}
	return binaryCode;
}

//функция проверки приспособленности
double Function(string binaryCode) {
	if (binaryCode == "0000000") {
		return 0;
	}
	else {
		bitset<L> num1(binaryCode);
		int num = num1.to_ullong();
		double Value = 5 * sin(num) + log(num);
		return round(Value * 100)/100;
	}
}

// Генерация окрестности
vector<string> getNeighborhood(const string binaryCode) {
	vector<string> neighborhood;
	for (int i = 0; i < binaryCode.length(); i++) {
		char flippedBit = (binaryCode[i] == '0') ? '1' : '0';
		string newCode = binaryCode;
		newCode[i] = flippedBit;

		neighborhood.push_back(newCode);
	}
	return neighborhood;
}

// ландшафт поиска
void Landscape(vector <string>& code, vector <double>& prisb) {
	cout << "Ландшафт поиска:\n";
	for (int i = 0; i < 32; i++) {
		code.push_back(RandomCode(L));
		prisb.push_back(Function(code[i]));
		cout << code[i] << " - приспособленность: " << prisb[i] << endl;
	}
}

void Monte_Carlo(int N, vector <string>& code, vector <double>& prisb, string& maxSPoint, double& maxPoint) {
	string S = "";
	maxSPoint = "";
	maxPoint = 0;
	for (int i = 0; i < N; i++) {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution <> dis(0, 31);
		S = code[dis(gen)]; // кодировка

		double mi = prisb[(dis(gen))]; // вычисляем приспособленность


		cout << "Шаг " << i + 1 << " Текущее решение: " << S << endl << " Текущия приспособленность: " << mi << endl << " Лучшее решение: " << maxSPoint << endl << " Лучшая приспособленность: " << maxPoint << endl;

		cout << endl;
		if (mi > maxPoint) {
			maxSPoint = S;
			maxPoint = mi;
			cout << " Новый max: " << maxPoint << endl << " Новый MaxS: " << maxSPoint << endl;
		}
		cout << endl;
	}
	cout << "Общее решение maxS: " << maxSPoint << endl << "Приспособленность общего решения: max = " << maxPoint << endl;
}

void depth_first_search(int N, vector <string>& code, vector <double>& prisb, string& maxSPoint, double& maxPoint) {
	maxPoint = 0; // макс. приспособленность
	maxSPoint = ""; // макс.кодировка
	vector <string> tmp;
	int k = 0;
	int currPrisb = 0;
	int count1 = 0;
	// определяем кодировку и приспособленность

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution <> dis(0, 31);

	maxSPoint = code[dis(gen)]; // кодировка
	maxPoint = prisb[(dis(gen))]; // приспособленность

	vector<string>neighborhood = getNeighborhood((maxSPoint)); // окрестность кодировки

	for (int i = 0; i < N; i++) {
		cout << "Шаг #" << i + 1 << endl;
		cout << "Текущий максимум приспособленности: " << maxPoint << endl;
		cout << "Текущая лучшая кодировка: " << maxSPoint << endl;
		cout << "Полученная на шаге окрестность: " << endl;
		neighborhood = getNeighborhood((maxSPoint));
		k = 0;
		while (k < neighborhood.size()) {
			for (int j = 0; j < tmp.size(); j++) {
				if (tmp[j] == neighborhood[k]) {
					neighborhood.erase(neighborhood.begin() + k);
					k--;
					break;
				}
			}
			k++;
		}
		k = 0;
		while (k < neighborhood.size()) {
			cout << k + 1 << " кодировка окрестности: " << neighborhood[k] << " | её приспособленность: " << Function(neighborhood[k]) << endl;
			k++;
		}
		if (neighborhood.size() > 0) {

			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution <> dis(0, neighborhood.size() - 1);
			int index = dis(gen);

			currPrisb = Function(neighborhood[index]);
			if (maxPoint < currPrisb) {
				maxSPoint = neighborhood[index];
				maxPoint = currPrisb;
				count1++;
			}
			tmp.push_back(neighborhood[index]);
			cout << "Выбираемая кодировка: " << neighborhood[index] << endl;
			cout << "Приспособленность выбираемой кодировки: " << currPrisb << endl;
			if (count1 != 0 && !tmp.empty()) {
				tmp.clear();
				count1 = 0;
			}
			/*cout << endl;*/

			if (maxSPoint == "11111") {
				cout << "_________________________________________________________________ " << endl;
				cout << "Текущий максимум приспособленности: " << maxPoint << endl;
				cout << "Текущая лучшая кодировка: " << maxSPoint << endl;
				cout << "Метод завершился за " << i + 1 << " шаг(ов)." << endl;
				break;
			}
		}
		else {
			break;
		}
	}
}

void Breadth_first_search(int N, vector <string>& code, vector <double>& prisb, string& maxSPoint, double& maxPoint) {
	maxPoint = 0; // макс. приспособленность
	maxSPoint = ""; // макс.кодировка
	int currPrisb = 0;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution <> dis(0, 31);

	maxSPoint = code[dis(gen)]; // кодировка
	maxPoint = prisb[(dis(gen))]; // приспособленность 
	vector<string>neighborhood = getNeighborhood((maxSPoint)); // окрестность кодировки

	int j = 0;
	for (int i = 0; i < N; i++) {
		cout << "Шаг #" << i + 1 << endl;
		cout << "Текущий максимум приспособленности: " << maxPoint << endl;
		cout << "Текущая лучшая кодировка: " << maxSPoint << endl;
		cout << "Полученная на шаге окрестность: " << endl;
		neighborhood = getNeighborhood((maxSPoint));
		for (int k = 0; k < neighborhood.size(); k++) {
			cout << k + 1 << " кодировка окрестности: " << neighborhood[k] << " | её приспособленность: " << Function(neighborhood[k]) << endl;
		}
		j = 0;
		bool flag = false;
		while (!neighborhood.empty()) {
			currPrisb = Function(neighborhood[0]);
			cout << j + 1 << " выбираемая кодировка из окрестности: " << neighborhood[0];
			setw(2);
			cout << "|  Приспособленность выбираемой кодировки: " << currPrisb << endl;
			if (maxPoint < currPrisb) {
				maxSPoint = neighborhood[0];
				maxPoint = currPrisb;
				cout << "-Новая максимальная кодировка: " << maxSPoint << endl;
				cout << "-Новая максимальная приспособленность: " << maxPoint << endl;
				flag = true;
			}
			neighborhood.erase(neighborhood.begin());
			j++;
		}
		cout << endl;
		if (!flag) {
			cout << "Текущий максимум приспособленности: " << maxPoint << endl;
			cout << "Текущая лучшая кодировка: " << maxSPoint << endl;
			cout << "Метод завершился за " << i + 1 << " шаг(ов)." << endl;
			break;
		}
	}
}