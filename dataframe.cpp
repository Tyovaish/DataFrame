#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
//#include "quandl(windows).h"
#include<vector>
using namespace std;
class Matrix{
	public:
	vector<string> columnNames;
	vector< vector<double>> matrix;
	Matrix(string fileName){
		string line;
		 ifstream myfile (fileName.c_str());
			if (myfile.is_open())
			{
				myfile>>line;
				string cName="";
				for(int i=0;i<line.size();i++){
					while(i<line.size()&&line[i]!=','){
						cName.push_back(line[i]);
						i++;
					}
					columnNames.push_back(cName);
					cName="";
				}
				while ( myfile>>line )
				{
					matrix.push_back(parseInput(line,','));
				}
			myfile.close();
		}
}
Matrix(int rowLength,int columnLength){
	matrix.resize(rowLength);
	for(int i=0;i<rowLength;i++){
		for(int j=0;j<columnLength;j++){
			matrix[i].push_back(0);
		}
	}
}
double convertStringToDouble(string s){
	double sum=0;
	bool hasPeriod=false;
	int positionOfPeriod=0;
	for(int i=0;i<s.size();i++){
		if(s[i]!='.'){
		sum*=10;
		sum+=s[i]-'0';
		}else if (s[i]=='.'){
			hasPeriod=true;
			positionOfPeriod=s.size()-1-i;
		}
	}
	if(hasPeriod){
		sum/=pow(10,positionOfPeriod);
	}
	return sum;
}
vector < double> parseInput(string line, char c){
	vector< double> temp;
	string cName="";
				for(int i=0;i<line.size();i++){
					cName="";
				if(line[i]!='\n'&&line[i]!=' '){
					while(i<line.size()&&line[i]!=','&&line[i]!=' '){
						cName.push_back(line[i]);
						i++;
					}
					temp.push_back(convertStringToDouble(cName));
				}
			}
	return temp;
}
	Matrix * addData(double data,int xPosition,int yPosition){
		matrix[xPosition][yPosition]=data;
		return this;
	}
	/*Matrix * addData(double * data,int xPosition){
		if(xPosition>=xLength||xPosition<0){
			cout<<"Could not add Data, outside of bounds"<<endl;
			return this;		
		}
		for(int i=0;i<sizeof(data);i++){
			matrix[xPosition][i]=data[i];
		}
		return this;
	}*/
	Matrix * transpose(){
		Matrix * transposedMatrix=new Matrix(matrix[0].size(),matrix.size());
		for(int i=0;i<matrix[0].size();i++){
			for(int j=0;j<matrix.size();j++){
				transposedMatrix->matrix[i][j]=matrix[j][i];
			}
		}
		return transposedMatrix;
	}
	void deleteColumn(string columnNamesToBeDeleted[]){
		int size=sizeof(columnNamesToBeDeleted);
		for(int i=0;i<size;i++){
			for(int j=0;j<columnNames.size();j++){
				if(columnNamesToBeDeleted[i].compare(columnNames[j])==0){
					for(int k=0;k<matrix.size();k++){
						matrix[k].erase(matrix[k].begin()+j);
					}
				}
			}
		}
	}
	Matrix * add(Matrix * matrixB){
		Matrix * temp= new Matrix(matrix.size(),matrix[0].size());
		for(int i=0;i<matrix.size();i++){
			for(int j=0;j<matrix[i].size();j++){
				temp->matrix[i][j]=matrixB->matrix[i][j]+matrix[i][j];
			}
		}
		return temp;
		
	}
	Matrix * substract(Matrix * matrixB){
		Matrix * temp= new Matrix(matrix.size(),matrix[0].size());
		for(int i=0;i<matrix.size();i++){
			for(int j=0;j<matrix[i].size();j++){
				temp->matrix[i][j]=matrix[i][j]-matrixB->matrix[i][j];
			}
		}
		return temp;
		
	}
	Matrix * multiply(Matrix * matrixB){
		Matrix * multipliedMatrix= new Matrix(matrix.size(),matrixB->matrix[0].size());
	for(int k=0;k<matrixB->matrix[0].size();k++){
		for(int i=0;i<matrix.size();i++){
			int rowValue=0;
			for(int j=0;j<matrix[0].size();j++){
				rowValue+=matrix[i][j]*matrixB->matrix[j][k];
			}
			multipliedMatrix->addData(rowValue,i,k);
		}
	}
		return multipliedMatrix;
	}
	//TODO: MAKE AN INVERSE FUNCTION FOR A MATRIX
	Matrix * inverse(){
		
	}
	
	void print(){
		for(int i=0;i<columnNames.size();i++){
			cout<<columnNames[i]<<" ";
		}
		cout<<"\n";
		for(int i=0;i<matrix.size();i++){
			for(int j=0;j<matrix[i].size();j++){
				cout<<matrix[i][j]<<" ";
			}
			cout<<"\n";
		}
		
	}

};
class Matrix_UI{
	public:
	vector <string> variableNames;
	vector <Matrix *> matrices;
	vector<string> locationOfDataFrames;
	Matrix_UI(){
		int input=0;
		do{
		cout<<"DataFrame UI"<<endl;
		cout<<"1. Import Data to DataFrame"<<endl;
		cout<<"2. Show Current DataFrames"<<endl;
		cout<<"3. Edit DataFrames"<<endl;
		cout<<"4. Operation on DataFrames"<<endl;
		cout<<"5. Summary Statistics of DataFrame"<<endl;
		cin>>input;
		switch(input){
			case 1: string matrixName="";
					string fileLocation="";
					cout<<"DataFrame Name:";
					cin>>matrixName;
					cout<<"File Location";
					cin>>fileLocation;
					variableNames.push_back(matrixName);
					Matrix * temp= new Matrix(fileLocation.c_str());
					matrices.push_back(temp);
					break;
			case 2: break;
			case 3: break;
			case 4: break;
			
		}
		}while(input!=5);
		cout<<"EXITING UI"<<endl;
	}	
};
int main(){

	return 0;
}