#include<bits/stdc++.h>
#include<fstream>

using namespace std;

int cToiE(char x);
bool checkSumE(string answer);
bool checkEAN(string answer);
void getHeaderForEncoding();
struct rowPad getPaddingInfo();
string getEncryption();
string getBinary(int value);
string getLinearEncryption();
void getImage(unsigned char *pixels,int rowSize,int paddingPerLine);
void getLinearImage(unsigned char *pixels,int rowSize,int paddingPerLine);
void makeHeaderUPCEAN(bool UPC, bool EAN);
void encode();
void encode(string barcode);
string checkFirstDigit();

string fileNameToWrite;
string inputForEncoding;
unsigned char header[54];
unsigned char black;                   //i have the value black that i can write in the file
unsigned char white;
int pixelSize;

struct rowPad{      //rowsize and padding structure to return value
    int rowsize;
    int paddingPerLine;
};

struct headerForEncoding{           //header structure

    int sizeOfFileE;
    int widthIntE;
    int heightIntE;
    int bitcountE;
    int offsetIntE;

};

int cToiE(char x){           //returns the char value to int
    return (int)(x-48);
}

bool checkSumE(string answer){                               //checks if UPC or not

    int x,y,a,b;

    x =cToiE(answer[0]) + cToiE(answer[2]) + cToiE(answer[4]) + cToiE(answer[6]) + cToiE(answer[8]) + cToiE(answer[10]);
    x = x*3;
    a =cToiE(answer[1]) + cToiE(answer[3]) +cToiE(answer[5]) + cToiE(answer[7]) + cToiE(answer[9]);
    y = x + a;
    y = y % 10;
    if(y==0)y=10;
    b = 10 - y;
    if((cToiE(answer[11]))==b){
        return true;
    }
    else{
        return false;
    }
}

bool checkEAN(string answer){               //checks if Ean or not
    int x,y,a,b;

    x =cToiE(answer[0]) + cToiE(answer[2]) + cToiE(answer[4]) + cToiE(answer[6]) + cToiE(answer[8]) + cToiE(answer[10]);

    a =cToiE(answer[1]) + cToiE(answer[3]) +cToiE(answer[5]) + cToiE(answer[7]) + cToiE(answer[9])+ cToiE(answer[11]);
    a=a*3;
    y = x + a;
    y = y % 10;
    if(y==0)y=10;
    b = 10 - y;
    if((cToiE(answer[12]))==b){
        return true;
    }
    else{
        return false;
    }
}

headerForEncoding encodedInfo;
void getHeaderForEncoding(){        //gets some of the important header information
        encodedInfo.sizeOfFileE = (int)header[2] + ( ((int)header[3]) * 256) + (((int)header[4]) * 65536) + (((int)header[5]) * 16777216);  //got size

        encodedInfo.widthIntE = (((int)header[18]) + ((int)header[19] * 256) +((int)header[20] *65536) + ((int)header[21] *16777216)); //got width

        encodedInfo.heightIntE=(((int)header[22]) + ((int)header[23] * 256) +((int)header[24] *65536) + ((int)header[25] *16777216));

        encodedInfo.bitcountE=(int)header[28];

        encodedInfo.offsetIntE=(((int)header[10]) + ((int)header[11] * 256) +((int)header[12] *65536) + ((int)header[13] *16777216));

}

struct rowPad getPaddingInfo(){     //gets the rowsize and padding

        rowPad r;
        int a,b,rowsize;
        a = encodedInfo.sizeOfFileE - encodedInfo.offsetIntE - (encodedInfo.widthIntE * encodedInfo.heightIntE * (encodedInfo.bitcountE/8));
        b=a/encodedInfo.heightIntE;
        rowsize = (encodedInfo.widthIntE * (encodedInfo.bitcountE/8))+b;

       /* cout << encodedInfo.sizeOfFileE << "\n";
        cout << a << "\n";
        cout << b << "\n";
        cout << rowsize << "\n";                                                //needed calculation
        cout << encodedInfo.heightIntE<<"\n";
        cout << rowsize*encodedInfo.heightIntE << "\n";
        cout << (rowsize*encodedInfo.heightIntE)+encodedInfo.offsetIntE << "\n";
        */

        r.rowsize=rowsize-b;
        r.paddingPerLine=b;

        return r;
}

string checkFirstDigit(){
    string parity="";
    if(inputForEncoding[0]=='0'){
            parity = "OOOOOO";
    }
    else if(inputForEncoding[0]=='1'){
            parity = "OOEOEE";
    }
    else if(inputForEncoding[0]=='2'){
            parity = "OOEEOE";
    }
    else if(inputForEncoding[0]=='3'){
            parity = "OOEEEO";
    }
    else if(inputForEncoding[0]=='4'){
            parity = "OEOOEE";
    }
    else if(inputForEncoding[0]=='5'){
            parity = "OEEOOE";
    }
    else if(inputForEncoding[0]=='6'){
            parity = "OEEEOO";
    }
    else if(inputForEncoding[0]=='7'){
            parity = "OEOEOE";
    }
    else if(inputForEncoding[0]=='8'){
            parity = "OEOEEO";
    }
    else if(inputForEncoding[0]=='9'){
            parity = "OEEOEO";
    }
    return parity;
}

string getEncryption(){         //encrypting value to upc or ean barcode
    string encrytedCode;
    int lengthOfBarcode=inputForEncoding.length();

    encrytedCode = "101";
    if(lengthOfBarcode==12){
            for(int i=0;i<6;i++){
                if(inputForEncoding[i]=='0'){
                    encrytedCode = encrytedCode + "0001101";
                }
                else if (inputForEncoding[i]=='1'){
                    encrytedCode = encrytedCode + "0011001";
                }
                else if (inputForEncoding[i]=='2'){
                    encrytedCode = encrytedCode + "0010011";
                }
                else if (inputForEncoding[i]=='3'){
                    encrytedCode = encrytedCode + "0111101";
                }
                else if (inputForEncoding[i]=='4'){
                    encrytedCode = encrytedCode + "0100011";
                }
                else if (inputForEncoding[i]=='5'){
                    encrytedCode = encrytedCode + "0110001";
                }
                else if (inputForEncoding[i]=='6'){
                    encrytedCode = encrytedCode + "0101111";
                }
                else if (inputForEncoding[i]=='7'){
                    encrytedCode = encrytedCode + "0111011";
                }
                else if (inputForEncoding[i]=='8'){
                    encrytedCode = encrytedCode + "0110111";
                }
                else if (inputForEncoding[i]=='9'){
                    encrytedCode = encrytedCode + "0001011";
                }
            }


            encrytedCode = encrytedCode +"01010";


            for(int i=6;i<12;i++){
                    if(inputForEncoding[i]=='0'){
                    encrytedCode = encrytedCode + "1110010";
                }
                else if (inputForEncoding[i]=='1'){
                    encrytedCode = encrytedCode + "1100110";
                }
                else if (inputForEncoding[i]=='2'){
                    encrytedCode = encrytedCode + "1101100";
                }
                else if (inputForEncoding[i]=='3'){
                    encrytedCode = encrytedCode + "1000010";
                }
                else if (inputForEncoding[i]=='4'){
                    encrytedCode = encrytedCode + "1011100";
                }
                else if (inputForEncoding[i]=='5'){
                    encrytedCode = encrytedCode + "1001110";
                }
                else if (inputForEncoding[i]=='6'){
                    encrytedCode = encrytedCode + "1010000";
                }
                else if (inputForEncoding[i]=='7'){
                    encrytedCode = encrytedCode + "1000100";
                }
                else if (inputForEncoding[i]=='8'){
                    encrytedCode = encrytedCode + "1001000";
                }
                else if (inputForEncoding[i]=='9'){
                    encrytedCode = encrytedCode + "1110100";
                }
            }
            encrytedCode = encrytedCode + "101";


    }

    else if (lengthOfBarcode==13){

            string parity = checkFirstDigit();
            for(int i=1;i<7;i++){
                if(inputForEncoding[i]=='0' && parity[i-1]=='O'){
                    encrytedCode = encrytedCode + "0001101";
                }
                else if (inputForEncoding[i]=='1'&& parity[i-1]=='O'){
                    encrytedCode = encrytedCode + "0011001";
                }
                else if (inputForEncoding[i]=='2'&& parity[i-1]=='O'){
                    encrytedCode = encrytedCode + "0010011";
                }
                else if (inputForEncoding[i]=='3'&& parity[i-1]=='O'){
                    encrytedCode = encrytedCode + "0111101";
                }
                else if (inputForEncoding[i]=='4'&& parity[i-1]=='O'){
                    encrytedCode = encrytedCode + "0100011";
                }
                else if (inputForEncoding[i]=='5'&& parity[i-1]=='O'){
                    encrytedCode = encrytedCode + "0110001";
                }
                else if (inputForEncoding[i]=='6'&& parity[i-1]=='O'){
                    encrytedCode = encrytedCode + "0101111";
                }
                else if (inputForEncoding[i]=='7'&& parity[i-1]=='O'){
                    encrytedCode = encrytedCode + "0111011";
                }
                else if (inputForEncoding[i]=='8'&& parity[i-1]=='O'){
                    encrytedCode = encrytedCode + "0110111";
                }
                else if (inputForEncoding[i]=='9'&& parity[i-1]=='O'){
                    encrytedCode = encrytedCode + "0001011";
                }

                else if(inputForEncoding[i]=='0' && parity[i-1]=='E'){
                    encrytedCode = encrytedCode + "0100111";
                }
                else if (inputForEncoding[i]=='1'&& parity[i-1]=='E'){
                    encrytedCode = encrytedCode + "0110011";
                }
                else if (inputForEncoding[i]=='2'&& parity[i-1]=='E'){
                    encrytedCode = encrytedCode + "0011011";
                }
                else if (inputForEncoding[i]=='3'&& parity[i-1]=='E'){
                    encrytedCode = encrytedCode + "0100001";
                }
                else if (inputForEncoding[i]=='4'&& parity[i-1]=='E'){
                    encrytedCode = encrytedCode + "0011101";
                }
                else if (inputForEncoding[i]=='5'&& parity[i-1]=='E'){
                    encrytedCode = encrytedCode + "0111001";
                }
                else if (inputForEncoding[i]=='6'&& parity[i-1]=='E'){
                    encrytedCode = encrytedCode + "0000101";
                }
                else if (inputForEncoding[i]=='7'&& parity[i-1]=='E'){
                    encrytedCode = encrytedCode + "0010001";
                }
                else if (inputForEncoding[i]=='8'&& parity[i-1]=='E'){
                    encrytedCode = encrytedCode + "0001001";
                }
                else if (inputForEncoding[i]=='9'&& parity[i-1]=='E'){
                    encrytedCode = encrytedCode + "0010111";
                }
            }
            encrytedCode = encrytedCode +"01010";

            for(int i=7;i<13;i++){
                    if(inputForEncoding[i]=='0'){
                    encrytedCode = encrytedCode + "1110010";
                }
                else if (inputForEncoding[i]=='1'){
                    encrytedCode = encrytedCode + "1100110";
                }
                else if (inputForEncoding[i]=='2'){
                    encrytedCode = encrytedCode + "1101100";
                }
                else if (inputForEncoding[i]=='3'){
                    encrytedCode = encrytedCode + "1000010";
                }
                else if (inputForEncoding[i]=='4'){
                    encrytedCode = encrytedCode + "1011100";
                }
                else if (inputForEncoding[i]=='5'){
                    encrytedCode = encrytedCode + "1001110";
                }
                else if (inputForEncoding[i]=='6'){
                    encrytedCode = encrytedCode + "1010000";
                }
                else if (inputForEncoding[i]=='7'){
                    encrytedCode = encrytedCode + "1000100";
                }
                else if (inputForEncoding[i]=='8'){
                    encrytedCode = encrytedCode + "1001000";
                }
                else if (inputForEncoding[i]=='9'){
                    encrytedCode = encrytedCode + "1110100";
                }
            }
            encrytedCode = encrytedCode + "101";
    }


    return encrytedCode;

}

string getBinary(int value){        //transforming value to binary for encryption purpose
        string convertedCode="";
        int a,b;

        for(int i=1;i<=4;i++){
            a=value%2;
            value=value/2;
            b=value%2;
            value=value/2;

            if(a==0 && b==0)convertedCode+="0";
            else if(a==0 && b==1)convertedCode+="1";
            else if(a==1 && b==0)convertedCode+="2";
            else if(a==1 && b==1)convertedCode+="3";
        }

        return convertedCode;
}

string getLinearEncryption(){           //encrypts the input to linear barcode
    string encryptedCode="";
    int lengthOfBarcode=inputForEncoding.length();

    for(int i=0;i<lengthOfBarcode;i++){
        encryptedCode =encryptedCode + getBinary((int)inputForEncoding[i]);
    }
    return encryptedCode;
}

void getImage(unsigned char *pixels,int rowSize,int paddingPerLine){        //if upc or ean then it makes the pixels
            string encrytedCode;
            encrytedCode = getEncryption();

           /* cout << pixelSize<<"\n";
            cout << encodedInfo.bitcountE << "\n";
            cout << encodedInfo.heightIntE * encodedInfo.widthIntE * (encodedInfo.bitcountE/8)<<"\n";
            cout << encodedInfo.heightIntE << "\n";
            cout << encodedInfo.widthIntE << "\n";
            cout << (encodedInfo.bitcountE/8) << "\n";*/
            //cout << rowSize<< "    " << paddingPerLine;

            int lineCount=3;

            while(true){
                if((95*lineCount)<rowSize)lineCount+=3;
                else{
                    lineCount-=3;
                    break;
                }
            }
            int quarters = (rowSize- (95*lineCount))/2;


            int mainCount=0;

            while(mainCount<1){                     //the real equations to make the image

                for(int j=1;j<=10;j++){
                    for(int k=1;k<=rowSize+paddingPerLine;k++){                              //make white to the lower screen
                            pixels[mainCount]=white;
                            mainCount++;
                    }
                }


                 for(int i=1;i<=10;i++){                                          //main drawing area
                    for(int x=1;x<=quarters;x++){                                                       //first quarter white
                            pixels[mainCount]=white;
                            mainCount++;
                    }

                    for(int i=0;i<95;i++){
                        if(encrytedCode[i]=='0'   &&  ((i>=0 && i<=9)|| (i>=46 && i<=48)||(i>=85 && i<=94))){
                                for(int x=0;x<lineCount;x++){
                                        pixels[mainCount]=white;
                                        mainCount++;
                                }
                        }
                        else if (encrytedCode[i]=='1'&&  ((i>=0 && i<=9)|| (i>=46 && i<=48)||(i>=85 && i<=94))){
                                 for(int x=0;x<lineCount;x++){
                                        pixels[mainCount]=black;
                                        mainCount++;
                                }
                        }
                        else{
                                 for(int x=0;x<lineCount;x++){
                                        pixels[mainCount]=white;
                                        mainCount++;
                                }
                        }
                    }


                    for(int x=quarters+(95*lineCount);x<rowSize;x++){            //last quarter white
                            pixels[mainCount]=white;
                            mainCount++;
                    }

                    for(int x=1;x<=paddingPerLine;x++){                 //getting rid of paddings
                            pixels[mainCount]=white;
                            mainCount++;
                    }
                }





                for(int i=1;i<=encodedInfo.heightIntE-40;i++){                                          //main drawing area
                    for(int x=1;x<=quarters;x++){                                                       //first quarter white
                            pixels[mainCount]=white;
                            mainCount++;
                    }

                    for(int i=0;i<95;i++){
                        if(encrytedCode[i]=='0'){
                                for(int x=0;x<lineCount;x++){
                                        pixels[mainCount]=white;
                                        mainCount++;
                                }
                        }
                        else if (encrytedCode[i]=='1'){
                                 for(int x=0;x<lineCount;x++){
                                        pixels[mainCount]=black;
                                        mainCount++;
                                }
                        }
                    }


                    for(int x=quarters+(95*lineCount);x<rowSize;x++){            //last quarter white
                            pixels[mainCount]=white;
                            mainCount++;
                    }

                    for(int x=1;x<=paddingPerLine;x++){                 //getting rid of paddings
                            pixels[mainCount]=white;
                            mainCount++;
                    }
                }



                  for(int j=1;j<=20;j++){
                    for(int k=1;k<=rowSize+paddingPerLine;k++){                                 //make white to the lower screen
                            pixels[mainCount]=white;
                            mainCount++;
                    }
                }


            }


}

void getLinearImage(unsigned char *pixels,int rowSize,int paddingPerLine){      //if linear barcode then it makes the pixels
            string encrytedCode;
            encrytedCode = getLinearEncryption();
            int lengthOfEncryptedCode = encrytedCode.length();
            //cout << encrytedCode << "\n";
            int lineCount=12;

           /* while(true){
                if((lengthOfEncryptedCode*lineCount)<rowSize)lineCount+=3;
                else{
                    lineCount-=3;
                    break;
                }
            }*/
            int quarters = (rowSize- (lengthOfEncryptedCode*lineCount))/2;

            //cout << quarters<<"   "<<rowSize<<"     "<< lengthOfEncryptedCode<<"     " << lineCount;
             int mainCount=0;

            while(mainCount<1){                     //the real equations to make the image

                                for(int j=1;j<=20;j++){
                                    for(int k=1;k<=rowSize+paddingPerLine;k++){                              //make white to the upper screen
                                            pixels[mainCount]=white;
                                            mainCount++;
                                    }
                                }


                                for(int i=1;i<=encodedInfo.heightIntE-40;i++){                                          //main drawing area
                                                for(int x=1;x<=quarters;x++){                                                       //first quarter white
                                                        pixels[mainCount]=white;
                                                        mainCount++;
                                                }

                                                for(int i=0;i<lengthOfEncryptedCode;i++){
                                                    if(encrytedCode[i]=='0'){                       //Blue                                          //BGR formated B+G=cyan  G+R=Yellow R+B=purple
                                                            for(int x=0;x<lineCount/3;x++){
                                                                    pixels[mainCount]=white;
                                                                    mainCount++;
                                                                    pixels[mainCount]=black;
                                                                    mainCount++;
                                                                    pixels[mainCount]=black;
                                                                    mainCount++;
                                                            }
                                                    }
                                                    else if (encrytedCode[i]=='1'){                 //Green // cyan
                                                             for(int x=0;x<lineCount/3;x++){
                                                                    pixels[mainCount]=black;
                                                                    mainCount++;
                                                                    pixels[mainCount]=white;
                                                                    mainCount++;
                                                                    pixels[mainCount]=black;
                                                                    mainCount++;
                                                            }
                                                    }
                                                    else if (encrytedCode[i]=='2'){                 //RED
                                                             for(int x=0;x<lineCount/3;x++){
                                                                    pixels[mainCount]=black;
                                                                    mainCount++;
                                                                    pixels[mainCount]=black;
                                                                    mainCount++;
                                                                    pixels[mainCount]=white;
                                                                    mainCount++;
                                                            }
                                                    }
                                                    else if (encrytedCode[i]=='3'){             //yellow
                                                             for(int x=0;x<lineCount/3;x++){
                                                                    pixels[mainCount]=black;
                                                                    mainCount++;
                                                                    pixels[mainCount]=white;
                                                                    mainCount++;
                                                                    pixels[mainCount]=white;
                                                                    mainCount++;
                                                            }
                                                    }
                                                }


                                                for(int x=quarters+(lengthOfEncryptedCode*lineCount);x<rowSize;x++){            //last quarter white
                                                        pixels[mainCount]=white;
                                                        mainCount++;
                                                }

                                                for(int x=1;x<=paddingPerLine;x++){                 //getting rid of paddings
                                                        pixels[mainCount]=white;
                                                        mainCount++;
                                                }
                                }



                                  for(int j=1;j<=20;j++){
                                    for(int k=1;k<=rowSize+paddingPerLine;k++){                                 //make white to the lower screen
                                            pixels[mainCount]=white;
                                            mainCount++;
                                    }
                                }


            }


}

void makeHeaderUPCEAN(bool UPC, bool EAN){      // writes the pixels in the image

    rowPad rowAndPad;
     FILE *outputFile,*inputFile;

    inputFile=fopen("SpecialForEncoding.bmp","rb");      //General header for my upc and ean images which i will encode
    fread(header,1,sizeof(header),inputFile);
    getHeaderForEncoding();                                         //calculates some important values for the image
    outputFile=fopen(fileNameToWrite.c_str(),"wb");
    if(!UPC && !EAN)header[6]='ÿ';                  //only signature to identify its linear ,important for later decoding
    fwrite(&header,1,54,outputFile);                                  //i have made the file bmp

    black =header[5];                   //i have the value black that i can write in the file
    white =  'ÿ';                               //I have the value of white that i can write it in the file

   rowAndPad = getPaddingInfo();

    pixelSize = encodedInfo.sizeOfFileE - encodedInfo.offsetIntE;           //size -54

    unsigned char pixels[pixelSize];

    if(UPC==false && EAN==false){
            getLinearImage(pixels,rowAndPad.rowsize,rowAndPad.paddingPerLine);
    }
    else{
            getImage(pixels,rowAndPad.rowsize,rowAndPad.paddingPerLine);
    }

   fseek(outputFile, encodedInfo.offsetIntE, SEEK_SET);
    fwrite(&pixels,1,sizeof(pixels),outputFile);
    fclose(outputFile);
//    outputFile.close();

}

void encode(){          //takes input checks barcode and bmp extension
    bool UPC=false,EAN=false;
    cout << "Enter the fileName in which you want to make your image and do give .bmp in the end: ";
    getline(cin,fileNameToWrite);
    string str = fileNameToWrite.substr((fileNameToWrite.length()-4),4);

    if(str!=".bmp"){
        cout << "There is no .bmp extension enter filename again with .bmp extension\n";
        encode();
    }
    bool foundBarcode=false;
    do{
        cout << "Enter the barcode: ";

        getline(cin,inputForEncoding);                                  //The barcode given by the User

        int lengthOfBarcode=inputForEncoding.length();

        if(lengthOfBarcode == 12){
            UPC = checkSumE(inputForEncoding);                   //Checks if UPC
        }
        else if(lengthOfBarcode == 13){
            EAN = checkEAN(inputForEncoding);                   //Checks if EAN
        }

       if(UPC){
                foundBarcode = true;
                cout << "UPC Barcode.\n";
                makeHeaderUPCEAN(UPC,EAN);

        }
        else if(EAN){
                foundBarcode = true;
                cout << "EAN Barcode.\n";
                makeHeaderUPCEAN(UPC,EAN);

        }

        else if(UPC==false && EAN==false){                       //If none make a linear barcode
            foundBarcode = true;
            cout << "Linear Barcode.\n";
            makeHeaderUPCEAN(UPC,EAN);
        }

    }while(foundBarcode==false);


}

void encode(string barcode){
	    bool UPC=false,EAN=false;
    cout << "Enter the fileName in which you want to make your image and do give .bmp in the end: ";
    getline(cin,fileNameToWrite);
    string str = fileNameToWrite.substr((fileNameToWrite.length()-4),4);

    if(str!=".bmp"){
        cout << "There is no .bmp extension enter filename again with .bmp extension\n";
        encode();
    }
    bool foundBarcode=false;

    do{
        //cout << "Enter the barcode: ";

	inputForEncoding=barcode;                                  //The barcode generated by the program

        int lengthOfBarcode=inputForEncoding.length();

        if(lengthOfBarcode == 12){
            UPC = checkSumE(inputForEncoding);                   //Checks if UPC
        }
        else if(lengthOfBarcode == 13){
            EAN = checkEAN(inputForEncoding);                   //Checks if EAN
        }

       if(UPC){
                foundBarcode = true;
                cout << "UPC Barcode.\n";
                makeHeaderUPCEAN(UPC,EAN);

        }
        else if(EAN){
                foundBarcode = true;
                cout << "EAN Barcode.\n";
                makeHeaderUPCEAN(UPC,EAN);

        }

        else if(UPC==false && EAN==false){                       //If none make a linear barcode
            foundBarcode = true;
            cout << "Linear Barcode.\n";
            makeHeaderUPCEAN(UPC,EAN);
        }

    }while(foundBarcode==false);
}
/*int main (){
    encode();
    return 0;
}*/
