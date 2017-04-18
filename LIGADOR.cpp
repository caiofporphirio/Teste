#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<iterator>
using namespace std;

int main() {
	string moda = "";
	ifstream file_a;
	file_a.open("moda.txt");
	if (file_a.is_open()) {
		string teste;
		while (!file_a.eof()) {
			string tempstring;
			getline(file_a, tempstring);
			moda += tempstring + '\n';
		}
	}
	else {
		cout <<"Erro" << endl;
	}// erro

	string modb = "";
	ifstream file_b;
	file_b.open("modb.txt");
	if (file_b.is_open()) {
		while (!file_b.eof()) {
			string tempstring;
			getline(file_b, tempstring);
			modb += tempstring + '\n';
		}
	}
	else {
		cout << "deu ruim" << endl;
	}
	file_b.close();


	int index_code_a, index_code_b, index_td_a, index_td_b, index_r_a, index_r_b, fator_correcao, k = 0;
	vector<int>vet_opcodeA;
	vector<int>vet_opcodeB;
	string opcodeA, opcodeB;
	
	index_code_a = moda.find("CODE");
	opcodeA = moda.substr(index_code_a + 5);// +5 pq code tem 4 letras
	opcodeA += ' ';
	
	index_code_b = modb.find("CODE");
	opcodeB = modb.substr(index_code_b + 5); // +5 pq code tem 4 letras
	opcodeB += ' ';

	
	//passando o opcode para um vetor de inteiros
	for (int i = 0; i < opcodeA.length(); i++) {
		string num_aux = "";
		int numero;
		
		if(opcodeA[i] != ' '){
			k++;
		}else{
			for (int j = k; j >= 1; j--) { //for decrementando pro num_aux nao ficar de traz pra frente
				num_aux += opcodeA[i - j];
			}
			k = 0;
			numero = stoi(num_aux);
			vet_opcodeA.push_back(numero);
		}
	}

	/*//Imprime o vetor
	for (int i = 0; i < vet_opcodeA.size(); i++)
	{
		cout << vet_opcodeA[i] << endl;
	}*/

	// De mod a eu ja acho o fator de correçao
	fator_correcao = vet_opcodeA.size();

	//passando o opcode para um vetor de inteiros
	for (int i = 0; i < opcodeB.length(); i++) {
		string num_aux = "";
		int numero;

		if (opcodeB[i] != ' ') {
			k++;
		}
		else {
			for (int j = k; j >= 1; j--) { //for decrementando pro num_aux nao ficar de traz pra frente
				num_aux += opcodeB[i - j];
			}

			k = 0;
			numero = stoi(num_aux);
			vet_opcodeB.push_back(numero);
		}
	}
	//criando uma substring do arquivo contendo apenas a tabela de def 
	int posicoes_td_a, posicoes_td_b;
	string definitionA, definitionB;
	index_td_a = moda.find("TABLE DEFINITION");
	index_r_a = moda.find("RELATIVE");
	posicoes_td_a = index_r_a - index_td_a - 18;
	definitionA = moda.substr(index_td_a+17, posicoes_td_a);

	index_td_b = modb.find("TABLE DEFINITION");
	index_r_b = modb.find("RELATIVE");
	posicoes_td_b = index_r_b - index_td_b - 18;
	definitionB = modb.substr(index_td_b + 17, posicoes_td_b);
	

	//Mapeando a tabela global de definiçoes
	map<string, int>tab_def;
	map<string, int>::iterator ittdef;
	int aux1 = 0, aux2, end_def;
	string rotulo_def, end_def_str;

	//Percorre a tabela de definiçoes de A
	for (int i = 0; i < definitionA.length(); i++) {
		if(definitionA[i] == ' '){
			aux2 = i +1;
			rotulo_def = definitionA.substr(aux1,i - aux1);
		}
		if (definitionA[i] == '\n') {
			aux1 = i+1;
			end_def_str = definitionA.substr(aux2, i - aux2);
			end_def = stoi(end_def_str);
			tab_def[rotulo_def] = end_def;
		}
	}

	aux1 = 0;
	//Percorre a tabela de definiçoes de B e corrige fator de correçao
	for (int i = 0; i < definitionB.length(); i++) {
		if (definitionB[i] == ' ') {
			aux2 = i + 1;
			rotulo_def = definitionB.substr(aux1, i - aux1);
		}
		if (definitionB[i] == '\n') {
			aux1 = i + 1;
			end_def_str = definitionB.substr(aux2, i - aux2);
			end_def = stoi(end_def_str) + fator_correcao;//Ja corrige o fator de correçao
			tab_def[rotulo_def] = end_def;
		}
	}

	/*//Imprime tabela de global de Definiçoes
	for (ittdef = tab_def.begin(); ittdef != tab_def.end(); ittdef++)
	{
		cout << ittdef->first << "  " << ittdef->second << endl;
	}
	*/

	int posicoes_tu_a, posicoes_tu_b, index_tu_a, index_tu_b;
	string useA, useB;
	index_tu_a = moda.find("TABLE USE");
	posicoes_tu_a = index_td_a - 11;
	useA = moda.substr(10, posicoes_tu_a);
	//cout << useA << endl;
	index_tu_b = modb.find("TABLE USE");
	posicoes_tu_b = index_td_b - 11;
	useB = modb.substr(10, posicoes_tu_b);
	//cout << useB << endl;


	//mapeia tabela de uso de A
	map<string, int>tab_useA;
	map<string, int>::iterator ittuseA;
	aux1 = 0;
	int end_useA;
	string rotulo_useA, end_useA_str;

	//Percorre a tabela de uso de A
	for (int i = 0; i < useA.length(); i++) {
		if (useA[i] == ' ') {
			aux2 = i + 1;
			rotulo_useA = useA.substr(aux1, i - aux1);
		}
		if (useA[i] == '\n') {
			aux1 = i + 1;
			end_useA_str = useA.substr(aux2, i - aux2);
			end_useA = stoi(end_useA_str);
			tab_useA[rotulo_useA] = end_useA;
		}
	}

	
	//Mapeia tabela de uso de B
	map<string, int>tab_useB;
	map<string, int>::iterator ittuseB;
	aux1 = 0;
	int end_useB;
	string rotulo_useB, end_useB_str;

	//Percorre a tabela de uso de B
	for (int i = 0; i < useB.length(); i++) {
		if (useB[i] == ' ') {
			aux2 = i + 1;
			rotulo_useB = useB.substr(aux1, i - aux1);
		}
		if (useB[i] == '\n') {
			aux1 = i + 1;
			end_useB_str = useB.substr(aux2, i - aux2);
			end_useB = stoi(end_useB_str);
			tab_useB[rotulo_useB] = end_useB;
		}
	}

	/*//imprime o mapa da tabela de uso
	for (ittuseB = tab_useB.begin(); ittuseB != tab_useB.end(); ittuseB++)
	{
		cout << ittuseB->first << "  " << ittuseB->second << endl;
	}*/



	
	for (ittuseA = tab_useA.begin(); ittuseA != tab_useA.end(); ittuseA++)
	{
		vet_opcodeA[ittuseA->second] = vet_opcodeA[ittuseA->second] + tab_def[ittuseA->first];
	}
	for (ittuseB = tab_useB.begin(); ittuseB != tab_useB.end(); ittuseB++)
	{
		vet_opcodeB[ittuseB->second] = vet_opcodeB[ittuseB->second] + tab_def[ittuseB->first];
	}
	
	
	int posicoes_r_a, posicoes_r_b;
	string relativesA, relativesB;
	posicoes_r_a = index_code_a - index_r_a - 10;
	relativesA = moda.substr(index_r_a + 9, posicoes_r_a);

	posicoes_r_b = index_code_b - index_r_b - 10;
	relativesB = modb.substr(index_r_b + 9, posicoes_r_b);
	relativesB += ' ';

	vector<int>vet_relativesA;
	vector<int>vet_relativesB;

	for (int i = 0; i < relativesB.length(); i++) {
		string num_aux = "";
		int numero;

		if (relativesB[i] != ' ') {
			k++;
		}
		else {
			for (int j = k; j >= 1; j--) { //for decrementando pro num_aux nao ficar de traz pra frente
				num_aux += relativesB[i - j];
			}

			k = 0;
			numero = stoi(num_aux);
			int ta_na_tab_use = false;
			for (ittuseB = tab_useB.begin(); ittuseB != tab_useB.end(); ittuseB++){
				if (ittuseB->second == numero){
					ta_na_tab_use = true;
				}
			}
			if(ta_na_tab_use == false)
				vet_relativesB.push_back(numero);//so coloca o numero no vetor de relativos se nao tiver ele na tab use
		}
	}
	for (int i = 0; i < vet_relativesB.size(); i++)
	{
		vet_opcodeB[vet_relativesB[i]] = vet_opcodeB[vet_relativesB[i]] + fator_correcao;
	}

	/*for (int i = 0; i < vet_opcodeA.size(); i++)
	{
	cout << vet_opcodeA[i] << endl;
	}
	cout<< endl;
	for (int i = 0; i < vet_opcodeB.size(); i++)
	{
	cout << vet_opcodeB[i] << endl;
	}*/
	
	ofstream file_exe;
	file_exe.open("TaLigado.txt");
	if (file_a.is_open()) {
		for (int i = 0; i < vet_opcodeA.size(); i++)
		{
			file_exe << vet_opcodeA[i] ;
			file_exe << " ";
		}
		for (int i = 0; i < vet_opcodeB.size(); i++)
		{
			file_exe << vet_opcodeB[i];
			file_exe << " ";
		}
	}
	else {
		cout << "deu ruim" << endl;
	}
	
	return 0;
}
