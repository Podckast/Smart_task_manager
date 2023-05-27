#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include "Perceptron.h"
#include "Questions.h"

using namespace std;

class Productivity_bot
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

        

        ofstream f("Discipline_base.txt");

        cout << "Заполните список дисциплин";

        vector<string> list_of_disciplines;
        
        

        switch (aim) {
        case 1:
            cout << "Введите все учебные дисциплины в порядке возрастания вашего текущего накопа по ним\n"
                << "(Начиная от дисциплины, по которой у вас самый низкий накоп, заканчивая той, по которой самый высокий\n"
                << "(Если накоп по всем дисциплинам равен нулю, введите дисциплины в любом порядке" << endl;
            break;
        case 2:
            cout << "Введите все учебные дисциплины в порядке убывания важности (начиная от самой важной, заканчивая самой бесполезной по вашему мнению)" << endl;
            break;

        case 3:
            cout << "Введите все учебные дисциплины в порядке убывания интересности (начиная от самой интересной, заканчивая самой скучной по вашему мнению)" << endl;
            break;

        case 4:
            cout << "Введите все учебные дисциплины в порядке убывания количества кредитов, получаемых за дисциплину\n"
                << "(Если у двух или более дисциплин количество получаемых кредитов совпадает, начните с тех, которые вам больше по душе" << endl;
            break;



        }



        for (int i = 0; i < count_of_disciplines; i++) {

            SetConsoleCP(1251);
            SetConsoleOutputCP(1251);

            cout << "Введите " << (i + 1) << " дисциплину" << endl;
            

            string discipline;

            cin >> discipline;
            
            list_of_disciplines.push_back(discipline);

            f << discipline << endl;
           
        }
        
        cout << "Все дисциплины успешно добавлены!" << endl;
        f.close();
        




    }

    vector<string> creation_list_of_disciplines() {

        string discipline;
        vector<string> list_of_disciplines;
      

        ifstream f("Discipline_base.txt");

        if (f.is_open()) {
            while (f >> discipline) {
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
    
    string get_key(map<string, double> tasks, int task) {
        
        for (auto const& p : tasks) {
            if (p.second == task) {
                return p.first;
            }
        }


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

int main() {
    while (true) {

        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

        Productivity_bot bot;

        Questions question_ex;
        pair<vector<int>, vector<double>> params;

        Perceptron perceptron;
        double perceptron_value;
        vector<double> perceptron_values;
        map<string, double> tasks;



        cout << "Вы хотите: \n"
            << "1 - определить цель\n"
            << "2 - заполнить список дисциплин\n"
            << "3 - распределить задачи\n"
            << "4 - выйти из программы" << endl;

        
        int opt, count_of_disciplines;
        int count_of_tasks;
        string task_type;
        string task;
        vector<string> disciplines;

        int aim = 0;
        cin >> opt;
        

        switch (opt) {


        case 1:

            bot.aims_def();
            break;

        case 2:

            aim = bot.aims();
            if (aim == 0) {
                break;
            }
            else {

                cout << "Введите количество учебных дисциплин" << endl;
                cin >> count_of_disciplines;
                
                bot.creation_data_base_of_disciplines(aim, count_of_disciplines);


                break;

                

            }

        case 3:

            aim = bot.aims();
            disciplines = bot.creation_list_of_disciplines();

            cout << "Какое количество задач вы хотите распределить?" << endl;
            cin >> count_of_tasks;

            cin.ignore();

            for (int i = 0; i < count_of_tasks; i++) {


                cout << "Введите " << (i+1) << " задачу" << endl;
                getline(cin, task);
                
               

                cout << "По какой дисциплине задача?" << endl;
                cin >> task_type;
                

                params = question_ex.questions(aim);

                perceptron_value = perceptron.predict(params, disciplines, task_type);

                perceptron_values.push_back(perceptron_value);

                tasks[task] = perceptron_value;

                cin.ignore();

                


            }

            perceptron_values = bot.mergeSort(perceptron_values);

            for (auto i = tasks.begin(); i != tasks.end(); ++i) {
                

                cout << i->first << " - " << i->second << endl;

            }
        case 4:

            return 0;

        }
        
    }
   
    return 0;
}