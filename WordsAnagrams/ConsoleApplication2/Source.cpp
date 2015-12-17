//���������� ���������� � ��������� ����������� ���������� ����� Lucida Console, ��� ����� ����� ������ ����������
//�� ���������� ���� ������� ������ ������� ����, � ���������� ���� �������� �������� � ���������� ��������� �����, 
//� ��������� ������ ��������� ����� ����������� ���������� ���������. 

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
	VecStr(string str)                       //����������� � ����������
	{
		string * newstr = new string;
		F.push_back(*newstr);
		F[F.size() - 1] = str;
	}

	void Add(string str)                    //���������� ������ �������� � ������� ������ F
	{
		string * newStr = new string;
		F.push_back(*newStr);
		F[F.size() - 1] = str;
	}
	~VecStr()                              //����������
	{
		F.clear();                         //������� ������� F
	}

	friend ostream& operator<<(ostream& os, const VecStr & M);  // ���������� ��������� << ��� �������, ��� ������ � ����
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

string in_str = "";							  //���������� ��� �������� ������, ��������� �� �����
string tempForIn = "";					      //������ ��� �������� ���������������� �����
multimap <string, VecStr> Mul;				  //���������� ���������� multimap ��� �������� ����, ��������������� �� �����





bool VerificationFile(const ifstream &in)
{
	if (!in.is_open())
	{
		cout << "���� ������� �� ������. ����������, ��������� ���� � ������� � ������� ��������." << endl;
		return false;
	}

	else
	{
		cout << "����� ������ 20 ������ ��� ������� ������� 1 Mb. ���� ����������..." << endl;
		return true;
	}
		
	
}
void SetData(ifstream &in)
{
	getline(in, in_str);						   //��������� ������ �� �����
	tempForIn = in_str;					           //������ ��� �������� ���������������� �����
	sort(tempForIn.begin(), tempForIn.end());	   //����������, ���������� �� ����� ������, �� ���� ��������� �����
}
void PrintToFile()
{
	ofstream out("result_file.txt", ios_base::out);                //������� ������������� �����
	out.close();
	ios_base::app;                                                 //���� ����������� � ������ ������ "� ����� �����"
	for (auto it = Mul.begin(); it != Mul.end(); ++it)             //downloading ����������� � �������� ����
	{
		if (it->second.F.size() > 1)                               //���� ���������� �����-���������, �� 
			out << it->second;									   //����������� ������ ��� ������
	}
	out.close();

	system("cls");
	cout << "������ ��������� ���������. ������ ��������� � ���� result_file.txt" << endl;
	cout << "���� ��������� � �������� � ������� ��������. " << endl;

}

int main()
{
	SetConsoleCP(1251);							//��������� ������� �������� win-cp 1251 � ����� ����� 
	SetConsoleOutputCP(1251);					//��������� ������� �������� win-cp 1251 � ����� ������

	ifstream in("dic1.txt");					//������� ������ ���� ifstream � ��������� ��� � ������ � �������� �����
	
	
	if (!VerificationFile(in))
	{
		system("pause");
		return 0;
	}
	else
	{
		SetData(in);                              //��������� ������, ��������, ���������
		VecStr *p = new VecStr(in_str);
		Mul.insert(pair <string, VecStr>(tempForIn, *p));
		bool tumb = false;
		while (!in.eof())								//��������� ����
		{
			SetData(in);                                //��������� ������, ��������, ���������   

			auto it = Mul.find(tempForIn);              // Mul.find ���������� ��������� �� ������ ������� ��� �� Mul.end(), ���� ������� �� ������
			if (it != Mul.end())                        //���� ������� ������, �� ���� Mul.find ������ �� Mul.end()...
			{
				it->second.Add(in_str);                 //��������� ������ � ������ �������� ��� ��� ������������� �����
			}
			else if (it == Mul.end())                    //���� ������� �� ������, �� ���� Mul.find(...) ������ Mul.end()...
			{
				VecStr *p = new VecStr(in_str);                     //������� ��������� �� ������ ������ VecStr
				Mul.insert(pair <string, VecStr>(tempForIn, *p));   //��������� � ��������� Mul ����: ���� + ������ �� �����
			}
		}
		PrintToFile();                                  //������ ������ � ���� result_file.txt
	}
	system("pause");
	return 1;
}
