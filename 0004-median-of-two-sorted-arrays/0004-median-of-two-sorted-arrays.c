double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int total = nums1Size +nums2Size;
    int arr[2001];
    int i=0,j=0,k=0;
    while (i<nums1Size && j<nums2Size){
        if (nums1[i]<nums2[j])
            arr[k++] = nums1[i++];
        else
            arr[k++]=nums2[j++];
    }
    while (i<nums1Size)
        arr[k++] = nums1[i++];

    while(j<nums2Size)
        arr[k++]=nums2[j++];
    if (total %2 ==1)
        return arr [total / 2];
    return (arr[total/2]+arr[total/2 -1 ])/2.0;


    
}