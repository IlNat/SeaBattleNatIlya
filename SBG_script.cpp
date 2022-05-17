#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

enum { SHIP = '*', MISS = '-', HIT= '+', NOTHING = '#' };
//(char)35 = '#'; (char)42 = '*'; (char)43 = '+'; (char)45 = '-'; 

bool is_player_move = true;

const int max_num_of_cells = 20;
const int size_of_field = 10;
const int amount_of_threedecked = 2;
const int amount_of_doubledecked = 3;
const int amount_of_singledecked = 4;


//void fill_computer_field(char computer_field[size_of_field][size_of_field]) {
//	int xcord, ycord;
//	//Создаём четырёхпалубный корабль.
//	xcord = rand() % 8;
//	ycord = rand() % 8;
//	int v = rand() % 2;
//	if (v == 1) 
//	{
//		computer_field[xcord][ycord] = SHIP;
//		computer_field[xcord][ycord + 1] = SHIP;
//		computer_field[xcord][ycord + 2] = SHIP;
//		computer_field[xcord][ycord + 3] = SHIP;
//	}
//	else 
//	{
//		computer_field[xcord][ycord] = SHIP;
//		computer_field[xcord + 1][ycord] = SHIP;
//		computer_field[xcord + 2][ycord] = SHIP;
//		computer_field[xcord + 3][ycord] = SHIP;
//	}
//	for (int i = 1; i < amount_of_threedecked; i++)
//	{
//		{
//			xcord = rand() % 10;
//			ycord = rand() % 10;
//		} while (computer_field[xcord][ycord] == SHIP || computer_field[xcord + 1][ycord + 1] == SHIP || computer_field[xcord - 1][ycord - 1] == SHIP || computer_field[xcord - 1][ycord + 1] == SHIP || computer_field[xcord + 1][ycord - 1] == SHIP || computer_field[xcord + 1][ycord] == SHIP || computer_field[xcord - 1][ycord] == SHIP || computer_field[xcord][ycord + 1] == SHIP || computer_field[xcord][ycord - 1] == SHIP);
//
//	}
//}


void fill_all_fields(char user_field[size_of_field][size_of_field], char computer_field[size_of_field][size_of_field], char empty_computer_field[size_of_field][size_of_field])
{
	ifstream computer_field_input("CBF.txt");
	if (!computer_field_input) 
	{
		cout << "Файл с игровым полем компьютера отсутствует.\n";
	}
	else 
	{
		for (int i = 0; i < size_of_field; i++) 
		{
			for (int j = 0; j < size_of_field; j++) 
			{
				computer_field_input >> computer_field[i][j];
			}
		}
		computer_field_input.close();
	}

	ifstream user_field_input("UBF.txt");
	if (!user_field_input) 
	{
		cout << "Файл с Вашим игровым полем отсутствует.\n";
	}
	else 
	{
		for (int i = 0; i < size_of_field; i++) 
		{
			for (int j = 0; j < size_of_field; j++) 
			{
				user_field_input >> user_field[i][j];
			}
		}
		user_field_input.close();
	}

	/*fill_computer_field(computer_field);*/
	
	for (int i = 0; i < size_of_field; i++)
	{
		for (int j = 0; j < size_of_field; j++)
		{
			empty_computer_field[i][j] = NOTHING;
		}
	}
}




void print_field(char field[10][10], int a)
{
	if (a == 1)
	{
		cout << "Печать игрового поля пользователя(\'#\' - пустое пространство; \'*\' - корабль/часть корабля; \'-\' - промах; \'+\' - попадание по Вашему кораблю;): \n";
	}
	if (a == 2)
	{
		cout << "Печать игрового поля противника(\'#\' - пустое пространство; \'+\' - попадание; \'-\' - промах;): \n";
	}
	for (int i = 0; i < 11; i++) 
	{
		for (int j = 0; j < 11; j++) 
		{
			if (i == 0 && j != 0) 
			{
				if (j == 10) 
				{
					cout << 0;
				}
				else 
				{
					cout << j;
				}
			}
			else if (j == 0) 
			{
				if(i != 10) 
				{
					cout << i;
				}
			else 
				{
					cout << 0;
				}
			}
			else 
			{
				cout << field[i - 1][j - 1];
			}
		}
		cout << "\n";
	}
	cout << '\n';
}

int check(char field[10][10]) 
{
	int amount_of_cells = 0;
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++) 
		{
			if (field[i][j] == SHIP) 
			{
				amount_of_cells++;
			}
		}
	}
	return amount_of_cells;
}

// Проверка полей на ошибки расстановки кораблей.
int check_for_mistakes(char field[10][10]) 
{
	int mistake = 0;
	for (int i = 0; i < 9; i++) 
	{
		for (int j = 0; j < 9; j++) 
		{
			if (field[i][j] == SHIP) 
			{ 
				if (j < 6 && field[i][j + 1] == SHIP && field[i][j + 2] == SHIP && field[i][j + 3] == SHIP && field[i][j + 4] == SHIP)//(char)42 = '*'
					mistake = 1;
				if (i < 6 && field[i + 1][j] == SHIP && field[i + 2][j] == SHIP && field[i + 3][j] == SHIP && field[i + 4][j] == SHIP)
					mistake = 2;
				if (j < 9 && i < 9 && j > 0 && i > 0 && (field[i + 1][j + 1] == SHIP || field[i - 1][j + 1] == SHIP || field[i - 1][j - 1] == SHIP || field[i + 1][j - 1] == SHIP))
					mistake = 3;
				if (j == 9 && i < 9 && (field[i + 1][j - 1] == SHIP ||field[i - 1][j - 1] == SHIP))
					mistake = 4;
				if (j < 9 && i == 9 && (field[i + 1][j - 1] == SHIP ||field[i - 1][j - 1] == SHIP))
					mistake = 5;
				if (j < 9 && i < 9 && i > 0 && j > 0 && ((field[i + 1][j] == SHIP && field[i][j + 1] == SHIP) || (field[i - 1][j] == SHIP && field[i][j + 1] == SHIP) || (field[i + 1][j] == SHIP && field[i][j - 1] == SHIP) || (field[i - 1][j] == SHIP && field[i][j - 1] == SHIP)))
					mistake = 6;
				if (j == 0 && i == 0 && field[i + 1][j] == SHIP && field[i][j + 1] == SHIP)
					mistake = 7;
				if (j == 9 && i == 0 && field[i + 1][j] == SHIP && field[i][j - 1] == SHIP)
					mistake = 8;
				if (j == 0 && i == 9 && field[i - 1][j] == SHIP && field[i][j + 1] == SHIP)
					mistake = 9;
				if (j == 9 && i == 9 && field[i - 1][j] == SHIP && field[i][j - 1] == SHIP)
					mistake = 10;
			}
		}
	}
	return mistake;
}

//Возвращает значение "true" если произошла ошибка. 
bool error(char field[10][10])
{	
	bool mistake = false;
	if (check(field) != 20) 
	{
		cout << "Количество ячеек кораблей больше или меньше необходимого.\n";
		mistake = true;
	}
	int a = check_for_mistakes(field);
	if (a != 0) 
	{
		if (a == 1)
			cout << "В ряду 5 ячеек корабля." << '\n';
		if (a == 2)
			cout << "В столбике 5 ячеек корабля." << '\n';
		if (a == 3)
			cout << "В столбике 5 ячеек корабля." << '\n';
		if (a == 4)
			cout << "В 9 ряду ячейки кораблей соприкасаются наискосок." << '\n';
		if (a == 5)
			cout << "В 9 столбике ячейки кораблей соприкасаются наискосок." << '\n';
		if (a == 6)
			cout << "В ячейки кораблей соприкасаются с разных сторон." << '\n';
		if (a == 7)
			cout << "В углу[1; 1] ячейки кораблей соприкасаются с разных сторон." << '\n';
		if (a == 8)
			cout << "В углу[1; 10] ячейки кораблей соприкасаются с разных сторон." << '\n';
		if (a == 9)
			cout << "В углу[10; 1] ячейки кораблей соприкасаются с разных сторон." << '\n';
		if (a == 10)
			cout << "В углу[10; 10] ячейки кораблей соприкасаются с разных сторон." << '\n';
		mistake = true;
	}

	else 
	{
		mistake = false;
	}
	return mistake;
}

int check_for_destroyed_ships(char field[10][10]) 
{
	int amount_of_cells = 0;
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++) 
		{
			if (field[i][j] == (char)43) 
			{
				amount_of_cells++;
			}
		}
	}
	return amount_of_cells;
}

int game_over(char user_field[size_of_field][size_of_field], char empty_computer_field[size_of_field][size_of_field])
{
	if (check_for_destroyed_ships(user_field) == max_num_of_cells) 
		return 1;
	else if (check_for_destroyed_ships(empty_computer_field) == max_num_of_cells) 
		return 2;
	else
		return 0;
}

int make_player_move(char computer_field[size_of_field][size_of_field], char empty_computer_field[size_of_field][size_of_field])
{
	int xcord, ycord;
	do 
	{
		cout << "Введите координаты для атаки (x [от 1 до 10]; y [от 1 до 10]): \n";
		cin >> xcord >> ycord;
		xcord--;
		ycord--;
		if (empty_computer_field[xcord][ycord] != (char)35 || xcord > 9 || xcord < 0 || ycord < 0 || ycord > 9)
			cout << "Введите другие координаты.\n";
	} while (empty_computer_field[xcord][ycord] != (char)35 || xcord > 9 || xcord < 0 || ycord < 0 || ycord > 9);
	if (computer_field[xcord][ycord] == '#') 
	{
		cout << "Промах.\n";
		empty_computer_field[xcord][ycord] = (char)45;
		return 0;
	}
	if (computer_field[xcord][ycord] == '*') 
	{
		cout << "Попадание.\n";
		empty_computer_field[xcord][ycord] = (char)43;
		return 1;
	}
}

// Ход компьютера.
int make_computer_move(char user_field[size_of_field][size_of_field])
{
	int xcord, ycord;
	do 
	{
		xcord = rand() % 10;
		ycord = rand() % 10;
	} while (user_field[xcord][ycord] != (char)35 && user_field[xcord][ycord] != (char)42);
	if (user_field[xcord][ycord] == (char)35) 
	{
		user_field[xcord][ycord] = (char)45;
		return 0; 
	}
	else 
	{
		user_field[xcord][ycord] = (char)43;
		return 1;
	}
}

void make_next_move(char user_field[size_of_field][size_of_field], char computer_field[size_of_field][size_of_field], char empty_computer_field[size_of_field][size_of_field])
{
	if (is_player_move) 
	{
		if (make_player_move(computer_field, empty_computer_field) == 1)
			is_player_move = true;
		else
			is_player_move = false;
	}
	if(!is_player_move) 
	{
		if (make_computer_move(user_field) == 0)
			is_player_move = true;
		else
			is_player_move = false;
	}
	
}

void game() 
{
	char user_field[size_of_field][size_of_field];
	char computer_field[size_of_field][size_of_field];
	char empty_computer_field[size_of_field][size_of_field];

	fill_all_fields(user_field, computer_field, empty_computer_field);

	if (error(user_field)) 
	{
		cout << "Возникла ошибка в файлах Вашего игрового поля.\n";
	}
	else if (error(computer_field)) 
	{
		cout << "Возникла ошибка в файлах игрового поля компьютера.\n";
	}
	else {
		print_field(user_field, 1);
		print_field(empty_computer_field, 2);
		while (game_over(user_field, empty_computer_field) == 0)
		{
			make_next_move(user_field, computer_field, empty_computer_field);
			if (is_player_move) 
			{
				print_field(user_field, 1);
				print_field(empty_computer_field, 2);
			}
			game_over(user_field, empty_computer_field);
		}
		if (game_over(user_field, empty_computer_field) == 1) 
		{
			cout << "Игра окончена. Победитель: компьютер.\n";
		}
		if (game_over(user_field, empty_computer_field) == 2) 
		{
			cout << "Игра окончена. Победитель: пользователь.\n";
		}
	}
}
