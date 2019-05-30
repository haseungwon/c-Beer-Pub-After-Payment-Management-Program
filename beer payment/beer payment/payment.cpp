#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

void fopen(fstream &f, String dir, char mode){
	if(mode=='w')		f.open(dir, ios:app);
	else if(mode=='r')	f.open(dir, ios::in);
	
	if(!f){
		cout << "Failed to load file" << endl;
		exit(1);
	}
}


int cnt = 0;
class Customer
{
private:

protected:
	time_t time_now;
	struct tm *Time;
	fstream f;
	int volume;
	char name[25];


public:
	
	void time_limit(tm *now)
	{
		fopen(f, "save_Data.txt", 'r');
		int hour, min, sec;
		int tmp;
		char tmpname[16];
		f >> tmpname>>tmp>>hour >> min >> sec;
		f.close();

		cout << hour << endl;
		tmp = now->tm_sec - sec;
		sec = tmp < 0 ? (tmp + 60) && (now->tm_min = now->tm_min - 1) : tmp;
		tmp = now->tm_min - min;
		min = tmp < 0 ? (tmp + 60) && (now->tm_hour = now->tm_hour - 1) : tmp;
		hour = now->tm_hour - hour;
		cout << hour << endl;

		if (hour >= 2)
		{
			printf("Time is Over!!");
		}

	}

	void record_time()
	{
		fopen(f, "save_Data.txt", "w");
		time_now = time(NULL);
		Time = localtime(&time_now);
		f << Time->tm_hour << " " << Time->tm_min << " " << Time->tm_sec << '\n';
		cout << Time->tm_hour << " " << Time->tm_min << " " << Time->tm_sec << '\n';
		f.close();

		time_limit(Time);
	}
	void record_beer()
	{
		fopen(f, "save_Data.txt", "w");
		cout << "Selected Beer: ";
		cin >> name;
		cout << "Volume: ";
		cin >> volume;
		f << name << " " << volume << " ";
		cnt++;
		f.close();
	}

};

class Cashier :private Customer
{
private:
	typedef struct cost_beer
	{
		char name[16];
		float won_per_cc;
	}Cost_beer;

	Cost_beer cost_list[14];

	int total_cost;

	void calculate_payment()
	{
		int i;
		int j;
		int cost;
		string tmp;
		for (i = 0; i < cnt; i++)
		{
			f.open("save_Data.txt", ios::in);
			f >> name >> volume;
			getline(f, tmp);
			f.close();
			for (j = 0; j < 14; j++)
			{
				if (strcmp(cost_list[j].name, name) == 0) //cost_list�� name�� �̻��ѹ��ڷ� �Ǿ����� �̰͸� �ذ��ϸ� ���ư��Ͱ���
				{
					cost = cost_list[j].won_per_cc*volume;
					f.open("final_bill.txt", ios::out);
					if (!f)
					{
						cout << "Input file opening failed";
						exit(1);
					}
					f << name << cost;
					total_cost += cost;
					f.close();
				}
			}
		}
	}

public:
	Cashier() {
		total_cost = 0;
	}
	void open_cost_list()
	{
		char name[16];
		float c;
		int i;
		f.open("cost_list.txt", ios::app);
		if (!f)
		{
			cout << "Input file opening failed"; //�� ���� �ȿ����� �������� �����
			exit(1);
		}
		for (i = 0; i < 14; i++)
		{
			f >> name >> c;
			strcpy(cost_list[i].name, name);
			cost_list[i].won_per_cc = c;
		}
		f.close();
	}

	void show_data()
	{
		string line;
		openfile_to_read();
		while (!f.eof())
		{
			getline(f, line);
			cout << line << endl;
			cnt++;
		}
	}
	void show_payment()
	{
		calculate_payment();
		f.open("final_bill.txt", ios::in);
		if (f.eof()) {
			cout << "Input file opening failed";
			exit(1);
		}
		while (!f.eof())
		{
			char name[16];
			int cost;
			f >> name >> cost;
			cout << name << ": " << cost << endl;
		}
		cout << "Total Sum: " << total_cost << endl;
	}

};


int main()
{
	Customer c;
	Cashier ch;
	c.record_beer();
	c.record_time();
	int a, b, q;
	char name[25];
	int volume;
	ifstream f("save_Data.txt");
	f >> name >> volume >> a >> b >> q;
	cout << name << volume << a << b << q << endl;
	ch.show_payment();
	ch.open_cost_list();
	ch.show_data();
	return 0;
}