#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include<iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <cstdlib>
#include <time.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <cstdio>
#include <ctime>
#include <chrono>

#include "subset.h"


using namespace std ;
using namespace chrono;

//--------- Global varibles---------
int subset_size ,set_size ;

// ---------Functions prototypes ---------


//--------- Fuction for Reading File

void ReadPR(vector<int>& v, subset subsets []){
    fstream readFile;
    readFile.open("ECP_5.txt");
    
    int i;
    string line_string;
    ifstream infile("ECP_5.txt");
    getline( infile , line_string);
    stringstream ss(line_string);
    
    
    while(  ss >> i)               //--------- reading set X
        v.push_back(i);


    getline( infile , line_string);//--------- reading number of subsets
    stringstream ss2(line_string);
    ss2>> subset_size;
    
    for (int x=0 ; x < subset_size ; x++) {      //--------- reading each subset
      
        
        getline( infile , line_string);
        stringstream ss3(line_string);
        
        while(  ss3 >> i)
        {
            subsets[x].sub_vector.push_back(i);
        }
    }
    
    readFile.close();
}


//--------- Print function ---------
void print (vector<int> setX, subset subsets [])
{
    cout<<"The main set (SetX) content: "<<endl;
    for (int i=0; i< setX.size() ; i++) {
        cout<<setX[i]<<' ';
    }
    cout<<endl;
    
    cout<<"\nNumber of subsets is: "<<subset_size<<endl;
    
    
    cout<<"\nSubset number" <<" |  Subset content"<<endl;
    cout<<"-------------------------------------------------------"<<endl;
    for (int x=0 ; x < subset_size; x++) {
        if (x<10)
            cout<<"     "<<x <<"        |  ";
        else
            cout<<"     "<<x <<"       |  ";
        
        for (int y=0 ; y < subsets[x].sub_vector.size() ; y++) {
            cout<< subsets[x].sub_vector[y]<<' ';
            
        }
        cout<<endl;
    }

}


//--------- Print flage function ---------
void print_flage (subset subsets [])
{
    cout<<"Sub-collection : \n";
    cout<<"Subset number    | ";
    for (int x=0 ; x < subset_size; x++) {
        
        cout<<x<<' ';
    }
    
    cout<<"\n";
    cout<<"------------------ ";
    for (int x=0 ; x < subset_size; x++) {
        if (x > 9)
            cout<<' '<<"-"<<' ';
        else
        cout<<"-"<<' ';
    }
    cout<<"\n";
    cout<<"Subset flag      | ";
    for (int x=0 ; x < subset_size; x++) {
        
        if (x > 9)
            cout<<' '<<subsets[x].flag<<' ';
        else
            cout<<subsets[x].flag<<' ';
    }

    cout<<"\n\n";
    
}


//---------  function for selecting flags randomly ---------

void random_flage(subset subsets [])
{
    srand(getpid());
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> idist(0,(subset_size-1));
    srand(time(NULL));

    for (int count=0 ;count < (subset_size-20) ;count++) // try----->  count < idist(gen)
    {
        int random_num = idist(gen);
        subsets[random_num].flag = true;
    }
}

//---------  h1----> number of missing values in array. ---------
int h1 ( vector<int> setX , subset subsets [])
{
    vector<int> set_flag_T;
    
    for (int x=0 ; x < subset_size; x++) {
        if (subsets[x].flag) {
            
            for (int j=0; j< subsets[x].sub_vector.size(); j++)
                 set_flag_T.push_back(subsets[x].sub_vector[j]) ;
        }
    }
    
    
    if (setX.size() == set_flag_T.size())
        
        return 0;
    else
    
    {
        int h = (setX.size() - set_flag_T.size());
        if (h < 0) {
            return 0;
        }
        
        return h;
    }

}

//---------  h2----> number of digit in which a recurrence occurred(overlapping). ---------
int h2 ( vector<int> setX , subset subsets [])
{
    vector<int> set_flag_T;
    
    for (int x=0 ; x < subset_size; x++) {
        if (subsets[x].flag) {
            
            for (int j=0; j< subsets[x].sub_vector.size(); j++)
                set_flag_T.push_back(subsets[x].sub_vector[j]) ;
        }
    }
    
    int overlapping =0;
    for (int x=0 ; x < set_flag_T.size() ; x++) {
        int value =  set_flag_T[x];
        
        for (int j=x ; j < set_flag_T.size() ; j++) {

            if (j != x)
                if (value == set_flag_T[j])
                    overlapping++ ;
        }
    }
    
    return overlapping ;
    
}
//---------   f(n) = h1 + h2. ---------

int obiectiv_function ( vector<int> setX , subset subsets [])
{
    return (h1 ( setX ,  subsets) + h2 ( setX ,  subsets));
}

//--------- Generate a random neighboring solution ---------
void G_neighboring (subset subsets [] , subset subsets_neighboring [] )
{
    
    for (int x=0 ; x < subset_size; x++) {
        subsets_neighboring[x].sub_vector.clear();
        subsets_neighboring[x].flag=false;
    }
    
    for (int x=0 ; x < subset_size; x++)
    {
        for (int y=0 ; y < subsets[x].sub_vector.size() ; y++)
        {
            subsets_neighboring[x].sub_vector.push_back(subsets[x].sub_vector[y]);
            
        }
    }
    
    
    random_flage(subsets_neighboring);

}

//-------- copy solution -------------
void copy_solution (subset subsets [] , subset subsets_neighboring [] )
{
    for (int x=0 ; x < subset_size; x++) {
        subsets_neighboring[x].sub_vector.clear();
        subsets_neighboring[x].flag=false;
    }
    
    
    for (int x=0 ; x < subset_size; x++)
    {
        subsets_neighboring[x].flag = subsets[x].flag;
        for (int y=0 ; y < subsets[x].sub_vector.size() ; y++)
            subsets_neighboring[x].sub_vector.push_back(subsets[x].sub_vector[y]);
    }
}


//-------- randomly-generated for simulated annealing -------------
double randomly_generated()
{
    double lower_bound = 0.0;
    double upper_bound = 1.0;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::default_random_engine re;
    double a_random_double = unif(re);
    return a_random_double;
}

//--------- The acceptance probability function ---------
double  acceptance_probability (int old_cost,int new_cost,double T)
{
    return ((2.71828)*((new_cost-old_cost)/T)) ;
}


//--------- simulated annealing function ---------
void simulated_annealing ( vector<int> setX ,subset subsets [] , subset subsets_neighboring [])
{
    double temperature= 1.0;
    double temperature_min = 0.00001;
    double alpha = 0.9;
    int i;
    int old_cost =obiectiv_function(setX , subsets );
    cout<< "Objective function f(n) = h1 + h2 for initial state is : "<<old_cost<<endl;
    print_flage (subsets);
    cout<< " ======================================================== "<<endl;

    while (temperature > temperature_min )
    {
        if (old_cost == 0)
            break;
        i=1;
        while (i <= 100) {
            
        
        G_neighboring ( subsets  ,  subsets_neighboring  );
        int new_cost  =obiectiv_function(setX , subsets_neighboring ); // Calculate neighboring cost
            if (i==1 && temperature==1.0)
                cout<< "Objective function f(n) = h1 + h2 for neighboring state is : "<< new_cost<<endl;
            
            if (new_cost == 0)
            {
                copy_solution(subsets_neighboring, subsets);
                old_cost = new_cost;
                break;
            }
            
            
            
        double ap = acceptance_probability(old_cost, new_cost, temperature);
        
        if (ap > randomly_generated() )
        {
            copy_solution(subsets_neighboring, subsets);
            old_cost = new_cost;
        }
            if (old_cost == 0)
                break;
            i++;
            
            
          
        }
          temperature = temperature * alpha;
    }
    
    cout<< " ======================================================== "<<endl;
    cout<< "After Applying Simulated Annealing Algorithm we get the following solution :"<<endl;
    print_flage (subsets);
    cout<< "Objective function f(n) = h1 + h2 for Goal state is : "<<old_cost<<endl;

    
}
void start_ ()
{

    
    vector<int> setX;  //--------- big set X
    
    
    subset subsets [26] ;   //--------- sub-collection
    subset subsets_neighboring [26] ;   //--------- sub-collection neighboring
    
    
    ReadPR(setX , subsets );
    
    print (setX , subsets );
    random_flage(subsets);
    
    cout<< " ======================================================== "<<endl;
    simulated_annealing ( setX , subsets  ,  subsets_neighboring );
    

    
}

//--------- Main function ---------
int main()
{
    auto start = high_resolution_clock::now();
    
    
    start_ ();

    
    auto end = high_resolution_clock::now();
    cout << "Run Time (seconds) : "<<duration_cast<seconds>(end - start).count() << '\n';
    cout << "Run Time (microseconds) : "<<duration_cast<microseconds>(end - start).count() << '\n';

    
    return 0;
}
