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
	char idsv[10];
	char tensv[50];
	char nganhsv[50];
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
	printf("\n==========ADD STUDENT==========");
	printf("\nStudent ID: ");
	fflush(stdin);
	fgets(st.idsv, sizeof(st.idsv),stdin);
	printf("Student Name: ");
	fflush(stdin);
	fgets(st.tensv, sizeof(st.tensv),stdin);
	xoaXuongDong(st.tensv);
	printf("Major: ");
	fflush(stdin);
	fgets(st.nganhsv, sizeof(st.nganhsv),stdin);
}
void addStudentList(ST ds[], int &n){
	do{
		printf("\nEnter the number of Student: ");
		scanf("%d", &n);
	}
	while(n<=0);
		for(int i=0;i<n;i++){
			printf("\nStudent No. %d", i+1);
			addStudent(ds[i]);
		}
}
void sapXepDanhSachSVTheoTen(ST ds[], int n){
	for(int i=0; i<n-1; i++){
		for(int j=i+1; j<n; j++){
			if(strcmp(strupr(ds[i].tensv), strupr(ds[j].tensv))>0){
				ST temp;
				temp = ds[i];
				ds[i] = ds[j];
				ds[j]=temp;
			}
		}
	}
}
void importSVToFile(ST ds[], int n){
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
void exportSVFromFile(ST ds[], int &n){
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
void displayNameSV(ST st){
	printf("\nStudent ID: %s", st.idsv);
	printf("\nStudent Name: %s", st.tensv);
	printf("\nMajor: %s", st.nganhsv);
}
void displayNameSVList(ST ds[], int n){
	for(int i=0;i<n;i++){
			printf("\n--------------------");
			displayName(ds[i]);
	}
}
int findStudent(ST ds[], int n, char tensv[]){
	for(int i=0; i<n ; i++){
		if(strstr(strupr(ds[i].tensv), strupr(tensv))){
			displayNameSV(ds[i]);
		}
	}
	return 0;
}
int main(){
	SV ds[100];
	int n;
	int choose;
	do{
		printf("------------------MENU-----------------");
		printf("\n1 - Them sach vao thu vien");
		printf("\n2 - Sua thong tin sach");
		printf("\n3 - Xoa mot cuon sach");
		printf("\n4 - In ra danh sach sach");
		printf("\n5 - Tim mot quyen sach");
		printf("\n6 - Thong tin 1 sinh vien");
		printf("\n7 - Liet ke toan bo thong tin sinh vien");
		printf("\n8 - Xoa thong tin sinh vien");
		printf("\n9 - Muon sach");
		printf("\n10 - Liet ke nhung sach da muon cua sinh vien");
		printf("\n11 - Tra sach");
		printf("\n12 - Liet ke toan bo sach da duoc muon");
		printf("\n13 - Tinh tien phat");
		printf("\n14 - .Tim mot hoc sinh theo ten");
		printf("\n15 - Thoat");
		printf("\n----------------------------------------\ n\n");
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
				exportFromFileSV(ds,n);
				sapXepDanhSachSVTheoTen(ds,n);
				displayNameSVList(ds,n);
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
			case 15: 
				exportFromFileSV(ds,n);
				char nameToFind[20];
				printf("Nhap ten sinh vien can tim: ");
				fflush(stdin);
				fgets(nameToFind, sizeof(nameToFind), stdin);
				xoaXuongDong(nameToFind);
				printf("%d", findStudent(ds,n,nameToFind));
				break;
			default : exit;
		}
								
				
		}while(choose<1 || choose>14);
}
