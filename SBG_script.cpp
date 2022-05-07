#include <iostream>
#include <fstream>
using namespace std;

char user_field[10][10];
char computer_field[10][10];
char empty_computer_field[10][10];

bool is_player_move;

void fill_empty_computer_field()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			empty_computer_field[i][j] = '#';
		}
	}
}

void fill_all_fields()
{
	char temp1[10][10];
	char temp2[10][10];
	ifstream computer_field_input("C:\\Users\\Admin\\source\\repos\\SeaBattleGameNatIlya\\CBF.txt");
	if (!computer_field_input) {
		cout << "���� � ������� ����� ���������� �����������.\n";
	}
	else {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				computer_field_input >> temp1[i][j];
			}
		}
		computer_field_input.close();
	}
	ifstream user_field_input("C:\\Users\\Admin\\source\\repos\\SeaBattleGameNatIlya\\UBF.txt");
	if (!user_field_input) {
		cout << "���� � ����� ������� ����� �����������.\n";
	}
	else {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				user_field_input >> temp2[i][j];
			}
		}
		user_field_input.close();
	}
	
	fill_empty_computer_field();

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			computer_field[i][j] = temp1[i][j];
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			user_field[i][j] = temp2[i][j];
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
	
	cout << "������ �������� ���� ������������(\'#\' - ������ ������������; \'*\' - �������/����� �������; \'-\' - ������; \'+\' - ��������� �� ������ �������;): \n";
	print(user_field);
}

void print_empty_computer_field()
{
	cout << "������ �������� ���� ����������(\'#\' - ������ ������������; \'*\' - �������/����� �������; \'-\' - ������;): \n";
	print(empty_computer_field);
}

int check(char field[10][10]) {
	int kolvo = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (field[i][j] == '*') {
				kolvo++;
			}
		}
	}
	return kolvo;
}

bool error(char field[10][10]) 
{	
	if (check(field) == 20) {
		return false;
	}
	else {
		return true;
	}
}

int game_over() {
	if (check(user_field) == 0) 
		return 1;
	else if (check(computer_field) == 0) 
		return 2;
	else
		return 0;
}

void make_player_move() {
	int fstcord, scdcord;
	do {
		cout << "������� ���������� ��� ����� (x [1; 10]; y [1; 10]): \n";
		cin >> fstcord >> scdcord;
		if (empty_computer_field[fstcord][scdcord] != '#')
			cout << "������� ������ ����������.\n";
	} while (empty_computer_field[fstcord][scdcord] != '#');
	fstcord--;
	scdcord--;
	if (computer_field[fstcord][scdcord] == '#') {
		cout << "������.\n";
		empty_computer_field[fstcord][scdcord] = (char)45;
	}
	if (computer_field[fstcord][scdcord] == '*') {
		if (computer_field[fstcord][scdcord] == computer_field[fstcord][scdcord + 1] || computer_field[fstcord][scdcord] == computer_field[fstcord][scdcord - 1] || computer_field[fstcord][scdcord] == computer_field[fstcord + 1][scdcord] || computer_field[fstcord][scdcord] == computer_field[fstcord - 1][scdcord]) {
			cout << "���������.\n";
			empty_computer_field[fstcord][scdcord] = (char)43;
		}
		else {
			cout << "������� ���������.";
		}
	}
}

void make_computer_move() {
	// ��� ����������.
	int fstcord;
	int scdcord{};
	do {
		fstcord = rand() % 10;
		scdcord = rand() % 10;
	} while (user_field[fstcord][scdcord] != '#');
	if (user_field[fstcord][scdcord] == '#')
		user_field[fstcord][scdcord] = (char)45;
	if (user_field[fstcord][scdcord] == '*')
		user_field[fstcord][scdcord] = (char)43;
}

void make_next_move() {
	if (is_player_move) {
		make_player_move();
		is_player_move = false;
	}
	else {
		make_computer_move();
		is_player_move = true;
	}
	
}
//char move_player_move() {
//	int row, col;
//	cout << "������� ���������� ���� x[]\n";
//	return '\0';
//}
/*if (field[i][j] == '*') {
					if (field[i][j] == field[i++][j++] || field[i][j] == field[i--][j--] || field[i][j] == field[i++][j--] || field[i][j] == field[i--][j++]) {
						return true;
					}
				}*/

void game() {
	fill_all_fields();

	if (error(user_field)) {
		cout << "�������� ������ � ������ ������ �������� ����.\n";
	}
	else if (error(computer_field)) {
		cout << "�������� ������ � ������ �������� ���� ����������.\n";
	}
	else {
		print_user_field();
		print_empty_computer_field();
		while (game_over() == 0) {
			make_next_move();
			if (is_player_move) {
				print_user_field();
				print_empty_computer_field();
			}
			game_over();
		}
		if (game_over() == 1) {
			cout << "���� ��������. ����������: ���������.\n";
		}
		if (game_over() == 2) {
			cout << "���� ��������. ����������: ������������.\n";
		}
	}
}

void run()
{
	setlocale(LC_ALL, "russian");
	cout << "����� ���������� � ���� \"������� ���\".\n";
	cout << "��������! ����� ������� ���� ��������� ��� ������� ����(����� \"CBF.txt\" � \"UBF.txt\" � ����� � ����������). � ������ �������������� ����������� ��������� � ������� ����� ��������� ������ ������ � ������� �� ����.\n";
	cout << "��� ������ ���� ������� 1, ��� ������ �� ��������� ������� 2.\n";
	int a = 0;
	do {
		cin >> a;
		switch (a) {
		case 1: {
			cout << "������ ����.\n";
			game();
			break;
		}
		case 2: {
			cout << "����� �� ���������.\n";
			break;
		}
		default: {
			cout << "����� ������� ���.\n";
			break;
		}
		}
	} while (a != 1 && a != 2);
}