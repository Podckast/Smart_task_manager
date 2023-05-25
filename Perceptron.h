#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Perceptron
{
public:

    int predict(pair<vector<int>, vector<double>> params, vector<string> lst_of_disciplines, string task) {



        int bias;
        int count_of_disciplines = lst_of_disciplines.size();
        double perceptron_value = 0;

        for (int i = 0; i < count_of_disciplines; i++) {

            if (task == lst_of_disciplines[i]) {
                bias = i;
                perceptron_value += bias;

                for (int j = 0; j < params.second.size(); j++) {
                    perceptron_value += params.first[j] * params.second[j];



                }

                return perceptron_value;
            }


        }
        return 0;
    }





};

