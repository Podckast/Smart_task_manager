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
#include "Smart_task_manager.h"
#include <cmath>
#undef max

using namespace std;

int main() {
    while (true) {

        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

        Smart_task_manager stm;

        Questions question_ex;
        pair<vector<int>, vector<double>> params;

        Perceptron perceptron;
        double perceptron_value;
        vector<double> perceptron_values;
        map<string, double> tasks;
        vector<string> task_list;
        vector<string> discipline_list;
        int k = 0;


        
        


        cout << "Вы хотите: \n"
            << "1 - Определить цель\n"
            << "2 - Создать и заполнить новый список дисциплин или добавить новые дисциплины в старый\n"
            << "3 - Заполнить список задач и распределить их по степени важности\n"
            << "4 - Вывести список задач\n"
            << "5 - Изменить цель (вам придётся заново заполнять список дисциплин и список задач!)\n"
            << "6 - Удалить выполненнную задачу из списка задач\n"
            << "7 - Вывести список дисциплин\n"
            << "8 - Удалить список задач\n"
            << "9 - Выйти из программы"

            << endl;


        
        int opt, count_of_disciplines;
        int choice;
        int count_of_tasks;
        string task_type;
        string task;
        string task_to_delete;
        vector<string> disciplines;

        int aim = 0;
        cin >> opt;
        

        switch (opt) {


        case 1:
            
            aim = stm.aims();

            if (aim != 0) {
                cout << "Цель уже определена!" << endl;
                break;
            }

            else {
                stm.aims_def();
                cout << "Цель определена" << endl;
                cout << endl;
                break;
            }
           

        case 2:

            aim = stm.aims();
            if (aim == 0) {
                cout << "Вы забыли определить цель" << endl;
                break;
            }
            else {

                cout << "Введите количество учебных дисциплин" << endl;
                cin >> count_of_disciplines;
                
                stm.creation_data_base_of_disciplines(aim, count_of_disciplines);


                break;

                

            }

        case 3:

            
            aim = stm.aims();
            disciplines = stm.creation_list_of_disciplines();
            if (disciplines.size() == 0) {
                cout << "Вы не заполнили список дисциплин!" << endl;
                cout << endl;
                break;
            }
            
            cout << "Какое количество задач вы хотите распределить?" << endl;
            cin >> count_of_tasks;

            cin.ignore();

            for (int i = 0; i < count_of_tasks; i++) {


                cout << "Введите " << (i+1) << " задачу" << endl;
                getline(cin, task);
                
                cout << "По какой дисциплине задача? (вводите дисциплину так же, как вы её ввводили, когда заполняли список дисциплин!)" << endl;
                getline(cin, task_type);
                

                params = question_ex.questions(aim);

                perceptron_value = perceptron.predict(params, disciplines, task_type);

                if (perceptron_value == 0) {
                    cout << "Вы неправильно ввели название дисциплины!" << endl;
                    cout << endl;
                    break;
                }

                else {
                    perceptron_values.push_back(perceptron_value);

                    tasks[task] = perceptron_value;

                    cin.ignore();
                }
                
                
                


            }
            
            if (perceptron_values.size() > 0) {
                perceptron_values = stm.mergeSort(perceptron_values);

                cout << "Ваш список задач: " << endl;
                cout << endl;

                for (const auto& value : perceptron_values) {

                    for (const auto& item : tasks) {

                        if (item.second == value) {

                            k++;
                            cout << k << " приоритет: " << item.first << endl;
                            stm.task_file_write(item.first);


                        }
                    }

                }
                cout << endl;
                break;
            }
            
            
            

        case 4:

            
            task_list = stm.task_file_read();
            if (task_list.size() == 0) {
                cout << "Ваш список задач пуст" << endl;
                break;
            }
            else {

                cout << "Ваш текущий список задач: " << endl;

                k = 0;

                for (auto el : task_list) {
                    k++;
                    cout << k << " приоритет: " << el << endl;

                }
                cout << endl;
                break;
            }
            

            
        case 5:
            cout << "Вы точно хотите изменить цель? (1 - да, 0 - нет)" << endl;
            cin >> choice;
            
            if (choice == 1) {
                remove("Aim.txt");
                remove("Discipline_base.txt");
                remove("Task_file.txt");
                cout << "Ваша текущая цель онулирована, нажмите 1 на главном меню, чтобы выбрать новую цель (ваши списки дисциплин и задач также удалились, вам необходимо заново их заполнять)" << endl;
                cout << endl;
                break;
            }
            else {
                break;
            }

        case 6:

            cout << "Введите задачу, которую вы выполнили и хотите убрать из списка задач" << endl;
            cin.ignore();
            getline(cin, task_to_delete);
            stm.task_del(task_to_delete);
            
            cout << "Задача удалена из списка задач" << endl;
            cout << endl;
            break;
            
        case 7:

            discipline_list = stm.discipline_file_read();

            if (discipline_list.size() == 0) {
                cout << "Вы не создали список дисциплин" << endl;
                cout << endl;
                break;
            }
            cout << "Ваш список дисциплин: " << endl;
            for (auto el : discipline_list) {

                cout << el << endl;

            }
            cout << endl;
            break;

        case 8:
            cout << "Вы точно хотите удалить список текущих задач? (1 - да, 0 - нет)" << endl;
            cin >> opt;
            if (opt == 1) {
                remove("Task_file.txt");
                cout << "Текущий список задач удалён" << endl;
                cout << endl;
                break;
            }
            else {
                break;
            }

        case 9:

            return 0;

        }


        
    }
   
    return 0;
}
