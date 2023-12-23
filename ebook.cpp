#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>



class ReadCheerStat {
public:

    ReadCheerStat() : users_read_to_page(max_users, 0), pages_reads(max_pages, 0) {}

    void Read(int user_id, int page_number);
    double Cheers(int user_id);
    void Reader(std::string& str);

private:
    const int max_users = 1e5+1 + 1;
    const int max_pages = 1000;
    std::vector<int> users_read_to_page;
    std::vector<int> pages_reads; //index - number page, int - count users

    int count_users = 0;
};


void ReadCheerStat::Read(int user_id, int page_number) {
    if(users_read_to_page[user_id] == 0) {
        users_read_to_page[user_id] = page_number;
        ++count_users;
        for(int i = 0; i < page_number; ++i) {
            ++pages_reads[i];
        }
    }
    else {
        for(int i = users_read_to_page[user_id]; i < page_number; ++i) {
            ++pages_reads[i];
        }
        users_read_to_page[user_id] = page_number;
    }


}

double ReadCheerStat::Cheers(int user_id) {

    if(users_read_to_page[user_id] == 0) {
        return 0.0;
    }
    else if(count_users == 1) {
        return 1.0;
    }
    else if(count_users == pages_reads[users_read_to_page[user_id]-1]) {
        return 0.0;
    }
    else {

        return (count_users - pages_reads[users_read_to_page[user_id]-1]) / ((double)count_users - 1.0);
    }

}


void Requests(std::istream& in, std::ostream& out, ReadCheerStat& stat) {
    int count = 0;
    in >> count;


    for(int i = 0; i <= count; ++i) {

        std::string str;
        std::getline(in, str);
        auto it_space = str.find_first_of(' ');

        if(str.substr(0, it_space) == "READ") {
            int user_id = std::stoi(str.substr(it_space, str.find_last_of(' ')));
            int page_number = std::stoi(str.substr(str.find_last_of(' ')));

            stat.Read(user_id, page_number);
        }
        else if(str.substr(0, it_space) == "CHEER") {
            int user_id = std::stoi(str.substr(it_space));

            out << stat.Cheers(user_id) << std::endl;
        }
    }
}



int main() {

ReadCheerStat stat;

Requests(std::cin, std::cout, stat);

return 0;
}
