#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <fstream>

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
	int cnt = 0;

public:
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
	void record_time()
	{
		time_now = time(NULL);
		Time = localtime(&time_now);
		f << Time->tm_hour << " " << Time->tm_min << " " << Time->tm_sec << '\n';
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
	void time_limit()
	{
		int hr1, min1, sec1;
		int hr2, min2, sec2;
		openfile_to_read();



	}

};

int main()
{
	Customer c;
	c.openfile_to_write();
	c.record_beer();
	c.record_time();
	int a, b, q;
	char name[25];
	int volume;
	ifstream f("save_Data.txt");
	f >> name >> volume >> a >> b >> q;

	cout << name << volume << a << b << q << endl;


	return 0;
}
class Cashier :protected Customer
{
public:
	void get_data(Customer, Cashier);
	void show_data();
	void show_payment();
};