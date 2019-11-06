#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <range/v3/all.hpp>

using ipPoolVector = std::vector<std::vector<int>>;

std::vector<int> toInt(const std::vector<std::string> &ip)
{
    std::vector<int> out;
    for (const auto& oct : ip)
    {
        out.push_back(std::stoi(oct));
    }
    return out;
}

void printIpPool(const ipPoolVector &ip_pool)
{
    for (const auto &ip : ip_pool)
    {
        for (auto oct = ip.cbegin(); oct != ip.cend(); ++oct)
        {
            if (oct != ip.cbegin())
            {
                std::cout << ".";
            }
            std::cout << *oct;
        }
        std::cout << std::endl;
    }
}

void reverseSortIpPool(ipPoolVector &ip_pool){
    ranges::sort(ip_pool, std::greater<>());
}

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

ipPoolVector filterIpPoolAny(const ipPoolVector& ip_pool, const int& value){
    ipPoolVector filtered_ip_pool;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(filtered_ip_pool), [&value](const auto ip)
                 {
                     return std::any_of(ip.begin(), ip.end(), [&value](const int &oct)
                     {
                         return oct == value;
                     });
                 }
    );
    return filtered_ip_pool;
}

template<typename... Args>
ipPoolVector filterIpPool(const ipPoolVector &ip_pool, Args const & ... args){
    ipPoolVector filtered_ip_pool;
    std::vector<int> values = {args...};
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(filtered_ip_pool), [&values](const auto ip)
                 {
                     return std::equal(ip.begin(), ip.begin() + values.size(), values.begin());
                 }
    );
    return filtered_ip_pool;
}


int main(int argc, char const *argv[])
{
    try
    {
        ipPoolVector ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(toInt(split(v.at(0), '.')));
        }

        // reverse lexicographically sort

        reverseSortIpPool(ip_pool);
        printIpPool(ip_pool);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        printIpPool(filterIpPool(ip_pool, 1));
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        printIpPool(filterIpPool(ip_pool, 46, 70));

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        printIpPool(filterIpPoolAny(ip_pool, 46));

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
