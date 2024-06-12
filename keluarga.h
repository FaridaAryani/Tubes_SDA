#ifndef KELUARGA_H
#define KELUARGA_H

typedef struct Pasangan{
	char nama[100];
	char gender;
	char status;
	char infoNikah[20];
	struct Keluarga* cp;
	struct Pasangan* next; // Next pasangan in the double linked list
    struct Pasangan* prev; // Previous pasangan in the double linked list
} Pasangan;

typedef struct Keluarga {
    char nama[100];
    char gender;		// l = laki-laki, p = perempuan
    char status;        // status kehidupan (H = hidup, M = Meninggal)
    char infoNikah[20];
    struct Keluarga* nb;    // next brother
    struct Keluarga* pr;    // parent
    struct Keluarga* fs;    // first son
    Pasangan* pasangan;    // couple
} Keluarga;

Keluarga* buatKeluarga(char* nama, char gender, char status);
/* IS : Keluarga belum diinisialisasi pointer menunjuk tak tentu dan size berisi tak tentu
	FS : Mengalokasikan memori untuk keluarga yang akan ditampung sebagai tree keluarga
*/

Keluarga* cariKeluarga(Keluarga* keluarga, char* nama);
/* IS : Pointer keluarga masih di root dan tidak diketahui keluarga nya kosong atau tidak
	FS : Pointer keluarga menuju nama yang dicari dan diketuhui nodenya ada dimana
*/

void tambahAnak(Keluarga* parent, Keluarga* anakBaru);
/* IS : belum ada node yang menunjukkan anak atau anakBaru = NULL
	FS : Node baru ditambahkan sesuai peran dalam keluarga, hubungan dengan anggota lain diperbaharui
*/

void tambahPasangan(Keluarga* keluarga, char* nama, char gender, char status);
/* IS : belum ada node yang menunjukkan pasangan atau pasangan = NULL
	FS : Node baru ditambahkan sesuai peran dalam keluarga, hubungan dengan anggota lain diperbaharui
*/

void tambahAnggotaKeluarga(Keluarga** root);
/* IS : belum ada node di tree
	FS : Node baru ditambahkan sesuai peran dalam keluarga, hubungan dengan anggota lain diperbaharui
*/

void updateStatus(Keluarga* root);
/* IS : Status awal diinisialisasikan sebagai hidup
	FS : Status akhir menjadi meninggal
*/

void cekAnggotaKeluarga(Keluarga* root);
/* IS : tidak diketahui apakah anggota tersebut ada di keluarga atau tidak
	FS : Menghasilkan pesan apakah nama anggota keluarga ditemukan atau tidak
*/

void infoKeluarga(Keluarga* root);
/* IS : Belum diketahui keterangan dari anggota tersebut
	FS : Menghasilkan pesan yang berisi informasi mengenai status kehidupan dan kedudukan dalam keluarga
*/

void tampilkanPohonKeluarga(Keluarga* keluarga, int level);
/* IS : Pohon keluarga belum diketahui
	FS : Menampilkan pohon keluarga secara level-order
*/

#endif 
