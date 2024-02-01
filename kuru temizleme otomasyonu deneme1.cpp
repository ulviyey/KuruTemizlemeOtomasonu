#include <iomanip> 
#include <cstring> 
#include <stdlib.h>
#include <conio.h>
#include <stdio.h> 
#include <fstream>                  
#include <iostream>

using namespace std;

struct Musteri
{
    char ad[80];
    char soyad[80];
    char tel[15];
    char giysiTuru[50];
    char giysiRengi[20];
    double temizlikUcreti;
    bool temizlendi;
};

void MusteriEkle();
void MusteriListeleme();
void MusteriArama();
void MusteriSil();
void MusteriDuzenle();

int main() {
    char anamenu;
    do {
        system("cls");

        cout << "|-------Hosgeldiniz------|" << endl ;
        cout << "|      Secim Yapiniz     |" << endl ;
        cout << "|   1- Musteri Ekleme    |" << endl ;
        cout << "|   2- Musteri Listeleme |" << endl ;
        cout << "|     3- Musteri Arama   |"<< endl;
        cout << "|    4- Musteri Sil      |"<< endl;
        cout << "|    5- Musteri Duzenle  |"<< endl;
        cout << "|------------------------|" << endl ;
        
        char secim;
        cin >> secim;

        switch(secim) {
            case '1' : 
                MusteriEkle();
                break;	
            case '2' : 
                MusteriListeleme();
                break;
            case '3' : 
                MusteriArama();
                break;
            case '4' : 
                MusteriSil();
                break;
            case '5' : 
                MusteriDuzenle();
                break;
        }
        
        cout << "Anamenuye Donmek icin: a basin cikmak icin: c" << endl ; 
        anamenu = getche();
    } while(anamenu == 'a');

    return 0;
}

Musteri musteri;

void MusteriEkle() {
    ofstream yaz("musteri.dat", ios::binary | ios::app);
    char secim;
    int adet = 0;
    
    do {
        cout << "Musteri Ad Giriniz" << endl;
        cin >> musteri.ad;
        cout << "Musteri Soyad Giriniz" << endl;
        cin >> musteri.soyad;
        cout << "Musteri Telefon Giriniz" << endl;
        cin >> musteri.tel;
        cout << "Giysi Turu Giriniz" << endl;
        cin >> musteri.giysiTuru;
        cout << "Giysi Rengi Giriniz" << endl;
        cin >> musteri.giysiRengi;
        cout << "Temizlik Ucreti Giriniz" << endl;
        cin >> musteri.temizlikUcreti;

        // Yeni özellik: Temizlik durumu baþlangýçta false olarak ayarlandý.
        musteri.temizlendi = false;
        
        yaz.write((char*)&musteri, sizeof(musteri));
        adet++;	
        
        cout << "Baska Kayit Eklemek Istermisin (E/H)" << endl;
        secim = getche();
        cout << endl;
    } while(secim == 'e' || secim == 'E');
    
    cout << adet << " adet Musteri Ekledi.." << endl;
    
    yaz.close();
}

void MusteriListeleme() {
    ifstream oku("musteri.dat", ios::binary | ios::app);
    
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(musteri);
    cout << "Toplam Musteri Kayit Sayisi:" << kayits << endl;
    
    if(kayits > 0) {
        for(int i = 0; i < kayits; i++) {
            oku.seekg(i * sizeof(musteri));
            oku.read((char*)&musteri, sizeof(musteri));	
            
            cout << i+1 << ". Musterinin Bilgileri"<< endl;
            cout << "Musteri Adi: " << musteri.ad << endl ;
            cout << "Musteri Soyadi: " << musteri.soyad << endl ;
            cout << "Musteri Telefon: " << musteri.tel << endl ;
            cout << "Giysi Turu: " << musteri.giysiTuru << endl ;
            cout << "Giysi Rengi: " << musteri.giysiRengi << endl ;
            cout << "Temizlik Ucreti: " << musteri.temizlikUcreti << " TL" << endl ;
            cout << "Temizlik Durumu: " << (musteri.temizlendi ? "Temizlendi" : "Temizlenmedi") << endl ;
        }
    } else {
        cout << "Kayit Bulunamadi..." << endl;
    }

    oku.close();
}

void MusteriArama() {
    ifstream oku("musteri.dat", ios::binary | ios::app);
    
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(musteri);

    cout << "Aranan Musteri Adini Giriniz" << endl;
    char arananAd[80];
    cin >> arananAd;

    if(kayits > 0) {
        for(int i = 0; i < kayits; i++) {
            oku.seekg(i * sizeof(musteri));
            oku.read((char*)&musteri, sizeof(musteri));
            
            if(strcmp(musteri.ad, arananAd) == 0) {
                cout <<  "Bulunan Musterinin Bilgileri"<< endl;
                cout << "Musteri Adi: " << musteri.ad << endl ;
                cout << "Musteri Soyadi: " << musteri.soyad << endl ;
                cout << "Musteri Telefon: " << musteri.tel << endl ;
                cout << "Giysi Turu: " << musteri.giysiTuru << endl ;
                cout << "Giysi Rengi: " << musteri.giysiRengi << endl ;
                cout << "Temizlik Ucreti: " << musteri.temizlikUcreti << " TL" << endl ;
                cout << "Temizlik Durumu: " << (musteri.temizlendi ? "Temizlendi" : "Temizlenmedi") << endl ;
            }
        }
    } else {
        cout << "Kayit Bulunamadi..." << endl;
    }

    oku.close();
}

void MusteriSil() {
    char musteriTel[15];
    char secim = ' ';
    bool var = false;
    
    ifstream oku("musteri.dat", ios::binary | ios::app);
    
    oku.seekg(0, ios::end);

    int kayitsayisi = oku.tellg() / sizeof(musteri);
    
    cout << "Silmek istediginiz Musteri Telefon Numarasini Giriniz : ";
    cin >> musteriTel;

    for(int i = 0; i < kayitsayisi; i++) {
        oku.seekg(i * sizeof(musteri));
        oku.read((char*)&musteri, sizeof(musteri));

        if(strcmp(musteri.tel, musteriTel) == 0) {
            cout << "Bulunan Musterinin Bilgileri" << endl;
            cout << "Musteri Adi: " << musteri.ad << endl ;
            cout << "Musteri Soyadi: " << musteri.soyad << endl ;
            cout << "Musteri Telefon: " << musteri.tel << endl ;
            cout << "Giysi Turu: " << musteri.giysiTuru << endl ;
            cout << "Giysi Rengi: " << musteri.giysiRengi << endl ;
            cout << "Temizlik Ucreti: " << musteri.temizlikUcreti << " TL" << endl ;
            cout << "Temizlik Durumu: " << (musteri.temizlendi ? "Temizlendi" : "Temizlenmedi") << endl ;

            cout << "\n\nSilmek Istediginiz Kayit Bu Mu? [E/H] : ";
            secim = getche();

            if(secim == 'H' || secim == 'h') {
                Musteri y_musteri;
                ofstream y_dosya("Yedek.dat", ios::app | ios::binary);
                
                strcpy(y_musteri.ad, musteri.ad);
                strcpy(y_musteri.soyad, musteri.soyad);
                strcpy(y_musteri.tel, musteri.tel);
                strcpy(y_musteri.giysiTuru, musteri.giysiTuru);
                strcpy(y_musteri.giysiRengi, musteri.giysiRengi);
                y_musteri.temizlikUcreti = musteri.temizlikUcreti;
                y_musteri.temizlendi = musteri.temizlendi;

                y_dosya.write((char*)&musteri, sizeof(musteri));
                y_dosya.close();
            }

            if(secim == 'e' || secim == 'E') {
                var = true;
            }
        } else {
            Musteri y_musteri;
            ofstream y_dosya("Yedek.dat", ios::app | ios::binary);
            
            strcpy(y_musteri.ad, musteri.ad);
            strcpy(y_musteri.soyad, musteri.soyad);
            strcpy(y_musteri.tel, musteri.tel);
            strcpy(y_musteri.giysiTuru, musteri.giysiTuru);
            strcpy(y_musteri.giysiRengi, musteri.giysiRengi);
            y_musteri.temizlikUcreti = musteri.temizlikUcreti;
            y_musteri.temizlendi = musteri.temizlendi;

            y_dosya.write((char*)&musteri, sizeof(musteri));
            y_dosya.close();
        }
    }

    oku.close();

    if(var) {
        remove("musteri.dat");
        rename("Yedek.dat", "musteri.dat");
        cout << "\n Musteri Kayit Silindi" << endl;
    } else {
        remove("Yedek.dat");
        cout << "\n Musteri Kayit Bulunamadi" << endl;                  
    }
}

void MusteriDuzenle() {
    char musteriTel[15];
    char secim = ' ';
    bool var = false;
    
    ifstream oku("musteri.dat", ios::binary | ios::app);
    
    oku.seekg(0, ios::end);

    int kayitsayisi = oku.tellg() / sizeof(musteri);
    
    cout << "Duzenlemek istediginiz Musteri Telefon Numarasini Giriniz : ";
    cin >> musteriTel;

    for(int i = 0; i < kayitsayisi; i++) {
        oku.seekg(i * sizeof(musteri));
        oku.read((char*)&musteri, sizeof(musteri));

        if(strcmp(musteri.tel, musteriTel) == 0) {
            cout << "Bulunan Musterinin Bilgileri" << endl;
            cout << "Musteri Adi: " << musteri.ad << endl ;
            cout << "Musteri Soyadi: " << musteri.soyad << endl ;
            cout << "Musteri Telefon: " << musteri.tel << endl ;
            cout << "Giysi Turu: " << musteri.giysiTuru << endl ;
            cout << "Giysi Rengi: " << musteri.giysiRengi << endl ;
            cout << "Temizlik Ucreti: " << musteri.temizlikUcreti << " TL" << endl ;
            cout << "Temizlik Durumu: " << (musteri.temizlendi ? "Temizlendi" : "Temizlenmedi") << endl ;

            cout << "\n\nDuzeltmek Istediginiz Kayit Bu Mu? [E/H] : ";
            secim = getche();

            if(secim == 'E' || secim == 'e') {
                var = true;
                ofstream dosya("Yedek.dat", ios::app | ios::binary);
                
                cout << "Musteri Ad Giriniz" << endl;
                cin >> musteri.ad;
                cout << "Musteri Soyad Giriniz" << endl;
                cin >> musteri.soyad;
                cout << "Musteri Telefon Giriniz" << endl;
                cin >> musteri.tel;
                cout << "Giysi Turu Giriniz" << endl;
                cin >> musteri.giysiTuru;
                cout << "Giysi Rengi Giriniz" << endl;
                cin >> musteri.giysiRengi;
                cout << "Temizlik Ucreti Giriniz" << endl;
                cin >> musteri.temizlikUcreti;
                
                // Yeni özellik: Temizlik durumu baþlangýçta false olarak ayarlandý.
                musteri.temizlendi = false;
                
                dosya.write((char*)&musteri, sizeof(musteri));
                dosya.close();
            } else {
                Musteri y_musteri;
                ofstream y_dosya("Yedek.dat", ios::app | ios::binary);
                
                strcpy(y_musteri.ad, musteri.ad);
                strcpy(y_musteri.soyad, musteri.soyad);
                strcpy(y_musteri.tel, musteri.tel);
                strcpy(y_musteri.giysiTuru, musteri.giysiTuru);
                strcpy(y_musteri.giysiRengi, musteri.giysiRengi);
                y_musteri.temizlikUcreti = musteri.temizlikUcreti;
                y_musteri.temizlendi = musteri.temizlendi;

                y_dosya.write((char*)&y_musteri, sizeof(y_musteri));
                y_dosya.close();
            }
        } else {
            Musteri y_musteri;
            ofstream y_dosya("Yedek.dat", ios::app | ios::binary);
            
            strcpy(y_musteri.ad, musteri.ad);
            strcpy(y_musteri.soyad, musteri.soyad);
            strcpy(y_musteri.tel, musteri.tel);
            strcpy(y_musteri.giysiTuru, musteri.giysiTuru);
            strcpy(y_musteri.giysiRengi, musteri.giysiRengi);
            y_musteri.temizlikUcreti = musteri.temizlikUcreti;
            y_musteri.temizlendi = musteri.temizlendi;

            y_dosya.write((char*)&y_musteri, sizeof(y_musteri));
            y_dosya.close();
        }
    }

    oku.close();

    if(var) {
        remove("musteri.dat");
        rename("Yedek.dat", "musteri.dat");
        cout << "\nMusteri Kayit Duzeltildi." << endl;
    } else {
        remove("Yedek.dat");
        cout << "\nMusteri Kayit Bulunamadi" << endl;                  
    }
};
