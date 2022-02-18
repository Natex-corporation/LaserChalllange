#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
//#include <ctime>
using namespace std;

int main() {
    ifstream InFile;
    InFile.open("data1firstblade.txt");
    if (!InFile) {
        exit(1); // terminate with error
    }
    vector <float> Values;
    string Mytext;
    while (getline(InFile, Mytext)) {
        Values.push_back(stof(Mytext));
    }
    vector<double> FloatingMean;
    for (int i = 4; i < Values.size(); i++) {
        float Sum = 0;
        for (int sub = 0; sub < 5; sub++) {
            //cout << Values[i - sub] << "brrr\n";
            Sum = Sum + Values[i - sub];
            //cout << Sum << "sumasum\n";
        }
        FloatingMean.push_back(Sum/5);
    }
    cout << FloatingMean.size() << "size of mean values\n";
    ofstream myfile;
    ofstream Gause;
    Gause.open("Gause.txt");
    myfile.open("AwaragedValues.txt");

    
    float ErrorMean = 0;//
    float Error = 0;

    for (int iter = 10; iter < (FloatingMean.size() / 4) + 1; iter++) {
        myfile << FloatingMean[iter] << "\n";
        //cout << FloatingMean[iter] << "\n";
        float MovingError = 0;
        vector <float> ErrorValues;
        for (int range = 0; range < 10; range++) {
            ErrorValues.push_back(FloatingMean[iter - range]); 
        }

        sort(ErrorValues.begin(), ErrorValues.end());
        //cout << ErrorMean << " Mean of previous 10values\n";
        Error = abs(ErrorValues.front() - ErrorValues.back());
        Gause << Error << "\n";
        //cout << Error << " Absolute difference of value\n";
        float limit = 0.7;
        if (FloatingMean[iter - 1] == FloatingMean[iter] +  && FloatingMean[iter - 1] == FloatingMean[iter] - Error) {
            cout << "linear\n";
        }
        if (FloatingMean[iter - 1] > FloatingMean[iter] + Error && FloatingMean[iter - 1] > FloatingMean[iter] - Error) {
            cout << "going down\n";
        }
        if (FloatingMean[iter - 1] < FloatingMean[iter] + Error && FloatingMean[iter - 1] < FloatingMean[iter] - Error) {
            cout << "going up\n";
        }
        else {
            cout << "am here1\n";
        }
    }

    /*sort(FloatingMean.begin(), FloatingMean.end() - (FloatingMean.size() / 4));
    for (int itr = 0; itr < FloatingMean.size(); itr++) {
        if (FloatingMean[itr] > 18) {
            cout << FloatingMean[itr] << "\n";
        }
        //cout << FloatingMean[itr] << "\n";
    }*/

    Gause.close();
    myfile.close();
    InFile.close();
}