#include <stdio.h>
#include <stdlib.h>
#include "libtype.h"


void insert_sort(u32 data[], u32 count)
{
    int i, j;

    for (i = 1; i < count; i++)
    {
        u32 target = data[i];

        for (j = i-1; (j >= 0) && (data[j] > target); j--)
        {
            data[j+1] = data[j];
        }

        data[j+1] = target;
    }
    
    return;        
}

// hill���� ��ʵ��������Сgap��ֱ�Ӳ�������
void shell_insert_sort(u32 data[], u32 count)
{
    int i, j, gap;

    for (gap=count/2; gap > 0; gap/=2)
    {
        for (i=gap; i < count; i++)
        {
            u32 target = data[i];
            for (j=i-gap; (j >= 0) && (target < data[j]); j-=gap)
            {
                data[j + gap] = data[j];
            }
            
            data[j + gap] = target;            
        }
    }

    return;
}

void swap(u32 *a, u32 *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(u32 data[], u32 count)
{
    int i, j;

    for (j = count-1; j > 0; j--)
    {
        for (i = 0; i < j; i++)
        {
            if (data[i] > data[i+1])
                swap(data+i, data+i+1);
        }
    }
}

// ��ð��
void bubble_sort2(u32 data[], u32 count)
{
    int i, j;

    for (j = 0; j < count - 1; j++)
    {
		//printf("loop %d\n", j);
        for (i = count-1; i > j; i--)
        {
            if (data[i] < data[i-1])
                swap(data+i, data+i-1);
        }
    }
}

void bubble_sort_opt(u32 data[], u32 count)
{
    int i, j;
    bool seq = 0;

    for (j = 0; (j < count - 1) && (seq == 0); j++)
    {
    	//printf("loop %d\n", j);
        seq = 1;
        for (i = count-1; i > j; i--)
        {
            if (data[i] < data[i-1]) {
                swap(data+i, data+i-1);
                seq = 0;
            }
        }
        
        // seq ??
        //if (seq == 1)
        	//break;
    }
}

int division(u32 list[], int left, int right) 
{
	u32 base = list[left];

	while (left < right) {
		while (left < right && list[right] >= base)
			right--;

		list[left] = list[right];

		while (left < right && list[left] <= base)
			left++;

		list[right] = list[left];
	}

	list[left] = base;

	return left;

}

void qsort_ok(u32 list[], int left, int right) 
{

	if (left < right) 
	{
		u32 base = division(list, left, right);

		qsort_ok(list, left, base - 1);
		qsort_ok(list, base + 1, right);
	}
}

void quicksort(int array[], int left, int right) {
    if (left < right) {
        int key = array[left];
        int low = left;
        int high = right;
        while (low < high) {
            while (low < high && array[high] >= key) {
                high--;
            }
            if (low < high) {
                array[low] = array[high];
                low++;
            } else {
                break;
            }
            while (low < high && array[low] <= key) {
                low++;
            }
            if (low < high) {
                array[high] = array[low];
                high--;
            } else {
                break;
            }
        }
        array[low] = key;
        quicksort(array, left, low - 1);
        quicksort(array, low + 1, right);
    }
}


void quick_sort(int a[], int left, int right)
{
	int i = left;
	int j = right;

	if (left>=right)
		return;

	int base = a[left];

	while(i != j) {
		while (a[j]>=base && j>i) {
			j--;
		}

		while (a[i]<=base && i<j) {
			i++;
		}

		if (i < j) {
			int tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
	}

	a[left] = a[i];
	a[i] = base;

	quick_sort(a, left, i-1);
	quick_sort(a, i+1, right);

}


int partition(int arr[], int low, int high)
{
    int pivot = arr[low];     //枢轴记录
    while (low<high){
        while (low<high && arr[high]>=pivot) --high;
        arr[low]=arr[high];             //交换比枢轴小的记录到左端
        while (low<high && arr[low]<=pivot) ++low;
        arr[high] = arr[low];           //交换比枢轴小的记录到右端
    }
    //扫描完成，枢轴到位
    arr[low] = pivot;
    //返回的是枢轴的位置
    return low;
}

void qsort2(int arr[], int low, int high)
{
    if (low < high){
        int pivot=partition(arr, low, high);        //将数组分为两部分
        qsort2(arr, low, pivot-1);                   //递归排序左子数组
        qsort2(arr, pivot+1, high);                  //递归排序右子数组
    }
}

void sort_test(void)
{
	int i;
	int a[] = {6, 1, 2, 7, 9, 11, 4, 5, 10, 8};
	int size = sizeof(a) / (sizeof(a[0]));
	
	//quicksort(a, 0, size - 1);
	qsort2(a, 0, size - 1);

	for (i = 0; i < size; i++) {
		printf("a[%d]=%d\n", i, a[i]);
	}
}

