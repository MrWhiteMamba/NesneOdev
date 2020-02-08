#include <iostream>
#include <fstream>
#include<math.h>
#include<time.h>
using namespace std;

template <class Type>

class Matrix {
protected:

	Type **data;
	int satir;
	int sutun;

private:

	char birim;
	int size;

public:

	Matrix(int Satir = 10, int Sutun = 10, int Birim = 0) {
		satir = Satir;
		sutun = Sutun;
		birim = Birim;
		size = satir * sutun;

		data = new Type*[satir];
		for (int i = 0; i < satir; i++) {
			data[i] = new Type[sutun];
		}


		if (char(birim) == 'r') { // r degeri girildigi zaman alacagi deger
			srand(time(NULL));
			for (int i = 0; i < satir; i++) {
				for (int k = 0; k < sutun; k++) {
					data[i][k] = (rand() % 256) + 1;
				}
			}
		}

		else if (char(birim) == 'e') {  // e degeri girildi zaman alacagi deger
			for (int i = 0; i < satir; i++) {
				for (int k = 0; k < sutun; k++) {
					if (i == k)
						data[i][k] = 1;
					else
						data[i][k] = 0;
				}
			}

		}

		else {   // main fonksiyondan birime deger veriliyorsa birimi matrise atamam
			for (int i = 0; i < satir; i++) {
				for (int k = 0; k < sutun; k++) {
					data[i][k] = birim;
				}
			}
		}

	} // MATRIS STRUCTOR'UN BITISI

	~Matrix() { // destruct
		/*for (int i = 0; i < satir; i++) {
			delete data[i];
		}
		delete data;*/
	}
	void print() { // print fonksiyonu
		for (int i = 0; i < satir; i++) {
			for (int k = 0; k < sutun; k++) {
				cout << data[i][k] << "   ";
			}
			cout << endl;
		}cout << endl;
	}
	void printFile(string dosya) { // yazma islemini yapan fonksiyon
		ofstream file;
		file.open(dosya);
		for (int i = 0; i < satir; i++) {
			for (int k = 0; k < sutun; k++) {
				file << data[i][k] << "   ";
			}
			file << endl;
		}file << endl;
		file.close();
	}
	Type emul(Matrix &e) {        // emul fonksiyonu
		for (int i = 0; i < satir; i++)
		{
			for (int k = 0; k < sutun; k++)
			{
				data[i][k] *= e.data[i][k];
			}
		}
		return 0;
	}

	void resize(int x, int y) { // resize fonksiyonu

		Type **rData;
		if(satir==x && sutun==y){
          return;
		}

		rData = new Type*[x];
		for (int i = 0; i < x; i++) {
			rData[i] = new Type[y];
		}

		for (int i = 0; i < x; i += 1) {
			for (int j = 0; j < y; j += 1) {
				rData[i][j] = 0;
			}
		}
		if (x <= satir && y <= sutun) {
			int buffer[x][y];
			for (int i = 0; i < x; i += 1) {
				for (int j = 0; j < y; j += 1) {
					rData[i][j] = data[i][j];
				}
			}
		}
		else if (x >= satir && y >= sutun) {
			for (int i = 0; i < satir; i += 1) {
				for (int j = 0; j < sutun; j += 1) {
					rData[i][j] = data[i][j];
				}
			}
		}
		else if (x <= satir && y >= sutun) {
			for (int i = 0; i < x; i += 1) {
				for (int j = 0; j < sutun; j += 1) {
					rData[i][j] = data[i][j];
				}
			}
		}
		else if (x >= satir && y <= sutun) {
			for (int i = 0; i < satir; i += 1) {
				for (int j = 0; j < y; j += 1) {
					rData[i][j] = data[i][j];
				}
			}
		}
			for(int i=0;i<satir;i++){
        delete [] data[i];
      }
			delete[] data;
			data=rData;
			satir = x;
			sutun = y;

		return;

	}

	Matrix inv() { // matrisin tersi fonksiyonu

	Matrix b(satir, sutun, 'e'); // birim matris olusturdum

	float d, f;
	for (int i = 0; i < satir; i++) {
		d = data[i][i];
		for (int k = 0; k < sutun; k++) {
			data[i][k] = data[i][k] / d;
			b.data[i][k] = b.data[i][k] / d;
		}
		for (int x = 0; x < satir; x++) {
			if (x != i) {
				f = data[x][i];
				for (int k = 0; k < sutun; k++) {
					data[x][k] = data[x][k] - (data[i][k] * x);
					b.data[x][k] = b.data[x][k] - (b.data[i][k] * x);
				}
			}
		}
	}
	return b;
	}

	double det() { // Determinant alan fonksiyon
		int dete;
		float  ratio;
		int i, j, k, n;

		if (satir == 1 && sutun == 1) {
			return data[0][0];
		}

		else if (satir == 2 && sutun == 2) {
			return ((data[0][0] * data[1][1]) - (data[1][0] * data[0][1]));
		}
		else {
			for (i = 0; i < satir; i++) {
				for (j = 0; j < sutun; j++) {
					if (j > i) {
						ratio = data[j][i] / data[i][i];
						for (k = 0; k < sutun; k++) {
							data[j][k] -= ratio * data[i][k];
						}
					}
				}
			}
			dete = 1;
			for (i = 0; i < sutun; i++)
				dete *= data[i][i];
			return dete;
		}
	}
void T() {         // Transpoze fonksiyonu
		int buffer = 0;
    int deg;
    if(satir>sutun){
      deg=satir;
    }
    else 
      deg=sutun;
    Matrix m(deg,deg,0);
    if(satir==sutun){
    for (int i = 0; i < satir; i++) {
			for (int k = i; k < sutun; k++)
			{
        buffer=data[i][k];
				data[i][k] = data[k][i];
        data[k][i]=buffer;
			}
		}
    }
    else{
  	for (int i = 0; i < satir; i++) {
			for (int k = 0; k < sutun; k++)
			{
				m.data[k][i] = data[i][k];
			}
		}
		m.resize(sutun, satir);
    this->sutun=m.sutun;
    this->satir=m.satir;
    this->data=m.data;
    return;
    }

	}


	//------------------------------------//
	//MATRIS ILE MATRIS OVERLOADING OPERATOR FONKSIYONLARI //


	Matrix operator + (const Matrix &x) { // matris toplama islemini yaptigim fonksiyon

		Matrix xYeni;
		xYeni.satir = this->satir;
		xYeni.sutun = this->sutun;
		xYeni.sutun = this->sutun;
		for (int i = 0; i < satir; i++) {
			for (int k = 0; k < sutun; k++) {
				xYeni.data[i][k] = this->data[i][k] + x.data[i][k];
			}
		}
		return xYeni;
	}
	Matrix operator - (const Matrix &x) { // matris cikarma islemini yaptigim fonksiyon

		Matrix xYeni;
		xYeni.satir = this->satir;
		xYeni.sutun = this->sutun;
		xYeni.sutun = this->sutun;
		for (int i = 0; i < satir; i++) {
			for (int k = 0; k < sutun; k++) {
				xYeni.data[i][k] = this->data[i][k] - x.data[i][k];
			}
		}
		return xYeni;
	}

	// -------------------------------- //
	//MATRIS ILE SAYI OVERLOADING OPERATOR FONKSIYONLARI //

	Matrix operator * (const int &s) { // matris US ALMA islemini yaptigim fonksiyon
	//-- s -> sayi --//
		Matrix sYeni;
		sYeni.satir = this->satir;
		sYeni.sutun = this->sutun;
		sYeni.sutun = this->sutun;
		for (int i = 0; i < satir; i++) {
			for (int k = 0; k < sutun; k++) {
				sYeni.data[i][k] = this->data[i][k] * data[i][k];
			}
		}
		return sYeni;
	}

	Matrix operator - (const int &s) { // matris SAYI CIKARMA islemini yaptigim fonksiyon

		Matrix sYeni;
		sYeni.satir = this->satir;
		sYeni.sutun = this->sutun;
		sYeni.sutun = this->sutun;
		for (int i = 0; i < satir; i++) {
			for (int k = 0; k < sutun; k++) {
				sYeni.data[i][k] = this->data[i][k] - s;
			}
		}
		return sYeni;
	}
	Matrix operator + (const int &s) { // matris SAYI TOPLAMA islemini yaptigim fonksiyon

		Matrix sYeni;
		sYeni.satir = this->satir;
		sYeni.sutun = this->sutun;
		sYeni.sutun = this->sutun;
		for (int i = 0; i < satir; i++) {
			for (int k = 0; k < sutun; k++) {
				sYeni.data[i][k] = this->data[i][k] + s;
			}
		}
		return sYeni;
	}
	Matrix operator / (const int &s) { // matris SAYI BOLME islemini yaptigim fonksiyon

		Matrix sYeni;
		sYeni.satir = this->satir;
		sYeni.sutun = this->sutun;
		sYeni.sutun = this->sutun;
		for (int i = 0; i < satir; i++) {
			for (int k = 0; k < sutun; k++) {
				sYeni.data[i][k] = this->data[i][k] / s;
			}
		}
		return sYeni;
	}
	Matrix operator % (const int &s) {//matris SAYI BOLUMUNDEN KALANI BULME islemini yaptigim fonksiyon

		Matrix sYeni;
		sYeni.satir = this->satir;
		sYeni.sutun = this->sutun;
		sYeni.sutun = this->sutun;
		for (int i = 0; i < satir; i++) {
			for (int k = 0; k < sutun; k++) {
				sYeni.data[i][k] = this->data[i][k] % s;
			}
		}
		return sYeni;
	}
};

int main()
{
	Matrix<int> *m1 = new Matrix<int>(3,3,9);
	m1->print();
Matrix<int> *m2 = new Matrix <int>(3,3,'r');
	m2->print();

	*(m1) = *(m1) % 12;
  m1->print();
 // m2->T();
  m2->print();
  m1->inv();
m1->print();
Matrix<double> *m3 = new Matrix <double>(3,3,'r');
 m3->print();
cout<<m3->det()<<endl;
 m3->print();
 





}