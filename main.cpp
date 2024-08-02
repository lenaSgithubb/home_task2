#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

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

    r |= std::atoi(str.substr(start+1, stop - start).c_str()) << 8*i;

    return r;
}

void print(std::vector<uint32_t> ip_pool){

    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        std::cout << ((*ip>>24)&0xFF) << '.' << ((*ip>>16)&0xFF) << '.' << ((*ip>>8)&0xFF) << '.' << (*ip&0xFF);

        std::cout << std::endl;
    }
}

std::vector<uint32_t> filter(std::vector<uint32_t> ip_pool, char pos, uint8_t val){
    std::vector<uint32_t> res;
    for (auto ip : ip_pool){
        if (val == ((ip >> 8*(4-pos))&0xFF)){
            res.push_back(ip);
        }
    }
    return res;
}

std::vector<uint32_t> filter_any(std::vector<uint32_t> ip_pool, uint8_t val){
    std::vector<uint32_t> res;
    for (auto ip : ip_pool){
        if (val == ((ip >> 24)&0xFF)||(val == ((ip >> 16)&0xFF))||(val == ((ip >> 8)&0xFF))||(val == (ip&0xFF))){
            res.push_back(ip);
        }
    }
    return res;
}


int main(int argc, char const *argv[])
{
    try
    {
        std::vector<uint32_t> ip_pool;
        size_t counter = 0;

        std::ifstream in(argv[1]); // окрываем файл для чтения
        if (in.is_open())
        {
            for(std::string line; std::getline(in, line);)
            {
                std::string v = line.substr(0, line.find_first_of('\t'));
                ip_pool.push_back(ipStringToInteger(v, '.'));
            }
        }
        // reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<uint32_t>());

        print(ip_pool);

        std::vector<uint32_t> filtered_pool = filter(ip_pool, 1, 1);
        print(filtered_pool);

        filtered_pool = filter(ip_pool,1, 46);
        filtered_pool = filter(filtered_pool, 2, 70);
        print(filtered_pool);

        filtered_pool = filter_any(ip_pool, 46);
        print(filtered_pool);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
