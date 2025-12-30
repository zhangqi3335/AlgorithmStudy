#include<stdio.h>
#include<stdlib.h>

void PrintArr(int arr[],int n){
    for (int i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

/**
 * @brief   直接插入排序(升序)
 * @param   待排序的整形数组首地址，数组元素为int类型
 * @param   待排序数组的有效数据个数
 * @note    1.算法特性：原地排序，稳定排序，时间复杂度O(n²),空间复杂度O(1)
 *          2.适用场景：适用基本有序的小数据，效率优于冒泡/选择排序
 *          3.核心思想：将数组分为「已排序区」和「未排序区」，依次将未排序区元素插入已排序区指定位置
 *          边界处理：n=0/1时直接返回，无需排序；数组地址为NULL时做安全校验
 * @warning 入参arr为NULL 或 n<0时，函数无排序行为，直接退出（防程序崩溃）
 */
void StraightInsertSort(int arr[],int n){
    if (arr == NULL || n <= 1)
    {
        return;
    }
    int temp,i,j;
    for (i = 1; i < n; i++)     //把arr[0]作为有序区的第一个元素
    {
        temp = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > temp)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

/**
 * @brief   希尔排序（升序）
 * @param   待排序的整形数组首地址，数组元素为int类型
 * @param   待排序数组的有效数据个数
 * @note    1.算法特性：原地排序，不稳定排序，时间复杂度(O(n^1.3)~O(n²))，空间复杂度O(1)
 *          2.核心思想：按gap分组，每组进行插入排序，直到gap = 1效率最高
 *          3.算法特色：(gap)间隔策略，n/2->n/4->n/8...->1
 */
void ShellSort(int arr[],int n){
    if (arr == NULL || n <= 1)
    {
        return;
    }
    for (int gap = n/2; gap > 0; gap = gap/2) //从gap开始，把gap之前的作为每组（隔一个gap的为同一组）的第一个元素
    {
        int temp;
        int j ;
        for (int i = gap; i < n; i++)//依次遍历，i++是遍历全部的未排序元素
        {
            temp = arr[i];
            for (j = i - gap; j >= 0 && arr[j] > temp ; j-=gap)//j-=gap是精髓，这个功能能作为遍历不同组的功能，i++之后再-gap，这两个元素还是同一个组的成员
            {
                arr[j+gap] = arr[j];
            }
            arr[j+gap] = temp;//这个是交换之后，运行j-=gap，再重新加上gap后保持已排序元素
        }
    }
}

/**
 * @brief   冒泡排序（升序）
 * @param   待排序的整形数组首地址，数组元素为int类型
 * @param   待排序数组的有效数据个数
 * @note    1.算法特性：原地排序，稳定排序，时间复杂度O(n²)，空间复杂度O(1)
 *          2.适用场景：数据量较小，对稳定性有要求的场景
 *          3.核心思想：通过相邻元素两两比较，将最大的元素“冒泡”到末尾
 *          4.优化策略：增加flag标志位，若某一轮没有发生交换，说明数组已有序，提前结束
 */
void BubbleSort(int arr[],int n){
    int i,j,temp;
    int Swapflag = 0;
    for (i = 0; i < n-1; i++)   //每次排序找到未排序中最大的，进行n轮
    {
        Swapflag = 0;
        for ( j = 0; j < n-i-1; j++)    //在未排序的范围内j<n-i-1    
        {
            if(arr[j]>arr[j+1]){    
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                Swapflag = 1;
            }
        }
        if(!Swapflag){
            break;
        }
    }
}

/**
 * @brief   快速排序的分区函数（辅助函数）
 * @note    使用挖坑法（Hole Filling）进行分区
 */
int _Partition(int arr[],int low,int high){
    int pivot = arr[low];//这是初始的坑位（hole）
    while (low<high)
    {
        while (low<high && arr[high]>=pivot)//从右到左，找到比比较值小的放在左边
        {
            high--;
        }
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot)//从左到右，找到比比较值大的放左边
        {
            low++;
        }
        arr[high] = arr[low];
    }
    arr[low] = pivot;//将比较值放在合适的位置
    return low;
}

/**
 * @brief   快速排序的递归函数（辅助函数）
 */
void _QuickSortRecursive(int arr[],int low,int high){
    if(low<high){
    int position = _Partition(arr,low,high);//获取基准位置
    _QuickSortRecursive(arr,low,position-1);//递归左边
    _QuickSortRecursive(arr,position+1,high);//递归右边
    }
}

/**
 * @brief   快速排序（升序）
 * @param   待排序的整形数组首地址，数组元素为int类型
 * @param   待排序数组的有效数据个数
 * @note    1.算法特性：原地排序，不稳定排序，平均时间复杂度最好O(nlogn)，最差O(n²)；空间复杂度最好O(log n),最差O(n)
 *          最好的时候是每次找到的基准都是中间值，平分数组，每层都是遍历完O(n),递归层数为O(log₂n),相乘约为O(nlogn)
 *          最坏的时候是每次找到的都是最大或者最小，每层都是遍历完O(n),递归层数为O(n),相乘约为O(n²)
 *          2.适用场景：处理大数据量的通用排序算法，性能优异
 *          3.核心思想：分治法(Divide and Conquer)。选定基准值，将数组分为两部分，左边比基准小，右边比基准大
 *          在工程应用中，取 arr[low]、arr[high]、arr[mid] 三者中间的那个数作为基准，交换到 low 位置后再开始排序。
 */
void QuickSort(int arr[],int n){   
    if(arr == NULL || n<=1){
        return;
    }
    _QuickSortRecursive(arr,0,n-1);
}


/**
 * @brief   简单选择排序（升序）
 * @param   arr 待排序的整形数组首地址
 * @param   n   待排序数组的有效数据个数
 * @note    1.算法特性：原地排序，不稳定排序，时间复杂度O(n²)，空间复杂度O(1)
 *          2.适用场景：数据量较小。
 *          3.核心思想：每一轮从未排序区中选出最小的元素，与未排序区的第一个元素交换
 *          4.与冒泡区别：冒泡是每轮交换多次，选择排序是每轮只交换一次（移动次数少），虽然复杂度相同，但通常略优于冒泡。
 */
void SelectSort(int arr[], int n) {
    if (arr == NULL || n <= 1) {
        return;
    }
    int i,j,temp,least;
    for (i = 0; i < n-1; i++)
    {
        int least = i;
        for (j = least; j < n; j++)     //在未排序区域找到最小的
        {
            if(arr[j]<arr[least]){
                least = j;
            }
        }
        if(arr[i] != arr[least]){       //记得判断交换的不相等
            temp = arr[i];
            arr[i] = arr[least];
            arr[least] = temp;
        }
    }
    
}

/**
 * @brief   核心引擎：堆调整 (Sift Down / Sink)
 * @param   arr    数组首地址
 * @param   parent 当前要调整的节点下标（假设它的子树已经是堆）
 * @param   len    当前堆的大小（用来判断是否越界）
 * @note    将 parent 节点“下沉”到合适位置，保证以 parent 为根的子树满足大顶堆性质
 */
void HeapAdjust(int arr[], int parent, int len){
    int childern = 2*parent + 1;
    int temp = arr[parent]; 
    while(childern<len){
        if (childern+1<len && arr[childern]<arr[childern+1])
        {
            childern++;
        }
        if(temp < arr[childern]){
            arr[parent] = arr[childern];
            parent = childern;          //记得更新父节点和叶子节点的下标
            childern = 2*parent + 1; 
        }
        else{
            break;
        }
    }
    arr[parent] = temp;
}

/**
 * @brief   堆排序主函数
 * @param   arr    数组首地址
 * @parm    n      数组的有效元素个数
 * @note    时间复杂度 O(n log n)，不稳定排序
 *          堆是完全二叉树，每一行的叶子节点必须满之后排下一行节点
 */
void HeapSort(int arr[], int n){
    int i,j,temp;
    for ( i = n/2 - 1; i >= 0; i--)     //建堆，要按照树的结构来看，先从节点下标3开始和叶子节点比较，依次推进，直到把最大的放到顶端
    {
        HeapAdjust(arr,i,n);
    }
    for ( j = n-1; j>0; j--)            //每次放最后一位后，未排序元素数量减一
    {
        if(arr[j] < arr[0]){            //把最大的元素（堆顶）放到末尾
            temp = arr[0];
            arr[0] = arr[j];
            arr[j] = temp;
        }
        HeapAdjust(arr,0,j);            //重新找到最大的放到堆顶
    }
}

/**
 * @brief   归并操作：将两个有序区间 [left...mid] 和 [mid+1...right] 合并
 * @param   arr   原数组
 * @param   temp  辅助数组（暂存区）
 * @param   left  左半区起点
 * @param   mid   中间点
 * @param   right 右半区终点
 */
void _merge(int arr[],int temp[],int left,int mid,int right){
    int i = left;
    int j = mid+1;
    int k = 0;
    while (i<=mid && j<=right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else{
            temp[k++] = arr[j++];
        }
    }
    while (i<=mid)
    {
        temp[k++] = arr[i++];
    }
    while (j <= right)
    {
        temp[k++] = arr[j++];
    }
    for (int t = 0; t < k; t++)
    {
        arr[left+t] = temp[t];
    }
}


/**
 * @brief   归并排序递归体
 */
void _mergeSortcursive(int arr[],int temp[],int left,int right){
    if(left<right){
        int mid = left + (right-left)/2;
        _mergeSortcursive(arr,temp,left,mid);
        _mergeSortcursive(arr,temp,mid+1,right);
        _merge(arr,temp,left,mid,right); 
    }
}


/**
 * @brief   归并排序（升序）
 * @param   arr 待排序数组
 * @param   n   数据个数
 * @note    1. 特性：稳定排序，时间复杂度 O(nlogn)，空间复杂度 O(n)
 *          2. 嵌入式注意：由于需要 malloc O(n) 的内存，在 RAM 紧张的单片机上要慎用。
 */
void mergeSort(int arr[],int n){
    if(arr == NULL || n<=1){
        return;
    }
    int* temp = (int*)malloc(n*sizeof(int));    //为暂时数组分配空间
    if(temp == NULL){
        return;
    }
    _mergeSortcursive(arr,temp,0,n-1);          //right为n-1，这个下标需要总数目减一
    free(temp);                                 //记得释放空间
}

/**
 * @brief   辅助函数：获取数组中的最大值（用来确定最大位数）
 */
int _GetMax(int arr[], int n){
    int Max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if(arr[i]>Max){
            Max = arr[i];
        }
    }
    return Max;
}


/**
 * @brief   辅助函数：对数组按照"某个位数"进行计数排序
 * @param   exp 当前的位数因子 (1代表个位, 10代表十位, 100代表百位...)
 * @note    这是基数排序的核心，必须是稳定排序，否则前一位的排序成果会白费。
 */
void _CountSortForRadix(int arr[], int n, int exp){
    int* output = (int*)malloc(n*sizeof(int));
    int bucket[10] = {0};

    if(output == NULL){return;}

    for (int i = 0; i < n; i++)         //统计桶的个数，就是每个位上有几个相同的数字：{13，123} bucket[3] = 2；
    {
        bucket[(arr[i]/exp)%10]++;
    }

    for (int i = 1; i < 10; i++)
    {
        bucket[i] += bucket[i-1];       //让桶记录下小于i的个数：{11，12，13}：bucket[3] = 3，不能用i+1，会越界；
    }
    
    for (int i = n-1; i >=0 ;i--)       //倒序遍历数组
    {
        int digit = (arr[i]/exp)%10;    //找到bucket[i]的i
        int pos = bucket[digit]-1;      //找到对应的下标
        output[pos] = arr[i];
        bucket[digit]--;                //排序之后数量减小
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
    
    free(output);
}

/**
 * @brief   基数排序（升序）
 * @param   arr 待排序数组（仅支持非负整数）
 * @param   n   数据个数
 * @note    1. 算法特性：稳定排序，时间复杂度 O(d(n+k)) -> 接近 O(n)
 *          2. 适用场景：正整数排序，且最大值不会特别大。
 *          3. 限制：不能直接处理负数和小数（需特殊转化）。
 */
void RadixSort(int arr[], int n){
    if(arr == NULL || n<=1){return;}
    int Max = _GetMax(arr,n);
    for (int exp = 1; (Max/exp)>0; exp *= 10)
    {
        _CountSortForRadix(arr,n,exp);
    }
}


int main() {
    int arr[8] = {14,26,38,97,44,12,59,66};
    int n = sizeof(arr)/sizeof(arr[1]);
    printf("排序前：");
    PrintArr(arr,n);
    //StraightInsertSort(arr,n);
    //ShellSort(arr,n);
    //BubbleSort(arr,n);
    //QuickSort(arr,n);
    //SelectSort(arr,n);
    //HeapSort(arr,n);
    //mergeSort(arr,n);
    RadixSort(arr,n);
    printf("排序后：");
    PrintArr(arr,n);
    return 0;
}