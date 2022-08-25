#include<iostream>
#include<assert.h>
#include<time.h>
using namespace std;
#include"RBTree.h"
int main()
{
	//srand(0);
	RBTree<int, int> rb;
	int n = 100;
	for (int i = 0; i < n; ++i)
	{
		rb.Insert(make_pair(i, i));
	}
	//rb.InOrder();
	rb.IsBalance();
	return 0;
}