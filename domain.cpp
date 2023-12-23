#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <cassert>

using namespace std;

class Domain {
public:
    Domain(const string& domain) : domain_(domain) {
        reverse(domain_.begin(), domain_.end());
        domain_.push_back('.');
    }

    bool operator==(const Domain& other) const {
        return lexicographical_compare(domain_.begin(), domain_.end(), other.domain_.begin(), other.domain_.end());
    }

    bool IsSubdomain(const Domain& other) const {
        return equal(other.domain_.begin(), other.domain_.end(), domain_.begin());
    }

    string GetDomain() const {
        return domain_;
    }

private:

    string domain_;
};

class DomainChecker {
public:

    template <typename It>
    DomainChecker(const It begin, const It end) : domains(begin, end) {
        sort(domains.begin(), domains.end(), [](const Domain& left, const Domain& right){
            return left == right;
        });
        auto uniq_it = unique(domains.begin(), domains.end(),[](const Domain& left, const Domain& right){
            return right.IsSubdomain(left);
        });

        domains.erase(uniq_it, domains.end());
    }

    bool IsForbidden(const Domain& domain_check) {
        if(domains.empty()) {
            return false;
        }
        auto domain_it = upper_bound(domains.begin(), domains.end(), domain_check, [](const Domain& left, const Domain& right) {
            return left.GetDomain() < right.GetDomain();
        });

        if(domains.begin() == domain_it) {
            return domain_check.IsSubdomain(domains[domain_it - domains.begin()]);
        }
        else {
            return domain_check.IsSubdomain(domains[domain_it - domains.begin() - 1]);
        }
    }

    size_t GetSize() {
        return domains.size();
    }

private:
    vector<Domain> domains;
};


// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа
const vector<Domain> ReadDomains(istream& in, size_t num) {
    vector<Domain> domains;
    string str;

    for(size_t i = 0; i < num; ++i) {
        getline(in, str);
        domains.push_back(str);
    }

    return domains;
}



template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

void TestDomain() {
    string name = "svg.com";

    Domain domain("svg.com");
    assert(!(domain == Domain(name)));

    assert(domain.GetDomain() == "moc.gvs.");


    assert(domain.IsSubdomain(Domain{"com"}) == true);

    Domain domain1("one.svg.com");
    assert(domain1.IsSubdomain(domain) == true);
    assert(domain.IsSubdomain(domain1) == false);
    assert(domain1.IsSubdomain(Domain{"svg.ru"}) == false);
}

void TestForbidden() {
    vector<Domain> vec_comain = {Domain{"svg.com"}, Domain{"ya.ru"}, Domain{"go.te"}, Domain{"one.svg.com"}};
    DomainChecker check(vec_comain.begin(), vec_comain.end());

    assert(check.GetSize() == 3);
    assert(check.IsForbidden(Domain{"ss.svg.com"}) == true);
    assert(check.IsForbidden(Domain{"ss.ya.ru"}) == true);
    assert(check.IsForbidden(Domain{"ss.go.te"}) == true);

}

void TestRead() {
    string str= "svg.com\nya.ru\ngo.te\none.svg.com";

    stringstream stream;
    stream << str;
    vector<Domain> domains = ReadDomains(stream, 4);

    assert(domains[0].GetDomain() == "moc.gvs.");
    assert(domains[1].GetDomain() == "ur.ay.");
    assert(domains[2].GetDomain() == "et.og.");
    assert(domains[3].GetDomain() == "moc.gvs.eno.");


}

void Tests() {

    TestDomain();
    TestForbidden();
    TestRead();

}

int main() {
    Tests();
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}
