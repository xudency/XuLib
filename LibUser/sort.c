#include <stdio.h>
#include <stdlib.h>
#include "type.h"


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

