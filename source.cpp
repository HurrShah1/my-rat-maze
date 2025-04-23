#include "myStack.h"




int countrows(ifstream& in);
int countcols(ifstream& in);
void allocaterowof2darray(int**& arr, int s);
void allocatecolsof2darray(int**& arr, int r, int c);
void inputin2darray(ifstream& in, int**& arr, int r, int c);
void inputin2darray(int**& arr, int r, int c);
void display(int** arr, int r, int c);
void outputof2darray(ofstream& out, int**& arr, int r, int c);
void deletearr(int**& arr, int r);


int main()
{

	ifstream in;
	int rows = 0;
	int cols = 0;
	int** arr = nullptr;
	int** arr2 = nullptr;
	bool flag = false;

	in.open("input.txt");
	if (in) {

		rows = countrows(in);
		in.close();
		in.open("input.txt");
		cols = countcols(in);

		in.close();
		in.open("input.txt");
		allocaterowof2darray(arr, rows);
		allocatecolsof2darray(arr, rows, cols);
		inputin2darray(in, arr, rows, cols);
		allocaterowof2darray(arr2, rows);
		allocatecolsof2darray(arr2, rows, cols);
		inputin2darray(arr2, rows, cols);

		myStack <string> obj(100);
		int i = 0;
		int j = 0;

		if (arr[0][0] == 0) {
			cout << "invalid game" << endl;
		}
		while (i < rows && j < cols) {
			if (i == rows - 1 && j == cols - 1) {

				flag = true;
				break;
			}
			if (j + 1 < cols && arr[i][j + 1] == 1 && arr[i][j + 1] != -1) {
				j++;
				obj.push("R");
				arr2[i][j] = 1;
			}
			else if ((j - 1 >= 0 && arr[i][j - 1] == 1) && (j + 1 >= cols || arr[i][j + 1] == -1 || arr[i][j + 1] == 0) && (arr[i + 1][j] == 0 || arr[i + 1][j] == -1 || i + 1 >= rows)) {
				arr[i][j] = -1;
				arr2[i][j] = 0;
				j--;
				obj.pop();

			}

			else if (i + 1 < rows && arr[i + 1][j] == 1 && arr[i+1][j] != -1) {
				i++;
				obj.push("D");
				arr2[i][j] = 1;
			}
			else if ((i - 1 >= 0 && arr[i-1][j] == 1) && (i + 1 >= rows || arr[i+1][j] == -1 || arr[i+1][j] == 0) && (arr[i][j+1] == 0 || arr[i][j+1] == -1 || j + 1 >= cols))
			{
				arr[i][j] = -1;
				arr2[i][j] = 0;
				i--;
				obj.pop();
			}
			



			else {
				ofstream out;
				out.open("output.txt");
				out << "path not found" << endl;
				
			//	display(arr2, rows, cols);
				out.close();
				break;
			}
		}




		if (flag == true) {
			ofstream out;
			out.open("output.txt");
			outputof2darray(out, arr2, rows, cols);
			//display(arr2, rows, cols);
			out.close();
			//	obj.display();
		}
	}
	else {
		cout << "file not open";
	}
	deletearr(arr, rows);
	deletearr(arr2, rows);
	return 0;

}
void inputin2darray(int**& arr, int r, int c) {
	for (int i = 0;i < r;i++) {
		for (int j = 0;j < c;j++) {
			arr[i][j] = 0;
		}
	}
	arr[0][0] = 1;
}



void display(int** arr, int r, int c) {

	for (int i = 0;i < r;i++) {
		for (int j = 0;j < c;j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

}


void inputin2darray(ifstream& in, int**& arr, int r, int c) {
	for (int i = 0;i < r;i++) {
		for (int j = 0;j < c;j++) {
			in >> arr[i][j];
		}
	}
}


void allocatecolsof2darray(int**& arr, int r, int c) {
	for (int i = 0;i < r;i++) {
		arr[i] = new int[c];
	}

}

void allocaterowof2darray(int**& arr, int s) {
	arr = new int* [s];
}


int countcols(ifstream& in) {
	int count = 0;
	char temp[1000] = {};
	in.getline(temp, 1000);
	for (int i = 0;temp[i] != '\0';i++) {
		if (temp[i] != ' ' && temp[i] != '\0') {
			count++;
		}

	}

	return count;
}

int countrows(ifstream& in) {
	int line = 0;

	char temp[1000] = {};
	while (!in.eof()) {
		in.getline(temp, 1000);
		line++;
	}
	return line;
}

void outputof2darray(ofstream& out, int**& arr, int r, int c) {
	for (int i = 0;i < r;i++) {
		for (int j = 0;j < c;j++) {
			out << arr[i][j] << " ";
		}
		out << endl;
	}
}
void deletearr(int**& arr, int r) {
	for (int i = 0;i < r;i++) {
		delete[]arr[i];
	}
	delete[]arr;
	arr = nullptr;
}