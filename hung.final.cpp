#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class Student {
public: 
	int ID;
	vector<int> grades;
	double avg;

	Student(int _ID, int n): ID(_ID), grades(vector<int>(n, 0)), avg(0.0) {};

	void calAvg() {
		double sum = 0.0;
		for (int i = 0; i < grades.size(); i++)
			sum += grades[i];
		avg = sum / grades.size();
	}

	static bool cmpByAvg(Student s1, Student s2) {
		return s1.avg > s2.avg;
	}
};

void showGrades(const vector<Student> &students) {
	for (int i = 0; i < students.size(); i++, puts("")) {
		printf("Student %d: ", students[i].ID);
		for (int j = 0; j < students[i].grades.size(); j++)
			printf("%d;", students[i].grades[j]);
	}
}



void showAvg(const vector<Student> &students, int version) {
	for (int i = 0; i < students.size(); i++){
	 printf("Student %d's avg: %.0f\n", students[i].ID, ((version) == 1) ?  (floor(students[i].avg)  ): (round(students[i].avg ))) ;
	}

	for(int i=0;i<students.size();i++){
		printf("%f \n",students[i].avg);
	}
}

void showFinalReport(const vector<Student> &students) {
	
	for (int i = 0; i < students.size(); i++) {
		// printf("Student %d's avg: %d ", students[i].ID);
		// int(floor(students[i].avg));
		// // printf("%s\n", (floor(students[i].avg) >= 60 ？ "(pass)" : "(fail)"));
		// printf("%d\n", "%s\n", (floor(students[i].avg) >= 60 ? "(pass)" : "(fail)"));

		printf( "Student %d's avg: %d ", students[i].ID, int(floor(students[i].avg)));
		printf( "%s\n", ((students[i].avg) >= 60.0 ? "(pass)" : "(fail)"));
	}
}

void writeFinalReport(const vector<Student> &students) {
	FILE *fout = fopen("FinalGrade.txt", "w");
	for (int i = 0; i < students.size(); i++) {
		fprintf(fout, "Student %d's avg: %d ", students[i].ID, int(floor(students[i].avg)));
		fprintf(fout, "%s\n", (floor(students[i].avg) >= 60 ? "(pass)" : "(fail)"));
	}	
}

void showSortedAvg(const vector<Student> &students) {
	vector<Student> sortedList(students);
	sort(sortedList.begin(), sortedList.end(), Student::cmpByAvg);

	for (int i = 0; i < sortedList.size(); i++)
		printf("Student %d's avg: %d\n", sortedList[i].ID, static_cast <int>(floor(sortedList[i].avg)));
}

void CLI(const vector<Student> &students) {
	bool running = true;
	while (running) {
		puts("1. Show all students grades");
		puts("2. Show the avg. for each student");
		puts("3. Show the sorted avg. values for all students");
		puts("4. Exit and output a final report");
		
		printf("Choose an option (1-4): ");

		int choose = 0;
		scanf("%d", &choose);
		switch(choose) {
			case 1:
				showGrades(students);
				break;
			case 2:
				showAvg(students, 1);
				break;
			case 3:
				showSortedAvg(students);
				break;
			case 4:
				showFinalReport(students);
				writeFinalReport(students);
				running = false;
				break;
		}
	}
}

int main() {
	// printf("fuck u \n");
	int m = 0, n = 0;
	FILE *fin = fopen("grade.txt", "r");
	fscanf(fin, "%d;%d;", &m, &n);


	vector<Student> students;
	for (int i = 0; i < m; i++) {
		Student newStudent(i+1, n);
		for (int j = 0; j < n; j++) {
			fscanf(fin, "%d;", &newStudent.grades[j]);
		}
		newStudent.calAvg();
		students.push_back(newStudent);
	}

	// Q1
	// showGrades(students);

	// Q2
	// puts("Version 1:");
	// showAvg(students, 1);
	// puts("");
	// puts("Version 2:");
	// showAvg(students, 2);

	// Q3
	// showFinalReport(students);
	// writeFinalReport(students);

	// Q4
	// showSortedAvg(students);

	// Q5
	CLI(students);

	return 0;
}