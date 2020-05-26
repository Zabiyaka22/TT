#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<unordered_map>

using namespace std;

struct Contact{
	string number, name, adress;
	int  id = -1;
	
};

Contact operator >> (istream& stream, Contact& a){
		string name, number, adress;
		cin >> a.name >> a.number >> a.adress;
		return a;
}


ostream& operator << (ostream& stream, Contact a){
		stream << a.name << ' ' << a.number << ' ' << a.adress << ' ' << a.id;
		return stream;
}

class PhoneBook{
	private:
		int num = 1;
		unordered_map<int, Contact> exist;
		void MakeId(Contact& current){
			cout << "Id is " << num << '\n';
			current.id = num++;
		}
		
		void CheckIfUniqueNumber(const Contact& current) const{
			for(const auto& i: exist){
				if (i.second.number == current.number){
					throw runtime_error("Error: a few people have an equal number");
				}
			}
		}
		void CheckIfUniqueName(const Contact& current) const {
			for(const auto& i: exist){
				if (i.second.name == current.name){
					throw runtime_error("Error: a few people have an equal name");
				}
			}
		}
		
		
	public:
		void AddContact(Contact& current) {
			if (current.number[0] != '+') current.number = '+' + current.number;
			CheckIfUniqueNumber(current);
			CheckIfUniqueName(current);
			MakeId(current);
			exist[current.id] = current;
		}
		void NumberFind(const string& number) {
			int result = -1;
			for(const auto& i: exist){
				if (i.second.number == number){
					result = i.first;
				}
			}
			if (result == -1){
				cout << "Such number doesn't exist\n";
			}
			else{
				cout << exist[result] << '\n';
			}
			
		}
		int NameFind(const string& name) {
				int result = -1;
			for(const auto& i: exist){
				if (i.second.name == name){
					result = i.first;
				}
			}
			if (result == -1){
				cout << "Such name doesn't exist\n";
			}
			else{
				cout << exist[result] << '\n';
			}
			
		}
		void IdFind(const int& Id) {
			if (!exist.count(Id)){
				cout << "Such Id doesn't Id\n";
			}
			else{
				cout << exist[Id] << '\n';
			}
		}
		void Erase(const int& Id){
			exist.erase(Id);
		}
		
		void FindByAdress(const string& a) const{
			for(auto i:exist){
				auto p = i.second.adress.find(a);
				if (p < i.second.adress.size()){
					cout << i.second << '\n';
				}
			}
		}
	
};
int main(){
	
	PhoneBook a;
	
  	while (true){
  		string Operation;
  		cin >> Operation;
  		
  		if (Operation == "EraseId"){
  			int Id;
  			cin >> Id;
  			a.Erase(Id);
		}
		
		if (Operation == "AddContact"){
			Contact current;
			cin >> current;
			a.AddContact(current);
		}
		
		if (Operation == "FindByNumber"){
			string number;
			cin >> number;
			if (number[0] != '+') number = '+' + number; 
			a.NumberFind(number);
		}
		
		if (Operation == "FindByName"){
			string name;
			cin >> name;
			a.NameFind(name);
		}
		
		if (Operation == "FindById"){
			int Id;
			cin >> Id;
			a.IdFind(Id);
		}
		
		if (Operation == "FindByAdress"){
			string s;
			cin >> s;
			a.FindByAdress(s);
		}
		
		if (Operation == "End"){
  			return 0;
		}
		
	  }
}
