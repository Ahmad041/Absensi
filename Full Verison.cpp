#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

/* Kelompok String Group*/
struct Absen {
	string nama;
	string kelas;
	string jurusan;
	string username;
	string password;
};

/* Fungsi login */
bool login(Absen &absen) {
	cout << "Masukan Username / Email	:";
	getline(cin, absen.username);
	cout << "Masukan Password	:";
	getline(cin, absen.password);

	// Cek apakah username/email dan password sesuai
	if (absen.username == "KeyWorld" && absen.password == "KeyWorld12") {
		return true;
	} else {
		return false;
	}
}

/* Menambahkan Absen */
void tambahAbsen(Absen &absen) {
	cout << "Masukkan nama: ";
	getline(cin, absen.nama);
	cout << "Masukkan kelas: ";
	getline(cin, absen.kelas);
	cout << "Masukkan jurusan: ";
	getline(cin, absen.jurusan);
}

/* Baca input Absen */
void bacaAbsen(Absen absen) {
	cout << "Nama: " << absen.nama << endl;
	cout << "Kelas: " << absen.kelas << endl;
	cout << "Jurusan: " << absen.jurusan << endl;
}

/* Menyimpan Absen */
void simpanAbsen(Absen absen) {
	ofstream fileAbsen;
	fileAbsen.open("absen.txt", ios::app);
	fileAbsen << absen.nama << endl;
	fileAbsen << absen.kelas << endl;
	fileAbsen << absen.jurusan << endl;
	fileAbsen.close();
	cout << "Data absen berhasil disimpan." << endl;
}

/* Menampilkan Data Absen */
void tampilkanAbsen() {
	ifstream fileAbsen("absen.txt");
	if (!fileAbsen) {
		cout << "File absen tidak ditemukan." << endl;
		return;
	}

	string namaFile, kelasFile, jurusanFile;
	cout << "Data absen:" << endl;
	cout << "Nama\t\t\t\tKelas\t\tJurusan" << endl;
	while (fileAbsen >> namaFile) {
		fileAbsen >> kelasFile;
		fileAbsen >> jurusanFile;
		cout << namaFile << "\t\t" << kelasFile << "\t\t" << jurusanFile << endl;
	}

	fileAbsen.close();
}

/* Cari Data Absen */

void cariAbsen() {
	ifstream inFile;
	inFile.open("absen.txt");
	string nama, kelas, jurusan, cariNama;
	cout << "Masukkan Nama yang ingin dicari: ";
	getline(cin, cariNama);
	bool found = false;
	cout << "Data Absen:" << endl;
	cout << "Nama\t\tKelas\t\tJurusan" << endl;
	while (inFile >> nama >> kelas >> jurusan) {
		if (nama == cariNama) {
			found = true;
			cout << nama << "\t\t" << kelas << "\t\t" << jurusan << endl;
		}
	}
	if (!found) {
		cout << "Data tidak ditemukan." << endl;
	}
	inFile.close();
}

/* Mengubah Data Absen */
void ubahAbsen(Absen &absen) {
	cout << "Masukkan nama baru: ";
	getline(cin, absen.nama);
	cout << "Masukkan kelas baru: ";
	getline(cin, absen.kelas);
	cout << "Masukkan jurusan baru: ";
	getline(cin, absen.jurusan);
}

/* Menghapus Data Absen */
void hapusAbsen(string nama) {
	ifstream fileAbsen("absen.txt");
	ofstream tempAbsen;
	tempAbsen.open("tempAbsen.txt", ios::app);
	string namaFile, kelasFile, jurusanFile;
	while (fileAbsen >> namaFile) {
		fileAbsen >> kelasFile;
		fileAbsen >> jurusanFile;
		if (namaFile != nama) {
			tempAbsen << namaFile << endl;
			tempAbsen << kelasFile << endl;
			tempAbsen << jurusanFile << endl;
		}
	}
	fileAbsen.close();
	tempAbsen.close();
	remove("absen.txt");
	rename("tempAbsen.txt", "absen.txt");
	cout << "Data absen berhasil dihapus." << endl;
}

/* Menu Utama Absen */
int main() {
	int pilihan;
    Absen absen;
    string nama;
    bool loggedIn = false;

    // Login
    while (!loggedIn) {
        loggedIn = login(absen);
        if (!loggedIn) {
            cout << "Username/Email dan password salah. Silakan coba lagi." << endl;
            cout<<endl;
        }
    }
	while (true) {
		system("CLS");
		cout << "\033[1;32m=========================" << endl;
		cout << "|       Menu Absen     |" << endl;
		cout << "=========================" << endl;
		cout << "| 1. Tambah data absen	|" << endl;
		cout << "| 2. Baca data absen	|" << endl;
		cout << "| 3. Simpan data absen	|" << endl;
		cout << "| 4. Lihat data absen	|" << endl;
		cout << "| 5. Ubah data absen	|" << endl;
		cout << "| 6. Hapus data absen	|" << endl;
		cout << "| 7. Cari data absen	|" << endl;
		cout << "| 8. Keluar	 	|" << endl;
		cout << "=========================" << endl;
		cout << "|Masukkan Pilihan Anda : ";
		cin >> pilihan;
		cout << "=========================\033[0m" << endl;
		cin.ignore();
		system("CLS");
		switch (pilihan) {
			case 1:
				tambahAbsen(absen);
				break;
			case 2:
				bacaAbsen(absen);
				break;
			case 3:
				simpanAbsen(absen);
				break;
			case 4:
				tampilkanAbsen();
				break;
			case 5:
				cout << "Masukkan nama yang akan diubah: ";
				getline(cin, nama);
				ubahAbsen(absen);
				break;
			case 6:
				cout << "Masukkan nama yang akan dihapus: ";
				getline(cin, nama);
				hapusAbsen(nama);
				break;
			case 7:
				cariAbsen();
				break;
			case 8:
				system("CLS");
				cout << "Terimakasih telah menggunakan fitur absen ini, aplikasi ini dibuat oleh KeyWorld." << endl;
				break;
			default:
				cout << "Pilihan salah." << endl;
		}
		cout << endl;
		system("PAUSE");
	}
	return 0;
}

