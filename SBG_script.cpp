#include <iostream>
#include <fstream>
using namespace std;
char user_field[10][10];
char computer_field[10][10];
char empty_computer_field[10][10];

void fill_user_field()
{
	ifstream computer_field_input("C:\\Users\\Admin\\source\\repos\\SeaBattleGameNatIlya\\CBF.txt");
	if (!computer_field_input) {
		cout << "Файл с игровым полем компьютера отсутствует.\n";
	}
	else {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				computer_field_input >> computer_field[i][j];
			}
		}
		computer_field_input.close();
	}
	ifstream user_field_input("C:\\Users\\Admin\\source\\repos\\SeaBattleGameNatIlya\\UBF.txt");
	if (!user_field_input) {
		cout << "Файл с Вашим игровым полем отсутствует.\n";
	}
	else {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				user_field_input >> user_field[i][j];
			}
		}
		user_field_input.close();
	}
	
}

void fill_computer_field()
{
	
	
}

void fill_empty_computer_field()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			empty_computer_field[i][j] = '#';
		}
	}
}


void print(char field[10][10])
{
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			if (i == 0 && j != 0) {
				if (j == 10) {
					cout << 0;
				}
				else {
					cout << j;
				}
			}
			else if (j == 0) {
				if(i != 10) {
					cout << i;
				}
			else {
				cout << 0;
			}
			}
			else {
				cout << field[i - 1][j - 1];
			}
		}
		cout << "\n";
	}
	cout << '\n';
}

void print_user_field() 
{
	
	cout << "Печать игрового поля пользователя(\'#\' - пустое пространство; \'*\' - корабль/часть корабля; \'+\' - попадание по кораблю; \'-\' - промах;): \n";
	print(user_field);
}

void print_empty_computer_field()
{
	cout << "Печать игрового поля противника(\'#\' - пустое пространство; \'*\' - корабль/часть корабля; \'+\' - попадание по кораблю; \'-\' - промах;): \n";
	print(empty_computer_field);
}

bool error(char field[10][10]) 
{
	int kolvo = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (field[i][j] == '*') {
				kolvo++;
			}
		}
	}
	if (kolvo == 20) {
		return false;
	}
	else {
		return true;
	}
}

//char move_player_move() {
//	int row, col;
//	cout << "Введите координаты цели x[]\n";
//	return '\0';
//}
/*if (field[i][j] == '*') {
					if (field[i][j] == field[i++][j++] || field[i][j] == field[i--][j--] || field[i][j] == field[i++][j--] || field[i][j] == field[i--][j++]) {
						return true;
					}
				}*/

void first_stage()
{
	setlocale(LC_ALL, "russian");
	
	fill_computer_field();
	fill_user_field();
	fill_empty_computer_field();
	
	
	if (error(user_field) == true) {
		cout << "Возникла ошибка в файлах Вашего игрового поля.\n";
	}
	else if (error(computer_field) == true) {
		print(user_field);
		print(computer_field);
		cout << "Возникла ошибка в файлах игрового поля компьютера.\n";
	}
	else {
		print_user_field();
		print_empty_computer_field();
	}
	
}