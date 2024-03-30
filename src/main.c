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
    int khoa;
    int khoi;
    int lop;
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
int cnt;

SinhVien NhapSinhVien();
void Intro();
void Menu();
void NhapHoVaTen(struct fullname *sv);
void NhapNgaySinh(SinhVien *sv);
void NhapDiaChi(struct address *DiaChi);
void TimTheoTen();
void TimTheoID();
void DocFile();
void GhiFile();
void toUpperCase(char s[]);
void toLowerCase(char s[]);
void Sapxep(); 
void CapMSV( MSVandEmail* dsMSVandEmail[] );
void CapEmail( MSVandEmail* dsMSVandEmail[] );


int main() {
    Intro();
    Menu();
    return 0;
}

SinhVien NhapSinhVien() {
  SinhVien sv;
    int SL;
    printf("So sinh vien can them : ");
    scanf("%d",&SL);
    cnt = SL;
    int demnhap = 0 ;
    while(SL--)
    {
    printf("Nhap thong tin sinh vien thu: %d\n",++demnhap);
    printf("Xin Hay Nhap Lop : ");
    scanf("%d", &sv.lop);
    // DocFile(sv.lop);
    NhapHoVaTen(&sv.HovaTen);
    NhapNgaySinh(&sv);
    while(getchar() != '\n');
    printf("Xin Hay Nhap Gioi tinh: ");
    fgets(sv.gender, sizeof(sv.gender), stdin);
    sv.gender[strcspn(sv.gender, "\n")] = '\0';
    printf("Xin Hay Nhap Dia Chi:\n");
    NhapDiaChi(&sv.DiaChi);
    // GhiFile(sv.lop);
    }
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

void nameFile(char fileName[])
{
    fgets(fileName, 100, stdin);
    fileName[strlen(fileName) - 1] = '\0';
}

void GhiFile(char fileName[]) {
    FILE *sv;
    sv = fopen(fileName, "wb+");
    if (sv == NULL) {
        printf("Khong mo duoc file!\n");
        return;
    }
    int sumSv = 0; 
    int check = 0; 
    fwrite(&sumSv, sizeof(int), 1, sv);
    fwrite(&check, sizeof(int), 1, sv);
    for (int i = 0; i < sumSv; i++) {
        fwrite(&MSV[i], sizeof(MSVandEmail), 1, sv);
        fwrite(&listSV[i], sizeof(SinhVien), 1, sv);
    }
    fclose(sv);
}

void DocFile(char fileName[])
{
    FILE *sv;
    sv = fopen(fileName, "rb");
    if (sv == NULL)
    {
        printf("Khong mo duoc file!\n");
        return;
    }
    int sumSv = 0;
    int check = 0;
    fread(&sumSv, sizeof(int), 1, sv);
    fread(&check, sizeof(int), 1, sv);
    for (int i = 0; i < sumSv; i++)
    {
        fread(&MSV[i], sizeof(MSVandEmail), 1, sv);
        fread(&listSV[i], sizeof(SinhVien), 1, sv);
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
    for (int i = Dodai_HoVaTen - 1; i >= 0; i--) {
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
    printf("Ho: %s\n", sv->ho);
    printf("Ten: %s\n", sv->ten);
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




void CapMSV( MSVandEmail* dsMSVandEmail[]) {
    for (int i = 0; i < cnt; i++)
    {
        dsMSVandEmail[i]->MSSV = 1022300000  + i;
    }
}

void CapEmail( MSVandEmail* dsMSVandEmail[] ) {
    for (int i = 0; i < cnt; i++)
    {
        sprintf( dsMSVandEmail[i]->email, "%d", dsMSVandEmail[i]->MSSV );
        strcat( dsMSVandEmail[i]->email, "@sv1.dut.udn.vn");
    }
    
}


void Intro() {
    printf("\t ______________________________________________________________________________________________\n");
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
	printf("\t|                            Huynh Nhu Bao Nhan(23T_Nhat1)   - MSV: 102230034                  |\n");
    printf("\t|                            Vo Van Cuong (23T_Nhat1)        - MSV: 102230007                  |\n");
    printf("\t|                                                                                              |\n");
    printf("\t|______________________________________________________________________________________________|\n");
}

void Menu(){
    printf("\t                                 MENU                                          \n");
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
            Menu();
            break;
        case 2:
            Sapxep();
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
    printf("1. Sap xep theo ten\n");
    printf("2. Sap xep theo toan bo sinh vien\n");
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
            Menu();
            break;
    }
}