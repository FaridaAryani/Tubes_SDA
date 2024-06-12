#include "keluarga.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Keluarga* buatKeluarga(char* nama, char gender, char status) {
    Keluarga* keluargaBaru = (Keluarga*)malloc(sizeof(Keluarga));
    strcpy(keluargaBaru->nama, nama);
    keluargaBaru->gender = gender;
    keluargaBaru->status = status;
    strcpy(keluargaBaru->infoNikah, "Belum Menikah");
    keluargaBaru->pasangan = NULL;
    keluargaBaru->nb = NULL;
    keluargaBaru->fs = NULL;
    keluargaBaru->pr = NULL;
    return keluargaBaru;
}

Pasangan* cariPasangan(Pasangan* pasangan, char* nama) {
    Pasangan* current = pasangan;
    while (current != NULL) {
        if (strcmp(current->nama, nama) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Keluarga* cariKeluarga(Keluarga* keluarga, char* nama) {
    if (keluarga == NULL) {
        return NULL;
    }

    if (strcmp(keluarga->nama, nama) == 0) {
        return keluarga;
    }

    Pasangan* pasangan = cariPasangan(keluarga->pasangan, nama);
    if (pasangan != NULL) {
        return (Keluarga*)pasangan;
    }
    
    Keluarga* result = cariKeluarga(keluarga->fs, nama);
    if (result != NULL) {
        return result;
    }

    result = cariKeluarga(keluarga->nb, nama);
    if (result != NULL) {
        return result;
    }

    return NULL;
}

void tambahAnak(Keluarga* parent, Keluarga* anakBaru) {
    if (parent->fs == NULL) {
        parent->fs = anakBaru;
    } else {
        Keluarga* temp = parent->fs;
        while (temp->nb != NULL) {
            temp = temp->nb;
        }
        temp->nb = anakBaru;
    }
    anakBaru->pr = parent;
}

void tambahPasangan(Keluarga* keluarga, char* nama, char gender, char status) {
    if (keluarga->pasangan != NULL) {
        printf("%s sudah memiliki pasangan!\n", keluarga->nama);
        return;
    }

    if ((keluarga->gender == 'L' || keluarga->gender == 'l') && (gender == 'L' || gender == 'l')) {
        printf("Kepala keluarga laki-laki harus memiliki pasangan perempuan!\n");
        return;
    }

    if ((keluarga->gender == 'P' || keluarga->gender == 'p') && (gender == 'P' || gender == 'p')) {
        printf("Kepala keluarga perempuan harus memiliki pasangan laki-laki!\n");
        return;
    }

    Pasangan* pasanganBaru = (Pasangan*)malloc(sizeof(Pasangan));
    if (pasanganBaru == NULL) {
        printf("Gagal mengalokasikan memori untuk pasangan baru!\n");
        return;
    }

    strcpy(pasanganBaru->nama, nama);
    pasanganBaru->gender = gender;
    pasanganBaru->status = status;
    strcpy(pasanganBaru->infoNikah, "Menikah");
    keluarga->pasangan = pasanganBaru;
    pasanganBaru->cp = keluarga;
    pasanganBaru->next = NULL;  // Inisialisasi next ke NULL
    
    strcpy(keluarga->infoNikah, "Menikah");
}


void tambahAnggotaKeluarga(Keluarga** root) {
    char nama[100], gender, status, jenis[100], dari[100];

    printf("Masukkan nama: ");
    scanf(" %99[^\n]", nama);
    getchar(); // Membersihkan buffer input dari newline

    Keluarga* cekNama = cariKeluarga(*root, nama);
    if (cekNama != NULL) {
        printf("%s sudah ada di keluarga, nama tidak boleh sama!\n", nama);
        return;
    }

    printf("Masukkan jenis kelamin (L untuk laki-laki, P untuk perempuan): ");
    scanf(" %c", &gender);
    getchar(); // Membersihkan buffer input dari newline

    printf("Masukkan status (H untuk hidup, M untuk meninggal): ");
    scanf(" %c", &status);
    getchar(); // Membersihkan buffer input dari newline

    if (*root == NULL) {
        *root = buatKeluarga(nama, gender, status);
        printf("Root keluarga berhasil ditambahkan!\n");
        return;
    }

    printf("Sebagai (anak/pasangan): ");
    scanf(" %99[^\n]", jenis);
    getchar(); // Membersihkan buffer input dari newline

    printf("Dari (nama orang tua/pasangan): ");
    scanf(" %99[^\n]", dari);
    getchar(); // Membersihkan buffer input dari newline

    Keluarga* target = cariKeluarga(*root, dari);
    if (target == NULL) {
        printf("Orang tua/pasangan tidak ditemukan!\n");
        return;
    }
    
    printf("Menambahkan %s sebagai %s dari %s\n", nama, jenis, dari);  // Debugging

    if (strcmp(jenis, "anak") == 0) {
        Keluarga* anakBaru = buatKeluarga(nama, gender, status);
        tambahAnak(target, anakBaru);
        printf("Anggota keluarga berhasil ditambahkan!\n");
    } else if (strcmp(jenis, "pasangan") == 0) {
        tambahPasangan(target, nama, gender, status);
        printf("Anggota keluarga berhasil ditambahkan!\n");
    } else {
        printf("Jenis hubungan tidak valid!\n");
    }
}

void updateStatus(Keluarga* root) {
    char nama[50];
    printf("Masukkan nama anggota keluarga: ");
    scanf(" %49[^\n]", nama);
    getchar(); // Membersihkan buffer input

    Keluarga* keluarga = cariKeluarga(root, nama);
    if (keluarga == NULL) {
        printf("Anggota keluarga tidak ditemukan!\n");
        return;
    }

    if (keluarga->status == 'M' || keluarga->status == 'm') {
        printf("%s memang sudah terdata meninggal.\n", nama);
    } else {
        keluarga->status = 'M';
        printf("Status anggota keluarga berhasil diupdate menjadi meninggal!\n");
    }
}

void cekRole(Keluarga* keluarga, Keluarga* ancestor, char* nama, char* role) {
	if (ancestor == NULL) {
        strcpy(role, "Tidak ditemukan");
        return;
    }

    // Cek apakah node tersebut adalah kepala keluarga
    if (strcmp(ancestor->nama, nama) == 0) {
        strcpy(role, "Kepala Keluarga");
        return;
    }
    
    if (strcmp(ancestor->pasangan->nama, nama) == 0) {
    	strcpy(role, "Istri Kepala Keluarga");
    	return;
	}

    // Cek apakah node tersebut adalah anak dari ancestor
    Keluarga* temp = ancestor->fs;
    while (temp != NULL) {
        if (strcmp(temp->nama, nama) == 0) {
            strcpy(role, (ancestor == keluarga) ? "Anak Kepala Keluarga" : "Anak");
            return;
        }

        // Cek apakah node tersebut adalah pasangan dari anak ancestor
        if (temp->pasangan != NULL && strcmp(temp->pasangan->nama, nama) == 0) {
            strcpy(role, (temp->gender == 'L' || temp->gender == 'l') ? "Istri Anak" : "Suami Anak");
            return;
        }

        temp = temp->nb;
    }
    
    Keluarga* tem = ancestor->fs->fs;
     while (tem != NULL) {
        if (strcmp(tem->nama, nama) == 0) {
            strcpy(role, (ancestor == keluarga) ? "Cucu Kepala Keluarga" : "Cucu");
            return;
        }

        // Cek apakah node tersebut adalah pasangan dari anak ancestor
        if (tem->pasangan != NULL && strcmp(tem->pasangan->nama, nama) == 0) {
            strcpy(role, (tem->gender == 'L' || tem->gender == 'l') ? "Istri Cucu" : "Suami Cucu");
            return;
        }
        temp = temp->nb;
    }
    
    Keluarga* buyut = ancestor->fs->fs->fs;
     while (buyut != NULL) {
        if (strcmp(buyut->nama, nama) == 0) {
            strcpy(role, (ancestor == keluarga) ? "Anak Kepala Keluarga" : "Anak");
            return;
        }

        // Cek apakah node tersebut adalah pasangan dari anak ancestor
        if (buyut->pasangan != NULL && strcmp(buyut->pasangan->nama, nama) == 0) {
            strcpy(role, (buyut->gender == 'L' || buyut->gender == 'l') ? "Istri Anak" : "Suami Anak");
            return;
        }

        buyut = buyut->nb;
    }

    // Jika nama tidak ditemukan di keturunan ancestor saat ini, set peran ke "Tidak ditemukan"
    strcpy(role, "Tidak ditemukan");
}

void cekAnggotaKeluarga(Keluarga* root) {
    char nama[100];
    printf("Masukkan nama anggota keluarga yang ingin diperiksa: ");
    scanf(" %99[^\n]", nama);
    getchar(); // Membersihkan buffer input

    Keluarga* keluarga = cariKeluarga(root, nama);
    if (keluarga == NULL) {
        printf("Anggota keluarga tidak ditemukan!\n");
        return;
    }

    char role[50];
    cekRole(root, root, nama, role);
    printf("Peran %s dalam keluarga adalah: %s\n", nama, role);
}

void infoKeluarga(Keluarga* root) {
    char nama[50];
    printf("Masukkan nama anggota keluarga: ");
    getchar();
    fgets(nama, sizeof(nama), stdin);
    size_t length = strlen(nama);
    if (length > 0 && nama[length - 1] == '\n') {
        nama[length - 1] = '\0';
    }

    Keluarga* keluarga = cariKeluarga(root, nama);
    if (keluarga != NULL) {
        printf("Nama: %s\n", keluarga->nama);
        printf("Jenis Kelamin: %s\n", (keluarga->gender == 'L' || keluarga->gender == 'l') ? "Laki-laki" : "Perempuan");
        printf("Status: %s\n", (keluarga->status == 'H' || keluarga->status == 'h') ? "Hidup" : "Meninggal");
		
        char role[50];
        cekRole(root, root, nama, role);
        printf("Sebagai: %s dari keluarga %s.\n", role, root->nama);

        if (keluarga->pasangan) {
            printf("Status Pernikahan: %s\n", keluarga->infoNikah);
        } else {
            printf("Status Pernikahan: Belum Menikah\n");
        }
    } else {
        printf("Anggota keluarga tidak ditemukan!\n");
    }
}

void tampilkanPohonKeluarga(Keluarga* keluarga, int level) {
    if (keluarga == NULL) {
        return;
    }

    for (int i = 0; i < level; i++) {
        printf(" ");
    }

    printf("%s (%s)\n", keluarga->nama, (keluarga->status == 'H' || keluarga->status == 'h') ? "Hidup" : "Meninggal");

    if (keluarga->pasangan != NULL) {
        for (int i = 0; i < level; i++) {
            printf(" ");
        }
        printf("Pasangan: %s (%s)\n", keluarga->pasangan->nama, (keluarga->pasangan->status == 'H' || keluarga->pasangan->status == 'h') ? "Hidup" : "Meninggal");
    }

    if (keluarga->fs != NULL) {
        tampilkanPohonKeluarga(keluarga->fs, level + 1);
    }

    if (keluarga->nb != NULL) {
        tampilkanPohonKeluarga(keluarga->nb, level);
    }
}
