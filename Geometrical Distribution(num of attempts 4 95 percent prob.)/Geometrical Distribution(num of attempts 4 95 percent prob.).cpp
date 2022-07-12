// Geometrical Distribution(num of attempts 4 95 percent prob.).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
using namespace std;

//преобразование цифры в строку
double strToDouble(string number)
{
	double returnValue = 0.;
	int digit = 0;
	int dotPos = 0;
	//1. найти точку
	for (int i = 0; i < number.size(); i++)
	{
		if (number[i] == '.')
		{
			dotPos = i;
			break;
		}
	}
	//2. влево - целая часть - pow(10,i)
	for (int i = 0; i < dotPos; i++)
	{
		switch (number[dotPos - i - 1])
		{
		case '0': digit = 0; break;
		case '1': digit = 1; break;
		case '2': digit = 2; break;
		case '3': digit = 3; break;
		case '4': digit = 4; break;
		case '5': digit = 5; break;
		case '6': digit = 6; break;
		case '7': digit = 7; break;
		case '8': digit = 8; break;
		case '9': digit = 9; break;
		}
		returnValue = returnValue + pow(10, i) * digit;
	}
	//3. вправо - дробная - pow(10,-i)
	for (int i = 0; i < number.size() - dotPos - 1; i++)
	{
		switch (number[dotPos + i + 1])
		{
		case '0': digit = 0; break;
		case '1': digit = 1; break;
		case '2': digit = 2; break;
		case '3': digit = 3; break;
		case '4': digit = 4; break;
		case '5': digit = 5; break;
		case '6': digit = 6; break;
		case '7': digit = 7; break;
		case '8': digit = 8; break;
		case '9': digit = 9; break;
		}
		returnValue = returnValue + pow(10, (-i-1)) * digit;
	}
	return returnValue;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Программа поиска числа попыток с заданной вероятностью при точности в 95%.\n";
	cout << "Версия: 1.0.\n";
	cout << "Разработал: Rizzak\n\n";
	srand(time(NULL));
	ifstream probabilitiesFile;
	ofstream attemptsFile;
	string fileName;
	char inputBuffer[100];
	string inputBufferString;
	cout << "Введите название файла(например, graphs.txt) в папке с exe с исходными данными: ";
	cin >> fileName;
	probabilitiesFile.open(fileName);
	attemptsFile.open("number of attempts.txt");
	while (!probabilitiesFile.is_open())
	{
		cout << "Ошибка 2. Введен неверный путь к файлу. Повторите ввод.";
		cin >> fileName;
		probabilitiesFile.open(fileName);
	}
	double chance = 0.;
	//chance(x)=p*pow(q,x) - шанс x неудач до первого успеха
	int x = 0;
	double p(0.), q(0.);
	while (!probabilitiesFile.eof())
	{
		probabilitiesFile.getline(inputBuffer, 100);
		inputBufferString = inputBuffer;
		p = strToDouble(inputBufferString);
		q = 1. - p;
		while (chance < 0.95)
		{
			chance = chance + (p * pow(q, x));//накопительный показатель - общий шанс получения ХОТЯ БЫ 1 успеха за x+1 попытку.
			x++;
		}
		attemptsFile << setprecision(4) << p << " " << x << "\n";
		x = 0;
		chance = 0.;
	}
	attemptsFile.close();
	probabilitiesFile.close();
	cout << "\nЧисло попыток найдено и записано в файл number of attempts.txt.\n";
	return 1;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
