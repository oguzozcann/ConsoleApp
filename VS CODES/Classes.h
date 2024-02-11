// Oðuzhan Özcan  410453 
// Mehmet Koçak 402541

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <chrono>
#include <future>
#include <time.h>
#include <regex>
#include <fstream>
#include <mysql.h>
#include <sstream>
#include <ctime>

using namespace std;

class Zaman
{
private:
	int saat;
	int dakika;
public:
	Zaman();
	~Zaman();
	void setZaman(int h, int m);
	string CurrentHour();
	string bitisZamani(string ilce);
	int geriSayim();
};


class Kiyafet
{
protected:
	string kategori;
	string boyut;
	string renk;
	string kiyafet_adi;
	double fiyat;
public:
	Kiyafet();
	~Kiyafet();
	int setKategori(string kategori);
	string getKategori() { return kategori; };
	int setBoyut(string boyut);
	string getBoyut() { return boyut; };
	int setRenk(string renk);
	string getRenk() { return renk; };
	int setFiyat(double fiyat);
	double getFiyat() { return fiyat; };
	void kiyafetInsert();
	void kiyafetDisplay();
};


class Kisi
{
protected:
	string ad_soyad;
	string telefon;
	bool isDigit(const char c);
	bool isChar(const char c);			//////////---> e posta kontrol icin
	bool isSpecialChar(const char c);	///////// ---^
public:
	Kisi();
	Kisi(string adSoyad, string telNo);
	~Kisi();
	int setAd_Soyad(string adSoyad);
	string getAd_Soyad() { return ad_soyad; };
	int TelNo(string telNo);
	string getTelNum() { return telefon; };
};



class Siparis :public Kiyafet
{
private:
	int siparis_no;
	double siparis_fiyat;
	Zaman siparis_baslangic;
	Zaman siparis_ulasim;
public:
	Siparis();
	~Siparis();
	void setSiparisNo(int siparisNo);
	int getSiparisNo() { return siparis_no; };
	void setSiparisFiyat(double siparisFiyati);
	double getSiparisFiyat() { return siparis_fiyat; };
	
};


class Kullanici :public Kisi{
private:
	string k_adi;
	string eposta;
	string adres;
	string sifre;
	string dtarih;
	bool ilceBilgisi(string);
public:

	Kullanici(string KullaniciAdi="", string KullaniciEposta = "",
		string KullaniciAdresIlce = "", string Kullanicisifre = "", string KullaniciDTarihi = "", string adSoyad = "", string telNo = "");
	~Kullanici();
	int setKullaniciAdi(string kullaniciAdi);
	string getKullaniciAdi() { return k_adi; };
	int setEposta(string kullaniciEposta);
	string getEposta() { return eposta; };
	int setAdresIlce(string kullaniciAdresIlce);
	string setAdresIlce() { return adres; };
	int setKullaniciSifre(string kullaniciSifre);
	string getKullaniciSifre() { return sifre; };
	int setDogumT(string kullaniciDTarihi);
	string getDogumT() { return dtarih; };
	void kullaniciEkleme();
};

class Yonetici :public Kisi {
private:

	string sifre;
public:
	Yonetici();
	~Yonetici();
	void setIndirimliFiyat(string);
	void fiyatGuncelleme(string,string);
	void yoneticiFatura();
	void kullaniciGoruntule();
};


class Kurye :public Kisi {
private:
	Zaman dagitim_bitisler;
	string ilce;
public:
	Kurye(string="", string="");
	~Kurye();
	void setDagitBitir(Zaman dagitBitir);
	Zaman getDagitBitir() { return dagitim_bitisler; };
	void kuryeEkleme();
	void kuryeGoruntuleme();
	void kuryeGuncelleme(string id,string bosMu);
	string kuryeSorgu();
	void setIlce(string ilce) { this->ilce = ilce; };
	string getIlce() { return ilce; };
};


class Function{
private:
	string id;
	string musteriNo;
	string kuryeIlce;
public:
	//Function();
	void anaMenu();
	void hesapOlusturma();
	void sistemGiris();


	void musteriAnaMenu();
	void sikayetEkleme();
	void sikayetGoruntulemeK();
	void sikayetGoruntulemeY();

	void kullaniciSifreGuncelleme();
	void kiyafetMenu();
	void yoneticiKiyafetMenu();
	void yoneticiAnaMenu();
	void katGoruntuleme(string);
	void faturaEkleme(string,string);
	void faturaGoruntuleme();
	void faturaGuncelleme(string,string);
	void setMusteriNo(string musterino) { musteriNo = musterino; };
	string getMusteriNo() const { return musteriNo; };
	void setId(string id) { this->id = id; };
	string idDondur() { return id; };
	void setKuryeIlce(string ilce) { kuryeIlce = ilce; };
	string getKuryeIlce() { return kuryeIlce; };
};





class dosyaIslemleri :public Kullanici {
public:
	void dosyaKaydetme(string a);
};










