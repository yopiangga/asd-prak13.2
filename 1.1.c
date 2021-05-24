#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX 100

typedef struct {
	int NO;
	char Nama[10];
	int Nilai;
} siswa;

int n, pilihMenu;
int keyNo;
char keyNama[10];

int sortBy = 1;
int search;
siswa data[MAX], data2[MAX];

int main(){
	
	jumlahN();
	alokasi();
	
	do {
		copyData();
		menu();
	} while(pilihMenu != 4);
}

int jumlahN(){
	printf("%-15s", "Jumlah data "); printf(": ");
	scanf("%d", &n);
	fflush(stdin);
}

int alokasi(){
	int i;
	
	for(i=0; i<n; i++){
		printf("Data Array ke %d \n", i+1);
		printf("%-10s", "NO"); printf(": ");
		scanf("%d", &data2[i].NO);
		fflush(stdin);
		printf("%-10s", "Nama"); printf(": ");
		scanf("%s", &data2[i].Nama);
		fflush(stdin);
		printf("%-10s", "Nilai"); printf(": ");
		scanf("%d", &data2[i].Nilai);
		fflush(stdin);
	}
}

int copyData(){
	int i;
	
	for(i=0; i<n; i++){
		data[i].NO = data2[i].NO;
		strcpy(data[i].Nama, data2[i].Nama);
		data[i].Nilai = data2[i].Nilai;
	}
}

int menu(){
	printf("========================\n");
	printf(" MENU SEARCH\n");
	printf("========================\n");
	printf("1. Tampilkan Data\n");
	printf("2. Sequential\n");
	printf("3. Binary\n");
	printf("4. Keluar\n");
	printf("%-25s", "Pilih Menu"); printf(": ");
	scanf("%d", &pilihMenu);
	fflush(stdin);
	
	if(pilihMenu == 4)
		exit(0);
	
	switch(pilihMenu){
		case 1:
			modeUrut();
			if(sortBy != 3){
				selection();
				tampil(data);
			} else 
			    tampil(data2);
			break;
		case 2:
			sortBy = 1;
			selection();
			searchBy();
			sequential();
			break;
		case 3:
			sortBy = 1;
			selection();
			searchBy();
			binary();
			break;
	}
}

int modeUrut(){
	printf("========================\n");
	printf(" MENU URUT BY\n");
	printf("========================\n");
	printf("1. No\n");
	printf("2. Nama\n");
	printf("3. Tidak Urut\n");
	printf("%-25s", "Pilih Menu"); printf(": ");
	scanf("%d", &sortBy);
	fflush(stdin);
}

int searchBy(){
	printf("========================\n");
	printf(" MENU SEARCH BY\n");
	printf("========================\n");
	printf("1. No\n");
	printf("2. Nama\n");
	printf("%-25s", "Pilih Menu"); printf(": ");
	scanf("%d", &search);
	fflush(stdin);
	
	switch(search){
		case 1:
			cariNo();
			break;
		case 2:
			cariNama();
			break;
	}
}

int cariNo(){
	printf("%-25s", "Input Key"); printf(": ");
	scanf("%d", &keyNo);
	fflush(stdin);
}

int cariNama(){
	printf("%-25s", "Input Key"); printf(": ");
	scanf("%s", &keyNama);
	fflush(stdin);
}

int selection(){
	
	int i,j, x, kondisi = 0;
    for(i=0; i<n-1; i++){
        x = i;
        for(j = i+1; j<n; j++){
        	if(sortBy == 1)
				kondisi = data[j].NO < data[x].NO;	
			else if (sortBy == 2)
				kondisi = data[j].NO > data[x].NO;	
				
        	if(kondisi)
        		x = j;
		}
        tukar(&data[i], &data[x]);
    }
	
}

int tukar(int *a, int *b){
	int temp;
	
    temp = *a;
    *a = *b;
    *b = temp;
}

int tampil(siswa data[]){
	int i;
	printf("\n");
	printf("%-5s", "NO"); 
	printf("%-15s", "Nama");
	printf("%-15s", "Nilai");
	for(i=0; i<n; i++){
		printf("\n");
		printf("%-5d ", data[i].NO); 
		printf("%-15s ", data[i].Nama); 
		printf("%-15d ", data[i].Nilai);
	}
	printf("\n\n");
}

int sequential() {
	int length = n;
	int i, ketemu = 0, kondisi;
	
	for(i=0; i<length; i++){
		if(search == 1)
			kondisi = data[i].NO == keyNo;
		else
			kondisi = strcmpi(data[i].Nama, keyNama) == 0;
			
		if(kondisi){
			ketemu = 1;
			break;
		}	
	}
	
	if(ketemu)
		printf("%d adalah index dari data yang dicari\n", i);
	else 
		printf("Data tidak ditemukan\n");
}

int binary() {
	
	int length = n, kondisi;
	int ketemu = 0, L, R, M;
	
	L = 0;
	R = length - 1;
	
	if(strcmpi(data[R].Nama, keyNama) == 0 && search == 2){
		printf("%d adalah index dari data yang dicari\n", R);
	} else {
		while(L <= R){
			M = (L+R) / 2;
			if(search == 1)
				kondisi = data[M].NO == keyNo;
			else {
				kondisi = strcmpi(data[M].Nama, keyNama) == 0;
			}
				
			if(kondisi){
				ketemu = 1;
				break;
			}
			
			if(search == 1){
				if(keyNo < data[M].NO)
					R = M - 1;
				else if(keyNo > data[M].NO)
					L = M + 1;
			} else {
				if(strcmpi(keyNama, data[M].Nama) < 0)
					R = M - 1;
				else if(strcmpi(keyNama, data[M].Nama) > 0)
					L = M + 1;
			}
		}
		
		if(ketemu)
			printf("%d adalah index dari data yang dicari\n", M);
		else 
			printf("Data tidak ditemukan\n");
	}
	
}
