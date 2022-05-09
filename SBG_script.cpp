#include <iostream>
#include <fstream>
using namespace std;

char user_field[10][10];
char computer_field[10][10];
char empty_computer_field[10][10];

bool is_player_move = true;

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
		cout << "Файл с игровым полем компьютера отсутствует.\n";
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
		cout << "Файл с Вашим игровым полем отсутствует.\n";
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
	
	cout << "Печать игрового поля пользователя(\'#\' - пустое пространство; \'*\' - корабль/часть корабля; \'-\' - промах; \'+\' - попадание по Вашему кораблю;): \n";
	print(user_field);
}

void print_empty_computer_field()
{
	cout << "Печать игрового поля противника(\'#\' - пустое пространство; \'*\' - корабль/часть корабля; \'-\' - промах;): \n";
	print(empty_computer_field);
}

int check(char field[10][10]) {
	int kolvo = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (field[i][j] == (char)42) {
				kolvo++;
			}
		}
	}
	return kolvo;
}

int check_for_mistakes(char field[10][10]) {
	int mistake = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (field[i][j] == (char)42) {//(char)42 = '*'
				if (j < 6 && field[i][j] == field[i][j + 1] && field[i][j + 1] == field[i][j + 2] && field[i][j + 2] == field[i][j + 3] && field[i][j + 4])//(char)42 = '*'
					mistake = 1;
				if (i < 6 && field[i][j] == field[i + 1][j] && field[i + 1][j] == field[i + 2][j] && field[i + 2][j] == field[i + 3][j] && field[i + 4][j])
					mistake = 2;
				if (j < 9 && i < 9 && j > 0 && i > 0 && (field[i][j] == field[i + 1][j + 1] || field[i][j] == field[i - 1][j + 1] || field[i][j] == field[i - 1][j - 1] || field[i][j] == field[i + 1][j - 1]))
					mistake = 3;
				if (j == 9 && i < 9 && (field[i][j] == field[i + 1][j - 1] || field[i][j] == field[i - 1][j - 1]))
					mistake = 4;
				if (j < 9 && i == 9 && (field[i][j] == field[i + 1][j - 1] || field[i][j] == field[i - 1][j - 1]))
					mistake = 5;
				if (j < 9 && i < 9 && i > 0 && j > 0 && ((field[i][j] == field[i + 1][j] && field[i][j] == field[i][j + 1]) || (field[i][j] == field[i - 1][j] && field[i][j] == field[i][j + 1]) || (field[i][j] == field[i + 1][j] && field[i][j] == field[i][j - 1]) || (field[i][j] == field[i - 1][j] && field[i][j] == field[i][j - 1])))
					mistake = 6;
				if (j == 0 && i == 0 && field[i][j] == field[i + 1][j] && field[i][j] == field[i][j + 1])
					mistake = 7;
				if (j == 9 && i == 0 && field[i][j] == field[i + 1][j] && field[i][j] == field[i][j - 1])
					mistake = 8;
				if (j == 0 && i == 9 && field[i][j] == field[i - 1][j] && field[i][j] == field[i][j + 1])
					mistake = 9;
				if (j == 9 && i == 9 && field[i][j] == field[i - 1][j] && field[i][j] == field[i][j - 1])
					mistake = 10;
			}
		}
	}
	return mistake;
}

bool error(char field[10][10]) 
{	
	if (check(field) == 20) {
		return false;
	}
	else if (check_for_mistakes(field) != 0) {
		cout << "Код ошибки: " << check_for_mistakes(field) << '\n';
		return true;
	}
	else {
		cout << "Код ошибки: 0\n";
		return true;
	}
}

int check_for_ships(char field[10][10]) {
	int kolvo = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (field[i][j] == (char)43) {
				kolvo++;
			}
		}
	}
	return kolvo;
}

int game_over() {
	if (check_for_ships(user_field) == 20) 
		return 1;
	else if (check_for_ships(empty_computer_field) == 20) 
		return 2;
	else
		return 0;
}

int make_player_move() {
	int fstcord, scdcord;
	do {
		cout << "Введите координаты для атаки (x [1; 10]; y [1; 10]): \n";
		cin >> fstcord >> scdcord;
		fstcord--;
		scdcord--;
		if (empty_computer_field[fstcord][scdcord] != '#' || fstcord > 9 || fstcord < 0 || scdcord < 0 || scdcord > 9)
			cout << "Введите другие координаты.\n";
	} while (empty_computer_field[fstcord][scdcord] != '#' || fstcord > 9 || fstcord < 0 || scdcord < 0 || scdcord > 9);
	if (computer_field[fstcord][scdcord] == '#') {
		cout << "Промах.\n";
		empty_computer_field[fstcord][scdcord] = (char)45;
		return 0;
	}
	if (computer_field[fstcord][scdcord] == '*') {
		cout << "Попадание.\n";
		empty_computer_field[fstcord][scdcord] = (char)43;
		return 1;
	}
}

int make_computer_move() {
	// Ход компьютера.
	int fstcord, scdcord;
	do {
		fstcord = rand() % 10;
		scdcord = rand() % 10;
	} while (user_field[fstcord][scdcord] != '#' && user_field[fstcord][scdcord] != '*');
	if (user_field[fstcord][scdcord] == '#') {
		user_field[fstcord][scdcord] = (char)45;// (char)45 = '-'
		return 0; 
	}
	else {
		user_field[fstcord][scdcord] = (char)43;// (char)43 = '+'
		return 1;
	}
}

void make_next_move() {
	if (is_player_move) {
		make_player_move();
		if (make_player_move() == 1)
			is_player_move = true;
		else
			is_player_move = false;
	}
	if(!is_player_move) {
		make_computer_move();
		if (make_computer_move() == 0)
			is_player_move = true;
		else
			is_player_move = false;
	}
	
}

void game() {
	fill_all_fields();

	if (error(user_field)) {
		cout << "Возникла ошибка в файлах Вашего игрового поля.\n";
	}
	else if (error(computer_field)) {
		cout << "Возникла ошибка в файлах игрового поля компьютера.\n";
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
			cout << "Игра окончена. Победитель: компьютер.\n";
		}
		if (game_over() == 2) {
			cout << "Игра окончена. Победитель: пользователь.\n";
		}
	}
}

void run()
{
	setlocale(LC_ALL, "russian");
	srand(time(nullptr));
	cout << "Добро пожаловать в игру \"Морской бой\".\n";
	cout << "Внимание! Перед началом игры проверьте все игровые поля(файлы \"CBF.txt\" и \"UBF.txt\" в папке с программой). В случае несоответствия расстановки элементов в игровых полях компьютер выдаст ошибку с ссылкой на файл.\n";
	cout << "Для начала игры введите 1, для выхода из программы введите 2.\n";
	int a = 0;
	do {
		cin >> a;
		switch (a) {
		case 1: {
			cout << "Начало игры.\n";
			game();
			break;
		}
		case 2: {
			cout << "Выход из программы.\n";
			break;
		}
		default: {
			cout << "Такой команды нет.\n";
			break;
		}
		}
	} while (a != 1 && a != 2);
}