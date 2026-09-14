#include <iostream>
#include <string>
#include <fstream>

using namespace std;


void frequencyAnalysis(string file);
void displayText(string file);
void letterSwap(string file, char a, char b);
const string encoded = "cipherText.txt";
const string decoded = "plainText.txt";

int main() {
	int choice = 0;
	char letter1 = 'a';
	char letter2 = 'b';

	cout << "| CODEBREAKER: SUBSTITUTION |\n";
	while (choice != 4) {
		cout << "||COMMANDS||\n" << "1) Frequency Analysis\n" << "2) Letter Swap\n" << "3) Display Decoding File\n" << "4) Exit\n";
		cout << "ENTER COPMMAND CODE: ";
		cin >> choice;
		while (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
			cout << "INVALID CODE!\nENTER NEW CODE:";
			cin >> choice;
		}
		switch (choice) {
		case 1:
			frequencyAnalysis(encoded);
			break;
		case 2:
			cout << "ENTER ORIGINAL LETTER: ";
			cin >> letter1;
			cout << "ENTER NEW LETTER: ";
			cin >> letter2;
			letterSwap(decoded, letter1, letter2);
			break;
		case 3:
			displayText(decoded);
			break;
		case 4:
			cout << "TERMINATE SESSION";
			break;
		}
	}

	return 0;
}

void frequencyAnalysis(string file) {
	int  frequency[26] = {0};
	int total = 0;
	char c;
	ifstream inFile(file);

	if (!inFile) {
		cerr << "ERROR: COULD NOT OPEN";
		return;
	}
	while (inFile.get(c)) {
		frequency[c - 'a']++;
		total++;
	}
	inFile.close();

	cout << "LETTER | AMOUNT | FREQUENCY\n";
	for (int i = 0; i < 26; i++) {
		double rate = (total > 0) ? (static_cast<double>(frequency[i]) / total) * 100 : 0;
		cout << (char)('a' + i) << " | " << frequency[i] << " | " << rate << "%\n";
	}
}

void displayText(string file) {
	ifstream inFile(file);

	if (!inFile) {
		cerr << "ERROR: COULD NOT OPEN";
		return;
	}
	string line;
	while (getline(inFile, line)) {
		cout << line << endl;
	}
	inFile.close();
}

void letterSwap(string file, char a, char b) {
	char c;
	fstream ioFile(file, ios::in | ios::out | ios::binary);
	if (!ioFile) {
		cerr << "ERROR: COULD NOT OPEN";
		return;
	}
	while (ioFile.get(c)) {
		if (c == a) {
			ioFile.seekp(-1, ios::cur);
			ioFile.put(b);
			ioFile.seekg(ioFile.tellp());
		}
		if (c == b) {
			ioFile.seekp(-1, ios::cur);
			ioFile.put(a);
			ioFile.seekg(ioFile.tellp());
		}
	}
	ioFile.close();
}