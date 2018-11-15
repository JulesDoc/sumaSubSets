//============================================================================
// Name        : sumaData.cpp
// Author      : Jules
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Given a list of numbers N and two integers M and C, this algorithm finds all subset of N composed by exactly M elements which sum exactly C
// Requirements: It need an input file with following format:
//					N1 N2 N3 .. Nn
//					M
//					C
//============================================================================

#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

vector<vector<bool>> matrizBool;

void procesarSolucion(vector<int> datos);
void calcularSubconjuntos(const vector<int> &datos, vector<bool> &temp ,unsigned int k, int &sumandos, int &suma, const int &m,const int &c);

int main(void){
	vector<int> datos;

	int m = 0;
	int c = 0;
	int number = 0;
	string line;
	istringstream ss;
	ifstream input_stream;
	try{
		input_stream.open("entrada.txt");
		getline(input_stream,line);
		ss.str(line);
		while(ss >> number){
			datos.push_back(number);
		}
		input_stream >> m;
		input_stream >> c;
		input_stream.close();
	}catch(ifstream::failure &readErr){
		cout << "Error opening/reading file" << endl;
	}

	if (m==1){
		ofstream output_stream("salida.txt");
		for (auto n : datos){
			if(n==c) output_stream << n << endl;
		}
		output_stream.close();
		return 0;
	}

	for (unsigned int i = 0; i < datos.size(); ++i){

		vector<bool> temp(datos.size(),false);
		int sumandos = 0;
		int suma = 0;

		calcularSubconjuntos(datos,temp,i,sumandos,suma,m,c);
	}

	procesarSolucion(datos);
	return 0;
}

void calcularSubconjuntos(const vector<int> &datos, vector<bool> &temp ,unsigned int k, int &sumandos, int &suma, const int &m, const int &c){


	if (k <= datos.size()){
		if(suma + datos[k] == c && (sumandos + 1) == m){
			temp[k] = true;
			matrizBool.push_back(temp);
		//	cout << endl;
		}
		else if(suma + datos[k] < c && (sumandos + 1) < m){
			suma = suma + datos[k];
			temp[k] = true;
			sumandos++;
			k++;
			calcularSubconjuntos(datos,temp,k,sumandos,suma, m, c);
		}
		else if((suma + datos[k] < c || suma + datos[k] > c) && (sumandos+1) == m){
			k++;
			calcularSubconjuntos(datos,temp,k,sumandos,suma, m, c);
		}
	}
}


void procesarSolucion(vector<int> datos){

	ofstream output_stream("salida.txt");
	for (unsigned int j = 0; j < matrizBool.size(); ++j){
		for (unsigned int i = 0; i < datos.size(); ++i){
			if(matrizBool[j][i] == true)
				output_stream << datos[i] << " ";
		}
		output_stream << endl;
	}
	output_stream.close();
}
