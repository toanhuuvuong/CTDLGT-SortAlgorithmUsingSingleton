#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include"SortAlgorithm.h"
#include<iostream>
#include<fstream>
#include<time.h>

#define INTEGER_MAX 32767

//======================================================= CÁC HÀM RANDOM =========================================================
void Sorted(int* &a, const int &n, bool(*Compare)(const int&, const int&))
{
	if (a)
		delete[] a;
	a = new int[n];
	if (Compare(1, 0))
	{
		a[0] = 0;
		for (int i = 1; i < n; i++)
			(a[i - 1] == INTEGER_MAX) ? a[i] = INTEGER_MAX : a[i] = a[i - 1] + rand() % 2;
	}
	else
	{
		a[0] = INTEGER_MAX;
		for (int i = 1; i < n; i++)
			(a[i - 1] == 0) ? a[i] = 0 : a[i] = a[i] = a[i - 1] - rand() % 2;
	}
}
void Reversed(int* &a, const int &n, bool(*Compare)(const int&, const int&))
{
	if (a)
		delete[] a;
	a = new int[n];
	if (Compare(1, 0))
	{
		a[0] = INTEGER_MAX;
		for (int i = 1; i < n; i++)
			(a[i - 1] == 0) ? a[i] = 0 : a[i] = a[i] = a[i - 1] - rand() % 2;
	}
	else
	{
		a[0] = 0;
		for (int i = 1; i < n; i++)
			(a[i - 1] == INTEGER_MAX) ? a[i] = INTEGER_MAX : a[i] = a[i - 1] + rand() % 2;
	}
}
void Random(int* &a, const int &n, bool(*Compare)(const int&, const int&))
{
	if (a)
		delete[] a;
	a = new int[n];
	for (int i = 0; i < n; i++)
		a[i] = 0 + rand() % (INTEGER_MAX + 1);
}
void NearlySorted(int* &a, const int &n, bool(*Compare)(const int&, const int&))
{
	if (a)
		delete[] a;
	a = new int[n];
	if (Compare(1, 0))
	{
		a[0] = 0;
		for (int i = 1; i < n; i++)
		{
			if(i % 500 == 0)
				a[i] = 0 + rand() % (a[i - 1] + 1);
			else
				(a[i - 1] == INTEGER_MAX) ? a[i] = INTEGER_MAX : a[i] = a[i - 1] + rand() % 2;
		}
	}
	else
	{
		a[0] = INTEGER_MAX;
		for (int i = 1; i < n; i++)
		{
			if (i % 500 == 0)
				a[i] = a[i - 1] + rand() % (INTEGER_MAX - a[i - 1] + 1);
			else
				(a[i - 1] == 0) ? a[i] = 0 : a[i] = a[i] = a[i - 1] - rand() % 2;
		}
	}
}
//===================================================== CÁC HÀM GHI FILE =========================================================
void writeArrayToFile(const char* fileName, int *a, const int &n)
{
	std::ofstream fileOut(fileName, std::ios::app);
	for (int i = 0; i < n; i++)
		fileOut << a[i] << " ";
	fileOut.close();
}
void writeTimeToFile(const char* fileName, const char* state, const int &n, double time[10])
{
	std::ofstream fileOut(fileName, std::ios::app);

	fileOut << state << "," << n << ",";

	fileOut << time[0] << "," << time[1] << "," << time[2] << "," << time[3] << "," << time[4];
	fileOut << "," << time[5] << "," << time[6] << "," << time[7] << "," << time[8] << "," << time[9];

	fileOut << std::endl;

	fileOut.close();
}
//====================================================== CÁC HÀM XỬ LÍ ===========================================================
char* plusString(const char *a, const char* b)
{
	char* result = NULL;
	int i, lengthA = strlen(a), lengthB = strlen(b);

	result = (char*)realloc(result, lengthA + lengthB + 1);
	for (int i = 0; i < lengthA; i++)
		result[i] = a[i];
	for (int i = 0; i < lengthB; i++)
		result[lengthA + i] = b[i];
	result[lengthA + lengthB] = '\0';

	return result;
}
void statisticalAlgorithm(const TYPE &typeSort, SORT_ALGORITHM<int>* &pAlg,
	                      int *a, const int &n, bool(*Compare)(const int&, const int&),
						  double &cpu_time_used, const char* fileName)
{
	clock_t start, end;
	//----Cài đặt loại thuật toán cần thống kê
	pAlg = SORT_ALGORITHM<int>::getObject(typeSort);
	//----Copy lại dữ liệu của mảng a cho 1 mảng phụ 
	int *temp = (int*)malloc(n*sizeof(int));
	for (int i = 0; i < n; i++)
		temp[i] = a[i];
	//----Tiến hành sắp xếp mảng phụ và đo thời gian
	start = clock();
	pAlg->Sort(temp, n, Compare);
	end = clock();
	cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
	//----Ghi mảng vừa sắp xếp vào file có đuôi _out
	char* outName = plusString(fileName, "_out.txt");
	writeArrayToFile(outName, temp, n);
	//----Hủy
	free(outName);
	free(temp);
}
void stateSorted(int *&a, SORT_ALGORITHM<int>* &pAlg, bool(*Compare)(const int&, const int&))
{
	double cpu_time_used[10] = { 0 };
	int n;
	//1000
	n = 1000;
	Sorted(a, n, Compare);
	writeArrayToFile("Sorted_1000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Sorted_1000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Sorted_1000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Sorted_1000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Sorted_1000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Sorted_1000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Sorted_1000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Sorted_1000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Sorted_1000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Sorted_1000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Sorted_1000");
	writeTimeToFile("Result.csv", "Sorted", n, cpu_time_used);
	//5000
	n = 5000;
	Sorted(a, n, Compare);
	writeArrayToFile("Sorted_5000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Sorted_5000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Sorted_5000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Sorted_5000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Sorted_5000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Sorted_5000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Sorted_5000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Sorted_5000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Sorted_5000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Sorted_5000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Sorted_5000");
	writeTimeToFile("Result.csv", "Sorted", n, cpu_time_used);
	//10000
	n = 10000;
	Sorted(a, n, Compare);
	writeArrayToFile("Sorted_10000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Sorted_10000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Sorted_10000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Sorted_10000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Sorted_10000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Sorted_10000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Sorted_10000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Sorted_10000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Sorted_10000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Sorted_10000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Sorted_10000");
	writeTimeToFile("Result.csv", "Sorted", n, cpu_time_used);
	//50000
	n = 50000;
	Sorted(a, n, Compare);
	writeArrayToFile("Sorted_50000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Sorted_50000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Sorted_50000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Sorted_50000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Sorted_50000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Sorted_50000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Sorted_50000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Sorted_50000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Sorted_50000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Sorted_50000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Sorted_50000");
	writeTimeToFile("Result.csv", "Sorted", n, cpu_time_used);
	//100000
	n = 100000;
	Sorted(a, n, Compare);
	writeArrayToFile("Sorted_100000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Sorted_100000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Sorted_100000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Sorted_100000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Sorted_100000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Sorted_100000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Sorted_100000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Sorted_100000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Sorted_100000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Sorted_100000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Sorted_100000");
	writeTimeToFile("Result.csv", "Sorted", n, cpu_time_used);
	//250000
	n = 250000;
	Sorted(a, n, Compare);
	writeArrayToFile("Sorted_250000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Sorted_250000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Sorted_250000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Sorted_250000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Sorted_250000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Sorted_250000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Sorted_250000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Sorted_250000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Sorted_250000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Sorted_250000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Sorted_250000");
	writeTimeToFile("Result.csv", "Sorted", n, cpu_time_used);
}
void stateReversed(int *&a, SORT_ALGORITHM<int>* &pAlg, bool(*Compare)(const int&, const int&))
{
	double cpu_time_used[10] = { 0 };
	int n;
	//1000
	n = 1000;
	Reversed(a, n, Compare);
	writeArrayToFile("Reversed_1000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Reversed_1000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Reversed_1000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Reversed_1000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Reversed_1000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Reversed_1000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Reversed_1000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Reversed_1000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Reversed_1000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Reversed_1000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Reversed_1000");
	writeTimeToFile("Result.csv", "Reversed", n, cpu_time_used);
	//5000
	n = 5000;
	Reversed(a, n, Compare);
	writeArrayToFile("Reversed_5000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Reversed_5000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Reversed_5000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Reversed_5000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Reversed_5000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Reversed_5000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Reversed_5000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Reversed_5000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Reversed_5000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Reversed_5000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Reversed_5000");
	writeTimeToFile("Result.csv", "Reversed", n, cpu_time_used);
	//10000
	n = 10000;
	Reversed(a, n, Compare);
	writeArrayToFile("Reversed_10000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Reversed_10000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Reversed_10000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Reversed_10000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Reversed_10000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Reversed_10000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Reversed_10000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Reversed_10000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Reversed_10000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Reversed_10000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Reversed_10000");
	writeTimeToFile("Result.csv", "Reversed", n, cpu_time_used);
	//50000
	n = 50000;
	Reversed(a, n, Compare);
	writeArrayToFile("Reversed_50000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Reversed_50000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Reversed_50000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Reversed_50000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Reversed_50000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Reversed_50000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Reversed_50000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Reversed_50000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Reversed_50000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Reversed_50000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Reversed_50000");
	writeTimeToFile("Result.csv", "Reversed", n, cpu_time_used);
	//100000
	n = 100000;
	Reversed(a, n, Compare);
	writeArrayToFile("Reversed_100000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Reversed_100000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Reversed_100000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Reversed_100000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Reversed_100000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Reversed_100000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Reversed_100000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Reversed_100000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Reversed_100000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Reversed_100000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Reversed_100000");
	writeTimeToFile("Result.csv", "Reversed", n, cpu_time_used);
	//250000
	n = 250000;
	Reversed(a, n, Compare);
	writeArrayToFile("Reversed_250000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Reversed_250000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Reversed_250000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Reversed_250000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Reversed_250000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Reversed_250000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Reversed_250000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Reversed_250000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Reversed_250000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Reversed_250000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Reversed_250000");
	writeTimeToFile("Result.csv", "Reversed", n, cpu_time_used);
}
void stateRandom(int *&a, SORT_ALGORITHM<int>* &pAlg, bool(*Compare)(const int&, const int&))
{
	double cpu_time_used[10] = { 0 };
	int n;
	//1000
	n = 1000;
	Random(a, n, Compare);
	writeArrayToFile("Random_1000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Random_1000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Random_1000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Random_1000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Random_1000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Random_1000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Random_1000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Random_1000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Random_1000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Random_1000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Random_1000");
	writeTimeToFile("Result.csv", "Random", n, cpu_time_used);
	//5000
	n = 5000;
	Random(a, n, Compare);
	writeArrayToFile("Random_5000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Random_5000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Random_5000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Random_5000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Random_5000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Random_5000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Random_5000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Random_5000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Random_5000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Random_5000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Random_5000");
	writeTimeToFile("Result.csv", "Random", n, cpu_time_used);
	//10000
	n = 10000;
	Random(a, n, Compare);
	writeArrayToFile("Random_10000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Random_10000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Random_10000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Random_10000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Random_10000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Random_10000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Random_10000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Random_10000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Random_10000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Random_10000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Random_10000");
	writeTimeToFile("Result.csv", "Random", n, cpu_time_used);
	//50000
	n = 50000;
	Random(a, n, Compare);
	writeArrayToFile("Random_50000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Random_50000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Random_50000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Random_50000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Random_50000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Random_50000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Random_50000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Random_50000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Random_50000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Random_50000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Random_50000");
	writeTimeToFile("Result.csv", "Random", n, cpu_time_used);
	//100000
	n = 100000;
	Random(a, n, Compare);
	writeArrayToFile("Random_100000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Random_100000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Random_100000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Random_100000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Random_100000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Random_100000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Random_100000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Random_100000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Random_100000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Random_100000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Random_100000");
	writeTimeToFile("Result.csv", "Random", n, cpu_time_used);
	//250000
	n = 250000;
	Random(a, n, Compare);
	writeArrayToFile("Random_250000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_Random_250000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_Random_250000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_Random_250000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_Random_250000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_Random_250000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_Random_250000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_Random_250000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_Random_250000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_Random_250000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_Random_250000");
	writeTimeToFile("Result.csv", "Random", n, cpu_time_used);
}
void stateNearlySorted(int *&a, SORT_ALGORITHM<int>* &pAlg, bool(*Compare)(const int&, const int&))
{
	double cpu_time_used[10] = { 0 };
	int n;
	//1000
	n = 1000;
	NearlySorted(a, n, Compare);
	writeArrayToFile("NearlySorted_1000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_NearlySorted_1000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_NearlySorted_1000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_NearlySorted_1000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_NearlySorted_1000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_NearlySorted_1000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_NearlySorted_1000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_NearlySorted_1000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_NearlySorted_1000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_NearlySorted_1000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_NearlySorted_1000");
	writeTimeToFile("Result.csv", "NearlySorted", n, cpu_time_used);
	//5000
	n = 5000;
	NearlySorted(a, n, Compare);
	writeArrayToFile("NearlySorted_5000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_NearlySorted_5000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_NearlySorted_5000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_NearlySorted_5000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_NearlySorted_5000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_NearlySorted_5000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_NearlySorted_5000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_NearlySorted_5000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_NearlySorted_5000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_NearlySorted_5000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_NearlySorted_5000");
	writeTimeToFile("Result.csv", "NearlySorted", n, cpu_time_used);
	//10000
	n = 10000;
	NearlySorted(a, n, Compare);
	writeArrayToFile("NearlySorted_10000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_NearlySorted_10000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_NearlySorted_10000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_NearlySorted_10000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_NearlySorted_10000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_NearlySorted_10000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_NearlySorted_10000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_NearlySorted_10000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_NearlySorted_10000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_NearlySorted_10000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_NearlySorted_10000");
	writeTimeToFile("Result.csv", "NearlySorted", n, cpu_time_used);
	//50000
	n = 50000;
	NearlySorted(a, n, Compare);
	writeArrayToFile("NearlySorted_50000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_NearlySorted_50000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_NearlySorted_50000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_NearlySorted_50000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_NearlySorted_50000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_NearlySorted_50000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_NearlySorted_50000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_NearlySorted_50000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_NearlySorted_50000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_NearlySorted_50000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_NearlySorted_50000");
	writeTimeToFile("Result.csv", "NearlySorted", n, cpu_time_used);
	//100000
	n = 100000;
	NearlySorted(a, n, Compare);
	writeArrayToFile("NearlySorted_100000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_NearlySorted_100000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_NearlySorted_100000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_NearlySorted_100000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_NearlySorted_100000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_NearlySorted_100000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_NearlySorted_100000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_NearlySorted_100000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_NearlySorted_100000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_NearlySorted_100000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_NearlySorted_100000");
	writeTimeToFile("Result.csv", "NearlySorted", n, cpu_time_used);
	//250000
	n = 250000;
	NearlySorted(a, n, Compare);
	writeArrayToFile("NearlySorted_250000_inp.txt", a, n);
	statisticalAlgorithm(INTERCHANGE, pAlg, a, n, Compare, cpu_time_used[0], "InterchangeSort_NearlySorted_250000");
	statisticalAlgorithm(SELECTION, pAlg, a, n, Compare, cpu_time_used[1], "SelectionSort_NearlySorted_250000");
	statisticalAlgorithm(INSERTION, pAlg, a, n, Compare, cpu_time_used[2], "InsertionSort_NearlySorted_250000");
	statisticalAlgorithm(BUBBLE, pAlg, a, n, Compare, cpu_time_used[3], "BubbleSort_NearlySorted_250000");
	statisticalAlgorithm(SHAKER, pAlg, a, n, Compare, cpu_time_used[4], "ShakerSort_NearlySorted_250000");
	statisticalAlgorithm(SHELL, pAlg, a, n, Compare, cpu_time_used[5], "ShellSort_NearlySorted_250000");
	statisticalAlgorithm(RADIX, pAlg, a, n, Compare, cpu_time_used[6], "RadixSort_NearlySorted_250000");
	statisticalAlgorithm(HEAP, pAlg, a, n, Compare, cpu_time_used[7], "HeapSort_NearlySorted_250000");
	statisticalAlgorithm(QUICK, pAlg, a, n, Compare, cpu_time_used[8], "QuickSort_NearlySorted_250000");
	statisticalAlgorithm(MERGE, pAlg, a, n, Compare, cpu_time_used[9], "MergeSort_NearlySorted_250000");
	writeTimeToFile("Result.csv", "NearlySorted", n, cpu_time_used);
}

#endif