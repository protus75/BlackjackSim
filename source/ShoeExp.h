#ifndef H_SHOE_EXP
#define H_SHOE_EXP

#include "Wlt.h"
#include "Divide.h"

namespace Bj
{
    std::vector<std::vector<Wlt> > D(11, std::vector<Wlt>(11, Wlt(0))); // Dealer
    std::vector<std::vector<Wlt> > R(11, std::vector<Wlt>(11, Wlt(0))); // Surrender
    std::vector<std::vector<Wlt> > B(11, std::vector<Wlt>(11, Wlt(0))); // Double
    std::vector<std::vector<Wlt> > P(11, std::vector<Wlt>(11, Wlt(0))); // Split
    std::vector<std::vector<Wlt> > T(11, std::vector<Wlt>(11, Wlt(0))); // Stand
    std::vector<std::vector<Wlt> > H(11, std::vector<Wlt>(11, Wlt(0))); // Hit

    Wlt Dealer_Zero(int one, int two, int thr, int fou, int fiv,
                    int six, int sev, int eig, int nin, int ten, int num)
    {
        const Wlt wlt(0);
        Wlt result(one ? gDivide[num][one] * Dealer_One(one-1,two,thr,fou,fiv,six,sev,eig,nin,ten,num-1,1) : wlt);
        result += (two ? gDivide[num][two] * Dealer_One(one,two-1,thr,fou,fiv,six,sev,eig,nin,ten,num-1,2) : wlt);
        result += (thr ? gDivide[num][thr] * Dealer_One(one,two,thr-1,fou,fiv,six,sev,eig,nin,ten,num-1,3) : wlt);
        result += (fou ? gDivide[num][fou] * Dealer_One(one,two,thr,fou-1,fiv,six,sev,eig,nin,ten,num-1,4) : wlt);
        result += (fiv ? gDivide[num][fiv] * Dealer_One(one,two,thr,fou,fiv-1,six,sev,eig,nin,ten,num-1,5) : wlt);
        result += (six ? gDivide[num][six] * Dealer_One(one,two,thr,fou,fiv,six-1,sev,eig,nin,ten,num-1,6) : wlt);
        result += (sev ? gDivide[num][sev] * Dealer_One(one,two,thr,fou,fiv,six,sev-1,eig,nin,ten,num-1,7) : wlt);
        result += (eig ? gDivide[num][eig] * Dealer_One(one,two,thr,fou,fiv,six,sev,eig-1,nin,ten,num-1,8) : wlt);
        result += (nin ? gDivide[num][nin] * Dealer_One(one,two,thr,fou,fiv,six,sev,eig,nin-1,ten,num-1,9) : wlt);
        result += (ten ? gDivide[num][ten] * Dealer_One(one,two,thr,fou,fiv,six,sev,eig,nin,ten-1,num-1,10) : wlt);
    }

    Wlt Dealer_One(int one, int two, int thr, int fou, int fiv,
                   int six, int sev, int eig, int nin, int ten, int num, int crd)       
    {
        const Wlt wlt(0);
        Wlt result(one ? gDivide[num][one] * D[crd][1] : wlt);
        result += (two ? gDivide[num][two] * D[crd][2] : wlt);
        result += (thr ? gDivide[num][thr] * D[crd][3] : wlt);
        result += (fou ? gDivide[num][fou] * D[crd][4] : wlt);
        result += (fiv ? gDivide[num][fiv] * D[crd][5] : wlt);
        result += (six ? gDivide[num][six] * D[crd][6] : wlt);
        result += (sev ? gDivide[num][sev] * D[crd][7] : wlt);
        result += (eig ? gDivide[num][eig] * D[crd][8] : wlt);
        result += (nin ? gDivide[num][nin] * D[crd][9] : wlt);
        result += (ten ? gDivide[num][ten] * D[crd][10] : wlt);
    }

    Wlt Dealer_Natural()
    {
        return Wlt(0);
    }

    Wlt Double()
    {
        return Wlt(0);
    }

    Wlt Split()
    {
        return Wlt(0);
    }

    Wlt Stand(int d1, int d2, int one, int two, int thr, int fou, int fiv,
              int six, int sev, int eig, int nin, int ten, int num)
    {
        const int odds(1.0);
        const int prob(1.0);
        D[1][1] = 
        for (int i = 1; i < 11; ++i)
        {
            for (int j = i; j < 11; ++j)
            {
                DealerResults dr;
                return dr.Results(d1,d2,num,one,two,thr,fou,fiv,six,sev,eig,nin,ten,prob,odds);
            }
        }
    }

    Wlt Hit()
    {
        return Wlt(0);
    }

    Wlt Insurance()
    {
        return Wlt(0);
    }

    Wlt Surrender()
    {
        return Wlt(0);
    }

    Wlt Dealer(int key)
    {
        using std::max;
        int ace(Count(1, key));
        int two(Count(2, key));
        int thr(Count(3, key));
        int fou(Count(4, key));
        int fiv(Count(5, key));
        int six(Count(6, key));
        int sev(Count(7, key));
        int eig(Count(8, key));
        int nin(Count(9, key));
        int ten(Count(10, key));
        int num(CardsFromKey(key));
        for (int i = 1; i < 11; ++i)
        {
            for (int j = i; j < 11; ++j)
            {
                if (i == 1)
                {
                    if (j == 10)
                    {
                        D[i][j] = Dealer_Natural();
                    }
                    else
                    {
                        D[i][j] = max(Surrender(),
                                      max(max(Double(),
                                              Split()),
                                          max(Stand(),
                                              Hit()))));
                    }
                    D[j][i] = D[i][j];
                    D[i][j] += Insurance();
                }
                else
                {
                    D[i][j] = max(Surrender(),
                                  max(max(Double(),
                                          Split()),
                                      max(Stand(),
                                          Hit()))));
                    D[j][i] = D[i][j];
                }
            }
        }

        return Dealer_Zero(

    }

}
#endif
