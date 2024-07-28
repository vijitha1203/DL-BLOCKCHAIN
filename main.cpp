//VIJITHA YARAVA(orp20)

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

//Intialize a structure
struct Ledger
{
  int customer_id;
  float customer_balance;
  float customer_credit;
  int customer_poetWaitTime;
};

//Initialize the array of structs;
const int array_size = 4;
Ledger customers[array_size];

int main()
{
  // Initialize random number generator
  int a= rand()% (3);
  // Generate a random number for probability
  double p = (double) rand() / (double) RAND_MAX ;
  
  // Initialize the values
  for(int j=0;j<array_size;j++)
  {
    customers[j].customer_id =j;
    customers[j].customer_balance = 50.0;
    customers[j].customer_credit = 0.0;
    customers[j].customer_poetWaitTime = -1;
  }
  // Open CSV file for writing output
  ofstream fout;
  fout.open("Data.csv");
  fout<< "Tick,Customer_id,Transaction type,Balance,Credit" << endl;
    //Intial value of tic
    int tic=0;
    //Assume that there is no collision until its proven true
    bool collision=false;
    // Intialize the percent 
    int y=20;
    while(true)
    {
      tic++;
      fout<<tic<<",";
      int flag=0;
      //Iterate a loop to check the status of the system
      for(int j=0;j<array_size;j++)
      {
          if(customers[j].customer_poetWaitTime>0)
          {
            customers[j].customer_poetWaitTime--;
            flag=1;
          }
          else if(customers[j].customer_poetWaitTime == 0)
            flag=1;
      }
      // This loop works only when there is no collision 
      if(flag==0)
      {
       collision=false;
       int s = rand() %(4);
       int t = rand() %(4);
       double f = (double) rand() / (double) RAND_MAX ;
       double g = (double) rand() / (double) RAND_MAX ;
        if(f>0.1&&g>0.1)
        {
         collision=true;
         fout<<"PoET WaitTime"<<endl;
        }
        else if(g>0.1)
        {
          customers[s].customer_poetWaitTime=0;
        }
        else if(f>0.1)
        {
          customers[t].customer_poetWaitTime=0;
        }
        else
        {
          fout<<"Event has not Occured"<<endl;
        }
       if (collision)
        {
            int poetDelay = rand() %(5) ;
            customers[s].customer_poetWaitTime = poetDelay;
            poetDelay = rand() %(5);
            customers[t].customer_poetWaitTime = poetDelay;
        }
      }
    // Intialize an array for credit check
    int Checkcredit[array_size]={-1,-1,-1,-1};
    int k=0;
        while(k<array_size)
        {
            if(Checkcredit[k]>0)
            {
                Checkcredit[k]--;
            }
            else if(Checkcredit[k]==0)
            {
                //update the credit by percent
                customers[k].customer_credit+=0.2* customers[k].customer_credit;
                customers[k].customer_balance=customers[k].customer_balance-customers[k].customer_credit;
                customers[k].customer_credit=0;
                Checkcredit[k]=-1;
            }
            k++;
        }
    int i=0;
    while(i<array_size)
    {
      if(customers[i].customer_poetWaitTime==0)
      {
        flag=0;
        // Generate a random number for the transaction type
        int b=rand()%(5);
        // Generate a random number for the amount
        int c=rand()%(50);
        // Generate a random number for customer to use in case of buy/sell
        int j=rand()%(3);
        switch (b)
        {
        case 0: // Deposit
          customers[i].customer_balance = customers[i].customer_balance + c;
           fout << char(customers[i].customer_id+65)<< "," <<"DEPOSIT"<<","<< customers[i].customer_balance << ","
           << customers[i].customer_credit << endl;
          break;
        case 1: // Withdraw
          if(customers[i].customer_balance>=c)
          {
            customers[i].customer_balance = customers[i].customer_balance - c;
            fout << char(customers[i].customer_id+65) << "," <<"WITHDRAW"<<","<< customers[i].customer_balance << ","
            << customers[i].customer_credit << endl;
          }
          else // if the balance is less than the amount
          {
             fout << char(customers[i].customer_id+65) << "," <<"WITHDRAW-NOT ENOUGH BALANCE"<<","<< customers[i].customer_balance << ","
            << customers[i].customer_credit << endl;
          }
          break;
        case 2: // Buy
          if(customers[i].customer_balance>customers[i].customer_credit && c<=customers[i].customer_balance)
          {
            customers[j].customer_balance =customers[j].customer_balance + c;
            customers[i].customer_balance =customers[i].customer_balance - c;
            fout << char(customers[i].customer_id+65) << ",BUY FROM "<<char(customers[j].customer_id+65)<<","<< customers[i].customer_balance<< ","<< customers[i].customer_credit << endl;
          }
          else
          {
             fout <<  char(customers[i].customer_id+65) << "," <<"BUY-NOT ENOUGH BALANCE"<<","<< customers[i].customer_balance << ","
            << customers[i].customer_credit << endl;
          }
          break;
        case 3: //Sell
          if(c<=customers[j].customer_balance)
          {
            customers[i].customer_balance =customers[i].customer_balance + c;
            customers[j].customer_balance =customers[j].customer_balance - c;
            fout << char(customers[i].customer_id+65) << ",SELL TO "<<char(customers[j].customer_id+65)<<","<< customers[i].customer_balance<< ","<< customers[i].customer_credit << endl;
          }
          else
          {
             fout << char(customers[i].customer_id+65) << "," <<"SELL-NOT POSSIBLE"<<","<< customers[i].customer_balance << ","
            << customers[i].customer_credit << endl;
          }
          break;
        case 4: // Request credit
          if(customers[i].customer_balance>0 && customers[i].customer_credit==0)
          {
            customers[i].customer_credit+=0.2* customers[i].customer_balance;
            Checkcredit[i]=y;
            fout << char(customers[i].customer_id+65) << "," <<"REQUEST CREDIT"<<","<< customers[i].customer_balance << ","
            << customers[i].customer_credit << endl;
          }
          else  
          {
            fout << char(customers[i].customer_id+65) << "," <<"REQUEST CREDIT - CANNOT BE DONE"<<","<< customers[i].customer_balance << ","
            << customers[i].customer_credit << endl;
          }
          break;
        default: // Null transaction
          break;
        }
        customers[i].customer_poetWaitTime--;
        break;
      } 
      i++;
    }
    if(flag==1)
       fout<<"PoET waitTime"<<endl;
    if(tic>=1000)
       break;
  }
  // Close file
  fout.close();
  return 0;
}
