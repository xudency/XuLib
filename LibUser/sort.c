#include <stdio.h>
#include <stdlib.h>
#include "type.h"


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

