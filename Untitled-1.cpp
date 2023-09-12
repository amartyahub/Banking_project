#include <bits/stdc++.h>
using namespace std;

class BankAccount{
    protected:
    string IFSC;
    int AccountNo;
    double InterestRate;
    int min_bal;
    int bal;

    string name;
    string password;
    string DOB;
    string pan;   
    
    public:
    BankAccount(){
        IFSC = "SCBN09173";
        InterestRate = 4.5;
    } 
    void setDetails(int tmp, string password){
        cout<<"enter your full name:"<<endl;
        while(true){
        cin.ignore();
        getline(cin, name);
        bool valid = true;
        for(int i = 0; i < name.size(); i++)
            if((name[i] < 'a' || name[i] > 'z') && name[i]!=' ') valid = false;
        
        if(valid) break;
        else cout<<"name cannot contain special characters or numbers, enter again:"<<endl;
        }
        cout<<"enter your date of birth(dd-mm-yyyy):"<<endl;
        while(true){
            cin>>DOB;
            int date = (DOB[0]-'0')*10 + (DOB[1]-'0');
            int month = (DOB[3]-'0')*10 + (DOB[4]-'0');
            int year = (DOB[6]-'0')*1000 + (DOB[7]-'0')*100 + (DOB[8]-'0')*10 + (DOB[9]-'0');
            if(date >= 0 && date <= 31 && month >= 0 && month <= 12 && year >= 0 && year <= 2023) break;
            else cout<<"invalid date"<<endl;
        }    
        cout<<"enter your PAN number:"<<endl;
        while(true){
            cin>>pan;
            bool uppercase = false;
            bool nums = false;
            bool sp_chars = false;
            for(int i = 0; i < pan.size(); i++) 
            {
            if(pan[i] >= 'A' && pan[i] <= 'Z') uppercase = true;
            else if((pan[i] >= '1' && pan[i] <= '9')) nums = true;
            else sp_chars = true;
            }
            if(uppercase && nums && !sp_chars) break;
            else cout<<"enter valid pan number(upper case letters and numbers)"<<endl;

        }
        AccountNo = tmp;
        cout<<"account created, acc no = "<<AccountNo<<endl;
    }
    
    void deposit(int amt){
        bal+=amt;
        cout<<"deposited to "<<AccountNo<<endl;
    }
    bool withdraw(int amt){
        cout<<bal<<endl;

        if(bal - amt >= min_bal) {
            bal-=amt;
            cout<<"withdrawn from "<<AccountNo<<endl;

            return true;
        }
        else {
            cout<<"insufficient balance"<<endl;
            return false;
        }
    }
    void displayDetails(){
        cout<<"account no:"<<AccountNo<<endl;
        cout<<"name:"<<name<<endl;
        cout<<"date of birth:"<<DOB<<endl;
        cout<<"bank IFSC code"<<IFSC<<endl;
        cout<<"current balance"<<bal<<endl;

    }
    
    
};
class SavingsAccount: public BankAccount{
    public:
    SavingsAccount(){

        min_bal = 1500;
        bal = min_bal;

        InterestRate = 4.5;

    }
    
};
class CurrentAccount: public BankAccount{
    public:
    CurrentAccount(){
        min_bal = 0;
        bal = min_bal;

        InterestRate = 0;
    }
    
};
unordered_map<int, SavingsAccount> s;
unordered_map<int, CurrentAccount> c;
unordered_map<int, string> pass;

int main(){
    bool NotExit = true;

    while(NotExit){
        cout<<"enter 1 to create an account"<<endl;
        cout<<"enter 2 to login"<<endl;
        cout<<"enter 3 exit"<<endl;
        int choice;
        while(true){ 
            cout<<"enter choice"<<endl;
            cin>>choice;
            if(choice == 1 || choice == 2 || choice == 3) break;
            else cout<<"invalid choice"<<endl;
        }
        if(choice == 1){
            string ps;
            cout<<"enter your new password"<<endl;
            while(true){
                cin>>ps;
                bool haveSpChar = false;
                bool haveNum = false;
                bool haveChar = false;
                for(int i = 0; i < ps.size(); i++){
                    if(ps[i] >= 'a' && ps[i] <= 'z') haveChar = true;
                    else if(ps[i] >= '0' && ps[i] <= '9') haveNum = true;
                    else haveSpChar = true;
                }
                if(haveChar && haveNum && haveSpChar) break;
                else cout<<"password must contain a number, a character and a special character"<<endl;

            }
            
            int tmp = rand()%(1000000000) + 1000000000;
            while((s.find(tmp) != s.end()) || (c.find(tmp) != c.end()) ) tmp = rand()%(1000000000) + 1000000000;
            pass[tmp] = ps;
            
            cout<<"savings account/current account?(s/c)"<<endl;
            
            char ac_type;
            while(true){
                cin>>ac_type;
                if(ac_type == 's'){
                    SavingsAccount acc1;
                    acc1.setDetails(tmp, ps);
                    s[tmp] = acc1;
                    break;
                }
                else if(ac_type == 'c'){
                    CurrentAccount acc1;
                    acc1.setDetails(tmp, ps);
                    c[tmp] = acc1;
                    break;
                }
                else cout<<"invalid choice, enter again"<<endl;
            }
        }
        else if(choice == 2){
            int acno;
            string ps;
            cout<<"enter account number"<<endl;
            while(true){
                cin>>acno;
                if(s.find(acno) == s.end() && c.find(acno) == c.end()){ 
                    cout<<"account not found, enter correct account number"<<endl;
                    continue;
                }
                else break;
            }
            cout<<"enter password"<<endl;

            while(true){
                cin>>ps;
                if(ps == pass[acno]) break;
                else cout<<"wrong password"<<endl;
            }

            cout<<"enter 1 to withdraw"<<endl;
            cout<<"enter 2 to deposit"<<endl;
            cout<<"enter 3 to make a bank transfer"<<endl;
            cout<<"enter 4 to view account details"<<endl;
            cout<<"enter 5 to exit"<<endl;

            int choice1;
            cin>>choice1;

            if(choice1 == 1){
                int amt;
                cout<<"enter amount"<<endl;
                cin>>amt;
                if(s.find(acno)!= s.end()){
                    s[acno].withdraw(amt);
                }
                else if(c.find(acno)!= c.end()){
                    c[acno].withdraw(amt);
                } 
            }
            else if(choice1 == 2){
                int amt;
                cout<<"enter amount"<<endl;
                cin>>amt;
                if(s.find(acno)!= s.end()){
                   s[acno].deposit(amt);
                }
                else if(c.find(acno)!= c.end()){
                    c[acno].deposit(amt);
                } 
            }
            else if(choice1 == 3){
                int racno;
                cout<<"enter reciver's account no "<<endl;
                cin>>racno;

                int amt;
                cout<<"enter amount "<<endl;
                cin>>amt;

                bool withdrawn = false;
                if(s.find(acno)!= s.end()){
                    withdrawn = s[acno].withdraw(amt);
                }
                else if(c.find(acno)!= c.end()){
                    withdrawn = c[acno].withdraw(amt);
                } 

                if(withdrawn && s.find(racno)!= s.end()){
                    s[racno].deposit(amt);
                }
                else if(withdrawn && c.find(racno)!= c.end()){
                    c[racno].deposit(amt);
                }    
            }
            else if(choice1 == 4){
                if(s.find(acno)!= s.end()){
                   s[acno].displayDetails();
                }
                else if(c.find(acno)!= c.end()){
                    c[acno].displayDetails();
                }
            }
            else if(choice1 == 5){
                NotExit = false;
            }
        }
        else if(choice == 3){
            NotExit = false;
        }
    }
    return 0;
}