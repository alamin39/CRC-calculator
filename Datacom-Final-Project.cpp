#include<bits/stdc++.h>
using namespace std;

string Vag_fol;
string Remove_Zero(string res) ///reducing rightmost Zero
{
    for(int i=0; i<res.size();)
    {
        if(res[0]=='1')
            break;
        else
            res.erase(res.begin()+0);
    }
    return res;
}


string Xor(string Minus,string divisor)/// Xor or minus
{
    string res="";
    for(int i=0; i<Minus.size(); i++)
    {
        if(Minus[i]==divisor[i])/// if same
        {
            res+="0";
        }
        else
            res+="1";
    }
    res = Remove_Zero(res);
    return res;
}


string Division(string signal,string divisor,int div_len)
{
    string Minus,remainder;
    int i,j;
    Minus=remainder=Vag_fol="";
    for(j=0; j<div_len; j++) /// vag korar jonno 1st step.
    {
        Minus+=signal[j];
    }
    remainder = Xor(Minus,divisor);

    if(remainder.size()==0)
        remainder="";

    Vag_fol+="1";
    Minus = remainder;

    for(i=j; i<signal.size(); i++)
    {
        if(Minus.size()<divisor.size())///divisor er theke jodi choto ase 0 remove korar pore
        {
            Minus+=signal[i];
            while(Minus.size()<divisor.size() && i<signal.size())///upor theke namaesi
            {
                Vag_fol+="0";
                i++;
                Minus+=signal[i];
            }
            if(Minus.size()==divisor.size())
            {
                remainder = Xor(Minus,divisor);

                if(remainder.size()==0)
                    remainder="";

                Vag_fol+="1";
            }
            else
                remainder = Minus;
        }
        Minus = remainder;
    }
    if(Minus.size()==0)
        Minus="0";
    return Minus;
}


int main()
{
    int i,j,div_len=0,fcs_len=0,r_len=0;
    string signal,prev_signal="",divisor,remainder,Minus;

    cout<<"Input a Digital Signal Data: ";
    cin>>signal;
    prev_signal=signal;
    cout<<"\n";

    cout<<"Input Divisor: ";
    cin>>divisor;
    cout<<"\n";

    cout<<"\nSignal is: "<<prev_signal<<endl;

    div_len = divisor.size();
    fcs_len = div_len-1;/// Fcs length

    for(i=0; i<fcs_len; i++) /// Adding 0 at the End.
    {
        signal+="0";
    }

/// | This part is for Division....|

    Minus=remainder=Vag_fol="";
    Minus = Division(signal,divisor,div_len);/// receive remainder

    ///***..................................****
    signal = prev_signal;
    if(Minus.size()<fcs_len) /// if remainder length is smaller than Fcs length
    {
        string temp="",tem=Minus;
        while(temp.size()+Minus.size()<fcs_len) /// remainder er samne 0 add korsi
            temp+="0";
        Minus=temp;
        Minus+=tem;
    }
    else if(Minus.size()>fcs_len)///if remainder length is greater than Fcs length
    {
        while(Minus.size()>fcs_len) /// samne theke remove korsi.
            Minus.erase(Minus.begin()+0);
    }
    signal+=Minus;

    cout<<"\nFCS = "<<Minus<<endl;
    cout<<"\nQuotient = "<<Vag_fol<<endl; /// vag_fol print

/// This part is for after adding FCS. here, i check there is error or not

    Minus=remainder=Vag_fol="";
    Minus = Division(signal,divisor,div_len);

    Minus = Remove_Zero(Minus);

    if(Minus.size()==0)
        Minus="0";

    cout<<"Remainder : "<<Minus<<endl;

    if(Minus[0]=='1')/// if remainder is not 0 then error.
        cout<<"\nERROR!! ^_^"<<endl;
    else
        cout<<"\nNO ERROR!! *_*"<<endl;
    return 0;
}
