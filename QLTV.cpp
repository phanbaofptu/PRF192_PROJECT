#include "stdio.h"
#include "string.h"
#include "time.h"
#include "conio.h"
#include "stdlib.h"
//SV : Sach Vo
//ST : Student - Sinh Vien
struct SachVo{
	char id[10];
	char ten[50];
	char tacgia[50];
};
struct SinhVien{
	char id[10];
	char ten[50];
	char nganh[50];
};

typedef SachVo SV;
typedef SinhVien ST;

void xoaXuongDong(char x[]){
	size_t len = strlen(x);
	if(x[len-1]=='\n'){
		x[len-1]='\0';
	}
}

void themSach(SachVo &sv){
	printf("\nThem Sach Moi");
	printf("\nID sach: ");
	fflush(stdin);
	fgets(sv.id, sizeof(sv.id),stdin);
	printf("Ten sach: ");
	fflush(stdin);
	fgets(sv.ten, sizeof(sv.ten),stdin);
	xoaXuongDong(sv.ten);
	printf("Ten tac gia: ");
	fflush(stdin);
	fgets(sv.tacgia, sizeof(sv.tacgia),stdin);
}
void addBookList(SV ds[], int &n){
	do{
		printf("\nEnter the number of book: ");
		scanf("%d", &n);
	}
	while(n<=0);
		for(int i=0;i<n;i++){
			printf("\nBook No. %d", i+1);
			themSach(ds[i]);
		}
}
void sapXepDanhSachSachTheoTen(SV ds[], int n){
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
	f = fopen("ThuVien.txt", "wb");
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
	f = fopen("ThuVien.txt", "rb");
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
void displayName(SV sv){
	printf("\nBook code : %s", sv.id);
	printf("\nBook name: %s", sv.ten);
	printf("\nTac gia: %s", sv.tacgia);
}
void displayNameList(SV ds[], int n){
	for(int i=0;i<n;i++){
			printf("\n--------------------");
			displayName(ds[i]);
	}
}
int findBook(SV ds[], int n, char ten[]){
	for(int i=0; i<n ; i++){
		if(strstr(strupr(ds[i].ten), strupr(ten))){
			displayName(ds[i]);
		}
	}
	return 0;
}
void addStudent(ST &st){
	printf("\n========== Enter new student==========");
	printf("\nStudent code: ");
	fflush(stdin);
	fgets(st.id, sizeof(st.id),stdin);
	printf("Student name: ");
	fflush(stdin);
	fgets(st.ten, sizeof(st.ten),stdin);
	xoaXuongDong(st.ten);
	printf("Major: ");
	fflush(stdin);
	fgets(st.nganh, sizeof(st.nganh),stdin);
}
void importToFileSV(ST ds[], int n){
	FILE *f;
	f = fopen("Student.txt", "wb");
	if(f==NULL){
		printf("\nLoi moi file de ghi!");
		return;
	}
	fwrite(&n, sizeof(n), 1, f);
	for(int i=0; i<n; i++){
		fwrite(&ds[i], sizeof(ST), 1, f);
	}
	fclose(f);
}
void addStudentList(ST ds[], int &n){
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
int main(){
	SV ds[100];
	int n;
	int choose;
	do{
		printf("------------------MENU-----------------");
		printf("\n1.Them sach vao thu vien");
		printf("\n2.Sua thong tin sach");
		printf("\n3.Xoa mot cuon sach");
		printf("\n4.In ra danh sach sach");
		printf("\n5.Thong tin sinh vien");
		printf("\n6.");
		printf("\n7.");
		printf("\n8.");
		printf("\n9.");
		printf("\n10.");
		printf("\n11.");
		printf("\n12.");
		printf("\n13.Tinh tien phat");
		printf("\n14.Tim mot quyen sach");
		printf("\nPlease choose menu(1-14): ");
		scanf("%d", &choose);
		switch(choose){
			case 1 : 
				addBookList(ds,n);
				importToFile(ds,n);
				break;
			case 2 :
				//Chua biet
			case 3 :
				//Chua biet
			case 4 :
				exportFromFile(ds,n);
				sapXepDanhSachSachTheoTen(ds,n);
				displayNameList(ds,n);
				break;
			case 5 :
				addStudentList(ds,n);
				importToFileSV(ds,n);
				break;
				//Dang gap loi trung (SachVo trung SinhVien)
			case 6 :
			case 7 :
			case 8 :
			case 9 :
			case 10 :
			case 11 :
			case 12 :
			case 13 : //Chua co cong thuc + thong ke so ngay sinh vien tre
			case 14 :
				exportFromFile(ds,n);
				char nameToFind[20];
				printf("Nhap ten sach can tim: ");
				fflush(stdin);
				fgets(nameToFind, sizeof(nameToFind), stdin);
				xoaXuongDong(nameToFind);
				printf("%d", findBook(ds,n,nameToFind));
				break;
			default : exit;
		}
								
				
		}while(choose<1 || choose>14);
}
