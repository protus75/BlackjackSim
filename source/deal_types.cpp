#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <functional>
#include <numeric>

using namespace std;

//#define DEBUG

#ifdef DEBUG
const bool gDebug(true);
#else
const bool gDebug(false);
#endif

const int DECKS = 2;
const int CARDS_PER_RANK = 4 * DECKS;
const int RANKS_NON_TENS = 9;
const int RANKS_ARE_TENS = 4;
const int CARDS_NON_TENS = (RANKS_NON_TENS * CARDS_PER_RANK);
const int CARDS_ARE_TENS = (RANKS_ARE_TENS * CARDS_PER_RANK);
const int CARDS = (CARDS_NON_TENS + CARDS_ARE_TENS);

const double DEAL_DEPTH = 0.75;
const int CARDS_DEALT = static_cast<int>(DEAL_DEPTH * CARDS);

//const double TRIM_TOLERANCE = 0.000015;
const double TRIM_TOLERANCE = 0.0;
const double TYPE_PERCENTAGE = 0.99;

int Combination[10][10] =
{
    //N   0    1    2    3    4    5    6    7    8    9      
    {   1,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // 0  M
    {   1,   1,   0,   0,   0,   0,   0,   0,   0,   0}, // 1
    {   1,   2,   1,   0,   0,   0,   0,   0,   0,   0}, // 2
    {   1,   3,   3,   1,   0,   0,   0,   0,   0,   0}, // 3 
    {   1,   4,   6,   4,   1,   0,   0,   0,   0,   0}, // 4
    {   1,   5,  10,  10,   5,   1,   0,   0,   0,   0}, // 5
    {   1,   6,  15,  20,  15,   6,   1,   0,   0,   0}, // 6
    {   1,   7,  21,  35,  35,  21,   7,   1,   0,   0}, // 7
    {   1,   8,  28,  56,  70,  56,  28,   8,   1,   0}, // 8
    {   1,   9,  36,  84, 126, 126,  84,  36,   9,   1}  // 9
};


class Combo
{
public:

    Combo() : T(0), N(RANKS_NON_TENS, 0), O(0.0)
    {
    }
    Combo(const Combo& c) : T(c.T), N(c.N), O(c.O)
    {
    }
    Combo& operator==(const Combo& c)
    {
        if (this != &c)
        {
            T = c.T;
            N = c.N;
            O = c.O;
        }
        return *this;
    }

    int T;
    vector<int> N;
    double O;

    /// Odds of a ten
    double TOdds() const
    {
        return(CARDS_ARE_TENS + 1.0 - T) / (CARDS + 1.0 - Cards());
    }
    /// Odds of the non-ten in the given position
    double NOdds(int n) const
    {
        if (N[n] == 1)
        {
            return((CARDS_NON_TENS + CARDS_PER_RANK) - (CARDS_PER_RANK * Diff())) / (CARDS + 1.0 - Cards());
        }
        else
        {
            return(CARDS_PER_RANK + 1.0 - N[n]) / (CARDS + 1.0 - Cards());
        }
    }
    /// number of cards in this combo
    int Cards() const 
    {
        return accumulate(N.begin(), N.end(), T);
    }
    /// number of different non-tens used
    int Diff() const
    {
        int d(0);
        while (d < N.size() && N[d])
        {
            ++d;
        }
        return d;
    }
    /// number of non-tens with same count
    int Indiv(int n) const
    {
        int s = 0;
        for (int i = 0; i < N.size(); ++i)
            s += (N[i] == n) ? 1 : 0;
        return s;
    }
    /// First non-ten with given count
    int First(int n) const
    {
        int d(0);
        while (d < N.size() && N[d] != n)
        {
            ++d;
        }
        return d;
    }

    bool operator<(const Combo& c) const
    {
        bool les = false;
        if (T == c.T)
            les = (N < c.N);
        else
            les = (T < c.T);

        return les;
    }

    void Print(ostream& outs) const
    {
        outs << T;
        for (int i = 0; i < N.size(); ++i)
        {
            outs << "," << N[i];
        }
    }
    /// Unique deals possible from this type combo
    double Deals() const
    {
        double deals(1.0);
        int ranks(RANKS_NON_TENS);
        for (size_t i = 0; i < CARDS_PER_RANK; ++i)
        {
            deals *= Combination[ranks][Indiv(i+1)];
            ranks -= Indiv(i+1);
        }
        return deals;       
    }

};

ostream& operator<<(ostream& outs, const Combo& c)
{
    c.Print(outs);
    return outs;
}

void CheckCombo(map<Combo,double>& s, double trim)
{
    if (s.empty())
    {
        cout << "Error, map is empty" << endl;
    }
    double o(trim);
    map<Combo,double>::iterator it(s.begin());
    const int n = it->first.Cards();
    while (it != s.end())
    {
        o += it->second;
        if (n != it->first.Cards())
        {
            cout << "Error, different cards: " << n << " " << it->first.Cards();
        }
        ++it;
    }
    if (fabs(o - 1.0) > 0.00000001)
    {
        cout << "Error, Odds != 1: << " << setprecision(14) << o << endl;
    }

}

void PrintOdds(map<Combo,double>& c)
{
    multimap<double,Combo> rev;
    map<Combo,double>::iterator it(c.begin());
    for (; it != c.end(); ++it)
    {
        if (gDebug) cout << it->first << " " << it->second << endl;
        rev.insert(pair<double,Combo>(it->second,it->first));
    }

    double d(0.0);
    multimap<double,Combo>::reverse_iterator rit(rev.rbegin());
    multimap<double,Combo> keep;
    multimap<double,Combo> drop;
    while (rit != rev.rend())
    {
        if (d < TYPE_PERCENTAGE)
        {
            keep.insert(pair<double,Combo>(rit->first,rit->second));
        }
        else
        {
            drop.insert(pair<double,Combo>(rit->first,rit->second));
        }
        d += rit->first;
        ++rit;
    }

    vector<double> odds(4 * DECKS + 1, 0.0);

    cout << setprecision(14);
    multimap<double,Combo>::reverse_iterator kit(keep.rbegin());
    while (kit != keep.rend())
    {
        for (unsigned int i = 0; i < odds.size(); ++i)
        {
            odds[i] += (kit->first / 9.0) * kit->second.Indiv(i);
        }
        ++kit;
    }       
    for (unsigned int i = 0; i < odds.size(); ++i)
    {
        cout << " " << odds[i];
    }
    cout << endl;
}

void PrintFinal(map<Combo,double>& c)
{
    multimap<double,Combo> rev;
    map<Combo,double>::iterator it(c.begin());
    for (; it != c.end(); ++it)
    {
        if (gDebug) cout << it->first << " " << it->second << endl;
        rev.insert(pair<double,Combo>(it->second,it->first));
    }

    cout << endl;

    double d(0.0);
    multimap<double,Combo>::reverse_iterator rit(rev.rbegin());
    multimap<double,Combo> keep;
    multimap<double,Combo> drop;
    while (rit != rev.rend())
    {
        if (d < TYPE_PERCENTAGE)
        {
            keep.insert(pair<double,Combo>(rit->first,rit->second));
        }
        else
        {
            drop.insert(pair<double,Combo>(rit->first,rit->second));
        }
        d += rit->first;
        ++rit;
    }

    double percentage(0);
    double deals(0);

    cout << setprecision(14);
    cout << "Kept:    " << keep.size() << endl;
    multimap<double,Combo>::reverse_iterator kit(keep.rbegin());
    while (kit != keep.rend())
    {
        percentage += kit->first;
        deals += kit->second.Deals();
        cout << kit->second << " " << kit->first << " " << percentage << " " 
        << kit->second.Deals() << " " << endl;
        ++kit;
    }       
    double keptDeals(deals);

    cout << "Dropped: " << drop.size() << endl;
    multimap<double,Combo>::reverse_iterator dit(drop.rbegin());
    while (dit != drop.rend())
    {
        percentage += dit->first;
        deals += dit->second.Deals();
        cout << dit->second << " " << dit->first << " " << percentage << " " 
        << dit->second.Deals() << endl;
        ++dit;
    }       

    cout << "Kept Deals " << keptDeals << " " << deals << " " << keptDeals / deals << endl;
}

void Combos(map<Combo,double>& c)
{
    map<Combo,double> n;

    static double trim(0);
    static int trimmed(0);
    static double trim_unique(0);
    static double keep_unique(0);
    CheckCombo(c, trim);

    int cards = c.begin()->first.Cards();
    if (cards < CARDS_DEALT)
    {
        if (gDebug) cout << cards << " " << c.size() << endl;

        map<Combo,double>::iterator it(c.begin());
        for (; it != c.end(); ++it)
        {
            if (it->first.T < CARDS_ARE_TENS)
            {
                Combo t(it->first);
                ++(t.T);
                const double d = t.TOdds() * it->second;
                n[t] += d;
                if (gDebug) cout << t << " " << d << " " << t.TOdds() << " " << it->second << endl;
            }
            for (int i = 0; i < CARDS_PER_RANK; ++i)
            {
                int indiv(it->first.Indiv(i));
                if (indiv)
                {
                    Combo a(it->first);
                    ++(a.N[it->first.First(i)]);
                    const double d = a.NOdds(it->first.First(i)) * it->second * (i ? indiv : 1);
                    n[a] += d;
                    if (gDebug) cout << a << " " << d << " " << a.NOdds(it->first.First(i)) << " " << it->second << endl;
                }
            }
        }

        if (gDebug) cout << "Resulting" << endl;

        double trim_deals(0);
        double keep_deals(0);
        map<Combo,double> r;
        it = n.begin();
        while (it != n.end())
        {
            if (it->second < TRIM_TOLERANCE)
            {
                if (gDebug)
                    cout << setw(3) << trimmed << " " << it->first.Cards() << " " << it->first << endl;
                trim += it->second;
                ++trimmed;
                if (gDebug && !(trimmed % 23))
                {
                    char c;
                    cin >> c;
                }
                trim_deals += it->first.Deals();
            }
            else
            {
                if (gDebug) cout << "Keep  " << it->first << " " << it->second << endl;
                keep_deals += it->first.Deals();
                r.insert(*it);
            }
            ++it;
        }
        if (gDebug) cout << "Trimmed " << trim << endl;
        trim_unique += trim_deals;
        keep_unique += keep_deals;
        if (gDebug) cout << r.begin()->first.Cards() << " " << r.size() 
            << " " << keep_deals << "k + " << trim_deals << "t  = " << trim_deals + keep_deals 
            << "d, " << keep_unique << "k " << trim_unique << "t" << endl;

        c.swap(r);
        Combos(c);
    }
    else
    {
        PrintFinal(c);
//		PrintOdds(c);
    }
}


void AllCombos()
{
    map<Combo,double> s;

    Combo t;
    ++(t.T);
    s[t] = t.TOdds();

    Combo a;
    ++(a.N[0]);
    s[a] = a.NOdds(0);

    Combos(s);
}

int main(int argc, char* argv[])
{
    AllCombos();
    return 0;
}

