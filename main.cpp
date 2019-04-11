#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

string* getLastLine(ifstream& in)
{
    //string line;
    //string sky, ground, dif;
    string *h;
    static string weather[5];
    //while (in >>ws && getline(in, line)); // skip empty lines
    //while (in >>ws && getline(in, sky, ',') && getline(in, ground, ',') && getline(in, dif, ' '));
    while (in >>ws && getline(in, weather[0], ',') && getline(in, weather[1], ',') && getline(in, weather[2], ',') && getline(in, weather[3], ',') && getline(in, weather[4], '\n'));
    h = weather;
    //return line;
    //return sky;
    //return ground;
    //return dif;
    return h;
}

int main()
{
    ifstream file("putty.log");
    string *line;
    if (file)
    {
        line = getLastLine(file);
        //Sky: 0
        //Ground : 1
        //Dif : 2
        //Clear Line: 3
        //Cloudy Line: 4
        //cout << line;
    }
    else
        cout << "Unable to open file.\n";


    ofstream myfile;

    stringstream temp(line[0]); //this section converts strings to int
    int skyT;
    temp >> skyT;

    stringstream temp1(line[1]); //this section converts strings to int
    int ambT;
    temp1 >> ambT;

    stringstream temp2(line[2]); //this section converts strings to int
    int diff;
    temp2 >> diff;

    stringstream temp3(line[3]); //this section converts strings to int
    float clear_line;
     temp3 >> clear_line;

    stringstream temp4(line[4]); //this section converts strings to int
    float cloudy_line;
    temp4 >> cloudy_line;

    myfile.open("data.txt");
    myfile<<"2005-06-03 02:07:23 C  "; //old format filler
    myfile<<skyT<<"  "; //sky Temp
    myfile<<ambT<<"  "; //Ambient Temp
    myfile<<"00.0   0 0 00000 000000.00000 "; //more old format filler
    if(diff >= clear_line){
        myfile<<"1 "; //implying clear conditions
    }
    else if (diff < clear_line && diff >= cloudy_line){
        myfile<<"2 "; //implying cloudy conditions
    }
    else {
        myfile<<"3 "; //very cloudy
    }
    //myfile<<line[2]<<endl;


//Testing purpose below
/*
    myfile<<endl;
    myfile<<"Sky Temp: "<<skyT<<";"<<line[0]<<endl;
    myfile<<"Amb Temp: "<<ambT<<";"<<line[1]<<endl;
    myfile<<"Diff: "<<diff<<";"<<line[2]<<endl;
*/
    myfile.close();


    return 0;
}
