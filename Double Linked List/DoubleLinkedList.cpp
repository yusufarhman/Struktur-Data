#include <iostream>
using namespace std;
#include <string>

struct Mahasiswa {
    string nama;
    string nim;
    string jurusan;
    string fakultas;

    Mahasiswa *next;
    Mahasiswa *prev;
};

Mahasiswa *head, *tail, *cur, *newNode, *del;

// Fungsi untuk menghitung panjang list
int hitungPanjang() {
    int jumlah = 0;
    cur = head;
    while(cur != NULL) {
        jumlah++;
        cur = cur->next;
    }
    return jumlah;
}

void CreateDoubleLinkedList(string nama, string nim, string jurusan, string fakultas) {
    head = new Mahasiswa;

    head->nama = nama;
    head->nim = nim;
    head->jurusan = jurusan;
    head->fakultas = fakultas;

    head->next = NULL;
    head->prev = NULL;

    tail = head;
};

void addFirst(string nama, string nim, string jurusan, string fakultas) {
    newNode = new Mahasiswa;

    newNode->nama = nama;
    newNode->nim = nim;
    newNode->jurusan = jurusan;
    newNode->fakultas = fakultas;

    newNode->next = head;
    newNode->prev = NULL;
    head->prev = newNode;
    head = newNode;
}

void addLast(string nama, string nim, string jurusan, string fakultas) {
    newNode = new Mahasiswa;

    newNode->nama = nama;
    newNode->nim = nim;
    newNode->jurusan = jurusan;
    newNode->fakultas = fakultas;

    newNode->next = NULL;
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
}

// Fungsi untuk menambah node di tengah
void addMiddle(string nama, string nim, string jurusan, string fakultas, int posisi) {
    if(posisi < 1 || posisi > hitungPanjang() + 1) {
        cout << "Posisi diluar jangkauan" << endl;
        return;
    }

    if(posisi == 1) {
        addFirst(nama, nim, jurusan, fakultas);
    } 
    else if(posisi == hitungPanjang() + 1) {
        addLast(nama, nim, jurusan, fakultas);
    }
    else {
        newNode = new Mahasiswa;
        newNode->nama = nama;
        newNode->nim = nim;
        newNode->jurusan = jurusan;
        newNode->fakultas = fakultas;

        cur = head;
        int nomor = 1;
        while(nomor < posisi - 1) {
            cur = cur->next;
            nomor++;
        }

        newNode->prev = cur;
        newNode->next = cur->next;
        cur->next->prev = newNode;
        cur->next = newNode;
    }
}

void changeFirst(string nama, string nim, string jurusan, string fakultas) {
    cur = head;
    cur -> nama = nama;
    cur -> nim = nim;
    cur -> jurusan = jurusan;
    cur -> fakultas = fakultas;
}

void changeLast(string nama, string nim, string jurusan, string fakultas) {
    cur = tail;
    cur -> nama = nama;
    cur -> nim = nim;
    cur -> jurusan = jurusan;
    cur -> fakultas = fakultas;
}

void changeMiddle(string nama, string nim, string jurusan, string fakultas, int posisi) {
    if(posisi < 1 || posisi > hitungPanjang()) {
        cout << "Posisi diluar jangkauan" << endl;
        return;
    }

    if(posisi == 1) {
        changeFirst(nama, nim, jurusan, fakultas);
    }
    else if(posisi == hitungPanjang()) {
        changeLast(nama, nim, jurusan, fakultas);
    }
    else {
        cur = head;
        int nomor = 1;
        while(nomor < posisi) {
            cur = cur->next;
            nomor++;
        }
        
        cur->nama = nama;
        cur->nim = nim;
        cur->jurusan = jurusan;
        cur->fakultas = fakultas;
    }
}


void delFirst() {
    del = head;
    head = head->next;
    head->prev = NULL;
    delete del;
}

void delLast() {
    del = tail;
    tail = tail->prev;
    tail->next = NULL;
    delete del;
}

void delMiddle(int posisi) {
    if(posisi < 1 || posisi > hitungPanjang()) {
        cout << "Posisi diluar jangkauan" << endl;
        return;
    }

    if(posisi == 1) {
        delFirst();
    }
    else if(posisi == hitungPanjang()) {
        delLast();
    }
    else {
        cur = head;
        int nomor = 1;
        while(nomor < posisi) {
            cur = cur->next;
            nomor++;
        }
        
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur;
    }
}

void PrintDoubleLinkedList() {
    cur = head;
    while (cur != NULL) {
        cout << "Nama : " << cur->nama << endl;
        cout << "NIM : " << cur->nim << endl;
        cout << "Jurusan : " << cur->jurusan << endl;
        cout << "Fakultas : " << cur->fakultas << endl;
        cout << endl;

        cur = cur->next;
    }
}

int main() {

    cout << "======= Membuat Node Pertama =======" << endl;
    CreateDoubleLinkedList("Rina", "23081010012", "Teknik Informatika", "Teknik");
    PrintDoubleLinkedList();

    cout << endl;

    cout << "======= Menambahkan Node di Awal =======" << endl;
    addFirst("Dewi", "23081010013", "Teknik Informatika", "Teknik");
    PrintDoubleLinkedList();

    cout << endl;

    cout << "======= Menambahkan Node di Tengah =======" << endl;
    addMiddle("Dicky", "23081010015", "Teknik Informatika", "Teknik", 2);
    PrintDoubleLinkedList();
    
    cout << endl;

    cout << "======= Menambahkan Node di Akhir =======" << endl;
    addLast("Rudi", "23081010014", "Teknik Informatika", "Teknik");
    PrintDoubleLinkedList();

    cout << endl;

    cout << "======= Mengganti Node di Awal =======" << endl;
    changeFirst("Reno", "23081010011", "Teknik Informatika", "Teknik");
    PrintDoubleLinkedList();

    cout << endl;

    cout << "======= Mengganti Node di Tengah =======" << endl;
    changeMiddle("Rahmad", "23081010016", "Teknik Informatika", "Teknik", 2);
    PrintDoubleLinkedList();

    cout << endl;

    cout << "======= Mengganti Node di Akhir =======" << endl;
    changeLast("Dico","23081010017", "Teknik Informatika", "Teknik");
    PrintDoubleLinkedList();

    cout << endl;

    cout << "======= Menghapus Node di Awal =======" << endl;
    delFirst();
    PrintDoubleLinkedList();

    cout << endl;

    cout << "======= Menghapus Node di Tengah =======" << endl;
    delMiddle(2);
    PrintDoubleLinkedList();

    cout << endl;

    cout << "======= Menghapus Node di Akhir =======" << endl;
    delLast();
    PrintDoubleLinkedList();

    return 0;
}
