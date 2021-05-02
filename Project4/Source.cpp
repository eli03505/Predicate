#include<iostream>
#include<fstream>
using namespace std;

class Person {
	string name;
	double phone;
public:
	Person() = default;
	Person(const string name, const double phone) {
		setName(name);
		setPhone(phone);
	}
	string getName()const {
		return name;
	}
	int getPhone()const {
		return phone;
	}
	void setName(const string name) {
		this->name = name;
	}
	void setPhone(const double phone) {
		this->phone = phone;
	}
	void show()const {
		cout << "Name: " << getName() << endl;
		cout << "Phone: " << getPhone() << endl;
	}
};
class President {
	string name;
	string country;
	int person_count = 0;
public:
	Person** persons;
	President() = default;
	President(const string name, const string country, Person** person, int count)
	{
		setName(name);
		setCountry(country);
		setPerson(person);
		setCount(count);
	}
	string getName()const {
		return name;
	}
	int getCount()const {
		return person_count;
	}
	string getCountry()const {
		return country;
	}
	Person** getPerson()const {
		return persons;
	}
	void setName(const string name) {
		if (!name.empty()) {
			this->name = name;
		}
	}
	void setCount(const int count) {
		if (count >= 0) {
			this->person_count = count;
		}
	}
	void setCountry(const string country) {
		if (!country.empty()) {
			this->country = country;
		}
	}
	void setPerson(Person** persons) {
		this->persons = persons;
	}
	void addPresident(Person* person) {
		auto newPerson = new Person * [person_count + 1]{};
		for (int i = 0; i < person_count; i++)
		{
			newPerson[i] = persons[i];
		}
		newPerson[person_count] = person;
		++person_count;
		persons = newPerson;
		newPerson = nullptr;
	}
	void show()const {
		cout << "Name: " << getName() << endl;
		cout << "Country: " << getCountry() << endl;
		for (int i = 0; i < person_count; i++)
		{
			persons[i]->show();
		}
	}
};
class FileHelper {
public:
	static string filename;
	static void Save(President jp) {
		ofstream fout("Data.txt", ios::app);
		if (fout.is_open()) {
			fout << jp.getName() << endl;
			fout << jp.getCountry() << endl;
			for (size_t i = 0; i < jp.getCount(); i++)
			{
				fout << jp.persons[i]->getName() << "  " << jp.persons[i]->getPhone() << endl;
			}
			fout.close();
		}
	}
	static President getPresident() {
		President pr;
		ifstream fin("Data.txt");
		if (fin.is_open()) {
			string name;
			fin >> name;
			pr.getName() = name;
			int count;
			fin >> count;
			for (size_t i = 0; i < count; i++)
			{
				Person* p = new Person;
				string name;
				int phone;
				fin >> name >> phone;
				p->setName(name);
				p->setPhone(phone);
				pr.addPresident(p);
			}
			fin.close();
		}
		return pr;
	}
};
void main() {
	Person* person1 = new Person("Ali", 998799399);
	Person* person2 = new Person("Murad", 775966907);
	Person** persons = new Person * [2]{ person1,person2 };

	President president("Ali", "Baku", persons, 2);
	president.addPresident(person2);
	president.show();
	FileHelper::Save(president);
	president.show();
}