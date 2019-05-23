#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

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
	int cnt = 0;

	void openfile_to_write()
	{
		f.open("save_Data.txt", ios::app);
		if (!f)
		{
			cout << "Input file opening failed";
			exit(1);
		}
	}
	void openfile_to_read()
	{
		f.open("save_Data.txt", ios::in);
		if (!f)
		{
			cout << "File does not open!!";
			exit(1);
		}
	}
	void time_limit(tm *now)
	{
		int hr1, min1, sec1;
		int tmp;
		f >> hr1 >> min1 >> sec1;
		tmp = now->tm_sec - sec1;
		sec1 = tmp < 0 ? (tmp + 60) &&(now->tm_min=now->tm_min-1): tmp;
		tmp = now->tm_min - min1;
		min1 = tmp < 0 ? (tmp + 60) && (now->tm_hour = now->tm_hour - 1) : tmp;
		hr1 = now->tm_hour - hr1;
		if (hr1 >= 2)
		{
			printf("Time is Over!!");
		}

	}
	void record_time()
	{
		
		time_now = time(NULL);
		Time = localtime(&time_now);
		f << Time->tm_hour << " " << Time->tm_min << " " << Time->tm_sec << '\n';
		time_limit(Time);
		cout << Time->tm_hour << " " << Time->tm_min << " " << Time->tm_sec << '\n';

		f.close();
	}
	void record_beer()
	{
		cout << "Selected Beer: ";
		cin >> name;
		cout << "Volume: ";
		cin >> volume;
		f << name << " " << volume << " ";
		cnt++;
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


public:
	void open_cost_list()
	{
		char name[16];
		float c;
		int i;
		f.open("cost_list.txt",ios::in);
		if (!f)
		{
			cout << "Input file opening failed";
			exit(1);
		}
		for ( i=0;i < 14;i++)
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

	}

};


int main()
{
	Customer c;
	Cashier ch;
/*	c.openfile_to_write();
	c.record_beer();
	c.record_time();
	int a, b, q;
	char name[25];
	int volume;
	ifstream f("save_Data.txt");
	f >> name >> volume >> a >> b >> q;
	cout << name << volume << a << b << q << endl;*/
	ch.open_cost_list();
	ch.show_data();
	k
	return 0;;
}
