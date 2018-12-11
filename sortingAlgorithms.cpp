#include <iostream>
#include <array>
#include <limits>
#include <tuple>


using namespace std;

void InsertionSort(int *A , int n);
void ShowArr(int *A , int n);
void Merge(int *A , int p , int q , int r);
void MergeSort(int *A,int p,int r);
tuple<int,int,int> MaxCrossingSubArray(int* A, int low , int mid, int high);
tuple<int,int,int> FindMaxSubArray(int* A, int low, int high);
void Max_Heapify(int *A , int i , int n);
int Parent(int i);
int Left(int i);
int Right(int i);
void BuildMax_Heap(int *A , int n);
void HeapSort(int* A , int n);

int main(){
	int A[] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	int n = sizeof(A)/sizeof(*A);
	

	HeapSort(A , n);
	ShowArr(A , n);

	//InsertionSort(A,n);
	MergeSort(A,0,n-1);
	ShowArr(A , n);

	//tuple<int,int,int> result = FindMaxSubArray(A,0,15);

	//cout << get<0>(result) << " " << get<1>(result) << " " << get<2>(result) << endl;

}

void ShowArr(int *A , int n){
	for (int i = 0; i < n ; i++){
		cout << A[i] << ' ';
	}
	cout << endl;
}

void InsertionSort(int *A , int n){
	for (int i = 1; i < n; i++){
		int key = A[i];

		int j = i-1;

		while(j>=0 && A[j] > key){
			A[j+1] = A[j];
			j--;
		}
		A[j+1] = key;

	}

}

void Merge(int *A , int p , int q , int r){
	int n1 = q-p+1;
	int n2 = r-q;

	int L[n1+1];
	int R[n2+1];


// see if it can be updated to a constant time op
	for (int i = 0; i < n1 ; i++){
		L[i] = A[p+i];
	}
	for (int i = 0 ;i < n2; i++){
		R[i] = A[q+i+1];
	}

	L[n1] = numeric_limits<int>::max();
	R[n2] = numeric_limits<int>::max();


	int i = 0;
	int j = 0;
	for (int k = p; k < r+1; k++){
		if (L[i] < R[j]){
			A[k] = L[i];
			i++;
		}
		else{
			A[k] = R[j];
			j++;
		}
	}
}

void MergeSort(int *A,int p,int r){
	if (p>=r){
		return;
	}
	if (p<r){
		int q = ((p+r)/2);
		MergeSort(A,p,q);
		MergeSort(A,q+1,r);
		Merge(A,p,q,r);
	}

}

tuple<int,int,int> MaxCrossingSubArray(int* A, int low , int mid, int high){
	int left_sum = numeric_limits<int>::min();
	int sum = 0;
	int max_left = 0;
	for (int i = mid; i>=low; i--){
		sum += A[i];
		if (sum > left_sum){
			left_sum = sum;
			max_left = i;
		}
	}

	int right_sum = numeric_limits<int>::min();
	sum = 0;
	int max_right = high;
	for (int i = mid+1; i<=high; i++){
		sum += A[i];
		if (sum > right_sum){
			right_sum = sum;
			max_right = i;
		}
	}

	return make_tuple(max_left,max_right,left_sum+right_sum);
}

tuple<int,int,int> FindMaxSubArray(int* A, int low, int high){
	if (high == low){
		return make_tuple(low,high,A[low]);
	}

	else{
		int mid = (low+high)/2;
		tuple<int,int,int> left = FindMaxSubArray(A,low,mid);
		tuple<int,int,int> right = FindMaxSubArray(A,mid+1,high);
		tuple<int,int,int> cross = MaxCrossingSubArray(A,low,mid,high);

		if((get<2>(left) >= get<2>(right)) && (get<2>(cross) <= get<2>(left) )){
			return left;
		}
		else if((get<2>(left) <= get<2>(right)) && (get<2>(cross) <= get<2>(right) )){
			return right;
		}

		else return cross;
	}
}

//Strassen's method of 2d matrices multiplication


//Heapsort

int Parent(int i){
	return i/2;
}

int Left(int i){
	return (i*2);
}

int Right(int i){
	return (2*i+1);
}

void Max_Heapify(int *A , int i , int n){
	int l = Left(i);
	int r = Right(i);
	int largest = i;
	if (l < n && (A[l]>A[i]) ){
		largest = l;
	}
	if (r < n && (A[r]>A[largest])){
		largest = r;
	}

	if (largest != i){
		int temp = A[largest];
		A[largest] = A[i] ;
		A[i] = temp;

		Max_Heapify(A , largest , n);
	}
}

void BuildMax_Heap(int *A , int n){
	int nn = n/2;
	for (int i = nn; i >= 0 ; i--){
		Max_Heapify(A,i,n);
	}
}

void HeapSort(int* A , int n){
	BuildMax_Heap(A , n);
	for (int i = n-1 ; i >=0 ; i--){
		int temp = A[i];
		A[i] = A[0];
		A[0] = temp;

		
		Max_Heapify(A,0,i);
	}
}


// quickSort

void QuickSort (int *A , int p , int r){

	if (p < r){
		q = Partition(A,p,r);
		QuickSort(A , p , q-1);
		QuickSort(A , q+1 , r);
	}
}


int Partition (int *A , int p , int r){
	int x = A[r];
	int j = p-1;
	for (int i = p; i < r; i++){
		if(A[i] <= x){
			j++;
			swap(A[i], A[j]);
		}
	}
	swap(A[j+1] , A[r]);

	return j+1;
}


// sorting in a range of numbers (counting sort)
//216

int Randomized_Partition(int *A ,int p , int r){
	int i = Random(p,r);
	swap(A[i] , A[r]);
	return Partition(A , p , r);
}


int Randomized_Select(int *A , int p , int r , int i){
	if (p == r){
		return A[p];
	}

	int q= Randomized_Partition(A,p,r);
	int k = q-p+1;

	if(i == k){
		return A[q];
	}
	else if (i < k){
		return Randomized_Select(A , p , q-1 , i);
	}
	else {
		return Randomized_Select(A, q+1 , r , i-k);
	}
}

