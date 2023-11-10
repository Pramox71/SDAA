#include <iostream>
#include <windows.h>
#include <cctype>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

 //=========================================//
//                  AKUN                   //

struct Data{
    string username;
    string password;
    string nama_user;
};

struct akun{
    Data user;
    akun *next;
    akun *prev;
};

 //=========================================//
//                  GAME                   //
struct game{
    string nama_game;
	string platform;
	int stok;
	int harga;
	int id;
};

struct node{
    game data_disc;
    node *next;
    node *prev;
};

 //=========================================//
//                Transaksi                 //
struct Transaksi{
    string nama;
    string nama_game;
    string platform;
    string status;
    int jumlah;
    int harga;
};

struct trans{
    Transaksi data_trans;
    trans *front;
    trans *rear;
};

 //=========================================//
//            Riwayat Transaksi            //

struct riwayat{
    string nama;
    string nama_game;
    string platform;
    string status;
    int jumlah;
    int harga;
};

struct rw{
    riwayat data_transaksi;
    rw *next = NULL;
};

string nama_pemesan;
game data_game[50], temp;
node *head = NULL, *tail = NULL, *vardelete;
akun *head_akun = NULL, *tail_akun = NULL;
trans *head_trans = NULL, *tail_trans = NULL;
rw *head_rw = NULL;

int pilih, Last_user, Last_game = 0, nambah, lanjut, urut, antrian, riwayat_pesan;
// Bool game
bool game_sort, id_game;

void CSV_Game(node **head, node **tail){
    Last_game = 0;
    string baris, elemen;
    ifstream file;
    stringstream ss;
    file.open("game.csv");
    node *terakhir;
    bool pertama = true;

    while (getline(file, baris)){
        ss.str(baris);
        node *game_baru = new node();
        for (int i = 0; getline(ss, elemen, ','); i++){
            if(i == 0){
                game_baru->data_disc.nama_game = elemen;
            }else if(i == 1){
                game_baru->data_disc.platform = elemen;
            }else if(i == 2){
                game_baru->data_disc.stok = stoi(elemen);
            }else if(i == 3){
                game_baru->data_disc.harga = stoi(elemen);
            }else if(i == 4){
                game_baru->data_disc.id = stoi(elemen);
                game_baru->next = NULL;
                if(*head == NULL){
                    game_baru->prev = NULL;
                    *head = game_baru;
                    terakhir = game_baru;
                    Last_game++;
                }else{
                    game_baru->prev = terakhir;
                    terakhir->next = game_baru;
                    Last_game++;
                }
            }
        }
        *tail = game_baru;
        if (pertama){
            pertama = false;
        }else{
            terakhir = terakhir->next;
        }
        ss.clear();
    }
}

void game_csv(node *head){
    ofstream out("game.csv");
    while (head != NULL){
        out << head->data_disc.nama_game << ",";
        out << head->data_disc.platform << ",";
        out << head->data_disc.stok << ",";
        out << head->data_disc.harga << ",";
        out << head->data_disc.id << endl;
        head = head->next;
    }
    out.close();
}

void CSV_akun(akun **head_akun, akun **tail_akun){
    Last_user = 0;
    string baris, elemen;
    ifstream file;
    stringstream ss;
    file.open("akun.csv");
    akun *terakhir;
    bool pertama = true;

    while (getline(file, baris)){
        ss.str(baris);
        akun *akun_baru = new akun();
        for (int i = 0; getline(ss, elemen, ','); i++){
            if(i == 0){
                akun_baru->user.nama_user = elemen;
            }else if(i == 1){
                akun_baru->user.username = elemen;
            }else if(i == 2){
                akun_baru->user.password = elemen;
                akun_baru->next = NULL;
                if(*head_akun == NULL){
                    akun_baru->prev = NULL;
                    *head_akun = akun_baru;
                    terakhir = akun_baru;
                    Last_user++;
                }else{
                    akun_baru->prev = terakhir;
                    terakhir->next = akun_baru;
                    Last_user++;
                }
            }
        }
        *tail_akun = akun_baru;
        if (pertama){
            pertama = false;
        }else{
            terakhir = terakhir->next;
        }
        ss.clear();
    }
}

void akun_csv(akun *head_akun){
    ofstream out("akun.csv");
    while (head_akun != NULL){
        out << head_akun->user.nama_user << ",";
        out << head_akun->user.username << ",";
        out << head_akun->user.password << endl;
        head_akun = head_akun->next;
    }
    out.close();
}

void CSV_riwayat(rw **head_rw){
    riwayat_pesan = 0;
    string baris, elemen;
    ifstream file;
    stringstream ss;
    file.open("riwayat.csv");
    rw *terakhir;
    bool pertama = true;

    while (getline(file, baris)){
        ss.str(baris);
        rw *rw_baru = new rw();
        for (int i = 0; getline(ss, elemen, ','); i++){
            if(i == 0){
                rw_baru->data_transaksi.nama_game = elemen;
            }else if(i == 1){
                rw_baru->data_transaksi.nama = elemen;
            }else if(i == 2){
                rw_baru->data_transaksi.platform = elemen;
            }else if(i == 3){
                rw_baru->data_transaksi.status = elemen;
            }else if(i == 4){
                rw_baru->data_transaksi.jumlah = stoi(elemen);
            }else if(i == 5){
                rw_baru->data_transaksi.harga = stoi(elemen);
                if(*head_rw == NULL){
                    *head_rw = rw_baru;
                    Last_user++;
                }else{
                    terakhir = *head_rw;
                    while (terakhir->next != NULL){
                        terakhir = terakhir->next;
                    }
                    terakhir->next = rw_baru;
                }
            }
        }
        if (pertama){
            pertama = false;
        }else{
            terakhir = terakhir->next;
        }
        ss.clear();
    }
}

void riwayat_csv(rw *head_rw){
    ofstream out("riwayat.csv");
    while (head_rw != NULL){
        out << head_rw->data_transaksi.nama_game << ",";
        out << head_rw->data_transaksi.nama << ",";
        out << head_rw->data_transaksi.platform << ",";
        out << head_rw->data_transaksi.status << ",";
        out << head_rw->data_transaksi.jumlah << ",";
        out << head_rw->data_transaksi.harga << endl;
        head_rw = head_rw->next;
    }
    out.close();
}

void display_game(node *head, node *tail){
    cout<<"|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|\n";
    cout<<"|                          DATA KASET GAME YANG TERSEDIA                           |\n";
    cout<<"|==================================================================================|\n";
	cout<<"|  No  |           Game           |    ID    |  Stok  |   Harga(Rp)   |  Platform  |\n";
	cout<<"|==================================================================================|\n";
    if (head == NULL){
    cout << "\n  [Table still empty]\n" << endl;
    return;
    }
    int i = 0; Last_game = 0;
    node *temp = head;
    while (temp != NULL){
        cout<<"| "<<setiosflags(ios::left)<<setw(5)<<i+1<<"|";
        cout<<" "<<setiosflags(ios::left)<<setw(25)<<temp->data_disc.nama_game<<"|";
        cout<<" "<<setiosflags(ios::left)<<setw(9)<<temp->data_disc.id<<"|";
        cout<<" "<<setiosflags(ios::left)<<setw(7)<<temp->data_disc.stok<<"|";
        cout<<" "<<setiosflags(ios::left)<<setw(14)<<temp->data_disc.harga<<"|";
        cout<<" "<<setiosflags(ios::left)<<setw(11)<<temp->data_disc.platform<<"|";
        cout<<"\n|==================================================================================|\n";
        Last_game++; i++;
        temp = temp->next;
    }
    game_csv(head);
}

void display_antrian(trans *head_trans, trans *tail_trans){
    if (head_trans == NULL){
        cout << "\n Antrian Masih Kosong" << endl;
        return;
    }
    int i = 0; antrian = 0;
    trans *temp = head_trans;
    while (temp != NULL){
    	cout << "---------------------------------------------" <<endl;
        cout << " Antrian Ke- " << i + 1 << endl;
        cout << " Game           : " << temp->data_trans.nama_game << endl;
        cout << " Nama Pemesan   : " << temp->data_trans.nama << endl;
        cout << " Platform       : " << temp->data_trans.platform << endl;
        cout << " status         : " << temp->data_trans.status << endl;
        cout << " Banyak Pesanan : " << temp->data_trans.jumlah << endl;
        cout << " Total Harga    : " << temp->data_trans.harga << endl;
        cout << "---------------------------------------------" <<endl;
        antrian++; i++;
        temp = temp->front;
    }
}

void display_riwayat(rw *head_rw){
    if (head_rw == NULL){
        cout << "Data Riwayat Transaksi Masih Kosong . . ." << endl;
        return;
    }
    int i = 0;
    rw *temp = head_rw;
    while (temp != NULL){
    	cout << "---------------------------------------------" <<endl;
        cout << " Data Ke- " << i + 1 << endl;
        cout << " Game           : " << temp->data_transaksi.nama_game << endl;
        cout << " Nama Pemesan   : " << temp->data_transaksi.nama << endl;
        cout << " Platform       : " << temp->data_transaksi.platform << endl;
        cout << " status         : " << temp->data_transaksi.status << endl;
        cout << " Banyak Pesanan : " << temp->data_transaksi.jumlah << endl;
        cout << " Total Harga    : " << temp->data_transaksi.harga << endl;
        cout << "---------------------------------------------" <<endl;
        i++;
        temp = temp->next;
    }
    riwayat_csv(head_rw);
}

string uppercase(string x, char *nama){
    strcpy(nama, x.c_str());
    for(int i =0;i<x.size();i++){
		nama[i] = toupper(nama[i]);
	}
    return nama;
}

void update_game(node **head, node **tail){
	update:
		system("cls");
		int stok;
		int id;
		int harga;
        string up_nama;
        char nama[0];
		display_game(*head, *tail);
    if(*head == NULL && *tail == NULL){
        cout << "\n  [Table still empty]\n" << endl;
        return;
    }
    cout <<"\n|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
    cout <<"|              UPDATE DATA GAME               |\n";
    cout <<"|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
    cout <<"  Silahkan Pilih Data Yang Ingin Di Update : ";cin >> pilih;
    node *temp = *head;
    if (pilih > 0 && pilih <= Last_game){
        for (int i = 1; i < pilih; i++){
            temp = temp->next;
        }
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout<<"         Silahkan Masukan Data Baru        \n";
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout<<"Nama Game   : ";fflush(stdin); getline(cin, up_nama);
        temp->data_disc.nama_game = uppercase(up_nama, &nama[0]);
        cout<<"ID Kaset    : "; cin >> id;
		if(cin.fail()){
			cout << "\nInputan Invalid..!!!\n" << endl;
			std::cin.clear();
	    	std::cin.ignore(256,'\n');   // ignore the line change
			system("pause");
			goto update;
		}
		else if(id < 1){
			cout << "\nInputan Invalid.!!!\n" << endl;
			system("pause");
			goto update;
		}
		else{
			temp->data_disc.id = id;
		}
		
		cout<<"Stok Kaset  : "; cin >> stok;
		if(cin.fail()){
			cout << "\nInputan Invalid..!!!\n" << endl;
			std::cin.clear();
	    	std::cin.ignore(256,'\n');   // ignore the line change
			system("pause");
			goto update;
		}
		else if(stok < 1){
			cout << "\nInputan Invalid.!!!\n" << endl;
			system("pause");
			goto update;
		}
		else{
			temp->data_disc.stok = stok;
		}
		
		
		cout<<"Harga       : "; cin >> harga;
		if(cin.fail()){
			cout << "\nInputan Invalid..!!!\n" << endl;
			std::cin.clear();
	    	std::cin.ignore(256,'\n');   // ignore the line change
			system("pause");
			goto update;
		}
		else if(harga < 1){
			cout << "\nInputan Invalid.!!!\n" << endl;
			system("pause");
			goto update;
		}
		else{
			temp->data_disc.harga = harga;
		}
		cout<<"Platform    : ";fflush(stdin); getline(cin, temp->data_disc.platform);
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout<<"\nDATA YANG DIMASUKAN BERHASIL DIUPDATE\n";
    }else{
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout<<"     ! DATA YANG DIPILIH TIDAK ADA !     \n" << endl;
    }
    system("pause");
    display_game(*head, *tail);
    system("cls");
}

void Tambah_game(node **head, node **tail){
	tambah:
	    system("cls");
	    string nama_temp;
	    char nama[25];
	    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "|              Tambah Game             |";
	        node *game_baru = new node;
            cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;
	        cout<<"Nama Game   : ";fflush(stdin); getline(cin, nama_temp);uppercase(nama_temp, &nama[0]);
	        game_baru->data_disc.nama_game = nama;
	        cout<<"Stok Kaset  : "; cin >> game_baru->data_disc.stok;
	        if(cin.fail()){
				cout << "\nInputan Invalid..!!!\n" << endl;
				std::cin.clear();
		    	std::cin.ignore(256,'\n');   // ignore the line change
				system("pause");
				goto tambah;
			}
			else if(game_baru->data_disc.stok < 1){
				cout << "\nInputan Invalid.!!!\n" << endl;
				system("pause");
				goto tambah;
			}
			
	        cout<<"ID Kaset    : "; cin >> game_baru->data_disc.id;
	        if(cin.fail()){
				cout << "\nInputan Invalid..!!!\n" << endl;
				std::cin.clear();
		    	std::cin.ignore(256,'\n');   // ignore the line change
				system("pause");
				goto tambah;
			}
			else if(game_baru->data_disc.id < 1){
				cout << "\nInputan Invalid.!!!\n" << endl;
				system("pause");
				goto tambah;
			}
			
	        cout<<"Harga       : "; cin >> game_baru->data_disc.harga;
	        if(cin.fail()){
				cout << "\nInputan Invalid..!!!\n" << endl;
				std::cin.clear();
		    	std::cin.ignore(256,'\n');   // ignore the line change
				system("pause");
				goto tambah;
			}
			else if(game_baru->data_disc.harga < 1){
				cout << "\nInputan Invalid.!!!\n" << endl;
				system("pause");
				goto tambah;
			}
			
	        cout<<"Platform    : ";fflush(stdin); getline(cin, game_baru->data_disc.platform);
	        game_baru->prev = *tail;
	        game_baru->next = NULL;
	        if (*head == NULL && *tail == NULL){
	            *head = game_baru;
	            *tail = game_baru;
	        }else{
	            (*tail)->next = game_baru;
	            *tail = game_baru;
	        }Last_game++;
        game_csv(*head);
	    cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	    cout <<"\n! DATA BERHASIL DITAMBAHKAN !\n" << endl;
	    system("pause");
}

void Hapus_game(node **head, node **tail){
	hapus:
		system("cls");
		display_game(*head, *tail);
    if (*head == NULL && *tail == NULL){
        system("pause");
        return;
    }
    node *temp = *head;
    int posisi;
    cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout <<" Silahkan Masukan Posisi Data Yang Ingin Dihapus : "; cin >> posisi;
    if(cin.fail()){
		cout << "\nInputan Invalid..!!!\n" << endl;
		std::cin.clear();
    	std::cin.ignore(256,'\n');   // ignore the line change
		system("pause");
		goto hapus;
	}
	else if(posisi < 1){
		cout << "\nInputan Invalid.!!!\n" << endl;
		system("pause");
		goto hapus;
	}
	else{
	    if (posisi == 1){
	        if((*head)->next == NULL){
	            vardelete = *head;
	            *head = NULL;
	            *tail = NULL;
	            delete vardelete;
	        }else{
	            vardelete = *head;
	            *head = (*head)->next;
	            (*head)->prev = NULL;
	            delete vardelete;
	        }
	    }else{
	        if (posisi < 1 || posisi > Last_game){
	            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	            cout << "   ! DATA YANG INGIN ANDA HAPUS TIDAK DITEMUKAN !  " << endl;
	            system("pause");
	            return;
	        }
	        for (int i = 1;  temp != NULL && i < posisi; i++){
	            temp = temp->next;
	        }
	        if (temp->next != NULL){
	            temp->next->prev = temp->prev;
	        }
	        if (temp->prev != NULL){
	            temp->prev->next = temp->next;
	        }
	        free(temp);
	    }
	}
    Last_game--;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "    ! DATA BERHASIL DIHAPUS !   " << endl;
    system("pause");
    display_game(*head, *tail);
    system("cls");

}

void konversi(game *data_game, node *head, int type){
    if (type == 1){
        for (int i = 0; i < Last_game && head != NULL; i++){
            data_game[i].nama_game = head->data_disc.nama_game;
            data_game[i].stok = head->data_disc.stok;
            data_game[i].id = head->data_disc.id;
            data_game[i].harga = head->data_disc.harga;
            data_game[i].platform = head->data_disc.platform;
            head = head->next;
        }
    }else if (type == 2){
        for (int i = 0; i < Last_game && head != NULL; i++){
            head->data_disc.nama_game = data_game[i].nama_game;
            head->data_disc.stok = data_game[i].stok;
            head->data_disc.id = data_game[i].id;
            head->data_disc.harga = data_game[i].harga;
            head->data_disc.platform = data_game[i].platform;
            head = head->next;
        }
    }
}

void shellsort(game *data_game, int size, int type, int urut){
    if (type == 1 and urut == 1){
        game_sort = 1;
        id_game = 0;
    }else if(type == 2 and urut == 1){
        game_sort = 0;
        id_game = 1;
    }else{
        game_sort = 0;
        id_game = 0;
    }
    for (int gap = size/2; gap > 0; gap /= 2) {
        for (int i = 0; i < size; i += 1){
            temp = data_game[i];
            int j;
            if (type == 1){
                if (urut == 1){
                    // membandingkan data nama
                    for(j=i; j >= gap && data_game[j-gap].nama_game > temp.nama_game; j -= gap)
                    // lalu menukarkan data secara keseluruhan
                        data_game[j] = data_game[j-gap];
                }else if (urut == 2){
                    for(j=i; j >= gap && data_game[j-gap].nama_game < temp.nama_game; j -= gap)
                        data_game[j] = data_game[j-gap];
                }
            }else if (type == 2){
                if (urut == 1){
                    for(j=i; j >= gap && data_game[j-gap].id > temp.id; j -= gap)
                        data_game[j] = data_game[j-gap];
                }else if (urut == 2){
                    for(j=i; j >= gap && data_game[j-gap].id < temp.id; j -= gap)
                        data_game[j] = data_game[j-gap];
                }
            }data_game[j] = temp;
        }
    }
}

void display(){
	display:
		system("cls");
    int jenis = -1;
    while (jenis != 0){
        cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "    MENU LIHAT DATA   " << endl;
        cout << "======================" << endl;
        cout << "  [1] Data Game       " << endl;
        cout << "  [2] Data Antrian    " << endl;
        cout << "  [3] Data Transaksi  " << endl;
        cout << "  [0] Kembali         " << endl;
        cout << "======================" << endl;
        cout << " >> "; cin >> jenis;
        if(cin.fail()){
			cout << "\nInputan Invalid..!!!\n" << endl;
			std::cin.clear();
	    	std::cin.ignore(256,'\n');   // ignore the line change
			system("pause");
			goto display;
		}
        else if(jenis > 3 or jenis <0){
		cout << "\nInputan tidak tersedia..!!!\n" << endl;
		system("pause");
		system("cls");
		continue;
		}

		else{
	        if (jenis ==  1){
	            pilih = -1;
	            while (pilih != 0){
	                system("cls");
	                cout << "|==========================|" << endl;
	                cout << "|  Lihat Data Berdasarkan  |" << endl;
	                cout << "|--------------------------|" << endl;
	                cout << "| 1. Nama Game             |" << endl;
	                cout << "| 2. ID Game               |" << endl;
	                cout << "| 0. Kembali               |" << endl;
	                cout << "|==========================|" << endl;
	                cout << " Pilih >> "; cin >> pilih;
	                if (pilih == 0){
						system("pause");
						system("cls");
						continue;
					}
	                system("cls");
	                cout << "|=========================|" << endl;
	                cout << "|   Sorting Data Secara   |" << endl;
	                cout << "|-------------------------|" << endl;
	                cout << "|  1. Ascending           |" << endl;
	                cout << "|  2. Descending          |" << endl;
	                cout << "|=========================|" << endl;
	                cout << " Pilih >> "; cin >> urut;
	                switch (pilih){
	                case 1:
	                    shellsort(&data_game[0], Last_game, 1, urut);
	                    konversi(&data_game[0], head, 2);
	                    cout << "[Mensorting Nama Game . . . ]\n";Sleep(2000);
	                    cout << "[Data Telah Berhasil di Sorting . . .]\n" << endl; Sleep(2000);
	                    system("cls");
	                    display_game(head, tail);
	                    system("pause");
	                    break;
	                case 2:
	                    shellsort(&data_game[0], Last_game, 2, urut);
	                    konversi(&data_game[0], head, 2);
	                    cout << "[Mensorting ID Game . . . ]\n";Sleep(2000);
	                    cout << "[Data Telah Berhasil di Sorting . . .]\n" << endl; Sleep(2000);
	                    system("cls");
	                    display_game(head, tail);
	                    system("pause");
	                default:
	                    system("pause");
	                    system("cls");
	                    break;
	                }
	            }
	        }else if(jenis == 2){
	        	system("cls");
	            display_antrian(head_trans, tail_trans);
	            system("pause");
	            system("cls");
	        }else if(jenis == 3){
	        	system("cls");
	            display_riwayat(head_rw);
	            system("pause");
	            system("cls");
	        }
	    }
    }
    
}

void Fibonaci(node *head, int size, int type){
    string cari_nama;
    int ID;
    if(type == 1){
        char nama[25];
        cin.ignore();
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Masukkan Nama Game Yang Ingin di cari : ";getline(cin, cari_nama);
        cari_nama = uppercase(cari_nama, &nama[0]);
    }else if (type == 2){
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Masukkan ID Game Yang Ingin di Cari : ";cin >> ID;
    }
    int F0 = 0; 
    int F1 = 1; 
    int F = F0 + F1; 
    while (F < size){
        F0 = F1; // F0 = 1 // F0 = 1
        F1 = F; // F1 = 1 // F1 = 2
        F = F0 + F1; // F = 2 // F = 3
    }
    int offset = -1;
    
    while (F > 1){
        // Inisiasi awal 
        node *temp = head;
        // min (-1+1=0 , 3-1=2) yang di ambil 0 iterasi 1 (i = 0)
        // min ( 0+1=1 , 3-1=2) yang di ambil 1 iterasi 2 (i = 1)
        int i = min(offset + F0, size - 1); 
        for (int trv = 0; temp->next != NULL && trv < i; trv++){
            temp = temp->next;
        }
        if (type == 1){
            if (temp->data_disc.nama_game < cari_nama){
                F = F1; // F = 2 // F = 1
                F1 = F0; // F1 = 1 // F1 = 1
                F0 = F - F1; // F0 = 1 // F0 = 0
                offset = i; // offset = 0, offset = 1
            }else if(temp->data_disc.nama_game > cari_nama){
                F = F0;
                F1 = F1 - F0;
                F0 = F - F1;
            }else{
                cout<<"|==================================================================================|\n";
                cout<<"|  No  |           Game           |    ID    |  Stok  |   Harga(Rp)   |  Platform  |\n";
                cout<<"|==================================================================================|\n";
                cout<<"| "<<setiosflags(ios::left)<<setw(5)<<i+1<<"|";
                cout<<" "<<setiosflags(ios::left)<<setw(25)<<temp->data_disc.nama_game<<"|";
                cout<<" "<<setiosflags(ios::left)<<setw(9)<<temp->data_disc.id<<"|";
                cout<<" "<<setiosflags(ios::left)<<setw(7)<<temp->data_disc.stok<<"|";
                cout<<" "<<setiosflags(ios::left)<<setw(14)<<temp->data_disc.harga<<"|";
                cout<<" "<<setiosflags(ios::left)<<setw(11)<<temp->data_disc.platform<<"|";
                cout<<"\n|==================================================================================|\n";
                system("pause");
                system("cls");
                return;
            }
        }else if (type == 2){
            if (temp->data_disc.id < ID){
                F = F1; // F = 2 // F = 1
                F1 = F0; // F1 = 1 // F1 = 1
                F0 = F - F1; // F0 = 1 // F0 = 0
                offset = i; // offset = 0, offset = 1
            }else if(temp->data_disc.id > ID){
                F = F0;
                F1 = F1 - F0;
                F0 = F - F1;
            }else{
                cout<<"|==================================================================================|\n";
                cout<<"|  No  |           Game           |    ID    |  Stok  |   Harga(Rp)   |  Platform  |\n";
                cout<<"|==================================================================================|\n";
                cout<<"| "<<setiosflags(ios::left)<<setw(5)<<i+1<<"|";
                cout<<" "<<setiosflags(ios::left)<<setw(25)<<temp->data_disc.nama_game<<"|";
                cout<<" "<<setiosflags(ios::left)<<setw(9)<<temp->data_disc.id<<"|";
                cout<<" "<<setiosflags(ios::left)<<setw(7)<<temp->data_disc.stok<<"|";
                cout<<" "<<setiosflags(ios::left)<<setw(14)<<temp->data_disc.harga<<"|";
                cout<<" "<<setiosflags(ios::left)<<setw(11)<<temp->data_disc.platform<<"|";
                cout<<"\n|==================================================================================|\n";
                system("pause");
                system("cls");
                return;
            }
        }
        
    }
    node *temp2 = head;
    for (int trv = 0; temp2->next != NULL && trv < offset + 1; trv++){
        temp2 = temp2->next;
    }
    if (F1 && (temp2->data_disc.nama_game == cari_nama or temp2->data_disc.id == ID)){
        cout<<"|==================================================================================|\n";
        cout<<"|  No  |           Game           |    ID    |  Stok  |   Harga(Rp)   |  Platform  |\n";
        cout<<"|==================================================================================|\n";
        cout<<"| "<<setiosflags(ios::left)<<setw(5)<<size<<"|";
        cout<<" "<<setiosflags(ios::left)<<setw(25)<<temp2->data_disc.nama_game<<"|";
        cout<<" "<<setiosflags(ios::left)<<setw(9)<<temp2->data_disc.id<<"|";
        cout<<" "<<setiosflags(ios::left)<<setw(7)<<temp2->data_disc.stok<<"|";
        cout<<" "<<setiosflags(ios::left)<<setw(14)<<temp2->data_disc.harga<<"|";
        cout<<" "<<setiosflags(ios::left)<<setw(11)<<temp2->data_disc.platform<<"|";
        cout<<"\n|==================================================================================|\n";
        system("pause");
        return;
    }else{
        cout << "[Data tidak di temukan . . . ]" << endl;
        system("pause");
        return;
    }
}

void search(){
    pilih = -1;
    while (pilih != 0){
        system("cls");
        cout << "================================" << endl;
        cout << "  Pilih Data Yang Ingin di Cari  " << endl;
        cout << "================================" << endl;
        cout << " [1] Data Game" << endl;
        cout << " [0] Kembali" << endl;
        cout << "===============================\n";
        cout << " >> "; cin >> pilih;
        if (pilih == 0)return;
        if (pilih == 1){
            int cari = -1;
            while (cari != 0){
                system("cls");
                cout << "===============================" << endl;
                cout << " Pilih Data Yang Ingin di cari " << endl;
                cout << "===============================" << endl;
                cout << " [1] Nama Game" << endl;
                cout << " [2] ID Game" << endl;
                cout << " [0] Kembali" << endl;
                cout << "==============================\n";
                cout << " >> "; cin >> cari;
                if(cari == 0)continue;
                if(cari == 1){
                    if(game_sort != 1){
                        konversi(&data_game[0], head, 1);
                        shellsort(&data_game[0], Last_game, 1, 1);
                        konversi(&data_game[0], head, 2);
                    }
                    Fibonaci(head, Last_game, 1);
                }else if(cari == 2){
                    if(id_game != 1){
                        konversi(&data_game[0], head, 1);
                        shellsort(&data_game[0], Last_game, 2, 1);
                        konversi(&data_game[0], head, 2);
                    }
                    Fibonaci(head, Last_game, 2);
                }
            }
        
        }
    }
}

void proses_pemesanan(trans **head_trans, trans **tail_trans, rw **head_rw){
    while (true){
        string yakin = "tidak";
        display_antrian(*head_trans, *tail_trans);
        if(*head_trans == NULL){
            cout << "Terima Kasih Telah Bekerja Keras Admin . . . " << endl;
            Sleep(2000);
            break;
        }
        cout << "Apakah Anda Ingin Memproses Pemesanan ?\n";
        cout << "[Ya / Tidak] : ";fflush(stdin); getline(cin, yakin);
        if (yakin == "y" or yakin == "Y" or yakin == "Yakin" or yakin == "yakin" or yakin == "ya" or yakin == "Ya"){
            trans *temp = *head_trans;
            if ((*head_trans)->front == NULL){
                *head_trans = NULL;
                *tail_trans = NULL;
            }else if((*head_trans)->front != NULL){
                *head_trans = (*head_trans)->front;
                (*head_trans)->rear = NULL;
            }else{
                break;
            }
            rw *riwayat_baru = new rw;
            riwayat_baru->data_transaksi.nama = temp->data_trans.nama;
            riwayat_baru->data_transaksi.nama_game = temp->data_trans.nama_game;
            riwayat_baru->data_transaksi.platform = temp->data_trans.platform;
            riwayat_baru->data_transaksi.status = "Lunas";
            riwayat_baru->data_transaksi.jumlah = temp->data_trans.jumlah;
            riwayat_baru->data_transaksi.harga = temp->data_trans.harga;
            if(*head_rw == NULL){
                *head_rw = riwayat_baru;
            }else{
                rw *temp_rw = *head_rw;
                while(temp_rw->next != NULL){
                    temp_rw = temp_rw->next;
                }
                temp_rw->next = riwayat_baru;
                delete temp;
                antrian--;
            }
        }else if (yakin == "t" or yakin == "T" or yakin == "Tidak" or yakin == "tidak"){
            cout << "Terima Kasih Telah Bekerja Keras Admin . . . " << endl;
            Sleep(2000);
            break;
        }else{
            cout << "Inputan Anda Salah . . . " << endl;
            continue;
        }
    }
}

void admin(){
    while(pilih != 7){
        konversi(&data_game[0], head, 1);
        system("cls");
        cout<<  "|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|";
        cout<<"\n|                    GAME SHOP                    |";
  		cout<<"\n|                 VIDEO GAME DISC                 |";
  		cout<<"\n|-------------------------------------------------|";
        cout<<"\n|                                                 |";
  		cout<<"\n|===================[MENU ADMIN]==================|";
        cout<<"\n|                                                 |";
	    cout<<"\n|               1. Tambah Data game               |";
	  	cout<<"\n|               2. Lihat Data                     |";
		cout<<"\n|               3. Update Data Game               |";
        cout<<"\n|               4. Proses Pemesanan               |"; 
		cout<<"\n|               5. Hapus Data Game                |";
        cout<<"\n|               6. Cari Data                      |";
		cout<<"\n|               7. Keluar                         |";
        cout<<"\n|                                                 |";
		cout<<"\n|=================================================|";
		cout<<"\nMasukkan Pilihan : ";
        cin >> pilih;
        if(cin.fail()){
			cout << "\nInputan anda tidak sesuai..!!!\n" << endl;
			std::cin.clear();
        	std::cin.ignore(256,'\n');   // ignore the line change
			system("pause");
			continue;
		}
		else{
	        switch (pilih){
	        case 1:
	            Tambah_game(&head, &tail);break;
	        case 2:
	            display();
	            system("pause");break;
	        case 3:
	            update_game(&head, &tail);break;
	        case 4:
	            proses_pemesanan(&head_trans, &tail_trans, &head_rw);
	            break;
	        case 5:
	            Hapus_game(&head, &tail);break;
	        case 6:
	            search();break;
	        case 7: 
	            cout << "\n! ANDA TELAH KELUAR DARI ADMIN !\n" << endl;
	            system("pause");
	        break;
	        default:
	            cout << "\nInputan anda tidak sesuai..!!!\n" << endl;
	            system("pause");
	            break;
	        }
	    }
    }
}

void Lihat_game(){
    pilih = -1;
    while (pilih != 0){
        pilih = -1;
        system("cls");
        display_game(head, tail);
        cout<<"\n|===========MENU============|";
        cout<<"\n| 1. Sorting Game           |";
        cout<<"\n| 2. Cari Game              |";
        cout<<"\n| 0. Kembali                |";
        cout<<"\n|===========================|\n";
        cout<<" Pilih >> "; cin >> pilih;
        if (pilih <= 0)continue;
        if (pilih == 1){
            pilih = -1;
            while (pilih != 0){
                system("cls");display_game(head, tail);
                cout << "\n|=========================|" << endl;
                cout << "|  Menu Lihat Berdasarkan  |" << endl;
                cout << "|--------------------------|" << endl;
                cout << "| 1. Nama Game             |" << endl;
                cout << "| 2. ID Game               |" << endl;
                cout << "| 0. Kembali               |" << endl;
                cout << "|==========================|" << endl;
                cout << " Pilih >> "; cin >> pilih;
                if(pilih <= 0 or pilih > 2)continue;
                system("cls");display_game(head, tail);
                cout << "\n|====================|" << endl;
                cout << "|   Sorting Secara   |" << endl;
                cout << "|--------------------|" << endl;
                cout << "|  1. Ascending      |" << endl;
                cout << "|  2. Descending     |" << endl;
                cout << "|====================|" << endl;
                cout << " Pilih >> "; cin >> urut;
                switch (pilih){
                case 1:
                    shellsort(&data_game[0], Last_game, 1, urut);
                    konversi(&data_game[0], head, 2);
                    cout << "[Mensorting Nama Game . . . ]\n";Sleep(2000);
                    cout << "[Data Telah Berhasil di Sorting . . .]" << endl;Sleep(2000);
                    system("cls");
                    display_game(head, tail);
                    system("pause");
                    pilih = 0;
                    break;
                case 2:
                    shellsort(&data_game[0], Last_game, 2, urut);
                    konversi(&data_game[0], head, 2);
                    cout << "[Mensorting ID Game . . . ]\n";Sleep(2000);
                    cout << "[Data Telah Berhasil di Sorting . . .]\n" << endl; Sleep(2000);
                    system("cls");display_game(head, tail);
                    system("pause");
                    pilih = 0;
                    break;
                default:
                    cout << "[Pilihan Tidak Tersedia . . . ]" << endl;
                    break;
                }
            }
        }else if (pilih == 2){
            pilih = -1;
            while (pilih != 0){
                system("cls");display_game(head, tail);
                cout << "\n|=====================|" << endl;
                cout << "|   Cari Berdasarkan  |" << endl;
                cout << "|---------------------|" << endl;
                cout << "| 1. Nama Game        |" << endl;
                cout << "| 2. ID Game          |" << endl;
                cout << "| 0. Kembali          |" << endl;
                cout << "|=====================|" << endl;
                cout << " Pilih >> "; cin >> pilih;
                if(pilih <= 0 or pilih > 2)continue;
                if(pilih == 1){
                    if(game_sort != 1){
                        konversi(&data_game[0], head, 1);
                        shellsort(&data_game[0], Last_game, 1, 1);
                        konversi(&data_game[0], head, 2);
                    }
                    Fibonaci(head, Last_game, 1);
                }else if(pilih == 2){
                    if(id_game != 1){
                        konversi(&data_game[0], head, 1);
                        shellsort(&data_game[0], Last_game, 2, 1);
                        konversi(&data_game[0], head, 2);
                    }
                    Fibonaci(head, Last_game, 2);
                }
            }  
        }
    }
}

void pesan_game(trans **head_trans, trans **tail_trans, node **head){
    salah :
    	system("cls");
        shellsort(&data_game[0], Last_game, 1, 1);
        konversi(&data_game[0], *head, 2);
        display_game(*head, tail);
        node *temp = *head;
        bool ada = false;
        int banyak;
        string nama;
        char char_nama[25];
        trans *Trans_baru = new trans;
        cout << "============================\n";
        cout << " Pesan Disc Game\n";
        cout << " Nama Game : "; fflush(stdin);getline(cin, nama);
        nama = uppercase(nama, &char_nama[0]);
        while (temp != NULL){
            if (temp->data_disc.nama_game == nama){
                cout << " Banyak Disc : "; cin >> banyak;
                if(cin.fail()){
					cout << "\nInputan anda tidak sesuai..!!!\n" << endl;
					cin.clear();
		        	cin.ignore(256,'\n');   // ignore the line change
					system("pause");
					goto salah;
				}
                else if (temp->data_disc.stok >= banyak and banyak >= 1){
                    ada = true;
                    break;
                }
            }
            temp = temp->next;
        }
        if (ada == true){            
                Trans_baru->data_trans.nama = nama_pemesan;
                Trans_baru->data_trans.nama_game = nama;
                Trans_baru->data_trans.platform = temp->data_disc.platform;
                Trans_baru->data_trans.harga = (temp->data_disc.harga * banyak);
                Trans_baru->data_trans.jumlah = banyak;
                Trans_baru->data_trans.status = "Belum Lunas";
                temp->data_disc.stok = (temp->data_disc.stok - banyak);
                Trans_baru->front = NULL;
                Trans_baru->rear = *tail_trans;
                if (*head_trans == NULL and *tail_trans == NULL){
                    *head_trans = Trans_baru;
                    *tail_trans = Trans_baru;
                }else{
                    (*tail_trans)->front = Trans_baru;
                    *tail_trans = Trans_baru;
                }
                antrian++;
                cout << "[Data Berhasil Di Pesan . . . ]" << endl;
                Sleep(2000);
        }else{
            cout << "Nama atau Banyak barang tidak sesuai dengan data yang ada . . ." << endl;
            system("pause");
            goto salah;
        }
}


void lihat_antrian(trans **head_trans, trans **tail_trans){
    if(*head_trans == NULL){
        cout << "\n Antrian Masih Kosong" << endl;
        return;
    }
    int i, j;
    trans *temp = *head_trans;
    while (temp != NULL){
        if (temp->data_trans.nama == nama_pemesan){
            j = i;
        }
        temp = temp->front;
        i++;
    }
    cout << "Anda Pada antrian ke- " << j + 1 << endl;
    cout << "Dari Antrian Sebanyak : " << i + 1 << endl;
}

void user(){
	user:
    while(pilih != 3){
        konversi(&data_game[0], head, 1);
        system("cls");
        cout<<  "|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|";
        cout<<"\n|                    GAME SHOP                    |";
  		cout<<"\n|                 VIDEO GAME DISC                 |";
  		cout<<"\n|-------------------------------------------------|";
        cout<<"\n|                                                 |";
  		cout<<"\n|=======================MENU======================|";
	    cout<<"\n|                1. Katalog Game                  |";
	  	cout<<"\n|                2. Pesan Game                    |";
		cout<<"\n|                3. Keluar                        |";
		cout<<"\n|=================================================|";
		cout<<"\n  Masukkan Pilihan : ";
        cin >> pilih;
        if(cin.fail()){
			cout << "\nInputan anda tidak sesuai..!!!\n" << endl;
			std::cin.clear();
        	std::cin.ignore(256,'\n');   // ignore the line change
			system("pause");
			goto user;
		}
		else{
	        switch (pilih){
	        case 1:
	            Lihat_game();break;
	        case 2:
	            pesan_game(&head_trans, &tail_trans, &head);break;
	        case 3:
	            cout << "[Keluar dari Menu . . . ]" << endl;break;
	        default:
	            cout << "\nInputan anda tidak sesuai..!!!\n" << endl;
	            system("pause");
	            break;
	        }
	    }
    }
}

void login(akun **head_akun, akun **tail_akun){
    string username, password;
    cout << "\nUsername\t : "; cin >> username;
    cout << "Password\t : "; cin >> password;
    akun *temp = *head_akun;
    bool verify = false;
    if(username == "admin" && password == "admin"){
        admin();
        return;
    }
    while(temp != NULL){
        if(temp->user.username == username && temp->user.password == password){
            verify = true;
            break;
        }
        temp = temp->next;
    }
    if (verify == true){
        cout << "" << endl;
        cout << "Selamat Datang " << temp->user.nama_user << endl;
        nama_pemesan = temp->user.nama_user;
        Sleep(1000);
        user();
    }else{
        cout << "\nPassword dan Username Salah\n\n";
        system("pause");
    }
}

void regis(akun **head_akun, akun **tail_akun){
    akun *akun_baru = new akun;
    char nama[25];
    cout << "Username\t : "; cin >> akun_baru->user.username;
    cout << "Nama\t\t : "; fflush(stdin); getline(cin, nama_pemesan);
    akun_baru->user.nama_user = uppercase(nama_pemesan, &nama[0]);
    cout << "Password\t : "; fflush(stdin); getline(cin, akun_baru->user.password);
    akun_baru->prev = *tail_akun;
    akun_baru->next = NULL;
    if (*head_akun == NULL && *tail_akun == NULL){
        *head_akun = akun_baru;
        *tail_akun = akun_baru;
    }else{
        (*tail_akun)->next = akun_baru;
        *tail_akun = akun_baru;
    }
    Last_user++;
    akun_csv(*head_akun);
}

int main(){
    CSV_akun(&head_akun, &tail_akun);
    CSV_Game(&head, &tail);
    CSV_riwayat(&head_rw);
    masuk:
    	system("cls");
        cout<<"|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|" << endl;
        cout<<"|                    GAME SHOP                    |" << endl;
  		cout<<"|                 VIDEO GAME DISC                 |" << endl;
  		cout<<"|-------------------------------------------------|" << endl;
        cout<<"|                                                 |" << endl;
        cout<<"|                  [1] Login                      |" << endl;
        cout<<"|                  [2] Register                   |" << endl;
        cout<<"|                                                 |" << endl;
        cout<<"|=================================================|" << endl;
        cout << " >> "; cin >> pilih;
        if(cin.fail()){
			cout << "\nInputan anda tidak sesuai..!!!\n" << endl;
			std::cin.clear();
        	std::cin.ignore(256,'\n');   // ignore the line change
			system("pause");
			goto masuk;
		}
		else{
	        switch (pilih){
	        case 1:
	            login(&head_akun, &tail_akun);
	            goto masuk;
	            break;
	        case 2:
	            regis(&head_akun, &tail_akun);
	            goto masuk;
	            break;
	        default:
	            cout << "\n ! PILIHAN ANDA TIDAK TERSEDIA ! \n\n";
	            system("pause");
	            goto masuk;
	            break;
	        }
	    }
    
}
