# pragma once

#include <string>

namespace chio {
    auto notSpace = std::not1(std::ptr_fun<int, int>(std::isspace));

    std::string ltrim(std::string s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
        return s;
    }

    std::string rtrim(std::string s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
        return s;
    }

    std::string trim(std::string const & s) {
        return ltrim(rtrim(s));
    }

    void checkIO(std::function<void()> const & fun, std::string const & input, std::string const & output) {
        std::istringstream iss;
        std::streambuf* p_cin_streambuf = std::cin.rdbuf();
        std::cin.rdbuf(iss.rdbuf());

        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        iss.str(input);

        fun();

        std::cout.rdbuf(p_cout_streambuf); // restore
        std::cin.rdbuf(p_cin_streambuf); // restore

        // test your oss content...
        assert(oss && trim(oss.str()) == output);
        std::cout << oss.str();
    }
}