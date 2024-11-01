#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
using namespace std;

//function for our welcome screen
void welcome(){
    cout<<endl<<"-----------------------------------------"<<endl;
    cout<<"|| Welcome to Budget Management System ||"<<endl;
    cout<<"||  A software to manage your budget   ||"<<endl;
    cout<<"-----------------------------------------"<<endl;
    cout<<endl<<"Developed By -"<<endl<<"-> Ritik Agarwal"<<endl<<"-> Bharat Kumar"<<endl<<endl;
    system("pause");
}

//code to check if user is registered or not
bool isregistered(string username, string password){
    string un, pw;
    ifstream myfile(username+".txt");
    getline(myfile,un);
    getline(myfile,pw);
    if(un==username && pw==password){
        return true;
    }
    else{
        return false;
    }
}

//code for class of control panel
//code for defining choices at different level in program
class controlpanel{
    public:
    //choices for first step
    int choiceatstartup(){
        int ch;
        cout<<endl<<"Enter a choice"<<endl;
        cout<<"1. New User"<<endl<<"2. Existing user"<<endl;
        cin>>ch;
        return ch;
    }
    //code for entering choice second time
    int choiceforlogin(){
        int ch;
        cout<<"Enter a choice"<<endl;
        cout<<"1. Login"<<endl<<"2. Exit"<<endl<<endl;
        cin>>ch;
        return ch;
    }
    //code for choices after successfully logged in
    int choiceafterlogin(){
        int ch;
        cout<<"Enter a choice: "<<endl<<"1. Add expense"<<endl<<"2. Add income"<<endl<<"3. Update budget"<<endl<<"4. Show summary"<<endl<<"5. Show report"<<endl<<"6. Logout"<<endl<<endl;
        cin>>ch;
        return ch;
    }
};

//code for derived class registration
//code for defining registration choices
class registration : public controlpanel{
    public:
    string username, password, firstname, lastname;
    int c1,c2;
    int reg(){
        //lable for incorrect username password
        lable1:
        c1 = choiceatstartup();
        //code for registering an user
        if(c1==1){

            //code to input data
            cout<<endl<<"Enter firstname: ";
            cin>>firstname;
            cout<<"Enter lastname: ";
            cin>>lastname;
            cout<<"Enter mail id: ";
            cin>>username;
            cout<<"Enter password: ";
            cin>>password;

            //code to enter data into file
            ofstream writefile(username+".txt");
            writefile<<username<<endl<<password<<endl<<"Name: "<<firstname<<" "<<lastname<<endl;
            cout<<endl<<"User created Successfully"<<endl<<"Your username is your mail id"<<endl<<endl;
            writefile.close();
            system("pause");
            goto lable2;
        }
        else if(c1==2){
            //lable for login page
            lable2:
            c2 = choiceforlogin();
            //code for logging into system
            if(c2 == 1){
                //code for input username password
                cout<<endl<<"Enter username: ";
                cin>>username;
                cout<<"Enter password: ";
                cin>>password;
                //code to check input data matched or not
                if(isregistered(username, password)){
                    cout<<"Logged in successfully."<<endl<<endl;
                }
                else{
                    cout<<"Invalid username or password."<<endl;
                    goto lable1;
                }
            //code to exit the program
            }else if(c2 == 2){
                cout<<"Thank you!!"<<endl<<"Have a great day."<<endl<<"Press any key to exit...";
                getch();
                system("exit");
            }
        }
        return 0;
    }
};

//code for derived class home
//code for defining options in home tab
class home : public registration{
    public:
    //code for functions in home tab
    int options(){
        //lable for asking options again
        lable3:
        if(c2 == 2){
            system("exit");
        }
        else{
            int c3;
            c3 = choiceafterlogin();

            //code for total income file
            string temp2;
            string d = "totalincome";
            d = username + d;
            long totalincomeamount = 0;
            ifstream income(d+".txt");
            if(income){
                getline(income,temp2);
                totalincomeamount = stol(temp2);
            }
            income.close();

            //code for extracting recent budget amount from file
            string a = "budget";
            string temp3;
            string e = username + a;
            long recentbudgetamount = 0;
            ifstream budget(e+".txt");
            if(budget){
                getline(budget,temp3);
                recentbudgetamount = stol(temp3);
            }
            budget.close();

            //code for total expense file
            string c = "totalexpense";
            string temp1;
            long totalexpenseamount = 0;
            c = username + c;
            ifstream expense(c+".txt");
            if(expense){
                getline(expense,temp1);
                totalexpenseamount = stol(temp1);
            }
            expense.close();

            //variable declaration
            string date,temp,mode,category; 
            long expenseamount,incomeamount,budgetamount,budgetleft,incomeleft;
            //file name for income data input
            string w = "income";
            string b = username + w;
            //file name for expense data input
            string y = "expense";
            string z = username + y;
            ofstream myfile1;               //variable for income file
            ofstream budget2;               //variable for budget file
            ofstream myfile2;               //variable for expense file
            ofstream expense2;              //variable for total income file
            ofstream income2;               //variable for total income file

            //code for adding income
            switch(c3){
                //expense
                case 1:
                //code to take input from user of expense
                cout<<"Enter date: (DD-MM-YYYY) ";
                cin>>date;
                cout<<"Enter category of expense: ";
                cin>>category;
                cout<<"Enter mode of payment: (bank/cash) ";
                cin>>mode;
                cout<<"Enter amount spent: ";
                cin>>expenseamount;

                //code to enter data of expense into file
                myfile2.open(z+".txt",ios::app);
                myfile2<<"***************************"<<endl<<"Date: "<<date<<endl<<"Category: "<<category<<endl<<"Mode of payment: "<<mode<<endl<<"Amount: "<<expenseamount<<endl;
                myfile2.close();

                //code for updating total expense amount to variable
                totalexpenseamount = totalexpenseamount + expenseamount;

                //code for updating total expense amount to file 
                expense2.open(c+".txt",ios::trunc);
                expense2<<totalexpenseamount;
                expense2.close();
                cout<<endl;
                system("pause");
                goto lable3;

                //income
                case 2:
                //code to take input from user of income
                cout<<"Enter date: (DD-MM-YYYY) ";
                cin>>date;
                cout<<"Enter mode of payment: (bank/cash) ";
                cin>>mode;
                cout<<"Enter amount: ";
                cin>>incomeamount;

                //code to enter income data to file
                myfile1.open(b+".txt",ios::app);
                myfile1<<"**********************"<<endl<<"Date: "<<date<<endl<<"Mode of payment: "<<mode<<endl<<"Amount: "<<incomeamount<<endl;
                myfile1.close();

                //code for updating total income amount in variable
                totalincomeamount = totalincomeamount + incomeamount;

                //code for updating total income amount to file
                income2.open(d+".txt",ios::trunc);
                income2<<totalincomeamount;
                income2.close();
                cout<<endl;
                system("pause");
                goto lable3;

                //budget
                case 3:
                //code to take input from user of budget
                cout<<"Enter budget amount: ";
                cin>>budgetamount;

                //code for updating budget amount to variable;
                recentbudgetamount = recentbudgetamount+budgetamount;

                //code to update budget amount to file
                budget2.open(e+".txt",ios::trunc);
                budget2<<recentbudgetamount;
                budget2.close();
                cout<<endl;
                system("pause");
                goto lable3;

                //summary
                case 4:
                cout<<"********SUMMARY********"<<endl;
                cout<<"Total expense amount: "<<totalexpenseamount<<endl;
                cout<<"Total income amount: "<<totalincomeamount<<endl;
                cout<<"Budget: "<<recentbudgetamount<<endl;
                cout<<endl;
                system("pause");
                goto lable3;

                //report
                case 5:
                cout<<"*************BUDGET REPORT*************"<<endl;
                incomeleft = totalincomeamount - totalexpenseamount;
                cout<<"Total income left: "<<incomeleft<<endl;
                budgetleft = recentbudgetamount-totalexpenseamount;
                cout<<"Total budget left: "<<budgetleft<<endl;
                if(recentbudgetamount>totalexpenseamount){
                    cout<<"You are on track. Your budget is more than your expense."<<endl;
                }
                else if(recentbudgetamount<totalexpenseamount){
                    cout<<"You are off track. Your expenses had crossed your set budget."<<endl;
                }
                else{
                    cout<<"Your expense had reach the budget amount you set."<<endl;
                }
                cout<<endl;
                system("pause");
                goto lable3;

                //logout
                case 6:
                // goto logout;
                cout<<"Logged out successfully."<<endl<<"THANK YOU!!!"<<endl<<"Have a great day."<<endl<<"Press any key to exit...";
                getch();
                system("exit");
                break;

                default:
                cout<<"Enter correct choice."<<endl;
                goto lable3;
            }
        }
        return 0;
    }
};
int main(){
    welcome();
    home h1;            //declaration of object to derived class home
    h1.reg();           //calling reg function of base class registration using derived class object
    h1.options();       //calling home class method 
    return 0;
}