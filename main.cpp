/*
* lloyd Trinder
* trinderl@student.vvc.edu
* Professor Tonning
* Bank statement chapter 6 Homework
*/

#include <iostream>
#include <string>
#include <vector>

const int MAX_DAY = 30;

class Transaction
{
public:
   Transaction();
   void read();
   void print() const; 
   int get_day();
   double get_amount();

private:
   int day;
   double amount;
   std::string description;
};

Transaction::Transaction()
{
  day = 0;
  amount = 0;
}

void Transaction::read()
{
  std::cout << "Please enter the day of the transaction: " << std::endl;
  std::cin >> day;
  std::cout << "Please enter the amount of the transaction: " << std::endl;
  std::cin >> amount;
  std::cin.ignore();
  std::cout << "Please enter the description of the transaction: " << std::endl;
  std::getline(std::cin,description);
}

void Transaction::print() const
{
    std::cout << "day:" << day << std::endl;
    std::cout << "amount:" << amount << std::endl;
    std::cout << "description:" << description << std::endl;
}

void print_transactions(std::vector<Transaction> t)// a for loop that stores in a vector
{
    for(int i=0;i<t.size();i++)
        t[i].print();
}

int Transaction::get_day()
{
  return day;
}

double Transaction::get_amount()
{
  return amount;
}

class Statement
{
  public:
  Statement();
  
  void statement_print(); 
  void get_interest_rate(int days);
  double get_balance(double a);
  double aver_daily(double average, int days);
  double min_daily(double a);
  void set_last_day(int a);
  double get_aver();
  
   
  private:
  double total_balance;
  double interest_rate;
  double total_interest;
  double the_average;
  int last_day;
};

Statement::Statement()
{
   total_balance = 0.0;
   interest_rate = 1.005;
   last_day = 0;
}   

void Statement::statement_print() // Prints the calculations
{
  std::cout << "The current balance is: " << total_balance << std::endl;
  std::cout << "The interest is: " << total_interest << std::endl;
  std::cout << "The Average Daily Balance is: " << the_average << std::endl;
}

void Statement::set_last_day(int a)
{
  last_day = a;
}

void Statement::get_interest_rate(int days)// calculates the interest rate based on input
{
     std::cout << days << " " <<  last_day << std::endl;
     int i = (days / 30) * 30;
        if( i > last_day && i < days)
        total_balance *= interest_rate;
 
     total_interest = total_balance * (interest_rate - 1);
}

double Statement::get_balance(double a)// Adds the input to the total balance
{
   total_balance = total_balance + a;
}

double Statement::aver_daily(double average, int days)//calculates the average daily amount in account
{
   double total_average = 0.0;  
   
   int i = (days / 30) * 30;
  
   if( i > last_day && i < days)
     total_average += average;
  
   the_average = total_average / 30.0; 
}  

double Statement::min_daily(double a = 35)// checks whether the user has enough in their account and penalizes if they dont
{
  if(total_balance < 500)
   {
     total_balance - a;
     std::cout << "You have been charged a $35 overdraft fee for having less than the required amount in your account" << std::endl;
   }
}

double Statement::get_aver()
{
  return the_average;
}

int main()
{
  Statement s;
   
   std::vector<Transaction> transaction;
   bool more = true;
   while(more)
   {
      Transaction t;
      
      double temp_addtobal = 0.0;
      int day;
      
      t.read();
      
      temp_addtobal = t.get_amount();
      s.get_balance(temp_addtobal);
      
      day = t.get_day();
      
      s.get_interest_rate(day);
      
      s.min_daily();
      s.aver_daily(temp_addtobal, day);
      s.set_last_day(t.get_day());
      transaction.push_back(t);
      s.statement_print();
      std::cout << "Enter another Transaction? y or n" << std::endl;
      char response;
      std::cin >> response;      
      if(response != 'y' && response != 'Y')
         more = false;  
    }

  s.statement_print();
  print_transactions(transaction);
    

 return 0;
}
