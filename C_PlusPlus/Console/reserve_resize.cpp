#include "reserve_resize.h"

int test_Reserve_Resize_Main()
{
	vector<testReserve_Resize> vecTest;
	vecTest.reserve(100);
	cout << vecTest.capacity() << endl;
	cout << vecTest.size() << endl;

	for (int i = 0; i < 100; i++)
	{
		vecTest.push_back(testReserve_Resize(i));
	}
	cout << "capacity:" << vecTest.capacity() << endl;
	cout << "size:" << vecTest.size() << endl;

	vecTest.resize(102);
	vecTest[100] = 1;
	vecTest[101] = 2;
	cout << "capacity:" << vecTest.capacity() << endl;
	cout << "size:" << vecTest.size() << endl;

	for (int i = 0; i< vecTest.size();i ++)
	{
		cout << vecTest[i].m_a << endl;
	}

	return 0;
}