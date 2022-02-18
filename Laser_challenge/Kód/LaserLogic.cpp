#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
//#include <ctime>
using namespace std;

//string input1 = "dataATMaTomRadost.txt";//"data1firstblade.txt";
//string input2 = "data2secondblade.txt";
string input3 = "Data.txt";
string output1 = "Gause.txt";
string output2 = "AwaragedValues.txt";

int main() {
    ifstream InFile;
    InFile.open(input3);

    if (!InFile) {
        exit(1); // terminate with error
    }

    vector <float> Values;
    string Mytext;
    while (getline(InFile, Mytext)) {
        Values.push_back(stof(Mytext));
    }

    vector<double> FloatingMean;
    for (int i = 99; i < Values.size(); i++) {
        float Sum = 0;

        for (int sub = 0; sub < 100; sub++) {
            Sum = Sum + Values[i - sub];
        }

        FloatingMean.push_back(Sum/100);
    }

    cout << "am here1";

    ofstream myfile;
    ofstream Gause;
    Gause.open(output1);
    myfile.open(output2);

    float NumberOfSteps = 0;

    for (int iter = 100; iter < (FloatingMean.size()/4)  + 1; iter++) {
        myfile << FloatingMean[iter] << "\n";
        float MovingError = 0;
        vector <float> ErrorValues;

        for (int range = 0; range < 100; range++) {
            MovingError = MovingError + FloatingMean[iter - 1 - range];
        }
        MovingError = MovingError / 100;

        float limit = 0.1;

        if (iter > (FloatingMean.size()/8) && abs(MovingError - FloatingMean[iter]) < limit) {
            cout << "not doing anything\n";
            iter = 3000;
        }
        else {
            if (abs(MovingError - FloatingMean[iter]) < limit) {
                cout << iter << "linear\n";
                Gause << abs(MovingError - FloatingMean[iter]) << "\n";
            }
            else if (abs(MovingError - FloatingMean[iter]) > limit) {
                cout << iter << "going down or down\n";
                Gause << abs(MovingError - FloatingMean[iter]) << "\n";
                NumberOfSteps++;
            }
            else {
                cout << iter << "am here1\n";
            }
        }
    }

    ofstream MyFile("Result.txt");

    // Write to the file
    //MyFile << "Files can be tricky, but it is fun enough!";
    cout << "The diametr on the closer blade is: " << (NumberOfSteps / 800) * 1.6;
    MyFile << (NumberOfSteps / 800) * 1.6 << "\n";

    string output1 = "Gause2.txt";
    string output2 = "AwaragedValues2.txt";

    ofstream myfile2;
    ofstream Gause2;
    Gause2.open(output1);
    myfile2.open(output2);


    NumberOfSteps = 0;

    for (int iter = 100; iter < (FloatingMean.size() / 4) + 1; iter++) {
        myfile2 << FloatingMean[(FloatingMean.size() / 2) + iter] << "\n";
        float MovingError = 0;
        vector <float> ErrorValues;

        for (int range = 0; range < 100; range++) {
            MovingError = MovingError + FloatingMean[(FloatingMean.size() / 2) + iter - 1 - range];
        }
        MovingError = MovingError / 100;

        float limit = 0.1;

        if (iter > (FloatingMean.size() / 8) && abs(MovingError - FloatingMean[(FloatingMean.size() / 2) + iter]) < limit) {
            //cout << "not doing anything\n";
            iter = 3000;
        }
        else {
            if (abs(MovingError - FloatingMean[(FloatingMean.size() / 2) + iter]) < limit) {
               // cout << iter << "linear\n";
                Gause2 << abs(MovingError - FloatingMean[(FloatingMean.size() / 2) + iter]) << "\n";
            }
            else if (abs(MovingError - FloatingMean[(FloatingMean.size() / 2) + iter]) > limit) {
               // cout << iter << "going down or down\n";
                Gause2 << abs(MovingError - FloatingMean[(FloatingMean.size() / 2) + iter]) << "\n";
                NumberOfSteps++;
            }
            else {
               // cout << iter << "am here1\n";
            }
        }
    }

    Gause2.close();
    myfile2.close();
    InFile.close();


   
    cout << "The diametr on the further blade is: " << (NumberOfSteps / 800) * 1.6;
    MyFile << (NumberOfSteps / 800) * 1.6 << "\n";
    MyFile.close();

   
}