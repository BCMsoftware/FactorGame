//Copyrights(C) BCMsoftware. All rights reserved.
//Written by XiaoDan on 2025/5/30 - 2025/5/31
//-std-C++14 -O2

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <direct.h>
using namespace std;

typedef long long ll;

void file_print(string path){
	ifstream infile;
	infile.open(path, ios::in);
	
	string out;
	while(getline(infile, out)) cout<<out<<endl; 
	
	infile.close();
	
	return;
} 

void file_create(string path){
	ofstream createfile;
	createfile.open(path, ios::out);
	
	return;
}

void file_write(string path,string write){
	fstream writefile(path, ios::out | ios::app);
	
	writefile<<write;
	
	writefile.close();
	
	return;
}

void folder_create(string path){
	mkdir(path.c_str());
	
	return;
}

bool check_file(string path){
	ifstream infile;
	infile.open(path, ios::in);
	
	return infile;
}

vector<ll> get_factor(ll num){
	vector<ll> factor1,factor2;
	
	for(ll i = 2; i * i <= num; ++i){
		if(num % i != 0) continue;
		
		factor1.push_back(i);
		
		if(i * i != num) factor2.insert(factor2.begin(), num/i);
	}
	
	factor1.insert(factor1.end(), factor2.begin(), factor2.end());
	
	return factor1;
}

ll get_array_p(vector<ll> array, ll num){
	ll l = 0, r = array.size()-1;
	
	while(l <= r){
		ll mid = (l + r) >> 1;
		if(array[mid] > num){
			r = mid - 1;
		}else if(array[mid] < num){
			l = mid + 1;
		}else return mid;
	}

	return -1;
} 

string path_lang = ".\\language\\";
string path_save = ".\\save\\";
string file_type = ".log";

string msg_en_rule = "Game Rules:\nInput a number *n*. The computer decides who starts first. Players take turns to act:\nThe acting player selects a factor *d* of this number, where 1 < d < n. If no such *d* can be found, the player loses. Otherwise, update *n* to (n - d).\n";

string msg_ename = "Entry this game's name: ";
string msg_save = "This game's log will be saved to ";
string msg_pt = "This FactorGame played on ";
string msg_el = "Entry a language: ";
string msg_fle = "Error:Unable to find this language file.\n";

string msg_welcome = "Welcone to FactorGame!\n";
string msg_cp = "Copyrights(C) BCMsoftware. All rights reserved.";

void init(){
	cout<<msg_welcome<<msg_cp<<"\n\n";
	
	string input;

	cout<<msg_ename;
	cin>>input;
	
	folder_create(path_save);
	path_save += input + file_type;
	
	cout<<msg_save + path_save + "\n\n";
	
	file_create(path_save);
	
	time_t now = time(0);
	string nowtime = ctime(&now);
	file_write(path_save,msg_pt + nowtime + "\n");
	
	while(true){
		cout<<msg_el;
		cin>>input;
		
		if(input == "en"){
			cout<<"\n";
			cout<<msg_en_rule;
			
			break;
		}
		
		if(check_file(path_lang + input + file_type)){
			path_lang += input + file_type; 
			
			cout<<"\n";
			file_print(path_lang);
			
			break;
		}else{
			cout<<msg_fle;
		}
	}
	
	return;
}

void clear(){
	system("cls");
	return;
}

void key_wait(){
	system("pause>nul");
	return;
}

void change_print(ll num, ll get, string msg){
	string out=msg + ": " + to_string(num) + " - " + to_string(get) + " => " + to_string(num-get) + "\n";	
	
	file_write(path_save, out);
	cout<<out;
	
	return;
}

string msg_now_num = "Current Numbers: ";
string msg_can_sub = "Now you can sub these factors: ";
string msg_entry_d = "Entry the d: ";
string msg_errord = "Error d!";
string msg_human = "Human", msg_computer = "Computer";

void win_do(ll num){
	while(true){
		vector<ll> factor = get_factor(num);
		
		if(factor.empty()) break;
		
		//human
		cout<<msg_now_num<<num<<"\n\n"<<msg_can_sub<<"\n";
		
		for(ll i : factor) cout<<i<<", ";
		
		cout<<"\n";
		
		ll get;
		
		while(true){
			cout<<msg_entry_d;
			cin>>get;
			
			if(get_array_p(factor, get) != -1) break;
			cout<<msg_errord<<"\n";
		}
		
		clear();
		
		change_print(num, get, msg_human);
		
		num-=get;
		
		//compter
		cout<<msg_now_num<<num<<"\n\n";
		
		factor = get_factor(num);
		
		for(get = 3;; get += 2){
			if(get_array_p(factor, get) != -1) break;
		}
		
		change_print(num, get, msg_computer);
		
		num-=get;
	}
	
	return;
}

void win_do2(ll num){
	vector<ll> factor = get_factor(num);
	ll get;

	for(get = 3;; get += 2){
		if(get_array_p(factor, get) != -1) break;
	}
	
	change_print(num, get, msg_computer);
	num-=get;
			
	win_do(num);
	
	return;
}

void p2_do(ll num){
	while(true){
		vector<ll> factor = get_factor(num);
		if(num==2) break;
		
		//human
		cout<<msg_now_num<<num<<"\n\n"<<msg_can_sub<<"\n";
		
		for(ll i : factor) cout<<i<<", ";
		
		cout<<"\n";
		
		ll get;
		
		while(true){
			cout<<msg_entry_d;
			cin>>get;
			
			if(get_array_p(factor, get) != -1) break;
			cout<<msg_errord<<"\n";
		}
		
		clear();
		
		change_print(num, get, msg_human);
		
		num-=get;
		cout<<msg_now_num<<num<<"\n\n";
		
		if(get != num){
			win_do2(num);
			break; 
		}
		
		//computer
		change_print(num, num/2, msg_computer);
		num/=2;
	}
	
	return;
}

void cd(){
	clear();
	
	cout<<"Computer: Emmm...413, I think it's difficult for me to win to you.\n";
	key_wait();
	cout<<"Computer: Do you want to listen to something intersting?\n";
	key_wait();
	cout<<"Human: What?\n";
	key_wait();
	cout<<"Computer: Do you know who made me?\n";
	key_wait();
	cout<<"Human: Who?\n";
	key_wait();
	cout<<"Computer: His name is XiaoDan. He is a good man.\n";
	key_wait();
	cout<<"Human: I hope so. Are there anything else?\n";
	key_wait();
	cout<<"Computer: No.\n";
	key_wait();
	cout<<"Human: ...\n";
	key_wait();
	cout<<"Computer: Above all, look your log file.\n";
	key_wait();
	cout<<"Human: I think so.\n";
	
	file_write(path_save, "Thank you for you to play FactorGame! -XiaoDan YWR\n\n");
	
	return;
} 

string msg_lose = "You lose!";
string msg_entryn = "Now entry a number: ";
string msg_init_num = "Initial Number: ";

string msg_hf = "Human first";
string msg_cf = "Computer first";

string msg_games = "Game Start!";
string msg_gamee = "Human lose!";

void game(){
	cout<<"\n"<<msg_entryn;
	
	ll num;
	cin>>num;
	
	if(num==413){
		cd();
		return;
	} 
	
	clear();
	cout<<msg_games+"\n";
	
	file_write(path_save,msg_init_num + to_string(num) + "\n");
	
	if(num%2 == 1){
		cout<<"\n" + msg_hf + "\n\n";
		win_do(num);
	}else{
		ll tmp=num; ll cnt=0;
		while(tmp % 2 == 0) tmp /= 2, ++cnt; 
		
		if(tmp>1){
			cout<<"\n" + msg_cf + "\n\n";
			win_do2(num);
		}else{
			if(cnt % 2 == 1){
				cout<<"\n" + msg_hf + "\n\n";
				p2_do(num);
			}
			else{
				cout<<"\n" + msg_cf + "\n\n";
				
				change_print(num, num/2, msg_computer);
		
				num/=2;
				
				p2_do(num);
			}
		}
	}
	
	cout<<msg_lose + "\n\n";
	file_write(path_save, msg_gamee + "\n\n");
	
	return;
}

string rst_msg = "Press any key to restart";

void restart(){
	cout<<rst_msg;
	key_wait();
	clear();
}

int main(){
	init();
	
	while(true){
		game();
		restart();
	}
	
	return 0;
}
