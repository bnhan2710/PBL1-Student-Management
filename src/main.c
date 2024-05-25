#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 100

struct fullname {
    char ho[20];
    char ten[20];
};

struct birthday {
    int day;
    int month;
    int year;
};

struct address {
    char SoNha[50];
    char TenDuong[50];
    char ThanhPho[50]; 
};

struct student {
    char lop[30];
    struct fullname HovaTen;
    struct birthday ngaysinh;
    char gender[10];
    struct address DiaChi; 
};

struct IDandMail {
    char email[30];
    int MSSV;
};

typedef struct student SinhVien;
typedef struct IDandMail MSVandEmail;
SinhVien listSV[MAX_SIZE];
MSVandEmail MSV[MAX_SIZE];
int TotalStudent;
int TotalClass = 2;
char fileClass[100][40] = {"23T_Nhat1", "23T_Nhat2" }; 
char fileName[100];
int KiemTraSapXep = 0;
int KiemTraCapMSV = 0;
int CurrentStudent = 0;

SinhVien NhapSinhVien();
void Intro();
void Menu();
void NhapHoVaTen(struct fullname *sv);
void NhapNgaySinh(SinhVien *sv);
void NhapGioiTinh(SinhVien *sv);
void NhapDiaChi(struct address *DiaChi);
void fileNames( char tenLop[] );
void DocFile();
void GhiFile();
void GhiFileLop();
void DocFileLop();
void ChonLopTrongDS();
void toUpperCase(char s[]);
void toLowerCase(char s[]);
void PascalCaseSV( struct fullname *sv  );
void PascalCaseS( char s[] );
void SapXep();// Hàm Sắp xếp sinh viên
void SapXepTheoTen( int low, int high );//sử dụng thuật toán QuickSort để sắp xếp theo tên
void SapXepTheoHo( int low, int high );//sử dụng thuật toán QuickSort để sắp xếp theo họ
void DuyetDsSapXep();
void TimSinhVien();// Hàm tìm sinh viên
void TimTheoTen(int left ,int right , char target[]);// tìm Sinh Viên theo Tên sử dụng Binary Search
void TimTheoMSV(int left ,int right,int MSSV);// tìm Sinh Viên theo MSSV sử dụng Binary Search
void CapMSV();// Cấp mã số sinh viên
void CapEmail(); // Cấp email cho sinh viên
void InDS();// Hàm in Danh sách sinh viên
void TaoVien();
void NoiDungTrongVien();
void KiemTraTruocCapMSV();
void KiemTraTruocCapEmail();
void InSV( SinhVien SV, MSVandEmail MSV );
void DuyetDS();
void XoaSinhVien();
void XoaTheoMSV(int MSSV);
void XoaTheoTen(char target[]);
void XoaDSLop(char target[]);

int main() {
    Intro();
    ChonLopTrongDS();
    Menu();
    return 0;
}

SinhVien NhapSinhVien() {
    SinhVien sv;
    int SL;
    printf("So sinh vien can them : ");
    scanf("%d",&SL);
    while(SL--)
    {
    printf("Nhap thong tin sinh vien thu: %d\n",++TotalStudent);
    fflush(stdin);
    NhapHoVaTen(&sv.HovaTen);
    fflush(stdin);
    NhapNgaySinh(&sv);
    while(getchar() != '\n');
    NhapGioiTinh(&sv);
    fflush(stdin);
    printf("Xin Hay Nhap Dia Chi:\n");
    NhapDiaChi(&sv.DiaChi);
    listSV[TotalStudent-1] = sv;
    GhiFile();
    }
    DocFile();
    KiemTraSapXep = 0;
    KiemTraCapMSV = 0;
    return sv;
}
void toUpperCase( char s[] ) {
	int i;
    for ( i = 0; i < (int)strlen( s ); i++ )
    {
        if ( s[i] >= 'a' && s[i] <= 'z' ) {
            s[i] = s[i] - 32;
        }
    }
}
void toLowerCase( char s[] ) {
	int i;
    for ( i = 0; i < (int)strlen( s ); i++ )
    {
        if ( s[i] >= 'A' && s[i] <= 'Z' ) {
            s[i] = s[i] + 32;
        }
    }
}

void PascalCaseSV( struct fullname *sv  ) {
    toLowerCase( sv->ho );
    toLowerCase( sv->ten );
    sv->ten[0] -= 32;
    sv->ho[0] -= 32;
    int index = strcspn( sv->ho, "\n" );
    int i;
    for( i = 1; i < index; i++ ) {
        if ( sv->ho[ i - 1 ] == ' ' ) {
            sv->ho[i] -= 32;
        }
    }
    sv->ten[strcspn(sv->ten, "\n")] = '\0';
    sv->ho[strcspn(sv->ho, "\n")] = '\0';
}

void PascalCaseS( char s[] ) {
    char Ten[20];
    char Ho[20];
    int Dodai_HoVaTen = strlen(s) - 1;
    int spaceIndex = -1;
    int i;
    for ( i = Dodai_HoVaTen - 1; i >= 0; i--) {
        if ( s[i] == ' ') {
            spaceIndex = i;
            break;
        }
    }
    if (spaceIndex != -1) {
        strncpy( Ten, s + spaceIndex + 1, sizeof(Ten));
        Ten[strcspn(Ten, "\n")] = '\0';
        strncpy(Ho, s, spaceIndex);
        Ho[spaceIndex] = '\0';
    } else {
        strcpy( Ten, s );
        Ho[0] = '\0';
    }
    toLowerCase( Ho );
    toLowerCase( Ten );
    Ten[0] -= 32;
    Ho[0] -= 32;
    int index = strcspn( Ho, "\n" );
    for( i = 1; i < index; i++ ) {
        if ( Ho[ i - 1 ] == ' ' ) {
            Ho[i] -= 32;
        }
    }
    sprintf( s, "%s %s", Ho, Ten );
    s[strcspn(s, "\n")] = '\0';
}

void fileNames( char tenLop[] )
{
    strcpy(fileName, tenLop);
}

void GhiFileLop() {
    FILE* file;
    file = fopen( "DsLop", "w");
    if ( file == NULL ) {
        printf("File khong ton tai!\n");
        return;
    } 
    fprintf( file, "%d\n", TotalClass );
    int i;
    for ( i = 0; i < TotalClass; i++)
    {
        fprintf( file, "%s", fileClass[i] );
        fputc('\n', file);
    }
    fclose( file );
}

void DocFileLop() {
    FILE* file;
    file = fopen("DsLop", "r");
    if (file == NULL) {
        printf("Khong the mo file DsLop!\n");
        return;
    } 

    fscanf(file, "%d", &TotalClass);
    fflush( stdin );
    fputc('\n', file);
    int i;
    for ( i = 0; i < TotalClass; i++) {
        fgets(fileClass[i], sizeof(fileClass[i]) , file);
        fileClass[i][strlen(fileClass[i]) - 1] = '\0';
    }    
    fclose(file);
}


void ChonLopTrongDS() {
    DocFileLop();
    int temp = 0;
    printf("\n");
    printf("\t\t                              Danh Sach Lop                                  \n");
    printf("\t====================================================================================\n");
    printf("\t Ban Muon Thao Tac Tren Lop Nao? \n");
    printf("\t So luong lop: %d\n", TotalClass);
    printf("\t Danh sach lop hien co: \n");
    while( temp < TotalClass ) {
        printf("\t %d. %s\n", temp + 1, fileClass[temp] );
        temp++;
    }
    printf("\t %d. Them danh sach moi \n", temp + 1 );
    printf("\t====================================================================================\n");
    int n;
    do{
        printf("Vui long nhap lua chon: ");
        scanf("%d", &n);
        if(n < 1 || n > temp + 1) printf("Vui long nhap lai!\n");
    } while(n < 1 || n > temp + 1);
    if ( n != temp + 1 ) {
        fileNames( fileClass[ n - 1 ] );
        DocFile();
    }
    else {
        printf("Xin hay nhap ten lop: ");
        fflush(stdin);
        fgets( fileName, sizeof(fileName), stdin );
        strcpy( fileClass[ temp ], fileName );
        TotalClass++;
        GhiFileLop();
        GhiFile();
    }
}

void GhiFile( ) {
    FILE *sv;
    sv = fopen(fileName, "wb+");
    if (sv == NULL)
    {
        printf("file khong ton tai!\n");
        return;
    }
    fwrite(&TotalStudent, sizeof(int), 1, sv); 
    fwrite(&CurrentStudent, sizeof(int), 1, sv );
    int i;
    for (i = 0; i < TotalStudent; i++) {
        fwrite(&listSV[i], sizeof(SinhVien), 1, sv);
        fwrite(&MSV[i], sizeof(MSVandEmail), 1, sv);
    }
    fclose(sv);
}



void DocFile() {
    FILE *sv;
    sv = fopen(fileName, "ab+");
    if (sv == NULL) {
        printf("Tao moi file!\n");
        GhiFile(fileName);
        return;
    }
    fread(&TotalStudent, sizeof(int), 1, sv);
    fread(&CurrentStudent, sizeof(int), 1, sv);
    int i;
    for ( i = 0; i < TotalStudent; i++) {
        fread(&listSV[i], sizeof(SinhVien), 1, sv);
        fread(&MSV[i], sizeof(MSVandEmail), 1, sv);
    }
    fclose(sv);
}



void NhapHoVaTen(struct fullname* sv) {
    char HoVaTen[MAX_SIZE];
    printf("Nhap ho va ten: ");
    fflush(stdin);
    fgets(HoVaTen, sizeof(HoVaTen), stdin);
    int Dodai_HoVaTen = strlen(HoVaTen) - 1;
    int spaceIndex = -1;
    int i;
    for ( i = Dodai_HoVaTen - 1; i >= 0; i--) {
        if (HoVaTen[i] == ' ') {
            spaceIndex = i;
            break;
        }
    }
    if (spaceIndex != -1) {
        strncpy(sv->ten, HoVaTen + spaceIndex + 1, sizeof(sv->ten));
        sv->ten[strcspn(sv->ten, "\n")] = '\0';
        strncpy(sv->ho, HoVaTen, spaceIndex);
        sv->ho[spaceIndex] = '\0';
    } else {
        strcpy(sv->ten, HoVaTen);
        sv->ho[0] = '\0';
    }
    PascalCaseSV( sv );
    printf("Ho: %s\n", sv->ho);
    printf("Ten: %s\n", sv->ten);
}



void NhapNgaySinh(SinhVien* sv) {
    int d, m, y;
    printf("Nhap ngay thang nam sinh: (DD MM YYYY): ");
    scanf("%d %d %d", &d, &m, &y);
    if (y < 1900 || y > 2005 || m < 1 || m > 12 || d < 1 || d > 31) {
        printf("Ngay thang nam sinh khong hop le, vui long nhap lai!\n");
        NhapNgaySinh(sv);
    } else {
        sv->ngaysinh.day = d;
        sv->ngaysinh.month = m;
        sv->ngaysinh.year = y;
    }
}

void NhapGioiTinh(SinhVien* sv) {
    printf("Xin Hay Chon Gioi Tinh: \n");
    printf("1. Nam\n");
    printf("2. Nu\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        strcpy(sv->gender, "Nam");
    } else if (choice == 2) {
        strcpy(sv->gender, "Nu");
    } else {
        printf("Gioi tinh khong hop le, vui long nhap lai!\n");
        NhapGioiTinh(sv);
    }
}

void NhapDiaChi(struct address *DiaChi) {
    printf("Xin Hay Nhap So Nha: ");
    fgets(DiaChi->SoNha, sizeof(DiaChi->SoNha), stdin);
    DiaChi->SoNha[strcspn(DiaChi->SoNha, "\n")] = '\0';

    printf("Xin Hay Nhap Ten Duong: ");
    fgets(DiaChi->TenDuong, sizeof(DiaChi->TenDuong), stdin);
    DiaChi->TenDuong[strcspn(DiaChi->TenDuong, "\n")] = '\0'; 

    printf("Xin Hay Nhap Tinh/Thanh Pho: ");
    fgets(DiaChi->ThanhPho, sizeof(DiaChi->ThanhPho), stdin);
    DiaChi->ThanhPho[strcspn(DiaChi->ThanhPho, "\n")] = '\0';
}


void TimTheoMSV( int left ,int right,int target){
    int mid = (left + right) / 2;
    if (left > right) {
        printf("Khong tim thay sinh vien\n");
        return;
    }
    if (MSV[mid].MSSV == target) {
        printf("                                 Thong tin sinh vien\n");
        printf("\t====================================================================================\n");
        printf("\t- Ho va ten: %s %s\n", listSV[mid].HovaTen.ho, listSV[mid].HovaTen.ten);
        printf("\t- Ngay sinh: %d/%d/%d\n", listSV[mid].ngaysinh.day, listSV[mid].ngaysinh.month, listSV[mid].ngaysinh.year);
        printf("\t- Gioi tinh: %s\n", listSV[mid].gender);
        printf("\t- Dia chi: %s %s %s\n", listSV[mid].DiaChi.SoNha, listSV[mid].DiaChi.TenDuong, listSV[mid].DiaChi.ThanhPho);
        printf("\t- Email: %s\n", MSV[mid].email);
        printf("\t- Lop: %s\n", listSV[mid].lop);
        printf("\t====================================================================================\n");
        return;
    }
    if (MSV[mid].MSSV > target) {
        TimTheoMSV(left, mid - 1, target);
    } else {
        TimTheoMSV(mid + 1, right, target);
    }
}


void TimTheoTen(int left, int right, char target[]) {
    int mid = (left + right) / 2;
       char fullName[50];
       sprintf(fullName, "%s %s", listSV[mid].HovaTen.ho, listSV[mid].HovaTen.ten);
    if (left > right) {
        printf("Khong tim thay sinh vien\n");
        return;
    }
    if (strcmp(fullName, target) == 0) {
        printf("                             Thong tin sinh vien\n");
        printf("\t====================================================================================\n");
        printf("\t- Ho va ten: %s %s\n", listSV[mid].HovaTen.ho, listSV[mid].HovaTen.ten);
        printf("\t- Ngay sinh: %d/%d/%d\n", listSV[mid].ngaysinh.day, listSV[mid].ngaysinh.month, listSV[mid].ngaysinh.year);
        printf("\t- Gioi tinh: %s\n", listSV[mid].gender);
        printf("\t- Dia chi: %s %s %s\n", listSV[mid].DiaChi.SoNha, listSV[mid].DiaChi.TenDuong, listSV[mid].DiaChi.ThanhPho);
        printf("\t- Email: %s\n", MSV[mid].email);
        printf("\t- Lop: %s\n", listSV[mid].lop);
        printf("\t====================================================================================\n");
        return;
    }
    if (strcmp(listSV[mid].HovaTen.ten, target) > 0) {
        TimTheoTen(left, mid - 1, target);
    } else {
        TimTheoTen(mid + 1, right, target);
    }
}



void CapMSV() {
	int i;
    for ( i = 0; i < TotalStudent; i++)
    {
        MSV[i].MSSV = 102230000  + i + 1;
    }
}

void CapEmail( ) {
	int i;
    for ( i = 0; i < TotalStudent; i++)
    {
        sprintf( MSV[i].email, "%d", MSV[i].MSSV );
        strcat( MSV[i].email, "@sv1.dut.udn.vn" );
    }
    
}

void TaoVien() {
    int i;
    for (i = 0; i < 169; i++)
    {
        if (i == 0 || i == 168 || i == 120 || i == 104 || i == 72 || i == 48 || i == 16)
            printf("+");
        else
            printf("-");
    }
    printf("\n");
}

void NoiDungTrongVien() {
    TaoVien();
    printf("|%8s\t|%20s\t\t|%16s\t|%19s\t\t|%10s     |%26s%22s\n", "So the SV", "Ho ten SV", "Ngay Sinh", "Email", "Gioi tinh", "Dia chi", "|");
    TaoVien();
}

void InSV(SinhVien SV, MSVandEmail MSV) {
    printf("%s %15s %31s %23s %31s %15s %47s","|","|","|","|","|","|","|");
     printf("\n|%11d   \t|%20s %s\t%s%8d-%2d-%2d\t|%27s\t|%8s  \t|\t%6s,%6s,%6s\t\t\t|", 
           MSV.MSSV, SV.HovaTen.ho, SV.HovaTen.ten, "|", 
           SV.ngaysinh.day, SV.ngaysinh.month, SV.ngaysinh.year, 
           MSV.email, SV.gender, 
           SV.DiaChi.SoNha, SV.DiaChi.TenDuong, SV.DiaChi.ThanhPho, " ");
    printf("\n");
}


void DuyetDS() {
    int i;
    for (  i = 0; i < TotalStudent; i++)
    {
        PascalCaseSV( &listSV[i].HovaTen );
        InSV( listSV[i], MSV[i] );
    }
    printf("\n");
    TaoVien();
    
}

void SapXepTheoTen( int low, int high ) {
    if ( low < high ) {
    char Pivot[20];
    strcpy( Pivot, listSV[high].HovaTen.ten );
	int i = low - 1;
	int j;
    SinhVien listSVTemp;
	for( j = low; j <= high - 1; j++ ) {
		if ( strcmp( listSV[j].HovaTen.ten, Pivot ) < 0 ) {
			i++;
            //swap
			listSVTemp = listSV[i];
            listSV[i] = listSV[j];
            listSV[j] = listSVTemp;
		}
	}
        // swap
    listSVTemp = listSV[i+1];
    listSV[i+1] = listSV[high];
    listSV[high] = listSVTemp;
    int vitri = i + 1;
	SapXepTheoTen( low, vitri - 1 );
	SapXepTheoTen( vitri + 1, high );
	}
}

void DuyetDsSapXep() {
    int i;
    int low = 0;
    int high = 0;
    int checked = 0;
    for (i = 1; i <= TotalStudent - 1; i++) {
        if (strcmp(listSV[i - 1].HovaTen.ten, listSV[i].HovaTen.ten) == 0) {
            if (checked != 1) {
                low = i - 1;
            }
            high++;
            checked = 1;
        } else if ( checked == 1 ) {
            SapXepTheoHo( low, low + high );
            high = 0;
            checked = 0;
        }
    }
    KiemTraSapXep = 1;
}

void SapXepTheoHo( int low, int high ) {
    if ( low < high ) {
    char Pivot[20];
    strcpy( Pivot, listSV[high].HovaTen.ho );
	int i = low - 1;
	int j;
    SinhVien listSVTemp;
	for( j = low; j <= high - 1; j++ ) {
		if ( strcmp( listSV[j].HovaTen.ho, Pivot ) < 0 ) {
			i++;
            //swap
			listSVTemp = listSV[i];
            listSV[i] = listSV[j];
            listSV[j] = listSVTemp;
		}
	}
        // swap
    listSVTemp = listSV[i+1];
    listSV[i+1] = listSV[high];
    listSV[high] = listSVTemp;
    int vitri = i + 1;
	SapXepTheoHo( low, vitri - 1 );
	SapXepTheoHo( vitri + 1, high );
	}
}

void XoaTheoMSV(int MSSV) {
    printf("Ban co chac muon xoa sinh vien voi ma so: %d !!\n", MSSV);
    printf("1. Co\n2. Khong\n");
    int n;
    int i;
    int j;
    int found = 0; 
    scanf("%d", &n);
    switch(n){
    case 1:
    for (i = 0; i < TotalStudent; i++) {
        if (MSV[i].MSSV == MSSV) {
            found = 1; 
            for (j = i; j < TotalStudent - 1; j++) {
        
                listSV[j] = listSV[j + 1];
                MSV[j] = MSV[j + 1];
            }
            TotalStudent--;
            GhiFile();
            break; 
        }
    }
    if (found) {
        printf("Xoa sinh vien thanh cong\n");
    } else {
        printf("Khong tim thay sinh vien voi ma so %d\n", MSSV);
    }
    case 2:
        Menu();
        break;
    }

}

void XoaTheoTen(char target[]) {
    printf("Ban co chac muon xoa sinh vien voi ten: %s !!\n", target);
    printf("1. Co\n2. Khong\n");
    int n;
    int i, j;
    int found = 0;
    scanf("%d", &n);
    switch(n){
    case 1:
    for (i = 0; i < TotalStudent; i++) {
       char fullName[50];
       sprintf(fullName, "%s %s", listSV[i].HovaTen.ho, listSV[i].HovaTen.ten);
        if (strcmp(fullName, target) == 0) {
            found = 1; 
     
            for (j = i; j < TotalStudent - 1; j++) {
                listSV[j] = listSV[j + 1];
                MSV[j] = MSV[j + 1];
            }
            TotalStudent--;
            i--; 
            GhiFile();
        }
    }
    if (found) {
        printf("Xoa sinh vien thanh cong\n");
    } else {
        printf("Khong tim thay sinh vien voi ten %s\n", target);
    }
    case 2:
        Menu();
        break;
    }
}


void Intro() {
    printf("\t ____________________________________________________________________________________\n");
    printf("\t|                     Truong Dai hoc Bach Khoa - Dai hoc Da Nang.                   |\n");
    printf("\t|                             Khoa Cong Nghe Thong Tin                              |\n");
    printf("\t|                                                                                   |\n");
    printf("\t|                              DO AN PBL1: LAP TRINH TINH TOAN                      |\n");
    printf("\t|                                                                                   |\n");
    printf("\t|                    DE TAI: XAY DUNG UNG DUNG QUAN LY DANH SACH SINH VIEN          |\n");
    printf("\t|                                                                                   |\n");
    printf("\t|                                                                                   |\n");
    printf("\t|                                     Giao vien huong dan: Nguyen Van Hieu          |\n");
    printf("\t|                                                                                   |\n");
    printf("\t|                                                                                   |\n");
    printf("\t|      Sinh vien thuc hien:                                                         |\n");
	printf("\t|                         Huynh Nhu Bao Nhan(23T_Nhat1)   - MSV: 102230034          |\n");
    printf("\t|                         Vo Van Cuong (23T_Nhat1)        - MSV: 102230007          |\n");
    printf("\t|                                                                                   |\n");
    printf("\t|___________________________________________________________________________________|\n");
}
#include <stdio.h>

void printMenu() {
    printf("\t\t\t\t\t\t MENU \n");
    printf("\t====================================================================================\n");
    printf("\t|                                                                                  |\n");
    printf("\t|  0. Chon lop hoc                                                                 |\n");
    printf("\t|  1. Them sinh vien                                                               |\n");
    printf("\t|  2. Sap xep danh sach sinh vien                                                  |\n");
    printf("\t|  3. Xoa sinh vien                                                                |\n");
    printf("\t|  4. Tim kiem sinh vien                                                           |\n");
    printf("\t|  5. Cap ma sinh vien                                                             |\n");
    printf("\t|  6. Cap email                                                                    |\n");
    printf("\t|  7. In danh sach sinh vien                                                       |\n");
    printf("\t|  8. Thoat                                                                        |\n");
    printf("\t|                                                                                  |\n");
    printf("\t====================================================================================\n");
}


void Menu(){
    printMenu();
    int n;
    printf("Vui long nhap lua chon: ");
    scanf("%d", &n);
    while(n < 0 || n > 8){
        printf("Vui long nhap lai!\n");
        scanf("%d", &n);
    }
    switch(n){
        case 0: 
            ChonLopTrongDS();
            Menu();
            break;
        case 1:
            NhapSinhVien();
            NoiDungTrongVien();
            DuyetDS();
            Menu();
            break;
        case 2:
            SapXep();
            Menu();
            break;
        case 3:
            XoaSinhVien();
            Menu();
            break;
        case 4:
            TimSinhVien();
            Menu();
            break;
        case 5:
            KiemTraTruocCapMSV();
            Menu();
            break;
        case 6:
            KiemTraTruocCapEmail();
            Menu();
            break;
        case 7:
            InDS();
            Menu();
            break;
        case 8:
           break;
    }
}

void SapXep(){
    printf("1. Sap xep theo lop o tren\n");
    printf("2. Chon lop khac\n");
    printf("3. Thoat\n");
    int n;
    do{
        printf("Ban chon: ");
        scanf("%d", &n);
        if(n < 1 || n > 3) printf("Vui long nhap lai!\n");
    }while(n < 1 || n > 3);
    switch(n){
        case 1:
            SapXepTheoTen( 0, TotalStudent - 1);
            DuyetDsSapXep();
            CapMSV();
            KiemTraCapMSV = 1;
            CapEmail();
            NoiDungTrongVien();
            DuyetDS();
            break;
        case 2:
            ChonLopTrongDS();
            Menu();
            break;
        case 3:
            Menu();
            break;
    }
}

void TimSinhVien(){
    printf("1. Tim kiem theo ten\n");
    printf("2. Tim kiem theo ma sinh vien\n");
    printf("3. Thoat\n");
    int n;
    do{
        printf("Ban chon: ");
        scanf("%d", &n);
        if(n < 1 || n > 3) printf("Vui long nhap lai!\n");
    }while(n < 1 || n > 3);
    switch(n){
        case 1:
            printf("Vui long nhap ten sinh vien can tim: ");
            char target[40];
            fflush(stdin);
            fgets(target, sizeof(target), stdin);
            target[strcspn(target, "\n")] = '\0';
            PascalCaseS( target );
            TimTheoTen(0, TotalStudent - 1, target);
            break;
        case 2:
           printf("Nhap ma sinh vien can tim: ");
            int IDfind;
            scanf("%d", &IDfind);
            TimTheoMSV(0, TotalStudent - 1, IDfind);
            break;
        case 3:
            Menu();
            break;
    }
}

void InDS() {
    printf("Ban muon in ra danh sach nao?\n");
    printf("1. Lop o tren\n");
    printf("2. Chon lop khac\n");
    printf("3. Thoat\n");
    int n;
    do{
        printf("Ban chon: ");
        scanf("%d", &n);
        if(n < 1 || n > 3) printf("Vui long nhap lai!\n");
    } while(n < 1 || n > 3);
    switch(n){
        case 1:
            NoiDungTrongVien();
            DuyetDS();
            break;
        case 2:
            ChonLopTrongDS();
            break;
        case 3:
            Menu();
            break;
    }
}

void KiemTraTruocCapMSV(){
    if( KiemTraSapXep ){
        printf("Ma sinh vien da duoc cap\n");
        return;
    } else {
        printf("Chua sap xep!\n");
        printf("Ban co muon sap xep danh sach va cap ma sinh vien khong?\n");
        printf("1. Co\n");
        printf("2. Khong\n");
    }
    int n;
    do{
        printf("Ban chon: ");
        scanf("%d", &n);
        if(n < 1 || n > 2) printf("Vui long nhap lai!\n");
    }while(n < 1 || n > 2);
    switch(n){
        case 1:
            SapXepTheoTen( 0, TotalStudent - 1 );
            CapMSV();
            KiemTraCapMSV = 1;
            printf("Cap ma sinh vien thanh cong\n");
            break;
        case 2:
            Menu();
            break;
    }
}

void KiemTraTruocCapEmail(){
    if ( KiemTraSapXep && KiemTraCapMSV ) {
        printf("Email da duoc cap\n");
        return;
    } else {
        printf("Chua sap xep!\n");
        printf("Ban co muon sap xep danh sach va cap Email khong?\n");
        printf("1. Co\n");
        printf("2. Khong\n");
    }
    int n;
    do{
        printf("Ban chon: ");
        scanf("%d", &n);
        if(n < 1 || n > 2) printf("Vui long nhap lai!\n");
    }while(n < 1 || n > 2);
    switch(n){
        case 1:
            SapXepTheoTen( 0, TotalStudent - 1 );
            CapMSV();
            CapEmail();
            printf("Cap Email thanh cong\n");
            break;
        case 2:
            Menu();
            break;
    }
}
void XoaSinhVien(){
    printf("Nhap lua chon:\n");
    printf("1. Xoa theo ten\n");
    printf("2. Xoa theo ma so sinh vien\n");
    printf("3. Thoat\n");
    int n;
    do {
        printf("Ban chon: ");
        scanf("%d", &n);
        if(n < 1 || n > 4) printf("Vui long nhap lai!\n");
    }while(n < 1 || n > 4);
    switch(n){
        case 1:
            printf("Vui long nhap ten sinh vien can xoa: ");
            char target[40];
            fflush(stdin);
            fgets(target, sizeof(target), stdin);
            target[strcspn(target, "\n")] = '\0';
            PascalCaseS( target );
            XoaTheoTen(target);
            break;
        case 2:
            printf("Vui long nhap ma sinh vien can xoa: ");
            int IDdel;
            scanf("%d", &IDdel);
            XoaTheoMSV(IDdel);
            break;
        case 3:
            Menu();
            break;
    }
}