#include<iostream>
#include<iomanip>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<time.h>
#include<sstream>

using namespace std;

int offset,n=0,suthan=0;

class pharmacy
{
    public:
    char item_name[20],category[10],major_comp[20],exp_date[10],mg[5],rate[10],no_items[5],disease[20],buffer[100];

    void add_item()
    {
        fstream rf,pf,sf;

        cout<<"\n\n--------------------Enter item details-------------------\n\n";
        cout<<"\t\tItem Name: ";
        cin>>item_name;
        cout<<"\t\tCategory: ";
        cin>>category;
        cout<<"\t\tMajor Component: ";
        cin>>major_comp;
        cout<<"\t\tmg: ";
        cin>>mg;
        cout<<"\t\tDisease/purpose:";
        cin>>disease;
        cout<<"\t\tExpiry Date(mm/yyyy): ";
        cin>>exp_date;
        cout<<"\t\tRate: ";
        cin>>rate;
        cout<<"\t\tNumber of items: ";
        cin>>no_items;

        rf.open("recordfile.txt",ios::out|ios::app);
        pf.open("pindex.txt",ios::out|ios::app);
        sf.open("sindex.txt",ios::out|ios::app);

        strcpy(buffer,"");
        strcat(buffer,item_name); strcat(buffer,"|");
        strcat(buffer,category);strcat(buffer,"|");
        strcat(buffer,major_comp);strcat(buffer,"|");
        strcat(buffer,mg); strcat(buffer,"|");
        strcat(buffer,disease); strcat(buffer,"|");
        strcat(buffer,exp_date);strcat(buffer,"|");
        strcat(buffer,rate); strcat(buffer,"|");
        strcat(buffer,no_items); strcat(buffer,"\n");

        int len=strlen(buffer);

        rf<<buffer;
        rf.seekg(0,ios_base::end);
        int fsize=rf.tellg();
        offset=fsize-len;
        pf<<item_name<<"|"<<offset<<"\n";
        sf<<exp_date<<"|"<<major_comp<<"|"<<offset<<"\n";
        n=n+1;

        cout<<"\n--------------------Item added succesfully------------------------\n";

        rf.close();
        pf.close();
        sf.close();
    }

    void search_s(char key[])
    {
        fstream sf;
        char addr[3];int selected;
        int found=0,items[10],i=0;

        sf.open("sindex.txt",ios::in);

        while(!sf.eof())
        {
            sf.getline(exp_date,10,'|');
            sf.getline(major_comp,20,'|');
            sf.getline(addr,3,'\n');
            if((strcmp(exp_date,key)==0)||(strcmp(major_comp,key)==0))
            {
                found+=1;
                items[i]=atoi(addr);
                cout<<i<<"\t";
                offset=items[i];
                i++;
                display();
            }
        }
        if(found>=1)
        {

            cout<<"---------------------Select item number you want---------------------\n\n ";
            cin>>selected;

                offset=items[selected];
                 cout<<setw(15)<<item_name<<setw(15)<<category<<setw(25)<<major_comp<<setw(10)<<mg<<setw(15)<<disease<<setw(20)<<exp_date<<setw(10)<<rate<<setw(20)<<no_items<<"\n";

                                display();
        }
        else
        {
            cout<<"\n----------------Item not in stock------------------\n";
            suthan=1;
        }

        sf.close();
        return;

    }

    void display()
    {
        fstream rf;
        rf.open("recordfile.txt",ios::in);
        rf.seekg(offset);

        rf.getline(item_name,20,'|');
        rf.getline(category,10,'|');
        rf.getline(major_comp,20,'|');
        rf.getline(mg,5,'|');
        rf.getline(disease,20,'|');
        rf.getline(exp_date,10,'|');
        rf.getline(rate,10,'|');
        rf.getline(no_items,5,'\n');


        cout<<setw(15)<<item_name<<setw(15)<<category<<setw(25)<<major_comp<<setw(10)<<mg<<setw(15)<<disease<<setw(20)<<exp_date<<setw(10)<<rate<<setw(20)<<no_items<<"\n";

        rf.close();


    }


     void search_p(char key[])
    {
        fstream pf;
        char addr[3];
        int found=0;

        pf.open("pindex.txt",ios::in);
        cout<<"\n\n\t\t"<<setw(10)<<"ITEM NUM"<<setw(15)<<"ITEM NAME"<<setw(15)<<"CATEGORY"<<setw(25)<<"MAJOR COMPONENT"<<setw(10)<<"mg"<<setw(15)<<"PURPOSE"<<setw(20)<<"EXPIRY DATE"<<setw(10)<<"RATE"<<setw(20)<<"No OF ITEMS\n\n";
        while(!pf.eof())
        {
            pf.getline(item_name,20,'|');
            pf.getline(addr,3,'\n');
            if(strcmp(item_name,key)==0)
            {
                found=1;
                offset=atoi(addr);
                cout<<"\t\t"<<setw(10)<<"0";
                display();
                pf.close();
                return;
            }
        }

        if(found==0)
           search_s(key);

        pf.close();
        return;
    }


    void sell()
    {
        char key[20];
        int num,temp;
        float cost;
        cout<<"\t\tSearch: ";
        cin>>key;
        search_p(key);
        if(suthan==1)
            return;

        cout<<"\n\t\tEnter number of items to sell: ";
        cin>>num;
        if (num>atoi(no_items))
        {
            cout<<"\n------------------------Insufficient stock------------------------------\n ";
            return;
        }
        else
        {
            cost=atof(rate)*num;
            cout<<"\n-------------------------BILL-------------------------\n\n";
            cout<<"ITEM NAME\tmg\tNUM OF ITEMS\tCOST\n";
            cout<<item_name<<"\t"<<mg<<"\t"<<num<<"\t"<<cost<<"\n";
            temp=atoi(no_items);
            temp-=num;

            fstream rf;
            rf.open("recordfile.txt",ios::out|ios::in);

            rf.seekp(offset,ios::beg);

            rf<<item_name<<'|'<<category<<'|'<<major_comp<<'|'<<mg<<'|'<<disease<<'|'<<exp_date<<'|'<<rate<<'|'<<temp<<'\n';

            rf.close();
        }

    }




};

int main()
{
    pharmacy obj;
    int ch;
    char key[20];

    fstream sf,rf,pf;
    rf.open("recordfile.txt",ios::out);
    pf.open("pindex.txt",ios::out);
    sf.open("sindex.txt",ios::out);
    rf.close();
    pf.close();
    sf.close();
     cout<<"-------------------------------------------------------------------------";
        cout<<"\n\t\t\tPharmacitical Billing System\t\t\t\n";
        cout<<"-------------------------------------------------------------------------";
    while(1)
    {

        cout<<"\n\n\t\t(1) ADD ITEM\n\t\t(2) SELL\n\t\t(3) SEARCH\n\t\t(4) DISPOSE EXPIRED ITEMS\n\t\tPress any key to exit\n\t\tEnter your choice: ";
        cin>>ch;
        switch(ch)
        {
            case 1: obj.add_item();
                    break;
            case 2: obj.sell();
                    break;
            case 3: cout<<"\n\t\tWhat do you like to search?\n\t\t";
                    cin>>key;
                    obj.search_p(key);
                    break;


           case 4:
                {
                        time_t thetime=time(NULL);
                        struct tm *atime=localtime(&thetime);
                        int month=atime->tm_mon+1;
                        int year=atime->tm_year+1900;

                        stringstream s;
                        s<<month<<'/'<<year;
                        string temp1=s.str();
                        char* cur_date=(char*)temp1.c_str();
                        cout<<"\n\t\tcurrent date: "<<cur_date<<"\n";

                        char addr[3];
                        int selected;
                        int found=0,items[10],i=0,en,rec_len,k,j,c,loc,temp[50];
                        pharmacy rec[50];

                        sf.open("sindex.txt",ios::in);

                        while(!sf.eof())
                        {
                            sf.getline(obj.exp_date,10,'|');
                            sf.getline(obj.major_comp,20,'|');
                            sf.getline(addr,3,'\n');
                            if(strcmp(obj.exp_date,cur_date)==0)
                            {
                                found+=1;
                                items[i]=atoi(addr);
                                cout<<i<<"\t";
                                offset=items[i];
                                i++;
                                obj.display();
                            }
                        }
                        en=i;
                        sf.close();
                        i=0;
                        j=0;

                        rf.open("recordfile.txt",ios::in);


                        while(j<en)
                        {
                            cout<<"loop 1";
                            rf.seekg(items[j],ios::beg);
                            rf.getline(obj.buffer,100,'\n');
                            rec_len=strlen(obj.buffer)+1;
                            cout<<"len="<<rec_len;
                            while(!rf.eof())
                            {
                                cout<<"loop 2";
                                rf.getline(rec[i].item_name,20,'|');
                                rf.getline(rec[i].category,10,'|');
                                rf.getline(rec[i].major_comp,20,'|');
                                rf.getline(rec[i].mg,5,'|');
                                rf.getline(rec[i].disease,20,'|');
                                rf.getline(rec[i].exp_date,10,'|');
                                rf.getline(rec[i].rate,10,'|');
                                rf.getline(rec[i].no_items,5,'\n');
                                i++;
                            }
                            rf.close();


                            rf.open("recordfile.txt",ios::out|ios::in);


                            rf.seekp(items[j],ios::beg);
                            k=0;
                            while(k<i-1)
                            {
                                cout<<"loop 3";
                                strcpy(obj.buffer,"");
                                strcat(obj.buffer,rec[k].item_name); strcat(obj.buffer,"|");
                                strcat(obj.buffer,rec[k].category);strcat(obj.buffer,"|");
                                strcat(obj.buffer,rec[k].major_comp);strcat(obj.buffer,"|");
                                strcat(obj.buffer,rec[k].mg); strcat(obj.buffer,"|");
                                strcat(obj.buffer,rec[k].disease); strcat(obj.buffer,"|");
                                strcat(obj.buffer,rec[k].exp_date);strcat(obj.buffer,"|");
                                strcat(obj.buffer,rec[k].rate); strcat(obj.buffer,"|");
                                strcat(obj.buffer,rec[k].no_items); strcat(obj.buffer,"\n");

                                rf<<obj.buffer;
                                k++;
                            }
                            rf.close();

                            pf.open("pindex.txt",ios::in);

                            c=0;

                            while(!pf.eof())
                            {
                                pf.getline(rec[c].item_name,20,'|');
                                pf.getline(rec[c].mg,5,'\n');
                                loc=atoi(rec[c].mg);
                                if(loc==items[j])
                                    continue;
                                else if(loc>items[j])
                                    temp[c]=loc-rec_len;
                                else
                                    temp[c]=loc;
                                c++;
                            }
                            pf.close();
                            pf.open("pindex.txt",ios::out);
                            k=0;
                            while(k<c-1)
                            {
                                pf<<rec[k].item_name<<"|"<<temp[k]<<"\n";
                                k++;
                            }
                            pf.close();

                            sf.open("sindex.txt",ios::in);


                            c=0;
                            while(!sf.eof())
                            {
                                sf.getline(rec[c].exp_date,10,'|');
                                sf.getline(rec[c].major_comp,20,'|');
                                sf.getline(rec[c].mg,3,'\n');
                                loc=atoi(rec[c].mg);
                                if(loc==items[j])
                                    continue;
                                else if(loc>items[j])
                                    temp[c]=loc-rec_len;
                                else
                                    temp[c]=loc;
                                c++;
                            }
                            sf.close();
                            sf.open("sindex.txt",ios::out);
                            k=0;
                            while(k<c-1)
                            {
                                 sf<<rec[k].exp_date<<"|"<<rec[k].major_comp<<"|"<<temp[k]<<"\n";
                                 k++;
                            }
                            j++;
                        }
                        cout<<"\n------------------Expired items disposed succesfully-----------------";

                        sf.close();
                        break;
                    }
            default:cout<<"\n\n****************************THANK YOU*****************************\n\n";exit(0);
        }
    }
}
