//Пожалуйста установите в свойствах консольного приложения шрифт Lucida Console, для этого после первой компиляции
//на консольном окне нажмите правую клавишу мыши, в выпадающем меню выберите свойства и установите требуемый шрифт, 
//в противном случае программа будет некорректно отображать кириллицу. 

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <map>
#include <fstream>

using namespace std;


class VecStr
{
public:
	vector <string> F;
	VecStr(string str)                       //конструктор с параметром
	{
		string * newstr = new string;
		F.push_back(*newstr);
		F[F.size() - 1] = str;
	}

	void Add(string str)                    //добавление нового элемента в текущий вектор F
	{
		string * newStr = new string;
		F.push_back(*newStr);
		F[F.size() - 1] = str;
	}
	~VecStr()                              //деструктор
	{
		F.clear();                         //очистка вектора F
	}

	friend ostream& operator<<(ostream& os, const VecStr & M);  // перегрузка оператора << для вектора, при печати в файл
};                               

ostream& operator<<(ostream& os, const VecStr & M)
{
	ofstream out("result_file.txt", ios_base::app);
	for (unsigned int i = 0; i < M.F.size(); i++)
	{
		out << M.F[i] << "  ";
	}
	out << endl;
	return os;
}

string in_str = "";							  //переменная для хранения строки, считанной из файла
string tempForIn = "";					      //строка для хранения отсортированного ключа
multimap <string, VecStr> Mul;				  //объявление контейнера multimap для хранения слов, отсортированных по ключу





bool VerificationFile(const ifstream &in)
{
	if (!in.is_open())
	{
		cout << "Файл словаря не найден. Пожалуйста, поместите файл в каталог с текущим проектом." << endl;
		return false;
	}

	else
	{
		cout << "Время работы 20 секунд для словаря объемом 1 Mb. Идет построение..." << endl;
		return true;
	}
		
	
}
void SetData(ifstream &in)
{
	getline(in, in_str);						   //считываем строку из файла
	tempForIn = in_str;					           //строка для хранения отсортированного ключа
	sort(tempForIn.begin(), tempForIn.end());	   //сортировка, полученной из файла строки, то есть получение ключа
}
void PrintToFile()
{
	ofstream out("result_file.txt", ios_base::out);                //очистка существующего файла
	out.close();
	ios_base::app;                                                 //файл открывается в режиме записи "в конец файла"
	for (auto it = Mul.begin(); it != Mul.end(); ++it)             //downloading результатов в конечный файл
	{
		if (it->second.F.size() > 1)                               //если существует слово-анаграмма, то 
			out << it->second;									   //выгружаются данные без ключей
	}
	out.close();

	system("cls");
	cout << "Работа программы завершена. Данные выгружены в файл result_file.txt" << endl;
	cout << "Файл находится в каталоге с текущим проектом. " << endl;

}

int main()
{
	SetConsoleCP(1251);							//установка кодовой страницы win-cp 1251 в поток ввода 
	SetConsoleOutputCP(1251);					//установка кодовой страницы win-cp 1251 в поток вывода

	ifstream in("dic1.txt");					//создаем объект типа ifstream и связываем его с файлом в корневой папке
	
	
	if (!VerificationFile(in))
	{
		system("pause");
		return 0;
	}
	else
	{
		SetData(in);                              //считываем строку, копируем, сортируем
		VecStr *p = new VecStr(in_str);
		Mul.insert(pair <string, VecStr>(tempForIn, *p));
		bool tumb = false;
		while (!in.eof())								//считываем файл
		{
			SetData(in);                                //считываем строку, копируем, сортируем   

			auto it = Mul.find(tempForIn);              // Mul.find возвращает указатель на данный элемент или на Mul.end(), если элемент НЕ найден
			if (it != Mul.end())                        //если элемент найден, то есть Mul.find вернул НЕ Mul.end()...
			{
				it->second.Add(in_str);                 //добавляем строку в вектор значений для уже существующего ключа
			}
			else if (it == Mul.end())                    //если элемент не найден, то есть Mul.find(...) вернул Mul.end()...
			{
				VecStr *p = new VecStr(in_str);                     //создаем указатель на объект класса VecStr
				Mul.insert(pair <string, VecStr>(tempForIn, *p));   //вставляем в контейнер Mul пару: ключ + вектор из строк
			}
		}
		PrintToFile();                                  //печать данных в файл result_file.txt
	}
	system("pause");
	return 1;
}
