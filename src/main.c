#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct student;
struct fullname {
	char ho[20];
	char ten[20];
};

struct birthday{
	int day;
	int month;
	int year;
};

struct student {
    int khoa;
    int khoi;
    int lop;
    int MSSV;
	char email[30];
	struct fullname HovaTen;
	struct birthday ngaysinh ;
	char gender[10];
	char address[30];
};

struct khoa {
    char tenKhoa[40];
    int maKhoa;
};
int soluongkhoa;
struct khoa dskhoa[100];
int vitriMSSV = 0;
int dsMSSV[100];


typedef struct student SinhVien;


// Dinh Nghia Ham

SinhVien NhapSinhVien();
void gioithieu();
void Menu();
void NhapHoVaTen( struct fullname* sv );
void NhapKhoa( SinhVien* sv );
int LuaChonCachNhapKhoa();
int NhapTenKhoa( char TenKhoa[] );
int KiemTraKhoa( char TenKhoa[] );
void NhapNgaySinh( SinhVien* sv );
void NhapMSSV( SinhVien* sv );
int LuaChonCoHayKhongMSSV();
int KiemTraMSSV( int MSSV );
void ThemVaoDsMSSV( int MSSV );
void NhapDiaChi( char DiaChi[] ); 
void DocFileKhoa();
void toUpperCase( char s[] );
void toLowerCase( char s[] );

int main(){
	gioithieu();
    Menu();
    return 0;
}

SinhVien NhapSinhVien() {
    SinhVien sv;
    NhapHoVaTen( &sv.HovaTen);
    NhapNgaySinh( &sv );
    // printf(" Ho : %s\n", sv.HovaTen.ho );
    // printf(" Ten : %s\n", sv.HovaTen.ten );
    printf("Xin Hay Nhap Nam Hoc: ");
    scanf("%d", &sv.khoi );
    DocFileKhoa();
    printf("Xin Hay Nhap Nhap Khoa: ");
    NhapKhoa( &sv );
    printf("Xin Hay Nhap Lop : ");
    scanf("%d", &sv.lop );
    // printf("Xin Hay Nhap Nhap Ma So Sinh Vien: ");
    // NhapMSSV( &sv );
    printf("Xin Hay Nhap Gioi tinh: ");
    scanf("%s", sv.gender );
    printf("Xin Hay Nhap Dia Chi:\n");
    NhapDiaChi( sv.address );
    printf("%s", sv.address );
    return sv;
}

void toUpperCase( char s[] ) {
    for ( int i = 0; i < strlen( s ); i++ )
    {
        if ( s[i] >= 'a' && s[i] <= 'z' ) {
            s[i] = s[i] - 32;
        }
    }
}
void toLowerCase( char s[] ) {
    for ( int i = 0; i < strlen( s ); i++ )
    {
        if ( s[i] >= 'A' && s[i] <= 'Z' ) {
            s[i] = s[i] + 32;
        }
    }
}

void NhapHoVaTen( struct fullname* sv ) {
    char HoVaTen[100];
    printf("Nhap ho va ten: ");
    fflush(stdin);
    gets( HoVaTen );
    int Dodai_HoVaTen = strlen( HoVaTen ) - 1;
    int cnt = 0, j = 0;
    for ( int i = 0; i <= Dodai_HoVaTen; i++ )
    {
        if ( HoVaTen[Dodai_HoVaTen - i] != ' ' && cnt == 0 ) {
            printf(" ten :%c\n", HoVaTen[ Dodai_HoVaTen - i] );
            sv->ten[j] = HoVaTen[ Dodai_HoVaTen - i];
            j++;
        } else {
            printf(" ho :%c\n", HoVaTen[ Dodai_HoVaTen - i] );
            sv->ho[cnt] = HoVaTen[ Dodai_HoVaTen - i];
            cnt++;
        }
    }

    strrev( sv->ten );
    strrev( sv->ho );
    sv->ho[cnt] = '\0';
}

void NhapKhoa( SinhVien* sv ) {
    int Choice = LuaChonCachNhapKhoa();
    if ( Choice == 1) {
        char tenKhoa[100];
        int vitri = NhapTenKhoa( tenKhoa );
        sv->khoa = dskhoa[vitri].maKhoa;
    } else {
        printf("Nhap ma khoa: ");
        scanf("%d", &sv->khoa );
    }
}

int LuaChonCachNhapKhoa() {
    int choice;
    printf("Ban co 2 lua chon:\n 1. Nhap Ten Khoa\n 2. Nhap Ma Khoa\n Lua chon: ( 1 / 2 ) ");
    scanf( "%d", &choice );
    switch (choice)
    {
    case 1:{
        return choice;
    }
    case 2: {
        return choice;
    }
    default:
        {
            printf("Ban khong co lua chon khac, vui long nhap lai\n");
            LuaChonCachNhapKhoa();
        }
    }
}

int NhapTenKhoa( char TenKhoa[] ) {
    printf("Nhap vao ten khoa: ");
    gets( TenKhoa );
    int vitri = KiemTraKhoa( TenKhoa );
    if ( vitri != -1 ) {
        return vitri;
    } else {
        printf("Ten khoa khong ton tai, vui long nhap lai\n");
        NhapTenKhoa( TenKhoa );
    }
}

int KiemTraKhoa( char TenKhoa[] ) {
    toUpperCase(TenKhoa);
    for( int i = 0; i < soluongkhoa; i++ ) {
        toUpperCase( dskhoa[i].tenKhoa );
        if( strcmp( TenKhoa, dskhoa[i].tenKhoa ) == 0 ) {
            return i;
        }
    }
    return -1;
}

void NhapNgaySinh( SinhVien* sv ) {
    printf("Nhap ngay thang nam sinh\n");
    printf("nhap ngay sinh:");
    scanf("%d", &sv->ngaysinh.day );
    printf("nhap thang sinh:");
    scanf("%d", &sv->ngaysinh.month );
    printf("nhap nam sinh:");
    scanf("%d", &sv->ngaysinh.year );
}

// void NhapMSSV( SinhVien* sv ) {
//     int Choice = LuaChonCoHayKhongMSSV();
//     if ( Choice == 1 ) {
//         int check;
//         do {
//             printf("Nhap Ma Sinh Vien: ");
//             scanf("%d", &sv->MSSV );
//             sprintf( sv->email, "%d", sv->MSSV );
//             strcat( sv->email, "@sv1.dut.udn.vn");
//             check = 1;
//             if ( KiemTraMSSV( sv->MSSV ) ) {
//                 ThemVaoDsMSSV( sv->MSSV );
//                 check = 0;
//             } else {
//                 printf("MSSV da ton tai hoac khong hop le, vui long nhap cai khac\n");
//                 printf("Ban Co Muon Tiep Tuc Nhap: ( 1 / 0 ) ");
//                 scanf("%d", &check );
//             }
//         } while( check );
//     } else {
//         printf("Ma Sinh Vien cua ban chua duoc cap nhat\n");
//         // strcpy( sv->email, "Chua Duoc Cap Email" );
//     }
// }

// int LuaChonCoHayKhongMSSV() {
//     int choice;
//     printf("Ban co muon nhap Ma So Sinh Vien?\n");
//     printf("Ban co 2 lua chon:\n 1. Co\n 2. Khong\n Lua chon: ( 1 / 2 ) ");
//     scanf( "%d", &choice );
//     switch (choice)
//     {
//     case 1:{
//         return choice;
//     }
//     case 2: {
//         return choice;
//     }
//     default:
//         {
//             printf("Ban khong co lua chon khac, vui long nhap lai\n");
//             LuaChonCoHayKhongMSSV();
//             break;
//         }
//     }
// }

int KiemTraMSSV( int MSSV ) {
    for (int i = 0; i <= vitriMSSV; i++)
    {
        if ( dsMSSV[i] == MSSV ) {
            return 0;
        }
     }
    return 1;
}

void ThemVaoDsMSSV( int MSSV ) {
    dsMSSV[ vitriMSSV ] = MSSV;
    vitriMSSV++;
}

void NhapDiaChi( char DiaChi[] ) {
    char CopyDiaChi[100];
    fflush(stdin);
    printf("Xin Hay Nhap So Nha: ");
    gets( CopyDiaChi );
    strcat( DiaChi, CopyDiaChi );
    strcat( DiaChi, "," );
    fflush(stdin);
    printf("Xin Hay Nhap Ten Duong: ");
    gets( CopyDiaChi );
    strcat( DiaChi, CopyDiaChi );
    strcat( DiaChi, "," );
    fflush(stdin);
    printf("Xin Hay Nhap Tinh/Thanh Pho: ");
    gets( CopyDiaChi );
    strcat( DiaChi, CopyDiaChi );
    fflush(stdin);
    DiaChi[ strlen( DiaChi ) ] = '\0';
}

void DocFileKhoa() {
    FILE* file;
    file = fopen("khoa", "r");
    if ( file == NULL ) {
        printf("Khong tim thay file\n");
        return;
    }
    fscanf( file, "%d", &soluongkhoa );
    for( int i = 0; i < soluongkhoa; i++ ) {
        fscanf( file, "%d", &dskhoa[i].maKhoa );
        if (fgets(dskhoa[i].tenKhoa, 40, file) != NULL) {
            // Đọc thành công, tiếp tục xử lý
            fgets(dskhoa[i].tenKhoa, 40, file);
            dskhoa[i].tenKhoa[ strlen(dskhoa[i].tenKhoa) ] = '\0';
            // printf("%s %d\n", dskhoa[i].tenKhoa, dskhoa[i].maKhoa );
        } else {
            // Đọc thất bại hoặc gặp kết thúc file
            printf("doc file fail\n" );
        }
    }
}
void gioithieu() {
    printf("\t ______________________________________________________________________________________________ \n");
    printf("\t|                                                                                              |\n");
    printf("\t|                                 DO AN PBL1: LAP TRINH TINH TOAN                              |\n");
    printf("\t|                                                                                              |\n");
    printf("\t|                       DE TAI: XAY DUNG UNG DUNG QUAN LY DANH SACH SINH VIEN                  |\n");
    printf("\t|                                                                                              |\n");
    printf("\t|                                                                                              |\n");
    printf("\t|                                        Giao vien huong dan: Nguyen Van Hieu                  |\n");
    printf("\t|                                                                                              |\n");
    printf("\t|                                                                                              |\n");
    printf("\t|         Sinh vien thuc hien:                                                                 |\n");
	printf("\t|                            Huynh Nhu Bao Nhan(23T_Nhat1)   - MSV: 102230034	               |\n");
    printf("\t|                            Vo Van Cuong (23T_Nhat1)        - MSV: 102230007	               |\n");
    printf("\t|                                                                                              |\n");
    printf("\t|______________________________________________________________________________________________|\n");
}

void Menu(){
    printf("\t                                 MENU\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("\t 1. Them sinh vien\n");
    printf("\t 2. Sap xep danh sach sinh vien\n");
    printf("\t 3. Xoa sinh vien\n");
    printf("\t 4. Tim kiem sinh vien\n");
    printf("\t 5. Cap ma sinh vien\n");
    printf("\t 6. Cap email\n");
    printf("\t 7. In danh sach sinh vien\n");
    printf("\t 8. Thoat\n");
    printf("---------------------------------------------------------------------------------\n");
    int n;
    printf("Vui long nhap lua chon: ");
    scanf("%d", &n);
    while(n < 1 || n > 8){
        printf("Vui long nhap lai!\n");
        scanf("%d", &n);
    }
    switch(n){
        case 1:
            NhapSinhVien();
            break;
        case 2:

            printf("Chua co\n");
            break;
        case 3:
            printf("Chua co\n");
            break;
        case 4:
            printf("Chua co\n");
            break;
        case 5:
            printf("Chua co\n");
            break;
        case 6:
            printf("Chua co\n");
            break;
        case 7:
            printf("Chua co\n");
            break;
    }
    }

void Sapxep(){
    printf("1. Sap xep theo khoa\n");
    printf("2. Sap xep theo ten\n");
    printf("3. Thoat\n");
    int n;
    do{
        printf("Ban chon: ");
        scanf("%d", &n);
        if(n < 1 || n > 3) printf("Vui long nhap lai!\n");
    }while(n < 1 || n > 3);
    switch(n){
        case 1:
            printf("Chua co\n");
            break;
        case 2:
           printf("Chua co\n");
            break;
        case 3:
            printf("Chua co\n");
            break;
    }
}