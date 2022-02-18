// M2 CLeaningAndCountingAproximation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include <sstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

int main() {
    //loading data form sources that should hava data
    vector<vector<string>> content;                                 //step size how many steps between mesuraments
    vector<string> row;
    vector<string> datafiles;
    string line, word;
    vector <double> NewRowData;

    fstream file("UserInput/StepSize.csv", ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";

    cout << row[0] << "\n";

    double NumberOfMesuraments = stod(row[0]);
    file.close();

    string path = "Data";
    for (const auto& entry : fs::directory_iterator(path)) {
        stringstream ss;
        string datafile;
        ss << entry.path();
        ss >> datafile;
        datafile.erase(0, 1);
        datafile.erase(datafile.size() - 1);
        datafiles.push_back(datafile);
    }

    for (int k = 0; k < datafiles.size(); k++) {
        cout << datafiles[k] << "\n";

    }

    for (int iterator = 0; iterator < datafiles.size(); iterator++) {
        cout << "am here1\n";
        vector<vector<string>> DataFromFile;                                 //step size how many steps between mesuraments
        vector<string> Datarow;
        string DataPoint, WordPoint;
        cout << datafiles[iterator] << "file form which is read\n";
        fstream file(datafiles[iterator], ios::in);
        if (file.is_open())
        {
            while (getline(file, line))
            {

                stringstream str(line);

                while (getline(str, WordPoint, ','))
                    Datarow.push_back(WordPoint);
                DataFromFile.push_back(Datarow);
            }
        }
        else
            cout << "Could not open the file\n";

        vector <double> NewRowData;


        for_each(Datarow.begin(), Datarow.end(), [&NewRowData](const string& ele) { NewRowData.push_back(stod(ele)); });

        




        double NumberOfSteps = 0;
        for (int iter = 100; iter < (NewRowData.size() / 4) + 1; iter++) {
            //Datarow[(Datarow.size() / 2) + iter] << "\n";
            double MovingError = 0;
            vector <double> ErrorValues;

            for (int range = 0; range < 100; range++) {
                MovingError = MovingError + NewRowData[(NewRowData.size() / 2) + iter - 1 - range];
            }
            MovingError = MovingError / 100;

            double limit = 0.1;

            if (iter > (NewRowData.size() / 8) && abs(MovingError - NewRowData[(NewRowData.size() / 2) + iter]) < limit) {
                 //cout << "not doing anything\n";
                iter = 3000;
            }
            else {
                if (abs(MovingError - NewRowData[(NewRowData.size() / 2) + iter]) < limit) {
                    cout << iter << "linear\n";
                    //Gause2 << abs(MovingError - NewRowData[(NewRowData.size() / 2) + iter]) << "\n";
                }
                else if (abs(MovingError - NewRowData[(NewRowData.size() / 2) + iter]) > limit) {
                    cout << iter << "going down or down\n";
                    //Gause2 << abs(MovingError - NewRowData[(NewRowData.size() / 2) + iter]) << "\n";
                    NumberOfSteps++;
                }
                else {
                        // cout << iter << "am here1\n";
                }
            }
        }
            //saveing the second mesurament in to the file
            cout << "The diametr on the further blade is: " << (NumberOfSteps / 800) * 1.6;
 
    }


        /*for (int iter = 100; iter < (doubleingMean.size() / 4) + 1; iter++) {
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
    }*/
    /*vector<vector<string>> content2;                                 //step size how many steps between mesuraments
    vector<string> row2;
    string line2, word2;

    fstream file("UserInput/StepSize.csv", ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";

    cout << row[0] << "\n";

    double NumberOfMesuraments = stod(row[0]);
}

    /*vector <double> AngleOfTheBeam;
    vector <double> DerivationDescription;
    for (int i = 0; i < diameter.size(); i++) {
        double AngleBetweenPoints = 0;
        AngleBetweenPoints = atan((diameter[0+i] / 2 - diameter[1+i] / 2) / StepSize);
        AngleBetweenPoints = AngleBetweenPoints * 180 / 3.14159256;
        
        DerivationDescription.push_back(AngleBetweenPoints);

        if (AngleBetweenPoints < 0) {
            cout << "angle between two points is negative so we are coming form the ¨wider part of beam\n";
        }
        else if (AngleBetweenPoints > 0) {
            cout << "we are going from the other side\n";
        }
        //DerivationOfTheCurve = atan( (diameter[0]/2 - diameter[1]/2) / StepSize)
        //AngleOfTheBeam.push_back(DerivationOfTheCurve)
    }

    for (int iter = 1; iter < DerivationDescription.size(); iter++) {
        if (DerivationDescription[0] < DerivationDescription[iter] || DerivationDescription[0] == DerivationDescription[iter]) {
            cout << "we are at the breaking point/the middle\n";
        }
    }*/

}

/*#include <iostream>
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
//string inputMesuraments = 
string output1 = "source/Gause.txt";
string output2 = "source/AwaragedValues.txt";

int main() {
    //
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

        doubleingMean.push_back(Sum / 100);
    }

    //loading the files in which we will load the result data for ploting
    ofstream myfile;
    ofstream Gause;
    Gause.open(output1);
    myfile.open(output2);

    double NumberOfSteps = 0;

    //the mesurament and detection of the brakes of power and prevention from miss mesurament
    for (int iter = 100; iter < (doubleingMean.size() / 4) + 1; iter++) {
        myfile << doubleingMean[iter] << "\n";
        double MovingError = 0;

        for (int range = 0; range < 100; range++) {
            MovingError = MovingError + doubleingMean[iter - 1 - range];
        }
        MovingError = MovingError / 100;

        double limit = 0.1;

        if (iter > (doubleingMean.size() / 8) && abs(MovingError - doubleingMean[iter]) < limit) {
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
    MyFile << /*"The diametr on the closer blade () is: " << (NumberOfSteps / 800) * 1.6 << "\n";

    string output1 = "source/Gause2.txt";
    string output2 = "source/AwaragedValues2.txt";

    ofstream myfile2;
    ofstream Gause2;
    Gause2.open(output1);
    myfile2.open(output2);

    //counting the diameter at the second blade
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream file("UserInput / NumberOfMesuraments.csv", ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";

    cout << row[0] << "\n";

    double NumberOfMesuraments = stod(row[0]);
    NumberOfSteps = 0;
    for (int iterator = 0; iterator < NumberOfMesuraments; iterator++) {
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
    

}*/