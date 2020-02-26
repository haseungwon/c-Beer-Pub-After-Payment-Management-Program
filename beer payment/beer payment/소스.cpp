#include <iostream>
using namespace std;

int main() {

	int *ptr;
	ptr = new int (10);
	float *q;
	q = new float[2]{ 1, 2 };

	cout << *ptr << "\t" << *(q+1) << endl;

	delete ptr;
	delete[] q;

	return 0;
}