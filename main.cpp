#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

size_t ipStringToInteger(const std::string &str, char d)
{
    size_t r = 0;

    std::string::size_type start = str.find_last_of(d);
    std::string::size_type stop = str.size();
    int i = 0;
    while(start != std::string::npos)
    {
        r |= std::atoi(str.substr(start+1, stop - start).c_str()) << 8*i;

        ++i;
        stop = start - 1;
        start = str.find_last_of(d, stop);
    }

    size_t tmp = std::atoi(str.substr(start+1, stop - start).c_str()) << 8*i;
    r |= std::atoi(str.substr(start+1, stop - start).c_str()) << 8*i;

    return r;
}

void print(std::vector<size_t> ip_pool){


    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        std::cout << ((*ip>>24)&0xFF) << '.' << ((*ip>>16)&0xFF) << '.' << ((*ip>>8)&0xFF) << '.' << (*ip&0xFF);

        std::cout << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<size_t> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::string v = line.substr(0, line.find_first_of('\t'));
            ip_pool.push_back(ipStringToInteger(v, '.'));

            print(ip_pool);
        }

        // reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<int>());

        print(ip_pool);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
