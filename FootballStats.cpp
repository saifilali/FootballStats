#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <math.h>  

using namespace std;

//----------------------------Declarations-------------------------------------------------------------------

double calcMean(vector <double>& vec),calcStdDeviation(vector <double>& dev,double mean);
double calcMax(vector <double>& max),calcMin(vector <double>& min); 
void readFile(),parseIt(),calcPSM(),printTeamStats();
double rTest();
vector<string> TeamName, TeamData;
vector<double> asM,py,dpy,ry,dry,to,dto,pendif,rettd,psm;

//---------------------------Main function-------------------------------------------------------------------

int main(int argc, char *argv[]) {     

    readFile();        
    parseIt();
    calcPSM();         
    rTest();           
    printTeamStats();  

    return 0;
}

//-------------This function will read text file "teamStats.txt"---------------------------------------------

void readFile(){                        
    string singleLine = "";
    ifstream infile;
    infile.open("teamStats.txt");

   
    while (!infile.eof()){
        getline(infile, singleLine);
        size_t key = singleLine.find("|");                //make your delimter = " | "
        string name = singleLine.substr (0,key-1);        //split string delimiter is found and make it team Name
        string data = singleLine.substr (key+1);          //make rest string as team data.
        TeamName.push_back(name);                         //store all first into teamName vector.
        TeamData.push_back(data);                         //store all second into teamData vector.
    }

    infile.close();                                      //closing the file is necessary.
}

//-------------This function will parse individual read(stored) line into teamName and teamData.-------------

void parseIt(){
       for(int i = 0; i<TeamData.size();i++){
        istringstream iss(TeamData[i]);

        int index = 0;

        while(!iss.eof()){
           string parsedString;
           iss >> parsedString;                  //parse teamData string into pieces to get all statstical values
           double convertedToDouble = stod(parsedString);     //convert all parsed string into double.

            if(index == 0)
                asM.push_back(convertedToDouble);
            else if(index == 1)
                py.push_back(convertedToDouble);
            else if(index == 2)
                dpy.push_back(convertedToDouble);
            else if(index== 3)
                ry.push_back(convertedToDouble);
            else if(index== 4)
                dry.push_back(convertedToDouble);
            else if(index== 5)
                to.push_back(convertedToDouble);
            else if(index== 6)
                dto.push_back(convertedToDouble);
            else if(index== 7)
                pendif.push_back(convertedToDouble);
            else if(index== 8)
                rettd.push_back(convertedToDouble);
            else 
                cout << "Error in Storing Data !\n";

            index++;
        }
    }
}

//-------------This function will calculate PSM of all the teams based on given stats.-----------------------

void calcPSM(){
    for(int i = 0; i < TeamName.size(); i++){
        double ans = 3.17 * (rettd[i]) - 0.06 * (pendif[i]) + 61.67 * (py[i]) + 26.44 * (ry[i]) - 2.77 * (to[i]) - 67.5 * (dpy[i]) - 22.79 * (dry[i]) + 3.49 * (dto[i]);
        psm.push_back(ans);
    }
}

//--------------This function will calculate rTest of ASM vs PSM.--------------------------------------------

double rTest(){
    double accumulator = 0.0,covariance = 0.0;

    for(int i = 0;i<32;i++){
       accumulator += (asM[i] - calcMean(asM)) * (psm[i] - calcMean(asM));
    }
        covariance = accumulator/31.0;

    return (covariance / (calcStdDeviation(asM,calcMean(asM)) * calcStdDeviation(psm,calcMean(psm))));
}

//--------------This function will calculate Mean of ASM & PSM.-----------------------------------------------

double calcMean(vector <double>& vec) {
    double sum = 0.0;
    for(int i = 0; i<32;i++){
        sum += vec[i];
    }
    return (sum/32.0);
}

//--------------This function will calculate Standard Deviation of ASM & PSM.---------------------------------

double calcStdDeviation(vector <double>& dev, double mean ){
    double result = 0.0;
    for(int i = 0; i<32;i++){
        result += ((dev[i] - mean) * (dev[i] - mean));
    }

    return (sqrt(result / 32.0));
}

//--------------This function will calculate Maximum of ASM & PSM.--------------------------------------------

double calcMax(vector <double>& max){
    double result = 0.0;
    for(int i=0;i<32;i++)
    {
        if(max[i]>result)
        result=max[i];
    }

    return result;
}

//--------------This function will calculate Minimum of ASM & PSM.--------------------------------------------

double calcMin(vector <double>& min){
    double result = 0.0;
    for(int i=0;i<32;i++)
    {
        if(min[i]<result)
        result=min[i];
    }

    return result;
}

//--------------This function will print all the output data in my program.-----------------------------------

void printTeamStats(){
    cout << "\n|-----------------------------------------------------------------------------------------------------------------------|";
    cout << "\n|----------TEAM NAME----------------------------------ASM------------------------------------------PSM------------------|";
    cout << "\n|-----------------------------------------------------------------------------------------------------------------------|\n";

    for(int i = 0; i<TeamName.size();i++){
        if (i == 0)
            cout <<"\nNFC East:\n";
        else if (i == 4)
            cout <<"\nNFC West:\n";
        else if (i == 8)
            cout <<"\nNFC North:\n";
        else if (i == 12)
            cout <<"\nNFC South:\n";
        else if (i == 16)
            cout <<"\nAFC East:\n";
        else if (i == 20)
            cout <<"\nAFC West:\n";
        else if (i == 24)
            cout <<"\nAFC North:\n";
        else if (i == 28)
            cout <<"\nAFC South:\n";

    cout << setw(22) << TeamName[i] << "              " << fixed << setprecision(2) << setw(22) << asM[i] << "                      " << setw(24) << psm[i] << "\n";
    }
    cout << "\n|-----------------------------------------------------------------------------------------------------------------------|\n"; 
    cout << setw(22) << "\nSample Size : " << setw(44) << 32;
    cout << setw(22) << "\nR-Test (ASM vs PSM) : " << setw(36) << setprecision(4) << rTest();
    cout << setw(22) << "\n\nMean of ASM : " << setw(44) << setprecision(4) << calcMean(asM);
    cout << setw(22) << "\nStandard Deviation of ASM : " << setw(30) << setprecision(4) << calcStdDeviation(asM,calcMean(asM));
    cout << setw(22) << "\nMax of ASM : " << setw(45) << setprecision(4) << calcMax(asM);
    cout << setw(22) << "\nMin of ASM : " << setw(45)<< setprecision(4) << calcMin(asM);
    cout << setw(22) << "\n\nMean of PSM : " << setw(44) << setprecision(4) << calcMean(psm);
    cout << setw(22) << "\nStandard Deviation of PSM : " << setw(30) << setprecision(4) << calcStdDeviation(psm,calcMean(psm));
    cout << setw(22) << "\nMax of PSM : " << setw(45) << setprecision(4) << calcMax(psm);
    cout << setw(22) << "\nMin of PSM : " << setw(45) << setprecision(4) << calcMin(psm);
}

//-----------------------END OF PROGRAM--------------------------------------------------------------------------------