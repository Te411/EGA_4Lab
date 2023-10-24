#include "Function.h"

// ����������� ���������
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

//������� �������� �����������������
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

// ��������� �����������
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

// �������� ������
void Landscape(vector <string>& code, vector <double>& prisb) {
	cout << "�������� ������:\n";
	for (int i = 0; i < 32; i++) {
		code.push_back(RandomCode(L));
		prisb.push_back(Function(code[i]));
		cout << code[i] << " - �����������������: " << prisb[i] << endl;
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
		S = code[dis(gen)]; // ���������

		double mi = prisb[(dis(gen))]; // ��������� �����������������


		cout << "��� " << i + 1 << " ������� �������: " << S << endl << " ������� �����������������: " << mi << endl << " ������ �������: " << maxSPoint << endl << " ������ �����������������: " << maxPoint << endl;

		cout << endl;
		if (mi > maxPoint) {
			maxSPoint = S;
			maxPoint = mi;
			cout << " ����� max: " << maxPoint << endl << " ����� MaxS: " << maxSPoint << endl;
		}
		cout << endl;
	}
	cout << "����� ������� maxS: " << maxSPoint << endl << "����������������� ������ �������: max = " << maxPoint << endl;
}

void depth_first_search(int N, vector <string>& code, vector <double>& prisb, string& maxSPoint, double& maxPoint) {
	maxPoint = 0; // ����. �����������������
	maxSPoint = ""; // ����.���������
	vector <string> tmp;
	int k = 0;
	int currPrisb = 0;
	int count1 = 0;
	// ���������� ��������� � �����������������

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution <> dis(0, 31);

	maxSPoint = code[dis(gen)]; // ���������
	maxPoint = prisb[(dis(gen))]; // �����������������

	vector<string>neighborhood = getNeighborhood((maxSPoint)); // ����������� ���������

	for (int i = 0; i < N; i++) {
		cout << "��� #" << i + 1 << endl;
		cout << "������� �������� �����������������: " << maxPoint << endl;
		cout << "������� ������ ���������: " << maxSPoint << endl;
		cout << "���������� �� ���� �����������: " << endl;
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
			cout << k + 1 << " ��������� �����������: " << neighborhood[k] << " | � �����������������: " << Function(neighborhood[k]) << endl;
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
			cout << "���������� ���������: " << neighborhood[index] << endl;
			cout << "����������������� ���������� ���������: " << currPrisb << endl;
			if (count1 != 0 && !tmp.empty()) {
				tmp.clear();
				count1 = 0;
			}
			/*cout << endl;*/

			if (maxSPoint == "11111") {
				cout << "_________________________________________________________________ " << endl;
				cout << "������� �������� �����������������: " << maxPoint << endl;
				cout << "������� ������ ���������: " << maxSPoint << endl;
				cout << "����� ���������� �� " << i + 1 << " ���(��)." << endl;
				break;
			}
		}
		else {
			break;
		}
	}
}

void Breadth_first_search(int N, vector <string>& code, vector <double>& prisb, string& maxSPoint, double& maxPoint) {
	maxPoint = 0; // ����. �����������������
	maxSPoint = ""; // ����.���������
	int currPrisb = 0;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution <> dis(0, 31);

	maxSPoint = code[dis(gen)]; // ���������
	maxPoint = prisb[(dis(gen))]; // ����������������� 
	vector<string>neighborhood = getNeighborhood((maxSPoint)); // ����������� ���������

	int j = 0;
	for (int i = 0; i < N; i++) {
		cout << "��� #" << i + 1 << endl;
		cout << "������� �������� �����������������: " << maxPoint << endl;
		cout << "������� ������ ���������: " << maxSPoint << endl;
		cout << "���������� �� ���� �����������: " << endl;
		neighborhood = getNeighborhood((maxSPoint));
		for (int k = 0; k < neighborhood.size(); k++) {
			cout << k + 1 << " ��������� �����������: " << neighborhood[k] << " | � �����������������: " << Function(neighborhood[k]) << endl;
		}
		j = 0;
		bool flag = false;
		while (!neighborhood.empty()) {
			currPrisb = Function(neighborhood[0]);
			cout << j + 1 << " ���������� ��������� �� �����������: " << neighborhood[0];
			setw(2);
			cout << "|  ����������������� ���������� ���������: " << currPrisb << endl;
			if (maxPoint < currPrisb) {
				maxSPoint = neighborhood[0];
				maxPoint = currPrisb;
				cout << "-����� ������������ ���������: " << maxSPoint << endl;
				cout << "-����� ������������ �����������������: " << maxPoint << endl;
				flag = true;
			}
			neighborhood.erase(neighborhood.begin());
			j++;
		}
		cout << endl;
		if (!flag) {
			cout << "������� �������� �����������������: " << maxPoint << endl;
			cout << "������� ������ ���������: " << maxSPoint << endl;
			cout << "����� ���������� �� " << i + 1 << " ���(��)." << endl;
			break;
		}
	}
}