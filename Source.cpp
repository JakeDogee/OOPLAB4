//18. Створити базовий клас НАСТІЛЬНА ГРА(задається назва).Створити похідний клас ШАХИ(задаються вага кожної з 32 фігур 6 типів, 
//	вага дошки для гри розміром 8x8).Для заданих прикладів різних комплектів настільних ігор відсортувати їх за зростанням ваги і обчислити сумарну вагу.


#include <iostream>
using namespace std;
#define LEN  10

enum Figures {
	DESK,
	PAWN,
	HOURSE,
	OFFICER,
	CASTLE,
	QUEEN,
	KING,
	MAX_FIGURES
};

class Games {

	string nameOfChess;

public:
	Games() : nameOfChess("Nothig") {};
	Games(string name) : nameOfChess(name) {};
	~Games() {};

	string getName() { return nameOfChess; }
	void SetName(string name) { nameOfChess = name; }
};

class Chess : public Games {

	double infOfChess[7];
	double weightOfChess;

public:

	Chess(double desk = 0, double pawn = 0, double hourse = 0, double officer = 0,
		double castle = 0, double queen = 0, double king = 0, string name = "----") : Games(name) {
		infOfChess[DESK] = desk;
		infOfChess[PAWN] = pawn;
		infOfChess[HOURSE] = hourse;
		infOfChess[OFFICER] = officer;
		infOfChess[CASTLE] = castle;
		infOfChess[QUEEN] = queen;
		infOfChess[KING] = king;
		weightOfChess = chessWeight(infOfChess);
	};

	~Chess() {};

	Chess operator + (Chess& obj) {
		for (int i = 0; i < MAX_FIGURES; i++)
			infOfChess[i] = obj.getFiguresWeight(i);

		weightOfChess = chessWeight(infOfChess);
		this->SetName(obj.getName());
		return *this;
	}

	double getFiguresWeight(int typeOfParam) { return infOfChess[typeOfParam]; }
	double weightOfAll() { return weightOfChess; }

	void SetWeight(int typeOfParam, double value) {
		infOfChess[typeOfParam] = value;
		chessWeight(infOfChess);
	}

	double chessWeight(double* chessInf) {
		return chessInf[DESK] + (chessInf[PAWN] * 16) + (chessInf[HOURSE] * 4) +
			(chessInf[OFFICER] * 4) + (chessInf[CASTLE] * 4) + (chessInf[QUEEN] * 2) + (chessInf[KING] * 2);
	}
};

ostream& operator << (ostream& out, Chess& obj) {
	char format[100];
	sprintf_s(format, "%10.2lf %10.2lf %10.2lf %10.2lf %10.2lf %10.2lf %10.2lf", obj.getFiguresWeight(DESK),
		obj.getFiguresWeight(PAWN), obj.getFiguresWeight(HOURSE), obj.getFiguresWeight(OFFICER),
		obj.getFiguresWeight(CASTLE), obj.getFiguresWeight(QUEEN), obj.getFiguresWeight(KING));
	return out << format << endl;
}

istream& operator >> (istream& in, Chess& obj) {
	int buffer;
	string bufferStr;
	for (int i = 0; i < MAX_FIGURES; i++) {
		in >> buffer;
		obj.SetWeight(i, buffer);
	}
	in >> bufferStr;
	obj.SetName(bufferStr);

	return in;
}


void Sort(Chess*, int, Chess);
void Input(Chess*, int*);
void Print(Chess*, int);
double AllWeight(Chess*, int);

int main() {
	Chess arrOfGames[LEN], * pArrOfGame = arrOfGames;
	Chess buffer;
	int count;

	Input(arrOfGames, &count);

	Print(arrOfGames, count);

	Sort(arrOfGames, count, buffer);

	Print(arrOfGames, count);

	cout << "\n\n\tWeight of all games : " << AllWeight(arrOfGames, count) << endl;

	getchar();
	return 0;
}

void Sort(Chess* desks, int enteredCount, Chess buffer) {
	Chess* pChess, * pBack;
	for (pChess = desks + 1; pChess < desks + enteredCount; pChess++) {
		if (pChess->weightOfAll() > (pChess - 1)->weightOfAll())
			continue;
		buffer = *pChess;
		for (pBack = pChess - 1; pBack->weightOfAll() > buffer.weightOfAll(); ) {
			*(pBack + 1) = *pBack;
			pBack--;
			if (desks > pBack)
				break;
		}
		*(pBack + 1) = buffer;
	}
}

void Input(Chess* pdesks, int* count) {
	int i;
	cout << "\n\n\t\tFor end enter print any letter\n\n" << endl;
	for (i = 0; i < LEN; ) {
		cout << "\tEnter weight of one desk, pawn, hourse, officer, castle, queen, king and name for object " << i + 1 << " : ";
		Chess temp;
		cin >> temp;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(2222, '\n');
			break;
		}
		*pdesks + temp;
		pdesks++;
		i++;
	}
	*count = i;
}

void Print(Chess* pdesks, int count) {
	printf("\n\n\t%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-20s%-20s\n\t", "Desk", "Pawn",
		"Hourse", "Officer", "Castle", "Queen", "King", "Average weight", "Name");
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < MAX_FIGURES; j++)
			printf("%-10.2lf", pdesks[i].getFiguresWeight(j));
		printf("%-20.2lf%-20s\n\t", pdesks[i].weightOfAll(), pdesks[i].getName().c_str());
	}
}

double AllWeight(Chess* desks, int count) {
	double res = 0;
	for (int i = 0; i < count; i++)
		res += desks[i].weightOfAll();
	return res;
}
