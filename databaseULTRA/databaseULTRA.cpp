// databaseULTRA.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


//можно еще сделать нумераци=поправит получение Названия
//можно сделать при ввода книгу проверку есть ли уже такая книга и если есть-> перезаписать
//можно поиск по книге в наличии

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>

#include <stdio.h>

struct Book // СТРУКТУРА хранящая данные о каждой записи в БД
{
	std::string name; // название книги
	std::string author; // автор книги
	std::string year; //год издания
	int can_take; //есть ли в наличии
};

std::vector <Book> book; // вектор структур

std::vector <std::string> lines; // вектор строк для считывания из файла

int flag = 0; //показывает были ли уже считаны данные из БД


void to_vector() // функция считывания из файла
{
	std::string line;

	flag = 1;
	
	std::ifstream in("database.txt");
	
	if (in.is_open())
	{
		while (getline(in, line)) 
		{
			
			lines.push_back(line); // считывание и добавление в вектор строк

		}
	}
	
	in.close();

	for (auto now : lines) // разбиение строки на элементы
	{
		Book enter;
		int n1 = 1;
		int n2 = now.find("\"  ", n1 + 1);

		for (n1; n1 < n2; n1++)
		{
			enter.name += now[n1]; //получаем название книги

		}

		n1 = n2 + 6;

		n2 = now.find(" | ", n1 + 1);

		for (n1; n1 < n2-1; n1++)
		{
			enter.author += now[n1]; // получаем автора книги

		}
		
		n1 = n2 + 4;
		
		n2 = now.find(" | ", n1 + 1);
		
		for (n1; n1 < n2; n1++)
		{
			enter.year += now[n1]; //дата издания

		}
		
		if (now.find("Есть") != -1) enter.can_take = 1; //есть в наличии
		
		else enter.can_take = 0; // нет в наличии
		
		book.push_back(enter); 


	}
}

void file_txt(); //фуекция записи в файл


void Show() //вывод инфо из бд
{
	if (flag == 0)
	{
		to_vector();
	}

	for (auto temp : book)
	{
		
		std::cout<<"\""<< temp.name<< "\"  |  " << temp.author << "  |  " << temp.year << "  |  ";
		
		if (temp.can_take) std::cout << "Есть в наличии;" << std::endl;
		else std::cout << "Нет в аличии;" << std::endl;
	}
	

}

int Quantity() //количество записей в бд
{
	if (flag == 0) to_vector();
	
	int i = 0;
	
	for (auto temp : lines)
		i++;
	
	return i;
}

void Get_on_number();
void Get_on_name();
void Get_on_author();


void Get()
{
	if (flag == 0) to_vector();
	
	std::cout << "Выберите по какому параметру вы хотите осуществить поиск:"<<std::endl << std::endl;
	
	int choise;

	std::cout << "1 - найти запись по номеру" << std::endl << std::endl;
	std::cout << "2 - найти запись по названию книги" << std::endl << std::endl;
	std::cout << "3 - найти все  книги автора" << std::endl << std::endl;

	std::cin >> choise;

	if (choise == 1) Get_on_number(); // поиск по номеру
	else if (choise == 2) Get_on_name() ;// поиск по названиюназвание функции которой еще нет 
		else if (choise == 3) Get_on_author();//поиск книг автора
			else std::cout << "Ошибка ввода данных." << std::endl << std::endl;
}

void Get_on_number()
{
	int a;

	std::cout << "Какую запись по номеру Вы хотите получить ? " << std::endl << std::endl;

	std::cin >> a;
	
	if (a > Quantity()) std::cout << "Неверно введенное значение" << std::endl;

	else
	{
		std::cout << "\"" << book[a - 1].name << "\"  |  " << book[a - 1].author << "  |  " << book[a - 1].year << "  |  ";
		if (book[a - 1].can_take) std::cout << "Есть в наличии;" << std::endl << std::endl;
		else std::cout << "Нет в аличии;" << std::endl << std::endl;
	}

}

void Get_on_name()
{
	std::cout << "Введите название произведения, информацию о котором хотите найти: " << std::endl << std::endl;
	
	std::string str;
	std::cin.ignore();
	std::getline(std::cin, str);
	
	int is_here = 0;
	for (auto now : book)
	{
		if (str == now.name)
		{
			std::cout << "\"" << now.name << "\"  |  " << now.author << "  |  " << now.year << "  |  ";
			
			if (now.can_take) std::cout << "Есть в наличии;" << std::endl << std::endl;
			else std::cout << "Нет в аличии;" << std::endl << std::endl;

			is_here = 1;
		}
		
	}

	if(is_here ==0)  std::cout << "Запрашиваемая книга не найдена." << std::endl << std::endl;
}

void Get_on_author()
{
	std::cout << "Введите автора, чьи произведения Вас интересуют: " << std::endl << std::endl;


	std::string str;
	std::cin.ignore();
	std::getline(std::cin, str);

	std::cout << std::endl;

	int is_here = 0;
	for (auto now : book)
	{
		//std::cout << "1" << now.author << "1" << std::endl;
		if (str == now.author)
		{
			
			std::cout << "\"" << now.name << "\"  |  " << now.author << "  |  " << now.year << "  |  ";

			if (now.can_take) std::cout << "Есть в наличии;" << std::endl << std::endl;
			else std::cout << "Нет в аличии;" << std::endl << std::endl;

			is_here = 1;
		}

	}

	if (is_here == 0)  std::cout << "Книги данного автора отсутствуют." << std::endl << std::endl;
}

void Delete() // удалить заись
{
	if (flag == 0) to_vector();
	
	int num;
	
	std::cout << "Какую запись по номеру Вы хотите удалить ? " << std::endl << std::endl;
	
	std::cin >> num;
	
	if (num > Quantity()) std::cout << "Неверно введенное значение" << std::endl;
	
	else
	{
		book.erase(book.begin() + (num-1));
		std::cout << "Запись удалена." << std::endl << std::endl;
	}
	
	file_txt();
	
}

void Delete_on_name() // удалить запись по названию книги
{
	if (flag == 0) to_vector();

	std::string to_delete;

	int i = -1, in_base = 0;

	std::cout << "Какую запись с какой книгой Вы хотите удалить ? Введите название книги. " << std::endl << std::endl;

	std::cin.ignore();

	std::getline(std::cin, to_delete);
	//std::cin >> to_delete;Е
}

int inbase( std::string check)//проверка , есть ли уже запись в БД
{
	int in_base = 0;

	for (auto now : book)
	{
		if (now.name.find(check) != -1)
			in_base = 1;
	}
	return in_base;
}

void Add()
{
	if (flag == 0) to_vector();

	std::cout << "Введите значени записи. и 1, если книга есть в наличии, 0, если нет " << std::endl;
		
	Book enter;
	//std::cin.clear();
	std::cout << "Название книги : ";
	
	std::cin.ignore();
	std::getline(std::cin, enter.name);
	int check = inbase(enter.name);

	if (check == 1)
	{
		int wish;
		
		std::cout << "Данная книга уже есть в базе данных. Хотите ввести данные о другой книге? 1 - да, 0 - нет" << std::endl << std::endl;
		
		std::cin >> wish;

		if (wish == 1 ) Add();
		

	}
	else
	{
		std::cout << std::endl << "Автор : ";
	
		std::cin >> enter.author;

		std::cout << std::endl << "Год издания : ";
		std::cin >> enter.year;
	
		std::cout << std::endl << " Есть ли книга в наличии? 1 - есть, 0 - нет :  ";
		std::cin>> enter.can_take;
	
		std::cout << std::endl;

		if (enter.can_take == 1 || enter.can_take == 0)
			{
				book.push_back(enter); //добавление введенных элементов в вектор
				file_txt();
			}
		else std::cout << std::endl << " Неверно введенное значение. (1/0)";

	}
	
	

}

void file_txt()//запись в файл
{
	if (flag == 0) to_vector();
	int i = 0;

	std::ofstream out("database.txt"); 
	
	for (auto temp : book)
	{
		out <<"\"" << temp.name << "\"  |  " << temp.author << "  |  " << temp.year << "  |  ";
		
		if (temp.can_take) out << "Есть в наличии;" << std::endl;
		
		else out << "Нет в аличии;" << std::endl;
	}

	out.close();
}



int main()
{
	setlocale(LC_ALL, "Russian");
	
	system("chcp 1251>nul");

	std::string wish;//для выбора функциии
	
	int cont = 1; //продолжить?

	
		while (cont)
	{
		system("CLS");

		std::cout << "Выберите, что Вы хотите сделать: " << std::endl;
		
		std::cout << std::endl << "show - посмотреть все записи " << std::endl << std::endl << "quantity - узнать кол-во записей" << std::endl;
		std::cout << std::endl << "get - получит запись " << std::endl << std::endl << "delete - удалить запись по названию книги" << std::endl << std::endl;
		std::cout<< "add - добавить запись" << std::endl << std::endl;
		
		std::cin >> wish;
		
		if (wish == "show") Show();
		
		if (wish == "quantity") 
		{
			int size = Quantity();
			std::cout << "Количество записей в базе данных равно " << size<< std::endl;
		}
		
		if (wish == "get") Get();
		
		if (wish == "delete") Delete_on_name();
		
		if (wish == "add") Add();
		
		std::cout << "Желаете продолжить? Введите 1, если да; 0, если нет" << std::endl;
		
		std::cin.ignore();
		
		std::cin >> cont;

		if (cont != 1 && cont != 0)
		{
			std::cout << "Введенное значение некорректно" << std::endl;
			//break;
		}
	}

}
