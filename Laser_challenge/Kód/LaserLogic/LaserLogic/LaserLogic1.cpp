#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
//#include <ctime>
using namespace std;

//creates the path string where we will store the data
string input3 = "source/Data.txt";
string output1 = "source/Gause.txt";
string output2 = "source/AwaragedValues.txt";

int main() {
    //loading the file with mesured valus for further processing
    ifstream InFile;
    InFile.open(input3);

    if (!InFile) {
        exit(1); // terminate with error
    }
    
    //loading the values to a vector for easier operations
    vector <double> Values;
    string Mytext;
    while (getline(InFile, Mytext)) {
        Values.push_back(stof(Mytext));
    }

    //creating the mean for all the mesured values from the previous value (reduces the noise)
    vector<double> doubleingMean;
    for (int i = 99; i < Values.size(); i++) {
        double Sum = 0;

        for (int sub = 0; sub < 100; sub++) {
            Sum = Sum + Values[i - sub];
        }

        doubleingMean.push_back(Sum/100);
    }

    //loading the files in which we will load the result data for ploting
    ofstream myfile;
    ofstream Gause;
    Gause.open(output1);
    myfile.open(output2);

    double NumberOfSteps = 0;

    //the mesurament and detection of the brakes of power and prevention from miss mesurament
    for (int iter = 100; iter < (doubleingMean.size()/4)  + 1; iter++) {
        myfile << doubleingMean[iter] << "\n";
        double MovingError = 0;

        for (int range = 0; range < 100; range++) {
            MovingError = MovingError + doubleingMean[iter - 1 - range];
        }
        MovingError = MovingError / 100;

        double limit = 0.1;

        if (iter > (doubleingMean.size()/8) && abs(MovingError - doubleingMean[iter]) < limit) {
            cout << "not doing anything\n";
            iter = 3000;
        }
        else {
            if (abs(MovingError - doubleingMean[iter]) < limit) {
                cout << iter << "linear\n";
                Gause << abs(MovingError - doubleingMean[iter]) << "\n";
            }
            else if (abs(MovingError - doubleingMean[iter]) > limit) {
                cout << iter << "going down or down\n";
                Gause << abs(MovingError - doubleingMean[iter]) << "\n";
                NumberOfSteps++;
            }
        }
    }
    //creating the file in which we will be saveing the data
    ofstream MyFile("Result.txt");

    //saveing the result of mesurament in cm in to the file
    cout << "The diametr on the closer blade () is: " << (NumberOfSteps / 800) * 1.6;
    MyFile << "The diametr on the closer blade () is: " <<(NumberOfSteps / 800) * 1.6 << "\n";

    string output1 = "source/Gause2.txt";
    string output2 = "source/AwaragedValues2.txt";

    ofstream myfile2;
    ofstream Gause2;
    Gause2.open(output1);
    myfile2.open(output2);

    //counting the diameter at the second blade
    NumberOfSteps = 0;

    for (int iter = 100; iter < (doubleingMean.size() / 4) + 1; iter++) {
        myfile2 << doubleingMean[(doubleingMean.size() / 2) + iter] << "\n";
        double MovingError = 0;
        vector <double> ErrorValues;

        for (int range = 0; range < 100; range++) {
            MovingError = MovingError + doubleingMean[(doubleingMean.size() / 2) + iter - 1 - range];
        }
        MovingError = MovingError / 100;

        double limit = 0.1;

        if (iter > (doubleingMean.size() / 8) && abs(MovingError - doubleingMean[(doubleingMean.size() / 2) + iter]) < limit) {
            //cout << "not doing anything\n";
            iter = 3000;
        }
        else {
            if (abs(MovingError - doubleingMean[(doubleingMean.size() / 2) + iter]) < limit) {
               // cout << iter << "linear\n";
                Gause2 << abs(MovingError - doubleingMean[(doubleingMean.size() / 2) + iter]) << "\n";
            }
            else if (abs(MovingError - doubleingMean[(doubleingMean.size() / 2) + iter]) > limit) {
               // cout << iter << "going down or down\n";
                Gause2 << abs(MovingError - doubleingMean[(doubleingMean.size() / 2) + iter]) << "\n";
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
    //saveing the second mesurament in to the file
    cout << "The diametr on the further blade is: " << (NumberOfSteps / 800) * 1.6;
    MyFile << "The diametr on the further blade is: " << (NumberOfSteps / 800) * 1.6 << "\n";
    MyFile.close();
   
}