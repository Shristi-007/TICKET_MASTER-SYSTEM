#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// variables to store the hall number
int obn, ext, direct_cust = 0, print_once = 0;
// direct_cust=0 if the user directly goes to the user rather than manager
int m = 0, *p, sn, argg, arg2, tckt, tckt_prnt, nt = 0, sti, foundu = 0, foundp = 0, pass_chk = 0, mv_str = 0, data_store = 0;
double cost = 0;
// data_store =0 o store that data is stored in file successfully
// mv_str: to run the loop when data is being brought from file to compiler
int pas_rak = 0; // to store the return value of function password_check()
// sn is variable for show number in manager function N m is for number of shows in a day
// pass_chk stores the value i.e password matched or not
// foundu to storevalue if user exists
// foundo to storevalue if password is correct
char cust_in;
// cust_in: to store if customer is new or existing
// stime: for storing showtime input in manager fn
// st: for showtime check the seat_disp func
// tckt: to count the no of tickets to be booked by the customer
// tckt_prnt: to print the no. of tickets to be booked
// nt: to store the number of timings of a particular movie
string name[100], tkt_pnt, pass, cust_id, cust_pas, user, hall_name;
// pass is to save the password
// cust_id: to store the customer id
// cust_pas: to store the customer password
// tkt_pnt: to print the movie name in the ticket
// hall_name: to store the hall name
int ar[100][100][100][12][18], tkt_row[12], tkt_col[18], str_time[100];
/* array ar:
1st arg: to store movie no.
2nd arg: for particular showtime of particular movie
3rd arg: for rows
4th arg: for columns
*/
// str_time: for saving the no. of show of a particular movie
string tim[100][100];
// tim array: to store the timings of a particular movie
// 1st argument for movie number and 2nd for no. of timings that particular movie runs
string timing[100]; // to store various timings of movie in file
class movie_booking
{
public:
    void first();
    void show_seat_frm_file();
    void show();
    void seatdisp(int z, int wt);
    void book(int z, int wt, int a);
    void seatin(int z, int wt);
    void manager();
    void ticket_print();
    void pass_protect();
    void data_str();
    int password_check();
    void Hall_name()
    {
        switch (obn)
        {
        case 1:
            hall_name = "INOX VARANASI";
            break;
        case 2:
            hall_name = "CINEPOLIS VARANASI";
            break;
        case 3:
            hall_name = "KESHARI TALKIES";
            break;
        case 4:
            hall_name = "MAHARAJA";
            break;
        }
    }
};

void movie_booking::first()
{
    int i;
    char in = 'c', man, cus; // man is manager input and cus is customer
    cout << "\n\n\t\t\t\t\tTO ENTER MANAGER LOGIN PRESS 'o' or 'O' ELSE ANY OTHER KEY FOR CUSTOMER\n";
    cout << "\t\t\t\t\t\t";
    cin >> man;
    int pas_count = 0;
    if ((man == 'o') || (man == 'O'))
    {
        while (pas_count < 3)
        {
            (*this).pass_protect();
            if (pass == "RAW")
            {
                (*this).manager(); // the manager mode to set the number of seats available for booking
                pas_count = 3;
            }
            else
            {
                cout << "PASSWORD ENTERED IS WRONG!!"
                     << " Attempts Remaining = " << (2 - pas_count) << "\n";
                pas_count++;
            }
        }
    }
    system("clear");
    cout << "\n\n\t\t\t\t\t\t\tDEAR CUSTOMER TO BOOK SEATS PRESS 'y' or 'Y'\n";
    cout << "\t\t\t\t\t\t\t\t";
    cin >> cus;
    if ((cus == 'y') || (cus == 'Y'))
    {
        cout << "\n\t\t\t\t\t\t\tIF YOU ARE NEW CUSTOMER PRESS N/n TO SIGN UP\n";
        cout << "\t\t\t\t\t\t\t";
        cin >> cust_in;
        if ((cust_in == 'N') || (cust_in == 'n'))
        {
            (*this).data_str();
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\tWELCOME EXISTING CUSTOMER!!\n";
            pas_rak = (*this).password_check();
        }
        cout << "\t\t\t\t\t\t";
        cout << "PRESS ANY KEY TO CONTINUE\n";
        system("clear");
        if ((pas_rak != 0) || (data_store != 0))
        {
            cout << "\n\n\t\t\t\t\t\tTHE SEATS AVAILABLE ARE:\n";
            while ((in == 'c') || (in == 'C'))
            {
                cost = 0;
                (*this).show_seat_frm_file();
                cout << "\n\n\t\t\t\t\t\t\tENTER THE MOVIE NUMBER TO BOOK TICKET\n";
                cout << "\t\t\t\t\t\t\t";
                cin >> argg;
                ifstream fin; // for retrieving movie name from the file
                fin.open("movie_test2.csv");
                for (i = 0; i < argg - 1; i++)
                {
                    getline(fin, name[i], '\n');
                }
                getline(fin, name[i], ',');
                fin.close();
                cout << "\n\n\t\t\t\t\t\t\tCHOOSE THE NUMBER CORRENSPONDING TO TIMING TO BOOK TICKET FOR MOVIE :-" << endl;

                cout << "\t\t\t\t\t\t\t" << name[i];
                cout << "\t\t\t\t\t\t\t";
                cin >> sti;

                tkt_pnt = name[i];
                (*this).seatdisp(argg, sti);
                (*this).seatin(argg, sti);
                system("clear");
                (*this).seatdisp(argg, sti);
                system("clear");

                (*this).ticket_print();
                cout << "\n\n\t\t\t\t\t\t\tPRESS 'C' or 'c' IF U WANT TO BOOK SEAT AGAIN?\n";
                cin >> in;
            }
        }
        else
        {
            cout << "\n\n\t\t\t\t\t\t\t YOU PRESSED WRONG USER PASSWORD\n";
            cout << "\n\n\t\t\t\t\t\t\t PROGRAM TERMINATED!!!\n";
            cout << "\n\n\t\t\t\t\t\t\t YOU ENTERED WRONG PASSWORD";
        }
    }
}
void movie_booking::show_seat_frm_file()
{
    int i = 0, j;
    system("clear");
    cout << "\n\n\t\t\t\t\t\t\tTHE MOVIES RUNNING IN HALL ARE:\n\n\n";
    ifstream fin;
    fin.open("movie_test2.csv");
    if (direct_cust == 0)
        m = 13;
    while (i < m)
    {
        cout << "\n\t\t\t\t\t\t\t";

        getline(fin, name[i], ',');
        cout << "MOVIE :\t" << i + 1 << "\t" << name[i] << endl
             << endl;
        cout << "\t\t\t\t\t\t\t";
        cout << "THE TIMINGS OF THE MOVIE : " << name[i] << " :-  " << endl;
        int j = 0;

        getline(fin, tim[i][j], '\n');
        cout << "\t\t\t\t\t\t\t";
        cout << tim[i][j] << endl
             << endl;

        i++;
    }
}
void movie_booking::show() // this function is for entering the number of movie running in hall
{
    int i, j;
    p = (int *)(malloc(sizeof(int)));
    cout << "\n\n\t\t\t\t\t\t\tENTER THE NUMBER MOVIES RUNNING IN THE HALL\n";
    cout << "\t\t\t\t\t\t\t";
    cin >> m;
    (*p) = m;
    ofstream fout;
    fout.open("movie_test2.csv", ios::app);
    for (i = 0; i < m; i++) // m is the total no of movies running in that hall
    {
        fflush(stdin);
        cout << "\n\n\t\t\t\t\t\t\tENTER THE NAME OF MOVIE " << i + 1 << endl;
        cout << "\t\t\t\t\t\t\t";
        getline(cin, name[i]);
        fflush(stdin);
        fout << name[i] << ","; // movie name writing in file
        cout << "\n\n\t\t\t\t\t\t\tENTER THE NUMBER OF SHOWS OF MOVIE: " << name[i] << " IN A DAY : ";
        cin >> nt;
        str_time[i] = nt;
        // here a function is to be added to save the show timings
        cout << "\n\n\t\t\t\t\t\t\tENTER THE SHOW TIMINGS OF THE MOVIE : " << name[i] << endl;
        for (j = 0; j < nt; j++)
        {
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t";
            getline(cin, tim[i][j]); // this is the function for collecting the show timings
            fout << tim[i][j] << ",";
        }
        fout << endl;
    }
    fout.close();
    m += 13;
    (*this).show_seat_frm_file();
}

void movie_booking::seatdisp(int z, int wt) // 1st argument to display the seats of that particular movie
// 2nd arg is for the particular movie time
{
    argg = z;
    sti = wt;
    int i, j;
    char ch = 'A', st;
    system("clear");
    cout << "\n\nCOST OF RECTILINEAR:Rs 500/-\n";
    cout << "COST OF SUPER DELUXE :Rs 200/-\n";
    cout << "COST OF  DELUXE :Rs 100/-\n";
    ifstream fin;
    fin.open("movie_test2.csv");
    cout << "\n\n\t\t\t\t\t\t\tBOOKED SEATS ARE MARKED WITH [x]\n\n";
    for (i = 0; i < argg - 1; i++)
    {
        getline(fin, name[i], '\n');
    }
    getline(fin, name[i], ',');
    cout << "\n\n\t\t\t\t\t\t\tTHIS IS THE SEAT MATRIX FOR MOVIE: " << name[i] << "\n\n";
    fin.close();
    for (i = 0; i < 13; i++)
    {
        ch = 'A';
        ch = ch + i;
        cout << "\t";
        for (j = 0; j < 18; j++)
        {
            if (ar[obn][argg][sti][i][j] == 1)
                cout << "["
                     << " X"
                     << "]";
            else
            {
                cout << "[" << ch << j + 1 << "]";
            }

            cout << " "; // 1 white spaces given
                         // the seat would be displayed in format[A1]

            if (j == 4 || j == 12)
                cout << "\t";
        }
        cout << "\n\n";
        if (i == 12)
        {
            cout << "\n\n\t\t\t\t\t\t SCREEN THIS WAY\n";
            cout << "\t______________________________________________________________________________________________________________";
        }
    }
}

void movie_booking::book(int z, int wt, int a) // first argument is for the movie number and 3rd argument for manager mode
// 2nd arg is for show time
{
    int i, j, num, al, n, col, stor, arg;
    arg = z;
    sti = wt;
    arg2 = a;
    if (arg2 == 100)
    {
        cout << "\n\n\t\t\t\t\t\t\tADMIN ENTER THE SEATS WHICH WONT BE AVAILABLE FOR BOOKING\n";
    }

    else
    {
        cout << "\n\n\t\t\t\t\t\t\tCUSTOMER BOOKING\n";
    }

    (*this).seatdisp(arg, sti);
    char ch = 'A', chr;
    cout << "\n\n\t\t\t\t\t\t\tENTER THE SEAT NUMBER\t";

    cin >> chr >> col;
    stor = chr - 65;
    col = col - 1;

    if (ar[obn][arg][sti][stor][col] == 0)
    {
        ar[obn][arg][sti][stor][col] = 1;

        tkt_col[tckt] = col;
        tkt_row[tckt] = stor;
    }
    else
    {

        while (ar[obn][arg][sti][stor][col] != 0)
        {
            if (arg2 == 100)
            {
                cout << "\n\n\t\t\t\t\t\t\tADMIN YOU HAVE ALREADY MARKED THIS SEAT AS BOOKED ENTER A NEW SEAT WHICH IS BOOKED\n";
                cout << "\t\t\t\t\t\t\t ";
            }

            else
            {
                cout << "\n\n\t\t\t\t\t\t\tTHE SEAT YOU SELECTED IS ALREADY OCCUPIED ENTER A NEW SEAT\n";
                cout << "\t\t\t\t\t\t\t ";
            }
            cin >> chr >> col;
            stor = chr - 65;
            col = col - 1;
        }
        ar[obn][arg][sti][stor][col] = 1;
        tkt_col[tckt] = col;
        tkt_row[tckt] = stor;
    }
}

void movie_booking::seatin(int z, int wt) // 1st argument for the particular movie seat booking
// 2nd arg is for particular show time of particular movie
{
    int n, i;
    argg = z;
    sti = wt;
    // cout<<"THE ARGUMENT IS nest="<<arg<<endl;
    cout << "\n\n\t\t\t\t\t\t\tENTER THE NUMBER OF SEATS TO BE BOOKED" << endl;
    ifstream fin; // this part is for retrieving moive name from file
    fin.open("movie_test2.csv");
    cout << "\n\n\t\t\t\t\t\t\tBOOKED SEATS ARE MARKED WITH [x]\n\n";

    for (i = 0; i < argg - 1; i++)
    {
        getline(fin, name[i], '\n');
    }
    getline(fin, name[i], ',');

    cout << "\t\t\t\t\t\t\t MOVIE NAME=" << name[i] << endl;
    fin.close();
    cout << "\t\t\t\t\t\t\t ";
    cin >> n;
    tckt_prnt = n;
    for (tckt = 0; tckt < n; tckt++) // loop for booking the desired no. of tickets as input by user
    {
        (*this).book(argg, sti, 20);
        // cout << "LOOP IS RUNNING\n";
        system("clear");
        (*this).seatdisp(argg, sti);
    }
    cout << "\n\n\t\t\t\t\t\t\tPRESS ANY KEY TO CONTINUE\n";
    // CLEAR();
    system("clear");
}

void movie_booking::manager()
{
    char mov = 'c', in = 'c';
    (*this).show();
    while ((mov == 'c') || (mov == 'C')) // this loop is for entering the seats that are booked for different movies
    {
        cout << "\n\n\t\t\t\t\t\t\t ENTER THE SHOW NUMBER WHOSE SEATS U WANT TO ASSIGN FOR BOOKING\n";
        cout << "\t\t\t\t\t\t\t";
        cin >> sn;
        cout << "\n\n\t\t\t\t\t\t\t ENTER THE NUMBER CORRESPONDING TO THE TIME TO BOOK TICKET (LIKE 1 FOR THE FIRST SHOW, 2 FOR THE SECOND AND SO ON)\n";
        cout << "\t\t\t\t\t\t\t";
        cin >> sti;
        tkt_pnt = name[sn];

        while ((in == 'c') || (in == 'C'))
        {
            (*this).book(sn, sti, 100);
            system("clear");
            (*this).seatdisp(sn, sti);
            cout << "\n\n\t\t\t\t\t\t\tPRESS 'C' or 'c' IF U WANT TO CONTINUE ENTERING THE BOOKED SEATS\n";
            cout << "\t\t\t\t\t\t\t";
            cin >> in;
        }

        cout << "\n\n\t\t\t\t\t\t\tPRESS 'C' or 'c' IF U WANT TO CONTINUE ENTERING FOR OTHER MOVIES\n";
        cout << "\t\t\t\t\t\t\t";
        cin >> mov;
        in = 'c';
    }
    mv_str++;
}

void movie_booking::ticket_print()
{
    int i, a = 0, b = 0, d = 0;
    char c;
    string time; // time to store the movie timing

    for (i = 0; i < tckt_prnt; i++) // this loop is for printing the total cost of ticket
    {

        if (tkt_row[i] == 0 || tkt_row[i] == 1)
        {
            cost = cost + 500;
            a++;
        }
        else if (tkt_row[i] > 1 && tkt_row[i] < 7)
        {
            cost = cost + 200;
            b++;
        }
        else
        {
            cost = cost + 100;
            d++;
        }
    }
    cout << "\n\n\n\t\t\tCOST : " << endl;
    if (a != 0)
        cout << "\t\t\t       " << a << " * 500" << endl;
    if (b != 0)
        cout << "\t\t\t      +" << b << " * 200" << endl;
    if (c != 0)
        cout << "\t\t\t      +" << d << " * 100" << endl;
    cout << "GST 18% = " << cost * 0.18 << endl;
    cost = cost + cost * (0.18);
    cout << "\n\n\n\n\t\t\tTHE TOTAL TICKET COST = Rs " << cost << "/-" << endl;
    cout << "\n\nPRESS ANY KEY TO CONTINUE\n";
    //    CLEAR();
    system("clear");

    system("clear");
    ifstream fin; // this part is for retrieving moive name from file
    fin.open("movie_test2.csv");

    for (i = 0; i < argg - 1; i++)
    {
        getline(fin, name[i], '\n');
    }
    getline(fin, name[i], ',');

    for (int j = 0; j < sti; j++)
    {
        getline(fin, time, ',');
    }
    fin.close();
    (*this).Hall_name();
    cout << "\n\n\n\n\t\t\t________________________________________________________________________\n";
    cout << "\t\t\t|                                                                       |\n";
    cout << "\t\t\t|   Dear Customer,                                                      |\n";
    cout << "\t\t\t|                      Congratulation!! Your tickets has been booked.   |\n";
    cout << "\t\t\t|                                                                       |\n";
    cout << "\t\t\t|                  THE DETAILS:                                         |\n";
    cout << "\t\t\t|                            MOVIE HALL: " << hall_name << "                 \n";
    cout << "\t\t\t|                            MOVIE NAME: " << name[i] << "                                 \n";
    cout << "\t\t\t|                            SHOW STARTS:" << time << "                        \n";
    cout << "\t\t\t|                            NUMBER OF TICKETS BOOKED: " << tckt_prnt << "                |\n";
    cout << "\t\t\t|                 THE SEAT NUMBERS ARE: ";
    for (i = 0; i < tckt_prnt; i++)
    {
        c = tkt_row[i] + 65;
        cout << c << tkt_col[i] + 1; // PLS CHECK WHY I HV WRITTEN HERE +
        if (i < tckt - 1)
        {
            cout << ",";
        }
    }
    cout << "                        \n";
    cout << "\t\t\t|                                                     QR CODE           |\n";
    cout << "\t\t\t|                                                       ..++>>>         |\n";
    cout << "\t\t\t|                                                       ..__***         |\n";
    cout << "\t\t\t|                                                       &%^>>>>         |\n";
    cout << "\t\t\t|                                                       :::::::         |\n";
    cout << "\t\t\t|_______________________________________________________________________|\n";
}

void movie_booking::pass_protect() // to protect the password
{

    int ps = 0, star = 0; // to count the characters in password

    // star is to print the password in * format
    // pas[-1]=0;//intialised just like that "I GUESS ITS NIT REQUIRED"
    cout << "\n\n\t\t\t\t\t\t\tENTER THE MANAGER PASSWORD\n";
    cout << "\t\t\t\t\t\t\t";

    cin >> pass;
    ps = pass.length();
    system("clear");
    while (star < ps)
    {
        if (star == 0)
        {
            cout << "\n\n\t\t\t\t\t\t\tENTER THE MANAGER PASSWORD\n\n";

            cout << "\t\t\t\t\t\t\t\t";
        }

        cout << " * ";
        star++;
    }
}

void movie_booking::data_str()
{
    ofstream fout;
    fout.open("database1.csv", ios::app);
    string name1, name2, usr_id, usr_psd;
    /*format to be save is 1st name,title,user id,age,password*/
    fflush(stdin);

    cout << "\t\t\t\t\t\t\tENTER THE FIRST NAME\n";
    fflush(stdin);
    getline(cin, name1);
    cout << "\t\t\t\t\t\t\tENTER THE LAST NAME\n";
    fflush(stdin);
    getline(cin, name2);
    cout << "\t\t\t\t\t\t\tENTER THE USER ID\n";
    fflush(stdin);
    getline(cin, usr_id);
    cout << "\t\t\t\t\t\t\tENTER THE USER PASSWORD\n";
    fflush(stdin);
    getline(cin, usr_psd);
    fout << name1 << "," << name2 << "," << usr_id << "," << usr_psd << endl;

    fout.close();
    data_store = 1;
}

int movie_booking::password_check()
{
    cout << "\n\n\t\t\t\t\t\t\tENTER YOUR USER ID\n";
    fflush(stdin);
    cout << "\t\t\t\t\t\t\t";

    cin >> cust_id;
    ifstream myfile;
    myfile.open("database1.csv");
    while (!myfile.eof())
    {
        getline(myfile, user, ',');
        getline(myfile, user, ',');
        getline(myfile, user, ',');
        getline(myfile, pass, '\n');
        fflush(stdin);

        fflush(stdin);
        if (user == cust_id || pass == cust_id)
        {
            foundu++;
            print_once++;
            if (print_once == 1)
                cout << "\n\n\t\t\t\t\t\t\tUSER ID FOUND\n";
        }
    }

    if (foundu == 0)
    {
        cout << "\n\n\t\t\t\t\t\t\tUSER ID NOT FOUND\n";
        myfile.close();
    }
    else
    {
        myfile.close();
        cout << "\n\n\t\t\t\t\t\t\tENTER YOUR USER PASSWORD\n";
        fflush(stdin);
        cout << "\t\t\t\t\t\t\t";
        cin >> cust_pas;
        myfile.open("database1.csv");
        while (!myfile.eof())
        {
            getline(myfile, user, ',');
            getline(myfile, user, ',');
            getline(myfile, user, ',');
            getline(myfile, pass, '\n');
            fflush(stdin);

            fflush(stdin);
            if (pass == cust_pas)
            {
                foundp++;
                cout << "\n\n\t\t\t\t\t\t\tPASSWORD MATCHED\n";
            }
        }
    }

    if (foundp == 0)
        cout << "\n\n\t\t\t\t\t\t\tPASSWORD IS WRONG\n";

    myfile.close();
    return foundp;
}

int main()
{
    print_once = 0;
    movie_booking obj[4];
    while (1)
    {
        cout << "\n\n\t\t\t\t\t\t\t PRESS 1 TO BOOK TICKET IN INOX VARANASI";
        cout << "\n\n\t\t\t\t\t\t\t PRESS 2 TO BOOK TICKET IN CINEPOLIS VARANASI";
        cout << "\n\n\t\t\t\t\t\t\t PRESS 3 TO BOOK TICKET IN KESHARI TALKIES ";
        cout << "\n\n\t\t\t\t\t\t\t PRESS 4 TO BOOK TICKET IN MAHARAJA";
        cout << "\n\n\t\t\t\t\t\t\t TO EXIT PROGRAM PRESS 9 ";
        cout << "\n\n\t\t\t\t\t\t\t ";
        cin >> obn;
        switch (obn)
        {
        case 1:
            cout << "\t\t\t\t\t\t\t";
            cout << "INOX VARANASI IS SELECTED\n";
            obj[0].first();
            break;
        case 2:
            cout << "\t\t\t\t\t\t\t";
            cout << "CINEPOLIS VARANASI IS SELECTED\n";
            obj[1].first();
            break;
        case 3:
            cout << "\t\t\t\t\t\t\t";
            cout << "KESHARI TALKIES VARANASI IS SELECTED\n";
            obj[2].first();
            break;
        case 4:
            cout << "\t\t\t\t\t\t\t";
            cout << "MAHARAJA VARANASI IS SELECTED\n";
            obj[3].first();
            break;
        case 9:
            goto bye;
            break;
        default:
            cout << "enter a valid number\n";
            goto bye;
            break;
        }
    }

bye:
    cout << "its working WITH file handling \n";
    system("clear");
    cout << "\n\n\n\n\t\t\t\t\t\t\t THANK YOU FOR USING OUR APPLICATION!!!!";
    return 0;
}