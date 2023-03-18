#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Contact 
{
private:	
	char* nume;
	char* prenume;
	int telefon[10];
	string email;

public:
	Contact() 
	{
		this->nume = new char[strlen("Necunoscut") + 1];
		strcpy(this->nume, "Necunoscut");
		this->prenume = new char[strlen("Necunoscut") + 1];
		strcpy(this->prenume, "Necunoscut");
		telefon[0] = 0;
		telefon[1] = 7;
		for (int i = 2; i < 10; i++) 
		{
			telefon[i] = 0;
		}
		this->email = "Necunoscut";
	}

	Contact(const char* nume, const char* prenume, string telefon, string email)
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->prenume = new char[strlen(prenume) + 1];
		strcpy(this->prenume, prenume);
		for (int i = 0; i < 10; i++) 
		{
			this->telefon[i] = telefon[i] - '0';
		}
		this->email = email;
	}

	Contact(const Contact& c) 
	{
		this->nume = new char[strlen(c.nume) + 1];
		strcpy(this->nume, c.nume);
		this->prenume = new char[strlen(c.prenume) + 1];
		strcpy(this->prenume, c.prenume);
		for (int i = 0; i < 10; i++) 
		{
			this->telefon[i] = c.telefon[i];
		}
		this->email = c.email;
	}
	
	~Contact() {
		if (nume != nullptr) 
		{
			delete[]this->nume;
		}
		if (prenume != nullptr) 
		{
			delete[]this->prenume;
		}
	}

	char* getNume() 
	{
		return this->nume;
	}
	char* getPrenume() 
	{
		return this->prenume;
	}
	int* getTelefon() 
	{
		return this->telefon;
	}
	string getEmail() 
	{
		return this->email;
	}

	explicit operator string() 
	{
		string telefon = "";
		for (int i = 0; i < 10; i++) 
		{
			telefon += to_string(this->telefon[i]);
		}
		return telefon;
	}

	Contact& operator=(const Contact& c) 
	{
		if (nume != nullptr) 
		{
			delete[]this->nume;
		}
		if (prenume != nullptr) 
		{
			delete[]this->prenume;
		}
		this->nume = new char[strlen(c.nume) + 1];
		strcpy(this->nume, c.nume);
		this->prenume = new char[strlen(c.prenume) + 1];
		strcpy(this->prenume, c.prenume);
		for (int i = 0; i < 10; i++) {
			this->telefon[i] = c.telefon[i];
		}
		this->email = c.email;
		return *this;
	}
	
	friend ostream& operator<<(ostream& out, Contact& c);
	friend istream& operator>>(istream& in, Contact& c);
};

ostream& operator<<(ostream& out, Contact& c) 
{
	out << "Nume: " << c.nume << endl;
	out << "Prenume: " << c.prenume << endl;
	out << "Telefon: ";
	for (int i = 0; i < 10; i++) 
	{
		out << c.telefon[i];
	}
	out << endl;
	out << "Email: " << c.email << endl;
	return out;
}

istream& operator>>(istream& in, Contact& c) 
{
	cout << "Nume: ";
	char buffer[50];
	in >> buffer;
	if (c.nume != nullptr) 
	{
		delete[] c.nume;
	}
	c.nume = new char[strlen(buffer) + 1];
	strcpy(c.nume, buffer);

	cout << "Prenume: ";
	in >> buffer;
	if (c.prenume != nullptr) 
	{
		delete[] c.prenume;
	}
	c.prenume = new char[strlen(buffer) + 1];
	strcpy(c.prenume, buffer);

	cout << "Telefon: ";
	in >> buffer;
	while (strlen(buffer) != 10) 
	{
		cout << endl << "Numarul de telefon trebuie sa aiba 10 cifre!" << endl << endl;
		cout << "Telefon: ";
		in >> buffer;
	}
	for (int i = 0; i < 10; i++) {
		c.telefon[i] = buffer[i] - '0';
	}

	cout << "Email: ";
	in >> c.email;

	return in;
}

class Agenda 
{
private:
	int nrContacte;
	Contact* contacte;

public:
	Agenda() = default;
	Agenda(Contact* contacte, int nrContacte) 
	{
		this->contacte = new Contact[nrContacte];
		for (int i = 0; i < nrContacte; i++) 
		{
			this->contacte[i] = contacte[i];
		}
		this->nrContacte = nrContacte;
	}
	Agenda(const Agenda& a) 
	{
		this->contacte = new Contact[a.nrContacte];
		for (int i = 0; i < a.nrContacte; i++) 
		{
			this->contacte[i] = a.contacte[i];
		}
		this->nrContacte = a.nrContacte;
	}

	~Agenda() 
	{
		if (contacte != nullptr) 
		{
			delete[]this->contacte;
		}
	}

	int getNrContacte() 
	{
		return this->nrContacte;
	}
	
	Agenda& operator=(const Agenda& a) 
	{
		if (this->contacte != nullptr) 
		{
			delete[]this->contacte;
		}
		this->contacte = new Contact[a.nrContacte];
		for (int i = 0; i < a.nrContacte; i++) 
		{
			this->contacte[i] = a.contacte[i];
		}
		this->nrContacte = a.nrContacte;
		return *this;
	}

	Agenda& operator+=(Contact& c) 
	{
		Contact* temp = new Contact[this->nrContacte + 1];
		for (int i = 0; i < this->nrContacte; i++) 
		{
			temp[i] = this->contacte[i];
		}
		temp[this->nrContacte] = c;
		if (this->contacte != nullptr) 
		{
			delete[]this->contacte;
		}
		this->contacte = temp;
		this->nrContacte++;
		return *this;
	}

	Agenda& operator-=(string telefon) 
	{
		int index = -1;
		for (int i = 0; i < this->nrContacte; i++) 
		{
			if (telefon == (string)this->contacte[i]) 
			{
				index = i;
				break;
			}
		}
		if (index != -1) 
		{
			Contact* temp = new Contact[this->nrContacte - 1];
			for (int i = 0; i < index; i++) {
				temp[i] = this->contacte[i];
			}
			for (int i = index; i < this->nrContacte - 1; i++) 
			{
				temp[i] = this->contacte[i + 1];
			}
			if (this->contacte != nullptr) 
			{
				delete[] this->contacte;
			}
			this->contacte = temp;
			this->nrContacte--;

			cout << endl << "Contactul a fost sters cu succes!" << endl;
		}
		else 
		{
			cout << endl << "Contact este inexistent!" << endl;
		}
		return *this;
	}

	Contact& operator[](int index) 
	{
		return this->contacte[index];
	}

	friend ostream& operator<<(ostream& out, Agenda& a);
	friend istream& operator>>(istream& in, Agenda& a);
};


ostream& operator<<(ostream& out, Agenda& a) 
{
	for (int i = 0; i < a.nrContacte; i++) 
	{
		out << a.contacte[i] << endl;
	}
	return out;
}

istream& operator>>(istream& in, Agenda& a) 
{
	cout << "Numar contacte: ";
	in >> a.nrContacte;
	if (a.contacte != nullptr) 
	{
		delete[] a.contacte;
	}
	a.contacte = new Contact[a.nrContacte];
	for (int i = 0; i < a.nrContacte; i++) 
	{
		cout << "Contact " << i + 1 << endl;
		in >> a.contacte[i];
	}
	return in;
}

void adaugaContact(Agenda& a) 
{
	cout << endl << "ADAUGARE CONTACT" << endl;
	Contact c;
	cin >> c;
	a += c;
}
void stergeContact(Agenda& a) 
{
	cout << endl << "STERGERE CONTACT" << endl;

	string telefon;
	cout << "Telefon: ";
	cin >> telefon;
	a -= telefon;
}
void afiseazaAgenda(Agenda& a) 
{
	cout << endl << "AGENDA" << endl;
	if (a.getNrContacte() == 0) 
	{
		cout << "Agenda este goala" << endl;
	}
	else 
	{
		cout << a;
	}
}
void cautareContact(Agenda& a) 
{
	cout << endl << "CAUTARE CONTACT" << endl;

	string cautare;
	cout << "Cautare: ";
	cin >> cautare;
	cout << endl;

	bool gasit = false;
	for (int i = 0; i < a.getNrContacte(); i++) 
	{
		if (((string)a[i]).find(cautare) != string::npos || strstr(a[i].getNume(), cautare.c_str()) != nullptr || strstr(a[i].getPrenume(), cautare.c_str()) != nullptr) {
			cout << a[i] << endl;
			gasit = true;
		}
	}
	if (!gasit) 
	{
		cout << "Nu s-a gasit niciun contact care sa contina " << cautare << endl;
	}
}

int main()
{
	cout << "APLICATIE AGENDA TELEFONICA" << endl << endl;

	Agenda a;

	while (1)
	{
		cout << "Meniu:" << endl;
		cout << "\t1. Adaugare contact" << endl;
		cout << "\t2. Stergere contact" << endl;
		cout << "\t3. Afisare agenda" << endl;
		cout << "\t4. Cautare contact" << endl;
		cout << "\t5. Iesire" << endl;
		cout << endl << "Alegeti o optiune: ";

		int optiune;
		cin >> optiune;

		switch (optiune) 
		{
		case 1:
			adaugaContact(a);
			break;
		case 2:
			stergeContact(a);
			break;
		case 3:
			afiseazaAgenda(a);
			break;
		case 4:
			cautareContact(a);
			break;
		case 5:
			return 0;
		default:
			cout << endl << "Optiune invalida!" << endl;
			break;
		}
		cout << endl;
	}

	return 0;
}