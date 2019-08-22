#include"Function.h"
#include<conio.h>

int main()
{
	srand(time(NULL));
	//========================================== KHAI BÁO CÁC BIẾN =======================================
	int* a = NULL;
	SORT_ALGORITHM<int>* pAlg;
	/*Random(a, 1000, minCompare);
	pAlg->Sort(a, 1000, minCompare);
	for (int i = 0; i < 1000; i++)
		std::cout << a[i] << " ";*/
	//======================================== BẮT ĐẦU CHƯƠNG TRÌNH ======================================
	//-------------- STATE SORTED
	stateSorted(a, pAlg, maxCompare);
	//-------------- STATE REVERSED
	stateReversed(a, pAlg, maxCompare);
	//-------------- STATE RANDOM
	stateRandom(a, pAlg, maxCompare);
	//-------------- STATE NEARLY SORTED
	stateNearlySorted(a, pAlg, maxCompare);
	//======================================== HỦY CÁC BIẾN CON TRỎ ======================================
	delete[] a;

	_getch();
	return 0;
}