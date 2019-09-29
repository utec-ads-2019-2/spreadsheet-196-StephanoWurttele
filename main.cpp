#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int getrow(char valor){
	vector<char> alphabet({'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'});
	for(int i=0;i<26;i++){
		if(alphabet[i]==valor){
			return i;
		}
	}
}

void test(vector<vector<string>> &inputs,string input,vector<vector<int>> &matrix,int row,int column);


int getvalues(vector<vector<int>> &matrix,vector<string> &celdas, vector<vector<string>> &inputs,int row, int column){
	int j=0;
	string indice="";
	int place=0;
	int value=0;
	vector<int> numbers;
	for(int i=0;i<celdas.size();i++){
		for(int k=0;k<celdas[i].size();k++){
			if(!(isdigit(celdas[i][k]))){
				numbers.insert(numbers.begin(),getrow(celdas[i][k]));
			}
			else{
				indice=indice+celdas[i][k];
			}
		}
		place+=numbers[0];
		for(int i=1;i<numbers.size();i++){
			place+=(pow(26,i))*(numbers[i]+1);
		}
		int owo=stoi(indice)-1;
		if(!isdigit(inputs[owo][place][0])){
			test(inputs,inputs[owo][place],matrix,owo,place);
		}
		value+=stoi(inputs[owo][place]);
		numbers.clear();
		indice="";
		place=0;
	}
	return (value);
}

void test(vector<vector<string>> &inputs,string input,vector<vector<int>> &matrix,int row,int column){
	if(isdigit(input[0]) || input[0]=='-'){
		matrix[row][column]=stoi(input);
		return;
	}
	else{
		string celda="";
		vector<string> celdas={};
		for(auto it=input.begin()+1;it!=input.end();it++){
			if(*it!='+')
				celda+=*it;
			else{
				celdas.push_back(celda);
				celda="";
			}
		}
		celdas.push_back(celda);
		matrix[row][column]=(getvalues(matrix,celdas,inputs,row,column));
		inputs[row][column]=to_string(matrix[row][column]);
	}
}

int main(){
	int rounds, columns, rows;
	cin>>rounds;
	while(rounds--){
		string temp;
		cin>>columns>>rows;
		vector<vector<string>> inputs(rows);
		vector<vector<int>> matrix(rows);
		vector<string> temps(columns);

		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				cin>>temp;
				temps[j]=(temp);
			}
			inputs[i]=temps;
			matrix[i].resize(columns,0);
		}
		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				test(inputs,inputs[i][j],matrix,i,j); //test call
			}
		}
		for(int i=0;i<rows;i++){
			for(int j=0;j<columns-1;j++){
				cout<<matrix[i][j]<<" ";
			}
			cout<<matrix[i][columns-1];
			cout<<endl;
		}


	}
}
