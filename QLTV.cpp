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

int validDate( int d, int m, int y) 
{
        int maxd = 31; 
            if ( d < 1 || d > 31 || m < 1 || m > 12 || y < 1) return 0;
            if ( m == 4 || m == 6 || m == 9 || m == 11) maxd = 30;
            else if (m == 2) 
            {	
                    maxd = ( y % 400 == 0 || ( y % 4 == 0 && y % 100 != 0) )? 29:28;
            }
        return d <= maxd; 
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
// case 3 : tu lam
void xoasachtheoID(SV dssv[], int &n, char id){
	for(int i=0; i<n ; i++){
		if(dssv[i].id == "id"){
			for(int j=i; j<n; j++){
				dssv[j] = dssv[j+1];
			}
			n-=1;
			return;
		}
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
	f = fopen("ThuVien.txt", "a");
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
	f = fopen("ThuVien.txt", "r+");
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

void muonSach(ST &st, SV &sv){
	printf("\nStudent ID: ");
	fflush(stdin);
	fgets(st.idsv, sizeof(st.idsv),stdin);
	printf("Book ID: ");
	fflush(stdin);
	fgets(sv.id, sizeof(sv.id),stdin);
	xoaXuongDong(st.tensv);
	printf("Ngay muon: ");
	scanf("%d %d %d", &d, & m, &y);
	if ( !validDate( d, m, y) ) printf("ngay khong hop ly");
        else fgets(st.nganhsv, sizeof(st.nganhsv),stdin);
	fflush(stdin);
}

void addStudentList(ST dssv[], int &m){
	do{
		printf("\nEnter the ID of Student: ");
		scanf("%d", &m);
	}
	while(m<=0);
		for(int i=0;i<m;i++){
			printf("\nStudent No. %d", i+1);
			addStudent(dssv[i]);
		}
}

void sapXepDanhSachSVTheoTen(ST dssv[], int m){
	for(int i=0; i<m-1; i++){
		for(int j=i+1; j<m; j++){
			if(strcmp(strupr(dssv[i].tensv), strupr(dssv[j].tensv))>0){
				ST temp;
				temp = dssv[i];
				dssv[i] = dssv[j];
				dssv[j]=temp;
			}
		}
	}
}
void importSVToFile(ST dssv[], int m){
	FILE *f;
	f = fopen("Student.txt", "a");
	if(f==NULL){
		printf("\nLoi moi file de ghi!");
		return;
	}
	fwrite(&m, sizeof(m), 1, f);
	for(int i=0; i<m; i++){
		fwrite(&dssv[i], sizeof(ST), 1, f);
	}
	fclose(f);
}
void exportSVFromFile(ST dssv[], int &m){
	FILE *f;
	f = fopen("Student.txt", "r+");
	if(f==NULL){
		printf("\nLoi moi file de doc!");
		return;
	}
	fread(&m, sizeof(m), 1, f);
	for(int i=0; i<m; i++){
		fread(&dssv[i], sizeof(ST), 1, f);
	}
	fclose(f);
}
void displayNameSV(ST st){
	printf("\nStudent ID: %s", st.idsv);
	printf("\nStudent Name: %s", st.tensv);
	printf("\nMajor: %s", st.nganhsv);
}
void displayNameSVList(ST dssv[], int m){
	for(int i=0;i<m;i++){
			printf("\n--------------------");
			displayNameSV(dssv[i]);
	}
}
int findStudent(ST dssv[], int m, char tensv[]){
	for(int i=0; i<m ; i++){
		if(strstr(strupr(dssv[i].tensv), strupr(tensv))){
			displayNameSV(dssv[i]);
		}
	}
	return 0;
}
void xoaSinhVienTheoId(ST dssv[], int &m, char idsv){
	for(int i=0; i<m ; i++){
		if(dssv[i].idsv == "idsv"){
			for(int j=i; j<m; j++){
				dssv[j] = dssv[j+1];
			}
			m-=1;
			return;
		}
	}
}
int main(){
	SV ds[100];
	ST dssv[100];
	int n, m;
	char idsv;
	int choose;
	do{
		printf("------------------MENU-----------------");
		printf("\n1.Them sach vao thu vien");
		printf("\n2.Sua thong tin sach");
		printf("\n3.Xoa mot cuon sach");
		printf("\n4.Hien thi danh sach sach co trong thu vien");
		printf("\n5.NhapThong tin sinh vien");
		printf("\n6.Sua thong tin sinh vien");
		printf("\n7.Xoa mot sinh vien");
		printf("\n8.Liet ke toan bo sinh vien");
		printf("\n9.Muon sach");
		printf("\n10.Tra sach");
		printf("\n11.Sach 1 hoc muon");
		printf("\n12.Toan bo sach duoc muon trong thu vien");
		printf("\n13.Tinh tien phat");
		printf("\n14.Tim mot quyen sach");
		printf("\n15.Tim mot hoc sinh theo ten");
		printf("\n16.Thoat!");
		printf("\nPlease choose menu(1-16): ");
		scanf("%d", &choose);
		switch(choose){
			case 1 : 
				addBookList(ds,n);
				importToFile(ds,n);
				break;
			case 2 :
				//Chua biet
			case 3 :
				//case3 tu lam
				int id;
				printf("\nNhap ID sach can xoa : "); 
				scanf("%d",&id);
				printf("\nDanh sach sau khi xoa\n");
				xoasachtheoID(dssv, m, idsv);
				displayNameList(ds, n);
				break;
			case 4 :
				exportFromFile(ds,n);
				sapXepDanhSachSachTheoTen(ds,n);
				displayNameList(ds,n);
				break;
			case 5 :
				addStudentList(dssv,m);
				importSVToFile(dssv,m);
				break;
			case 6 :
			case 7 :
				printf("\nNhap ID Sinh vien can xoa"); scanf("%s", &idsv);
				printf("\nDanh sach sau khi xoa\n");
				xoaSinhVienTheoId(dssv, m, idsv);
				break;
			case 8 :
				exportSVFromFile(dssv,m);
				sapXepDanhSachSVTheoTen(dssv,m);
				displayNameSVList(dssv,m);
				break;
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
				exportSVFromFile(dssv,m);
				char nameToFindSV[20];
				printf("Nhap ten sinh vien can tim: ");
				fflush(stdin);
				fgets(nameToFindSV, sizeof(nameToFindSV), stdin);
				xoaXuongDong(nameToFindSV);
				printf("%d", findStudent(dssv,m,nameToFindSV));
				break;
			case 16: 
				exit;
		}
								
				
		}while(choose != 16);
}
