#include <iostream>
#include <locale.h>
#include <Windows.h>

/*Если последний камень попал в пустую лунку принадлежащую ему и
противоположная лунка соперника не пуста, то этот камень и все камни из противоположной лунки соперника игрок переносит себе в калах. - ИСПРАВИТЬ MOVE*/

void ini_new_game(int mArray[14])
{
	for (int i = 0; i < 14; i++)
	{
		if (i != 6 && i != 13)
			mArray[i] = 6;
		else
			mArray[i] = 0;
	}
}


//0 - нижний игрок
//1 - верхний игрок

//функция возвращает 1 если происходит смена хода, 0 если не происходит
bool move(int mArray[14], int number, bool player, bool comp_or_player)
{
	if ((comp_or_player && player && (number < 6 || number > 12)) || (comp_or_player && !player && (number > 6 || number < 0)))// проверка на дурака
	{
		//cout << "Ход не соответствует игроку\nВведите любое число, чтобы продолжить, player == " << player << "i == " << number << endl;
		printf("Ход не соответствует игроку\nВведите любое число, чтобы продолжить, player == %d   i == %d\n", player, number);
		int tmp;
		//cin >> tmp;
		//scanf_s("%d", &tmp);
	}

	//if (comp_or_player && !player && (number > 6 || number < 0))
	//{
	//	//cout << "Ход не соответствует игроку\nВведите любое число, чтобы продолжить, player == " << player << "i == " << number << endl;
	//	printf("Ход не соответствует игроку\nВведите любое число, чтобы продолжить, player == %d   i == %d\n", player, number);
	//	int tmp;
	//	//scanf_s("%d", &tmp);
	//	//cin >> tmp;
	//}

	if (!comp_or_player)
	{
		if (player)
			number += 7;
		number--;
	}

	int count = mArray[number];
	mArray[number] = 0;
	int i = number;
	int tmp = -1;

	i++;
	if (player)//ходит верхний игрок
	{
		do
		{
			for (i; (i < 14) && (count > 0); i++)
			{
				if (i != 6)
				{
					tmp = mArray[i];
					//mArray[i]++;
					__asm {
						mov         eax, dword ptr[i]
						mov         ecx, dword ptr[mArray]
						mov         edx, dword ptr[ecx + eax * 4]
						add         edx, 1
						mov         eax, dword ptr[i]
						mov         ecx, dword ptr[mArray]
						mov         dword ptr[ecx + eax * 4], edx

					}

					//count--;
					__asm {
						mov         eax, dword ptr[count]
						sub         eax, 1
						mov         dword ptr[count], eax
					}
				}
			}
			if (count != 0)
				i = 0;
		} while (count != 0);

		i--;
		if (tmp == 0 && (i < 13 && i>6) && mArray[12 - i] != 0)
		{
			//i--;

			//new: (comment next line)
			//cout << "\nПопадание последнего камня в свою нулевую лунку и проиивоположная лунке не нулевая";

			//mArray[13] = mArray[13] + mArray[12 - i] + 1;
			__asm {
				mov         eax, 4
				imul        ecx, eax, 0Dh
				mov         edx, 0Ch
				sub         edx, dword ptr[i]
				mov         eax, dword ptr[mArray]
				mov         ecx, dword ptr[eax + ecx]
				mov         eax, dword ptr[mArray]
				mov         edx, dword ptr[eax + edx * 4]
				lea         eax, [ecx + edx + 1]
				mov         ecx, 4
				imul        edx, ecx, 0Dh
				mov         ecx, dword ptr[mArray]
				mov         dword ptr[ecx + edx], eax
			}
			mArray[i] = 0;
			mArray[12 - i] = 0;
			//i++;
		}

		if (i == 13)
		{
			//new: (comment next line)
			//cout << "\nПопадание последнего камня в калах";
			return 0;
		}
	}
	else
	{
		do
		{
			for (i; (i < 13) && (count > 0); i++)
			{
				tmp = mArray[i];
				mArray[i]++;
				count--;
			}
			if (count != 0)
				i = 0;
		} while (count != 0);

		i--;

		if (tmp == 0 && i < 6 && mArray[12 - i] != 0)
		{
			//i--;

			//new: (comment next line)
			//cout << "\nПопадание последнего камня в свою нулевую лунку";

			//mArray[6] = mArray[6] + mArray[12 - i] + 1;
			__asm {
				mov         eax, 4
				imul        ecx, eax, 6
				mov         edx, 0Ch
				sub         edx, dword ptr[i]
				mov         eax, dword ptr[mArray]
				mov         ecx, dword ptr[eax + ecx]
				mov         eax, dword ptr[mArray]
				mov         edx, dword ptr[eax + edx * 4]
				lea         eax, [ecx + edx + 1]
				mov         ecx, 4
				imul        edx, ecx, 6
				mov         ecx, dword ptr[mArray]
				mov         dword ptr[ecx + edx], eax
			}
			mArray[i] = 0;
			mArray[12 - i] = 0;
			//i++;
		}

		if (i == 6)
		{
			//new: (comment next line)
			//cout << "\nПопадание последнего камня в калах";
			return 0;
		}
	}
	//cout << "СМЕНА ИГРОКА   СМЕНА ИГРОКА   СМЕНА ИГРОКА" << endl;
	return 1;
}

//пока глубина не три - ход
//гл == три - сохраняем кол-во очков + запоминаем первый ход и возращаемся на пред уровень -> далее ходим следующей позицией
//вся функция работает пока нижний уровень не уйдет на 7
//сделать функцию которая будет принимать копию поля а не само поле 

void copyArray14(int* izn, int* it)
{
	for (int i = 0; i < 14; i++)
	{
		it[i] = izn[i];
	}
}


//alg_opt_old:
//void print_playing_field(int* mArray)
//{
//	cout << "\n______________________\n";
//	cout << "    6 5 4 3 2 1\n\n";
//	cout << mArray[13] << "   ";
//	for (int i = 12; i > 6; i--)
//	{
//		cout << mArray[i] << " ";
//	}
//	cout << '\n' << "    ";
//	for (int i = 0; i < 6; i++)
//	{
//		cout << mArray[i] << " ";
//	}
//	cout << "   " << mArray[6];
//	cout << "\n\n    1 2 3 4 5 6\n______________________\n";
//}

//alg_opt_new:
void print_playing_field(int* mArray)
{

	printf("\n______________________\n    6 5 4 3 2 1\n\n%d   %d %d %d %d %d %d \n    %d %d %d %d %d %d   %d\n\n    1 2 3 4 5 6\n______________________\n",
		mArray[13], mArray[12], mArray[11], mArray[10], mArray[9], mArray[8], mArray[7], mArray[0], mArray[1], mArray[2], mArray[3], mArray[4], mArray[5], mArray[6]);

}

//если конец игры - возращает ноль, иначе 1
bool check_end(int* mArray)
{
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < 6; i++)
	{
		sum1 += mArray[i];
	}

	for (int i = 7; i < 13; i++)
	{
		sum2 += mArray[i];
	}

	if (sum1 == 0 || sum2 == 0)
		return 0;
	else return 1;
}

void if_end(int* mArray)
{
	for (int i = 0; i < 6; i++)
	{
		mArray[6] += mArray[i];
		mArray[i] = 0;
	}

	for (int i = 7; i < 13; i++)
	{
		mArray[13] += mArray[i];
		mArray[i] = 0;
	}
}


int evaluation(int* field)
{
	int k = 0;
	//k = 3 * (field[6] - field[13]) + 300 + (field[0] + field[1] + field[2] + field[3] + field[4] + field[5]) - (field[12] + field[11] + field[10] + field[9] + field[8] + field[7]);
	__asm {
		mov         eax, 4
		imul        ecx, eax, 6
		mov         edx, 4
		imul        eax, edx, 0Dh
		mov         edx, dword ptr[field]
		mov         esi, dword ptr[field]
		mov         ecx, dword ptr[edx + ecx]
		sub         ecx, dword ptr[esi + eax]
		imul        edx, ecx, 3
		mov         eax, 4
		imul        ecx, eax, 0
		mov         eax, 4
		shl         eax, 0
		mov         esi, dword ptr[field]
		mov         ecx, dword ptr[esi + ecx]
		mov         esi, dword ptr[field]
		add         ecx, dword ptr[esi + eax]
		mov         eax, 4
		shl         eax, 1
		mov         esi, dword ptr[field]
		add         ecx, dword ptr[esi + eax]
		mov         eax, 4
		imul        eax, eax, 3
		mov         esi, dword ptr[field]
		add         ecx, dword ptr[esi + eax]
		mov         eax, 4
		shl         eax, 2
		mov         esi, dword ptr[field]
		add         ecx, dword ptr[esi + eax]
		mov         eax, 4
		imul        eax, eax, 5
		mov         esi, dword ptr[field]
		add         edx, dword ptr[esi + eax]
		lea         ecx, [ecx + edx + 12Ch]
		mov         edx, 4
		imul        eax, edx, 0Ch
		mov         edx, 4
		imul        edx, edx, 0Bh
		mov         esi, dword ptr[field]
		mov         eax, dword ptr[esi + eax]
		mov         esi, dword ptr[field]
		add         eax, dword ptr[esi + edx]
		mov         edx, 4
		imul        edx, edx, 0Ah
		mov         esi, dword ptr[field]
		add         eax, dword ptr[esi + edx]
		mov         edx, 4
		imul        edx, edx, 9
		mov         esi, dword ptr[field]
		add         eax, dword ptr[esi + edx]
		mov         edx, 4
		shl         edx, 3
		mov         esi, dword ptr[field]
		add         eax, dword ptr[esi + edx]
		mov         edx, 4
		imul        edx, edx, 7
		mov         esi, dword ptr[field]
		add         eax, dword ptr[esi + edx]
		sub         ecx, eax
		mov         dword ptr[k], ecx
	}
	return (k);
}


//*********************************************************************************************************************************************************
//*********************************************************************************************************************************************************
//*********************************************************************************************************************************************************
//*********************************************************BOT PLAY****************************************************************************************
//*********************************************************************************************************************************************************
//*********************************************************************************************************************************************************
//*********************************************************************************************************************************************************

struct game_status
{
	int field[14];
	bool player;
	int depth;
	int number_of_player_changes;

	game_status(int* f, bool p, int d, int n)
	{
		copyArray14(f, field);
		player = p;
		depth = d;
		number_of_player_changes = n;
	}
};

//bool move(int mArray[14], int number, bool player)
int max_my[6] = { -2147483646,-2147483646 ,-2147483646 ,-2147483646 ,-2147483646 ,-2147483646 };
int min_my = 2147483647;
int min_array[6] = { 2147483547, 2147483547, 2147483547, 2147483547, 2147483547, 2147483547 };
int min_field[6][14];
int best_i = 0;

int global_minimax = -1;

bool this_is_first_move = 1;

float best_move_2(game_status* main_game, int i, int first_move, bool level)
{
	if (main_game->number_of_player_changes == 2)
	{
		return 0;
	}


	int copy_field[14];
	bool check_change = 0;

	int final_depth, final_changes;//переменные для новой структуры
	//bool final_player = 0;

	//int final_changes_check_change = 0;

	/*for (int i = 0; i < 14; i=i+2)
	{
		copy_field[i] = main_game->field[i];
	}*/
	copy_field[0] = main_game->field[0];
	copy_field[1] = main_game->field[1];
	copy_field[2] = main_game->field[2];
	copy_field[3] = main_game->field[3];
	copy_field[4] = main_game->field[4];
	copy_field[5] = main_game->field[5];
	copy_field[6] = main_game->field[6];
	copy_field[7] = main_game->field[7];
	copy_field[8] = main_game->field[8];
	copy_field[9] = main_game->field[9];
	copy_field[10] = main_game->field[10];
	copy_field[11] = main_game->field[11];
	copy_field[12] = main_game->field[12];
	copy_field[13] = main_game->field[13];



	if (main_game->depth == 0)
	{
		while (copy_field[i] == 0)
		{
			i++;
		}
	}
	else
	{
		if (main_game->player)
		{
			while (copy_field[i] == 0 && i < 13)
			{
				i++;
			}
		}
		else
		{
			while (copy_field[i] == 0 && i < 6)
			{
				i++;
			}
		}
	}

	if (!main_game->player && main_game->depth == 0 && i > 5)
	{
		int mini_max = -2147483646;
		int tmp;
		for (int i = 0; i < 6; i++)
		{
			//cout << "\ni=" << i << "     " << "min= " << min_array[i] << "     " << "max[i]=" << max_my[i];
			if (min_array[i] != 0 && min_array[i] != 2147483647 && max_my[i] != -2147483646)
			{
				//tmp = max_my[i] * min_array[i];
				//new3
				tmp = max_my[i] - min_array[i];
				//printf("\nmax_my[%d] = %d;   min_array[%d] = %d;", i, max_my[i], i, min_array[i]);
				//cout << "   tmp = max / min == " << tmp;
				if (tmp > mini_max)
				{
					mini_max = tmp;
					global_minimax = mini_max;
					best_i = i;
				}
				//printf("\n\nmini_max_inside_1[%d] = %d\n", i, tmp);
			}
		}
		//printf("\n\n\n***************************************mini_max (1)***************************************\n\n\n");
		if (level)
		{
			//printf("\n LEVEL:\n mini_max = %d\n", global_minimax);
			return global_minimax;
		}
		else
			return best_i;
	}


	if (main_game->depth == 0)
	{
		first_move = i;
	}

	if (this_is_first_move && i == 0)
	{
		i++;
		first_move++;
		this_is_first_move = !this_is_first_move;


		if (main_game->player && i < 13)
			check_change = move(copy_field, i, main_game->player, 1);
		else if (!main_game->player && i < 6)
			check_change = move(copy_field, i, main_game->player, 1);


	}
	else
	{

		if (main_game->player && i < 13)
			check_change = move(copy_field, i, main_game->player, 1);
		else if (main_game->player && i > 12)
			return 0;
		else if (!main_game->player && i < 6)
			check_change = move(copy_field, i, main_game->player, 1);
		else if (!main_game->player && i > 5)
			return 0;
	}

	final_depth = main_game->depth + 1;

	if (check_change)
		final_changes = main_game->number_of_player_changes + 1;
	else
		final_changes = main_game->number_of_player_changes;

	if (check_change && final_changes == 1 && main_game->field[i] != 0)//максимум для первого хода
	{
		int  max_tmp = evaluation(copy_field);
		if (max_tmp > max_my[first_move])
		{
			max_my[first_move] = max_tmp;
		}
	}

	if (final_changes == 2)
	{
		int min_tmp = evaluation(copy_field);
		if (min_tmp < (min_array[first_move]) && main_game->field[i] != 0)
		{
			min_array[first_move] = min_tmp;

			//new3:
			if (!level)
				for (int k = 0; k < 14; k++)
					min_field[first_move][k] = copy_field[k];
		}

		if (check_change)
		{
			game_status* new_status = new game_status(copy_field, !main_game->player, final_depth, final_changes);
			if (!main_game->player)//если игрок верхний
			{
				best_move_2(new_status, 7, first_move, 0);//final_changes_check_change везде стоят ошибочно
			}
			else
			{
				best_move_2(new_status, 0, first_move, 0);
			}
		}
		else
		{
			game_status* new_status = new game_status(copy_field, main_game->player, final_depth, final_changes);
			if (main_game->player)//если игрок верхний
			{
				best_move_2(new_status, 7, first_move, 0);
			}
			else
			{
				best_move_2(new_status, 0, first_move, 0);
			}
		}
	}
	else
	{
		if (check_change)
		{
			game_status* new_status = new game_status(copy_field, !main_game->player, final_depth, final_changes);
			if (!main_game->player)//если игрок верхний
			{
				best_move_2(new_status, 7, first_move, 0);
			}
			else
			{
				best_move_2(new_status, 0, first_move, 0);
			}
		}
		else
		{
			game_status* new_status = new game_status(copy_field, main_game->player, final_depth, final_changes);
			if (main_game->player)//если игрок верхний
			{
				best_move_2(new_status, 7, first_move, 0);
			}
			else
			{
				best_move_2(new_status, 0, first_move, 0);
			}
		}
	}

	if (main_game->player && i < 12)
	{
		i++;
		best_move_2(main_game, i, first_move, 0);
	}
	else if (!main_game->player && i < 5)
	{
		i++;
		best_move_2(main_game, i, first_move, 0);
	}
	else if (!main_game->player && main_game->depth == 0 && i > 4)
	{//конец уже здесь
		int  mini_max = -2147483646;
		int  tmp;
		for (int i = 0; i < 6; i++)
		{
			if (min_array[i] != 0 && min_array[i] != 2147483647 && max_my[i] != -2147483646)
			{
				//tmp = max_my[i] * min_array[i];
				//new3
				tmp = max_my[i] - min_array[i];
				//printf("\nmax_my[%d] = %d;   min_array[%d] = %d;", i, max_my[i], i, min_array[i]);???
				if (tmp > mini_max)
				{
					mini_max = tmp;
					global_minimax = mini_max;
					best_i = i;
				}
				//printf("\n\nmini_max_inside_1[%d] = %d\n", i, tmp);
			}
		}

		//printf("\n\n\n***************************************mini_max (2)***************************************\n\n\n");
	}

	if (level)
	{
		//printf("\n LEVEL:\n mini_max = %d\n", global_minimax);
		return global_minimax;
	}
	else
		return best_i;
}

//new:
int global_inc = -1;
int fast_move()
{
	int sequence[] = { 1,2,1,3,4,6,6,4,3,5,6,2,4,5,6,1,3,3,1,2,6,3,5 };
	global_inc++;
	return sequence[global_inc];
}

int main()
{
	setlocale(LC_ALL, "rus");

	int main_array[14];
	bool player_number;

	int array[28] = { 4,1,2,5,4,4,5,6,3,1,2,5,3,5,1,6,3,2,4,3,4,1,2,4,3,5,4,6 };
	int k = 0;

	int doWhile1 = 0, doWhile2 = 0;
	do
	{
		//cout << "\n1. Новая игра\n2. Выход\n";
		printf("\n1. Новая игра\n2. Выход\n");
		//old:
		//cin >> doWhile2;
		//new: (for testing) 
		doWhile2 = 1;

		if (doWhile2 == 1)
		{
			do
			{
				//cout << "\n1. Играть 1х1\n2. Против компьютера\n";
				printf("\n1. Играть 1х1\n2. Против компьютера\n");
				//old:
				//cin >> doWhile1;
				scanf_s("%d", &doWhile1);
				//new:
				//doWhile1 = 2;
			} while (doWhile1 != 1 && doWhile1 != 2);

			switch (doWhile1)
			{
			case 1:
				ini_new_game(main_array);
				player_number = 0;
				print_playing_field(main_array);
				do
				{
					int n = 0;
					if (player_number)
						printf("\nХод верхнего игрока");
					//cout << "\nХод верхнего игрока";
					else
						printf("\nХод нижнего игрока");
					//cout << "\nХод нижнего игрока";

					if (player_number)
					{
						do
						{
							//cout << "\nВведите номер лунки (от 1 до 6):\n";
							printf("\nВведите номер лунки (от 1 до 6):\n");
							//cin >> n;
							scanf_s("%d", &n);
						} while (n > 6 || n < 1);
					}
					else
					{
						do
						{
							printf("\nВведите номер лунки (от 1 до 6):\n");
							//cin >> n;
							scanf_s("%d", &n);
						} while (n > 6 || n < 1);
					}

					if (move(main_array, n, player_number, 0))
						player_number = !player_number;
					print_playing_field(main_array);
				} while (check_end(main_array));

				if_end(main_array);
				print_playing_field(main_array);
				if (main_array[13] > main_array[6])
					printf("\n\nПОБЕДИЛ ВЕРХНИЙ ИГРОК!");
				//cout << "\nВведите номер лунки (от 1 до 6):\n";
				else if (main_array[13] < main_array[6])
					//cout << "\nВведите номер лунки (от 1 до 6):\n";
					printf("\n\nПОБЕДИЛ НИЖНИЙ ИГРОК!");
				else if (main_array[13] == main_array[6])
					printf("\n\nНИЧЬЯ");
				//cout << "\nВведите номер лунки (от 1 до 6):\n";

				break;
			case 2:

				player_number = 0;
				ini_new_game(main_array);
				print_playing_field(main_array);

				int copy_1[14];
				game_status* first;
				game_status* second;

				do
				{
					int n = 0;
					if (player_number)
						printf("\nХодите");
					//cout << "\nХодите";

					if (player_number)
					{
						do
						{
							//cout << "\nВведите номер лунки (от 1 до 6):\n";
							printf("\nВведите номер лунки (от 1 до 6):\n");
							n = array[k];
							k++;

						} while (n > 6 || n < 1);
					}
					else
					{
						copyArray14(main_array, copy_1);
						first = new game_status(copy_1, 0, 0, 0);
						printf("\nКОМП ПРОСЧИТЫВАЕТ\n");
						//cout << "\nКОМП ПРОСЧИТЫВАЕТ\n";
						n = best_move_2(first, 0, 0, 0);

						int MinMax[6] = { -2147483646, -2147483646, -2147483646, -2147483646, -2147483646, -2147483646 };

						global_minimax = -1;

						printf("\n\n\nbefore:\n");
						int copy_min_field[6][14];
						for (int i = 0; i < 6; i++)/*печать состояния всех шести окончательных после первого хода полей*/
						{

							for (int p = 0; p < 14; p = p + 2)
							{
								copy_min_field[i][p] = min_field[i][p];
								copy_min_field[i][p + 1] = min_field[i][p + 1];
							}
							//printf("\n\n");
						}

						//поиск трех лучших ходов для отсечения
						int new_MINIMAX[6], tmp = -2147483646, best_number_1 = -1, best_number_2 = -1;
						for (int i = 0; i < 6; i = i + 2)
						{
							new_MINIMAX[i] = max_my[i] - min_array[i];
							new_MINIMAX[i + 1] = max_my[i + 1] - min_array[i + 1];
						}
						for (int i = 0; i < 6; i++)
						{
							if (new_MINIMAX[i] > tmp)
							{
								best_number_1 = i;
								tmp = new_MINIMAX[i];
							}
						}
						tmp = -2147483646;
						for (int i = 0; i < 6; i++)
						{
							if (new_MINIMAX[i] > tmp && i != best_number_1)
							{
								best_number_2 = i;
								tmp = new_MINIMAX[i];
							}
						}
						printf("\nbest_number_1 = %d;  best_number_2 = %d", best_number_1, best_number_2);

						for (int k = 0; k < 6; k++)
						{
							for (int j = 0; j < 6; j++)
							{
								max_my[0] = -2147483646;
								min_array[0] = 2147483547;
								max_my[1] = -2147483646;
								min_array[1] = 2147483547;
								max_my[2] = -2147483646;
								min_array[2] = 2147483547;
								max_my[3] = -2147483646;
								min_array[3] = 2147483547;
								max_my[4] = -2147483646;
								min_array[4] = 2147483547;
								max_my[5] = -2147483646;
								min_array[5] = 2147483547;


							}
							global_minimax = -1;
							min_my = 2147483647;
							best_i = 0;


							if (check_end(copy_min_field[k]) && (k == best_number_1 || k == best_number_2))//теперь и без копии массива будет работать
							{
								second = new game_status(copy_min_field[k], 0, 0, 0);
								//printf("\n++++++++++++++++++++++\n++++++++++++++++++++++>>>>>>>>\nSECOND LEVEL: i = %d\n", k);
								//print_playing_field(copy_min_field[k]);
								MinMax[k] = best_move_2(second, 0, 0, 1);
								//printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\nMinMax[%d] = %d\n\n", k, MinMax[k]);???
								//printf("\n++++++++++++++++++++++\n++++++++++++++++++++++<<<<<<<<\n\nMinMax[%d] = %d\n", k, MinMax[k]);
								delete second;
							}
						}

						for (int i = 0; i < 6; i++)
						{
							for (int j = 0; j < 14; j++)
							{
								copy_min_field[i][j] = 0;
								min_field[i][j] = 0;
							}
						}

						int new_tmp = -2147483646;
						int count = -1;
						for (int i = 0; i < 6; i++)
						{
							if (MinMax[i] > new_tmp)
							{
								count = i;
								new_tmp = MinMax[i];
								//new3
								n = count;
							}

							//printf("\nmin_max_END[%d] = %d", i, MinMax[i]);???
						}

						n++;

						delete first;

						for (int i = 0; i < 6; i++)
						{
							MinMax[i] = -2147483646;
							max_my[i] = -2147483646;
							min_array[i] = 2147483547;
						}
						global_minimax = -1;
						min_my = 2147483647;
						best_i = 0;

						printf("\nРАСЧЁТ ОКОНЧЕН\n");
						//cout << "\nРАСЧЁТ ОКОНЧЕН\n";
					}

					if (!player_number)
					{
						//cout << "\nВыбран ход: " << n << "\nДО MOVE:" << endl;
						printf("\nВыбран ход: %d\nДО MOVE:\n", n);
						print_playing_field(main_array);
					}

					if (move(main_array, n, player_number, 0))
						player_number = !player_number;

					print_playing_field(main_array);
				} while ((main_array[12] != 0 || main_array[11] != 0 || main_array[10] != 0 || main_array[9] != 0 || main_array[8] != 0 || main_array[7] != 0) &&
					(main_array[0] != 0 || main_array[1] != 0 || main_array[2] != 0 || main_array[3] != 0 || main_array[4] != 0 || main_array[5] != 0));
				// old:
				// while (check_end(main_array));


				if_end(main_array);
				print_playing_field(main_array);

				break;
			}

		}
	} while (doWhile2 != 1 && doWhile2 != 2);
	return 0;
}