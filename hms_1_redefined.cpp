#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

/*------------------------- class admin ------------------------*/


class admin
{
	string buffer,dname,address,did,age;
	string adminlist[100];
    int count,addlist[100];
 public:
 
 void createindex(string filename);
 string extract_a_id(string buffer);
 void sortindex();
 
 void adddoc();
 void display_doctor();
 //void dunpack();
 //void print();
 int dsearch1(char *);
 
 /*add nurse*/
 
 void addnurse();
 void display_nurse();
 
 /*add receptionist*/
 
 void addrecep();
 void display_recep();
 
 /*add ward*/
 
 void addward();
 void display_ward();

} a;

/*------------------------- class patient ------------------------*/


class patients
{
    public:
            string pid,paddress,page,pname,pproblem;
           string pidlist[100];
           int count,addlist[100];
           void createindex();
           void remove(string);
           void insert();
           int searchindex(string);
           void search(string);
           void sortindex();
           void display_p_record();
           void print();
           string extractpid(string);
}pa;

/*--------------------------------Patinets starts from here ----------------------*/


void patients::createindex() {
     	fstream file;
	int pos;
	string buffer,pid;
     	count=-1;
     	file.open("patients.txt",ios::in);
     	while(!file.eof())
	{
           pos=file.tellg();
           buffer.erase();
           getline(file,buffer);
           if(buffer[0]!='*')
           {
                      if(buffer.empty())
                      break;
                      pid=extractpid(buffer);
                      pidlist[++count]=pid;
                      addlist[count]=pos;
           }
     }
     file.close();
     sortindex();
     buffer.erase();
 }
 string patients::extractpid(string buffer)
 {
     string pid;
     int i=0;
     pid.erase();
     while(buffer[i]!='|')
     pid+=buffer[i++];
     return pid;
 }
 void patients::insert()
 {
     string pid,pname,paage,pprob,paddr,buffer;
     int pos;
     fstream file;
     //cout<<"enter values for patientID, Patient Name,Patient Age,Patient Problem,Patient Address\n";
      cout<<"Enter  Patient ID \n";
      cin>>pid;
       cout<<"Enter  Patient name \n";
      cin>>pname;
       cout<<"Enter  Age \n";
      cin>>paage;
      cout<<"Enter  Patient problem \n";
      cin>>pprob;
      cout<<"Enter  Address\n";
      cin>>paddr;
     //cin>>pid>>pname>>paage>>pprob>>paddr;
     buffer=pid+"|"+pname+"|"+paage+"|"+pprob+"|"+paddr+"$\n";
     file.open("patients.txt",ios::out|ios::app);
     pos=file.tellp();
     file<<buffer;
     file.close();
     pidlist[++count]=pid;
     addlist[count]=pos;
     sortindex();
 }
 void patients::sortindex()
 {
     int i,j,tempadd;
     string tempusn;
     for(i=0;i<=count;i++)
     {
           for(j=i+1;j<=count;j++)
           {
               if(pidlist[i]>pidlist[j])
                {
                      tempusn=pidlist[i];
			          pidlist[i]=pidlist[j];
                      pidlist[j]=tempusn;
                      tempadd=addlist[i];
                      addlist[i]=addlist[j];
                      addlist[j]=tempadd;
                }
           }
     }
     cout<<"\n------INDEXLIST-------\n";
     cout<<"\nPATIENT ID\tINDEX";
     for(i=0;i<=count;i++)
     cout<<"\n"<<pidlist[i]<<"\t"<<addlist[i]<<endl;

 }
 void patients::search(string key)
 {
     int pos=0,t;
     string buffer;
     fstream file;
     buffer.erase();
     pos=searchindex(key);
     if(pos==-1)
           cout<<"Record not found\n";
     else if(pos>=0)
     {
           file.open("patients.txt");
           t=addlist[pos];
           file.seekp(t,ios::beg);
           getline(file,buffer);
           cout<<"Record found\n";
           cout<<"\nRecords are: \n"<<buffer;
           file.close();
    }
 }
  int patients::searchindex(string key)
 {
     int low=0,high=count,mid=0,flag=0;
     while(low<=high)
     {
           mid=(low+high)/2;
           if(pidlist[mid]==key)
           {
                flag=1;
                break;
           }
           else if(pidlist[mid]<key)
                low=mid+1;
           else if(pidlist[mid]>key)
                high=mid-1;
     }
     if(flag)
           return mid;
     else
           return -1;
 }
 void patients::remove(string key)
 {
  	fstream fp;
 	char delch='*';
	int pos=0,i,address;
	string buffer,pid,pname,paage,paddr,pprob;
	 fstream file;
  pos=searchindex(key);
  if(pos>=0)
  {
       file.open("patients.txt");
       address=addlist[pos];
       file.seekp(address,ios::beg);
       file.put(delch);
       file.close();
       cout<<"Record has been deleted\n";
       for(i=pos;i<count;i++)
       {
       pidlist[i]=pidlist[i+1];
       addlist[i]=addlist[i+1];
       }
      count--;
  }  else
       cout<<"Record not found\n";
  cout<<"\nUpdated file is\n";
  system("cat patients.txt");
 }
 void patients::display_p_record(){
     cout<<"The Patient details are\n";
     system("cat patients.txt");
 }
void patients::print()
{
	cout<<"Patients ID:"<<pid<<" Name:"<<pname<<" Age:"<<page<<"address:"<<paddress<<"Patient Problem"<<pproblem<<endl;
}

/*------------------Admin section ---- doctor----*/


void admin::createindex(string filename) {
     	fstream file;
	int pos;
	string buffer,aid;
     	count=-1;
     	file.open(filename,ios::in);
     	while(!file.eof())
	{
           pos=file.tellg();
           buffer.erase();
           getline(file,buffer);
           if(buffer[0]!='*')
           {
                      if(buffer.empty())
                      break;
                      aid=extract_a_id(buffer);
                      adminlist[++count]=aid;
                      addlist[count]=pos;
           }
     }
     file.close();
     sortindex();
     buffer.erase();
 }
 string admin::extract_a_id(string buffer)
 {
     string aid;
     int i=0;
     aid.erase();
     while(buffer[i]!='|')
     aid+=buffer[i++];
     return aid;
 }
 void admin::sortindex()
 {
     int i,j,tempadd;
     string tempusn;
     for(i=0;i<=count;i++)
     {
           for(j=i+1;j<=count;j++)
           {
               if(adminlist[i]>adminlist[j])

                {
                      tempusn=adminlist[i];
			          adminlist[i]=adminlist[j];
                      adminlist[j]=tempusn;
                      tempadd=addlist[i];
                      addlist[i]=addlist[j];
                      addlist[j]=tempadd;
                }
           }
     }
     cout<<"\n-------INDEXLIST--------\n";
     cout<<"\n ID\tINDEX";
     for(i=0;i<=count;i++)
     cout<<"\n"<<adminlist[i]<<"\t"<<addlist[i]<<endl;

 }
 
 

void admin::adddoc()
{
    string dname,did,age,address,buffer;

    fstream fp;
    cout << "\nEnter Name\n";
    cin >> dname;
    cout << "\nID\n";
    cin >> did;
    cout << "\nAge\n";
    cin >> age;
    cout << "\nAddress\n";
    cin >> address;

    buffer=did+"|"+dname+"|"+age+"|"+address+" $\n";
    fp.open("doctor.txt",ios::out|ios::app);
    fp<<buffer;
    
    cout<<"\nDoctor added Successfully....\n";
  	fp.close ();

}
void admin::display_doctor()
{
	 system("cat doctor.txt");

}

/*Admin section --- nurse section ----*/

void admin::addnurse()
{
    string nname,nid,age,address,buffer;

    fstream fp;
    cout << "\nEnter Name\n";
    cin >> nname;
    cout << "\nID\n";
    cin >> nid;
    cout << "\nAge\n";
    cin >> age;
    cout << "\nAddress\n";
    cin >> address;

    buffer=nid+"|"+nname+"|"+age+"|"+address+" $\n";
    fp.open("nurse.txt",ios::out|ios::app);
    fp<<buffer;
    
    cout<<"\nNurse added Successfully....\n";
  	fp.close ();

}
void admin::display_nurse()
{
	 system("cat nurse.txt");

}

/*Admin section ---- Receptionist Section -----*/

void admin::addrecep()
{
    string rname,rid,age,address,buffer;

    fstream fp;
    cout << "\nEnter Name\n";
    cin >> rname;
    cout << "\nID\n";
    cin >> rid;
    cout << "\nAge\n";
    cin >> age;
    cout << "\nAddress\n";
    cin >> address;

    buffer=rid+"|"+rname+"|"+age+"|"+address+" $\n";
    fp.open("recep.txt",ios::out|ios::app);
    fp<<buffer;
    
    cout<<"\nReceptionist added Successfully....\n";
  	fp.close ();

}
void admin::display_recep()
{
	 system("cat recep.txt");

}

/*Admin section ----- ward details----*/

void admin::addward()
{
    string wname,wno,t_beds,buffer;

    fstream fp;
    cout << "\nWard number\n";
    cin >> wno;
    cout << "\nEnter Ward Name\n";
    cin >> wname;
    cout << "\nEnter Total number of Beds present\n";
    cin >> t_beds;

    buffer=wno+"|"+wname+"|"+t_beds+" $\n";
    fp.open("ward.txt",ios::out|ios::app);
    fp<<buffer;
    
    cout<<"\nWard added Successfully....\n";
  	fp.close ();

}
void admin::display_ward()
{
	 system("cat ward.txt");

}

 int main()
 {
     int ch;
     string key;
     patients pa;
     admin ad;
     string filename_doctor="doctor.txt";
     string filename_nurse="nurse.txt";
     string filename_recep="recep.txt";
     string filename_ward="ward.txt";
    while(1){

            int dch,nch,rch;
            string username="admin",password="jnnce",u,p;
            cout<<"\nHOSPITAL MANAGEMENT SYSTEM\n";
            cout<<"Enter \n1. Admin\n2. Doctor\n3.Nurse\n4.Receptionist\n0.Exit";
            cout<<"\nEnter your choice\n";
            cin>>ch;
            switch(ch)
             {
   		            case 1:
                    cout<<"Enter your username\n";
                    cin>>u;
                    cout<<"Enter your password\n";
                    cin>>p;
                    if(u==username && p==password)
                    {
                         int ach;
                        cout<<"Welcome Admin";
                        cout<<"\n1. ADD Doctors\t\t2. Display doctors records\n3. Add Nurse\t\t4. Display Nurse records\n5. Add Receptionist\t6. Display Receptionist Record\n7. add ward\t\t8. Display Ward details\n\n Enter your choice\n";
                        cin>>ach;
                        switch(ach)
                        {
                            case 1:a.adddoc();
                            		ad.createindex(filename_doctor);
                                    break;
               	            case 2:a.display_doctor();
                   		            break;
                   		    case 3:a.addnurse();
                   		    		ad.createindex(filename_nurse);
                   		    		break;
                   		    case 4:a.display_nurse();
                   		    		break;
                	        case 5:a.addrecep();
                	        		ad.createindex(filename_recep);
                                    break;
                            case 6:a.display_recep();
                            		break;
                        	case 7:a.addward();
                        			ad.createindex(filename_ward);
                            		break;
                        	case 8:a.display_ward();
                        			break;

                        default:cout<<"Invalid choice";
                     	}
                	}

                break;

        case 2:cout<<"Welcome doctor\n";
                        cout<<"1. Search Patient Record\n2. Display Patient Record\nEnter your choice \n";
                        cin>>dch;
                        switch(dch)
                        {
                               case 1: cout<<"enter Patient ID\n";
                                    cin>>key;
                                    pa.search(key);
                                    break;
            	                case 2:pa.display_p_record();
             	                       break;
                        }
                        break;

       	case 3:
       	                cout<<"Welcome Nurse\n";
                        cout<<"1. Search Patient Record\n2. Display Patient Record\nEnter your choice \n";
                        cin>>nch;
                        switch(nch)
                        {
                             case 1: cout<<"enter Patient ID\n";
                                    cin>>key;
                                    pa.search(key);
                                    break;

   		       	            case 2:pa.display_p_record();
   		       	            break;

                        }
                        break;

        case 4:cout<<"Welcome Receptionist\n";
        	            cout<<"1. Add Patient\n2.Generate Bill\n3.Remove Patients";
        	            cout<<"Enter your choice\n";
        	            cin>>rch;
        	            switch(rch)
        	            {
        		            case 1: pa.insert();
        		                    break;
        	                /*	case 2:generatebill();
        		                    break;
                                */
                            case 3: cout<<"enter Patient ID\n";
                                    cin>>key;
                                    pa.remove(key);
                                     break;
        		            default:cout<<"Invalid choice";

        	            }


                      break;
        case 0:exit(0);
        
        default: cout<<"Invalid Choice";
        }

    }
 }
