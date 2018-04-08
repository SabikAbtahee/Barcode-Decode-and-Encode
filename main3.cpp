#include<bits/stdc++.h>

#include "encode2.cpp"
#include "database.cpp"
#include "decode1.cpp"

using namespace std;

void run();

void run(){

    int option;
    string falseLine;
    cout << "\n1 for decode\n2 for encode\n3 for entering product\n0 for exit.\nEnter your option: ";
    //cin.clear();
    cin >> option;
    getline(cin,falseLine);
    if(cin.fail()){
           cout << "Error giving Input\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
           // run();
    }
    //getline(cin,falseLine);
    if(option==1)decode();
    else if(option==2)encode();
    else if (option==3)createDatabase();
    else if(option==0)return;
    run();



}

int main (){
        run();
        return 0;
}
