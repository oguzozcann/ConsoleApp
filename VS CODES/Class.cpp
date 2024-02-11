// Oðuzhan Özcan  410453 
// Mehmet Koçak 402541

#include"Classes.h"



void Function::anaMenu() {
	 char giris;
	do
	{
		cout << "\t\t\tUye kaydi icin (1)" << endl;
		cout << "\t\t\tSisteme giris icin (2)" << endl;
		cout << "\t\t\tCikis icin (3)" << endl;
		cout << "==================================================================\n: ";
		cin >> giris;

		if (!((giris == '1') || (giris == '2') || (giris == '3')))
		{
			system("cls");
			cout << "Gecerli bir deger giriniz!\n" << endl;
		}
	} while (!((giris == '1') || (giris == '2') || (giris == '3')));

	if (giris == '1') {
		system("pause");
		system("CLS");
		hesapOlusturma();
	}
	if (giris == '2') {
		system("pause");
		system("CLS");
		sistemGiris();

	}
	if (giris == '3')
	{
		system("pause");
		system("CLS");
		cout << "Cikis yapiliyor.." << endl;
		exit(0);//bu kisimda konsol ekraný kapatma komutu bulabilirsen yap!
	}
}

void Function::hesapOlusturma() {
back:
	string email, sifre1, sifre2, adSoyad, dTarihi, adresIlce, kullaniciAdi, telNo;
	char c, c2;
	Kullanici kullanici;
	cout << "Kullanici Adi:";
	cin >> kullaniciAdi;
	while (kullanici.setKullaniciAdi(kullaniciAdi) == 0) { cin >> kullaniciAdi; system("CLS"); }
	cout << "Email:";
	cin >> email;
	while (kullanici.setEposta(email) == 0) { cin >> email; system("CLS"); }
	cout << "Ad-Soyad:";
	cin.ignore();
	getline(cin, adSoyad);
	while (kullanici.setAd_Soyad(adSoyad) == 0) { cin >> adSoyad; system("CLS"); }
	cout << "Dogum Tarihi:";
	cin >> dTarihi;
	while (kullanici.setDogumT(dTarihi) == 0) { cin >> dTarihi; system("CLS"); }
	cout << "Adres:";
	cin.ignore();
	getline(cin, adresIlce);
	while (kullanici.setAdresIlce(adresIlce) == 0) { cin >> adresIlce; system("CLS"); }
	cout << "Telefon Numarasi:";
	cin >> telNo;
	while (kullanici.TelNo(telNo) == 0) { cin >> telNo; system("CLS"); }


back1:
	sifre1 = "";
	cout << "\nSifre Olusturunuz: ";
	do
	{
		c = _getch();
		if (isprint(c))
		{
			sifre1 += c;
			cout << '*';
		}
		else if (c == 8 && !sifre1.empty())
		{
			sifre1.pop_back();
			cout << "\b \b";
		}
	} while (c != 13);
	sifre2 = "";
	while (kullanici.setKullaniciSifre(sifre1) == 0) { system("CLS"); goto back1; }
	cout << "\nSifreyi Tekrar Giriniz: ";
	do
	{
		c2 = _getch();
		if (isprint(c2))
		{
			sifre2 += c2;
			cout << '*';
		}
		else if (c2 == 8 && !sifre2.empty())
		{
			sifre2.pop_back();
			cout << "\b \b";
		}
	} while (c2 != 13);


	if (kullanici.setKullaniciAdi(kullaniciAdi) == 1 && kullanici.setEposta(email) == 1 && kullanici.setAd_Soyad(adSoyad) == 1 &&
		kullanici.setDogumT(dTarihi) == 1 && kullanici.setAdresIlce(adresIlce) == 1 && kullanici.TelNo(telNo) == 1 &&
		(kullanici.setKullaniciSifre(sifre1) == 2 || kullanici.setKullaniciSifre(sifre1) == 1)) {

	}

	if (sifre1 != sifre2)
	{
		cout << "\nGirilen Sifreler Birbiriyle Uyusmuyor Lutfen Tekrar Deneyiniz!\n";
		system("pause");
		system("CLS");
		goto back1;
	}


	dosyaIslemleri a;
	int dbSorgu = 1;
	string dbKadiSorgu = "";
	string dbEpostaSorgu = "";
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);

	string query = "SELECT * FROM kullaniciTablo";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			dbKadiSorgu = row[1];
			dbEpostaSorgu = row[2];
			if (dbKadiSorgu == kullaniciAdi)
			{
				cout << "\nBu kullanici adi daha once kullanilmis lutfen tekrar deneyiniz..." << endl;
				dbSorgu = 0;
				system("pause");
				system("CLS");
				break;
			}
			if (email == dbEpostaSorgu)
			{
				cout << "\nBu E-posta daha once kullanilmis lutfen tekrar deneyiniz..." << endl;
				dbSorgu = 0;
				system("pause");
				system("CLS");
				break;
			}
		}

	}
	if (dbSorgu==1)
	{
		kullanici.kullaniciEkleme();
		string query = "SELECT * FROM kullanicitablo";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				if (row[1]==kullaniciAdi)
				{
					musteriNo = row[0];
					setId(musteriNo);
					musteriNo = "1000" + musteriNo;
					setMusteriNo(musteriNo);
					break;
				}
			}
		}
		
		musteriAnaMenu();
	}
	else {
		goto back;
	}
}



void Function::sistemGiris() {

	Kullanici kullanici;
	string musteriNo = "";
	char giris;
	do
	{
		cout << "Yonetici girisi icin (1):" << endl;
		cout << "Musteri girisi icin (2):" << endl;
		cout << "==================================================================\n: ";
		cin >> giris;
		if (!((giris == '1') || (giris == '2')))
		{
			system("pause");
			system("CLS");
			cout << "Gecerli bir deger giriniz!\n" << endl;
		}
	} while (!((giris == '1') || (giris == '2')));

back:
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	string kullaniciAdi, sifre1;
	char c;
	string k_adi, sifre;
	int girisKontrol = 0;
	do
	{
		cout << "\nKullanici adi:";
		cin >> k_adi;
		cout << "Sifre:";
		sifre = "";
		do
		{
			c = _getch();
			if (isprint(c))
			{
				sifre += c;
				cout << '*';
			}
			else if (c == 8 && !sifre.empty())
			{
				sifre.pop_back();
				cout << "\b \b";
			}
		} while (c != 13);
		if (giris == '1') {
			conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
			if (conn) {
				string query = "SELECT * FROM yonetici";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate)
				{
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res))
					{
						kullaniciAdi = row[1];
						sifre1 = row[3];
						if (kullaniciAdi == k_adi && sifre == sifre1)
						{

							cout << "\nGiris Basarili!" << endl;
							system("pause");
							system("CLS");
							yoneticiAnaMenu();
							break;
						}
						else {
							cout << "\nLutfen kullanici adi ve sifrenizi dogru giriniz:\n";
							goto back;
						}
					}

				}
				girisKontrol = 1;
			}

		}
		else if (giris == '2') {
			conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
			if (conn) {
				string query = "SELECT * FROM kullanicitablo";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate)
				{
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res))
					{
						musteriNo = row[0];
						setId(musteriNo);
						musteriNo = "1000" + musteriNo;
						kullaniciAdi = row[1];
						sifre1 = row[7];
						if (kullaniciAdi == k_adi && sifre == sifre1)
						{
							setMusteriNo(musteriNo);
							cout << "\nGiris Basarili!" << endl;
							girisKontrol = 1;
							break;
							
						}
					}
					if (girisKontrol == 1) {
						system("pause");
						system("CLS");
						musteriAnaMenu();
					}
					else {
						cout << "\nLutfen kullanici adi ve sifrenizi dogru giriniz:\n";
						goto back;
					}

				}

			}
		}

	} while (girisKontrol == 0);
}

void Function::musteriAnaMenu() {
	int sayac;
	dosyaIslemleri a;
	char secim;
	Zaman gerisayim;
	Kurye kurye;
	do
	{
		cout << "\t\t\t\t\tMusteri Ana Menu";
		cout << "\n=========================================================================================================\n";
		cout << "\t\t\tKiyafet Kategorilerinin Gosterimi Ve Urun Secimi Icin (1)" << endl;
		cout << "\t\t\tSikayet Oneri (Geri Bildirimler) Icin (2)" << endl;
		cout << "\t\t\tSikayet Oneri (Geri Bildirimler) Goruntulemek Icin (3)" << endl;
		cout << "\t\t\tSifre Degistirmek Icin (4)" << endl;
		cout << "\t\t\tFatura Goruntulemek Icin (5)" << endl;
		cout << "\t\t\tCikis Yapmak Icin (6)" << endl;
		cout << "\n=========================================================================================================\n: ";
		cin >> secim;

		if (!((secim == '1') || (secim == '2') || (secim == '3') || (secim == '4') || (secim == '5') || (secim == '6')))
		{
			cout << "Gecerli bir deger giriniz!\n" << endl;
			system("pause");
			system("CLS");
		}
	} while (!((secim == '1') || (secim == '2') || (secim == '3') || (secim == '4') || (secim == '5') || (secim == '6')));

	
	if (secim == '1')
	{
		system("pause");
		system("CLS");
		kiyafetMenu();
	}
	else if (secim == '2')
	{
		system("pause");
		system("CLS");
		sikayetEkleme();
	}
	else if (secim == '3')
	{
		system("pause");
		system("CLS");
		sikayetGoruntulemeK();
	}
	else if (secim == '4')
	{
		system("pause");
		system("CLS");
		kullaniciSifreGuncelleme();
	}
	else if (secim == '5')
	{
		system("pause");
		system("CLS");
		int sayac = gerisayim.geriSayim();
		string kuryeIlce = getKuryeIlce();
		if (sayac == 0)
		{
			faturaGuncelleme("1000"+idDondur(), "Tamamlandi");
			kurye.kuryeGuncelleme(kuryeIlce,"pasif");
		}
		faturaGoruntuleme();
	}
	else
	{
		system("pause");
		system("CLS");
		exit(0);
	}
	
}
//---------------------------------------------------------------
void Function::kullaniciSifreGuncelleme() {
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	dosyaIslemleri a;
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
	string sifre1,sifre2,id=idDondur();

	char c, c2;
	Kullanici kullanici;
back1:
	sifre1 = "";
	cout << "\nYeni Sifrenizi Olusturunuz: ";
	do
	{
		c = _getch();
		if (isprint(c))
		{
			sifre1 += c;
			cout << '*';
		}
		else if (c == 8 && !sifre1.empty())
		{
			sifre1.pop_back();
			cout << "\b \b";
		}
	} while (c != 13);

	while (kullanici.setKullaniciSifre(sifre1) == 0) { system("CLS"); cout << "Lutfen Guclu Bir Sifre Olusturunuz.\n"; goto back1; }
	sifre2 = "";
	
	cout << "\nSifreyi Tekrar Giriniz: ";
	do
	{
		c2 = _getch();
		if (isprint(c2))
		{
			sifre2 += c2;
			cout << '*';
		}
		else if (c2 == 8 && !sifre2.empty())
		{
			sifre2.pop_back();
			cout << "\b \b";
		}
	} while (c2 != 13);
	
	if (sifre1 != sifre2)
	{
		cout << "\nGirilen Sifreler Birbiriyle Uyusmuyor Lutfen Tekrar Deneyiniz!\n";
		system("pause");
		system("CLS");
		goto back1;
	}

	if (conn) {
		string query = "UPDATE  kullanicitablo SET sifre='" + sifre1 + "' WHERE id='"+id+"'";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			cout << "Sifre Guncellendi Ana Menuye Yonlendiriliyorsunuz..." << endl;
			system("pause");
			system("CLS");
			a.dosyaKaydetme("kullanici");
			musteriAnaMenu();
		}
		else
		{
			cout << "Sistemsel bir hata oluþtu daha sonra tekrar deneyiniz!: " << mysql_error(conn) << endl;
			musteriAnaMenu();
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}

void Function::yoneticiAnaMenu() {
	Kiyafet a;
	Kurye kurye;
	char secim;
	Yonetici yonetici;
	do
	{
		cout << "\t\t\t\t\tYonetici Ana Menu";
		cout << "\n=========================================================================================================\n";
		cout << "\t\t\tKullanicilari Goruntulemek Icin (1)" << endl;
		cout << "\t\t\tUrun Girisi Icin (2)" << endl;
		cout << "\t\t\tKurye Eklemek Icin (3)" << endl;
		cout << "\t\t\tKurye Goruntulemek Icin (4)" << endl;
		cout << "\t\t\tSikayet Ve Oneri Okumak Icin (5)" << endl;
		cout << "\t\t\tIndirim Kodu Tanimlamak Icin (6)" << endl;
		cout << "\t\t\tFatura Goruntulemek Icin (7)" << endl;
		cout << "\t\t\tUrunleri Goruntulemek Icin (8)" << endl;
		cout << "\t\t\tCikis Yapmak Icin (9)" << endl;


		cout << "\n=========================================================================================================\n: ";
		cin >> secim;

		if (!((secim == '1') || (secim == '2') || (secim == '3') || (secim == '4') || (secim == '5') || (secim == '6') || (secim == '7') || (secim == '8') ||(secim=='9')))
		{
			cout << "Gecerli bir deger giriniz!\n" << endl;
			system("pause");
			system("CLS");
		}
	} while (!((secim == '1') || (secim == '2') || (secim == '3') || (secim == '4') || (secim == '5') || (secim == '6') || (secim == '7') || (secim == '8') || (secim == '9')));

	string faturaNo;
	system("pause");
	system("CLS");
	switch (secim)
	{
	case '1':
		yonetici.kullaniciGoruntule();

	case '2':
		a.kiyafetInsert();
		break;
	case '3':
		kurye.kuryeEkleme();
		break;
	case '4':
		kurye.kuryeGoruntuleme();
		break;
	case '5':
		sikayetGoruntulemeY();
		break;
	case '6':
		yonetici.yoneticiFatura();
		cout << "\nIndirim Tanimlamak Istediginiz Fatura Numarasini Girin:";
		cin >> faturaNo;
		yonetici.setIndirimliFiyat(faturaNo);
		
		break;
	case '7':
		yonetici.yoneticiFatura();
		break;
	case '8':
		a.kiyafetDisplay();
		break;
	case '9':
		exit(0);
		break;
	default:
		cout << "Gecerli Bir Deger Giriniz:" << endl;
		system("pause");
		system("CLS");
		break;
	}
}


void Function::kiyafetMenu() {
	char secim;
	do
	{
		cout << "\t\t\t\t\tKiyafet Secimi";
		cout << "\n=========================================================================================================\n";
		cout << "\t\t\tElbise Icin (1)" << endl;
		cout << "\t\t\tTisort Icin (2)" << endl;
		cout << "\t\t\tPantolon Icin (3)" << endl;
		cout << "\t\t\tGomlek Icin (4)" << endl;
		cout << "\t\t\tEtek Icin (5)" << endl;
		cout << "\t\t\tAyakkabi Icin (6)" << endl;
		cout << "\t\t\tBir Onceki Menuye Donmek Icin (7)" << endl;
		cout << "\n=========================================================================================================\n: ";
		cin >> secim;

		if (!((secim == '1') || (secim == '2') || (secim == '3') || (secim == '4') || (secim == '5') || (secim == '6') || (secim == '7')))
		{
			cout << "Gecerli bir deger giriniz!\n" << endl;
			system("pause");
			system("CLS");
		}
	} while (!((secim == '1') || (secim == '2') || (secim == '3') || (secim == '4') || (secim == '5') || (secim == '6') || (secim == '7')));


	system("pause");
	system("CLS");
	switch (secim)
	{
	case '1':
		katGoruntuleme("Elbise");

		break;
	case '2':
		katGoruntuleme("Tisort");

		break;
	case '3':
		katGoruntuleme("Pantolon");

		break;
	case '4':
		katGoruntuleme("Gomlek");
		break;
	case '5':
		katGoruntuleme("Etek");
		break;
	case '6':
		katGoruntuleme("Ayakkabi");
		break;
	case '7':
		musteriAnaMenu();
		break;
	}
}

void Function::katGoruntuleme(string secim) {
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
	string id,kontrol2;
	if (conn) {
	
		string query = "SELECT * FROM kiyafet WHERE kategori='" + secim + "'";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("ID: %s, Kategori: %s, Beden: %s Renk: %s Fiyat: %s\n", row[0], row[1], row[2], row[3], row[4]);
				kontrol2 = row[3];
			}
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}
	if (!(kontrol2==""))
	{
		cout << "Eklemek istediginiz id:" << endl;
		cin >> id;
		faturaEkleme(id,getMusteriNo());
		system("PAUSE");
		system("CLS");
		musteriAnaMenu();
	}
	else
	{
		cout << "Urun Stokta Kalmamistir..\n";
		system("PAUSE");
		system("CLS");
		musteriAnaMenu();
	}

}


void Function::faturaEkleme(string id,string musterino) {
	Zaman saat;
	dosyaIslemleri x;
	string anlikSaat,bitisSaat;
	anlikSaat = saat.CurrentHour();
	Kurye a;
	string id2 = "000";
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	string beden, renk, fiyat, kategori, faturaNo;
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
	if (conn) {
		string query = "SELECT * FROM kiyafet WHERE id='" + id + "'";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				faturaNo = row[0];
				kategori = row[1];
				beden = row[2];
				renk = row[3];
				fiyat = row[4];
				
			}
		}

		if (!renk.empty())
		{
			string ilce = a.kuryeSorgu();
			if (ilce != "YOK")
			{
				setKuryeIlce(ilce);
				bitisSaat=saat.bitisZamani(ilce);
				string siparisDurumu = "DevamEdiyor";
				cout << "Kayit olusturuluyor.\n" << endl;
				faturaNo = "0000" + faturaNo;

				string query2 = "INSERT INTO fatura(id,faturaNo,kategori,beden,renk,fiyat,hesapNo,baslangic,bitis,siparisDurumu) VALUES (NULL,'" + faturaNo + "','" + kategori + "','" + beden + "','" + renk + "','" + fiyat + "','" + musterino + "','" + anlikSaat + "','" + bitisSaat + "','" + siparisDurumu + "')";
				const char* q2 = query2.c_str();
				qstate = mysql_query(conn, q2);
				
				string query3 = "DELETE FROM kiyafet WHERE id='" + id + "'";
				const char* q3 = query3.c_str();
				qstate = mysql_query(conn, q3);
				
				system("PAUSE");
				system("CLS");
				x.dosyaKaydetme("fatura");
				x.dosyaKaydetme("kiyafet");
				musteriAnaMenu();
			}
			else
			{
				cout << "Kurye bosta yok." << endl;
			}
		}
		else
		{
			cout << "Kayit olusturulurken hata olustu.\n";
			system("PAUSE");
			system("CLS");
			musteriAnaMenu();
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}


void Function::faturaGoruntuleme() {
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	string hesapNo = getMusteriNo();
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);

	if (conn) {
		string query = "SELECT * FROM fatura WHERE hesapNo='" + hesapNo + "'";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("Urun id: %s | Fatura No: %s | Kategori: %s | Beden: %s | Renk: %s | Fiyat: %s |\nhesapNo: %s | Baslangic: %s | Bitis: %s | Siparis Durumu: %s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9]);
				cout << endl;

			}
			system("PAUSE");
			system("CLS");
			musteriAnaMenu();
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}


void Function::sikayetEkleme() {
	dosyaIslemleri a;
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
	string sikayetOneri="";
	cout << "\nLutfen Eklemek Istediginiz Sikayet Veya Onerilerinizi Giriniz: " << endl;
	cin.ignore();
	getline(cin, sikayetOneri);
	if (conn) {
		string query = "INSERT INTO sikayet(id,sikayetOneri,musteriNo) VALUES (NULL,'" + sikayetOneri + "','"+getMusteriNo()+ "')";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			cout << "\nSikayet Ve Oneri Kaydiniz Olusturuluyor..." << endl;
			system("PAUSE");
			system("CLS");
			a.dosyaKaydetme("sikayet");
			musteriAnaMenu();
		}
		else
		{
			cout << "\nSistemsel Bir hata Olustu Daha Sonra Tekrar Deneyiniz..." << mysql_error(conn) << endl;
			system("PAUSE");
			system("CLS");
			musteriAnaMenu();
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}

void Function::sikayetGoruntulemeK() {
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);

	if (conn) {
		string query = "SELECT * FROM sikayet WHERE musteriNo='"+getMusteriNo()+ "'";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("Sikayet: %s\n", row[1]);
				
				
			}
			
			system("PAUSE");
			system("CLS");
			musteriAnaMenu();
		}
		else
		{
			cout << "\nSistemsel Bir hata Olustu Daha Sonra Tekrar Deneyiniz..." << mysql_error(conn) << endl;
			system("PAUSE");
			system("CLS");
			musteriAnaMenu();
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}



void Function::sikayetGoruntulemeY() {
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);

	if (conn) {
		string query = "SELECT * FROM sikayet";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("\nSikayet: %s", row[1]);
			}
			system("PAUSE");
			system("CLS");
			yoneticiAnaMenu();
		}
		else
		{
			cout << "\nSistemsel Bir hata Olustu Daha Sonra Tekrar Deneyiniz..." << mysql_error(conn) << endl;
			system("PAUSE");
			system("CLS");
			yoneticiAnaMenu();
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}



void Function::faturaGuncelleme(string id,string durum) {
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	dosyaIslemleri a;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
	if (conn)
	{
		string query = "UPDATE  fatura SET siparisDurumu='" + durum + "' WHERE hesapNo='" + id + "'";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		a.dosyaKaydetme("fatura");
	}
}



//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void dosyaIslemleri::dosyaKaydetme(string a) {
	if (a == "kullanici")
	{
		int qstate;
		MYSQL* conn;
		MYSQL_ROW row;
		MYSQL_RES* res;
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
		if (conn) {
			string id, k_adi, eposta, ad_soyad, telefon, dTarih, adres, sifre;
			string query = "SELECT * FROM kullaniciTablo";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
			if (!qstate)
			{


				ofstream outfile("kullanici.txt");
				res = mysql_store_result(conn);
				outfile << "|ID " << "\t\t\t|Kullanici Adi " << "\t\t\t|E-Posta " << "\t\t\t\t|Ad-Soyad \t" << "\t\t\t\t|Telefon \t" << "\t\t\t\t|Dogum Tarihi " << "\t\t|Adres " << "\t\t\t|Sifre " << endl;
				outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				while (row = mysql_fetch_row(res))
				{
					id = row[0];
					k_adi = row[1];
					eposta = row[2];
					ad_soyad = row[3];
					telefon = row[4];
					dTarih = row[5];
					adres = row[6];
					sifre = row[7];
					outfile << id << "\t\t| " << k_adi << "\t\t\t| " << eposta << "\t\t\t| " << ad_soyad << "\t\t\t| " << telefon << "\t\t\t| " << dTarih << "\t\t\t| " << adres << "\t\t\t| " << sifre << "\t\t\t " << endl;
					outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

				}
				outfile.close();
			}
		}
	}
	if (a == "yonetici")
	{
		int qstate;
		MYSQL* conn;
		MYSQL_ROW row;
		MYSQL_RES* res;
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
		if (conn) {
			string id, k_adi, telefon, sifre;
			string query = "SELECT * FROM yonetici";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
			if (!qstate)
			{
				ofstream outfile("yonetici.txt");
				res = mysql_store_result(conn);
				outfile << "|ID " << "\t\t|Kullanici Adi " << "\t\t\t|Telefon " << "\t\t\t\t|Sifre " << endl;
				outfile << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
				while (row = mysql_fetch_row(res))
				{
					id = row[0];
					k_adi = row[1];
					telefon = row[2];
					sifre = row[3];
					outfile << id << "\t\t| " << k_adi << "\t\t\t| " << telefon << "\t\t\t| " << sifre << "\t\t\t " << endl;
					outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

				}
				outfile.close();
			}
		}
	}
	if (a == "kurye")
	{
		int qstate;
		MYSQL* conn;
		MYSQL_ROW row;
		MYSQL_RES* res;
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
		if (conn) {
			string id, ad_soyad, telefon, BosMu, ilce;
			string query = "SELECT * FROM kurye";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
			if (!qstate)
			{
				ofstream outfile("kurye.txt");
				res = mysql_store_result(conn);
				outfile << "|ID " << "\t\t|Ad-Soyad \t\t" << "\t\t\t|Telefon " << "\t\t\t\t|Bos Mu " << "\t\t\t|Ilce" << endl;
				outfile << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
				while (row = mysql_fetch_row(res))
				{
					id = row[0];
					ad_soyad = row[1];
					telefon = row[2];
					BosMu = row[3];
					ilce = row[4];
					outfile << id << "\t\t| " << ad_soyad << "\t\t\t\t| " << telefon << "\t\t\t| " << BosMu << "\t\t\t| " << ilce << "\t\t\t " << endl;
					outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

				}
				outfile.close();
			}
		}
	}
	if (a == "fatura")
	{
		int qstate;
		MYSQL* conn;
		MYSQL_ROW row;
		MYSQL_RES* res;
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
		if (conn) {
			string id, faturaNo, kategori, beden, renk, fiyat, hesapNo, baslangic, bitis, siparisDurumu;
			string query = "SELECT * FROM fatura";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
			if (!qstate)
			{
				ofstream outfile("fatura.txt");
				res = mysql_store_result(conn);
				outfile << "|ID\t\t" << "|Fatura No\t\t" << "|Kategori\t\t\t" << "|Beden\t\t\t\t" << "|Renk\t\t\t\t" << "|Fiyat\t\t" << "|Hesap No\t\t" << "|Baslangic\t\t\t" << "|Bitis\t\t\t\t" << "|Siparis Durumu" << endl;
				outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				while (row = mysql_fetch_row(res))
				{
					id = row[0];
					faturaNo = row[1];
					kategori = row[2];
					beden = row[3];
					renk = row[4];
					fiyat = row[5];
					hesapNo = row[6];
					baslangic = row[7];
					bitis = row[8];
					siparisDurumu = row[9];
					outfile << id << "\t\t" << faturaNo << "\t\t" << kategori << "\t\t\t " << beden << "\t\t\t" << "\t\t" << renk << "\t\t\t" << "\t" << fiyat << "\t\t" << "\t" << hesapNo << "\t\t" << baslangic << "\t\t" << bitis << "\t\t\t" << siparisDurumu << endl;
					outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

				}
				outfile.close();
			}
		}
	}
	if (a == "kiyafet")
	{
		int qstate;
		MYSQL* conn;
		MYSQL_ROW row;
		MYSQL_RES* res;
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
		if (conn) {
			string id, kategori, beden, renk, fiyat;
			string query = "SELECT * FROM kiyafet";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
			if (!qstate)
			{
				ofstream outfile("kiyafet.txt");
				res = mysql_store_result(conn);
				outfile << "|ID\t\t" << "|Kategori\t\t" << "|Beden\t\t\t" << "|Renk\t\t\t\t" << "|Fiyat" << endl;
				outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				while (row = mysql_fetch_row(res))
				{
					id = row[0];
					kategori = row[1];
					beden = row[2];
					renk = row[3];
					fiyat = row[4];
					outfile << id << "\t\t| " << kategori << "\t\t| " << beden << "\t\t" << "\t\t| " << renk << "  \t\t\t| " << fiyat << endl;
					outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

				}
				outfile.close();
			}
		}
	}

	if (a == "sikayet")
	{
		int qstate;
		MYSQL* conn;
		MYSQL_ROW row;
		MYSQL_RES* res;
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
		if (conn) {
			string id, sikayetOneri, musteriNo;
			string query = "SELECT * FROM sikayet";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
			if (!qstate)
			{
				ofstream outfile("sikayet.txt");
				res = mysql_store_result(conn);
				outfile << "|ID\t\t" << "|sikayetOneri\t\t" << "|musteriNo\t\t\t"<< endl;
				outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				while (row = mysql_fetch_row(res))
				{
					id = row[0];
					sikayetOneri = row[1];
					musteriNo = row[2];
					outfile << id << "\t\t| " << sikayetOneri << "\t\t| " << musteriNo << endl;
					outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

				}
				outfile.close();
			}
		}
	}
}



//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
Kurye::Kurye(string adSoyad, string telNo) :Kisi(adSoyad, telNo) {

}

Kurye::~Kurye() {

}


string Kurye::kuryeSorgu() {
	int qstate;
	Function function;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
	string kuryeId, kuryeIlce;
	string bosMu, kontrol;
	if (conn) {
		string query = "SELECT * FROM kurye";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				kontrol = row[3];
				if (kontrol == "pasif")
				{
					kuryeId = row[0];
					kuryeIlce = row[4];
					kuryeGuncelleme(kuryeIlce, "aktif");
					setIlce(row[4]);
					return kuryeIlce;

				}
			}
			if (kontrol == "aktif")
			{
				system("PAUSE");
				system("CLS");
				return "YOK";
			}
		}
		else
		{
			cout << "\nSistemsel Bir hata Olustu Daha Sonra Tekrar Deneyiniz..." << mysql_error(conn) << endl;
			system("PAUSE");
			system("CLS");
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}


void Kurye::kuryeGuncelleme(string ilce, string bosMu) {
	int qstate;
	dosyaIslemleri a;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
	if (conn)
	{
		string query = "UPDATE  kurye SET BosMu='" + bosMu + "' WHERE ilce='" + ilce + "'";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		a.dosyaKaydetme("Kurye");
	}
}


void Kurye::kuryeEkleme() {
	dosyaIslemleri a;
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	Kullanici kullanici;
	Function yonetici;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
	cout << "\nKurye Ekleme: " << endl;
	string id, ad_soyad, telefon, BosMu = "pasif", ilce;
	cout << "Kurye Ad-Soyad Giriniz: ";
	cin.ignore();
	getline(cin, ad_soyad);
	setAd_Soyad(ad_soyad);
	cout << "Kurye Telefon Numarasini Giriniz: ";
	cin >> telefon;
	while (TelNo(telefon) == 0) { cin >> telefon; system("CLS"); }
	cout << "Ilce Bilgisi Giriniz :";
	cin >> ilce;
	while (kullanici.setAdresIlce(ilce) == 0) { cin >> ilce; system("CLS"); }
	if (conn) {
		string query = "INSERT INTO kurye(id,ad_soyad,telefon,BosMu,ilce) VALUES (NULL,'" + ad_soyad + "','" + telefon + "','" + BosMu + "','" + ilce + "')";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			cout << "\nKurye Bilgileri Ataniyor..." << endl;
			system("PAUSE");
			system("CLS");
			a.dosyaKaydetme("kurye");
			yonetici.yoneticiAnaMenu();
		}
		else
		{
			cout << "\nSistemsel Bir hata Olustu Daha Sonra Tekrar Deneyiniz..." << mysql_error(conn) << endl;
			system("PAUSE");
			system("CLS");
			yonetici.yoneticiAnaMenu();
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}


void Kurye::kuryeGoruntuleme() {
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
	Function yonetici;
	if (conn) {
		string query = "SELECT * FROM kurye";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("Kurye Id: %s | Ad-Soyad: %s | Telefon: %s | BosMu : %s | Ilce: %s |\n", row[0], row[1], row[2], row[3], row[4]);
				cout << endl;

			}
			system("PAUSE");
			system("CLS");

			yonetici.yoneticiAnaMenu();
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Zaman::Zaman() {

}

Zaman::~Zaman() {

}
static int sayac = 30;
int Zaman::geriSayim() {
	sayac -= 5;
	return sayac - 5;
}

void Zaman::setZaman(int h, int m) {
	if (m > 0 && m < 60) {
		dakika = m;
	}
	else if (m > 60) {
		h += 1;
		m -= 60;
	}
	if (h > 0 && h > 24) {
		saat = h;
	}

}

string Zaman::CurrentHour() {
	string basla;
	time_t curr_time;
	tm* curr_tm;
	char date_string[100];
	char time_string[100];
	string anlikSaat = "";
	string anlikDakika = "";
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	strftime(time_string, 50, "%T", curr_tm);
	cout << time_string << endl;
	for (int i = 0; i < strlen(time_string); i++)
	{
		anlikSaat += time_string[i];
	}
	cout << endl;
	anlikSaat = time_string[0];
	anlikSaat += time_string[1];
	anlikDakika = time_string[3];
	anlikDakika += time_string[4];

	basla = anlikSaat + ":" + anlikDakika + ":00";

	return basla;

}

string Zaman::bitisZamani(string ilce) {
	time_t curr_time;
	tm* curr_tm;
	char date_string[100];
	char time_string[100];
	string anlikSaat = "";
	string anlikDakika = "";
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	strftime(time_string, 50, "%T", curr_tm);
	for (int i = 0; i < strlen(time_string); i++)
	{
		anlikSaat += time_string[i];
	}
	cout << endl;
	anlikSaat = time_string[0];
	anlikSaat += time_string[1];
	anlikDakika = time_string[3];
	anlikDakika += time_string[4];

	int a, b;
	istringstream(anlikDakika) >> a;
	istringstream(anlikSaat) >> b;
	if (ilce == "Arsin") {
		a += 70;
	}
	else if (ilce == "Yomra") {
		a += 55;
	}
	else if (ilce == "Arakli") {
		a += 100;
	}
	else if (ilce == "Besikduzu") {
		a += 110;
	}
	else if (ilce == "Vakfikebir") {
		a += 90;
	}
	else if (ilce == "Akcaabat") {
		a += 50;
	}
	else if (ilce == "Ortahisar") {
		a += 35;
	}

	while ((a > 60)) {
		a -= 60;
		b += 1;
	}
	setZaman(b, a);

	string saat = to_string(b);
	string dakika = to_string(a);

	string bitis = saat + ":" + dakika + ":00";
	return bitis;
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Kiyafet::Kiyafet() {

}
Kiyafet::~Kiyafet() {

}
int Kiyafet::setKategori(string kategori) {
	string urunler[] = { "Elbise","Tisort","Pantolon","Gomlek","Etek","Ayakkabi" };
	for (int i = 0; i < 6; i++) {
		if (kategori == urunler[i]) {
			this->kategori = kategori;
			return 1;
		}
	}
	cout << "Lutfen gecerli bir deger giriniz." << endl;
	return 0;
}
int Kiyafet::setBoyut(string boyut) {
	string beden[] = { "XS", "S", "M" ,"L","XL","36","37","38","39","40","41","42","43" };
	for (int i = 0; i < 13; i++) {
		if (boyut == beden[i]) {
			this->boyut = boyut;
			return 1;
		}
	}
	cout << "Lutfen gecerli bir deger giriniz." << endl;
	return 0;
}
int Kiyafet::setRenk(string renk) {
	string renkler[] = { "Siyah","Mavi","Yesil","Turuncu","Kirmizi","Beyaz","Sari","Kahverengi","Gri","Turkuaz","Bordo" };
	for (int i = 0; i < 11; i++) {
		if (renk == renkler[i]) {
			this->renk = renk;
			return 1;
		}
	}
	cout << "Lutfen gecerli bir deger giriniz." << endl;
	return 0;
}

int Kiyafet::setFiyat(double fiyat) {
	this->fiyat = fiyat;
	return 1;
}


void Kiyafet::kiyafetInsert() {
back:
	double y;
	Function a;
	string kategori;
	string beden;
	string renk;
	string fiyat;

	dosyaIslemleri x;
	cout << "Lutfen Eklemek Istediginiz Urunun Kategorisini Giriniz: ";
	cin >> kategori;
	while (setKategori(kategori) == 0) { cin >> kategori; system("CLS"); }
	cout << "Eklemek Istediginiz Urununun Bedenini Giriniz: ";
	cin >> beden;
	while (setBoyut(beden) == 0) { cin >> beden; system("CLS"); }
	cout << "Eklemek Istediginiz Urunun Rengini Giriniz: ";
	cin >> renk;
	while (setRenk(renk) == 0) { cin >> renk; system("CLS"); }
	cout << "Eklemek Istediginiz Urunun Fiyatini Giriniz: ";
	cin >> fiyat;
	istringstream(fiyat) >> y;
	setFiyat(y);
	setRenk(renk);
	setBoyut(boyut);

	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);

	if (conn) {
		string query = "INSERT INTO kiyafet(id,kategori,beden,renk,fiyat) VALUES (NULL,'" + kategori + "','" + beden + "','" + renk + "','" + fiyat + "')";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);;
		if (!qstate)
		{
			cout << "\nUrun Girisi Basarili Bir Sekilde Gerceklesti..." << endl;
			x.dosyaKaydetme("kiyafet");
			system("PAUSE");
			system("CLS");
			int secim = 0;
			cout << "Baska Bir Urun Eklemek Icin (1):\nAna Menu Icin (2)\n";
			cin >> secim;
			if (secim == 1)
			{
				system("PAUSE");
				system("CLS");
				goto back;
			}
			if (secim == 2) {
				system("PAUSE");
				system("CLS");
				a.yoneticiAnaMenu();
			}
		}
		else
		{
			cout << "\nSistemsel Bir hata Olustu Daha Sonra Tekrar Deneyiniz..." << mysql_error(conn) << endl;
			system("PAUSE");
			system("CLS");
			a.yoneticiAnaMenu();
		}
	}
	else {
		puts("Connection to database has failed!");
	}

}

void Kiyafet::kiyafetDisplay() {
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	Function a;
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);

	if (conn) {
		string query = "SELECT * FROM kiyafet";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("Urun id: %s | Kategori: %s | Beden: %s | Renk: %s | Fiyat: %s |\n", row[0], row[1], row[2], row[3], row[4]);
			}
			system("pause");
			system("CLS");
			a.yoneticiAnaMenu();
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Kisi::Kisi() {

}
Kisi::Kisi(string adSoyad, string telNo) {
	setAd_Soyad(adSoyad);
	TelNo(telNo);
}
Kisi::~Kisi() {

}

int Kisi::setAd_Soyad(string adSoyad) {
	ad_soyad = adSoyad;
	return 1;

}


int Kisi::TelNo(string telNo) {
	string telKontrol = "";
	if (telNo.length() != 11 && (telNo[0] != 0 && telNo[1] != 5)) {
		cout << "Telefon Bilgileriniz Hatali lutfen tekrar deneyiniz.";
		return 0;
	}
	for (int i = 0; i < telNo.length(); i++) {
		if (!(isDigit(telNo[i]))) {
			cout << "Telefon Bilgileriniz Hatali lutfen tekrar deneyiniz.";
			return 0;
		}
	}
	telKontrol = telNo[2];

	if (telKontrol == "0" || telKontrol == "3" || telKontrol == "4" || telKontrol == "5") {
		this->telefon = telNo;
		return 1;
	}
}
bool Kisi::isDigit(const char c) {
	return (c >= '0' && c <= '9');
}

bool Kisi::isChar(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}
bool Kisi::isSpecialChar(const char c) {
	return (c == '-' || c == '.' || c == '_' || c == '@');
}




//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Kullanici::Kullanici(string KullaniciAdi, string KullaniciEposta,string KullaniciAdresIlce, string KullaniciSifre, string KullaniciDTarihi, string adSoyad, string telNo)
	:Kisi(adSoyad, telNo)
{


}
Kullanici::~Kullanici() {

}

int Kullanici::setKullaniciAdi(string kullaniciAdi) {
	if (kullaniciAdi.length() < 8) {
		cout << "\nKullanici adiniz hatali lutfen tekrar deneyiniz:";
		return 0;
	}
	else {
		char ch;
		for (int i = 0; i < kullaniciAdi.length(); i++) {
			ch = kullaniciAdi[i];
			if (!(isChar(ch) || isDigit(ch))) {
				cout << "\nKullanici adiniz hatali lutfen tekrar deneyiniz:";
				return 0;
			}
		}
		k_adi = kullaniciAdi;
		return 1;

	}


}


int Kullanici::setEposta(string email)
{

	if (!isChar(email[0])) {
		cout << "\nEposta bilgileriniz hatali lutfen tekrar deneyiniz:";
		return 0;
	}

	int size = email.length();
	int At = 0, At2 = 0, At3 = 0;

	string test = "@gmail.com";
	string test2 = "@hotmail.com";
	string test3 = "@ktu.edu.tr";
	int num = 0;

	char ch = email[0];
	char ch2 = email[0];
	for (int i = 0; i < size; i++) {
		ch = email[i];
		if (!(isDigit(ch) || isChar(ch) || isSpecialChar(ch))) {
			cout << "\nEposta bilgileriniz hatali lutfen tekrar deneyiniz:";
			return 0;
		}
		if (ch == '@') {
			num++;
		}
	}
	if (num != 1) {
		cout << "\nEposta bilgileriniz hatali lutfen tekrar deneyiniz:";
		return 0;
	}
	for (int i = 0; i < size; i++) {
		if (email[i] <= size - 1) {
			ch = email[i + 1];
		}
		ch2 = email[i];
		if (!(isDigit(ch) || isChar(ch)) && !(isDigit(ch2) || isChar(ch2))) {
			cout << "\nEposta bilgileriniz hatali lutfen tekrar deneyiniz:";
			return 0;
		}
	}
	At = email.find(test);
	At2 = email.find(test2);
	At3 = email.find(test3);

	if (At != string::npos) {
		eposta = email;
		return 1;
	}
	else if (At2 != string::npos) {
		eposta = email;
		return 1;
	}
	else if (At3 != string::npos) {
		eposta = email;
		return 1;
	}
	else {
		cout << "\nEposta bilgileriniz hatali lutfen tekrar deneyiniz:";
		return 0;
	}
}
int Kullanici::setAdresIlce(string kullaniciAdresIlce) {
	if (ilceBilgisi(kullaniciAdresIlce)) {
		this->adres = kullaniciAdresIlce;
		return 1;
	}
	cout << "\nAdres-Ilce bilgileriniz hatali lutfen tekrar deneyiniz:";
	return 0;

}
int Kullanici::setDogumT(string kullaniciDTarihi) {

	string temp;

	if (kullaniciDTarihi.length() == 10)
	{
		if (kullaniciDTarihi[2] == '-' && kullaniciDTarihi[5] == '-')
		{
			int tempDay, tempMonth, tempYear;

			temp = kullaniciDTarihi[0];
			temp += kullaniciDTarihi[1];
			temp += kullaniciDTarihi[2];
			temp += kullaniciDTarihi[3];
			tempYear = stoi(temp);
			temp = "";

			temp = kullaniciDTarihi[3];
			temp += kullaniciDTarihi[4];
			//convert string to int
			tempMonth = stoi(temp);

			temp = "";
			temp = kullaniciDTarihi[0];
			temp += kullaniciDTarihi[1];
			//convert string to int
			tempDay = stoi(temp);
			temp = "";





			//convert string to int
			temp = "";
			if (tempYear >= 1965 && tempYear <= 2005 && tempMonth > 0 && tempMonth <= 12)
			{
				if ((tempMonth == 9 || tempMonth == 4 || tempMonth == 6 || tempMonth == 11) && tempDay > 0 && tempDay <= 30)
				{
					dtarih = kullaniciDTarihi;
					return 1;

				}
				else if (tempMonth == 2 && tempDay > 0 && tempDay <= 28)
				{
					dtarih = kullaniciDTarihi;
					return 1;

				}
				else
				{
					if (tempDay > 0 && tempDay <= 31)
					{
						dtarih = kullaniciDTarihi;
						return 1;
					}
				}

			}
			else {
				cout << "\nDogum Tarihi bilgileriniz hatali. Lutfen tekrar deneyiniz:";
				return 0;
			}
		}

	}
	else {
		cout << "\nDogum Tarihi bilgileriniz hatali. Lutfen tekrar deneyiniz:";
		return 0;
	}
	dtarih = kullaniciDTarihi;
	return 1;

}
int Kullanici::setKullaniciSifre(string kullaniciSifre) {
	int n = kullaniciSifre.length();
	// Buyuk Kucuk Harf Kontrolu
	bool hasLower = false, hasUpper = false;
	bool hasDigit = false, specialChar = false;
	string normalChars = "abcdefghijklmnopqrstu" "vwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
	for (int i = 0; i < n; i++) {
		if (islower(kullaniciSifre[i]))
			hasLower = true;
		if (isupper(kullaniciSifre[i]))
			hasUpper = true;
		if (isdigit(kullaniciSifre[i]))
			hasDigit = true;
		size_t special = kullaniciSifre.find_first_not_of(normalChars);
		if (special != string::npos)
			specialChar = true;
	}
	// Olusturulan Sifrenin Gucu
	if (hasLower && hasUpper && hasDigit && specialChar && (n >= 8)) {
		sifre = kullaniciSifre;
		return 2;   //SIFRE GUCLU
	}

	else if ((hasLower || hasUpper) && specialChar && (n >= 6)) {
		sifre = kullaniciSifre;
		return 1;   //SIFRE ORTA
	}

	else {
		cout << "\nSifreniz Zayif Lutfen guclu-orta bir sifre girerek tekrar deneyiniz.";
		return 0;   //SIFRE ZAYIF
	}


}
bool Kullanici::ilceBilgisi(string ilce) {
	string ilceler[] = { "Vakfikebir","Yomra","Ortahisar","Akcaabat","Arakli","Arsin","Besikduzu" };

	for (int i = 0; i < 7; i++) {
		if (ilce == (ilceler[i])) {
			return true;
		}
	}
	return false;
}

void Kullanici::kullaniciEkleme() {
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	dosyaIslemleri a;
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);

	if (conn) {
		puts("Successful connection to database!");
		string query = "INSERT INTO kullanicitablo(id,k_adi,eposta,ad_soyad,telefon,dtarih,adres,sifre) VALUES (NULL,'" + k_adi + "','" + eposta + "','" + ad_soyad + "','" + telefon + "','" + dtarih + "','" + adres + "','" + sifre + "')";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			cout << "Kayit olusturuluyor." << endl;
			a.dosyaKaydetme("kullanici");
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
Yonetici::Yonetici() {

}
Yonetici::~Yonetici() {

}

void Yonetici::setIndirimliFiyat(string fatura) {
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	Function a;
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
	string tutar = "";
	double toplamTutar = 0, temp = 0;
	if (conn) {
		puts("Successful connection to database!");
		string query = "SELECT * FROM fatura";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				if (fatura == row[1])
				{
					tutar = row[5];
					istringstream(tutar) >> temp;
					toplamTutar += temp;
					break;
				}
			}
		}
		

	}



	if (toplamTutar >= 700)
	{
		toplamTutar = toplamTutar - (toplamTutar * 30) / 100;
		tutar = to_string(toplamTutar);
		fiyatGuncelleme(fatura, tutar);
	}
	else if (toplamTutar >= 400 && toplamTutar <= 700)
	{
		toplamTutar = toplamTutar - (toplamTutar * 15) / 100;
		tutar = to_string(toplamTutar);
		fiyatGuncelleme(fatura, tutar);
	}
	else
	{
		tutar = to_string(toplamTutar);
		fiyatGuncelleme(fatura, tutar);
	}
	system("PAUSE");
	system("CLS");
	a.yoneticiAnaMenu();

}

void Yonetici::fiyatGuncelleme(string fatura, string fiyat) {
	int qstate;
	dosyaIslemleri a;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
	if (conn)
	{
		string query = "UPDATE  fatura SET fiyat='" + fiyat + "' WHERE faturaNo='" + fatura + "'";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		a.dosyaKaydetme("fatura");
	}
}

void Yonetici::yoneticiFatura() {
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
	Function yonetici;
	if (conn) {
		string query = "SELECT * FROM fatura";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("Urun id: %s | Fatura No: %s | Kategori: %s | Beden: %s | Renk: %s | Fiyat: %s |\nhesapNo: %s | Baslangic: %s | Bitis: %s | Siparis Durumu: %s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9]);
				cout << endl;

			}
			system("PAUSE");
			system("CLS");
			yonetici.yoneticiAnaMenu();
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}


void Yonetici::kullaniciGoruntule() {

	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "password", "db", 3306, "password", 0);
	Function yonetici;
	if (conn) {
		string query = "SELECT * FROM kullaniciTablo";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("Id: %s | Kullanici Adi: %s | Eposta: %s | Ad Soyad : %s | Telefon: %s | Dogum Tarihi : %s | Adres: %s\n", row[0], row[1], row[2], row[3], row[4],row[5],row[6]);
				cout << endl;

			}
			system("PAUSE");
			system("CLS");

			yonetici.yoneticiAnaMenu();
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}




