#ifndef __SORT_ALGORITHM_H__
#define __SORT_ALGORITHM_H__

#include<iostream>
#include<minmax.h>

//======================================================= CÁC HÀM SO SÁNH =========================================================
template<class T>
bool maxCompare(const T &a, const T &b)
{
	return (a > b);
}
template<class T>
bool minCompare(const T &a, const T &b)
{
	return (a < b);
}
//============================================== CÁC HÀM XỬ LÝ DỮ LIỆU TRONG MẢNG =================================================
template<class T>
void swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}
//======================================================== KHAI BÁO LỚP ===========================================================
enum TYPE{ INTERCHANGE, SELECTION, INSERTION, BUBBLE, SHAKER, SHELL, RADIX, HEAP, QUICK, MERGE };
template<class T>
class SORT_ALGORITHM
{
private:
	static SORT_ALGORITHM* m_object; // template Singleton
	TYPE m_type;
	SORT_ALGORITHM(); // hàm khởi tạo đặt private để cho người dùng không thể khai báo tùy tiện
public:
	// Lấy đối tượng duy nhất
	static SORT_ALGORITHM* getObject(const TYPE &type);
	// Các thuật toán sắp xếp
	static void interchangeSort(T* a, const int &n, bool(*Compare)(const T&, const T&));
	static void selectionSort(T* a, const int &n, bool(*Compare)(const T&, const T&));
	static void insertionSort(T* a, const int &n, bool(*Compare)(const T&, const T&));
	static void bubbleSort(T* a, const int &n, bool(*Compare)(const T&, const T&));
	static void shakerSort(T* a, const int &n, bool(*Compare)(const T&, const T&));
	static void shellSort(T* a, const int &n, bool(*Compare)(const T&, const T&));
	static void countSort(T* a, const int &n, bool(*Compare)(const T&, const T&), const int &exponent);
	static void radixSort(T* a, const int &n, bool(*Compare)(const T&, const T&));
	static void heapify(const int &i, T *a, const int &n, bool(*Compare)(const T&, const T&));
	static void heapSort(T* a, const int &n, bool(*Compare)(const T&, const T&));
	static void quickSort(T* a, const int &left, const int &right, bool(*Compare)(const T&, const T&));
	static void merge(T* a, const int &left, const int &mid, const int &right, bool(*Compare)(const T&, const T&));
	static void mergeSort(T* a, const int &left, const int &right, bool(*Compare)(const T&, const T&));
	// Hành động bắt đầu sắp xếp
	void Sort(T* a, const int &n, bool(*Compare)(const T&, const T&));
};
//======================================================= ĐỊNH NGHĨA LỚP ==========================================================
//---------Khởi động đối tượng duy nhất của lớp
template<class T>
SORT_ALGORITHM<T>* SORT_ALGORITHM<T>::m_object = NULL;
//---------Hàm khởi tạo
template<class T>
SORT_ALGORITHM<T>::SORT_ALGORITHM()
{
	m_type = INTERCHANGE;
}
//---------Hàm lấy đối tượng duy nhất
template<class T>
SORT_ALGORITHM<T>* SORT_ALGORITHM<T>::getObject(const TYPE &type)
{
	if (m_object == NULL)
		m_object = new SORT_ALGORITHM();
	if (m_object)
		m_object->m_type = type;
	return m_object;
}
//---------Hàm thực thi sort
template<class T>
void SORT_ALGORITHM<T>::Sort(T* a, const int &n, bool(*Compare)(const T&, const T&))
{
	switch (m_type)
	{
	case INTERCHANGE:
		interchangeSort(a, n, Compare);
		break;
	case SELECTION:
		selectionSort(a, n, Compare);
		break;
	case INSERTION:
		insertionSort(a, n, Compare);
		break;
	case BUBBLE:
		bubbleSort(a, n, Compare);
		break;
	case SHAKER:
		shakerSort(a, n, Compare);
		break;
	case SHELL:
		shellSort(a, n, Compare);
		break;
	case RADIX:
		radixSort(a, n, Compare);
		break;
	case HEAP:
		heapSort(a, n, Compare);
		break;
	case QUICK:
		quickSort(a, 0, n - 1, Compare);
		break;
	default:
		mergeSort(a, 0, n - 1, Compare);
		break;
	}
}
//---------Các thuật toán sắp xếp
template<class T>
void SORT_ALGORITHM<T>::interchangeSort(T* a, const int &n, bool(*Compare)(const T&, const T&))
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (Compare(a[i], a[j]))
				swap(a[i], a[j]);
		}
	}
}
template<class T>
void SORT_ALGORITHM<T>::selectionSort(T* a, const int &n, bool(*Compare)(const T&, const T&))
{
	int i, j, bestIndex;
	for (i = 0; i < n - 1; i++)
	{
		bestIndex = i;
		for (j = i + 1; j < n; j++)
		{
			if (Compare(a[bestIndex], a[j]))
				bestIndex = j;
		}
		if (bestIndex != i)
			swap(a[bestIndex], a[i]);
	}
}
template<class T>
void SORT_ALGORITHM<T>::insertionSort(T* a, const int &n, bool(*Compare)(const T&, const T&))
{
	int i, j, temp;
	for (i = 1; i < n; i++)
	{
		temp = a[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (Compare(temp, a[j]))
				break;
			a[j + 1] = a[j];
		}
		a[j + 1] = temp;
	}
}
template<class T>
void SORT_ALGORITHM<T>::bubbleSort(T* a, const int &n, bool(*Compare)(const T&, const T&))
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = n - 1; j > i; j--)
		{
			if (Compare(a[j - 1], a[j]))
				swap(a[j - 1], a[j]);
		}
	}
}
template<class T>
void SORT_ALGORITHM<T>::shakerSort(T* a, const int &n, bool(*Compare)(const T&, const T&))
{
	int i, posLastSwap = n - 1, left = 0, right = n - 1;
	while (left < right)
	{
		for (i = left; i < right - 1; i++)
		{
			if (Compare(a[i], a[i + 1]))
			{
				swap(a[i], a[i + 1]);
				posLastSwap = i;
			}
		}
		right = posLastSwap;
		for (i = right; i > left; i--)
		{
			if (Compare(a[i - 1], a[i]))
			{
				swap(a[i - 1], a[i]);
				posLastSwap = i;
			}
		}
		left = posLastSwap;
	}
}
template<class T>
void SORT_ALGORITHM<T>::shellSort(T* a, const int &n, bool(*Compare)(const T&, const T&))
{
	T temp;
	int i, j, distance;
	for (distance = n / 2; distance > 0; distance /= 2)
	{
		for (i = distance; i < n; i++)
		{
			temp = a[i];
			j = i;
			while ((j -= distance) >= 0)
			{
				if (Compare(temp, a[j]))
					break;
				a[j + distance] = a[j];
			}
			a[j + distance] = temp;
		}

	}
}
template<class T>
void SORT_ALGORITHM<T>::countSort(T *a, const int &n, bool(*Compare)(const T&, const T&), const int &exponent)
{
	int i, digit[10] = { 0 };
	T* outArray = (T*)malloc(n * sizeof(T));
	// Bắt đầu đếm
	for (i = 0; i < n; i++)
		digit[(a[i] / exponent) % 10]++;
	// Cộng dồn ra chỉ số
	if (Compare == maxCompare)
	{
		for (i = 1; i < 10; i++)
			digit[i] += digit[i - 1];
	}
	else
	{
		for (i = 8; i >= 0; i--)
			digit[i] += digit[i + 1];
	}
	// Sắp xếp lại cơ số 
	for (i = n - 1; i >= 0; i--)
	{
		outArray[digit[(a[i] / exponent) % 10] - 1] = a[i];
		digit[(a[i] / exponent) % 10]--;
	}
	// Chép lại dữ liệu
	for (i = 0; i < n; i++)
		a[i] = outArray[i];

	free(outArray);
}
template<class T>
void SORT_ALGORITHM<T>::radixSort(T *a, const int &n, bool(*Compare)(const T&, const T&))
{
	int i;
	// Tìm phần tử có nhiều cơ số nhất
	T max = a[0];
	for (i = 1; i < n; i++)
	{
		if (a[i] > max)
			max = a[i];
	}
	// Bắt đầu sắp xếp cơ số từ hàng đơn vị trở lên
	for (int exponent = 1; max / exponent > 0; exponent *= 10)
		countSort(a, n, Compare, exponent);
}
template<class T>
void SORT_ALGORITHM<T>::heapify(const int &i, T *a, const int &n, bool(*Compare)(const T&, const T&))
{
	int greatest = i, left = 2 * i + 1, right = 2 * i + 2;

	if (left < n && Compare(a[left], a[greatest]))
		greatest = left;
	if (right < n && Compare(a[right], a[greatest]))
		greatest = right;

	if (greatest != i)
	{
		swap(a[greatest], a[i]);
		heapify(greatest, a, n, Compare);
	}
}
template<class T>
void SORT_ALGORITHM<T>::heapSort(T *a, const int &n, bool(*Compare)(const T&, const T&))
{
	int i;
	for (i = n / 2 - 1; i >= 0; i--)
		heapify(i, a, n, Compare);
	for (i = n - 1; i >= 0; i--)
	{
		swap(a[0], a[i]);
		heapify(0, a, i, Compare);
	}
}
template<class T>
void SORT_ALGORITHM<T>::quickSort(T* a, const int &left, const int &right, bool(*Compare)(const T&, const T&))
{
	int i = left, j = right, pivot = a[(left + right) / 2];
	while (i <= j)
	{
		while (Compare(pivot, a[i]))
			i++;
		while (Compare(a[j], pivot))
			j--;
		if (i <= j)
		{
			swap(a[i], a[j]);
			i++;
			j--;
		}
	}
	// Đệ quy
	if (left < j)
		quickSort(a, left, j, Compare);
	if (i < right)
		quickSort(a, i, right, Compare);
}
template<class T>
void SORT_ALGORITHM<T>::merge(T* a, const int &left, const int &mid, const int &right, bool(*Compare)(const T&, const T&))
{
	int i = left, j = mid + 1, k = 0;
	T* temp = new T[right - left + 1];
	while (i <= mid && j <= right)
	{
		if (Compare(a[i], a[j]))
		{
			temp[k] = a[j];
			j++;
		}
		else
		{
			temp[k] = a[i];
			i++;
		}
		k++;
	}
	while (i <= mid)
	{
		temp[k] = a[i];
		i++;
		k++;
	}
	while (j <= right)
	{
		temp[k] = a[j];
		j++;
		k++;
	}
	for (i = 0; i < k; i++)
		a[i + left] = temp[i];
	delete[] temp;
}
template<class T>
void SORT_ALGORITHM<T>::mergeSort(T* a, const int &left, const int &right, bool(*Compare)(const T&, const T&))
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		mergeSort(a, left, mid, Compare);
		mergeSort(a, mid + 1, right, Compare);
		merge(a, left, mid, right, Compare);
	}
}

#endif