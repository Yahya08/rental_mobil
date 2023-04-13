//  Copyright © 2021-2022 Yahya Handarestanto, Pijar Pahlawan Qolbu, Aldi Putra Miftaqul Ullum, Valen Achmad Apiliawan, Michael Mardiansyah, Tifani Dea Shafira, Putra Budi Rahayu, Muhammad Zhafar Al Fathi, Nabella Ayu Giwanti
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 

#include <iostream>
#include <conio.h>
#include "RandomData.h"
#include "Helpers.h"
#include "ProgramSection.h"

using namespace std;

#define SEBELUMNYA 75  // 75 adalah kode ASCII tombol panah ke kiri
#define SELANJUTNYA 77 // 77 adalah kode ASCII tombol panah ke kanan
#define KELUAR 27      // 27 adalah kode ASCII tombol esc
#define MASUK 13       // 13 adalah kode ASCII tombol enter

int main()
{
    bool doneInteraction = false; // variabel sebagai kondisi looping menampilkan daftar mobil
    bool reprint = false;          // variabel sebagai kondisi untuk mencetak daftar mobil
    int currentGarage = 0;        // variabel untuk menampung nomor garasi
    int garageCap = 0;            // variabel untuk menampung jumlah kapasitas mobil per garasi
    int metodeBayar = 0;          // variabel yang menampung pilihan metode pembayaran
    string pilMob = "";           // variabel untuk menampung pilihan mobil sementara sebelum dicasting ke tipe integer

    Welcome();
    GenerateRandomData();

    /* control flow display models */
menu:
    currentGarage = 1;          
    doneInteraction = false;    
    reprint = true;             
    while (true)
    {
        if (reprint)
            DisplayGarageContent(currentGarage);
        switch (getch())
        {
        case SEBELUMNYA:
            reprint = true;
            currentGarage--;
            break;
        case SELANJUTNYA:
            reprint = true;
            currentGarage++;
            break;
        case MASUK:
            reprint = true;
            doneInteraction = true;
            break;
        case KELUAR:
            reprint = true;
            doneInteraction = true;
            Selesai();
        default:
            reprint = false;
            break;
        }
        if (doneInteraction)
            break;
        currentGarage = currentGarage > 3 ? 1 : currentGarage < 1 ? 3 : currentGarage;
    }
    if (exitProgram)
        return 0;

    /* get chosen models */
    cout << "\nMasukan Pilihan: ";
    cin >> pilMob;
    pilihanMobil = StrToInt(pilMob);

    if (currentGarage == 1)
        garageCap = 5;
    else if (currentGarage == 2)
        garageCap = 6;
    else if (currentGarage == 3)
        garageCap = 4;
    /* menentukan inputan sesuai dengan yang diminta atau tidak */
    if ((pilihanMobil > 0) && (pilihanMobil <= garageCap) && IsStringAllDigit(pilMob))
    {
        pilihanMobil = pilihanMobil + start - 1;

        /* mencari mobil tersedia atau tidak, dan menampilkan data spesifikasi mobil jika tersedia */
        if (!tersedia[pilihanMobil])
        {
            cout << "\n###########################################################################" << endl;
            cout << "(!)                   Mohon Maaf Mobil Tidak Tersedia                   (!)" << endl;
            cout << "###########################################################################" << endl;
            cout << "\nTekan ENTER untuk kembali ke menu memilih mobil...";
            cin.ignore();
            cin.get();
            goto menu;
        }

    /* menampilkan spesifikasi dan bertanya kepada user apakah yakin atau tidak
    jika yakin lanjut ke sesi berikutnya. jika tidak yakin kembali ke menu pilihan mobil*/
    spesifikasi:
        system("cls");
        Specification(pilihanMobil);
        cout << "Apakah anda yakin? (y/n): ";
        cin >> y_n;
        if (MakeLowercase(y_n)[0] == 'y')
        {
            // MEMASUKKAN JUMLAH HARI DAN KALKULASI TARIF PINJAM
            GetCarLoanPeriod();
            tarif = jmlh_hari * harga[pilihanMobil];
            // INPUT DATA DIRI PELANGGAN
            CustomerDatas();
            // MENGELUARKAN RESUME DATA DIRI PELANGGAN, BIAYA, DAN MEMINTA METODE PEMBAYARAN
            metodeBayar = GetPaymentMethod(tarif);
            // PEMBAYARAN
            GetPaid(metodeBayar);
        }
        else
        {
            if (MakeLowercase(y_n)[0] == 'n')
            {
                cout << "\nTekan ENTER untuk kembali ke menu memilih mobil...";
                cin.ignore();
                cin.get();
                goto menu;
            }
            else
            {
                ErrorNotif(1);
                cout << "\nTekan ENTER untuk kembali memilih y/n...";
                cin.ignore();
                cin.get();
                goto spesifikasi;
            }
        }
    }
    else
    {
        ErrorNotif(2);
        cout << "\nTekan ENTER untuk kembali ke menu memilih mobil...";
        cin.ignore();
        cin.get();
        goto menu;
    }

    Selesai();
    return 0;
}
