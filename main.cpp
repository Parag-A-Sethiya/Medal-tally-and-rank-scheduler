
#include<conio.h>
#include <iostream>
#include <Windows.h>
#include <mysql.h>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include <stdio.h>
#include<fstream>


using namespace std;



 int main()
 {



     MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES * res;

    int qstate;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "", "medal_tally", 0, NULL, 0);



     char ch;
           int select;
            string password;
            cout<<"\n\n";
            system("color B0");
            cout<<" \t      ^^^......* Medal Tally And Rank Scheduler *.....^^^"<<"\n\n\n";

            cout<<"\t\t      ^^****** Password Validation *******^^\t\t";
            cout<<"\n\n\n";
            cout<<"   "<<"                     ^****^ Created By: The Admin ^****^";
            cout<<"\n\n\n";
            cout<<"   "<<"                      ^****^ Enter The Password ^****^ \n\n";
            cout<<"                                   ";

            while((ch=getch())!=13)

                {cout<<" *";
                password+=ch;
                }
                if(password=="12345")
                {

                    cout<<"\n\n\t\t   ^** Password Is Correct. Access Is Granted!! **^\n"<<endl;

                }
                else
                    {


                    cout<<"\n"<<"   "<<"     Incorrect Password";
                     exit(0);
                    cout<<endl;
                    }



        bool repeat= true;

        while(repeat= true)
        {



      cout<<"       Enter 1 To Insert New Event Record."<<"\n\n";
      cout<<"       Enter 2 To Get Records On The Basis Of Country's Name."<<"\n\n";
      cout<<"       Enter 3 To Get Records On the Basis Of Event ID."<<"\n\n";
      cout<<"       Enter 4 To Get Previous year's Event's Complete Records."<<"\n\n";
      cout<<"       Enter 5 To Get Records Between  Two years.\n\n";
      cout<<"       Enter 6 To Exit. "<<"\n\n";
      int a;
      cout<<"       Enter Your Choice :-  ";
      cin>>a;
      cout<<endl;

            switch(a)
            {

            case 1:
                {



  struct table{
  char name[10];
  int go,si,bo,tot;
  };
  struct table t[20],temp,emp,mp;
  int i,n,j,k,y,rank=1;
  string eid;
  string a,m,c;

  cout<<"\n"<<"    Enter the Name of the Event... ";
  cin>>a;
  cout<<"\n    Enter the Event ID(1 Char 2 Digits)... ";
  cin>>eid;
  cout<<"\n    Enter the Year and Month(3 char)... ";
  cin>>y;
  cin>>m;
  cout<<"\n    Enter the Host City Name... ";
  cin>>c;
  cout<<"\n    Enter the no. Of Countries participating... ";
  cin>>n;

  for(i=1;i<=n;i++)
   {
     cout<<"     Enter country's name(3 char) and no. of Gold Silver & Bronze Medals... ";
     cin>>t[i].name>>t[i].go>>t[i].si>>t[i].bo;
     t[i].tot=t[i].go+t[i].si+t[i].bo;
   }

      for(j=1;j<=n;j++)
       {
	     for(k=j+1;k<=n;k++)
	       {

	      if(t[j].go == t[k].go)
              {
                if(t[j].si == t[k].si)
	                {
	                  if (t[j].bo<t[k].bo)
	       {
		 mp=t[j];
		 t[j]=t[k];
		 t[k]=mp;
		 }
		 }
         }



	     if(t[j].go==t[k].go)
	     {
	      if(t[j].si<t[k].si)
	      {
	      emp=t[j];
	      t[j]=t[k];
	      t[k]=emp;
	      }
	     }


	      if(t[j].go<t[k].go)
	    {  temp=t[j];
	       t[j]=t[k];
	       t[k]=temp;
	     }


	   }
	  }



       if(conn)
    {
        cout <<"   Connection to database successful:\n"<<endl;
        cout<<endl;


       cout<<"          Event Name-> "<<a<<endl;
       cout<<"\n";
       cout<<"          Event-ID ->  "<<eid<<endl;
       cout<<"\n"<<"          Year & Month-> "<<y<<"  "<<m;
       cout<<"\n\n"<<"         Host City-> "<<c<<"\n\n";


      stringstream sp;
      sp << " INSERT INTO event_detail (Event_Id, Event, year, Month, Host) values ('" <<eid<<"','" <<a<<"','" <<y<<"','" <<m<<"','" <<c<<"')";


       string query = sp.str ();
        const char * q = query.c_str();
        qstate = mysql_query(conn, q);

        if (qstate == 0)
        {

            cout <<"    Record inserted successfully ..."<<endl;
        }


         else
        {
            cout <<" Error, data not inserted..."<<endl;
        }

      cout<<"\n"<<"|Event_Id | Rank | country | gold | silver |  bronze |  total |"<<"\n";
            cout<<"---------------------------------------------------------------";


    for(i=1;i<=n;i++)
      {
          if(t[i].go== t[i-1].go)
            {
                if((t[i].si == t[i-1].si) && (t[i].bo == t[i-1].bo))
                {
                    rank--;
                }
            }

       cout<<"\n"<<"| "<<eid<<"     |  "<<rank<<"   |   "<<t[i].name<<"   |  "<<t[i].go<<"   |   "<<t[i].si<<"    |    "<<t[i].bo<<"    |    "<<t[i].tot<<"   |";



        stringstream ss;

        ss << " INSERT INTO ranking (Event_Id, Rank, Country, Gold, Silver, Bronze, Total) values ('" <<eid<<" ','" <<rank<<" ','" <<t[i].name<<" ','" <<t[i].go<<" ','" <<t[i].si<<"','" <<t[i].bo<<"','" <<t[i].tot<<"')";

        string query = ss.str ();
        const char * q = query.c_str();
        qstate = mysql_query(conn, q);

        if (qstate == 0)
        {

            cout <<" Record inserted successfully ..."<<endl;
        }
        else
        {
            cout <<" Error, data not inserted..."<<endl;
        }

        rank++;
    }


       ofstream outdata;
       string filename;
       cout<<"\n\n       Enter the file name... ";
       cin>>filename;
       int rankk=1;
       outdata.open(filename.c_str());




       if(!outdata)
       {
           cout<<"\nFile Not Created\n";
       }
        else
        {
            cout<<"\n      Text File of Record Has Been Created\n";

         outdata<<"            Medal Tally Of Current Event\n\n";
        outdata<<"          Event Name-> "<<a;
       outdata<<"\n\n"<<"           Year & Month-> "<<y<<"  "<<m;
       outdata<<"\n\n"<<"         Host City-> "<<c<<"\n\n";



      outdata<<"|Event_Id | Rank | country | gold | silver |  bronze |  total |"<<"\n";
            outdata<<"---------------------------------------------------------------\n";



    for(i=1;i<=n;i++)
      {

          if(t[i].go== t[i-1].go)
            {
                if((t[i].si == t[i-1].si) && (t[i].bo == t[i-1].bo))
                {
                    rankk--;
                }
            }


       outdata<<"\n"<<"| "<<eid<<"     |  "<<rankk<<"   |   "<<t[i].name<<"   |  "<<t[i].go<<"   |   "<<t[i].si<<"    |    "<<t[i].bo<<"    |    "<<t[i].tot<<"   |";
       rankk++;
      }


        }

      outdata.close();


    }

     else

        cout <<" Connection failure"<<endl;

                }


                cout<<"\n\n\n\n";




       break;


            case 2:
                {


     MYSQL* conn;
     MYSQL_ROW row;
     MYSQL_RES* res;


     int qstate; //stores query status after execution 0 if error and non zero if succeeded

     conn= mysql_init(0);
     if(conn) //if succeeded
     {
          cout<<"   Connection To DataBase Successful :"<<endl;
          cout<<endl;
     }

    else
    {

        cout << "connection object problem!" <<mysql_error(conn)<< endl;

    }

    conn = mysql_real_connect(conn,"localhost","root","","medal_tally",0,NULL,0);
    if(conn) //if succeeded
    {//if done
          //cout<<"connection to database successful "<<conn<<endl;
        //before select insertion is done here
          string n;
          cout<<"Enter the Name of Country (3 char)  ";
          cin>>n;
          cout<<endl;
          cout<<endl;
          string fuery="SELECT * FROM ranking WHERE Country = '"+n+ " ' " ;


            const char* b = fuery.c_str();


        qstate = mysql_query(conn,b);

        if(!qstate)
        {
             //get records from conn object to res pointer
           res = mysql_store_result(conn);

            //now read and display


            //now read and display


            cout<<"Event_ID"<<"     "<<"Rank"<<"      "<<"Country"<<"     "<<"Gold"<<"      "<<"Silver"<<"       "<<"Bronze"<<"       "<<"Total"<<endl;
            cout<<"----------------------------------------------------------------------------\n";




             int z=0;

           while(row=mysql_fetch_row(res))
          {

            cout<<"  "<<row[0]<<"        "<<row[1]<<"          "<<row[2]<<"       "<<row[3]<<"          "<<row[4]<<"            "<<row[5]<<"           "<<row[6]<<endl;
            cout<<"-----------------------------------------------------------------------------\n";


                z++;

              }

                cout<<endl;
               cout<<"      Nation Participated In ";
       cout<<z;
       cout<<" Event/S";


    }

           else

        {
            cout<<"query problem: "<<mysql_error(conn)<<endl;
        }


    }



      cout<<"\n\n\n\n";
                }


    break;





   case 3:
    {

     MYSQL* conn;
     MYSQL_ROW row;
     MYSQL_RES* res;

     int qstate; //stores query status after execution 0 if error and non zero if succeeded

     conn= mysql_init(0);
     if(conn) //if succeeded
     {
          cout<<"   Connection To DataBase Successful :"<<endl;
          cout<<endl;
     }

    else
    {

        cout << "connection object problem!" <<mysql_error(conn)<< endl;

    }

    conn = mysql_real_connect(conn,"localhost","root","","medal_tally",0,NULL,0);
    if(conn) //if succeeded
    {//if done
        //cout<<"connection to database Successful "<<conn<<endl;
        //before select insertion is done here
          string eid;
          cout<<"Enter the Event Id  ";
          cin>>eid;
          cout<<endl;
          cout<<endl;
          string tuery="SELECT * FROM event_detail WHERE Event_Id = '"+eid+ " ' " ;


        const char* r = tuery.c_str();


        qstate = mysql_query(conn,r);




        if(!qstate)
        {
             //get records from conn object to res pointer
            res = mysql_store_result(conn);





            //now read and display
             cout<<"Event-ID"<<"     "<<"year"<<"     "<<"Month"<<"        "<<"Host"<<"          "<<"Event"<<endl;

             cout<<"-----------------------------------------------------------";
             cout<<endl;
              int y=0;
            while(row=mysql_fetch_row(res))
            {

                cout<<"  "<<row[0]<<"       "<<row[2]<<"       "<<row[3]<<"         "<<row[4]<<"         "<<row[1]<<endl;

                y++;


            }


            cout<<endl;

            if(y!=0)

                cout<<"      Event Found having This ID";
                else
                    cout<<"      Event Not Found Having This ID";


        }




         cout<<endl;
         cout<<endl;
        string suery="select * from ranking WHERE Event_Id = '"+eid+ " ' ";

        const char* z = suery.c_str();


        qstate = mysql_query(conn,z);






        if(!qstate)
        {
             //get records from conn object to res pointer
            res = mysql_store_result(conn);




            cout<<"Event_ID"<<"     "<<"Rank"<<"      "<<"Country"<<"     "<<"Gold"<<"      "<<"Silver"<<"       "<<"Bronze"<<"       "<<"Total"<<endl;
            cout<<"----------------------------------------------------------------------------"<<endl;
           while(row=mysql_fetch_row(res))
          {

               cout<<"  "<<row[0]<<"        "<<row[1]<<"          "<<row[2]<<"       "<<row[3]<<"          "<<row[4]<<"            "<<row[5]<<"           "<<row[6]<<endl;
               cout<<"-----------------------------------------------------------------------------\n";
           }

          }

      else
        {
            cout<<"query problem: "<<mysql_error(conn)<<endl;
        }

    }


        }

        cout<<"\n\n\n\n";

    break;



     case 4:

       {


     MYSQL* conn;
     MYSQL_ROW row;
     MYSQL_RES* res;

     int qstate; //stores query status after execution 0 if error and non zero if succeeded

     conn= mysql_init(0);
     if(conn) //if succeeded
     {
          cout<<"   connection object ok "<<endl;
     }

    else
    {

        cout << "connection object problem!" <<mysql_error(conn)<< endl;

    }

    conn = mysql_real_connect(conn,"localhost","root","","medal_tally",0,NULL,0);
    if(conn) //if succeeded
    {//if done
        cout<<"   connection to database Successful\n "<<endl;
        //before select insertion is done here


          string query="select * from ranking";

        const char* q = query.c_str();


        qstate = mysql_query(conn,q);

        if(!qstate)
        {
             //get records from conn object to res pointer
            res = mysql_store_result(conn);
            //now read and display


            cout<<"Event_ID"<<"     "<<"Rank"<<"     "<<"Country"<<"    "<<"Gold"<<"     "<<"Silver"<<"     "<<"Bronze"<<"     "<<"Total"<<endl;
            cout<<"--------------------------------------------------------------------------";
            cout<<endl;
           while(row=mysql_fetch_row(res))
          {

               cout<<"  "<<row[0]<<"        "<<row[1]<<"          "<<row[2]<<"       "<<row[3]<<"       "<<row[4]<<"          "<<row[5]<<"         "<<row[6]<<endl;
               cout<<"------------------------------------------------------------------------\n";
           }

        }




        string iqry="select * from event_detail";
         const char* p = iqry.c_str();
         cout<<endl;


        qstate = mysql_query(conn,p);
        if(!qstate)
        {
             //get records from conn object to res pointer
            res = mysql_store_result(conn);
            //now read and display
            cout<<"Event-ID"<<"     "<<"year"<<"     "<<"Month"<<"        "<<"Host"<<"            "<<"Event_Name"<<endl;
            cout<<"----------------------------------------------------------------";
            cout<<endl;
            while(row=mysql_fetch_row(res))
            {
                cout<<"  "<<row[0]<<"       "<<row[2]<<"       "<<row[3]<<"         "<<row[4]<<"             "<<row[1]<<endl;
                cout<<"------------------------------------------------------------------------\n";
            }

        }
        else
        {
            cout<<"query problem: "<<mysql_error(conn)<<endl;
        }

    }

    else
    {
       cout << "connection object problem!" <<mysql_error(conn)<< endl;
    }
       }

       cout<<"\n\n\n\n";

    break;



     case 5:
        {
           MYSQL* conn;
     MYSQL_ROW row;
     MYSQL_RES* res;

     int qstate; //stores query status after execution 0 if error and non zero if succeeded

     conn= mysql_init(0);
     if(conn) //if succeeded
     {
          cout<<"   connection object ok "<<endl;
     }

    else
    {

        cout << "connection object problem!" <<mysql_error(conn)<< endl;

    }

    conn = mysql_real_connect(conn,"localhost","root","","medal_tally",0,NULL,0);
    if(conn) //if succeeded
    {//if done

        {


        cout<<"   connection to database Successful\n "<<endl;


        }

          string y1,y2;
          int d=0;
          cout<<"   Enter Both years... ";
          cin>>y1>>y2;

        string wqry="SELECT * FROM event_detail WHERE Year BETWEEN '"+y1+ " ' AND '"+y2+ " ' ";
         const char* w = wqry.c_str();
         cout<<endl;


        qstate = mysql_query(conn,w);
        if(!qstate)
        {
             //get records from conn object to res pointer
            res = mysql_store_result(conn);
            //now read and display
            cout<<"Event-ID"<<"     "<<"year"<<"     "<<"Month"<<"        "<<"Host"<<"            "<<"Event_Name"<<endl;
            cout<<"--------------------------------------------------------------------";
            cout<<endl;
            while(row=mysql_fetch_row(res))
            {
                cout<<"  "<<row[0]<<"       "<<row[2]<<"       "<<row[3]<<"         "<<row[4]<<"             "<<row[1]<<endl;
                cout<<"------------------------------------------------------------------------\n";
                d++;
            }

            cout<<endl;
            cout<<"       Total"<<" "<<d<<" Event/S Found";

        }
        else
        {
            cout<<"query problem: "<<mysql_error(conn)<<endl;
        }

    }

    else
    {
       cout << "connection object problem!" <<mysql_error(conn)<< endl;

    }

       cout<<"\n\n\n\n";

            }


        break;






   case 6:
       {


    exit(0);
       }
    break;


     default:
         {
         cout<<"wrong choice";
         }

            }
        }

        mysql_free_result(res);
        mysql_close(conn);


    return 0;
   }

