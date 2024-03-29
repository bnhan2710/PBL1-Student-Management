#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void gioithieu();

void Menu();
// void ThemSinhvien();
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
int main(){
	gioithieu();
    Menu();
    return 0;
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
            printf("Chua co\n");
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
    }   
    while(n < 1 || n > 3);
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
// void Sapxeptheokhoa(){
//     printf("Chua co\n");
// }
// void Sapxeptheoten(){
//     printf("Chua co\n");
// }

