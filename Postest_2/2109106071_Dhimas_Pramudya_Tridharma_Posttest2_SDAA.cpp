#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Deklarasi Struct
struct Lahir{
    string Tempat;
    int tanggal;
    int bulan;
    int tahun;
};

struct Tentara{
    string Nama;
    float Tinggi;
    int ID_Tentara;
    string Divisi;
    Lahir TTL;
};

struct node{
    Tentara Data_TNI;
    node *next = NULL;
};

// Deklaris Variabel Global

int Last_Node, pilih, nambah, up;
node *head = NULL, *VarDelete;

bool Kosong(node *head){
    if (head == NULL){
        return true;
    }
    return false;
}
node *new_node(){
    // Membuat Node Baru
    node *nodebaru = new node;
    cout << "Nama\t\t : "; fflush(stdin);getline(cin, nodebaru->Data_TNI.Nama);
    cout << "Tinggi\t\t : "; cin >> nodebaru->Data_TNI.Tinggi;
    cout << "ID Tentara\t : "; cin >> nodebaru->Data_TNI.ID_Tentara;
    cout << "Divisi\t\t : "; fflush(stdin); getline(cin, nodebaru->Data_TNI.Divisi);
    cout << "Tempat Lahir\t : "; getline(cin, nodebaru->Data_TNI.TTL.Tempat);
    cout << "Tanggal Lahir\t : "; cin >> nodebaru->Data_TNI.TTL.tanggal;
    cout << "Bulan Lahir\t : "; cin >> nodebaru->Data_TNI.TTL.bulan;
    cout << "Tahun Lahir\t : "; cin >> nodebaru->Data_TNI.TTL.tahun;
    return nodebaru;
}

void Tampilkan(node *head){
    if (Kosong(head)){
        cout << "[Linked List Masih Kosong . . . ]" << endl;
        return;
    }
    cout << "=================================" << endl;
    cout << "[DATA TENTARA REPUBLIK INDONESIA]" << endl;
    cout << "=================================" << endl;
    int i = 0;  Last_Node = 0;
    node *temp = head;
    while (temp != NULL){
        cout << "\nData Ke- " << i+1 << "." << endl;
        cout << "Nama\t\t : " << temp->Data_TNI.Nama << endl;
        cout << "Tinggi\t\t : " << temp->Data_TNI.Tinggi << endl;
        cout << "ID_Tentara\t : " << temp->Data_TNI.ID_Tentara << endl;
        cout << "Divisi\t\t : " << temp->Data_TNI.Divisi << endl;
        cout << "TTL\t\t : " << temp->Data_TNI.TTL.Tempat << ", " << temp->Data_TNI.TTL.tanggal << "-" << temp->Data_TNI.TTL.bulan << "-" << temp->Data_TNI.TTL.tahun << endl;
        Last_Node++; i++;
        temp = temp->next;
    }
}
    
void Tambah_Data(node **head, int type){
    int posisi;
    if (type == 3){
        cout << "Tambah Data pada No "; cin >> posisi;
    }
    cout << "Banyak Data yang di Input : "; cin >> nambah;
    for (int i = 0; i < nambah; i++){
        cout << "Data Ke- " << i+1 << endl;
        node *nodebaru = new_node();
        if (type == 1){ // ADD FIRST
            if (Kosong(*head)){// Jika Data Kosong
                *head = nodebaru;
            }else{ // Jika sudah ada data
                nodebaru->next = *head;
                *head = nodebaru;
            }
        }else if (type == 2){
            if (Kosong(*head)){
                *head = nodebaru;
            }else{
                node *temp =  *head;
                while (temp->next != NULL){
                    temp = temp->next;
                }
                // menghubungkan node di akhir dengan node baru
                temp->next =  nodebaru;
            }
        }else if (type == 3){
            if (posisi > Last_Node){
                cout << "ERROR, Posisi Terlalu Jauh . . .\n";
                system("pause");
                return;
            }
            node *temp = *head;
            if (posisi == 1){
                if(Kosong(*head)){//Jika data masih kosong
                    *head = nodebaru;
                }else{
                    nodebaru->next =  *head;
                    *head = nodebaru;
                }
            }else{
                for (int i = 2; i < posisi; i++){
                    if (temp->next != NULL){
                        temp =  temp->next;
                    }
                }nodebaru->next =  temp->next;
                temp->next = nodebaru;
            }
        }Last_Node++;
        posisi++;    
    }cout << "\n[Data Berhasil Di Tambahkan . . .]" << endl;
    system("pause");
}
    
void Hapus_Data(node **head, int type){
    if (Kosong(*head)){
        cout << "[Linked List Masih Kosong . . . ]" << endl;
        system("pause");
        return;
    }
    if (type == 1){ // Delete First
        VarDelete = *head;
        *head = (*head)->next;
        delete VarDelete;
    }else if (type == 2){// Delete Last
        if ((*head)->next == NULL){
            *head = NULL;
            return;
        }
        node *temp = *head;
        while (temp->next->next != NULL){
            temp = temp->next;
        }
        VarDelete = temp->next;
        temp->next = NULL;
        delete VarDelete;
    }else if (type == 3){
        node *temp = *head;
        int posisi;
        cout << "Hapus Data Pada Posisi : "; cin >> posisi;
        if (posisi == 1){
            *head = temp->next;
        }else{
            if (posisi < 1 || posisi > Last_Node){
                cout << "[Data yang anda cari tidak di temukan . . .]" << endl;
                system("pause");
                return;
            }
            node *Hapus = temp;
            for (int i = 1; Hapus != NULL && i < posisi; i++){
                Hapus = Hapus->next;
            }
            for (int i = 1; temp != NULL && i < posisi-1; i++){
                temp = temp->next;
            }
            temp->next = temp->next->next;
            free(Hapus);
        }
    }
    Last_Node--;
    cout << "\n[Data Berhasil Di Hapus . . .]" << endl;
    system("pause");
}
    
    
void Update_Data(node **head){
    if(Kosong(*head)){
        cout << "[Linked List Masih Kosong . . . ]" << endl;
        system("pause");
        return;
    }
    cout << "Pilih Data yang ingin di Update : "; cin >> pilih;
    node *temp = *head;
    if (pilih > 0 && pilih <= Last_Node){
        for (int i =1; i < pilih; i++){
            temp = temp->next;
        }
        cout << "Nama\t\t : "; fflush(stdin);getline(cin, temp->Data_TNI.Nama);
        cout << "Tinggi\t\t : "; cin >> temp->Data_TNI.Tinggi;
        cout << "ID Tentara\t : "; cin >> temp->Data_TNI.ID_Tentara;
        cout << "Divisi\t\t : "; fflush(stdin); getline(cin, temp->Data_TNI.Divisi);
        cout << "Tempat Lahir\t : "; getline(cin, temp->Data_TNI.TTL.Tempat);
        cout << "Tanggal Lahir\t : "; cin >> temp->Data_TNI.TTL.tanggal;
        cout << "Bulan Lahir\t : "; cin >> temp->Data_TNI.TTL.bulan;
        cout << "Tahun Lahir\t : "; cin >> temp->Data_TNI.TTL.tahun;
    }
    else{
        cout << "[Data Yang Anda Cari Tidak di Temukan . . .]" << endl;
    }
    cout << "\n[Data Berhasil Di Update . . .]" << endl;
    system("pause");
}
    
int main(){
    int pilih;
    while (pilih != 9){
        system("cls");
        cout << "========================\n";
        cout << "[Menu Pendataan Tentara]" << endl;
        cout << "[1] Lihat Data Tentara" << endl;
        cout << "[2] Tambah Data Tentara di Awal" << endl;
        cout << "[3] Tambah Data Tentara di Akhir" << endl;
        cout << "[4] Tambah Data Tentara Spesifik" << endl;
        cout << "[5] Hapus Data Tentara di Awal" << endl;
        cout << "[6] Hapus Data Tentara di Akhir" << endl;
        cout << "[7] Hapus Data Tentara Spesifik" << endl;
        cout << "[8] Edit Data Tentara" << endl;
        cout << "[9] Exit Program" << endl;
        cout << "========================\n";
        cout << " >> ";
        cin >> pilih;
        switch (pilih){
        // fungsi menampilkan ada di setiap pilihan agar menampilkan data yang udah ada sebelum nya
        case 1:
            Tampilkan(head);system("Pause");break;
        case 2:
            Tampilkan(head);
            Tambah_Data(&head, 1);break;
        case 3:
            Tampilkan(head);
            Tambah_Data(&head, 2);break;
        case 4:
            Tampilkan(head);
            Tambah_Data(&head, 3);break;
        case 5:
            Tampilkan(head);
            Hapus_Data(&head, 1);break;
        case 6:
            Tampilkan(head);
            Hapus_Data(&head, 2);break;
        case 7:
            Tampilkan(head);
            Hapus_Data(&head, 3);break;
        case 8:
            Tampilkan(head);
            Update_Data(&head); break;
        case 9:cout << "[Terima Kasih Telah Mendaftar semoga beruntung . . . ]" << endl;break;
        default:
            cout << "Pilihan Anda tidak Tersedia . . ." << endl;
            break;
        }
    }
    
}