#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

//items//

class Monster;
class Debuff;

class Item{
	private:
		string name;
		int price;
		int reqlvl;
	public:
		Item(string, int, int);
		
		virtual void print(int)=0;	//print gets a value of 0 for print without price, 1 for buying price (normal) or 2 for selling price (half)
		string getname() const;
		int getprice() const;
		int getlvl() const;
};

class Weapon: public Item{
	private:
		int damage;
		int hands;
	public:
		Weapon(string, int, int, int, int);
		
		void print(int);
		int getdamage() const;
		int gethands() const;
};

class Armor: public Item{
	private:
		int defense;
	public:
		Armor(string, int, int, int);
		
		void print(int);
		int getdefense() const;
};

class Potion: public Item{
	private:
		string stat;
		int amount;
	public:
		Potion(string, int, int, string, int);
		
		void print(int);
		string getstat() const;
		int getamount() const;
};

//spells//

class Spell{
	private:
		string name;
		int price;
		int reqlvl;
		int min;
		int max;
		int cost;
		int reduction;
	public:
		Spell(string, int, int, int, int, int, int);
		
		virtual void print(int)=0;	//print gets a value of 0 for print without price, 1 for buying price (normal) or 2 for selling price (half)
		string getname() const;
		int getprice() const;
		void cast(Monster*, int);
		int getmp() const;
		int getreduction() const;
		int getlvl() const;
};

class IceSpell: public Spell{
	private:

	public:
		IceSpell(string, int, int, int, int, int, int);
		
		void print(int);
};

class FireSpell: public Spell{
	private:

	public:
		FireSpell(string, int, int, int, int, int, int);
		
		void print(int);
};

class LightningSpell: public Spell{
	private:

	public:
		LightningSpell(string, int, int, int, int, int, int);
		
		void print(int);
};

//living beings//

class Living{
	private:
		string name;
		int level;
		int maxhp;
		int temphp;
	public:
		Living(string, int, int);
		
		string getname() const;
		void heal(int);
		void damage(int);
		int gethp() const;
		int getlvl() const;
		void revive();
		void displaystats();
		void levelup();
		void hpup(int);
};

//classes//

class Hero: public Living{
	private:
		int maxmp;
		int tempmp;
		int strength;
		int dexterity;
		int agility;
		int money;
		int experience;
		Weapon* righthand;
		Weapon* lefthand;
		Armor* armor;
		
		vector<Item*> inventory;
		vector<Spell*> spellbook;
	public:
		Hero(string, int, int, int, int, int, int, int);
		Hero(string, int, int, int, int, int, int, int, Item*, Item*);
		Hero(string, int, int, int, int, int, int, int, Spell*);
		virtual ~Hero(){}
		
		void market(Item**, int, Spell**, int);
		void buy(Item*);
		void buy(Spell*);
		void sell(int);
		void sells(int);
		void checkInventory(int);
		void checkSpells(int, int);
		void equip();
		void use();
		int getstr() const;
		int getspellsize() const;
		bool cast(Monster*, int);		//1 means mp was enough, 0 otherwise
		void damage(int);
		void healmp(int);
		void lose();
		void win(int, int);
		void displaystats();
		void levelup();
};

class Warrior: public Hero{
	public:
		Warrior(string,Item*, Item*);
};

class Sorcerer: public Hero{
	public:
		Sorcerer(string, Spell*);
};

class Paladin: public Hero{
	public:
		Paladin(string, Item*, Item*);
};

//mobs//

class Monster: public Living{
	private:
		int min;
		int max;
		int defense;
		int dodge;
		
		vector<Debuff*> debuff;
	public:
		Monster(string, int, int, int, int, int, int);
		
		bool damage(int);			//returns 1 if hit and 0 if dodged, used to check if it should apply debuffs
		int getstr() const;
		void displaystats();
		void apply(Debuff*);
		void counter();
};

class Dragon: public Monster{
	public:
		Dragon(string, int, int, int, int, int, int);
};

class Exoskeleton: public Monster{
	public:
		Exoskeleton(string, int, int, int, int, int, int);
};

class Spirit: public Monster{
	public:
		Spirit(string, int, int, int, int, int, int);
};

//other//

class Grid{
	private:
		string type;
	public:
		Grid(string);
		
		string getname(){
			return type;
		}
};

class Debuff{
	private:
		string type;
		int amount;
		int duration;
	public:
		Debuff (string, int);
		
		string gettype() const;
		int getamount() const;
		int getduration() const;
		void reduce();
};

//constructors//

Item::Item(string name,int price, int reqlvl):
name(name),price(price),reqlvl(reqlvl){
}

Weapon::Weapon(string name,int price, int reqlvl,int damage, int hands):
Item(name, price, reqlvl),damage(damage),hands(hands){
}

Armor::Armor(string name, int price, int reqlvl, int defense):
Item(name, price, reqlvl),defense(defense){
}

Potion::Potion(string name,int price, int reqlvl, string stat, int amount):
Item(name, price, reqlvl),stat(stat),amount(amount){
}

Spell::Spell(string name, int price, int reqlvl, int min, int max, int cost, int reduction):
name(name),price(price),reqlvl(reqlvl), min(min), max(max), cost(cost), reduction(reduction){
}

IceSpell::IceSpell(string name, int price, int reqlvl, int min, int max, int cost, int reduction):
Spell(name, price, reqlvl, min, max, cost, reduction){
}

FireSpell::FireSpell(string name, int price, int reqlvl, int min, int max, int cost, int reduction):
Spell(name, price, reqlvl, min, max, cost, reduction){
}

LightningSpell::LightningSpell(string name, int price, int reqlvl, int min, int max, int cost, int reduction):
Spell(name, price, reqlvl, min, max, cost, reduction){
}

Living::Living(string name, int lvl, int hp):
name(name), level(lvl), maxhp(hp), temphp(hp){
}

Hero::Hero(string name, int lvl, int hp,int mp, int str, int dex, int agl, int money):
Living(name, lvl, hp),maxmp(mp),tempmp(mp),strength(str),dexterity(dex),agility(agl),money(money),experience(0),righthand(NULL),lefthand(NULL),armor(NULL){
}

Hero::Hero(string name, int lvl, int hp,int mp, int str, int dex, int agl, int money,  Item* weapon, Item* armor):
Living(name, lvl, hp),maxmp(mp),tempmp(mp),strength(str),dexterity(dex),agility(agl),money(money),experience(0),righthand((Weapon*)weapon),lefthand(NULL),armor((Armor*)armor){
}

Hero::Hero(string name, int lvl, int hp,int mp, int str, int dex, int agl, int money,  Spell* spell):
Living(name, lvl, hp),maxmp(mp),tempmp(mp),strength(str),dexterity(dex),agility(agl),money(money),experience(0),righthand(NULL),lefthand(NULL),armor(NULL){
		spellbook.push_back(spell);
}

Warrior::Warrior(string name, Item* weapon, Item* armor):
Hero(name, 1, 11 + rand()%7,5+rand()%7,5+rand()%7,5+rand()%4,5+rand()%7,1000,weapon,armor){
}

Sorcerer::Sorcerer(string name, Spell* spell):
Hero(name, 1, 11 + rand()%7,5+rand()%7,5+rand()%4,5+rand()%7,5+rand()%7,1000,spell){
}

Paladin::Paladin(string name, Item* weapon, Item* armor):
Hero(name, 1, 11 + rand()%7,5+rand()%7,5+rand()%7,5+rand()%7,5+rand()%4,1000,weapon,armor){
}

Monster::Monster(string name, int lvl, int hp, int min, int max, int def, int dodge):
Living(name, lvl, hp),min(min), max(max), defense(def), dodge(dodge){
}

Dragon::Dragon(string name, int lvl, int hp, int min, int max, int def, int dodge):
Monster(name, lvl, hp, min, max, def, dodge){
}

Exoskeleton::Exoskeleton(string name, int lvl, int hp, int min, int max, int def, int dodge):
Monster(name, lvl, hp, min, max, def, dodge){
}

Spirit::Spirit(string name, int lvl, int hp, int min, int max, int def, int dodge):
Monster(name, lvl, hp, min, max, def, dodge){
}

Grid::Grid(string type):
type(type){
}

Debuff::Debuff(string type, int amount):
type(type),amount(amount),duration(5){
}

//accessors//

string Living::getname() const{
	return name;
}

string Item::getname() const{
	return name;
}

int Item::getprice() const{
	return price;
}

int Item::getlvl() const{
	return reqlvl;
}

string Spell::getname() const{
	return name;
}

int Spell::getprice() const{
	return price;
}

int Spell::getlvl() const{
	return reqlvl;
}

string Potion::getstat() const{
	return stat;
}

int Potion::getamount() const{
	return amount;
}

int Weapon::getdamage() const{
	return damage;
}

int Weapon::gethands() const{
	return hands;
}

int Armor::getdefense() const{
	return defense;
}

int Hero::getstr() const{
	int str = strength;
	if (righthand != NULL){
		str += righthand->getdamage();
	}
	if (lefthand != NULL){
		str += lefthand->getdamage();
	}
	return str;
}

int Monster::getstr() const{
	int str;
	if (min){
		str = min + rand()%(max-min+1);
	}else if (max){
		str = 1+rand()%(max);
	}else{
		str = 1;
	}
	return str;
}

int Hero::getspellsize() const{
	return spellbook.size();
}

int Spell::getmp() const{
	return cost;
}

int Spell::getreduction() const{
	return reduction;
}

string Debuff::gettype() const{
	return type;
}

int Debuff::getamount() const{
	return amount;
}

int Debuff::getduration() const{
	return duration;
}

int Living::gethp() const{
	return temphp;
}

int Living::getlvl() const{
	return level;
}

//print//

void Item::print(int type=0){
	if (type == 0){
		cout << name << ", required level: " << reqlvl;
	}else if (type == 1){
		cout << name << ", price: " << price << " G, required level: " << reqlvl;
	}else{
	cout << name << ", selling price: " << price/2 << " G, required level: " << reqlvl;
	}
}

void Weapon::print(int type=0){
	cout << "Weapon: ";
	Item::print(type);
	cout << ", +" << damage << " DMG, " << hands << " hands required." << endl;
}

void Armor::print(int type=0){
	cout << "Armor: ";
	Item::print(type);
	cout << ", +" << defense << " DEF." << endl;
}

void Potion::print(int type=0){
	cout << "Potion: ";
	Item::print(type);
	cout << "." << endl;
}

void Spell::print(int type=0){
	cout << name;
	if (type == 0){
		cout << ", required level: " << reqlvl;
	}else if (type == 1){
		cout << ", price: " << price << " G, required level: " << reqlvl;
	}else{
	cout << ", selling price: " << price/2 << " G, required level: " << reqlvl;
	}
	cout << ", DMG: " << min << "-" << max << ", Mana cost: " << cost;
}

void IceSpell::print(int type=0){
	cout << "Ice spell: ";
	Spell::print(type);
	cout << ", damage reduction: " << getreduction() << "." << endl;
}

void FireSpell::print(int type=0){
	cout << "Fire spell: ";
	Spell::print(type);
	cout << ", armor reduction: " << getreduction() << "." << endl;
}

void LightningSpell::print(int type=0){
	cout << "Lightning spell: ";
	Spell::print(type);
	cout << ", dodge reduction: " << getreduction() << "." << endl;
}

void Hero::checkInventory(int type=0){
	cout << getname() << "'s inventory is:" << endl;
	cout << " " << money << " Gold." << endl;
    for (int i = 0; i < inventory.size(); i++){
    	cout << " " << i << ")";
        inventory[i]->print(type);
	}
}

void Hero::checkSpells(int type=0,int offset=0){
    for (int i = 0; i < spellbook.size(); i++){
    	cout << i+offset << ")";
        spellbook[i]->print(type);
	}
}

void displayMap(Grid*** world,int maxx, int maxy, int currx, int curry){
	for (int i=0; i<maxy; i++){
		for (int j=0; j<maxx; j++){
			if (i==curry && j==currx){
				cout << "[" << "O" << "]";
			}else{
				cout << "[" << world[i][j]->getname() << "]";	
			}
		}
		cout << endl;
	}
	cout << endl;
}

//market//

void Hero::market(Item** items, int isize, Spell** spells, int ssize){
	cout << "Lamp Oil, Rope, Bombs? You want it? It's yours, my friend. As long as you have enough rupees." << endl;
	string answerc;
	int answeri;
	while(1){
		cout << "Available Gold: " << money << ". (B) to buy, (S) to sell, (X) to exit:" << endl;
		cin >> answerc;
		if (answerc == "b" || answerc == "B"){
			cout << "available items:" << endl;
			for (int i=0; i<isize; i++){
				cout << i << ") ";
				items[i]->print(1);
			}
			for (int i=isize; i<isize+ssize; i++){
				cout << i << ") ";
				spells[i-isize]->print(1);
			}
			cout << "Enter the number of the item you wish to buy:" << endl;
			cin >> answeri;
			if(cin.fail()){
				cin.clear();
				cin >> answerc;
				cout << "Invalid item!" << endl;
			}else if (answeri >= 0 && answeri < isize){
				buy(items[answeri]);
			}else if (answeri < isize+ssize){
				buy(spells[answeri-isize]);
			}else{
				cout << "Invalid item!" << endl;
			}
		}else if(answerc == "s" || answerc == "S"){
			checkInventory(2);
			checkSpells(2,inventory.size());
			cout << "Enter the number of the item you wish to sell:" << endl;
			cin >> answeri;
			if(cin.fail()){
				cin.clear();
				cin >> answerc;
				cout << "Invalid item!" << endl;
			} else if (answeri >= 0 && answeri < inventory.size()){
				sell(answeri);
			}else if (answeri < inventory.size()+spellbook.size()){
				sells(answeri-inventory.size());
			}else{	
				cout << "Invalid item!" << endl;
			}
		}else if(answerc == "x" || answerc == "X"){
			cout << "Please come again!" << endl;
			return;
		}else{
			cout << "invalid answer. please try again." << endl;
		}
	}
}

void Hero::buy(Item* item){
	if (item->getprice() <= money){
		money-= item->getprice();
		cout << item->getname() << " bought!" << endl;
		inventory.push_back(item);
	}else{
		cout << "Sorry, friend. I can't give credit! Come back when you're a little... richer!" << endl;
	}
}

void Hero::buy(Spell* spell){
	if (spell->getprice() <= money){
		money-= spell->getprice();
		cout << spell->getname() << " bought!" << endl;
		spellbook.push_back(spell);
	}else{
		cout << "Sorry, friend. I can't give credit! Come back when you're a little... richer!" << endl;
	}
}

void Hero::sell(int i){
	money+= inventory[i]->getprice()/2;
	cout << inventory[i]->getname() << " sold!" << endl;
	inventory.erase(inventory.begin()+i);
}

void Hero::sells(int i){
	money+= spellbook[i]->getprice()/2;
	cout << spellbook[i]->getname() << " sold!" << endl;
	spellbook.erase(spellbook.begin()+i);
}

//equip//

void Hero::equip(){
	checkInventory();
	cout << "Enter the number of the item you wish to equip:" << endl;
	int i;
	string answer;
	cin >> i;
	if(cin.fail()){
		cin.clear();
		cin >> answer;
		cout << "Invalid item!" << endl;
	} else if (i >= 0 && i < inventory.size()){
		if (dynamic_cast<Weapon*>(inventory[i])){
			Weapon* weapon = (Weapon*)inventory[i];
			if (weapon->getlvl() > getlvl()){
				cout << "Your level is too low for that weapon!" << endl;
				return;
			}
			if (weapon->gethands() == 1){
				cout << "Select (L) for left hand or (R) for right hand" << endl;
				cin >> answer;
				if (answer == "L" || answer == "l" || answer == "left" || answer == "Left"){
					if (lefthand != NULL){
						inventory.push_back(lefthand);
						lefthand = NULL;
					}
					if (righthand != NULL){
						if (righthand->gethands() == 2){
							inventory.push_back(righthand);
							righthand = NULL;
						}
					}
					lefthand = weapon;
					inventory.erase(inventory.begin()+i);
				}else if (answer == "R" || answer == "r" || answer == "right" || answer == "Right"){
					if (righthand != NULL){
						inventory.push_back(righthand);
						righthand = NULL;
					}
					if (lefthand != NULL){
						if (lefthand->gethands() == 2){
							inventory.push_back(lefthand);
							lefthand = NULL;
						}
					}
					righthand = weapon;
					inventory.erase(inventory.begin()+i);
				}else{
					cout << "Invalid hand!" << endl;
				}
			}else{
				if (righthand != NULL){
					inventory.push_back(righthand);
					righthand = NULL;
				}
				if (lefthand != NULL){
					inventory.push_back(lefthand);
					lefthand = NULL;
				}
				righthand = weapon;
				inventory.erase(inventory.begin()+i);
			}
			cout << "Equipping weapon..." << endl;
		}else if (dynamic_cast<Armor*>(inventory[i])){
			Armor* armornew = (Armor*)inventory[i];
			if (armornew->getlvl() > getlvl()){
				cout << "Your level is too low for that armor!" << endl;
				return;
			}
			cout << "Equipping armor..." << endl;
			if (armor != NULL){
				inventory.push_back(armor);
				armor = NULL;
			}
			armor = armornew;
			inventory.erase(inventory.begin()+i);
		}else if (dynamic_cast<Potion*>(inventory[i])){
			cout << "Sorry, cannot equip a potion!" << endl;
		}
	}else{
		cout << "Invalid item!" << endl;
	}	
}

//use//

void Hero::use(){
	checkInventory();
	cout << "Enter the number of the item you wish to use:" << endl;
	int i;
	cin >> i;
	if(cin.fail()){
		cin.clear();
		string buffer;
		cin >> buffer;
		cout << "Invalid item!" << endl;
	} else if (i >= 0 && i < inventory.size()){
		if (dynamic_cast<Potion*>(inventory[i])){
			Potion* potion = (Potion*)inventory[i];
			if (potion->getlvl() > getlvl()){
				cout << "Your level is too low for that potion!" << endl;
				return;
			}
			if (potion->getstat() == "hp"){
				heal(potion->getamount());
			}else if (potion->getstat() == "mp"){
				healmp(potion->getamount());
			}else if (potion->getstat() == "maxhp"){
				hpup(potion->getamount());
			}else if (potion->getstat() == "maxmp"){
				maxmp += potion->getamount();
				tempmp += potion->getamount();
			}else if (potion->getstat() == "str"){
				strength += potion->getamount();
			}else if (potion->getstat() == "dex"){
				dexterity += potion->getamount();
			}else if (potion->getstat() == "agl"){
				agility += potion->getamount();
			}
			inventory.erase(inventory.begin()+i);
		}else{
			cout << "Sorry, you can't use that item!" << endl;
		}
	}else{
		cout << "Invalid item!" << endl;
	}
}

void Living::hpup(int amount){
	maxhp += amount;
	temphp += amount;
}

void Living::heal(int hp){
	temphp += hp;
	if (temphp > maxhp){
		cout << name << " recovered " << hp - temphp + maxhp << " HP!" << endl;	
		temphp = maxhp;
	}else{
		cout << name << " recovered " << hp << " HP!" << endl;	
	}
}

void Hero::healmp(int mp){
	tempmp += mp;
	if (tempmp > maxmp){
		cout << getname() << " recovered " << mp - tempmp + maxmp << " MP!" << endl;	
		tempmp = maxmp;
	}else{
		cout << getname() << " recovered " << mp << " MP!" << endl;	
	}
}

//combat//

void combat(Hero** heroes, int hsize, Monster** monsters, int msize){
	string answer;
	int answeri;
	while(1){
		bool flag;
		for (int i=0; i<hsize; i++){		//hero turn
			if (heroes[i]->gethp() == 0) continue;
			while(1){
				cout << heroes[i]->getname() << "'s turn, available actions: (A) to attack, (S) to cast spells, (U) to use, (E) to equip, (D) to display stats:" << endl;
				cin >> answer;
				if (answer == "a" || answer == "A" || answer == "attack"){	
					for (int j=0; j<msize; j++){
						if (monsters[j]->gethp() > 0){
							cout << j << ") " << monsters[j]->getname() <<endl;	
						}
					}
					cout << "Enter the number of the monster you wish to attack:" << endl;
					cin >> answeri;
					if(cin.fail()){
						cin.clear();
						cin >> answer;
						cout << "Invalid monster!" << endl;
					}else if (answeri >= 0 && answeri < msize){
						if (monsters[answeri]->gethp() > 0){
							monsters[answeri]->damage(heroes[i]->getstr());
							break;
						}
						cout << "Invalid monster!" << endl;
					}else{
						cout << "Invalid monster!" << endl;
					}
					
				}else if (answer == "s" || answer == "S" || answer == "castSpell" || answer == "castspell" || answer == "Spell" || answer == "spell"){
					heroes[i]->checkSpells();
					cout << "Enter the number of the spell you wish to cast:" << endl;
					cin >> answeri;
					if(cin.fail()){
						cin.clear();
						cin >> answer;
						cout << "Invalid spell!" << endl;
					} else if (answeri >= 0 && answeri < heroes[i]->getspellsize()){
						for (int j=0; j<msize; j++){
							if (monsters[j]->gethp() > 0){
								cout << j << ") " << monsters[j]->getname() <<endl;	
							}
						}
						cout << "Enter the number of the monster you wish to attack:" << endl;
						int answer2;
						cin >> answer2;
						if(cin.fail()){
							cin.clear();
							cin >> answer;
							cout << "Invalid monster!" << endl;
						}else if (answer2 >= 0 && answer2 < msize){
							if (monsters[answer2]->gethp() > 0){
								if (heroes[i]->cast(monsters[answer2],answeri) == 1) break;
							}else{
								cout << "Invalid monster!" << endl;
							}
						}else{
							cout << "Invalid monster!" << endl;
						}
					}else{
						cout << "Invalid spell!" << endl;
					}
					
				}else if (answer == "e" || answer == "E" || answer == "equip"){
					heroes[i]->equip();
					break;
					
				}else if (answer == "u" || answer == "U" || answer == "use"){
					heroes[i]->use();
					break;
					
				}else if (answer == "d" || answer == "D" || answer == "displayStats" || answer == "displaystats"){
					for (int j=0; j<hsize; j++){
						heroes[j]->displaystats();
					}
					cout << endl;
					for (int j=0; j<msize; j++){
						monsters[j]->displaystats();
					}
					
				}else{
					cout << "invalid answer. please try again." << endl;
				}
			}
			flag = 1;
			for (int i=0; i<msize; i++){
				if (monsters[i]->gethp() > 0){
					flag = 0;
					break;
				}
			}
			if (flag == 1){
				break;		//ends if all heroes die
			}
		}
		flag = 0;
		for (int i=0; i<msize; i++){	//monster turn
			if (monsters[i]->gethp() == 0) continue;
			flag = 1;
			cout << monsters[i]->getname() << " attacks!" << endl;
			while(1){
				int r = rand()%hsize;
				if (heroes[r]->gethp() > 0){
					heroes[r]->damage(monsters[i]->getstr());
					break;
				}
			}
			for (int i=0; i<hsize; i++){
				if (heroes[i]->gethp() > 0){
					flag = 0;
					break;
				}
			}
			if (flag == 1){
				break;		//ends if all heroes die
			}
		}
		for (int i=0; i<hsize; i++){
			if (heroes[i]->gethp() > 0){
				heroes[i]->heal(heroes[i]->getlvl());
				heroes[i]->healmp(heroes[i]->getlvl());	
			}
		}
		if (flag == 1){
			cout << "You have been defeated!" <<endl;
			for (int i=0; i<hsize; i++){
				heroes[i]->lose();
			}
			break;
		}
		flag = 1;
		for (int i=0; i<msize; i++){
			if (monsters[i]->gethp() > 0){
				monsters[i]->heal(monsters[i]->getlvl());
				monsters[i]->counter();
				flag = 0;
			}
		}
		if (flag == 1){
			cout << "You are victorious" <<endl;
			int rem;
			for (int i=0; i<hsize; i++){
				rem++;
			}
			for (int i=0; i<hsize; i++){
				heroes[i]->win(msize,rem);
			}
			break;
		}
	}
	for (int i=0; i<hsize; i++){
		if (heroes[i]->gethp() > 0){
			heroes[i]->revive();
		}
	}
}

void Living::damage(int hp){
	temphp -= hp;
	if (temphp <= 0){
		cout << name << " lost " << hp+temphp << " HP!" << endl;
		cout << name << " has been defeated!" << endl;
		temphp = 0;
	}else{
		cout << name << " lost " << hp << " HP!" << endl;
	}
}

bool Monster::damage(int hp){
	if (rand()%100 >= 10000/(100+dodge)){
		cout << getname() << " dodged the attack!" << endl;
		return 0;
	}
	if (defense) hp -= defense;
	if (hp < 0) hp = 0;
	Living::damage(hp);
	return 1;
}

void Hero::damage(int hp){
	if (rand()%100 >= 10000/(100+agility)){
		cout << getname() << " dodged the attack!" << endl;
		return;
	}
	if (armor != NULL){
		hp -= armor->getdefense();
	}
	if (hp < 0) hp = 0;
	Living::damage(hp);
}

void Spell::cast(Monster* monster, int dex){
	int dmg = min + rand()%(max-min+1) + dex;
	if (monster->damage(dmg)){
		string type;
		if (dynamic_cast<IceSpell*>(this)){
			type = "damage";
		}else if (dynamic_cast<FireSpell*>(this)){
			type = "defense";
		}else{
			type = "dodge";
		}
		Debuff* d;
		d = new Debuff(type,this->getreduction());
		monster->apply(d);
	}
}

bool Hero::cast(Monster* monster, int spell){
	if (tempmp < spellbook[spell]->getmp()){
		cout << "Not enough MP to cast that!" << endl;
		return 0;
	}
	if (spellbook[spell]->getlvl() > getlvl()){
		cout << "Your level is too low to cast that!" << endl;
		return 0;
	}
	tempmp -= spellbook[spell]->getmp();
	spellbook[spell]->cast(monster, dexterity);
	return 1;
}

void Monster::apply(Debuff* d){
	if (d->gettype() == "damage"){
		cout << getname() << " is freezing and has been weakened!" << endl;
		min -= d->getamount();
		max -= d->getamount();
	}else if (d->gettype() == "defense"){
		cout << getname() << " was burned and is now vunerable!" << endl;
		defense -= d->getamount();
	}else{
		cout << getname() << " is paralyzed and can't move well!" << endl;
		dodge -= d->getamount();
	}
	debuff.push_back(d);
}

void Monster::counter(){
	for (vector<Debuff*>::iterator it = debuff.begin(); it != debuff.end();){
		(*it)->reduce();
		if ((*it)->getduration() == 0){
			if ((*it)->gettype() == "damage"){
				min += (*it)->getamount();
				max += (*it)->getamount();
			}else if ((*it)->gettype() == "defense"){
				defense += (*it)->getamount();
			}else{
				dodge += (*it)->getamount();
			}
			Debuff* p = *it;
   			it = debuff.erase(it);
   			delete p;
  		}else{
  			it++;
		}
    }
}

void Debuff::reduce(){
	duration--;
}

void Living::revive(){
	temphp = maxhp/2;
}

void Hero::lose(){
	money /= 2;
}

void Hero::win(int i, int j){
	cout << getname() << " gained " << i*100*getlvl()/(7*j) << " XP and " << getlvl()*i*50/j << " Gold!" << endl;
	money += getlvl()*i*50/j;
	experience += i*100*getlvl()/(7*j);
	while (experience >= (getlvl()+1)*(getlvl()+1)*(getlvl()+1)){
		levelup();
	}
	cout << endl;
}

void Hero::levelup(){
	Living::levelup();
	int mp = rand()%7;
	cout << "MP: " << maxmp << "->" << maxmp+mp << endl;
	maxmp+=mp;
	tempmp+=mp;
	if (dynamic_cast<Warrior*>(this)){
		int str = rand()%7;
		cout << "Strength: " << strength << "->" << strength+str << endl;
		strength+=str;
		int dex = rand()%7;
		cout << "Dexterity: " << dexterity << "->" << dexterity+dex << endl;
		dexterity+=dex;
		int agl = rand()%4;
		cout << "Agility: " << agility << "->" << agility+agl << endl;
		agility+=agl;
	}else if (dynamic_cast<Sorcerer*>(this)){
		int str = rand()%4;
		cout << "Strength: " << strength << "->" << strength+str << endl;
		strength+=str;
		int dex = rand()%7;
		cout << "Dexterity: " << dexterity << "->" << dexterity+dex << endl;
		dexterity+=dex;
		int agl = rand()%7;
		cout << "Agility: " << agility << "->" << agility+agl << endl;
		agility+=agl;
	}else{
		int str = rand()%7;
		cout << "Strength: " << strength << "->" << strength+str << endl;
		strength+=str;
		int dex = rand()%7;
		cout << "Dexterity: " << dexterity << "->" << dexterity+dex << endl;
		dexterity+=dex;
		int agl = rand()%4;
		cout << "Agility: " << agility << "->" << agility+agl << endl;
		agility+=agl;
	}
}

void Living::levelup(){
	level++;
	cout << name << " has gained a level! Level " << level << " reached!" << endl;
	int hp = 1 + rand()%7;
	cout << "HP: " << maxhp << "->" << maxhp+hp << endl;
	maxhp+=hp;
	temphp+=hp;
}


void Living::displaystats(){
	cout << getname() << "'s stats:" << endl;
	cout << " Level: " << level << endl;
	cout << " HP: " << temphp << "/" << maxhp << endl;
}

void Hero::displaystats(){
	Living::displaystats();
	cout << " MP: " << tempmp << "/" << maxmp << endl;
	cout << " Strength: " << strength << endl;
	cout << " Dexterity: " << dexterity << endl;
	cout << " Agility: " << agility << endl;
}

void Monster::displaystats(){
	Living::displaystats();
	if (min){
		cout << " Damage: " << min << "-" << max << endl;
	}else if (max){
		cout << " Damage: 1-" << max << endl;
	}else {
		cout << " Damage: 1-1" << endl;
	}
	if (defense){
		cout << " Defense: " << defense << endl;
	}else{
		cout << " Defense: 0" << endl;
	}
	if (dodge){
		cout << " Dodge: " << dodge << endl;
	}else{
		cout << " Dodge: 0" << endl;
	}
}

void encounter(Hero** heroes, int hsize){
	cout << "Enemy encounter!" << endl;
	int min = heroes[0]->getlvl(), max = heroes[0]->getlvl();
	for (int i=1; i<hsize; i++){
		if (heroes[i]->getlvl()<min) min = heroes[i]->getlvl();
		if (heroes[i]->getlvl()>max) max = heroes[i]->getlvl();
	}
	int msize = rand()%(hsize+2) + 1;	//random monster team size from 1 to hsize+2
	Monster** monsters;
	monsters = new Monster*[msize];
	for (int i=0; i<msize; i++){
		int lvl = min + rand()%(max-min+1);	//random monster level between min and max lvl in hero party
		int hp = 10 + lvl + rand()%(lvl*5+1);
		int r = rand()%3;					//randomly selects class
		if (r==0){
			int dmg = 5+rand()%(lvl*5+1);
			monsters[i] = new Dragon("Dragon", lvl, hp, dmg*0.8, dmg, 5+rand()%(lvl*3+1), 5+rand()%(lvl*3+1));
		}else if (r==1){
			int dmg = 5+rand()%(lvl*3+1);
			monsters[i] = new Exoskeleton("Bug", lvl, hp, dmg*0.8, dmg, 5+rand()%(lvl*5+1), 5+rand()%(lvl*3+1));
		}else{
			int dmg = 5+rand()%(lvl*3+1);
			monsters[i] = new Spirit("Ghost", lvl, hp, dmg*0.8, dmg, 5+rand()%(lvl*3+1), 5+rand()%(lvl*5+1));
		}
	}
	combat(heroes, hsize, monsters, msize);
	for (int i=0;i<msize;i++){
    	delete monsters[i];
	}
	delete[] monsters;
}

//main//

int main(void){
	
	//initialization process//
	
	srand(time(NULL));
	
	//pools//
	
	Item** shopitems;
	int isize = 28;
	shopitems = new Item*[isize];
	
	shopitems[0] = new Weapon("Wooden sword", 350, 1, 15, 1);
	shopitems[1] = new Weapon("Copper sword", 450, 5, 20, 1);
	shopitems[2] = new Weapon("Bronze sword", 600, 10, 25, 1);
	shopitems[3] = new Weapon("Iron sword", 700, 15, 30, 1);
	shopitems[4] = new Weapon("Platinum sword", 1400, 20, 60, 1);
	
	shopitems[5] = new Weapon("Wooden greatsword", 550, 1, 25, 2);
	shopitems[6] = new Weapon("Copper greatsword", 700, 5, 33, 2);
	shopitems[7] = new Weapon("Bronze greatsword", 900, 10, 40, 2);
	shopitems[8] = new Weapon("Iron greatsword", 1100, 15, 50, 2);
	shopitems[9] = new Weapon("Platinum greatsword", 2200, 20, 100, 2);
	
	shopitems[10] = new Armor("Leather armor", 300, 1, 10);
	shopitems[11] = new Armor("Copper armor", 450, 5, 15);
	shopitems[12] = new Armor("Bronze armor", 600, 10, 20);
	shopitems[13] = new Armor("Iron armor", 750, 15, 25);
	shopitems[14] = new Armor("Platinum armor", 900, 20, 30);
	
	shopitems[15] = new Potion("Small Potion", 300, 1, "hp", 20);
	shopitems[16] = new Potion("Good Potion", 700, 15, "hp", 50);
	shopitems[17] = new Potion("Great Potion", 1500, 35, "hp", 200);
	shopitems[18] = new Potion("Huge Potion", 2500, 50, "hp", 999);
	
	shopitems[19] = new Potion("Small Mana Potion", 1200, 1, "mp", 10);
	shopitems[20] = new Potion("Good Mana Potion", 2000, 15, "mp", 25);
	shopitems[21] = new Potion("Great Mana Potion", 3000, 35, "mp", 40);
	shopitems[22] = new Potion("Huge Mana Potion", 4500, 50, "mp", 100);
	
	shopitems[23] = new Potion("HP up", 9800, 30, "maxhp", 1);
	shopitems[24] = new Potion("Strength Potion", 9800, 30, "str", 1);
	shopitems[25] = new Potion("Magic Enzymes", 9800, 30, "dex", 1);
	shopitems[26] = new Potion("Speed Pills", 9800, 30, "agl", 1);
	shopitems[27] = new Potion("MP up", 9800, 30, "maxmp", 5);
	
	Spell** shopspells;
	int ssize = 13;
	shopspells = new Spell*[ssize];
	//name, price, level, min and max damage, mana cost, stat reduction
	//ice = -damage
	shopspells[0] = new IceSpell("Arctic Beam",100,1,50,65,5,30);
	shopspells[1] = new IceSpell("Frost Ball",3000,30,60,75,7,10);
	shopspells[2] = new IceSpell("Frost Beam",3000,30,75,95,10,10);
	shopspells[3] = new IceSpell("Blizzard",5000,51,95,120,20,10);
	//fire = -armor
	shopspells[4] = new FireSpell("Firespark",100,1,30,40,4,10);
	shopspells[5] = new FireSpell("Flame Sphere",3000,35,60,75,7,10);
	shopspells[6] = new FireSpell("Flame Breath",3500,35,75,95,7,10);
	shopspells[7] = new FireSpell("Fire Whirl",4000,39,35,45,7,50);
	shopspells[8] = new FireSpell("Hellfire",4500,44,95,120,20,30);
	//lightning =-dodge
	shopspells[9] = new LightningSpell("Electric Shock",100,1,30,40,3,10);
	shopspells[10] = new LightningSpell("Lightning Orb",3000,25,60,75,7,10);
	shopspells[11] = new LightningSpell("High Discharge",2500,25,75,95,7,10);
	shopspells[12] = new LightningSpell("Thunderbolt",4000,43,95,120,10,10);
	
	//world generation//
	
	string answer;
	
	Grid*** world;
	cout << "Select map height:" << endl;
	int maxx, maxy;
	while (1){
		cin >> maxy;
		if(cin.fail()){
			cin.clear();
			cin >> answer;
			cout << "Invalid number!" << endl;	
		}else break;
	}
	
	cout << "Select map width:" << endl;
		while (1){
		cin >> maxx;
		if(cin.fail()){
			cin.clear();
			cin >> answer;
			cout << "Invalid number!" << endl;	
		}else break;
	}
	
	int currx=rand()%maxx, curry=rand()%maxy;
	world = new Grid**[maxy];
	for (int i=0; i<maxy; i++){
		world[i] = new Grid*[maxx];
		for (int j=0; j<maxx; j++){
			int r = rand()%100;
			if (i==curry && j==currx){
				world[i][j] = new Grid(" ");
			}else if (r < 5){
				world[i][j] = new Grid("M");
			}else if (r < 35){
				world[i][j] = new Grid("X");
			}else{
				world[i][j] = new Grid(" ");
			}
		}
	}
	
	//player generation//
	Hero** heroes;
	cout << "how many heroes would you like to control?" << endl;
	int hsize;
	while (1){
		cin >> hsize;
		if(cin.fail()){
			cin.clear();
			cin >> answer;
			cout << "Invalid number!" << endl;	
		}else break;
	}
	heroes = new Hero*[hsize];
	
	//name, lvl ,hp, mp, str, dex, agl, money
	for (int i=0; i<hsize; i++){
		while (1){
			cout << "choose class for hero number " << i+1 << ", Available classes: (W) Warrior, (S) Sorcerer, (P) Paladin." << endl;
			cin >> answer;
			if (answer == "W" || answer == "w" || answer == "Warrior" || answer == "warrior"){
				cout << "choose name for hero number " << i+1 << "." << endl;
				cin >> answer;
				heroes[i] = new Warrior(answer, shopitems[0],shopitems[10]);
				break;
			}else if (answer == "S" || answer == "s" || answer == "Sorcerer" || answer == "sorcerer"){
				cout << "choose name for hero number " << i+1 << "." << endl;
				cin >> answer;
				heroes[i] = new Sorcerer(answer, shopspells[9]);
				break;
			}else if (answer == "P" || answer == "p" || answer == "Paladin" || answer == "paladin"){
				cout << "choose name for hero number " << i+1 << "." << endl;
				cin >> answer;
				heroes[i] = new Paladin(answer, shopitems[5],shopitems[10]);
				break;
			}else{
				cout << "invalid answer. please try again." << endl;
			}
		}
	}
	
	//main part//
	
	bool d = 1;			//toggles display
	while(1){
		cout << endl;
		if (d) displayMap(world, maxx, maxy, currx, curry);
		cout << "Actions: (W,A,S,D) to move, ";
		if (world[curry][currx]->getname() == "M") cout << "(P) to access market, ";
		cout << "(I) to check your inventory, (E) to equip, (U) to use, (M) to toggle display map, (X) to quit game." << endl;
		cin >> answer;
		if (answer == "x" || answer == "X" || answer == "quitGame" || answer == "quitgame" || answer == "quit"){
			break;
		}else if (answer == "w" || answer == "W"){
			if (curry > 0){
				if (world[curry-1][currx]->getname() != "X"){
					curry--;
					if (world[curry][currx]->getname() == " "){
						int r = rand()%100;
						if (r<10) encounter(heroes, hsize);
					}
				}
			}
		}else if (answer == "a" || answer == "A"){
			if (currx > 0){
				if (world[curry][currx-1]->getname() != "X"){
					currx--;
					if (world[curry][currx]->getname() == " "){
						int r = rand()%100;
						if (r<10) encounter(heroes, hsize);
					}
				}
			}
		}else if (answer == "s" || answer == "S"){
			if (curry < maxy-1){
				if (world[curry+1][currx]->getname() != "X"){
					curry++;
					if (world[curry][currx]->getname() == " "){
						int r = rand()%100;
						if (r<10) encounter(heroes, hsize);
					}
				}
			}
		}else if (answer == "d" || answer == "D"){
			if (currx < maxx-1){
				if (world[curry][currx+1]->getname() != "X"){
					currx++;
					if (world[curry][currx]->getname() == " "){
						int r = rand()%100;
						if (r<10) encounter(heroes, hsize);
					}
				}
			}

		}else if (world[curry][currx]->getname() == "M" && (answer == "p" || answer == "P" || answer == "market")){
			cout << "Enter the number of the hero you wish to shop with:" << endl;
			for (int i=0; i<hsize; i++){
				cout << i << ") " << heroes[i]->getname() <<endl;
			}
			int answeri;
			cin >> answeri;
			if(cin.fail()){
				cin.clear();
				cin >> answer;
				cout << "Invalid hero!" << endl;
			}else if (answeri >= 0 && answeri < hsize){
				heroes[answeri]->market(shopitems,isize,shopspells,ssize);
			}else{
				cout << "Invalid hero!" << endl;
			}
			
		}else if (answer == "i" || answer == "I" || answer == "checkInventory" || answer == "checkinventory" || answer == "Inventory" || answer == "inventory"){
			for (int i=0; i<hsize; i++){
				heroes[i]->checkInventory();	
			}
			
		}else if (answer == "m" || answer == "M" || answer == "displayMap" || answer == "displaymap" || answer == "Map" || answer == "map"){
			if (d) d = 0;
			else d = 1;
			
		}else if (answer == "e" || answer == "E" || answer == "equip"){
			cout << "Enter the number of the hero you wish to interact with:" << endl;
			for (int i=0; i<hsize; i++){
				cout << i << ") " << heroes[i]->getname() <<endl;
			}
			int answeri;
			cin >> answeri;
			if(cin.fail()){
				cin.clear();
				cin >> answer;
				cout << "Invalid hero!" << endl;
			}else if (answeri >= 0 && answeri < hsize){
				heroes[answeri]->equip();
			}else{
				cout << "Invalid hero!" << endl;
			}
			
		}else if (answer == "u" || answer == "U" || answer == "use"){
			cout << "Enter the number of the hero you wish to interact with:" << endl;
			for (int i=0; i<hsize; i++){
				cout << i << ") " << heroes[i]->getname() <<endl;
			}
			int answeri;
			cin >> answeri;
			if(cin.fail()){
				cin.clear();
				cin >> answer;
				cout << "Invalid hero!" << endl;
			}else if (answeri >= 0 && answeri < hsize){
				heroes[answeri]->use();
			}else{
				cout << "Invalid hero!" << endl;
			}
			
		}else{
			cout << "invalid answer. please try again." << endl;
		}
	}
	
	//termination process//

    for (int i=0;i<isize;i++){
    	delete shopitems[i];
	}
	delete[] shopitems;

    for (int i=0;i<ssize;i++){
    	delete shopspells[i];
	}
	delete[] shopspells;
	
    for (int i=0;i<hsize;i++){
    	delete heroes[i];
	}
	delete[] heroes;

	for (int i=0;i<maxy;i++){
		for (int j=0;j<maxx;j++){
			delete world[i][j];
		}
		delete world[i];
	}
	delete[] world;
	cout << "Thank you for playing my game!" << endl;

	return 0;
}
