''' Merge Sort

Description:
    Sorts a list of integers using the Merge Sort algorithm.

Args:
    arr (list[int]): The list of integers to be sorted.

Return:
    list[int]: The sorted list. (Ascending order)

T(n): Av=O(nlog(n)), Worst=O(nlog(n)), Best=O(nlog(n))
S(n): Av=O(n)

Usage Example:
    data = [2, -10, -4, -11, -8, -20, -6, 0, 26, 2]
    print(merge_sort(data)) # [-14, -10, -4, 11, 23, 24, 24, 26, 27, 29]

'''

def merge_sort(arr: list[int]):

    n: int = len(arr)
    # Base case, n == 1 or n == 0. No sorting needed
    if (n < 2): return arr

    # left and right partitions
    left = arr[:n//2]
    right = arr[n//2:]

    # Recursevely devide both subarrays
    merge_sort(left)
    merge_sort(right)

    def combine(parent: list[int], leftSide: list[int], rightSide: list[int]):
        """
            Description:
                Helper function to merge two sorted lists into a single sorted list.

            Args:
                leftSide (list[int]): The left sorted list.
                rightSide (list[int]): The right sorted list.

            Returns:
                list[int]: A new list containing all elements from both input lists in sorted order.
        """

        # i -> leftSide pointer
        # j -> rightSide pointer
        # k -> parent pointer
        i, j, k = [0]*3

        n, m = len(leftSide), len(rightSide)

        # Compare elements from both lists and set the smaller one in its parent's correct index
        while (i<n and j<m):
            # Change '<' to '>' for descending order
            if leftSide[i]<=rightSide[j]:
                parent[k] = leftSide[i]
                i+=1
            else:
                parent[k] = rightSide[j]
                j+=1

            k+=1


        # left overs on LeftSide
        while (i<n):
            parent[k] = leftSide[i]
            i+=1
            k+=1

        # left overs on RightSide
        while (j<m):
            parent[k] = rightSide[j]
            j+=1
            k+=1

        return parent

    # Merge the sorted subarrays back together.
    return combine(parent=arr, leftSide=left, rightSide=right)


''' Quick Sort

Description:
    Sorts a list of integers in-place using the Quick Sort algorithm.

Args:
    arr (list[int]): The list of integers to be sorted.
    low (int): The starting index of the subarray to sort.
    high (int): The ending index of the subarray to sort

return:
    None. (sort in-place)

T(n): Av=O(nlog(n)), Worst=O(n^2), Best=O(nlog(n))
S(n): Av=O(1)

Usage Example:
    data = [26, 7, 19, -16, -1, 2, 4, -12, 11, 15]

    quick_sort(data, low=0, high=len(data)-1)

    print(data) # [-16, -12, -1, 2, 4, 7, 11, 15, 19, 26]

'''

def quick_sort(arr: list[int], low: int, high: int):
    # Base case, subarray has one or zero elements and is already sorted.
    if low >= high:
        return
    """
        Description:
            Helper function to partition the array around a pivot element.

        rearranges the subarray so that all elements smaller than the pivot come before it,
        and all elements greater than the pivot come after it.

        Args:
            arr (list[int]): The list being sorted.
            low (int): The starting index of the subarray.
            high (int): The ending index of the subarray.

        
        return:
            int: The final index of the pivot element after partitioning.
    """
    def partition(arr: list[int], low: int, high: int) -> int:
        # Select the last element as the pivot.
        pivot = arr[high]

        # index of the last element smaller than the pivot afterwards.
        i = low-1


        for j in range(low, high):
            # If the current element is smaller than the pivot, swap it
            # with the element at the next available position for smaller elements.
            if arr[j] < pivot:
                i+=1
                arr[i], arr[j] = arr[j], arr[i]

        # Place the pivot in its correct sorted position by swapping it
        # with the element at i+1.
        arr[i+1], arr[high] = arr[high], arr[i+1]

        # current index of the pivot
        return i+1
    
    # Partition the array and get the new pivot index.
    pivotIndx = partition(arr, low, high)

    # Recursively sort the left subarray (elements before the pivot).
    quick_sort(arr, low, pivotIndx-1)

    # Recursively sort the right subarray (elements after the pivot).
    quick_sort(arr, pivotIndx+1, high)

