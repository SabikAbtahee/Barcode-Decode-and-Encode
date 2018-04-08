#include<bits/stdc++.h>
#include<fstream>


using namespace std;

void createDatabase ();
void setInFile();
string generateBarcode(int increment,int secondIncrement);
char getCheckDigit(string barcode );
char iToC(int perDigit);
void searchInDatabase(string barcode);
bool askForProduct();
int cToiD(char x);
bool searchInDatabaseX(string barcode);
bool searchInDatabaseX();

struct productInformation{
	string productType;
            string manufacturerName;
            string productName;


};

productInformation product;

bool askForProduct(){
	cout << "Enter product type: ";
	getline(cin,product.productType);

	cout << "Enter manufacturer name: ";
	getline(cin,product.manufacturerName);

	cout << "Enter product name: ";
	getline(cin,product.productName);

   bool x = searchInDatabaseX();
    return x;


}

void searchInDatabase(string barcode){
            ifstream database("database.txt");

            string type;
            string manufacturerName;
            string productName;
            string barcodeinFile;
	bool foundInfo = false;

            while(database >> type >> manufacturerName >> productName >> barcodeinFile){

		if(barcode==barcodeinFile){

                                    cout << "Product Type: " << type << endl;
                                    cout << "Manufacturer Name: " << manufacturerName << endl;
                                    cout << "Product Name: " << productName << endl;

			foundInfo=true;
		}
            }
            if(foundInfo==false){
		cout << "\nProduct not in database\n\n ";
            }
           // return foundInfo;
}

bool searchInDatabaseX(){
            ifstream database("database.txt");

            string type;
            string manufacturerName;
            string productName;
            string barcodeinFile;
            bool foundInfo = false;

            while(database >> type >> manufacturerName >> productName >> barcodeinFile){

                    if(type==product.productType && manufacturerName==product.manufacturerName && productName==product.productName){
                        cout << "Product already exists in Database. Corresponding barcode is  " << barcodeinFile << "\n";
                        foundInfo=true;
                    }
            }

            return foundInfo;
}

bool searchInDatabaseX(string barcode){
            ifstream database("database.txt");

            string type;
            string manufacturerName;
            string productName;
            string barcodeinFile;
	bool foundInfo = false;

            while(database >> type >> manufacturerName >> productName >> barcodeinFile){

                    if(barcode==barcodeinFile){
                        foundInfo=true;
                    }
            }

            return foundInfo;
}

char iToC(int perDigit){
	return (perDigit+48);
}

int cToiD(char x){
    return (int)(x-48);
}

char getCheckDigit(string barcode ){
            int total=0;
            for(int i=1;i<=11;i=i+2){
		total = total + (int)(cToiD(barcode[i]));
            }
            total = 3 * total;

            for(int j =0;j<=10;j=j+2){
		total = total + (int)(cToiD(barcode[j]));
            }
            total = total%10;
            if(total==0){
                total=10;
            }
	total = 10-total;
	//cout << total << "\n\n\n";
	char checkDigit;
	checkDigit=(char)(iToC(total));
	return checkDigit;
}

string generateBarcode(int increment,int secondIncrement){
	string barcode="";
	int perDigit;
	int extra=secondIncrement;
	for(int i=1;i<=12;i++){

		perDigit = i+increment;

		if(perDigit>=10){
			perDigit=perDigit%extra;
			secondIncrement--;
			if(secondIncrement==0){
				secondIncrement=10;
			}
		}
		barcode= barcode + (char)(iToC(perDigit));
	}

	barcode =barcode + (char)(getCheckDigit(barcode));

	bool foundInfo = searchInDatabaseX(barcode);
	//cout << endl<<foundInfo << endl;
	if(foundInfo){
			increment+=1;
			barcode = generateBarcode(increment,secondIncrement);
	}
	//encode(barcode);

	return barcode;

}

void setInFile(){
            ofstream database("database.txt",ios::app);
            bool check = askForProduct();
            if(check==false){
                    string barcodeMain = generateBarcode(0,10);
                    database <<  product.productType  <<  ' '   <<   product.manufacturerName   <<   ' '   <<   product.productName   <<   ' '  <<   barcodeMain  <<  endl;
                     //cout << barcodeMain << endl;
                    encode(barcodeMain);
            }// cout << barcodeMain << endl;


}

void createDatabase (){
	setInFile();
}
