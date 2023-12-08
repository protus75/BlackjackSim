#ifndef CARDS_H
#define CARDS_H

#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::setprecision;

namespace Bj
{

    typedef std::pair<int, int> TOdds;

    enum Name
    {
        Ace = 1,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King
    };

    enum Kind
    {
        Hard = 0,
        Soft,
        Pair
    };

/// \todo put a real comparison routine here
    static bool IsClose(const double aA, const double aB)
    {
        return std::fabs(aA - aB) < 0.000000000001;
    }


    inline int Sum(int i, int j, int k = 0, int l = 0, int m = 0, int n = 0, int o = 0)
    {
        int s(i);
        s += j;
        s += k;
        s += l;
        s += m;
        s += n;
        s += o;

        if (s <= 11)
        {
            if ((1 == i) || (1 == k) || (1 == l) || (1 == m) || (1 == n) || (1 == o))
                s += 10;
        }

        return s;
    }

}

#endif
