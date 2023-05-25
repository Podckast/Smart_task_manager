#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
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


        cout << "Вы хотите: \n"
            << "1 - определить цель\n"
            << "2 - заполнить список дисциплин\n"
            << "3 - распределить задачи\n"
            << "4 - выйти из программы" << endl;

        
        int opt, count_of_disciplines;
        string task_type;
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
            cout << aim << endl;

            cout << "По какой дисциплине задача?" << endl;
            cin >> task_type;

            disciplines = bot.creation_list_of_disciplines();

            
            params = question_ex.questions(aim);

            
            perceptron_value = perceptron.predict(params, disciplines, task_type);

            cout << perceptron_value << endl;
            
          
            
            break;



        

        
        case 4:

            return 0;

            
       
        }
        
    }
   
    return 0;
}