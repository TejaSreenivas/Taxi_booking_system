#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;
class booking{
    public:
    int custid,fr,to,ptym,dtym,cost,taxid;
};vector<booking> history;
class location{
public:
    int id;
    vector<int> available;
};vector<location> loc;
class cust{
    public:
        int spent=0;
        vector<int> hist;
};vector<cust> customers;
class taxi{
    public:
    int earn=0;
    vector<int> hist;
};vector<taxi> taxis;

bool cmplist1(int x,int y){
    return taxis[x].earn<taxis[y].earn;
}
bool evaluate(booking& bk){

    int x,frt=bk.fr,bac=bk.fr;
    if(loc[bk.fr].available.begin()!=loc[bk.fr].available.end()){
        sort(loc[bk.fr].available.begin(),loc[bk.fr].available.end(),cmplist1);
        x=loc[bk.fr].available[0];
    }
    else{
        bac=bk.fr+1;
        while(bac<loc.size()){
            if(loc[bac].available.begin()!=loc[bac].available.end()){
                  x=loc[bac].available[0];
                 break;
            }
            bac++;
        }
        frt=bk.fr-1;
        while(frt>=0){
            if(loc[frt].available.begin()!=loc[frt].available.end()){
                x=loc[frt].available[0];
                 break;
            }
            frt--;
        }

    }
    if(x==-1)
        return false;
    else{
        if(bac==frt){
            loc[bk.fr].available.erase(loc[bk.fr].available.begin()+x);
        }
        else{
                if(bac-bk.fr<bk.fr-frt)
                    loc[bac].available.erase(loc[bk.fr].available.begin()+x);
                else
                    loc[frt].available.erase(loc[bk.fr].available.begin()+x);

        }
        loc[bk.to].available.push_back(x);
    }
    bk.dtym=bk.ptym+abs(bk.fr-bk.to);
    bk.cost=30*abs(bk.fr-bk.to);
    taxis[x].earn+=bk.cost;
    customers[bk.custid].spent+=bk.cost;
    bk.taxid=x;
    return true;
}
initial(int n_taxis){
    for(int i=0;i<n_taxis;i++)
        loc[0].available.push_back(i);
}
void display(int i){

        cout<<"taxi: "<<i+1<<"  details"<<endl;
        cout<<"from    To   cost"<<endl;
        for(int k=0;k<taxis[i].hist.size();k++){
            cout<<history[taxis[i].hist[k]].fr<<"  "<<history[taxis[i].hist[k]].to<<"  "<<history[taxis[i].hist[k]].cost<<endl;
        for(int k=0;k<history.size();k++)
            cout<<history[k].custid<<" "<<history[k].fr<<" "<<history[k].to<<" "<<history[k].ptym<<endl;
        }

}
int main(){
    int n_cust,n_taxi,n_loc;
    cout<<"enter number of customers,taxis,locations"<<endl;
    cin>>n_cust>>n_taxi>>n_loc;
    customers.resize(n_cust);taxis.resize(n_taxi);loc.resize(n_loc);
    initial(n_taxi);
    fstream file("C:\\Users\\k_tej\\Documents\\TEJA\\Programming\\c++\\zoho\\taxi\\booking_data.txt",ios_base::in);
    string a;
    while(file>>a){
        booking bk;
        bk.custid=atoi(a.c_str());
        file>>a;
        bk.fr=atoi(a.c_str());
        file>>a;
        bk.to=atoi(a.c_str());
        file>>a;
        bk.ptym=atoi(a.c_str());
        if(evaluate(bk)){
            history.push_back(bk);
            cout<<"booking "<<history.size()<<" completed"<<endl;
        }
        else
            cout<<"booking unsuccessful ! "<<endl;

    }
    display(0);
    return 0;
}
