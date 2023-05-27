#pragma once
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Questions
{
public:

	pair<vector<int>, vector<double>> questions(int aim) {

		int option;
		double nakop;
		vector<int> values;
		vector<double> weights;
		cout << "������ ��� ��������� �������� �� ��������� ��������, ����� ��������� ������ ����� ���������� ������� ���������� �����\n"
			<< "���� ����� �� ������ ��, ������ 1; ���� ��� - ������ 0;" << endl;

		cout << "������� ������ ����� 5 ���� ��� ������?" << endl;
		cin >> option;
		cin.ignore();
		values.push_back(option);
		weights.push_back(0.8);

		cout << "������ ������ ������������ ����� ����������� ������ ��� �������?" << endl;
		cin >> option;
		cin.ignore();
		values.push_back(option);

		cout << "������� ��� ������� ����� �� ����������" << endl;
		cin >> nakop;


		if (nakop <= 1) {
			weights.push_back(0.8);

		}

		else if (nakop > 1 && nakop <= 2) {
			weights.push_back(0.7);
		}

		else if (nakop > 2 && nakop <= 3) {
			weights.push_back(0.6);
		}

		else if (nakop > 3 && nakop < 4) {
			weights.push_back(0.5);
		}

		else {
			weights.push_back(0.3);
		}

		values.push_back(1);



		switch (aim) {

		case 1:


			if (option == 0) {


				weights.push_back(0.4);
				cout << "���� �� � ��� ����������� ����-�� ������������ ������?" << endl;
				cin >> option;
				cin.ignore();
				values.push_back(option);
				if (option == 1) {
					weights.push_back(0.35);
				}

				else {
					weights.push_back(0.65);
				}


			}
			else {

				weights.push_back(0.6);
			}
			break;



		case 2:

			if (option == 0) {
				weights.push_back(0.4);
				cout << "������ ������� ������� �������� ����������, ���������� ��� �� ������� ������ ���������� � ��������� ��������� ������� ����?" << endl;
				cin >> option;
				cin.ignore();
				values.push_back(option);

				if (option == 1) {
					weights.push_back(0.9);
				}
				else {
					weights.push_back(0.1);
				}

			}
			else {
				weights.push_back(0.6);
			}

			cout << "������� �� ������ �� ���������� � ���, ��� �� ������ ���������� � �������?";
			cin >> option;
			cin.ignore();
			values.push_back(option);
			if (option == 1) {
				weights.push_back(0.99);
			}
			else {
				weights.push_back(0.01);
			}

			break;

		case 3:
			if (option == 1) {
				weights.push_back(0.6);

			}
			else {
				weights.push_back(0.4);
			}

			break;
		case 4:

			if (option == 0) {
				weights.push_back(0.4);
				cout << "���� �� � ��� ����������� ������������ ������ ��Ĩ����� �������� (������� ������� �� ����������� �����������?";
				cin >> option;
				cin.ignore();
				values.push_back(option);
				if (option == 1) {
					weights.push_back(0.1);
				}
				else {
					weights.push_back(0.9);
				}


			}
			else {
				weights.push_back(0.6);
			}
			break;


		}
		return make_pair(values, weights);



	}
	
	

};