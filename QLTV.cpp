#include "stdio.h"
#include "string.h"
#include "time.h"
#include "conio.h"
#include "stdlib.h"

struct SinhVien{
	char id[10];
	char ten[50];
	char nganh[50];
};

typedef SinhVien SV;

void xoaXuongDong(char x[]){
	size_t len = strlen(x);
	if(x[len-1]=='\n'){
		x[len-1]='\0';
	}
}

void addStudent(SV &sv){
	printf("\n========== Enter new student==========");
	printf("\nStudent code: ");
	fflush(stdin);
	fgets(sv.id, sizeof(sv.id),stdin);
	printf("Student name: ");
	fflush(stdin);
	fgets(sv.ten, sizeof(sv.ten),stdin);
	xoaXuongDong(sv.ten);
	printf("Major: ");
	fflush(stdin);
	fgets(sv.nganh, sizeof(sv.nganh),stdin);
}

void addStudentList(SV ds[], int &n){
	do{
		printf("\nEnter the number of student: ");
		scanf("%d", &n);
	}
	while(n<=0);
		for(int i=0;i<n;i++){
			printf("\nStudent No. %d", i+1);
			addStudent(ds[i]);
		}
}

void displayName(SV sv){
	printf("\nStudent code: %s", sv.id);
	printf("\nStudent name: %s", sv.ten);
	printf("\nMajor: %s", sv.nganh);
}

void displayNameList(SV ds[], int n){
	for(int i=0;i<n;i++){
			printf("\n--------------------");
			displayName(ds[i]);
	}
}

int findStudent(SV ds[], int n, char ten[]){
	for(int i=0; i<n ; i++){
		if(strstr(strupr(ds[i].ten), strupr(ten))){
			displayName(ds[i]);
		}
	}
	return 0;
}
void sapXepDanhSachSinhVienTheoTen(SV ds[], int n){
	for(int i=0; i<n-1; i++){
		for(int j=i+1; j<n; j++){
			if(strcmp(strupr(ds[i].ten), strupr(ds[j].ten))>0){
				SV temp;
				temp = ds[i];
				ds[i] = ds[j];
				ds[j]=temp;
			}
		}
	}
}
void importToFile(SV ds[], int n){
	FILE *f;
	f = fopen("Student.txt", "wb");
	if(f==NULL){
		printf("\nLoi moi file de ghi!");
		return;
	}
	fwrite(&n, sizeof(n), 1, f);
	for(int i=0; i<n; i++){
		fwrite(&ds[i], sizeof(SV), 1, f);
	}
	fclose(f);
}
void exportFromFile(SV ds[], int &n){
	FILE *f;
	f = fopen("Student.txt", "rb");
	if(f==NULL){
		printf("\nLoi moi file de doc!");
		return;
	}
	fread(&n, sizeof(n), 1, f);
	for(int i=0; i<n; i++){
		fread(&ds[i], sizeof(SV), 1, f);
	}
	fclose(f);
}
int main(){
	SV ds[100];
	int n;
	int choose;
	do{
		printf("\n1. Enter student list");
		printf("\n2. Look up student");
		printf("\n3. Display student list");
		printf("\n4. Exit");
		printf("\nPlease choose menu(1-4): ");
		scanf("%d", &choose);
		
		switch(choose){
			case 1:
				addStudentList(ds,n);
				importToFile(ds,n);
				break;
			case 2:
				exportFromFile(ds,n);
				char nameToFind[20];
				printf("Please enter student name: ");
				fflush(stdin);
				fgets(nameToFind, sizeof(nameToFind), stdin);
				xoaXuongDong(nameToFind);
				printf("%d", findStudent(ds,n,nameToFind));
				break;
			case 3:
				exportFromFile(ds,n);
				sapXepDanhSachSinhVienTheoTen(ds,n);
				displayNameList(ds,n);
				break;
			case 4:
				exit;
		}
	}
	while(n!=0 && choose!=4);

}
