#include "stdio.h"
#include "string.h"
#include "time.h"
#include "conio.h"
#include "stdlib.h"
#define day 31
#define month 12
#define year 9999
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

void addBorrowedBook(ST dssv[], int m, SV ds[], int n);
int findStudent(ST dssv[], int m, char idsv[]);
void importBookToFile(SV ds[],ST dssv[], int &m, int &n);

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



int truNgay(int d, int m, int y){
	int t = 0;
	while (year>=y){
		if (year == y && month == m){
			t += day - d;
			break;
		}
		else {
			if ( m == 4 || m == 6 || m == 9 || m == 11)
			     t += 30 - d;
			     if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10|| m == 12)
			     t += 31 - d;
			     if (m == 2)
				 {
				 	if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0)
				 	    t += 29 - d;
				 	else t += 28 - d;
				 }
				 m++; 
				 d = 0;
				 if (m == 13){
				 	
				 	y++; 
					 m = 1;
				 }
		}
	}
	return t;
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
	f = fopen("ThuVien.txt", "ab");
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
	printf("Book name: %s", sv.ten);
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


void addBorrowedBook(ST &st, ST dssv[], SV &sv, int m, SV ds[], int n){
	//printf("\n==========ADD STUDENT==========");
	printf("\nStudent ID: ");
	fflush(stdin);
	fgets(st.idsv, sizeof(st.idsv),stdin);
//	xoaXuongDong(idToFindSV);
	printf("\nBook ID: ");
	fgets(sv.id, sizeof(sv.id),stdin);
	if(findStudent(dssv,m,st.idsv)==0)
		printf("Error!!!");
}
void importBookToFile(SV ds[],ST dssv[], int &m, int &n){
	FILE *f;
	f = fopen("Sachmuon.txt", "ab");
	if(f==NULL){
		printf("\nError!!!!");
		return;
	}
	fwrite(&m, sizeof(m), 1, f);
	for(int i=0; i<m; i++){
		fwrite(&dssv[i], sizeof(ST), 1, f);
	}
	fclose(f);
}

void exportBookFromFile(SV ds[],ST dssv[], int &m, int &n){
	FILE *f;
	f = fopen("Sachmuon.txt", "rb");
	if(f==NULL){
		printf("\nError!!!");
		return;
	}
	fread(&m, sizeof(m), 1, f);
	for(int i=0; i<m; i++){
		fread(&dssv[i], sizeof(ST), 1, f);
	}
	fclose(f);
}

void addStudentList(ST dssv[], int &m){
	do{
		printf("\nEnter the number of Student: ");
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
	f = fopen("Student.txt", "ab");
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
	f = fopen("Student.txt", "rb");
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
	printf("Student Name: %s", st.tensv);
	printf("\nMajor: %s", st.nganhsv);
}
void displayNameSVList(ST dssv[], int m){
	for(int i=0;i<m;i++){
			printf("\n--------------------");
			displayNameSV(dssv[i]);
	}
}
int findStudent(ST dssv[], int m, char idsv[]){
	for(int i=0; i<m ; i++){
		if(strstr(strupr(dssv[i].idsv), strupr(idsv))){
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
		printf("\n2.Xoa mot cuon sach");
		printf("\n3.Hien thi danh sach sach co trong thu vien");
		printf("\n4.NhapThong tin sinh vien");
		printf("\n5.Xoa mot sinh vien");
		printf("\n6.Liet ke toan bo sinh vien");
		printf("\n7.Muon sach");
		printf("\n8.Toan bo sach trong thu vien");
		printf("\n9.Tinh tien phat");
		printf("\n10.Tim mot quyen sach");
		printf("\n11.Tim mot hoc sinh theo ten");
		printf("\n12.Thoat!");
		printf("\nPlease choose menu(1-16): ");
		scanf("%d", &choose);
		switch(choose){
			case 1 : 
				addBookList(ds,n);
				importToFile(ds,n);
				break;
			case 2 :
				//case3 tu lam
				int id;
				printf("\nNhap ID sach can xoa : "); 
				scanf("%d",&id);
				printf("\nDanh sach sau khi xoa\n");
				xoasachtheoID(ds, m, id);
				displayNameList(ds, n);
				break;
			case 3 :
				exportFromFile(ds,n);
				sapXepDanhSachSachTheoTen(ds,n);
				displayNameList(ds,n);
				break;
			case 4 :
				addStudentList(dssv,m);
				importSVToFile(dssv,m);
				break;
			case 5 :
				printf("\nNhap ID Sinh vien can xoa"); scanf("%s", &idsv);
				printf("\nDanh sach sau khi xoa\n");
				xoaSinhVienTheoId(dssv, m, idsv);
				break;
			case 6 :
				exportSVFromFile(dssv,m);
				sapXepDanhSachSVTheoTen(dssv,m);
				displayNameSVList(dssv,m);
				break;
			case 7 :
			        addBorrowedBook(dssv,m,ds,n);
			        importBookToFile(ds,dssv,m,n);
			        break;
			case 8 :
				exportBookFromFile(ds,dssv,m,n);
				displayNameList(ds,n);
				break;
			case 9 :
				int d,m,y;
				int dm, mm, ym;
				int cn ;
				//cn = chenh ngay
				int tp; // tp = tien phat mot ngay
				printf("nhap so tien phan mot ngay qua han: ");
				scanf("%d", &tp);
				printf("Nhap ngay muon: ");
				scanf("%d %d %d", &dm, &mm, &ym);
				printf("Nhap ngay tra: ");
				scanf("%d %d %d", &d, &m, &y);
				cn = abs(truNgay(d,m,y) - truNgay(dm,mm,ym));
				if (!validDate(d,m,y) || !validDate(dm, mm, ym)) printf("ngay khong hop le");
				else printf("Ngay da muon: %d\n",cn);
				if (cn > 30) printf("Tien phat tre %d ngay la: %d\n", cn - 30 , (cn - 30) *tp);
				else printf("ban da nap sach dung han\n");
				system ("pause");
				break;
			case 10 :
				exportFromFile(ds,n);
				char nameToFind[20];
				printf("Nhap ten sach can tim: ");
				fflush(stdin);
				fgets(nameToFind, sizeof(nameToFind), stdin);
				xoaXuongDong(nameToFind);
				printf("%d", findBook(ds,n,nameToFind));
				break;
			case 11: 
				exportSVFromFile(dssv,m);
				char idToFindSV[20];
				printf("Nhap ID sinh vien can tim: ");
				fflush(stdin);
				fgets(idToFindSV, sizeof(idToFindSV), stdin);
				xoaXuongDong(idToFindSV);
				printf("%d", findStudent(dssv,m,idToFindSV));
				break;
			case 12: exit;
		}
	}while(choose != 16);	
}
