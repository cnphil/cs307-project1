#include "cse356header.h"

int numbers[1000000], temp[1000000];

struct arg_struct {
	int le;
	int ri;
};

void *m_sort(void *args);
void merge(int left, int mid, int right);

void mergeSort(int array_size)
{
  struct arg_struct aus;
  aus.le = 0; aus.ri = array_size - 1;
  pthread_t mth;
  pthread_create(&mth, NULL, m_sort, &aus);
  pthread_join(mth, NULL);
}
 
 
void *m_sort(void *args)
{
  struct arg_struct *aus = (struct arg_struct *) args;
  int mid, left = aus->le, right = aus->ri;



  if (right > left)
  {

    mid = (right + left) / 2;
	pthread_t lth, rth;
	struct arg_struct lst, rst;
	lst.le = left; lst.ri = mid;
	rst.le = mid + 1; rst.ri = right;

    pthread_create(&lth, NULL, m_sort, &lst);
    pthread_create(&rth, NULL, m_sort, &rst);

	pthread_join(lth, NULL);
	pthread_join(rth, NULL);
    merge(left, mid+1, right);
  

  }
 
  

  pthread_exit(0);
}
 
void merge(int left, int mid, int right)
{
  int i, left_end, num_elements, temp_pos;
 
  left_end = mid - 1;
  temp_pos = left;
  num_elements = right - left + 1;
 
  while ((left <= left_end) && (mid <= right))
  {
    if (numbers[left] <= numbers[mid])
    {
      temp[temp_pos] = numbers[left];
      temp_pos = temp_pos + 1;
      left = left +1;
    }
    else
    {
      temp[temp_pos] = numbers[mid];
      temp_pos = temp_pos + 1;
      mid = mid + 1;
    }
  }
 
  while (left <= left_end)
  {
    temp[temp_pos] = numbers[left];
    left = left + 1;
    temp_pos = temp_pos + 1;
  }
  while (mid <= right)
  {
    temp[temp_pos] = numbers[mid];
    mid = mid + 1;
    temp_pos = temp_pos + 1;
  }

  for (i=0; i <= num_elements; i++)
  {
    numbers[right] = temp[right];
    right = right - 1;
  }
}


main()
{
	freopen("data.in", "r", stdin);
	freopen("data.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", numbers + i);
	
	mergeSort(n);

	for(int i = 0; i < n; i++) printf("%d ", numbers[i]);
	exit(0);
}
