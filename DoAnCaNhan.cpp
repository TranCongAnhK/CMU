#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// Person class
class Person {
protected:
    string name;
    int age;
    string gender;
public:
    virtual void inputBasicInfo() {
        cout << "[*] Nhap ten: ";
        getline(cin, name);

        cout << "[*] Nhap tuoi: ";
        string temp;
        getline(cin, temp);
        age = atoi(temp.c_str());

        cout << "[*] Nhap gioi tinh: ";
        getline(cin, gender);
    }

    virtual void displayBasicInfo() const {
        cout << "[*] Ten: " << name << endl;
        cout << "[*] Tuoi: " << age << endl;
        cout << "[*] Gioi tinh: " << gender << endl;
    }
};

// thêm tội danh, mức độ nguy hiểm, tiền thưởng.
class Criminal : public Person {
protected:
    string crime;
    int dangerLevel;
    float bounty;
public:
    virtual void inputCriminalInfo() {
        inputBasicInfo();

        cout << "[*] Nhap toi danh: ";
        getline(cin, crime);

        cout << "[*] Nhap muc do nguy hiem (1-10): ";
        string temp;
        getline(cin, temp);
        dangerLevel = atoi(temp.c_str());

        cout << "[*] Nhap muc truy na: ";
        getline(cin, temp);
        bounty = (float)atof(temp.c_str());
    }

    virtual void displayCriminalInfo() const {
        displayBasicInfo();
        cout << "[*] Toi danh: " << crime << endl;
        cout << "[*] Muc do nguy hiem: " << dangerLevel << endl;
        cout << "[*] Tien thuong: $" << bounty << endl;
    }
};

// hêm thông tin vị trí và thời gian cuối cùng bị phát hiện.
class WantedCriminal : public Criminal {
protected:
    string lastSeenLocation;
    string lastSeenTime;
public:
    virtual void inputWantedInfo() {
        inputCriminalInfo();

        cout << "[*] Nhap vi tri nhin thay lan cuoi: ";
        getline(cin, lastSeenLocation);

        cout << "[*] Nhap thoi gian nhin thay lan cuoi: ";
        getline(cin, lastSeenTime);
    }

    virtual void displayWantedInfo() const {
        displayCriminalInfo();
        cout << "[*] Vi tri cuoi cung: " << lastSeenLocation << endl;
        cout << "[*] Thoi gian cuoi cung: " << lastSeenTime << endl;
    }
};

// 
class HighRiskCriminal : public WantedCriminal {
private:
    string identification;
    bool isArmed;
    string criminalID;
public:
    bool inputHighRiskInfo() {
        inputWantedInfo();

        cout << "[*] Nhap dau hieu nhan dang: ";
        getline(cin, identification);

        string temp;
        cout << "[*] Co vu khi khong? (1: Co, 0: Khong): ";
        getline(cin, temp);
        isArmed = (temp == "1");

        cout << "[*] Nhap ma toi pham: ";
        getline(cin, criminalID);

        return true;
    }

    void displayHighRiskInfo() const {
        displayWantedInfo();
        cout << "[*] Dau hieu nhan dang: " << identification << endl;
        cout << "[*] Co vu khi: " << (isArmed ? "Co" : "Khong") << endl;
        cout << "[*] Ma toi pham: " << criminalID << endl;
    }

    string getCriminalID() const { return criminalID; }

    void serialize(ofstream &out) const {
        out << criminalID << endl;
        out << name << endl;
        out << age << endl;
        out << gender << endl;
        out << crime << endl;
        out << dangerLevel << endl;
        out << bounty << endl;
        out << lastSeenLocation << endl;
        out << lastSeenTime << endl;
        out << identification << endl;
        out << isArmed << endl;
        out << "====\n";
    }

    void deserialize(ifstream &in) {
        string temp;
        getline(in, criminalID);
        getline(in, name);
        getline(in, temp); age = atoi(temp.c_str());
        getline(in, gender);
        getline(in, crime);
        getline(in, temp); dangerLevel = atoi(temp.c_str());
        getline(in, temp); bounty = (float)atof(temp.c_str());
        getline(in, lastSeenLocation);
        getline(in, lastSeenTime);
        getline(in, identification);
        getline(in, temp); isArmed = (temp == "1");
    }
};

// quản lý danh sách tội phạm, thao tác CRUD.
class CrimeDatabase {
private:
    vector<HighRiskCriminal> criminals;
public:
    void addCriminal(const HighRiskCriminal &criminal) {
        criminals.push_back(criminal);
    }

    void removeCriminal(const string &criminalID) {
        for (vector<HighRiskCriminal>::iterator it = criminals.begin(); it != criminals.end(); ++it) {
            if (it->getCriminalID() == criminalID) {
                criminals.erase(it);
                cout << "\n[✓] Da xoa toi pham.\n";
                return;
            }
        }
        cout << "\n Khong tim thay toi pham.\n";
    }

    HighRiskCriminal* searchCriminal(const string &criminalID) {
        for (size_t i = 0; i < criminals.size(); ++i) {
            if (criminals[i].getCriminalID() == criminalID)
                return &criminals[i];
        }
        return 0;
    }

    void generateReport() const {
        cout << "\n==== BAO CAO TOI PHAM ====" << endl;
        for (size_t i = 0; i < criminals.size(); ++i) {
            criminals[i].displayHighRiskInfo();
            cout << "---------------------------\n";
        }
    }

    void saveToFile(const string &fileName) {
        ofstream out(fileName.c_str());
        for (size_t i = 0; i < criminals.size(); ++i) {
            criminals[i].serialize(out);
        }
        out.close();
        cout << "\n[✓] Da luu vao file " << fileName << endl;
    }

    void loadFromFile(const string &fileName) {
        ifstream in(fileName.c_str());
        if (!in) {
            cout << " Khong mo duoc file " << fileName << endl;
            return;
        }

        criminals.clear();
        string line;
        while (!in.eof()) {
            HighRiskCriminal temp;
            temp.deserialize(in);
            getline(in, line); // Đọc dòng ====
            if (temp.getCriminalID() != "") {
                criminals.push_back(temp);
            }
        }

        in.close();
        cout << " Da tai danh sach toi pham tu file.\n";
    }
};

// xử lý đăng nhập
class AuthSystem {
private:
    string username;
    string password;
    bool loggedIn;
public:
    AuthSystem() : loggedIn(false) {}

    bool login() {
        string u, p;
        cout << "[*] Nhap ten dang nhap: "; getline(cin, u);
        cout << "[*] Nhap mat khau: "; getline(cin, p);
        if (u == "admin" && p == "1234") {
            loggedIn = true;
            cout << "[✓] Dang nhap thanh cong.\n";
            return true;
        }
        cout << " Sai thong tin dang nhap.\n";
        return false;
    }

    void logout() {
        loggedIn = false;
        cout << "[✓] Da dang xuat.\n";
    }

    bool isLoggedIn() const { return loggedIn; }
};

// giao diện chính của chương trình
class App {
private:
    CrimeDatabase crimeDatabase;
    AuthSystem authSystem;
public:
    void run() {
        crimeDatabase.loadFromFile("toipham.txt");

        if (!authSystem.login()) return;

        int choice;
        do {
            system("cls");
            cout << "\n=============================================" << endl;
            cout << "      == HE THONG QUAN LY TOI PHAM ==\n";
            cout << "=============================================" << endl;
            cout << " [1] ==> Them toi pham" << endl;
            cout << " [2] ==> Xoa toi pham" << endl;
            cout << " [3] ==> Tim toi pham" << endl;
            cout << " [4] ==> Xuat bao cao" << endl;
            cout << " [5] ==> Luu vao tep" << endl;
            cout << " [6] ==> Dang xuat" << endl;
            cout << "---------------------------------------------" << endl;
            cout << " ==> Chon chuc nang (1-6): ";

            cin >> choice; cin.ignore();
            system("cls");

            switch (choice) {
                case 1: {
                    cout << "==== Nhap thong tin toi pham ====" << endl;
                    HighRiskCriminal c;
                    c.inputHighRiskInfo();
                    crimeDatabase.addCriminal(c);
                    cout << "\n[✓] Da them toi pham thanh cong.\n";
                    break;
                }
                case 2: {
                    string id;
                    cout << "[*] Nhap ma toi pham de xoa: ";
                    getline(cin, id);
                    crimeDatabase.removeCriminal(id);
                    break;
                }
                case 3: {
                    crimeDatabase.loadFromFile("toipham.txt");
                    string id;
                    cout << "[*] Nhap ma toi pham de tim: ";
                    getline(cin, id);
                    HighRiskCriminal* c = crimeDatabase.searchCriminal(id);
                    if (c) c->displayHighRiskInfo();
                    else cout << "[!] Khong tim thay toi pham.\n";
                    break;
                }
                case 4:
                    crimeDatabase.generateReport();
                    break;
                case 5:
                    crimeDatabase.saveToFile("toipham.txt");
                    break;
                case 6:
                    authSystem.logout();
                    return;
                default:
                    cout << "[!] Lua chon khong hop le.\n";
            }
            cout << "\nNhan Enter de tiep tuc...";
            cin.get();
        } while (true);
    }
};

int main() {
    App app;
    app.run();
    return 0;
}
