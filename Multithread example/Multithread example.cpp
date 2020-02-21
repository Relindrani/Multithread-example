//Program demonstrating using multiple threads to perform functions on matrices by assigning each row to a thread

#include <iostream>
#include <thread>
#include <vector>

#define THREAD_COUNT 16 //number of threads to create and number of rows/cols in the vectors

using namespace std;

//declare matrices
vector<vector<int>> matrixA(THREAD_COUNT, vector<int>(THREAD_COUNT)), matrixB(THREAD_COUNT, vector<int>(THREAD_COUNT)), matrixResult(THREAD_COUNT, vector<int>(THREAD_COUNT));

//function to add matrices together, takes step as an argument to have the thread "step" to that row
void threadAddition(void* step) {
	auto threadNum = (int)step;

	for (auto i = 0; i < THREAD_COUNT; i++) {
		matrixResult[threadNum][i] = matrixA[threadNum][i] + matrixB[threadNum][i];
	}
}
//function to subtract matrices, takes step as an argument to have the thread "step" to that row
void threadSubtraction(void* step) {
	auto threadNum = (int)step;

	for (auto i = 0; i < THREAD_COUNT; i++) {
		matrixResult[threadNum][i] = matrixA[threadNum][i] - matrixB[threadNum][i];
	}
}
//function to multiply matrices (not accurate to actually multiplying matrices, but still demonstrates multithreading), takes step as an argument to have the thread "step" to that row
void threadMultiplication(void* step) {
	auto threadNum = (int)step;

	for (auto i = 0; i < THREAD_COUNT; i++) {
		matrixResult[threadNum][i] = matrixA[threadNum][i] * matrixB[threadNum][i];
	}
}
//function to divide matrices (not accurate to actually dividing matrices, but still demonstrates multithreading), takes step as an argument to have the thread "step" to that row
void threadDivision(void* step) {
	auto threadNum = (int)step;

	for (auto i = 0; i < THREAD_COUNT; i++) {
		matrixResult[threadNum][i] = matrixA[threadNum][i] / matrixB[threadNum][i];
	}
}

//function to display matrices
void displayMatrix(vector<vector<int>> mat) {
	for (auto i = 0; i < THREAD_COUNT; i++) {
		for (auto j = 0; j < THREAD_COUNT; j++) {
			cout << mat[i][j] << "\t";
		}
		cout << endl;
	}
}

int main(){
	srand(time(NULL));//randomize seed

	thread threads[THREAD_COUNT];//declare threads

	auto step = 0;//declare step variable that is used to place threads in specific rows of the matrices

	//fill matrices with random values between 1 and 9
	for (auto i = 0; i < THREAD_COUNT; i++) {
		for (auto j = 0; j < THREAD_COUNT; j++) {
			matrixA[i][j] = rand() % 9 + 1;
			matrixB[i][j] = rand() % 9 + 1;
		}
	}
	cout << "Matrix A" << endl;
	displayMatrix(matrixA);
	cout << endl << endl << "Matrix B" << endl;
	displayMatrix(matrixB);

	//calls addition function with each thread passing a step counter to assign which row the thread will add, then waits for the threads to all finish, then displays the new matrix
	for (step = 0; step < THREAD_COUNT; step++) threads[step] = thread{ threadAddition, (void*)step };
	for (auto i = 0; i < THREAD_COUNT; i++) threads[i].join();
	cout << endl << endl << "Matrix A + Matrix B" << endl;
	displayMatrix(matrixResult);

	//calls subtraction function with each thread passing a step counter to assign which row the thread will subtract, then waits for the threads to all finish, then displays the new matrix
	for (step = 0; step < THREAD_COUNT; step++) threads[step] = thread{ threadSubtraction, (void*)step };
	for (auto i = 0; i < THREAD_COUNT; i++) threads[i].join();
	cout << endl << endl << "Matrix A - Matrix B" << endl;
	displayMatrix(matrixResult);

	//calls multiply function with each thread passing a step counter to assign which row the thread will multiply, then waits for the threads to all finish, then displays the new matrix
	for (step = 0; step < THREAD_COUNT; step++) threads[step] = thread{ threadMultiplication, (void*)step };
	for (auto i = 0; i < THREAD_COUNT; i++) threads[i].join();
	cout << endl << endl << "Matrix A * Matrix B" << endl;
	displayMatrix(matrixResult);

	//calls divide function with each thread passing a step counter to assign which row the thread will divide, then waits for the threads to all finish, then displays the new matrix
	for (step = 0; step < THREAD_COUNT; step++) threads[step] = thread{ threadDivision, (void*)step };
	for (auto i = 0; i < THREAD_COUNT; i++) threads[i].join();
	cout << endl << endl << "Matrix A / Matrix B" << endl;
	displayMatrix(matrixResult);
}