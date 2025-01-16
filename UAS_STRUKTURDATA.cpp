#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// Struktur Buku
struct Book {
    int id;
    string title;
    string author;
    int year;
    Book *next;
};

Book *head = nullptr; // Pointer awal Linked List

// Fungsi untuk membuat buku baru
Book *createBook(int id, const string &title, const string &author, int year) {
    Book *newBook = new Book;
    newBook->id = id;
    newBook->title = title;
    newBook->author = author;
    newBook->year = year;
    newBook->next = nullptr;
    return newBook;
}

// Fungsi untuk menambahkan buku ke Linked List
void tambahBuku(int id, const string &title, const string &author, int year) {
    Book *newBook = createBook(id, title, author, year);
    if (head == nullptr) {
        head = newBook;
    } else {
        Book *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
    cout << "\nBuku berhasil ditambahkan!\n";
}

// Fungsi untuk menampilkan semua buku
void tampilkanBuku() {
    if (head == nullptr) {
        cout << "\nTidak ada buku dalam perpustakaan.\n";
        return;
    }
    Book *temp = head;
    cout << "\n+-----------------------------------------------------------------+\n";
    cout << "|                              Daftar Buku                          |\n";
    cout << "+-------------------------------------------------------------------+\n";
    cout << "| ID     | Judul                     | Penulis              | Tahun |\n";
    cout << "+-------------------------------------------------------------------+\n";
    while (temp != nullptr) {
        cout << "| " << setw(4) << temp->id << " | "
             << setw(25) << temp->title << " | "
             << setw(20) << temp->author << " | "
             << setw(5) << temp->year << " |\n";
        temp = temp->next;
    }
    cout << "+---------------------------------------------------------------+\n";
}

// Fungsi untuk mencari buku berdasarkan ID
Book *cariBuku(int id) {
    Book *temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Fungsi untuk menghapus buku
void hapusBuku(int id) {
    if (head == nullptr) {
        cout << "\nPerpustakaan kosong. Tidak ada buku yang bisa dihapus.\n";
        return;
    }

    if (head->id == id) {
        Book *temp = head;
        head = head->next;
        delete temp;
        cout << "\nBuku berhasil dihapus!\n";
        return;
    }

    Book *temp = head;
    while (temp->next != nullptr && temp->next->id != id) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << "\nBuku dengan ID " << id << " tidak ditemukan.\n";
    } else {
        Book *toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "\nBuku berhasil dihapus!\n";
    }
}

// Fungsi untuk memperbarui buku
void perbaruiBuku(int id) {
    Book *book = cariBuku(id);
    if (book == nullptr) {
        cout << "\nBuku dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    cout << "\nMasukkan judul baru: ";
    cin.ignore();
    getline(cin, book->title);

    cout << "Masukkan penulis baru: ";
    getline(cin, book->author);

    cout << "Masukkan tahun baru: ";
    cin >> book->year;

    cout << "\nBuku berhasil diperbarui!\n";
}

// Fungsi untuk menyimpan data ke file
void simpanKeFile() {
    ofstream file("library.txt");
    if (!file) {
        cout << "\nGagal membuka file untuk menyimpan data.\n";
        return;
    }

    Book *temp = head;
    while (temp != nullptr) {
        file << temp->id << "\n"
             << temp->title << "\n"
             << temp->author << "\n"
             << temp->year << "\n";
        temp = temp->next;
    }

    file.close();
    cout << "\nData berhasil disimpan ke file!\n";
}

// Fungsi untuk memuat data dari file
void muatDariFile() {
    ifstream file("library.txt");
    if (!file) {
        cout << "\nTidak ada file data untuk dimuat.\n";
        return;
    }

    while (!file.eof()) {
        int id, year;
        string title, author;

        file >> id;
        file.ignore();
        getline(file, title);
        getline(file, author);
        file >> year;
        file.ignore();

        if (file.fail()) break;
        tambahBuku(id, title, author, year);
    }

    file.close();
    cout << "\nData berhasil dimuat dari file!\n";
}

// Fungsi untuk menghitung total buku
void hitungTotalBuku() {
    int total = 0;
    Book *temp = head;
    while (temp != nullptr) {
        total++;
        temp = temp->next;
    }
    cout << "\nTotal buku dalam perpustakaan: " << total << "\n";
}

// Fungsi untuk menampilkan menu utama
void tampilkanMenu() {
    cout << "\n===============================================================\n";
    cout << "                   Sistem Perpustakaan                        \n";
    cout << "===============================================================\n";
    cout << "1. Tambah Buku\n";
    cout << "2. Tampilkan Semua Buku\n";
    cout << "3. Cari Buku Berdasarkan ID\n";
    cout << "4. Hapus Buku\n";
    cout << "5. Perbarui Buku\n";
    cout << "6. Simpan Data ke File\n";
    cout << "7. Muat Data dari File\n";
    cout << "8. Hitung Total Buku\n";
    cout << "9. Keluar\n";
    cout << "===============================================================\n";
    cout << "Pilihan Anda: ";
}

// Fungsi utama
int main() {
    int pilihan, id, tahun;
    string judul, penulis;

    muatDariFile();

    do {
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "\nMasukkan ID Buku: ";
                cin >> id;
                cin.ignore();
                cout << "Masukkan Judul Buku: ";
                getline(cin, judul);
                cout << "Masukkan Penulis Buku: ";
                getline(cin, penulis);
                cout << "Masukkan Tahun Terbit: ";
                cin >> tahun;

                tambahBuku(id, judul, penulis, tahun);
                break;

            case 2:
                tampilkanBuku();
                break;

            case 3:
                cout << "\nMasukkan ID Buku yang Dicari: ";
                cin >> id;
                {
                    Book *buku = cariBuku(id);
                    if (buku != nullptr) {
                        cout << "\nBuku Ditemukan:\n";
                        cout << "ID: " << buku->id << "\n"
                             << "Judul: " << buku->title << "\n"
                             << "Penulis: " << buku->author << "\n"
                             << "Tahun: " << buku->year << "\n";
                    } else {
                        cout << "\nBuku dengan ID " << id << " tidak ditemukan.\n";
                    }
                }
                break;

            case 4:
                cout << "\nMasukkan ID Buku yang Ingin Dihapus: ";
                cin >> id;
                hapusBuku(id);
                break;

            case 5:
                cout << "\nMasukkan ID Buku yang Ingin Diperbarui: ";
                cin >> id;
                perbaruiBuku(id);
                break;

            case 6:
                simpanKeFile();
                break;

            case 7:
                muatDariFile();
                break;

            case 8:
                hitungTotalBuku();
                break;

            case 9:
                cout << "\nKeluar dari program.\n";
                simpanKeFile();
                break;

            default:
                cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
        }
    } 
    while (pilihan != 9);
    return 0;
}