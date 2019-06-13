#include <iostream>
#include <iomanip>
/*
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <cmath>
#include <random>
*/

#define FOR(X,Y) for (int (X) = 0;(X) < (Y);++(X))
#define FORn(X,N,Y) for (int(X) = (N);(X) < (Y);++(X))

using namespace std;

bool newbudget(short *wm,double *inc,double *min,bool exp_ver[],string exp_nm[]);
bool primary(short *wm,double *inc,double *min,double *pf,bool exp_ver[],string exp_nm[],double exp_val[],double *sav);

/*  THERE IS PRECIOUS LITTLE ERROR CORRECTION IN THIS MOCKUP
    ENTRIES MUST BE PRECISE */

int main() {
    bool RUN = true,STOP = false;
    short wk_or_mo;
    double budget_income=0,budget_min=0,savings=0;
    bool expense_verify[10];
    string expense_name[10]={""};
    double expense_value[10]={0};
    while(RUN){
        wk_or_mo = 0;
        budget_income = 0;
        budget_min = 0;
        savings = 0;
        FOR(i,10){
            expense_verify[i] = false;
            expense_name[i] = "";
            expense_value[i] = 0;
        }
        newbudget(&wk_or_mo,&budget_income,&budget_min,expense_verify,expense_name);
        double pushforward = 0;
        STOP = false;
        while(!STOP){
            STOP = primary(&wk_or_mo,&budget_income,&budget_min,&pushforward,expense_verify,expense_name,expense_value,&savings);
        }
    }
        
        
return 0;
}

bool newbudget(short *wm, double *inc, double *min, bool exp_ver[], string exp_nm[]){
    string trash;
    cout<<"WELCOME TO COIN CATCH!!!\n\n";
    cout<<"This is a simple budgeting app that helps you account for the money you spend! We’ll help you keep track of your expenses, as well as a virtual savings account. You can also let extra money be rolled over to the next period. An important thing to remember is that at the end of an income period, you will either have a positive or negative balance. If it’s positive, you can either roll that amount forward to the next budget period or tell us to get rid of it (hopefully you save it, but we’re not pushy). If you overspend your budget, we can deduct it from the virtual savings account, or we can reduce the next period’s budget. If you’re ever confused about what a term means, tap it to bring up an explanation! For people with complicated expenses, this app may not be right for you, but if you’re flying through life without caring where your money ends up, we can help you be a little more careful!\n\n";
    cout<<"Press enter to continue...";
    getline(cin,trash);
    
    cout<<"\n\n***********************\n";
    cout<<"*** CREATE A BUDGET ***\n";
    cout<<"***********************\n";
    cout<<"Press enter to continue...";
    getline(cin,trash);
    
    cout<<"\n\n*****************\n";
    cout<<"*** FREQUENCY ***\n";
    cout<<"*****************\n";
    while (*wm!=1&&*wm!=2){
        cout<<"Frequency:\n1) Weekly\n2) Monthly\n3) Tooltip\n";
        cout<<"input> ";
        cin>>*wm;
        if (*wm==3)
            cout<<"First you need to decide: is this a weekly or monthly budget model?\n\n";
    }
    cout<<"Press enter to continue...";
    getline(cin,trash);
    
    cout<<"\n\n************************\n";
    cout<<"*** RECURRING CREDIT ***\n";
    cout<<"************************\n";
    while(*inc<=0){
        cout<<"Enter an income or enter -1 for the tooltip: $";
        cin>>*inc;
        if (*inc==-1)
        cout<<"The next thing you need to decide is how much you of your income you'll use for this budget model. This is the amount of money know you need to set aside for your expenses!\n\nFor example, if you make $1500 per month, perhaps your typical income credit could be $1000. That means you’re responsible for $500, but we’ll help you account for how you spend the other $1000 on things like bills, food, movies, etc. It’s up to you how much you'll set aside, so make sure it’s enough! Also, remember that this is either a weekly or monthly amount, depending on what model you chose at the beginning!\n\n";
    }
    cout<<"Press enter to continue...";
    getline(cin,trash);
    
    cout<<"\n\n**********************\n";
    cout<<"*** BUDGET MINIMUM ***\n";
    cout<<"**********************\n";
    while (*min<=0){
        cout<<"Enter a budget minimum or -1 for the tooltip: $";
        cin>>*min;
        if (*min==-1)
        cout<<"The next thing you need to decide is a budget minimum. This is necessary because you can outspend your budget if you’ve set it too low. If you ever overspend so much that your budget minimum is reached, we’ll stop the tracking at the end of the period and have you redo your math!\n";
    }
    
    cout<<"\n\n*********************\n";
    cout<<"*** EXPENSE TYPES ***\n";
    cout<<"*********************\n";
    cout<<"tooltip: We need to know what types of expenses you have. You can create up to 9 categories, each named whatever you like (and you can change the names later!) but if you ever need to add a category or delete one, we’ll need to start from scratch, so be careful! But don’t worry. There’s a category called “miscellaneous” that we will automatically add for you so you can account for extra expenses that you didn’t realize you’d have, just in case!";
    cout<<"\n\nEnter a name for each expense, or \"exit\" if you want to stop.\n";
    string temp;
    int thing=9;
    FOR(i,9){
        cout<<"Name of Expense "<<i+1<<" : ";
        cin>>temp;
        if (temp=="exit"){
            thing = i;
            break;}
        exp_ver[i] = true;
        exp_nm[i] = temp;
    }
    exp_ver[thing] = true;
    exp_nm[thing] = "Miscellaneous";

    
    cout<<"\n\nOk, we’re ready to go! We’ve already accounted for this (week’s/month’s) first budget, so you can start spending right away. We’ll notify you at the end of the (week/month) to remind you to enter any expenses you may have forgotten. Also, you can choose to input all your expenses at that time if you’d prefer. At the end of every period, we’ll calculate how much you have left or how much you overspent. If you have money left over, sock it away in the virtual savings account or roll it over to increase the next period’s budget amount! If you overspent, don’t worry! We’ll have you deduct it either 1) from your virtual savings account, or 2) from your next period’s budget amount. Be careful with your money! If you overspend too often, we’ll have to suspend the tracking and have you start over with a new model. Happy coin catching!";
    return true;
}

bool primary(short *wm,double *inc,double *min,double *pf,bool exp_ver[],string exp_nm[],double exp_val[],double *sav){
    double budg = *inc+*pf;
    string trash;
    bool STOP = false;
    double sum=0;
    FOR(i,10) sum += exp_val[i];
    cout<<"\n\n";
    cout<<"Recurring Credit toward Budget: $"<<*inc<<"\n";
    cout<<"Budget amount for this period: $"<<budg<<"\n";
    cout<<"Total spent this period: $"<<sum<<"\n";
    cout<<"Current left to spend: $"<<budg-sum<<"\n";
    if (budg-sum<0){
        cout<<"You've exceeded your current budget.\n";
        if (-(budg-sum)>(*min)){
            cout<<"You've also reached your budget min. Tracking stopped at end of period.";
            STOP = true;}}
    cout<<"Current virtual savings: $"<<*sav<<"\n";
    cout<<"* * * * * *\n\n";
    cout<<"OPTIONS\n*******\n";
    cout<<"1) Expense breakdown by list\n";
    cout<<"2) Expense breakdown by chart\n";
    cout<<"3) SPEND!\n";
    cout<<"4) End of period (automatic in app)\n";
    cout<<"5) tooltip for \'Recurring Credit\'\n";
    cout<<"6) tooltip for \'Current left to spend\'\n";
    cout<<"7) tooltip for \'Budget minimum reached\'\n";
    cout<<"8) tooltip for \'[INFO]\' button on \'SPEND!\' screen\n";
    cout<<"input> ";
    short input;
    cin>>input;
    switch (input) {
        case 1:
        cout<<"\n*******\n";
        short count1,sum1; count1 = 0; sum1 = 0;
        while (exp_ver[count1]){
            cout<<count1+1<<". "<<exp_nm[count1]<<" -- $"<<exp_val[count1]<<"\n";
            sum1 += exp_val[count1];
            count1 += 1;}
        cout<<"Total expense amount: $"<<sum1;
        return false;
        break;
        
        case 2:
        cout<<"\n*******\n";
        cout<<"OMG SUPER COOL PIE CHART WITH COLORZ AND STUF\n";
        cout<<"\n*******\n";
        cout<<"<Press enter to continue>";
        getline(cin,trash);
        return false;
        
        case 3:
        cout<<"\n";
        short count3; count3 = 0;
        while(exp_ver[count3]){
            cout<<count3+1<<") "<<exp_nm[count3]<<"\n";
            count3++;}
        if (count3!=9) cout<<count3+1<<") "<<exp_nm[9]<<"\n";
        short input; input = 0;
        double temp; temp = 0;
        cout<<"[INFO]\n";
        cout<<"You will enter expenses by number entry, or -1 to stop.\n";
        while(1){
            cout<<"Input expense by number: ";
            cin>>input;
            if (input == -1) break;
            cout<<"Input "<<exp_nm[input-1]<<" expense amount: ";
            cin>>temp;
            exp_val[input-1] += temp;}
        cout<<"Confirmation in app would occur here\n";
        return false;
        
        case 4:
        cout<<"\n\nEND OF CURRENT PERIOD\n*********************\n";
        cout<<"Starting Budget: $"<<budg<<"\n";
        double sum; sum = 0;
        FOR(i,10) sum += exp_val[i];
        cout<<"Total Spent: $"<<sum<<"\n";
        double diff; diff = budg-sum;
        cout<<"Difference: $"<<diff<<"\n";
        if (diff>=0){
            string thing;
            cout<<"Would you like to push this amount toward next period's budget or sock it in your virtual savings account? Type \'budget\' or \'savings\': ";
            cin>>thing;
            if (thing == "budget") *pf = diff;
            else {
                *sav += diff;
                *pf = 0;}}
        else {
            cout<<"Unfortunately you've exceeded your budget this period.\n";
            if (STOP){
                cout<<"Also, you reached your budget minimum, which means we need to start over. You'll be redirected to budget creation now.\n";
                return true;}
            string thing;
            cout<<"Would you like to reduce next period's budget by this amount or deduct it from your virtual savings account to cover the cost? Type \'budget\' or \'savings\': ";
            cin>>thing;
            if (thing == "budget") *pf = diff;
            else {
                *sav += diff;
                *pf = 0;}}
        short count4; count4 = -1;
        while(exp_ver[++count4]) exp_val[count4] = 0;
        return false;
        
        case 5:
        cout<<"\nThis is how much money you started the (week/month) with. This figure includes your initial budget amount (how much of your income you’re setting aside for us to work with). Also, if you had money left over last (week/month), we added it to the figure if you told us to, and if you spent too much, we deducted that number instead.\n";
        return false;
        
        case 6:
        cout<<"\nThis is how much money you still have left after the expenses you’ve already entered with the “SPEND!” button. We only deduct money from here if you tell us to, so make sure you’re keeping track!\n";
        return false;
        
        case 7:
        cout<<"\nYou've reached the budget minimum, so at the end of the period, we're going to create a new budget model. However, you can continue to track expenses until the end of the period. Or, you can end the current tracking and start over now by tapping the upper right corner menu and then tapping \'Delete Budget\'\n";
        return false;
        
        case 8:
        cout<<"\nTap a field below and enter how much you spent. You can only reverse an expense right after you enter it the first time, so be careful! We’ll have you confirm every entry, just in case. You can enter multiple expenses at once, and you can enter them immediately, or you can wait until the end of the week/month if you like!\n";
        return false;
        }
    return true;
        
    }

/*
if (input == 1){
    cout<<"\n*******\n";
    short count = 0;
    while (exp_ver[count]){
        cout<<count+1<<". "<<exp_nm[count]<<" -- $"<<exp_val[count]<<"\n";
        count += 1;}
    return false;}
else if (input == 2){
    cout<<"\n*******\n";
    cout<<"OMG SUPER COOL PIE CHART WITH COLORZ AND STUF\n";
    cout<<"\n*******\n";
    cout<<"<Press enter to continue>";
    getline(cin,trash);
    return false;}
else if (input == 3){
    cout<<"\n";
    short count = 0;
    while(exp_ver[count]){
        cout<<count+1<<") "<<exp_nm[count]<<"\n";
        count++;}
    if (count!=9) cout<<count+1<<") "<<exp_nm[9]<<"\n";
    short input = 0;
    double temp = 0;
    cout<<"[INFO]\n";
    cout<<"You will enter expenses by number entry, or -1 to stop.\n";
    while(1){
        cout<<"Input expense by number: ";
        cin>>input;
        if (input == -1) break;
        cout<<"Input "<<exp_nm[input-1]<<" expense amount: ";
        cin>>temp;
        exp_val[input-1] += temp;}
    cout<<"Confirmation in app would occur here\n";
    return false;}
else if (input == 4){
    cout<<"\n\nEND OF CURRENT PERIOD\n*********************\n";
    if (STOP) cout<<"## Your budget minimum was reached, so you'll need to create a new budget model. ##\n";
    cout<<"Starting Budget: $"<<budg<<"\n";
    double sum = 0;
    FOR(i,10) sum += exp_val[i];
    cout<<"Total Spent: $"<<sum<<"\n";
    double diff = budg-sum;
    cout<<"Difference: $"<<diff<<"\n";
    if (diff>=0){
        string thing;
        cout<<"Would you like to push this amount toward next period's budget or sock it in your virtual savings account? Type \'budget\' or \'savings\': ";
        cin>>thing;
        if (thing == "budget") *pf = diff;
        else {
            *sav += diff;
            *pf = 0;}}
    else {
        cout<<"Unfortunately you've exceeded your budget this period.\n";
        if (STOP){
            cout<<"Also, you reached your budget minimum, which means we need to start over. You'll be redirected to budget creation now.\n";
            return true;}
        string thing;
        cout<<"Would you like to reduce next period's budget by this amount or deduct it from your virtual savings account to cover the cost? Type \'budget\' or \'savings\': ";
        cin>>thing;
        if (thing == "budget") *pf = diff;
        else {
            *sav += diff;
            *pf = 0;}}
    int count = 0;
    while(exp_ver[count]) exp_val[count] = 0;
    return false;}
else if (input == 5){
    cout<<"\nThis is how much money you started the (week/month) with. This figure includes your initial budget amount (how much of your income you’re setting aside for us to work with). Also, if you had money left over last (week/month), we added it to the figure if you told us to, and if you spent too much, we deducted that number instead.\n";
    return false;}

else if (input == 6){
    cout<<"\nThis is how much money you still have left after the expenses you’ve already entered with the “SPEND!” button. We only deduct money from here if you tell us to, so make sure you’re keeping track!\n";
    return false;}

else if (input == 7){
    cout<<"\nYou've reached the budget minimum, so at the end of the period, we're going to create a new budget model. However, you can continue to track expenses until the end of the period. Or, you can end the current tracking and start over now by tapping the upper right corner menu and then tapping \'Delete Budget\'\n";
    return false;}

else if (input == 8){
    cout<<"\nTap a field below and enter how much you spent. You can only reverse an expense right after you enter it the first time, so be careful! We’ll have you confirm every entry, just in case. You can enter multiple expenses at once, and you can enter them immediately, or you can wait until the end of the week/month if you like!\n";
    return false;} */


