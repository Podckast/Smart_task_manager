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
		cout << "Сейчас вам предстоит ответить на несколько вопросов, чтобы нейросеть смогла чётко определить порядок выполнения задач\n"
			<< "Если ответ на вопрос да, пишите 1; если нет - пишите 0;" << endl;

		cout << "Дедлайн задачи через 5 дней или меньше?" << endl;
		cin >> option;
		//cin.ignore();
		values.push_back(option);
		weights.push_back(0.99);

		cout << "Данная задача представляет собой контрольную работу или экзамен?" << endl;
		cin >> option;
		//cin.ignore();
		values.push_back(option);

		cout << "Введите ваш текущий накоп по дисциплине" << endl;
		cin >> nakop;


		if (nakop <= 1) {
			weights.push_back(0.99);

		}

		else if (nakop > 1 && nakop <= 2) {
			weights.push_back(0.9);
		}

		else if (nakop > 2 && nakop <= 3) {
			weights.push_back(0.8);
		}

		else if (nakop > 3 && nakop < 4) {
			weights.push_back(0.5);
		}

		else {
			weights.push_back(0.01);
		}

		values.push_back(1);



		switch (aim) {

		case 1:


			if (option == 0) {


				weights.push_back(0.4);
				cout << "Есть ли у вас возможность кому-то делегировать задачу?" << endl;
				cin >> option;
				//cin.ignore();
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
				cout << "Задача требует высокой мозговой активности, творческая или же имеется чёткая инструкция с подробным описанием каждого шага?" << endl;
				cin >> option;
				//cin.ignore();
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

			cout << "Связана ли задача по дисциплине с тем, чем вы хотите заниматься в будущем?" << endl;
			cin >> option;
			//cin.ignore();
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
				cout << "Есть ли у вас возможность делегировать задачу НАДЁЖНОМУ человеку (который сделает всё максимально качественно?" << endl;
				cin >> option;
				//cin.ignore();
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
