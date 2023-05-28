#pragma once
#include <iostream>
#include <limits>
#include <string>
#include <Windows.h>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include "Perceptron.h"
#include "Questions.h"
#include <cmath>
#undef max

using namespace std;

class Smart_task_manager
{
public:

    void aims_def() {

        setlocale(LC_ALL, "Russian");
        cout << "Какие цели вы преследуете?" << endl;
        cout << "Введите 1, если вы акцентируете всё своё внимание только на работе/интересующих вас вещах. Из вуза нужно просто не вылететь\n"
            << "2, если вы акцентируете своё внимание на вузовской программе на всех предметах, при этом вам важно развитие навыков/способностей. Оценки и рейтинг вещи второстепенные. Кроме того, хотите заниматься работой/тем, что мне нравится\n"
            << "3, если вы акцентируете своё внимание только на тех предметах вузовской программы, которые вам интересны. Остальные лишь бы закрыть\n"
            << "4, если вы акцентируете своё внимание на оценки и рейтинг, при этом знания и навыки вам не особо важны" << endl;
        int option;
        cin >> option;

        ofstream f("Aim.txt");
        f << option << endl;
        f.close();

    }


    int aims() {


        ifstream f("Aim.txt");

        if (f.is_open()) {
            int aim;
            f >> aim;
            f.close();
            return aim;
        }
        else {

            cout << "Вы забыли определить цель" << endl;
            return 0;

        }


    }




    void creation_data_base_of_disciplines(int aim, int count_of_disciplines) {



        ofstream f("Discipline_base.txt", ios::app);

        cout << "Заполните список дисциплин" << endl;

        vector<string> list_of_disciplines;



        switch (aim) {
        case 1:
            cout << "Введите все учебные дисциплины в порядке убывания вашего текущего накопа по ним\n"
                << "(Начиная от дисциплины, по которой у вас самый низкий накоп, заканчивая той, по которой самый высокий\n"
                << "(Если накоп по всем дисциплинам равен нулю, введите дисциплины в любом порядке" << endl;
            break;
        case 2:
            cout << "Введите все учебные дисциплины в порядке возрастания важности" << endl;
            break;

        case 3:
            cout << "Введите все учебные дисциплины в порядке возрастания интересности" << endl;
            break;

        case 4:
            cout << "Введите все учебные дисциплины в порядке возрастания количества кредитов, получаемых за дисциплину\n"
                << "(Если у двух или более дисциплин количество получаемых кредитов совпадает, начните с тех, которые вам больше по душе" << endl;
            break;



        }

        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

        cin.ignore();

        for (int i = 0; i < count_of_disciplines; i++) {

            string discipline;

            cout << "Введите " << (i + 1) << " дисциплину" << endl;

            getline(cin, discipline);

            f << discipline << "\n";
        }

        cout << "Все дисциплины успешно добавлены!" << endl;
        f.close();





    }




    vector<string> creation_list_of_disciplines() {

        string discipline;
        vector<string> list_of_disciplines;


        ifstream f("Discipline_base.txt");

        if (f.is_open()) {
            while (getline(f, discipline)) {
                list_of_disciplines.push_back(discipline);

            }
            f.close();
        }
        return list_of_disciplines;

    }


    vector<double> mergeSort(vector<double>& arr) {
        if (arr.size() == 1) {
            return arr;
        }


        int mid_index = arr.size() / 2;
        vector<double> left_arr(arr.begin(), arr.begin() + mid_index);
        vector<double> right_arr(arr.begin() + mid_index, arr.end());


        left_arr = mergeSort(left_arr);
        right_arr = mergeSort(right_arr);


        return merge(left_arr, right_arr);
    }

    void task_file_write(string task) {

        ofstream f_w("Task_file.txt", ios::app);

        if (f_w.is_open()) {
            f_w << task << endl;
        }

        f_w.close();

    }

    vector<string> discipline_file_read() {
        string f_discipline;
        vector<string> discipline_list;
        ifstream f_r("Discipline_base.txt");
        if (f_r.is_open()) {




            while (getline(f_r, f_discipline)) {

                discipline_list.push_back(f_discipline);

            }
            f_r.close();

        }


        return discipline_list;
    }

    vector<string> task_file_read() {



        string f_task;
        vector<string> task_list;
        ifstream f_r("Task_file.txt");
        if (f_r.is_open()) {




            while (getline(f_r, f_task)) {

                task_list.push_back(f_task);

            }
            f_r.close();

        }


        return task_list;

    }

    void task_del(string f_task) {

        ifstream f("Task_file.txt");
        ofstream temp_f("Temp.txt");

        string line;

        while (getline(f, line)) {

            if (line != f_task) {

                temp_f << line << endl;
            }
        }
        f.close();
        temp_f.close();

        remove("Task_file.txt");
        rename("Temp.txt", "Task_file.txt");



    }

private:
    vector<double> merge(vector<double>& left_arr, vector<double>& right_arr) {
        vector<double> merged_arr; // Новый массив для объединения

        int i = 0, j = 0;
        while (i < left_arr.size() && j < right_arr.size()) {
            if (left_arr[i] > right_arr[j]) {
                merged_arr.push_back(left_arr[i]);
                i++;
            }
            else {
                merged_arr.push_back(right_arr[j]);
                j++;
            }
        }


        while (i < left_arr.size()) {
            merged_arr.push_back(left_arr[i]);
            i++;
        }

        while (j < right_arr.size()) {
            merged_arr.push_back(right_arr[j]);
            j++;
        }

        return merged_arr;
    }

};