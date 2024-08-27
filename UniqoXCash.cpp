// latest one

#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

class member
{
private:
    string mob;
    string name;
    int pin;
    double cash = 120;
    vector<string> history;

public:
    member() {};
    void setdata(string m, string n, int p)
    {
        mob = m;
        name = n;
        pin = p;
    }
    void setcash(double c = 0.0, string s = "")
    {
        if (s == "main")
        {
            this->cash = c;
        }
        else if (s == "in")
        {
            this->cash += c;
        }
        else if (s == "send")
        {
            this->cash -= c;
        }
        else
        {
            this->cash -= (c + 0.0105 * c);
        }
    }

    double getcash()
    {
        return this->cash;
    }
    void setname(string s)
    {
        this->name = s;
    }
    string getname()
    {
        return name;
    }
    void setpin(int s)
    {
        this->pin = s;
    }
    int getPin()
    {
        return pin;
    }
    string getMobile()
    {
        return mob;
    }
};

vector<member *> registeredMembers;
vector<string> uddokta = {"01712345678", "01812345678", "01912345678", "01612345678", "01512345678", "01312345678", "01412345678", "01798765432", "01898765432", "01998765432"};
int line, destline;

void readRegisteredMembersFromFile()
{
    ifstream file("effective_member01.txt");

    if (file.is_open())
    {
        registeredMembers.clear();

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string mobile, name;
            int pin;
            double cash;

            ss >> mobile >> name >> pin >> cash;

            member *newMember = new member();
            newMember->setdata(mobile, name, pin);
            newMember->setcash(cash, "main");
            registeredMembers.push_back(newMember);
        }

        file.close();
    }
    else
    {
        cout << "Error: Unable to open the file for reading." << endl;
    }
}

void update_data(int lineNo, const string &column, const string &newValue)
{
    fstream inFile("effective_member01.txt");
    ofstream outFile("temp.txt");

    string line;
    int currentLine = 1;

    while (getline(inFile, line))
    {
        if (currentLine == lineNo)
        {
            stringstream ss(line); // Split the line into components
            vector<string> parts;
            string part;

            while (ss >> part)
            {
                parts.push_back(part);
            }

            if (column == "name")
            {
                parts[1] = newValue;
            }
            else if (column == "pin")
            {
                parts[2] = newValue;
            }
            else if (column == "balance")
            {
                parts[3] = newValue;
            }

            line = parts[0] + " " + parts[1] + " " + parts[2] + " " + parts[3];
        }

        outFile << line << endl;
        currentLine++;
    }

    inFile.close();
    outFile.close();

    remove("effective_member01.txt");
    rename("temp.txt", "effective_member01.txt");
    return;
}

void eraseLine(int lineNo)
{
    ifstream inFile("effective_member01.txt");
    ofstream outFile("temp.txt");

    string line;
    int currentLine = 1;

    while (getline(inFile, line))
    {
        // Skip writing the line if it matches the line number to be erased
        if (currentLine != lineNo)
        {
            outFile << line << endl;
        }
        currentLine++;
    }

    inFile.close();
    outFile.close();

    // Replace the original file with the updated file
    remove("effective_member01.txt");
    rename("temp.txt", "effective_member01.txt");
}

string date_time()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm *localTime = std::localtime(&currentTime);
    std::stringstream dateTimeStream;
    dateTimeStream << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return dateTimeStream.str();
}

string generateTrxID(int length = 12)
{
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string trxID;
    srand(time(0)); // Seed the random number generator

    for (int i = 0; i < length; ++i)
    {
        trxID += chars[rand() % chars.size()];
    }

    return trxID;
}

void history(string file, string trxid, string about, string amount)
{
    string filename = file + ".txt";
    ofstream outFile(filename, ios::app);

    if (outFile.is_open())
    {
        outFile << date_time() + " " + trxid + " " + about + " " + amount << endl;
        outFile.close();
    }
    else
    {
        cout << "Unable to open the file." << endl;
    }
    return;
}

void history_show(string file)
{
    string filename = file + ".txt";
    ifstream inFile(filename);

    if (inFile.is_open())
    {
        string line;
        while (getline(inFile, line))
        {
            cout << line << endl; // Print each line as it is
        }
        inFile.close();
    }
    else
    {
        cout << "Unable to open the file." << endl;
    }
}

int main_menu()
{
    int x;
    cout << "--WELCOME  TO  UniqoXCash--" << endl;
    cout << "   A UniqoXTech Product" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
    cout << "   Enter Your Opiton :";
    cin >> x;
    try
    {
        if (x < 1 && x > 3)
        {
            throw x;
        }
        else
        {
            return x;
        }
    }
    catch (int x)
    {
        cout << "INVALID INPUT" << endl;
        main_menu();
    }
    return 0;
}

int pin_taking()
{
    int pin, apin, otp, i, j = 0;
    char pIn[6], re[6];
    cout << "Enter PIN(5 digit): ";
    for (i = 0; i < 5;)
    {
        char ch = _getch();

        if (isdigit(ch) && i < 5)
        {
            cout << '*';
            pIn[i] = ch;
            i++;
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            cout << "\b \b";
        }
        else if (ch == 13)
        {
            break;
        }
    }
    pIn[i] = '\0';
    pin = atoi(pIn);
    char see;
    cout << "\nDo you want to view your PIN? [y/N]: ";
    cin >> see;
    if (see == 'y')
    {
        cout << "Your Pin is : " << pin << endl;
    }

piin:
    cout << "Reconfirm PIN: ";
    for (i = 0; i < 5;)
    {
        char ch = _getch();

        if (isdigit(ch) && i < 5)
        {
            cout << '*';
            re[i] = ch;
            i++;
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            cout << "\b \b";
        }
        else if (ch == 13)
        {
            break;
        }
    }
    re[i] = '\0';
    apin = atoi(re);
    cout << "\nDo you want to view? [y/N]: ";
    char seee;
    cin >> seee;
    if (seee == 'y')
    {
        cout << "Comfirmed Pin is : " << apin << endl;
    }
    if ((pin != apin))
    {
        cout << "PIN Mismatch" << endl;
        j++;
        if (j < 3)
        {
            goto piin;
        }
        else
        {
            cout << "Limit Exceeded" << endl;
            return 0;
        }
    }
    else
    {
        return pin;
    }
}

bool otp_related()
{
    int otp, count = 0;
    const int otpExpirySeconds = 15;

    srand(static_cast<unsigned>(time(nullptr)));
    int x = rand() % 9000 + 1000; // random number generator
    chrono::time_point<chrono::system_clock> startTime = chrono::system_clock::now();
    cout << "UniqoXCash OTP: " << x << endl;

    while (true)
    {
        cout << "Enter OTP: ";
        cin >> otp;
        chrono::time_point<chrono::system_clock> currentTime = chrono::system_clock::now();
        chrono::duration<double> elapsedSeconds = currentTime - startTime;

        if (count >= 3)
        {
            return false;
        }

        if (otp == x && elapsedSeconds.count() <= otpExpirySeconds && count < 3)
        {
            return true;
        }
        else
        {
            if (elapsedSeconds.count() > otpExpirySeconds)
            {
                cout << "OTP EXPIRED" << endl;
                count++;
                cout << "Do you want to get new OTP(y/N)? : ";
                char g;
                cin >> g;
                if (g == 'y' || g == 'Y')
                {
                    x = rand() % 9000 + 1000;
                    cout << "New UniqoXCash OTP: " << x << endl;
                    startTime = chrono::system_clock::now();
                }
                else
                {
                    break;
                }
            }
            else
            {
                cout << "NOT MATCHED" << endl;
                count++;
            }
        }
    }
    return false;
}

void registeer()
{
    string mob, name;
    int pin = 0;
    while (1)
    {
        cout << "Enter Mobile No. (11 digit) : ";
        cin >> mob;
        if (mob.length() != 11)
        {
            cout << "Invalid mobile no." << endl;
        }
        else
        {
            break;
        }
    }

    for (auto m : registeredMembers)
    {
        if (m->getMobile() == mob)
        {
            cout << "Already Registered" << endl;
            return;
        }
    }

    cout << "Enter Name: ";
    cin >> name;

    while (pin == 0)
    {
        pin = pin_taking();
    }

    bool otp = otp_related();

    if (otp)
    {
        member *m = new member();
        m->setdata(mob, name, pin);
        registeredMembers.push_back(m);
        cout << "Registration is Successful" << endl
             << "You have got 120 BDT as registration bonus." << endl;

        ofstream file("effective_member01.txt", ios::app); // Save member details to a file
        if (file.is_open())
        {
            file << mob << " " << name << " " << pin << " " << 120.000000 << "\n";
            file.close();

            string filename = mob + ".txt";
            ofstream outfile(filename);
            if (!outfile)
            {
                cerr << "Error creating file!" << std::endl;
                return;
            }
            outfile << "WELCOME to UniqoXTransaction " << date_time() << endl
                    << endl;

            outfile.close();
        }
        else
        {
            cout << "Error: Unable to open the file for writing." << endl;
        }
    }
    else
    {
        cout << "Regestration Failed" << endl;
        return;
    }
    return;
}

void updateMe(member &m)
{
    cout << "Old Name: " << m.getname() << endl;
    cout << "Do you want to change your name? (Y/N): ";
    char cch;
    cin >> cch;
    string newName;
    if (cch == 'Y' || cch == 'y')
    {
        cout << "New name: ";
        cin >> newName;
    }
    else
    {
        newName = m.getname();
    }
    cout << "Do you want to change your PIN? (Y/N): ";
    char choice;
    cin >> choice;
    int npin;
    if (choice == 'Y' || choice == 'y')
    {
        cout << "Current PIN window" << endl;
        int cpin = pin_taking();
        if (m.getPin() == cpin)
        {
            cout << "New PIN window" << endl;
            npin = pin_taking();
        }
        else
        {
            cout << "Worng input of current PIN." << endl;
            return;
        }
    }
    bool otp = otp_related();
    if (otp)
    {
        // cout << npin << " " << newName << endl;
        m.setpin(npin);
        m.setname(newName);

        update_data(line, "name", newName);
        update_data(line, "pin", to_string(npin));

        cout << "Update is successfull" << endl;
        // int lm = m.getPin();
        // cout << lm << endl;
        return;
    }
    else
    {
        cout << "Unsuccessfull attempt" << endl;
    }
}

void removeMe(member &m)
{
    bool otp;
    string mob;
    while (1)
    {
        cout << "Enter Mobile No. (11 digit) : ";
        cin >> mob;
        if (mob.length() != 11)
        {
            cout << "Invalid mobile no." << endl;
        }
        else
        {
            break;
        }
    }

    otp = otp_related();

    if (otp)
    {
        for (auto it = registeredMembers.begin(); it != registeredMembers.end(); ++it)
        {
            member *user = *it;
            if (user->getMobile() == mob)
            {
                // User found, remove from the vector
                delete user; // Deallocate memory (assuming you allocated memory for the members)
                registeredMembers.erase(it);
                eraseLine(line);
                string feedb;
                cout << "Give your Feedback: ";
                cin.ignore();
                getline(cin, feedb);
                ofstream outFile("FeedBack.txt", ios::app);

                if (outFile.is_open())
                {
                    outFile << mob + " " + feedb << endl;
                    outFile.close();
                }
                else
                {
                    cout << "Unable to open the file." << endl;
                }
                cout << "Your registration has been removed successfully." << endl;
                return;
            }
        }
    }
    return;
}

void sendmoney(member &m)
{
    member *p = nullptr;
    while (1)
    {
        cout << "Enter Receiver No: ";
        string destNo;
        cin >> destNo;
        if (destNo != m.getMobile())
        {
            bool flag = false;
            destline = 0;
            for (member *k : registeredMembers)
            {
                destline++;
                string xion = k->getMobile();
                if (xion == destNo)
                {
                    p = &(*k);
                    flag = true;
                    // cout << p->getMobile() << p->getname() << endl;
                    break;
                }
            }
            if (flag == false)
            {
                cout << "Invalid Destination. Try again." << endl;
                return;
            }
            else
            {
                break;
            }
        }
        else
        {
            cout << "You cannot send money to yourself." << endl;
        }
    }

    while (1)
    {
        cout << "Enter the amount to send: ";
        double amount;
        cin >> amount;
        if (amount < m.getcash())
        {
            int pin = pin_taking();
            if (m.getPin() == pin)
            {
                bool otp = otp_related();
                if (otp)
                {
                    m.setcash(amount, "send");
                    p->setcash(amount, "in");

                    update_data(line, "balance", to_string(m.getcash()));
                    update_data(destline, "balance", to_string(p->getcash()));

                    history(m.getMobile(), generateTrxID(), "Send Money", to_string(amount));
                    history(p->getMobile(), generateTrxID(), "Received Money", to_string(amount));

                    // for (member *k : registeredMembers)
                    // {
                    //     double ulla = k->getcash ();
                    //     cout << ulla << endl;
                    // }
                    cout << "Send money successfull" << endl;
                    // (*p).setcash(amount,"in");
                    // string strrr = p->getMobile();
                    // cout << strrr << endl;
                    // cout << "yes" << endl;
                    return;
                }
            }
        }
        else
        {
            cout << "Insufficient balance" << endl;
        }
    }
    return;
}

void cashin(member &m)
{
    cout << "Enter Amount: ";
    double x;
    cin >> x;
    bool otp = otp_related();
    if (otp)
    {
        cout << "Cash-in: " << x << endl;
        cout << "Are you sure? (y/N): ";
        char c;
        cin >> c;
        if (c == 'y')
        {
            m.setcash(x, "in");
            history(m.getMobile(), generateTrxID(), "Cash-in", to_string(x));
            update_data(line, "balance", to_string(m.getcash()));
        }
    }
    return;
}

void cashout(member &m)
{
    string udd, towards;
    while (1)
    {
        cout << "Uddokta mobile: ";
        cin >> towards;
        if (towards != m.getMobile())
        {
            bool flag = false;
            for (auto i : uddokta)
            {
                if (i == towards)
                {
                    udd = towards;
                    flag = true;
                    break;
                }
            }
            if (flag == false)
            {
                cout << "Invalid Number." << endl;
                return;
            }
            else
            {
                break;
            }
        }
        else
        {
            cout << "It's you." << endl;
        }
    }
    while (1)
    {
        cout << "Enter the amount : ";
        double amount;
        cin >> amount;
        if (amount < m.getcash())
        {
            int pin = pin_taking();
            if (m.getPin() == pin)
            {
                bool otp = otp_related();
                if (otp)
                {
                    m.setcash(amount, "out");

                    update_data(line, "balance", to_string(m.getcash()));

                    history(m.getMobile(), generateTrxID(), "Cash-out", to_string(amount));

                    cout << "Cash out successfull" << endl;

                    return;
                }
            }
        }
        else
        {
            cout << "Insufficient balance" << endl;
        }
    }

    return;
}

void checkbalance(member &m)
{
    cout << "Your Balance : " << m.getcash() << endl;
    return;
}

void paybill(member &m)
{
    int y;
    while (1)
    {
        cout << "Enter Bill Type (Gas/Electricity/water/internet-1/2/3/4) : ";
        int c;
        cin >> c;
        if (c = 1)
        {
            y = 1080;
            break;
        }
        else if (c = 3)
        {
            y = 700;
            break;
        }
        else if (c = 4)
        {
            y = 1000;
            break;
        }
        else if (c = 2)
        {
            y = rand() % 1301 + 700;
            break;
        }
        else
        {
            cout << "Invalid Input" << endl;
        }
    }
    cout << "Bill amount: " << y << endl;
    if (y < m.getcash())
    {
        cout << "Do you want to pay? (y/N): ";
        char yn;
        cin >> yn;
        if ((yn == 'Y') || (yn == 'y'))
        {
            bool otp = otp_related();
            if (otp)
            {
                m.setcash(y, "send");
                update_data(line, "balance", to_string(m.getcash()));
                history(m.getMobile(), generateTrxID(), "Bill", to_string(y));
                cout << "Bill Payment is Successfull" << endl;
                return;
            }
        }
    }
    else
    {
        cout << "Insufficient cash" << endl;
    }

    return;
}

void logout()
{

    cout << "Logged Out Successfully" << endl;
    return;
}

void menu(member &m)
{
    int x;
    do
    {
        cout << "UniqoXCash Menu" << endl;
        cout << "1.Update Me" << endl;
        cout << "2.Remove Me" << endl;
        cout << "3.Send Money" << endl;
        cout << "4.Cash-in" << endl;
        cout << "5.Cash-out" << endl;
        cout << "6.Pay Bill" << endl;
        cout << "7.Check Balance" << endl;
        cout << "8.History" << endl;
        cout << "9.Logout" << endl;
        cout << "  Enter Your Option(1-9): ";
        cin >> x;
        switch (x)
        {
        case 1:
            updateMe(m);
            break;
        case 2:
            removeMe(m);
            return;
            break;
        case 3:
            sendmoney(m);
            break;
        case 4:
            cashin(m);
            break;
        case 5:
            cashout(m);
            break;
        case 6:
            paybill(m);
            break;
        case 7:
            checkbalance(m);
            break;
        case 8:
            history_show(m.getMobile());
            break;
        case 9:
            logout();
            return;
        default:
            cout << "Invalid input" << endl;
            break;
        }
        cout << "Press any key to go to the menu..." << endl;
        cin.ignore();
        cin.get();
        system("cls");
    } while (x != 9);
    return;
}

void login()
{
    string mob;
    int pin;
    while (1)
    {
        cout << "Enter Mobile No. (11 digit) : ";
        cin >> mob;
        if (mob.length() != 11)
        {
            cout << "Invalid mobile no." << endl;
        }
        else
        {
            break;
        }
    }
    member *n = nullptr;
    int marker = 0;
    line = 0;
    for (auto m : registeredMembers)
    {
        line++;
        if (m->getMobile() == mob)
        {
            n = m;
            marker = 1;
            break;
        }
    }
    if (marker == 0)
    {
        cout << "Your are not registered." << endl;
        line = -1;
        return;
    }
    else
    {
        pin = pin_taking();
    }
    if (n->getPin() == pin)
    {
        cout << "Login successful." << endl;
        menu(*n);
    }
    else
    {
        cout << "Login failed. Mobile number and PIN do not match." << endl;
    }
    return;
}

int main()
{
    int x;
    readRegisteredMembersFromFile();
    do
    {
        x = main_menu();

        switch (x)
        {
        case 1:
            login();
            break;
        case 2:
            registeer();
            break;
        case 3:
            exit(1);
        default:
            cout << "Invalid option! Please try again." << endl;
            break;
        }
        cout << "Press any key to go to the main menu..." << endl;
        cin.ignore();
        cin.get();
        system("cls");
    } while (x != 3);
    return 0;
}

// line number 264 --- adding return false;
// logout er age file clear kore then file e write korte hobe
