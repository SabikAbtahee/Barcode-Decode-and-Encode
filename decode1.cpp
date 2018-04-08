#include<bits/stdc++.h>
#include<exception>
#include<vector>
#include <iostream>
#include<string>

using namespace std;

void fileOpen(ifstream &myFile);            //Prototypes
void storeHeaderBytes();
void processHeaderInformation();
void  printHeaderInformation();
void printSize();
void printWidth();
void printHeight();
void printPixelArray();
void printBitCount();
string startMidScan();
void printSignature();
void printHorizontalResolution();
void printVerticalResolution();
struct address getMidScanAddress();
bool checkSum(string answer);
void getEan(string answer);
int cToi(char x);
void decode();
void linearDecode();
string linearBarcodeAnswer(string finalDecode);
string getAlphabet(string temp);
char iToCD(int perDigit);

struct information{
	unsigned char signature[2];
	unsigned char sizeBytes[4];
	unsigned char reserved[4];
	unsigned char offset[4];
    int offsetInt;
	unsigned char dibHeader[4];
	unsigned char width[4];
	int widthInt;
    unsigned char height[4];
	int heightInt;
	unsigned char colorPanes[2];
	unsigned char bitCount[2];
	int bitCountInt;
	unsigned char compression[4];
	unsigned char rawBitmapData[4];
	unsigned char horizontalResolution[4];
	unsigned char verticalResolution[4];
	unsigned char colorPallete[4];
	unsigned char importantColor[4];
	int sizeOfFile;
};

struct address{
    int startAddress;
    int endAddress;
};

information info;
vector <unsigned char> bytes;
string binaryFormat;
long long int addressOfPixelArray;
int lineCount=12;

void fileOpen(ifstream &myFile){            //open the file by giving input

    unsigned char characters;
    string input;
    bool flag=true;

    while(flag==true){
        cout << "Enter the name of the image file:" ;
        getline(cin,input);
        myFile.open(input.c_str(),ifstream::binary);                          //Open Image file through here

        if(myFile.is_open()){
            flag=false;
            int i=0;
            do{
                characters = myFile.get();
                bytes.push_back(characters);
            }while(myFile.good());
        }
        else{
            cout << "Could Not Open File." << endl;
            cout << "Input correctly." << endl;
            flag =true;
          //  exit (EXIT_FAILURE);
        }
    }
}

void storeHeaderBytes(){                    //Stores 54 byte of header information

		for(int i=0,j=0;i<2;i++,j++){
			info.signature[i]=bytes[j];       //2 byte header BM
        }
        for(int i=0,j=2;i<4;i++,j++){       //4 byte size of image
			info.sizeBytes[i]=bytes[j];
        }
        for(int i=0,j=6;i<4;i++,j++){       //4 byte size of image
			info.reserved[i]=bytes[j];
        }
		for(int i=0,j=10;i<4;i++,j++){   //4 byte offset address
			info.offset[i] = bytes[j];
		}
		for(int i=0,j=14;i<4;i++,j++){
			info.dibHeader[i] = bytes[j];       //4 byte dib header
		}
		for(int i=0,j=18;i<4;i++,j++){
            info.width[i]=bytes[j];         //4 byte width
		}
		for(int i=0,j=22;i<4;i++,j++){
            info.height[i]=bytes[j];         //4 byte height
		}
		for(int i=0,j=26;i<2;i++,j++){       //4 byte size of image
			info.colorPanes[i]=bytes[j];
        }
        for(int i=0,j=28;i<2;i++,j++){
            info.bitCount[i] = bytes[j];
        }
        for(int i=0,j=30;i<4;i++,j++){
            info.compression[i] = bytes[j];
        }
        for(int i=0,j=34;i<4;i++,j++){
            info.rawBitmapData[i] = bytes[j];
        }
        for(int i=0,j=38;i<4;i++,j++){
            info.horizontalResolution[i] = bytes[j];   // 4 byte horizontalResolution
        }
        for(int i=0,j=42;i<4;i++,j++){
            info.verticalResolution[i] = bytes[j];    //4 byte verticalResolution
        }
        for(int i=0,j=46;i<4;i++,j++){
            info.colorPallete[i] = bytes[j];
        }
        for(int i=0,j=50;i<4;i++,j++){
            info.importantColor[i] = bytes[j];
        }
}

void processHeaderInformation(){            // processes all the needed values

    printSize();
    printWidth();
    printHeight();
    printPixelArray();
    printBitCount();
    //printHorizontalResolution();
    //printVerticalResolution();

}

void  printHeaderInformation(){             //Prints all the header information

    printSignature();
    cout << "Image Size is :" << info.sizeOfFile <<" bytes"<< endl;
    cout << "Image Width is :" << info.widthInt << endl;
    cout << "Image height is :" << info.heightInt << endl;
    cout << "Start of the pixel array: "<<addressOfPixelArray << endl;
    cout << "Bits per pixel : " << (int)info.bitCount[0] << endl;
    printHorizontalResolution();
    printVerticalResolution();
}

void printHorizontalResolution(){       //prints horizontal resolution

    int horizontalResolution = ((int)info.horizontalResolution[0]) + ((int)info.horizontalResolution[1] * 256) + ((int)info.horizontalResolution[2] * 65536) + ((int)info.horizontalResolution[3] * 16777216);
    cout << "Horizontal Resolution is " << horizontalResolution << " pixels per meter. " << "\n";

}

void printVerticalResolution(){             //prints vertical resolution

    int verticalResolution = ((int)info.verticalResolution[0]) + ((int)info.verticalResolution[1] * 256) + ((int)info.verticalResolution[2] * 65536) + ((int)info.verticalResolution[3] * 16777216);
    cout << "Vertical Resolution is " << verticalResolution << " pixels per meter. " << "\n";

}

void printSignature(){              //calculates signature

    printf("Image Signature is: %x %x\n",info.signature[0],info.signature[1]);
    if((int)info.signature[0]==66 && (int)info.signature[1]==77 ){
        cout << "Image is in BMP format.\n" ;
    }

}

void printSize(){                   //calculates size

    info.sizeOfFile = (int)info.sizeBytes[0] + ( ((int)info.sizeBytes[1]) * 256) + (((int)info.sizeBytes[2]) * 65536) + (((int)info.sizeBytes[3]) * 16777216);
    //cout << "Image Size is :" << info.sizeOfFile <<" bytes"<< endl;
}

void printWidth(){              //calculates Width

    info.widthInt = (((int)info.width[0]) + ((int)info.width[1] * 256) +((int)info.width[2] *65536) + ((int)info.width[3] *16777216));
    //cout << "Image Width is :" << info.widthInt << endl;

}

void printHeight(){             ////calculates Height

    info.heightInt = (((int)info.height[0]) + ((int)info.height[1] * 256) +((int)info.height[2] *65536) + ((int)info.height[3] *16777216));
    //cout << "Image height is :" << info.heightInt << endl;

}

void printPixelArray(){         //gets the starting of pixel array

    //long long int addressOfPixelArray;
    addressOfPixelArray = (((int)info.offset[0]) + ((int)info.offset[1] * 256) +((int)info.offset[2] *65536) + ((int)info.offset[3] *16777216));
    //cout << "Start of the pixel array: "<<addressOfPixelArray << endl;
    info.offsetInt= addressOfPixelArray;

}

void printBitCount(){               //gets the bit count

    //cout << "Bits per pixel : " << (int)info.bitCount[0] << endl;
    info.bitCountInt = (int)info.bitCount[0];

}

string approximation(string decode){                        //gets the 1's and 0's to 95 numbers approximately

    int last = decode.length()-1;
    float approx,send1,send0;
    string finalDecode = "";

    while(1){
        if(decode[last]=='1'){
            break;
        }
        last--;
    }
    approx = ((float)(last+1)/95);

    bool flag=true;
    int count0=0,count1=0;

    for(int i=0;i<=last;i++){
        if(decode[i]=='0' && flag==false){
            count0++;
            if(decode[i+1]=='1'){
                send0=(float)(count0/approx);
                if( (abs(send0-((int)send0)))>=0.5){
                    for(int i=0;i<((int)send0+1);i++){
                        if(i==4)break;
                        finalDecode = finalDecode + "0" ;

                    }
                }
                else if( (abs(send0-((int)send0)))<0.5){
                    for(int i=0;i<((int)send0);i++){
                        if(i==4)break;
                        finalDecode = finalDecode + "0" ;
                    }
                }
                count0=0;
                flag=true;
            }
        }

        else if(decode[i]=='1' && flag==true){
            count1++;
            if(decode[i+1]=='0'){
                send1=(float)(count1/approx);
                if( (abs(send1-((int)send1)))>=0.5){
                    for(int i=0;i<((int)send1+1);i++){
                        if(i==4)break;
                        finalDecode = finalDecode + "1" ;
                    }
                }
                else if( (abs(send1-((int)send1)))<0.5){
                    for(int i=0;i<((int)send1);i++){
                        if(i==4)break;
                        finalDecode = finalDecode + "1" ;
                    }
                }
                count1=0;
                flag=false;
            }
        }
    }
   // cout <<"\n\n\n\n"<< finalDecode << endl;
    return finalDecode;
}

string startMidScan(){                                       //      returns the final binary format of the barcode

    struct address midScan;
    midScan = getMidScanAddress();

    string decode = "";
    string finalDecode = "";

    int x = info.bitCountInt/8;
    float temp=0;
    bool startFlag=false;
    for(int i=midScan.startAddress;i<midScan.endAddress-x;i=i+x){
        for(int j=i;j<i+x;j++){
            temp = temp +(float)(bytes.at(j));
        }
        temp = temp/x;
        if(temp>127.5 && startFlag==true){
            decode = decode + "0";
        }
        else if(temp<=127.5){
            decode = decode + "1";
            startFlag = true;
        }
        temp=0;

    }
    //cout << decode << endl;
    finalDecode = approximation(decode);

    return finalDecode;

}

struct address getMidScanAddress(){                         //calculates the middle front address of the image to scan the image

    struct address r;
    int a,b,rowSize,startMidAddress,endMidAddress;

    a = info.sizeOfFile - info.offsetInt - (info.widthInt * info.heightInt * (info.bitCountInt/8));
    b = a/info.heightInt;
    rowSize = (info.widthInt * (info.bitCountInt/8))+b;
    startMidAddress = rowSize * ((int)(info.heightInt/2)) + info.offsetInt;
    endMidAddress = startMidAddress+rowSize-b;

    r.startAddress = startMidAddress;
    r.endAddress = endMidAddress;

    //cout << "Starting scan from : " << startMidAddress << endl;
    //cout << "End scan to : " << endMidAddress << endl;
    return r;

}

int cToi(char x){
    return (int)(x-48);
}

bool checkSum(string answer){                               //checks if UPC or not

    int x,y,a,b;

    x =cToi(answer[0]) + cToi(answer[2]) + cToi(answer[4]) + cToi(answer[6]) + cToi(answer[8]) + cToi(answer[10]);
    x = x*3;
    a =cToi(answer[1]) + cToi(answer[3]) +cToi(answer[5]) + cToi(answer[7]) + cToi(answer[9]);
    y = x + a;
    y = y % 10;
    if(y==0)y=10;
    b = 10 - y;
    if((cToi(answer[11]))==b){
        return true;
    }
    else{
        return false;
    }
}

void checkUpc(string result){                               //first checks upc or not if not goes to EAN checking

    //cout << result.length() << "   " << result << "\n\n\n";
    if(result.length()!=95){
        cout << "Corrupted" << endl;
        return;
    }
    string answer = "";
    bool flag = false,flag2=false;
    bool UPC;
    do{
        if(result.compare(0,3,"101")==0 && flag==false){
            flag = true;

        }

        else if (flag==true && answer.length()<6){
            for(int j=3;j<45;j=j+7){
                if(result.compare(j,7,"0001101")==0){
                    answer = answer + "0";
                }
                else if(result.compare(j,7,"0011001")==0){
                    answer =answer + "1";
                }
                else if(result.compare(j,7,"0010011")==0){
                    answer =answer + "2";
                }
                else if(result.compare(j,7,"0111101")==0){
                    answer =answer + "3";
                }
                else if(result.compare(j,7,"0100011")==0){
                    answer =answer + "4";
                }
                else if(result.compare(j,7,"0110001")==0){
                    answer =answer + "5";
                }
                else if(result.compare(j,7,"0101111")==0){
                    answer =answer + "6";
                }
                else if(result.compare(j,7,"0111011")==0){
                    answer =answer + "7";
                }
                else if(result.compare(j,7,"0110111")==0){
                    answer =answer + "8";
                }
                else if(result.compare(j,7,"0001011")==0){
                    answer =answer + "9";
                }
                else if(result.compare(j,7,"0100111")==0){
                    answer =answer + "0";
                }
                else if(result.compare(j,7,"0110011")==0){
                    answer =answer + "1";
                }
                else if(result.compare(j,7,"0011011")==0){
                    answer =answer + "2";
                }
                else if(result.compare(j,7,"0100001")==0){
                    answer =answer + "3";
                }
                else if(result.compare(j,7,"0011101")==0){
                    answer =answer + "4";
                }
                else if(result.compare(j,7,"0111001")==0){
                    answer =answer + "5";
                }
                else if(result.compare(j,7,"0000101")==0){
                    answer =answer + "6";
                }
                else if(result.compare(j,7,"0010001")==0){
                    answer =answer + "7";
                }
                else if(result.compare(j,7,"0001001")==0){
                    answer =answer + "8";
                }
                else if(result.compare(j,7,"0010111")==0){
                    answer =answer + "9";
                }
            }

        }

        else if(result.compare(45,5,"01010")==0 && flag2==false){
            flag2=true;
        }

        else if(flag2==true && answer.length()<12){
            for(int j=50;j<95;j=j+7){
                if(result.compare(j,7,"1110010")==0){
                    answer = answer + "0";
                }
                else if(result.compare(j,7,"1100110")==0){
                    answer =answer + "1";
                }
                else if(result.compare(j,7,"1101100")==0){
                    answer =answer + "2";
                }
                else if(result.compare(j,7,"1000010")==0){
                    answer =answer + "3";
                }
                else if(result.compare(j,7,"1011100")==0){
                    answer =answer + "4";
                }
                else if(result.compare(j,7,"1001110")==0){
                    answer =answer + "5";
                }
                else if(result.compare(j,7,"1010000")==0){
                    answer =answer + "6";
                }
                else if(result.compare(j,7,"1000100")==0){
                    answer =answer + "7";
                }
                else if(result.compare(j,7,"1001000")==0){
                    answer =answer + "8";
                }
                else if(result.compare(j,7,"1110100")==0){
                    answer =answer + "9";
                }
            }

        }

    }while(answer.length()!=12);

    //cout << answer << endl;
    UPC = checkSum(answer);

   if(UPC==true){
        cout << "\n\n" <<"Upc Barcode is: " << answer[0] << " " << answer.substr(1,5) << " " << answer.substr(6,5) << " "<< answer[11] << endl;

        searchInDatabase(answer);
   }
   else if(UPC==false){
        getEan(answer);
   }
}

char iToCD(int perDigit){
	return (perDigit+48);
}

void getEan(string answer){                                 //if this function is called then it returns shows the first digit and the rest of the barcode
    int x,y,a,b,firstDigit;

    x =(cToi(answer[0])) + (cToi(answer[2])) + (cToi(answer[4])) + (cToi(answer[6])) + (cToi(answer[8])) + (cToi(answer[10]));
    x = x*3;
    a =(cToi(answer[1])) + (cToi(answer[3])) +(cToi(answer[5])) + (cToi(answer[7])) +  (cToi(answer[9])) + (cToi(answer[11]));
    y = x + a;
    y = y % 10;
    if(y==0)y=10;
    b = 10 - y;

    firstDigit = b;
    //searchInDatabase(answer);
    cout << "\n\nEAN barcode is " << firstDigit << " " << answer.substr(0,6) << " " << answer.substr(6,6) << endl;

    answer = (char)(iToCD(firstDigit)) + answer ;
    searchInDatabase(answer);
    //cout << answer;

}

string getAlphabet(string temp){                        //return alphabet of current number
        string answer="";
        int x=0;
        for(int i=0;i<8;i++){
            if(temp[i]=='1')x=x+pow(2,i);

        }
        answer = (char)(x);

      return answer;
}

string linearBarcodeAnswer(string finalDecode){         //returns string by the code
    string answer="";
    string temp="";
    for(int i=0;i<finalDecode.length();i++){

        if(finalDecode[i]=='3')temp= temp+"11";
        else if(finalDecode[i]=='2')temp= temp+"10";
        else if(finalDecode[i]=='1')temp= temp+"01";
        else if(finalDecode[i]=='0')temp= temp+"00";

        if(temp.length()==8){

            answer = answer + getAlphabet(temp);
            temp="";

        }

    }

    return answer;

}

void linearDecode(){            //Decodes if barcode is linear
        struct address midScan;
        midScan = getMidScanAddress();

            string decode = "";
    string finalDecode = "";
    string Answer="";
    int x = info.bitCountInt/8;         //if x!=3 it wont work
    int temp=0;
    int a,b,c;
    bool startFlag=false;
    for(int i=midScan.startAddress;i<midScan.endAddress-x;i=i+x){

            a=(int)bytes.at(i);
            b=(int)bytes.at(i+1);
            c=(int)bytes.at(i+2);                               //BGR format    //BGR formated B+G=cyan  G+R=Yellow R+B=purple // 0 is blue , 1 is green ,2 is red , 3 is yellow
            temp = a+b+c;
            if(temp!=0)startFlag=true;
            else if (temp==0)startFlag=false;
            if(startFlag){
                    if(a==255 && b==0 && c==0){
                            decode+="0";
                    }
                    else if(a==0 && b==255 && c==0){
                            decode+="1";
                    }
                    else if(a==0 && b==0 && c==255){
                            decode+="2";
                    }
                    else if(a==0 && b==255 && c==255){
                            decode+="3";
                    }
            }

    }

    for(int i=0;i<decode.length();i=i+(lineCount/x)){
            finalDecode +=decode[i];
    }
    Answer = linearBarcodeAnswer(finalDecode);
    cout << "Linear Barcode \n\n" << Answer << "\n\n";
}

void decode(){              //Starts decoding
        ifstream myFile;
        fileOpen(myFile);
        storeHeaderBytes();
        processHeaderInformation();
        //printHeaderInformation();
        if(info.reserved[0]==255){
                linearDecode();
        }
        else{
            binaryFormat = startMidScan();
            checkUpc(binaryFormat);
        }
        bytes.clear();
}

