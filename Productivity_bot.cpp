#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

int aims() {
    setlocale(LC_ALL, "Russian");
    cout << "Какие цели вы преследуете?" << endl;
    cout << "Введите 1, если вы акцентируете всё своё внимание только на работе/интересующих вас вещах. Из вуза нужно просто не вылететь\n"
        << "2, если вы акцентируете своё внимание на вузовской программе на всех предметах, при этом вам важно развитие навыков/способностей. Оценки и рейтинг вещи второстепенные. Кроме того, хочу заниматься работой/тем, что мне нравится\n"
        << "3, если вы акцентируете своё внимание только на тех предметах вузовской программы, которые мне интересны. Остальные лишь бы закрыть\n"
        << "4, если вы акцентируете своё внимание на оценки и рейтинг, при этом знания и навыки вам не особо важны\n"
        << "5, если вам важен и рейтинг, и навыки, и при этом вы хотите заниматься тем, чем нравится/работой\n" << endl;
    int option;
    cin >> option;

    return option;

}

void creation_array_of_disciplines(int count_of_disciplines) {


    string* AoD; //array of input discipines, result
    string* AoD2; //extra array
    string s;
    int count=0;
    AoD = nullptr;

    while (count < count_of_disciplines) {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

        cout << "Введите " << count + 1 << " предмет" << endl;
        getline(cin, s);

        if (s != " " and s != "") {
            count++;
            AoD2 = new string[count]; //release memory for the new array

            //copying the data from the old array
            for (int i = 0; i < count - 1; i++) {
                AoD2[i] = AoD[i];

            

            }
            AoD2[count - 1] = s;
            
            //release memory allocated for old (previous array)
            if (AoD != nullptr) { 
                delete[] AoD;

            }
            //redirect pointer from the previous array AoD to the array AoD2
            AoD = AoD2;

        }
        else {
            break;
        }


    }
    for (int i = 0; i < count_of_disciplines; i++) {
        cout << AoD[i] << endl;

    }

}




int main() {
    int count_of_disciplines = 3;
    creation_array_of_disciplines(3);
    return 0;
}