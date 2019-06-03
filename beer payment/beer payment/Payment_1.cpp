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



void f_open(fstream &f, string dir, char mode) {
	if (mode == 'w')		f.open(dir, ios::app);
	else if (mode == 'r')	f.open(dir, ios::in);

	if (!f) {
		cout << "Failed to load file" << endl;
		exit(1);
	}
}

int cnt = 0;	//number of order

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
	int Countinue = 1;
	void time_limit(tm *now)
	{
		f_open(f, "save_Data.txt", 'r');
		int hour, min, sec;
		int tmp;
		char tmpname[16];
		f >> tmpname >> tmp >> hour >> min >> sec;
		f.close();

		tmp = now->tm_sec - sec;
		sec = tmp < 0 ? (tmp + 60) && (now->tm_min = now->tm_min - 1) : tmp;
		tmp = now->tm_min - min;
		min = tmp < 0 ? (tmp + 60) && (now->tm_hour = now->tm_hour - 1) : tmp;
		hour = now->tm_hour - hour;

		if (hour >= 2)
		{
			printf("Time is Over!!");
			Countinue = 0;
		}

	}

	void record_time()
	{
		f_open(f, "save_Data.txt", 'w');
		time_now = time(NULL);
		Time = localtime(&time_now);
		f << Time->tm_hour << " " << Time->tm_min << " " << Time->tm_sec << '\n';
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

		f.close();

	}
};

class Cashier :private Customer
{


private:


	int total_cost;
	int num;
	void calculate_payment()
	{
		int i, j, cost;

		char name_tmp[14];
		string tmp;
		Cost_beer *calculated_list = new Cost_beer[cnt];
		Cost_beer remove_overlap[14];
		f_open(f, "save_Data.txt", 'r');
		for (i = 0; i < cnt; i++)
		{
			f >> name >> volume;
			getline(f, tmp);
			for (j = 0; j < 14; j++)
			{
				if (strcmp(cost_list[j].name, name) == 0)
				{
					cost = (cost_list[j].won_per_cc*volume);
					strcpy(calculated_list[i].name, name);
					calculated_list[i].won_per_cc = cost;
					total_cost += cost;

				}
			}

		}
		f.close();
		remove_overlap[num].won_per_cc = calculated_list[0].won_per_cc;			//중복 제거
		strcpy(remove_overlap[num].name, calculated_list[0].name);
		for (i = 1; i < cnt; i++)
		{
			for (j = 0; j <= num; j++)
			{
				if (strcmp(calculated_list[i].name, remove_overlap[j].name) == 0)
				{
					remove_overlap[j].won_per_cc += calculated_list[i].won_per_cc;
					break;
				}
				else
					continue;

			}
			if (j == num + 1)
			{
				strcpy(remove_overlap[j].name, calculated_list[i].name);
				remove_overlap[j].won_per_cc = calculated_list[i].won_per_cc;
				num++;
			}
		}
		for (i = 0; i <= num; i++)						//사전순
		{
			for (j = 0; j <= num; j++)
			{
				if (strcmp(remove_overlap[j].name, remove_overlap[j + 1].name) > 0)
				{
					strcpy(name_tmp, remove_overlap[j].name);
					strcpy(remove_overlap[j].name, remove_overlap[j + 1].name);
					strcpy(remove_overlap[j + 1].name, name_tmp);

				}
			}
		}

		f_open(f, "final_bill.txt", 'w');			//저장

		for (i = 0; i <= num; i++)
		{

			f << remove_overlap[i].name << " " << remove_overlap[i].won_per_cc << "\n";

		}
		free(calculated_list);
		f.close();
	}

public:
	Cashier() {
		total_cost = 0;
		num = 0;
	}
	void load_cost_list(Cost_beer tmp[])
	{
		char name[16];
		float cost;
		int i;

		f_open(f, "cost_list.txt", 'r');
		for (i = 0; i < 14; i++)
		{
			f >> name >> cost;
			strcpy(tmp[i].name, name);
			tmp[i].won_per_cc = cost;
		}
		f.close();
	}

	void show_cost_list(Cost_beer tmp[]) {
		cout << "welcome to sejong beer pub!" << endl;
		cout << "num\tmenu\t\tprice" << endl;
		for (int i = 0; i < 14; i++) {
			cout << i + 1 << "\t";
			cout.flags(ios::left);
			cout.width(16);
			cout << tmp[i].name;
			cout.width(2);
			cout << tmp[i].won_per_cc << endl;
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
		cnt--;
		f.close();
	}
	void show_payment()

	{

		calculate_payment();
		f_open(f, "final_bill.txt", 'r');
		cout << "---------Final Bill List-------" << endl;
		for (int i = 0; i <= num; i++)
		{
			char name[16];
			int cost;
			f >> name >> cost;
			cout << name << ":" << cost << endl;
		}
		f.close();
		cout << "Total Sum: " << total_cost << endl;


	}
};

int main()
{
	int hour, min, sec;
	char name[25];
	int volume;
	ifstream f;

	Customer customer;
	Cashier cashier;

	while (customer.Countinue)
	{
		cashier.load_cost_list(cost_list);
		cashier.show_cost_list(cost_list);

		customer.record_beer();
		customer.record_time();
	}
	cashier.show_save_data();
	cashier.show_payment();


	return 0;
}