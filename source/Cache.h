#ifndef CACHE_H
#define CACHE_H

#include "cards.h"
#include "Hand.h"
#include "Shoe.h"

namespace Bj
{
    class Cache
    {
    public:
        Cache() : mAdds(0)
        {
        }

        void Add(int k, double v)
        {
            ++mAdds;
            ML::iterator it(mCache.find(k));
            if (it != mCache.end())
                it->second += v;
            else
                mCache[k] = v;
        }

        double Sum()
        {
            double sum = 0.0;
            for (ML::iterator it(mCache.begin()); it != mCache.end(); ++it)
                sum += it->second;
            return sum;
        }

        struct Key
        {
            int p1, p2, d1, d2;
            Key(int k)
            {
                p1 = k & 0xF;
                p2 = (k & 0xF0) >> 4;
                d1 = (k & 0xF00) >> 8;
                d2 = (k & 0xF000) >> 12;
            }
        };

        void PlayCache(Hand& p, Hand& d, Shoe& s)
        {
            for (ML::iterator it(mCache.begin()); it != mCache.end(); ++it)
            {
                Key k(it->first);   
                p.Push(s.Pop(k.p1));
                d.Push(s.Pop(k.d1));
                p.Push(s.Pop(k.p2));
                d.Push(s.Pop(k.d2));



                s.Push(d.Pop());
                s.Push(p.Pop());
                s.Push(d.Pop());
                s.Push(p.Pop());
            }
        }

        void Clear()
        {
            mAdds = 0;
            mCache.clear();
        }

        int mAdds;
        typedef map<int, double> ML;
        ML mCache;
    };
}

#endif 