#include "stdafx.h"
#include <locale>
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

bool IsValidString(string str, string alfabet) {
	int count = 0;
	for (int i = 0; i < str.size(); ++i) {
		for (int j = 0; j < alfabet.size(); ++j) {
			if (str[i] == alfabet[j]) {
				count++;
				break;
			}
		}
	}
	if (count == str.size()) return true; 
	else return false;
}

char GetInput(string strinfo) {
	char* buffer;
	buffer = new char[1000];
	string result;
	bool flag = false;
	do {
		cout << strinfo;
		cin.getline(buffer, 1000);
		result = buffer;
		if (result.size() == 1 && (result[0] == '0' || result[0] == '1')) flag = true;
		else cout << "Ошибка ввода" << endl;
	} while (!flag);
	return result[0];
}

string GetInput(string strinfo, string alfabet, bool isKeyWord = false) {
	char* buffer;
	buffer = new char[1000];
	string result;
	if (isKeyWord) alfabet[alfabet.size()-1] = alfabet[0];
	bool flag = false;
	do {
		cout << strinfo;
		cin.getline(buffer, 1000);
		result = buffer;
		for (int i = 0; i < result.size() - 1; ++i){
			if (result[i]>'A' && result[i]<'Z') result[i] += 'z' - 'Z';
			if (result[i]>'А' && result[i]<'Я') result[i] += 'я' - 'Я';
		}
		if (IsValidString(result, alfabet)) flag = true;
		else cout << "Ошибка ввода" << endl;
	} while (!flag);
	return result;
}

int GetNumber(char symbol, string alfabet){
	for (int i = 0; i < alfabet.size(); ++i) {
		if (symbol == alfabet[i]) return i;
	}
}

string Encryption(string text, string keyWord, string alfabet) {
	string result;
	int countKeyWord = 0;
	for (int i = 0; i < text.size(); ++i) {
		int newCount = GetNumber(text[i], alfabet) + GetNumber(keyWord[countKeyWord], alfabet) + 1;
		if (newCount > alfabet.size() - 1) newCount -= alfabet.size();
		result.push_back(alfabet[newCount]);
		if ((countKeyWord + 1) > keyWord.size() - 1) countKeyWord = 0;
		else countKeyWord++;
	}
	return result;
}

string Decryption(string text, string keyWord, string alfabet) {
	string result;
	int countKeyWord = 0;
	for (int i = 0; i < text.size(); ++i) {
		int newCount = GetNumber(text[i], alfabet) - GetNumber(keyWord[countKeyWord], alfabet) - 1;
		if (newCount < 0) newCount += alfabet.size();
		result.push_back(alfabet[newCount]);
		if ((countKeyWord + 1) > keyWord.size() - 1) countKeyWord = 0;
		else countKeyWord++;
	}
	return result;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string text;
	string keyWord;
	string alfabetRus = "абвгдежзийклмнопрстуфхцчшщъыьэюя ";
	string alfabetEng = "abcdefghijklmnopqrstuvwxyz ";
	
	while (true) {
		switch (GetInput("Выберите язык (0-русский, 1-english): ")) {
		case '0':

			keyWord = GetInput("Введите ключевое слово: ", alfabetRus, true);
			text = GetInput("Введите текст: ", alfabetRus);
			switch (GetInput("Выберите действие (0-зашифровать, 1-расшифровать): ")) {
			case '0':
				cout << "Результат: " << Encryption(text, keyWord, alfabetRus) << endl;
				break;
			case '1':
				cout << "Результат: " << Decryption(text, keyWord, alfabetRus) << endl;
				break;
			}
			break;
		case '1':

			keyWord = GetInput("Введите ключевое слово: ", alfabetEng, true);
			text = GetInput("Введите текст: ", alfabetEng);
			switch (GetInput("Выберите действие (0-зашифровать, 1-расшифровать): ")) {
			case '0':
				cout << "Результат: " << Encryption(text, keyWord, alfabetEng) << endl;
				break;
			case '1':
				cout << "Результат: " << Decryption(text, keyWord, alfabetEng) << endl;
				break;
			}
			break;
		}
	}
    return 0;
}