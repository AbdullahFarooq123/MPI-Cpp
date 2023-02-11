//#include <mpi.h>
//#include<iostream>
//#include<math.h>
//using namespace std;
//int get_occurance(int*, int, int, int);
//int main(int argc, char** argv) {
//	int array[] = {2, 4, 1, 5, 1, 5, 6, 8, 62};
//	int no_of_processes;
//	MPI_Init(NULL, NULL);
//	int my_rank;
//	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &no_of_processes);
//	int size_of_array = sizeof(array) / sizeof(int);
//	int no_of_elements = ceil(size_of_array / (float)no_of_processes);
//	int my_start = my_rank * no_of_elements;
//	int my_end = my_start + no_of_elements;
//	my_end = my_end >= size_of_array ? size_of_array : my_end;
//	int my_occurance = 0;
//	int key = 5;
//	MPI_Status* statuses = new MPI_Status[no_of_processes];
//	int total_occurance = 0;
//	switch (my_rank)
//	{
//	case 0:
//		
//		my_occurance = get_occurance(array, my_start, my_end, key);
//		total_occurance = my_occurance;
//		for (int i = 1; i < no_of_processes; i++) {
//			int occurance = 0;
//			MPI_Recv(&occurance, i, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//			total_occurance += occurance;
//		}
//		cout << "ARRAY IS : [";
//		for (int i : array) {
//			cout << i << ", ";
//		}
//		cout << "]\n";
//		cout << "TOTAL OCCURANCES OF " << key << " in the array is : " << total_occurance;
//		break;
//	default:
//		my_occurance = get_occurance(array, my_start, my_end, key);
//		MPI_Send(&my_occurance, 1, MPI_INT, 0, my_rank, MPI_COMM_WORLD);
//		break;
//	}
//	MPI_Finalize();
//}
//int get_occurance(int* array, int start, int end, int key) {
//	int occurance = 0;
//	for (int i = start; i < end; i++)
//		if (array[i] == key)
//			occurance++;
//	return occurance;
//}