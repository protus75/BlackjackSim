#include <vector>
#include <iomanip>
#include <algorithm>

#include "DealerResults.h"
#include "Wlt.h"
#include "Divide.h"

const auto gBjPayout = double(3.0 / 2.0); // (6.0 / 5.0);
const auto gHitSoft17 = bool(false);
const auto gSurrender = bool(true);
const auto gIgnoreDealerBj = bool(true);
const auto gMaxSplit = int(4);

const auto gStrategy = bool(false);

using std::vector;

auto zero1D = vector<double>(10, 0);
auto zero2D = vector<vector<double>>(10, zero1D);

auto loss1D = vector<double>(10, -1.0);

auto sur1D = vector<double>(10, gSurrender ? -0.5 : -1.0);
auto sur2D = vector<vector<double>>(10, sur1D);

auto wlt1D = vector<Bj::Wlt>(10);
auto wlt2D = vector<vector<Bj::Wlt>>(10, wlt1D);

//vector<vector<Bj::Wlt> > gSplit(10, tmp1);

auto unk1D = vector<char>(10, '?');
auto unk2D = vector<vector<char>>(10, unk1D);

class Expect
{
public:

    vector<vector<vector<double>>> mOdds;
    vector<vector<vector<double>>> mBest;
    vector<vector<vector<Bj::Wlt>>> mDouble;
    vector<vector<vector<Bj::Wlt>>> mStand;
    vector<vector<vector<Bj::Wlt>>> mHit;
    vector<vector<double>> mSplit;
    vector<vector<vector<char>>> mChoice;

    double mExp;

    Expect(int s[11], int rem)
        : mOdds(10, zero2D)
        , mBest(10, sur2D)
        , mDouble(10, wlt2D)
        , mStand(10, wlt2D)
        , mHit(10, wlt2D)
        , mSplit(10, loss1D)
        , mChoice(10, unk2D)
        , mExp(0.0)
    {
        Play(s, rem);

        Choose();

        auto odds = double(0.0);
        for (int i = 9; i >= 0; --i)
        {
            for (int j = 0; j < 10; ++j)
            {
                for (int k = 0; k <= j; ++k)
                {
                    odds += mOdds[i][k][j];
                    mExp += mOdds[i][k][j] * mBest[i][k][j];
                }
            }
        }

        if (odds != 1.0 and (abs(odds - 1.0) > 0.000001))
        {
            std::cerr << "Deck odds did not sum to 1.0.  (" << odds << ")";
        }
    }

private:
    void Odds(int s[11], int rem);

    void Stand(int s[11], int rem);
    
    void Double(int s[11], int rem);
    
    Bj::Wlt Hit(const Bj::Wlt& stand, int p[11], int s[11], int rem, int d1, int p1, int p2, double ratio);
    
    void Hit(int s[11], int rem);
    
    void Split(int s[11], int rem);
    
    double Split(int s[11], int rem, int d, int p);

    // Calculate individual cases for each hand
    void Play(int s[11], int rem)
    {
        Odds(s, rem);
        Stand(s, rem);
        Double(s, rem);
        Hit(s, rem);
        Split(s, rem);
    }

    void Choose()
    {
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                for (int k = 0; k <= j; ++k)
                {
                    mBest[i][k][j] = mStand[i][k][j].exp();
                    mChoice[i][k][j] = 'S';

                    const auto hit = mHit[i][k][j].exp();
                    if (hit > mBest[i][k][j])
                    {
                        mBest[i][k][j] = hit;
                        mChoice[i][k][j] = 'H';
                    }

                    /// when Hit and Double are essentially the same odds, and positive, then should choose Double with a small tolerance to avoid spurious Hit instead of Double
                    const auto dbl = mDouble[i][k][j].exp();
                    if ((dbl >= 0.0) and ((dbl > mBest[i][k][j]) or (abs(dbl - mBest[i][k][j]) < 0.001)))
                    {
                        mBest[i][k][j] = dbl;
                        mChoice[i][k][j] = '2';
                    }

                    // can only figure surrender when ignoring dealer natural
                    /// \todo why?
                    if (gSurrender && gIgnoreDealerBj)
                    {
                        mBest[i][k][j] = std::max(mBest[i][k][j], -0.5);
                        mChoice[i][k][j] = 'U';
                    }

                    // only consider split when have same rank cards
                    if (j == k)
                    {
                        mBest[i][k][j] = std::max(mBest[i][k][j], mSplit[i][j]);
                        mChoice[i][k][j] = '|';
                    }
                }
            }
        }
    }

public:

    void Print() const;
};

void Expect::Odds(int s[11], int rem)
{
    for (int p1 = 10; p1 > 0; --p1) if (s[p1])
    {
        const double p1Odds(double(s[p1]) / rem);
        --s[p1]; --rem;

        for (int p2 = p1; p2 <= 10; ++p2) if (s[p2])
        {
            const double p2Odds(double(s[p2]) / rem);
            --s[p2]; --rem;

            const double ratio = ((p1 == p2) ? 1.0 : 2.0);

            for (int d1 = 10; d1 > 0; --d1) if (s[d1])
            {
                const double d1Odds(double(s[d1]) / rem);

                mOdds[d1 - 1][p1 - 1][p2 - 1] = d1Odds * p1Odds * p2Odds * ratio;

            }

            ++s[p2]; ++rem;
        }

        ++s[p1]; ++rem;
    }
}

void Expect::Stand(int s[11], int rem)
{
    for (int p1 = 10; p1 > 0; --p1) if (s[p1])
    {
        --s[p1]; --rem;

        for (int p2 = p1; p2 <= 10; ++p2) if (s[p2])
        {
            --s[p2]; --rem;

            bool natural(((p1 == 1) && (p2 == 10)) || ((p1 == 10) && (p2 == 1)));
            int p[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            ++p[p1];
            ++p[p2];

            for (int d1 = 10; d1 > 0; --d1) if (s[d1])
            {
                --s[d1]; --rem;

                // skip any dealer BJs
                const int beg((10 == d1) ? 2 : 1);
                const int end((1 == d1) ? 9 : 10);

                Bj::Wlt stand;
                for (int d2 = beg; d2 <= end; ++d2) if (s[d2])
                {
                    const double d2Odds(double(s[d2]) / rem);
                    --s[d2]; --rem;

                    Bj::DealerResults dr(gHitSoft17);
                    dr.Results(d1, d2, rem, s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8], s[9], s[10], 1.0, p1 + p2);
                    stand += dr.WinLoss(p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], natural, gIgnoreDealerBj).scale(d2Odds);

                    ++s[d2]; ++rem;
                }

                if (natural)
                {
                    stand.scale(gBjPayout, false);
                }

                double ratio(1.0);
                if ((d1 == 10) || (d1 == 1))
                {
                    const int off((d1 == 10) ? s[1] : s[10]);
                    if (rem != off)
                    {
                        ratio = (double(rem) / (rem - off));
                        //                        stand.scale(ratio);
                        if (natural)
                        {
                            stand.mCards = 4.0 / ratio;
                        }
                    }
                }

                mStand[d1 - 1][p1 - 1][p2 - 1] = stand * ratio;

                ++s[d1]; ++rem;
            }

            ++s[p2]; ++rem;
        }

        ++s[p1]; ++rem;
    }
}

void Expect::Double(int s[11], int rem)
{
    for (int p1 = 10; p1 > 0; --p1)
    {
        if (s[p1])
        {
            --s[p1]; --rem;

            for (int p2 = p1; p2 <= 10; ++p2)
            {
                if (s[p2])
                {
                    --s[p2]; --rem;

                    for (int d1 = 10; d1 > 0; --d1)
                    {
//                        cout << ((p1 + p2 <= 11) && (p1 == 1 || p2 == 1) ? p1 + p2 + 10 : p1 + p2) 
//                        << " = " << d1 << ",? : " << p1 << "," << p2 << "  " << endl;
                        if (s[d1])
                        {
                            --s[d1]; --rem;

                            Bj::Wlt wr;
#define REORDER_OK
#ifdef REORDER_OK
                            double dl_nat_odds(0.0);
                            double odds(0.0);
                            for (int p3 = 1; p3 <= 10; ++p3)
                            {
                                if (s[p3])
                                {
                                    const double p3Odds = double(s[p3]) / rem;
                                    --s[p3]; --rem;

                                    Bj::Wlt wd;

                                    double p_dl_nat_odds(0.0);
                                    double p_odds(0.0);
                                    for (int d2 = 1; d2 <= 10; ++d2)
                                    {
                                        if (s[d2])
                                        {
                                            const double d2Odds = double(s[d2]) / rem;
                                            --s[d2]; --rem;

                                            if (gIgnoreDealerBj)
                                            {
                                                bool dl_nat(((d1 == 1) && (d2 == 10)) || ((d1 == 10) && (d2 == 1)));
                                                if (dl_nat)
                                                {
                                                    p_dl_nat_odds = d2Odds;
                                                }
                                            }

                                            p_odds += d2Odds;

                                            Bj::DealerResults dr(gHitSoft17);
                                            dr.Results(d1,d2,rem,s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9],s[10],
                                                       1.0, p1 + p2 + p3);

                                            int p[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                                            ++p[p1];
                                            ++p[p2];
                                            ++p[p3];
                                            wd += dr.WinLoss(p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],false,gIgnoreDealerBj).scale(d2Odds);

                                            ++s[d2]; ++rem;
                                        }
                                    }

                                    dl_nat_odds += p3Odds * p_dl_nat_odds;
                                    odds += p3Odds * p_odds;

                                    wr += wd.scale(p3Odds);

                                    ++s[p3]; ++rem;
                                }
                            }

                            mDouble[d1 - 1][p1 - 1][p2 - 1] = wr.scale(2.0, false);
                            if (gIgnoreDealerBj)
                            {
                                const double adjust(1.0 / (1.0 - dl_nat_odds));
                                mDouble[d1 - 1][p1 - 1][p2 - 1] *= adjust;
                            }
#else
                            double dl_nat_odds(0.0);
                            for (int d2 = 1; d2 <= 10; ++d2)
                            {
                                if (s[d2])
                                {
                                    const double d2Odds = double(s[d2]) / rem;
                                    --s[d2]; --rem;

                                    if (gIgnoreDealerBj)
                                    {
                                        bool dl_nat(((d1 == 1) && (d2 == 10)) || ((d1 == 10) && (d2 == 1)));
                                        if (dl_nat)
                                        {
                                            dl_nat_odds += d2Odds;
                                        }
                                    }

                                    for (int p3 = 1; p3 <= 10; ++p3)
                                    {
                                        if (s[p3])
                                        {
                                            const double p3Odds = double(s[p3]) / rem;
                                            --s[p3]; --rem;

                                            Bj::DealerResults dr(gHitSoft17);
                                            dr.Results(d1,d2,rem,s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9],s[10],
                                                       1.0, p1 + p2 + p3);

                                            int p[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                                            ++p[p1];
                                            ++p[p2];
                                            ++p[p3];
                                            wr += dr.WinLoss(p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],false,gIgnoreDealerBj).scale(d2Odds*p3Odds);

                                            ++s[p3]; ++rem;
                                        }
                                    }

                                    ++s[d2]; ++rem;
                                }
                            }

                            mDouble[d1 - 1][p1 - 1][p2 - 1] = wr.scale(2.0);
                            if (gIgnoreDealerBj)
                            {
                                const double adjust(1.0 / (1.0 - dl_nat_odds));
                                mDouble[d1 - 1][p1 - 1][p2 - 1] *= adjust;
                            }
#endif                           
                            ++s[d1]; ++rem;
                        }
                    }

                    ++s[p2]; ++rem;
                }
            }

            ++s[p1]; ++rem;
        }
    }
//    cout << endl;
}

//    int off(0);
//    if (2 == cards && s[10] != rem) off = s[10];
//    if (2 == cards && s[1] != rem) off = s[1];
//    const double dbj_ratio(rem != off ? double(rem) / (rem - off) : 0.0);
//    Bj::Wlt tmp_stand(stand);
//    tmp_stand.scale(1.0 / dbj_ratio);
//    hit = 
//    hit.scale(dbj_ratio);

Bj::Wlt Expect::Hit(const Bj::Wlt& stand, int p[11], int s[11], int rem, int d1, int p1, int p2, double ratio)
{
    int sum(p[1] + 2 * p[2] + 3 * p[3] + 4 * p[4] + 5 * p[5] + 6 * p[6] + 7 * p[7] + 8 * p[8] + 9 * p[9] + 10 * p[10]);
    int cards(p[1] + p[2] + p[3] + p[4] + p[5] + p[6] + p[7] + p[8] + p[9] + p[10]);

    //std::cout << cards << "c " << std::endl;

    const int beg((10 == d1) ? 2 : 1);
    const int end((1 == d1) ? 9 : 10);

    Bj::Wlt hit;
    for (int i = 1; i <= 10; ++i) if (s[i])
    {
        //std::cout << std::setw(cards) << i << std::endl;
        const double p1Odds(double(s[i]) / rem);
        sum += i; ++cards; 
        --s[i]; --rem; ++p[i];

    	double cur_ratio(1.0);
		if ((d1 == 10) || (d1 == 1))
		{
			const int off((d1 == 10) ? s[1] : s[10]);
			cur_ratio = (rem - off) / double(rem);
		}

        if (sum > 21)
        {

            Bj::DealerOdds odds;
            odds.m20 = 1.0;
            odds.mCards = 2.0;
            Bj::Wlt loss(odds, false, sum, cards, true);
            hit += loss.scale(cur_ratio * p1Odds);
        }
        else
        {
            Bj::Wlt hit_stand;
            for (int d2 = beg; d2 <= end; ++d2) if (s[d2])
            {
                const double d2Odds(double(s[d2]) / rem);
                --s[d2]; --rem;

                Bj::DealerResults dr(gHitSoft17);
                dr.Results(d1,d2,rem,s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9],s[10],1.0,i);
                hit_stand += dr.WinLoss(p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],false,gIgnoreDealerBj).scale(d2Odds);

                ++s[d2]; ++rem;
            }
			hit_stand.scale(cur_ratio);

            //std::cout << "hit_stand: "; hit_stand.print(4);
            if (cards < 5)
            {
                const Bj::Wlt tmp_hit(Hit(hit_stand, p, s, rem, d1, p1, p2, 1.0));
                hit_stand = std::max(hit_stand, tmp_hit);
            }
            //std::cout << "hit_stand: "; hit_stand.print(4);

			hit += hit_stand.scale(p1Odds);

        }

        ++s[i]; ++rem; --p[i];
        sum -= i; --cards; 
    }

    //std::cout << "hit      : "; hit.print(4);
    //std::cout << "    stand: "; stand.print(4);
    //std::cout << std::endl;

    if (cards == 2)
    {
        return hit;
    }
    else
    {
        return std::max(stand, hit);
    }
}

void Expect::Hit(int s[11], int rem)
{
    for (int p1 = 10; p1 > 0; --p1) if (s[p1])
    {
        --s[p1]; --rem;

        for (int p2 = p1; p2 <= 10; ++p2) if (s[p2])
        {
            --s[p2]; --rem;

            int p[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            ++p[p1];
            ++p[p2];

            for (int d1 = 10; d1 > 0; --d1) if (s[d1])
            {
                --s[d1]; --rem;
                //std::cout << p1 << " " << p2 << " " << d1 << std::endl;

                double ratio(1.0);
                if ((d1 == 10) || (d1 == 1))
                {
                    const int off((d1 == 10) ? s[1] : s[10]);
                    if (rem != off)
                    {
                        ratio = (double(rem) / (rem - off));
                    }
                }

                mHit[d1 - 1][p1 - 1][p2 - 1] = Hit(mStand[d1 - 1][p1 - 1][p2 - 1], p, s, rem, d1, p1, p2, 1.0);

                mHit[d1 - 1][p1 - 1][p2 - 1] *= ratio;

                //std::cout << "Hit      : "; mHit[d1 - 1][p1 - 1][p2 - 1].print(4);

                ++s[d1]; ++rem;
            }

            ++s[p2]; ++rem;
        }

        ++s[p1]; ++rem;
    }
}

double Expect::Split(int s[11], int rem, int d1, int p1)
{
    double exp(0.0);
    if (1 == p1)
    {
        double split_two(0.0);
        double cumul(0.0);
        // Only get one card per ace after splitting aces
        for (int p2a = 1; p2a <= 10; ++p2a)
        {
            if (s[p2a])
            {
                const double p2aOdds = double(s[p2a]) / rem;
                --s[p2a]; --rem;

                for (int p2b = p2a; p2b <= 10; ++p2b)
                {
                    if (s[p2b])
                    {
                        const double p2bOdds = double(s[p2b]) / rem;
                        --s[p2b]; --rem;

                        Bj::DealerResults dlr_res(gHitSoft17);

                        for (int d2 = 1; d2 <= 10; ++d2)
                        {
                            if (s[d2])
                            {
                                const double d2Odds = double(s[d2]) / rem;

                                --s[d2]; --rem;

                                dlr_res.Results(d1,d2,rem,s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9],s[10],d2Odds,-99);

                                ++s[d2]; ++rem;
                            }
                        }

                        int pa[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                        ++pa[p1];
                        ++pa[p2a];

                        int pb[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                        ++pb[p1];
                        ++pb[p2b];

                        const double expa(dlr_res.WinLoss(pa[1],pa[2],pa[3],pa[4],pa[5],pa[6],pa[7],pa[8],pa[9],pa[10],false,gIgnoreDealerBj).exp());

                        const double expb(dlr_res.WinLoss(pb[1],pb[2],pb[3],pb[4],pb[5],pb[6],pb[7],pb[8],pb[9],pb[10],false,gIgnoreDealerBj).exp());

                        const double odds_ratio(p2a == p2b ? 1.0 : 2.0);

                        cumul += odds_ratio * p2aOdds * p2bOdds;

                        split_two += odds_ratio * (expa + expb) * p2aOdds * p2bOdds;

                        if (false)
                        {
                            using std::setw;
                            std::cout << "d:" << setw(3) << d1;
                            std::cout << ", a:" << setw(3) << p2a << " e:" << setw(8) << expa << ", o:" << setw(8) << p2aOdds;
                            std::cout << ", b:" << setw(3) << p2b << " e:" << setw(8) << expb << ", o:" << setw(8) << p2bOdds;
                            std::cout << ", cm:" << setw(8) << cumul << ", x:" << setw(8) << split_two << std::endl;
                        }

                        ++s[p2b]; ++rem;
                    }
                }

                ++s[p2a]; ++rem;
            }
        }
        double split_thr(-1.0);
        if (s[1])
        {
        }
        exp = std::max(split_two, split_thr);
    }
    else
    {
        exp = mSplit[d1-1][p1-1];
    }

    return exp;
}


void Expect::Split(int s[11], int rem)
{
    mSplit[0][0] =  0.2239;
    mSplit[0][1] = -0.422;
    mSplit[0][2] = -0.465;
    mSplit[0][3] = -0.527;
    mSplit[0][4] = -0.613;
    mSplit[0][5] = -0.617;
    mSplit[0][6] = -0.613;
    mSplit[0][7] = -0.363;
    mSplit[0][8] = -0.113;
    mSplit[0][9] =  0.097;
    mSplit[1][0] =  0.5657;
    mSplit[1][1] = -0.047;
    mSplit[1][2] = -0.116;
    mSplit[1][3] = -0.156;
    mSplit[1][4] = -0.193;
    mSplit[1][5] = -0.165;
    mSplit[1][6] = -0.105;
    mSplit[1][7] =  0.064;
    mSplit[1][8] =  0.188;
    mSplit[1][9] =  0.331;
    mSplit[2][0] =  0.6128;
    mSplit[2][1] =  0.021;
    mSplit[2][2] = -0.031;
    mSplit[2][3] = -0.048;
    mSplit[2][4] = -0.104;
    mSplit[2][5] = -0.069;
    mSplit[2][6] = -0.020;
    mSplit[2][7] =  0.132;
    mSplit[2][8] =  0.242;
    mSplit[2][9] =  0.383;
    mSplit[3][0] =  0.6686;
    mSplit[3][1] =  0.112;
    mSplit[3][2] =  0.102;
    mSplit[3][3] =  0.076;
    mSplit[3][4] =  0.014;
    mSplit[3][5] =  0.047;
    mSplit[3][6] =  0.103;
    mSplit[3][7] =  0.215;
    mSplit[3][8] =  0.320;
    mSplit[3][9] =  0.444;
    mSplit[4][0] =  0.7322;
    mSplit[4][1] =  0.239;
    mSplit[4][2] =  0.228;
    mSplit[4][3] =  0.197;
    mSplit[4][4] =  0.133;
    mSplit[4][5] =  0.172;
    mSplit[4][6] =  0.200;
    mSplit[4][7] =  0.312;
    mSplit[4][8] =  0.415;
    mSplit[4][9] =  0.521;
    mSplit[5][0] =  0.7583;
    mSplit[5][1] =  0.240;
    mSplit[5][2] =  0.220;
    mSplit[5][3] =  0.183;
    mSplit[5][4] =  0.131;
    mSplit[5][5] =  0.151;
    mSplit[5][6] =  0.220;
    mSplit[5][7] =  0.356;
    mSplit[5][8] =  0.437;
    mSplit[5][9] =  0.543;
    mSplit[6][0] =  0.5407;
    mSplit[6][1] = -0.006;
    mSplit[6][2] = -0.068;
    mSplit[6][3] = -0.160;
    mSplit[6][4] = -0.228;
    mSplit[6][5] = -0.228;
    mSplit[6][6] = -0.056;
    mSplit[6][7] =  0.259;
    mSplit[6][8] =  0.364;
    mSplit[6][9] =  0.478;
    mSplit[7][0] =  0.4065;
    mSplit[7][1] = -0.192;
    mSplit[7][2] = -0.244;
    mSplit[7][3] = -0.291;
    mSplit[7][4] = -0.391;
    mSplit[7][5] = -0.374;
    mSplit[7][6] = -0.378;
    mSplit[7][7] = -0.059;
    mSplit[7][8] =  0.207;
    mSplit[7][9] =  0.345;
    mSplit[8][0] =  0.2898;
    mSplit[8][1] = -0.373;
    mSplit[8][2] = -0.395;
    mSplit[8][3] = -0.459;
    mSplit[8][4] = -0.560;
    mSplit[8][5] = -0.542;
    mSplit[8][6] = -0.535;
    mSplit[8][7] = -0.383;
    mSplit[8][8] = -0.093;
    mSplit[8][9] =  0.172;
    mSplit[9][0] =  0.1942;
    mSplit[9][1] = -0.499;
    mSplit[9][2] = -0.498;
    mSplit[9][3] = -0.552;
    mSplit[9][4] = -0.648;
    mSplit[9][5] = -0.647;
    mSplit[9][6] = -0.606;
    mSplit[9][7] = -0.447;
    mSplit[9][8] = -0.265;
    mSplit[9][9] =  0.033;

    for (int d = 1; d <= 10; ++d)
    {
        if (s[d])
        {
            --s[d]; --rem;
            for (int p = 1; p <= 10; ++p)
            {
                if (s[p] >= 2)
                {
                    s[p] -= 2; rem -= 2;

                    mSplit[d-1][p-1] = Split(s,rem,d,p);

                    s[p] += 2; rem += 2;
                }

            }
            ++s[d]; ++rem;
        }
    }
}

void ColHeader(const std::string aType)
{
    cout << std::setw(8) << aType;
    for (int c = 1; c <= 10; ++c)
    {
        std::cout << std::setw(8) << c;
    }
    cout << endl;
}

void Expect::Print() const
{
	// output

	std::cout.precision(4);
	std::cout.setf(std::ios::fixed);

    cout << endl << mExp << endl;

	cout << endl << "+++" << endl;

    double sum_sum_sum(0.0);

#if 0
    bool isPrintCards = true;
#else
    bool isPrintCards = false;
#endif

    for (int i = 9; i >= 0; --i)
    {
        cout << "Dealer Up Card: " << i + 1 << endl;
        std::cout << std::endl;
/////////////////////////////////////////////////////////////////////////////
        ColHeader("Stand");
        for (int j = 0; j < 10; ++j)
        {
            std::cout << std::setw(8) << j + 1;
            for (int k = 0; k <= j; ++k)
            {
                std::cout << std::setw(8) << mStand[i][k][j].exp();
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        if (isPrintCards)
        {
            ColHeader("Stand #");
            for (int j = 0; j < 10; ++j)
            {
                std::cout << std::setw(8) << j + 1;
                for (int k = 0; k <= j; ++k)
                {
                    std::cout << std::setw(8) << mStand[i][k][j].mCards;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
/////////////////////////////////////////////////////////////////////////////
        ColHeader("Hit");
        for (int j = 0; j < 10; ++j)
        {
            std::cout << std::setw(8) << j + 1;
            for (int k = 0; k <= j; ++k)
            {
                std::cout << std::setw(8) << mHit[i][k][j].exp();
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        if (isPrintCards)
        {
            ColHeader("Hit #");
            for (int j = 0; j < 10; ++j)
            {
                std::cout << std::setw(8) << j + 1;
                for (int k = 0; k <= j; ++k)
                {
                    std::cout << std::setw(8) << mHit[i][k][j].mCards;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
 /////////////////////////////////////////////////////////////////////////////
        ColHeader("Double");
        for (int j = 0; j < 10; ++j)
        {
            std::cout << std::setw(8) << j + 1;
            for (int k = 0; k <= j; ++k)
            {
                std::cout << std::setw(8) << mDouble[i][k][j].exp();
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        if (isPrintCards)
        {
            ColHeader("Double #");
            for (int j = 0; j < 10; ++j)
            {
                std::cout << std::setw(8) << j + 1;
                for (int k = 0; k <= j; ++k)
                {
                    std::cout << std::setw(8) << mDouble[i][k][j].mCards;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
 /////////////////////////////////////////////////////////////////////////////
        ColHeader("Split");

        if (true)
        {
            std::cout << std::setw(8) << " ";
            for (int j = 0; j < 10; ++j)
            {
                std::cout << std::setw(8) << mSplit[i][j];
            }
            std::cout << std::endl;
        }
        else
        {
            for (int j = 0; j < 10; ++j)
            {
                std::cout << std::setw(8) << j + 1;
                for (int k = 0; k < j; ++k)
                {
                    std::cout << std::setw(8) << " ";
                }
                std::cout << std::setw(8) << mSplit[i][j];
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
/////////////////////////////////////////////////////////////////////////////
        {
            ColHeader("Best");
            for (int j = 0; j < 10; ++j)
            {
                std::cout << std::setw(8) << j + 1;
                for (int k = 0; k <= j; ++k)
                {
                    std::cout << std::setw(8) << mBest[i][k][j];
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
/////////////////////////////////////////////////////////////////////////////
        {
            ColHeader("Odds");
            vector<double> sum(10, 0.0);
            for (int j = 0; j < 10; ++j)
            {
                std::cout << std::setw(8) << j + 1;
                for (int k = 0; k <= j; ++k)
                {
                    sum[k] += mOdds[i][k][j];
                    std::cout << std::setw(8) << mOdds[i][k][j];
                }
                std::cout << std::endl;
            }
            cout << std::setw(8) << "Sum";
            double sum_sum(0.0);
            for (int j = 0; j < 10; ++j)
            {
                sum_sum += sum[j];
                std::cout << std::setw(8) << sum[j];
            }
            std::cout << std::setw(8) << sum_sum << std::endl;
            std::cout << std::endl;
        }
/////////////////////////////////////////////////////////////////////////////
        {
            ColHeader("Exp");
            vector<double> sum(10, 0.0);
            for (int j = 0; j < 10; ++j)
            {
                std::cout << std::setw(8) << j + 1;
                for (int k = 0; k <= j; ++k)
                {
                    sum[k] += mOdds[i][k][j] * mBest[i][k][j];
                    std::cout << std::setw(8) << mOdds[i][k][j] * mBest[i][k][j];
                }
                std::cout << std::endl;
            }
            cout << std::setw(8) << "Sum";
            double sum_sum(0.0);
            for (int j = 0; j < 10; ++j)
            {
                sum_sum += sum[j];
                std::cout << std::setw(8) << sum[j];
            }
            std::cout << std::setw(8) << sum_sum << std::endl;
            std::cout << std::endl;

            sum_sum_sum += sum_sum;
        }

        cout << "---" << endl;
    }
    std::cout << std::setw(8) << sum_sum_sum << std::endl;

}

int main(int argc, char* argv[])
{
    const int d = 1;
    const int r = 4;

    int s[11] = { 0, d * r, d * r, d * r, d * r, d * r, d * r, d * r, d * r, d * r, 4 * d * r };
    int rem = d * r * 13;

    Bj::InitialDivide();

    const auto e = Expect(s, rem);

    e.Print();

    return 0;
}


    #if 0
for (int i = 1; i <= 10; ++i)
{
    if (s[i])
    {
        const double p1Odds(double(s[i]) / rem);
        sum += i; ++cards; 

        if (sum > 21)
        {
            Bj::DealerOdds dlr_odds;
            dlr_odds.m21 = 1.0;
            hit += Bj::Wlt(dlr_odds, false, sum, gIgnoreDealerBj).scale(p1Odds);
        }
        else
        {
            --s[i]; --rem; ++p[i];

            Bj::DealerResults dlr_res(gHitSoft17);
            Bj::Wlt wr;

            for (int d2 = 1; d2 <= 10; ++d2)
            {
                if (s[d2])
                {
                    const double d2Odds = double(s[d2]) / rem;

                    --s[d2]; --rem;

                    dlr_res.Results(d1,d2,rem,s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9],s[10],d2Odds,sum);

                    ++s[d2]; ++rem;
                }
            }

            Bj::Wlt hit_stand(dlr_res.WinLoss(p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],false,gIgnoreDealerBj));
            hit += Bj::Wlt(std::max(hit_stand,
                                    Hit(hit_stand, p, s, rem, d1, p1, p2))).scale(p1Odds);
    #else
    #endif

