#include <stdio.h>
#include <stdlib.h>
#include "type.h"


// 直接插入排序 
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

// hill排序 其实质是逐步缩小gap的直接插入排序
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

// 逐步冒泡
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
    bool seq = false;

    for (j = 0; (j < count - 1) && (seq == false); j++)
    {
    	//printf("loop %d\n", j);
        seq = true;
        for (i = count-1; i > j; i--)
        {
            if (data[i] < data[i-1]) {
                swap(data+i, data+i-1);
                seq = false;
            }
        }
        
        // seq ??
        //if (seq == true)
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
            // high下标位置开始，向左边遍历，查找不大于基准数的元素
            while (low < high && array[high] >= key) {
                high--;
            }
            if (low < high) {// 找到小于准基数key的元素
                array[low] = array[high];// 赋值给low下标位置，low下标位置元素已经与基准数对比过了
                low++;// low下标后移
            } else {// 没有找到比准基数小的元素
                // 说明high位置右边元素都不小于准基数
                break;
            }
            // low下标位置开始，向右边遍历，查找不小于基准数的元素
            while (low < high && array[low] <= key) {
                low++;
            }
            if (low < high) {// 找到比基准数大的元素
                array[high] = array[low];// 赋值给high下标位置，high下标位置元素已经与基准数对比过了
                high--;// high下标前移，
            } else {// 没有找到比基准数小的元素
                // 说明low位置左边元素都不大于基准数
                break;
            }
        }
        array[low] = key;// low下标赋值基准数
        quicksort(array, left, low - 1);
        quicksort(array, low + 1, right);
    }
}


void sort_test(void)
{
	int i;
	int a[] = {33, 47, 25, 68, 4, 12, 56, 9};
	int size = sizeof(a) / (sizeof(a[0]));
	
	quicksort(a, 0, size - 1);

	for (i = 0; i < size; i++) {
		printf("a[%d]=%d\n", i, a[i]);
	}
}

