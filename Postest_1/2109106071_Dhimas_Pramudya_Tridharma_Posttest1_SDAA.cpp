#include <iostream>
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
// Deklaris Variabel Global
Tentara Data_TNI[100];
int index, pilih, nambah, up;
char confirm;

void Tampilkan(Tentara *data, int lastindex){
    system("cls");
    cout << "=================================" << endl;
    cout << "[DATA TENTARA REPUBLIK INDONESIA]" << endl;
    cout << "=================================" << endl;
    // perulangan untuk menampilkan data pada array of struct
    for (int i = 0; i < 100 && !data[i].Nama.empty(); i++){
        cout << "\nData Ke- " << i+1 << "." << endl;
        cout << "Nama\t\t : " << data[i].Nama << endl;
        cout << "Tinggi\t\t : " << data[i].Tinggi << endl;
        cout << "ID_Tentara\t : " << data[i].ID_Tentara << endl;
        cout << "Divisi\t\t : " << data[i].Divisi << endl;
        cout << "TTL\t\t : " << data[i].TTL.Tempat << ", " << data[i].TTL.tanggal << "-" << data[i].TTL.bulan << "-" << data[i].TTL.tahun << endl;
    }
    if (index == 0){
        cout << "\n[DATA MASIH KOSONG]" << endl;
    // mengembalikan nilai index yang nanti berfungsi sebagai index baru untuk menambahkan data baru
    }
}
void Tambah_Data(Tentara *data, int lastindex){
    // untuk mencari alamat pointer data terakhir
    for(int i =0; i < lastindex; i-=-1){
        data++;
    }
    // inputan banyak data yang akan di tambahkan
    cout << "\nTambah Data Sebanyak : "; cin >> nambah;
    if (index + nambah <= 100){
        for (int i = 0; i < nambah; i++){
            cin.ignore();
            cout << "\nData Ke- " << index+1 << "." <<endl;
            cout << "Nama\t\t : "; getline(cin, data->Nama);
            cout << "Tinggi\t\t : "; cin >> data->Tinggi;
            cout << "ID_Tentara\t : "; cin >> data->ID_Tentara; fflush(stdin);
            cout << "Divisi\t\t : "; getline(cin, data->Divisi); fflush(stdin);
            cout << "Tempat Lahir\t : "; getline(cin, data->TTL.Tempat);
            cout << "Tanggal Lahir\t : "; cin >> data->TTL.tanggal;
            cout << "Bulan Lahir\t : "; cin >> data->TTL.bulan;
            cout << "Tahun Lahir\t : "; cin >> data->TTL.tahun;
            index++;
            data++;
        }
    }else if(index + nambah > 100){
        cout << "\n[DATA SUDAH TERISI PENUH HARAP MENGOSONGKAN RUANG PENYIMPANAN]" << endl;
    }cout << "[Data Berhasil Di Tambahkan . . . ]" << endl;
    system("Pause");
}
void Hapus_Data(Tentara *data, int lastindex){
    cout << "\nHapus data ke- : "; cin >> up;
    // pertama data memeriksa apa data tersedia atau tidak
    if (data[up-1].Nama == ""){
        cout << "[DATA TIDAK TERSEDIA, HARAP PERIKSA KEMBALI PILIHAN ANDA]\n" << endl;
        system("pause");
    }else{
    // jika iya maka akan menjalankan program berikut dengan cara menimpa data yang ingin di hapus dengan data setelah nya
        for (int i = up-1; i < lastindex; i++){
            data[i].Nama = data[i+1].Nama;
            data[i].Tinggi = data[i+1].Tinggi;
            data[i].ID_Tentara = data[i+1].ID_Tentara;
            data[i].Divisi = data[i+1].Divisi;
            data[i].TTL.Tempat = data[i+1].TTL.Tempat;
            data[i].TTL.tanggal = data[i+1].TTL.tanggal;
            data[i].TTL.bulan = data[i+1].TTL.bulan;
            data[i].TTL.tahun = data[i+1].TTL.tahun;
            // untuk index yang berada paling akhir datanya akan di pindah kan ke data sebelum nya
            // dan data yang masih tertinggal di index akhir tersebut akan di hapus dengan progam di bawah ini.
            if (index - i == 0){
                data[i+1].Nama = "";
                data[i+1].Tinggi = 0;
                data[i+1].ID_Tentara = 0;
                data[i+1].Divisi = "";
                data[i+1].TTL.Tempat = "";
                data[i+1].TTL.tanggal = 0;
                data[i+1].TTL.bulan = 0;
                data[i+1].TTL.tahun = 0;
            }
        }index--;
        cout << "[Data Berhasil Di Hapus . . . ]" << endl;
    }system("Pause");
}
    
void Update_Data(Tentara *data, int lastindex){
    // untuk mengakes alamat pointer data yang akan di edit atau update
    cout << "\nEdit Data Ke- : "; cin >> up;
    for(int i; i < up-1; i-=-1){
        data++;
    }
    // mengecek ketersediaan data yang akan di update
    if (data->Nama == ""){
        cout << "[DATA TIDAK TERSEDIA, HARAP PERIKSA KEMBALI PILIHAN ANDA]\n" << endl;
        system("pause");
    }else{
        cin.ignore();
        cout << "\nData Ke- " << up << "." <<endl;
        cout << "Nama\t\t : "; getline(cin, data->Nama);
        cout << "Tinggi\t\t : "; cin >> data->Tinggi;
        cout << "ID_Tentara\t : "; cin >> data->ID_Tentara; fflush(stdin);
        cout << "Divisi\t\t : "; getline(cin, data->Divisi); fflush(stdin);
        cout << "Tempat Lahir\t : "; getline(cin, data->TTL.Tempat);
        cout << "Tanggal Lahir\t : "; cin >> data->TTL.tanggal;
        cout << "Bulan Lahir\t : "; cin >> data->TTL.bulan;
        cout << "Tahun Lahir\t : "; cin >> data->TTL.tahun;
        cout << "\n[Data Berhasil Di Perbarui . . . ]" << endl;
    }
    system("Pause");
}
int main(){
    int pilih;
    while (pilih != 5){
        system("cls");
        cout << "[Menu Pendataan Tentara]" << endl;
        cout << "[1] Lihat Data Tentara" << endl;
        cout << "[2] Tambah Data Tentara" << endl;
        cout << "[3] Hapus Data Tentara" << endl;
        cout << "[4] Edit Data Tentara" << endl;
        cout << "[5] Exit Program" << endl;
        cout << "========================\n";
        cout << " >> ";
        cin >> pilih;
        switch (pilih){
        // fungsi menampilkan ada di setiap pilihan agar menampilkan data yang udah ada sebelum nya
        case 1:
            Tampilkan(&Data_TNI[0], index);system("Pause");break;
        case 2:
            Tampilkan(&Data_TNI[0], index);
            Tambah_Data(&Data_TNI[0], index);break;
        case 3:
            Tampilkan(&Data_TNI[0], index);
            Hapus_Data(&Data_TNI[0], index);break;
        case 4:
            Tampilkan(&Data_TNI[0], index);
            Update_Data(&Data_TNI[0], index);break;
        case 5:
            cout << "[Terima Kasih Telah Mendaftar semoga beruntung . . . ]" << endl;
            break;
        default:
            cout << "Pilihan Anda tidak Tersedia . . ." << endl;
            break;
        }
    }
    
}