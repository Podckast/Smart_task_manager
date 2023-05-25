#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#define _SQLITE3_H
#include <sqlite3.h>
#include <sstream>
#include <fstream>
#include "Perceptron.h"
#include "Questions.h"


using namespace std;



class Productivity_bot {

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
        f << option;
        f.close();

    }

    int aims() {

        ifstream f("Aim.txt");
        int aim;
        f >> aim;
        f.close();
        return aim;
        
    }

    void disciplines_base_creation() {
        sqlite3* db;
        char* err_message = nullptr;
         


        int rc = sqlite3_open("C:\\Users\\User\\source\\repos\\Productivity_bot\\disciplines.db", &db);

        if (rc != SQLITE_OK) {

            cerr << "Невозможно открыть базу дисциплин: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return;

        }

        const char* create_table_sql = "CREATE TABLE IF NOT EXISTS disciplines (discipline TEXT)";

        rc = sqlite3_exec(db, create_table_sql, nullptr, 0, &err_message);

        if (rc != SQLITE_OK) {
            cerr << "SQL error: " << err_message << endl;
            sqlite3_free(err_message);

        }

        else {

            cout << "База дисциплин успешно создана" << endl;

        }

        sqlite3_close(db);


    }

    static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
        return 0;
    }




    void disciplines_base_filling(int aim, int count_of_disciplines) {

        sqlite3* db;
        int rc = sqlite3_open("C:\\Users\\User\\source\\repos\\Productivity_bot\\disciplines.db", &db);

        if (rc != SQLITE_OK) {
            cerr << "Ошибка открытия базы данных" << sqlite3_errmsg(db) << endl;
            return;
        }

        char* ErrMsg = nullptr;
        const char* check = "SELECT name FROM sqlite_master WHERE type='table' AND name='disciplines_table';";
        rc = sqlite3_exec(db, check, callback, 0, &ErrMsg);

        if (rc != SQLITE_OK || ErrMsg != nullptr) {
            cerr << "Список дисциплин не создан!";
            sqlite3_free(ErrMsg);
            sqlite3_close(db);

        }

        else {

            cout << "Созданный список дисциплин найден!" << endl;
            cout << "Заполните список дисциплин" << endl;


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

            string discipline;
            sqlite3_stmt* stmt;
            const char* disciplines_table_append = "INSERT INTO disciplines_table(discipline) VALUES(?)";
            rc = sqlite3_prepare_v2(db, disciplines_table_append, -1, &stmt, NULL);

            for (int i = 0; i < count_of_disciplines; ++i) {
                
                discipline = "Математический";

                
                
                

                
                rc = sqlite3_bind_text(stmt, 1, discipline.c_str(), -1, SQLITE_TRANSIENT);
                rc = sqlite3_step(stmt);
                rc = sqlite3_reset(stmt);


                if (rc != SQLITE_OK) {
                    cerr << "Ошибка добавления элементов  базу данных";
                    sqlite3_free(ErrMsg);


                }



            }
            
            cout << "Все дисциплины успешно добавлены";
            rc = sqlite3_finalize(stmt);


            sqlite3_close(db);


        }


    }

    static int callback2(void* data, int argc, char** argv, char** azColName) {
        vector<string>* lst_of_disciplines = reinterpret_cast<vector<string>*>(data);
        lst_of_disciplines->push_back(argv[1]);
        return 0;
    }

    vector<string> creation_array_of_disciplines() {

        sqlite3* db;
        vector<string> error;

        int rc = sqlite3_open("C:\\Users\\User\\source\\repos\\Productivity_bot\\disciplines.db", &db);

        if (rc != SQLITE_OK) {
            cerr << "Ошибка открытия базы данных" << sqlite3_errmsg(db) << endl;
            return error;
        }

        char* ErrMsg = nullptr;
        const char* check_table = "SELECT name FROM sqlite_master WHERE type='table' AND name='disciplines_table';";
        rc = sqlite3_exec(db, check_table, callback, 0, &ErrMsg);

        if (rc != SQLITE_OK || ErrMsg != nullptr) {
            cerr << "Список дисциплин не создан!";
            sqlite3_free(ErrMsg);
            sqlite3_close(db);
            return error;

        }

        else {
            vector<string> lst_of_discipines;
            rc = sqlite3_exec(db, "SELECT * FROM disciplines_table;", callback2, &lst_of_discipines, nullptr);

            if (rc != SQLITE_OK) {
                cout << "Произошла какая-то ошибка, возможно вы не заполнили список дисциплин";
                sqlite3_close(db);
                return error;
            }

            sqlite3_close(db);
            return lst_of_discipines;
        }


    }



    

    

};

    
int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Productivity_bot bot;
    cout << "Вы хотите: \n"
        << "1 - определить цель\n"
        << "2 - создать список дисциплин\n"
        << "3 - заполнить список дисциплин\n"
        << "4 - распределить задачи\n" << endl;

    int opt;
    int aim;
    int count_of_disciplines;
    cin >> opt;

    switch (opt) {

    case 1:

        bot.aims_def();
        break;

    case 2:

        aim = bot.aims();
        bot.disciplines_base_creation();
        break;

    case 3:

        aim = bot.aims();
        int count_of_disciplines;

        cout << "Введите количество учебных дисциплин" << endl;
        cin >> count_of_disciplines;

        bot.disciplines_base_filling(aim,count_of_disciplines);
        break;

    case 4:

        aim = bot.aims();
        
        vector<string> lst_of_disciplines = bot.creation_array_of_disciplines();

        for (auto c : lst_of_disciplines) {
            cout << c;

        }

        //string task_type;
        //cout << "По какой дисциплине задача?";
        //(cin >> task_type).get();

        //Questions qsts;
        //pair<vector<int>, vector<double>> params = qsts.questions(aim);

        //Perceptron perceptron;
        //perceptron.predict(params, lst_of_disciplines, task_type);

    }

}