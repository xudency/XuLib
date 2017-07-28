#include <stdio.h>
#include <stdlib.h>
#include "type.h"


// ֱ�Ӳ������� 
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
            // high�±�λ�ÿ�ʼ������߱��������Ҳ����ڻ�׼����Ԫ��
            while (low < high && array[high] >= key) {
                high--;
            }
            if (low < high) {// �ҵ�С��׼����key��Ԫ��
                array[low] = array[high];// ��ֵ��low�±�λ�ã�low�±�λ��Ԫ���Ѿ����׼���Աȹ���
                low++;// low�±����
            } else {// û���ҵ���׼����С��Ԫ��
                // ˵��highλ���ұ�Ԫ�ض���С��׼����
                break;
            }
            // low�±�λ�ÿ�ʼ�����ұ߱��������Ҳ�С�ڻ�׼����Ԫ��
            while (low < high && array[low] <= key) {
                low++;
            }
            if (low < high) {// �ҵ��Ȼ�׼�����Ԫ��
                array[high] = array[low];// ��ֵ��high�±�λ�ã�high�±�λ��Ԫ���Ѿ����׼���Աȹ���
                high--;// high�±�ǰ�ƣ�
            } else {// û���ҵ��Ȼ�׼��С��Ԫ��
                // ˵��lowλ�����Ԫ�ض������ڻ�׼��
                break;
            }
        }
        array[low] = key;// low�±긳ֵ��׼��
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

