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

int main(){

}