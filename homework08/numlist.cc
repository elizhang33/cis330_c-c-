#include "numlist.h"

// Partitioning functions
// Serial partition
unsigned int NumList::partition(vector<int>& keys, unsigned int low, 
                                unsigned int high)
{
    // Use the last element as the pivot
    int pivot = keys[high];

    // TODO: Implement the serial partitioning method
    /*find the pseudocode from CLRS book  */
    unsigned int i = low -1;  //smallest element's index 
    unsigned int j;
    for (j = low; j < high; j++) { 
        //if current element is smaller than pivot, do swap 
        if (keys[j] <= pivot) {
            i++;        //before swap, increment i to next smaller index of element
            swap(keys[i], keys[j]);
        }
    }
    swap(keys[i+1], keys[high]);
    return i + 1;

}

// Parallel partition
unsigned int NumList:: partition_par(vector<int>& keys, unsigned int low,
                                     unsigned int high)
{
    // Use the last element as the pivot
    int pivot = keys[high];


    // TODO: Implement the parallel partitioning method
    // There should be two #pragmas to parallelize the loop
    // First loop is calculating the lt and gt arrays
    // Second is when the integers are copied to the correct position (i.e.,
    // left or right side of the 


    vector<int> temp_keys(keys.begin(), keys.end());
    unsigned int size = (high - low + 1);
    vector<int> lt(size, 0);
    vector<int> lt_prefix_sum(size, 0);
    vector<int> gt(size, 0);
    vector<int> gt_prefix_sum(size, 0);

    /*initialize the lt and gt vectors*/
    #pragma omp parallel for
    for (unsigned int i = low; i < high; i++) {
        if (temp_keys[i] <= pivot) {  //keep temp_keys indexing the same as keys which starts from low to high not necessarily starts from 0
            lt[i - low] = 1;    // lt indexing starts from 0
            gt[i - low] = 0;    // lt indexing starts from 0
        } else {
            gt[i - low] = 1;
            lt[i - low] = 0;
        }
    }

    /*initialize the prefix_sum vectors for lt and gt   */
    for (unsigned int j = low; j < high; j++) {
        if (lt[j - low] == 1) {     //consider the lowth index situation 
            if (j == low) {
                lt_prefix_sum[j - low] = 1;
            } else {
                lt_prefix_sum[j - low] = lt_prefix_sum[j - low - 1] + lt[j - low];
                gt_prefix_sum[j - low] = gt_prefix_sum[j - low - 1] + gt[j - low];
            }
        } else {
            if (j == low) {
                gt_prefix_sum[j - low] = 1;
            } else {
                gt_prefix_sum[j - low] = gt_prefix_sum[j - low - 1] + gt[j - low];
                lt_prefix_sum[j - low] = lt_prefix_sum[j - low - 1] + lt[j - low];
            }
        }
    }
    /*set up the pivot position */
    lt[high - low] = 0;
    lt_prefix_sum[high - low] = lt_prefix_sum[high - low - 1];
    gt[high - low] = 0;
    gt_prefix_sum[high - low] = gt_prefix_sum[high - low - 1];
    
    /*putting back elements into vector keys from temp_keys excluding pivot*/
    #pragma omp parallel for
    for (unsigned int k = low ; k < high; k++) {
        if(temp_keys[k] <= pivot) {
            keys[low + lt_prefix_sum[k - low] - 1] = temp_keys[k];
        } else {
            keys[low + gt_prefix_sum[k - low] + lt_prefix_sum[high - low]] = temp_keys[k];
         }
  }
    /*put pivot back to its corresponding position*/
    keys[low + lt_prefix_sum[high - low]] = temp_keys[high];

    unsigned int new_pivot_id =low + lt_prefix_sum[high - low];

    /*clear up the vectors created*/
    lt.clear();
    gt.clear();
    lt_prefix_sum.clear();
    gt_prefix_sum.clear();
    temp_keys.clear();

    return new_pivot_id;

}

// Actual qsort that recursively calls itself with particular partitioning
// strategy to sort the list
void NumList::qsort(vector<int>& keys, int low, int high, ImplType opt)
{
    if(low < high) {
        unsigned int pi;
        if(opt == serial) {
            pi = partition(keys, low, high);
        } else {
            pi = partition_par(keys, low, high);
        }
        qsort(keys, low, pi - 1, opt);
        qsort(keys, pi + 1, high, opt);
    }
}

// wrapper for calling qsort
void NumList::my_qsort(ImplType opt)
{
    /* Initiate the quick sort from this function */
    qsort(list, 0, list.size() - 1, opt);
}
// Default constructor
// This should "create" an empty list
NumList::NumList() {
    /* do nothing */
    /* you will have an empty vector */
}
// Contructor
// Pass in a vector and the partitioning strategy to use
NumList::NumList(vector<int> in, ImplType opt) {
    list = in;
    my_qsort(opt);
}
// Destructor
NumList::~NumList() {
    /* do nothing */
    /* vector will be cleaned up automatically by its destructor */
}
// Get the element at index
int NumList::get_elem(unsigned int index)
{
    return list[index];
}
// Print the list
void NumList::print(ostream& os)
{
    for(unsigned int i = 0; i < list.size(); i++) {
        os << i << ":\t" << list[i] << endl;
    }
}
