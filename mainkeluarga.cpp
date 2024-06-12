#include "keluarga.h"
#include <stdio.h>
#include <cstdlib>

int main() {
    Keluarga* root = NULL;    // Root awalnya kosong
   
    int pil;
    do {
        printf("\n[ Menu ]\n");
        printf("| 1. Tambah anggota keluarga\n");
        printf("| 2. Update status anggota keluarga\n");
        printf("| 3. Cek anggota keluarga\n");
        printf("| 4. Info keluarga\n");
        printf("| 5. Tampilkan pohon keluarga\n");
        printf("| 6. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pil);
        system("cls");
       
        switch (pil) {
            case 1:
                tambahAnggotaKeluarga(&root);
                break;
            case 2:
                if (root == NULL) {
                    printf("Pohon keluarga kosong! Tambahkan root terlebih dahulu.\n");
                } else {
                    updateStatus(root);
                }
                break;
            case 3:
                if (root == NULL) {
                    printf("Pohon keluarga kosong! Tambahkan root terlebih dahulu.\n");
                } else {
                    cekAnggotaKeluarga(root);
                }
                break;
            case 4:
                if (root == NULL) {
                    printf("Pohon keluarga kosong! Tambahkan root terlebih dahulu.\n");
                } else {
                    infoKeluarga(root);
                }
                break;
            case 5:
                if (root == NULL) {
                    printf("Pohon keluarga kosong! Tambahkan root terlebih dahulu.\n");
                } else {
                    tampilkanPohonKeluarga(root, 0);
                }
                break;
            case 6:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                break;
        }
    } while (pil != 6);
   
    return 0;
}

