#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

typedef struct cost_beer
{
	char name[16];
	float won_per_cc;
}Cost_beer;

Cost_beer cost_list[14];

void f_open(fstream &f, string dir, char mode){
	if(mode=='w')		f.open(dir, ios::app);
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
	int volume, menu;
	char name[25];
	

public:
	
	void time_limit(tm *now)
	{
		f_open(f, "save_Data.txt", 'r');
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
		f_open(f, "save_Data.txt", 'w');
		time_now = time(NULL);
		Time = localtime(&time_now);
		f << Time->tm_hour << " " << Time->tm_min << " " << Time->tm_sec << '\n';
		cout << Time->tm_hour << " " << Time->tm_min << " " << Time->tm_sec << '\n';
		f.close();

		time_limit(Time);
	}
	void record_beer()
	{
		f_open(f, "save_Data.txt", 'w');
		cout << "Select Beer: ";
		cin >> menu;
		menu--;
		cout << "Volume: ";
		cin >> volume;
		f << cost_list[menu].name << " " << volume << " ";
		cnt++;
		f.close();
	}
};

class Cashier :private Customer
{
private:

	int total_cost;

	void calculate_payment()
	{
		int i, j, cost;
		string tmp;
		for (i = 0; i < cnt; i++)
		{
			f_open(f, "save_Data.txt", 'r');
			f >> name >> volume;
			getline(f, tmp);
			f.close();

			for (j = 0; j < 14; j++)
			{
				if (strcmp(cost_list[j].name, name) == 0)
				{
					cost = (int)round(cost_list[j].won_per_cc*volume);
					
					f_open(f, "final_bill.txt", 'w');
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
	void load_cost_list()
	{
		char name[16];
		float cost;
		int i;

		f_open(f, "cost_list.txt", 'r');
		for (i = 0; i < 14; i++)
		{
			f >> name >> cost;
			strcpy(cost_list[i].name, name);
			cost_list[i].won_per_cc = cost;
		}
		f.close();
	}

	void show_cost_list() {
		cout << "welcome to sejong beer pub!" << endl;
		cout << "num\tmenu\t\tprice" << endl;
		for (int i = 0; i < 14; i++) {
			cout << i+1 << "\t";			
			cout.flags(ios::left);
			cout.width(16);
			cout << cost_list[i].name;
			cout.width(2);
			cout << cost_list[i].won_per_cc << endl;
		}
	}

	void show_save_data()
	{
		f_open(f, "save_Data.txt", 'r');

		string line;
		while (!f.eof())
		{
			getline(f, line);
			cout << line << endl;
			cnt++;
		}

		f.close();
	}
	void show_payment()
	{
		calculate_payment();
		f_open(f, "final_bill.txt", 'r');
		while (!f.eof())
		{
			char name[16];
			int cost;
			f >> name >> cost;
			cout << name << ": " << cost << endl;
		}
		cout << "Total Sum: " << total_cost << endl;
		f.close();
	}

};

int main()
{
	int hour, min, sec;
	char name[25];
	int volume;
	ifstream f("save_Data.txt");

	Customer customer;
	Cashier cashier;

	cashier.load_cost_list();
	cashier.show_cost_list();

	customer.record_beer();
	customer.record_time();
	
	f >> name >> volume >> hour >> min >> sec;
	cout << name << volume << hour << min << sec << endl;

	cashier.show_payment();
	cashier.show_save_data();
	return 0;
}