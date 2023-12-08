
#include "DealerResults.h"
#include "Wlt.h"
#include "Divide.h"

void Bj::DealerResults::Scor(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla, const int sum)
{
#if 0
    if (car != (ace + two + thr + fou + fiv + six + sev + eig + nin + ten))
    {
        cout << "Remaining cards wrong" << endl;
        cout << "A: " << ace 
        << ", 2: " << two 
        << ", 3: " << thr 
        << ", 4: " << fou
        << ", 5: " << fiv 
        << ", 6: " << six 
        << ", 7: " << sev 
        << ", 8: " << eig 
        << ", 9: " << nin 
        << ", T: " << ten << " != " << car << endl;
        exit(1);
    }
    if (sum < 17)
    {
        cout << "Dealer didn't draw up to 17, only " << sum << endl;
        exit(1);
    }
#endif
	mOdds.mCards += (odd * ds);
    switch (sum)
    {
    case 17: mOdds.m17 += odd; break;
    case 18: mOdds.m18 += odd; break;
    case 19: mOdds.m19 += odd; break;
    case 20: mOdds.m20 += odd; break;
    case 21: mOdds.m21 += odd; break;
    default: mOdds.mBust += odd; break;
    }

}
Bj::DealerResults::DealerResults(bool aHitSoft17)
: mDealerHitsS17(aHitSoft17)
{
}
Bj::DealerResults::~DealerResults()
{
}
void Bj::DealerResults::Print()
{
    mOdds.print();
}
void Bj::DealerResults::Results(const int d1, const int d2, const int car, 
                                const int ace, const int two, const int thr, const int fou, const int fiv, 
								const int six, const int sev, const int eig, const int nin, const int ten, 
                                double odd, const int sum)
{
    if (d1 == 1 || d2 == 1)
    {                                            
        switch (d1 + d2 + 10)
        {
        case 21: Scor(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum,21); 
            mOdds.mNatural += odd; break;
        case 20: Scor(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum,20); break;
        case 19: Scor(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum,19); break;
        case 18: Scor(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum,18); break;
        case 17: DS17(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case 16: DS16(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case 15: DS15(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case 14: DS14(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case 13: DS13(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case 12: DS12(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        default: cout << "Bad dealer cards, sum: " << d1 + d2 << endl; exit(1); break;
        }
    }
    else
    {
        switch (d1 + d2)
        {
        case 20: Scor(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum,20); break;
        case 19: Scor(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum,19); break;
        case 18: Scor(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum,18); break;
        case 17: Scor(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum,17); break;
        case 16: DXH16(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case 15: DH15(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case 14: DH14(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case 13: DH13(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case 12: DH12(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case 11: DH11(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case 10: DH10(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case  9: DH09(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case  8: DH08(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case  7: DH07(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case  6: DH06(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case  5: DH05(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        case  4: DH04(d1,d2,car,2,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,sum); break;
        default: cout << "Bad dealer cards, sum: " << d1 + d2 << endl; exit(1); break;
        }
    }
}
Bj::Wlt Bj::DealerResults::WinLoss(const int ace, const int two, const int thr, const int fou, const int fiv, 
								   const int six, const int sev, const int eig, const int nin, const int ten, 
								   const bool aNatural, const bool aIgnoreDealerBj)
{
    const int cards(ace + two + thr + fou + fiv + six + sev + eig + nin + ten);
    int sum(ace + (2 * two) + (3 * thr) + (4 * fou) + (5 * fiv) + (6 * six) + (7 * sev) + (8 * eig) + (9 * nin) + (10 * ten));
    if (ace && (sum <= 11))
        sum += 10;

    return Wlt(mOdds, aNatural, sum, cards, aIgnoreDealerBj);
}
void Bj::DealerResults::DS12(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    if (ace) DS13(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][ace],pla);
    if (two) DS14(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla);
    if (thr) DS15(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla);
    if (fou) DS16(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla);
    if (fiv) DS17(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla);
    if (six) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla,18);
    if (sev) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla,19);
    if (eig) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla,20);
    if (nin) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla,21);
    if (ten) DH12(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla);
}
void Bj::DealerResults::DS13(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    if (ace) DS14(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][ace],pla);
    if (two) DS15(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla);
    if (thr) DS16(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla);
    if (fou) DS17(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla);
    if (fiv) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla,18);
    if (six) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla,19);
    if (sev) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla,20);
    if (eig) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla,21);
    if (nin) DH12(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla);
    if (ten) DH13(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla);
}
void Bj::DealerResults::DS14(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    if (ace) DS15(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][ace],pla);
    if (two) DS16(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla);
    if (thr) DS17(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla);
    if (fou) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla,18);
    if (fiv) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla,19);
    if (six) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla,20);
    if (sev) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla,21);
    if (eig) DH12(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla);
    if (nin) DH13(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla);
    if (ten) DH14(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla);
}
void Bj::DealerResults::DS15(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    if (ace) DS16(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][ace],pla);
    if (two) DS17(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla);
    if (thr) Scor(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla,18);
    if (fou) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla,19);
    if (fiv) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla,20);
    if (six) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla,21);
    if (sev) DH12(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla);
    if (eig) DH13(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla);
    if (nin) DH14(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla);
    if (ten) DH15(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla);
}
void Bj::DealerResults::DS16(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    if (ace) DS17(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][ace],pla);
    if (two) Scor(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla,18);
    if (thr) Scor(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla,19);
    if (fou) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla,20);
    if (fiv) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla,21);
    if (six) DH12(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla);
    if (sev) DH13(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla);
    if (eig) DH14(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla);
    if (nin) DH15(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla);
    if (ten) DXH16(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla);
}
void Bj::DealerResults::DS17(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    if (mDealerHitsS17)
    {
        if (ace) Scor(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][ace],pla,18);
        if (two) Scor(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla,19);
        if (thr) Scor(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla,20);
        if (fou) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla,21);
        if (fiv) DH12(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla);
        if (six) DH13(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla);
        if (sev) DH14(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla);
        if (eig) DH15(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla);
        if (nin) DXH16(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla);
        if (ten) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla,17);
    }
    else
        Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd,pla,17);
}
void Bj::DealerResults::DXH07(const int d1, const int d2, const int car, const int ds, 
							  const int ace, const int two, const int thr, const int fou, const int fiv, 
							  const int six, const int sev, const int eig, const int nin, const int ten, 
							  double odd, const int pla)
{
    const int s =  7;
    if (ten) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla,s+10);
}
void Bj::DealerResults::DH08(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    if (ace)
    {
        const double ace1 = odd * Bj::Divide()[car][ace];
        // combo A terminations
        Scor(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,ace1,pla,19);

        if (two)
        {
            const double ace1two1 = ace1 * Bj::Divide()[car-1][two];
            // combo 2A terminations
            Scor(d1,d2,car-2,ds+2,ace-1,two-1,thr,fou,fiv,six,sev,eig,nin,ten,ace1two1,pla,21);

            if (thr)
            {
                const double ace1two1thr1 = ace1two1 * Bj::Divide()[car-2][thr];
                // combo 23A, 3A2, 32A terminations
                DXH14(d1,d2,car-3,ds+3,ace-1,two-1,thr-1,fou,fiv,six,sev,eig,nin,ten,3*ace1two1thr1,pla);
            }
            // combo 24A, 4A2, 42A terminations
            if (fou) DXH15(d1,d2,car-3,ds+3,ace-1,two-1,thr,fou-1,fiv,six,sev,eig,nin,ten,3*ace1two1*Bj::Divide()[car-2][fou],pla);
            // combo 25A, 5A2, 52A terminations
            if (fiv) DXH16(d1,d2,car-3,ds+3,ace-1,two-1,thr,fou,fiv-1,six,sev,eig,nin,ten,3*ace1two1*Bj::Divide()[car-2][fiv],pla);

            if (two > 1)
            {
                const double ace1two2 = ace1two1 * Bj::Divide()[car-2][two-1];
                // combo 22A - terminations
                DXH13(d1,d2,car-3,ds+3,ace-1,two-2,thr,fou,fiv,six,sev,eig,nin,ten,ace1two2,pla);
                // combo 22A3, 223A, 23A2, 232A, 3A22, 32A2, 322A - terminations
                if (thr) DXH16(d1,d2,car-4,ds+4,ace-1,two-2,thr-1,fou,fiv,six,sev,eig,nin,ten,7*ace1two2*Bj::Divide()[car-3][thr],pla);

                if (two > 2)
                {
                    const double ace1two3 = ace1two2 * Bj::Divide()[car-3][two-2];
                    // combo 22A2, 222A - terminations
                    DXH15(d1,d2,car-4,ds+4,ace-1,two-3,thr,fou,fiv,six,sev,eig,nin,ten,2*ace1two3,pla);
                }
            }
        }
        if (thr)
        {
            const double ace1thr1 = ace1 * Bj::Divide()[car-1][thr];
            // combo 3A terminations
            DXH12(d1,d2,car-2,ds+2,ace-1,two,thr-1,fou,fiv,six,sev,eig,nin,ten,ace1thr1,pla);

            // combo 3A4, 34A, 4A3, 43A
            if (fou) DXH16(d1,d2,car-3,ds+3,ace-1,two,thr-1,fou-1,fiv,six,sev,eig,nin,ten,4*ace1thr1*Bj::Divide()[car-2][fou],pla);

            if (thr > 1)
            {
                const double ace1thr2 = ace1thr1 * Bj::Divide()[car-2][thr-1];
                // combo 3A3, 33A - terminations
                DXH15(d1,d2,car-3,ds+3,ace-1,two,thr-2,fou,fiv,six,sev,eig,nin,ten,2*ace1thr2,pla);
            }
        }
        // combo 4A terminations
        if (fou) DXH13(d1,d2,car-2,ds+2,ace-1,two,thr,fou-1,fiv,six,sev,eig,nin,ten,ace1*Bj::Divide()[car-1][fou],pla);
        // combo 5A terminations
        if (fiv) DXH14(d1,d2,car-2,ds+2,ace-1,two,thr,fou,fiv-1,six,sev,eig,nin,ten,ace1*Bj::Divide()[car-1][fiv],pla);
        // combo 6A terminations
        if (six) DXH15(d1,d2,car-2,ds+2,ace-1,two,thr,fou,fiv,six-1,sev,eig,nin,ten,ace1*Bj::Divide()[car-1][six],pla);
        // combo 7A terminations
        if (sev) DXH16(d1,d2,car-2,ds+2,ace-1,two,thr,fou,fiv,six,sev-1,eig,nin,ten,ace1*Bj::Divide()[car-1][sev],pla);

        if (ace > 1)
        {
            const double ace2 = ace1 * Bj::Divide()[car-1][ace-1];
            // don't need combo AA

            if (two)
            {
                const double ace2two1 = ace2 * Bj::Divide()[car-2][two];
                // don't need combo 2AA
                if (thr)
                {
                    const double ace2two1thr1 = ace2two1*Bj::Divide()[car-3][thr];
                    // combo 23AA, 3AA2, 3A2A, 32AA terminations
                    DXH15(d1,d2,car-4,ds+4,ace-2,two-1,thr-1,fou,fiv,six,sev,eig,nin,ten,4*ace2two1thr1,pla);
                }
                // combo 24AA, 4AA2, 4A2A, 42AA terminations
                if (fou) DXH16(d1,d2,car-4,ds+4,ace-2,two-1,thr,fou-1,fiv,six,sev,eig,nin,ten,4*ace2two1*Bj::Divide()[car-3][fou],pla);

                if (two > 1)
                {
                    const double ace2two2 = ace2two1 * Bj::Divide()[car-3][two-1];
                    // combo 22AA terminations
                    DXH14(d1,d2,car-4,ds+4,ace-2,two-2,thr,fou,fiv,six,sev,eig,nin,ten,ace2two2,pla);
                    if (two > 2)
                    {
                        const double ace2two3 = ace2two2 * Bj::Divide()[car-4][two-2];
                        // combo 22AA2, 22A2A, 222AA terminations
                        DXH16(d1,d2,car-5,ds+5,ace-2,two-3,thr,fou,fiv,six,sev,eig,nin,ten,3*ace2two3,pla);
                    }
                }
            }

            if (thr)
            {
                const double ace2thr1 = ace2 * Bj::Divide()[car-2][thr];
                // combo 3AA terminations
                DXH13(d1,d2,car-3,ds+3,ace-2,two,thr-1,fou,fiv,six,sev,eig,nin,ten,ace2thr1,pla);

                if (thr > 1)
                {
                    const double ace2thr2 = ace2thr1 * Bj::Divide()[car-3][thr-1];
                    // combo 3AA3, 3A3A, 33AA - terminations
                    DXH16(d1,d2,car-4,ds+4,ace-2,two,thr-2,fou,fiv,six,sev,eig,nin,ten,3*ace2thr2,pla);
                }
            }

            // combo 4AA terminations
            if (fou) DXH14(d1,d2,car-3,ds+3,ace-2,two,thr,fou-1,fiv,six,sev,eig,nin,ten,ace2*Bj::Divide()[car-2][fou],pla);
            // combo 5AA terminations
            if (fiv) DXH15(d1,d2,car-3,ds+3,ace-2,two,thr,fou,fiv-1,six,sev,eig,nin,ten,ace2*Bj::Divide()[car-2][fiv],pla);
            // combo 6AA terminations
            if (six) DXH16(d1,d2,car-3,ds+3,ace-2,two,thr,fou,fiv,six-1,sev,eig,nin,ten,ace2*Bj::Divide()[car-2][six],pla);

            if (ace > 2)
            {
                const double ace3 = ace2 * Bj::Divide()[car-2][ace-2];

                if (two)
                {
                    const double ace3two1 = ace3 * Bj::Divide()[car-3][two];
                    /// don't need combo 2AAA
                    // combo 23AAA, 3AAA2, 3AA2A, 3A2AA, 32AAA terminations
                    if (thr) DXH16(d1,d2,car-5,ds+5,ace-3,two-1,thr-1,fou,fiv,six,sev,eig,nin,ten,5*ace3two1*Bj::Divide()[car-4][thr],pla);

                    if (two > 1)
                    {
                        const double ace3two2 = ace3two1 * Bj::Divide()[car-4][two-1];
                        // combo 22AAA terminations
                        DXH15(d1,d2,car-5,ds+5,ace-3,two-2,thr,fou,fiv,six,sev,eig,nin,ten,ace3two2,pla);
                    }
                }
                /// combo 3AAA
                if (thr) DXH14(d1,d2,car-4,ds+4,ace-3,two,thr-1,fou,fiv,six,sev,eig,nin,ten,ace3*Bj::Divide()[car-3][thr],pla);
                /// combo 4AAA
                if (fou) DXH15(d1,d2,car-4,ds+4,ace-3,two,thr,fou-1,fiv,six,sev,eig,nin,ten,ace3*Bj::Divide()[car-3][fou],pla);
                /// combo 5AAA
                if (fiv) DXH16(d1,d2,car-4,ds+4,ace-3,two,thr,fou,fiv-1,six,sev,eig,nin,ten,ace3*Bj::Divide()[car-3][fiv],pla);

                if (ace > 3)
                {
                    const double ace4 = ace3 * Bj::Divide()[car-3][ace-3];

                    if (two)
                    {
                        const double ace4two1 = ace4 * Bj::Divide()[car-4][two];
                        /// don't need combo 2AAAA

                        if (two > 1)
                        {
                            const double ace4two2 = ace4two1 * Bj::Divide()[car-5][two-1];
                            // combo 22AAAA terminations
                            DXH16(d1,d2,car-6,ds+6,ace-4,two-2,thr,fou,fiv,six,sev,eig,nin,ten,ace4two2,pla);
                        }
                    }

                    /// combo 3AAAA
                    if (thr) DXH15(d1,d2,car-5,ds+5,ace-4,two,thr-1,fou,fiv,six,sev,eig,nin,ten,ace4*Bj::Divide()[car-4][thr],pla);
                    /// combo 4AAAA
                    if (fou) DXH16(d1,d2,car-5,ds+5,ace-4,two,thr,fou-1,fiv,six,sev,eig,nin,ten,ace4*Bj::Divide()[car-4][fou],pla);

                    if (ace > 4)
                    {
                        const double ace5 = ace4 * Bj::Divide()[car-4][ace-4];
                        /// don't need combo 2AAAAA
                        /// combo 3AAAAA
                        if (thr) DXH16(d1,d2,car-6,ds+6,ace-5,two,thr-1,fou,fiv,six,sev,eig,nin,ten,ace5*Bj::Divide()[car-5][thr],pla);

                        if (ace > 5)
                        {
                            const double ace6 = ace5 * Bj::Divide()[car-5][ace-5];
                            /// don't need combo 2AAAAAA
                        }
                    }
                }
            }
        }
    }
    if (two)
    {
        const double two1 = odd * Bj::Divide()[car][two];
        // combo 2 ternminations
        DXH10(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,two1,pla);
        if (thr)
        {
            const double two1thr1 = two1*Bj::Divide()[car-1][thr];
            // combo 23, 32 terminations
            DXH13(d1,d2,car-2,ds+2,ace,two-1,thr-1,fou,fiv,six,sev,eig,nin,ten,2*two1thr1,pla);
            if (thr > 1)
            {
                const double two1thr2 = two1thr1 * Bj::Divide()[car-2][thr-1];
                // combo 233, 332, 323 terminations
                DXH16(d1,d2,car-3,ds+3,ace,two-1,thr-2,fou,fiv,six,sev,eig,nin,ten,3*two1thr2,pla);
            }
        }
        // combo 24, 42 terminations
        if (fou) DXH14(d1,d2,car-2,ds+2,ace,two-1,thr,fou-1,fiv,six,sev,eig,nin,ten,2*two1*Bj::Divide()[car-1][fou],pla);
        // combo 25, 52 terminations
        if (fiv) DXH15(d1,d2,car-2,ds+2,ace,two-1,thr,fou,fiv-1,six,sev,eig,nin,ten,2*two1*Bj::Divide()[car-1][fiv],pla);
        // combo 26, 62 terminations
        if (six) DXH16(d1,d2,car-2,ds+2,ace,two-1,thr,fou,fiv,six-1,sev,eig,nin,ten,2*two1*Bj::Divide()[car-1][six],pla);

        if (two > 1)
        {
            const double two2 = two1 * Bj::Divide()[car-1][two-1];
            // combo 22 terminations
            DXH12(d1,d2,car-2,ds+2,ace,two-2,thr,fou,fiv,six,sev,eig,nin,ten,two2,pla);
            // combo 223, 232, 322 terminations
            if (thr) DXH15(d1,d2,car-3,ds+3,ace,two-2,thr-1,fou,fiv,six,sev,eig,nin,ten,3*two2*Bj::Divide()[car-2][thr],pla);
            // combo 224, 242, 422 terminations
            if (fou) DXH16(d1,d2,car-3,ds+3,ace,two-2,thr,fou-1,fiv,six,sev,eig,nin,ten,3*two2*Bj::Divide()[car-2][fou],pla);

            if (two > 2)
            {
                const double two3 = two2*Bj::Divide()[car-2][two-2];
                // combo 222 terminations
                DXH14(d1,d2,car-3,ds+3,ace,two-3,thr,fou,fiv,six,sev,eig,nin,ten,two3,pla);
                // combo 2222 
                if (two > 3) DXH16(d1,d2,car-4,ds+4,ace,two-4,thr,fou,fiv,six,sev,eig,nin,ten,two3*Bj::Divide()[car-3][two-3],pla);
            }
        }
    }
    if (thr)
    {
        const double thr1 = odd * Bj::Divide()[car][thr];
        // combo 3 terminations
        DXH11(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,thr1,pla);
        // combo 34, 43 terminations
        if (fou) DXH15(d1,d2,car-2,ds+2,ace,two,thr-1,fou-1,fiv,six,sev,eig,nin,ten,2*thr1*Bj::Divide()[car-1][fou],pla);
        // combo 35, 53 terminations
        if (fiv) DXH16(d1,d2,car-2,ds+2,ace,two,thr-1,fou,fiv-1,six,sev,eig,nin,ten,2*thr1*Bj::Divide()[car-1][fiv],pla);
        // combo 33 terminations
        if (thr > 1) DXH14(d1,d2,car-2,ds+2,ace,two,thr-2,fou,fiv,six,sev,eig,nin,ten,thr1*Bj::Divide()[car-1][thr-1],pla);
    }

    if (fou)
    {
        const double fou1 = odd * Bj::Divide()[car][fou];
        // combo 4
        DXH12(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,fou1,pla);
        if (fou > 1)
        {
            const double fou2 = fou1 * Bj::Divide()[car-1][fou-1];
            // combo 44
            DXH16(d1,d2,car-2,ds+2,ace,two,thr,fou-2,fiv,six,sev,eig,nin,ten,fou2,pla);
        }
    }
    if (fiv) DXH13(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla);
    if (six) DXH14(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla);
    if (sev) DXH15(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla);

    if (eig) DXH16(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla);
    // our terminations 
    DXH08(d1,d2,car,ds,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,pla);
}
void Bj::DealerResults::DXH08(const int d1, const int d2, const int car, const int ds, 
							  const int ace, const int two, const int thr, const int fou, const int fiv, 
							  const int six, const int sev, const int eig, const int nin, const int ten, 
							  double odd, const int pla)
{
    const int s =  8;
    if (nin) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla,s+9);
    if (ten) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla,s+10);
}
void Bj::DealerResults::DXH09(const int d1, const int d2, const int car, const int ds, 
							  const int ace, const int two, const int thr, const int fou, const int fiv, 
							  const int six, const int sev, const int eig, const int nin, const int ten, 
							  double odd, const int pla)
{
    const int s = 9;
    if (eig) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla,s+8);
    if (nin) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla,s+9);
    if (ten) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla,s+10);
}
void Bj::DealerResults::DXH10(const int d1, const int d2, const int car, const int ds, 
							  const int ace, const int two, const int thr, const int fou, const int fiv, 
							  const int six, const int sev, const int eig, const int nin, const int ten, 
							  double odd, const int pla)
{
    const int s = 10;
    if (sev) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla,s+7);
    if (eig) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla,s+8);
    if (nin) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla,s+9);
    if (ten) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla,s+10);
}
void Bj::DealerResults::DH11(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    if (ace)
    {
        const double ace1 = odd * Bj::Divide()[car][ace];
        // combo A
        DXH12(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,ace1,pla);

        if (two)
        {
            const double ace1two1 = ace1 * Bj::Divide()[car-1][two];
            // combo A2, 2A terminations
            DXH14(d1,d2,car-2,ds+2,ace-1,two-1,thr,fou,fiv,six,sev,eig,nin,ten,2*ace1two1,pla);

            if (two > 1)
            {
                const double ace1two2 = ace1two1 * Bj::Divide()[car-2][two-1];
                // combo A22, 2A2, 22A - terminations
                DXH16(d1,d2,car-3,ds+3,ace-1,two-2,thr,fou,fiv,six,sev,eig,nin,ten,3*ace1two2,pla);
            }
        }
        if (thr)
        {
            const double ace1thr1 = ace1 * Bj::Divide()[car-1][thr];
            // combo A3, 3A terminations
            DXH15(d1,d2,car-2,ds+2,ace-1,two,thr-1,fou,fiv,six,sev,eig,nin,ten,2*ace1thr1,pla);
        }
        if (fou)
        {
            const double ace1fou1 = ace1 * Bj::Divide()[car-1][fou];
            // combo A4, 4A terminations
            DXH16(d1,d2,car-2,ds+2,ace-1,two,thr,fou-1,fiv,six,sev,eig,nin,ten,2*ace1fou1,pla);
        }

        if (ace > 1)
        {
            const double ace2 = ace1 * Bj::Divide()[car-1][ace-1];
            // combo AA
            DXH13(d1,d2,car-2,ds+2,ace-2,two,thr,fou,fiv,six,sev,eig,nin,ten,ace2,pla);

            if (two)
            {
                // combo AA2, A2A, 2AA - terminations
                DXH15(d1,d2,car-3,ds+3,ace-2,two-1,thr,fou,fiv,six,sev,eig,nin,ten,3*ace2*Bj::Divide()[car-2][two],pla);
            }
            if (thr)
            {
                // combo AA3, A3A, 3AA - terminations
                DXH16(d1,d2,car-3,ds+3,ace-2,two,thr-1,fou,fiv,six,sev,eig,nin,ten,3*ace2*Bj::Divide()[car-2][thr],pla);
            }

            if (ace > 2)
            {
                const double ace3 = ace2 * Bj::Divide()[car-2][ace-2];
                // combo AAA
                DXH14(d1,d2,car-3,ds+3,ace-3,two,thr,fou,fiv,six,sev,eig,nin,ten,ace3,pla);

                if (two)
                {
                    /// combo AAA2, AA2A, A2AA, 2AAA
                    DXH16(d1,d2,car-4,ds+4,ace-3,two-1,thr,fou,fiv,six,sev,eig,nin,ten,4*ace3*Bj::Divide()[car-3][two],pla);
                }

                if (ace > 3)
                {
                    const double ace4 = ace3 * Bj::Divide()[car-3][ace-3];
                    // combo AAAA
                    DXH15(d1,d2,car-4,ds+4,ace-4,two,thr,fou,fiv,six,sev,eig,nin,ten,ace4,pla);

                    if (ace > 4)
                    {
                        const double ace5 = ace4 * Bj::Divide()[car-4][ace-4];
                        // combo AAAAA
                        DXH16(d1,d2,car-5,ds+5,ace-5,two,thr,fou,fiv,six,sev,eig,nin,ten,ace5,pla);
                    }
                }
            }
        }
    }
    if (two)
    {
        const double two1 = odd * Bj::Divide()[car][two];
        // combo 2
        DXH13(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,two1,pla);

        if (two > 1)
        {
            const double two2 = two1 * Bj::Divide()[car-1][two-1];
            // combo 22 terminations
            DXH15(d1,d2,car-2,ds+2,ace,two-2,thr,fou,fiv,six,sev,eig,nin,ten,two2,pla);
        }
        if (thr)
        {
            const double two1thr1 = two1 * Bj::Divide()[car-1][thr];
            // combo 23, 32 terminations
            DXH16(d1,d2,car-2,ds+2,ace,two-1,thr-1,fou,fiv,six,sev,eig,nin,ten,2*two1thr1,pla);
        }
    }

    if (thr) DXH14(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla);
    if (fou) DXH15(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla);
    if (fiv) DXH16(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla);
    // our terminations 
    DXH11(d1,d2,car,ds,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,pla);
}
void Bj::DealerResults::DXH11(const int d1, const int d2, const int car, const int ds, 
							  const int ace, const int two, const int thr, const int fou, const int fiv, 
							  const int six, const int sev, const int eig, const int nin, const int ten, 
							  double odd, const int pla)
{
    const int s = 11;
    if (six) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla,s+6);
    if (sev) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla,s+7);
    if (eig) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla,s+8);
    if (nin) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla,s+9);
    if (ten) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla,s+10);
}
void Bj::DealerResults::DH12(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    const int s = 12;
    if (ace)
    {
        const double ace1 = odd * Bj::Divide()[car][ace];
        // combo A
        DXH13(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,ace1,pla);

        // combo A2, 2A
        if (two)
        {
            const double ace1two1 = ace1 * Bj::Divide()[car-1][two];
            DXH15(d1,d2,car-2,ds+2,ace-1,two-1,thr,fou,fiv,six,sev,eig,nin,ten,2*ace1two1,pla);
        }
        // combo A3, 3A terminations
        if (thr)
        {
            const double ace1thr1 = ace1 * Bj::Divide()[car-1][thr];
            DXH16(d1,d2,car-2,ds+2,ace-1,two,thr-1,fou,fiv,six,sev,eig,nin,ten,2*ace1thr1,pla);
        }

        if (ace > 1)
        {
            const double ace2 = ace1 * Bj::Divide()[car-1][ace-1];
            // combo AA
            DXH14(d1,d2,car-2,ds+2,ace-2,two,thr,fou,fiv,six,sev,eig,nin,ten,ace2,pla);

            // combo AA2, A2A, 2AA - terminations
            if (two)
            {
                DXH16(d1,d2,car-3,ds+3,ace-2,two-1,thr,fou,fiv,six,sev,eig,nin,ten,3*ace2*Bj::Divide()[car-2][two],pla);
            }

            if (ace > 2)
            {
                const double ace3 = ace2 * Bj::Divide()[car-2][ace-2];
                // combo AAA
                DXH15(d1,d2,car-3,ds+3,ace-3,two,thr,fou,fiv,six,sev,eig,nin,ten,ace3,pla);

                if (ace > 3)
                {
                    const double ace4 = ace3 * Bj::Divide()[car-3][ace-3];
                    // combo AAAA
                    DXH16(d1,d2,car-4,ds+4,ace-4,two,thr,fou,fiv,six,sev,eig,nin,ten,ace4,pla);

                }
            }
        }
    }

    // combo 22 terminations
    if (two)
    {
        const double two1 = odd * Bj::Divide()[car][two];
        DXH14(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,two1,pla);

        if (two > 1)
        {
            const double two2 = two1 * Bj::Divide()[car-1][two-1];
            DXH16(d1,d2,car-2,ds+2,ace,two-2,thr,fou,fiv,six,sev,eig,nin,ten,two2,pla);
        }
    }
    if (thr) DXH15(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla);
    if (fou) DXH16(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla);
    // our terminations 
    DXH12(d1,d2,car,ds,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,pla);
}
void Bj::DealerResults::DXH12(const int d1, const int d2, const int car, const int ds, 
							  const int ace, const int two, const int thr, const int fou, const int fiv, 
							  const int six, const int sev, const int eig, const int nin, const int ten, 
							  double odd, const int pla)
{
    const int s = 12;
    if (fiv) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla,s+5);
    if (six) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla,s+6);
    if (sev) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla,s+7);
    if (eig) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla,s+8);
    if (nin) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla,s+9);
    if (ten) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla,s+10);
}
void Bj::DealerResults::DH13(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    if (ace)
    {
        const double ace1 = odd * Bj::Divide()[car][ace];
        // combo A
        DXH14(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,ace1,pla);
        if (two)
        {
            const double ace1two1 = ace1 * Bj::Divide()[car-1][two];
            // combo A2, 2A -> 16
            DXH16(d1,d2,car-2,ds+2,ace-1,two-1,thr,fou,fiv,six,sev,eig,nin,ten,2*ace1two1,pla);
        }
        if (ace > 1)
        {
            const double ace2 = ace1 * Bj::Divide()[car-1][ace-1];
            // combo AA
            DXH15(d1,d2,car-2,ds+2,ace-2,two,thr,fou,fiv,six,sev,eig,nin,ten,ace2,pla);

            if (ace > 2)
            {
                const double ace3 = ace2 * Bj::Divide()[car-2][ace-2];
                // combo AAA
                DXH16(d1,d2,car-3,ds+3,ace-3,two,thr,fou,fiv,six,sev,eig,nin,ten,ace3,pla);
            }
        }
    }
    if (two) DXH15(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla);

    if (thr) DXH16(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla);
    DXH13(d1,d2,car,ds,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,pla);
}
void Bj::DealerResults::DXH13(const int d1, const int d2, const int car, const int ds, 
							  const int ace, const int two, const int thr, const int fou, const int fiv, 
							  const int six, const int sev, const int eig, const int nin, const int ten, 
							  double odd, const int pla)
{
    const int s = 13;
    if (fou) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla,s+4);
    if (fiv) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla,s+5);
    if (six) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla,s+6);
    if (sev) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla,s+7);
    if (eig) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla,s+8);
    if (nin) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla,s+9);
    if (ten) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla,s+10);
}
void Bj::DealerResults::DH14(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    if (ace)
    {
        const double ace1 = odd * Bj::Divide()[car][ace];
        DXH15(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,ace1,pla);
        if (ace > 1)
        {
            const double ace2 = ace1 * Bj::Divide()[car-1][ace-1];
            DXH16(d1,d2,car-2,ds+2,ace-2,two,thr,fou,fiv,six,sev,eig,nin,ten,ace2,pla);
        }
    }
    if (two)
    {
        DXH16(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla);
    }

    DXH14(d1,d2,car,ds,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,pla);
}
void Bj::DealerResults::DXH14(const int d1, const int d2, const int car, const int ds, 
							  const int ace, const int two, const int thr, const int fou, const int fiv, 
							  const int six, const int sev, const int eig, const int nin, const int ten, 
							  double odd, const int pla)
{
    const int s = 14;
    if (thr) Scor(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla,s+3);
    if (fou) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla,s+4);
    if (fiv) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla,s+5);
    if (six) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla,s+6);
    if (sev) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla,s+7);
    if (eig) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla,s+8);
    if (nin) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla,s+9);
    if (ten) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla,s+10);
}
void Bj::DealerResults::DH15(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    if (ace) DXH16(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][ace],pla);
    DXH15(d1,d2,car,ds,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,pla);
}
void Bj::DealerResults::DXH15(const int d1, const int d2, const int car, const int ds, 
							  const int ace, const int two, const int thr, const int fou, const int fiv, 
							  const int six, const int sev, const int eig, const int nin, const int ten, 
							  double odd, const int pla)
{
    const int s = 15;
    if (two) Scor(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla,s+2);
    if (thr) Scor(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla,s+3);
    if (fou) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla,s+4);
    if (fiv) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla,s+5);
    if (six) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla,s+6);
    if (sev) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla,s+7);
    if (eig) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla,s+8);
    if (nin) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla,s+9);
    if (ten) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla,s+10);
}
void Bj::DealerResults::DXH16(const int d1, const int d2, const int car, const int ds, 
							  const int ace, const int two, const int thr, const int fou, const int fiv, 
							  const int six, const int sev, const int eig, const int nin, const int ten, 
							  double odd, const int pla)
{
    const int s = 16;
    if (ace) Scor(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][ace],pla,s+1);
    if (two) Scor(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla,s+2);
    if (thr) Scor(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla,s+3);
    if (fou) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla,s+4);
    if (fiv) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla,s+5);
    if (six) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla,s+6);
    if (sev) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla,s+7);
    if (eig) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla,s+8);
    if (nin) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla,s+9);
    if (ten) Scor(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla,s+10);
}
void Bj::DealerResults::DH04(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    if (ace) DS15(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][ace],pla);
    if (two) DH06(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla);
    if (thr) DH07(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla);
    if (fou) DH08(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla);
    if (fiv) DH09(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla);
    if (six) DH10(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla);
    if (sev) DH11(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla);
    if (eig) DH12(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla);
    if (nin) DH13(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla);
    if (ten) DH14(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla);
}
void Bj::DealerResults::DH05(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    if (ace) DS16(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][ace],pla);
    if (two) DH07(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla);
    if (thr) DH08(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla);
    if (fou) DH09(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla);
    if (fiv) DH10(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla);
    if (six) DH11(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla);
    if (sev) DH12(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla);
    if (eig) DH13(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla);
    if (nin) DH14(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla);
    if (ten) DH15(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla);
}
void Bj::DealerResults::DH06(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    const int s =  6;
    if (ace) DS17(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][ace],pla);
    if (two) DH08(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla);
    if (thr) DH09(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla);
    if (fou) DH10(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla);
    if (fiv) DH11(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla);
    if (six) DH12(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla);
    if (sev) DH13(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla);
    if (eig) DH14(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla);
    if (nin) DH15(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla);
    if (ten) DXH16(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin,ten-1,odd*Bj::Divide()[car][ten],pla);
}
void Bj::DealerResults::DH07(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    const int s =  7;
    if (ace) Scor(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][ace],pla,s+11);
    if (two) DH09(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][two],pla);
    if (thr) DH10(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][thr],pla);
    if (fou) DH11(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla);
    if (fiv) DH12(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla);
    if (six) DH13(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla);
    if (sev) DH14(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla);
    if (eig) DH15(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig-1,nin,ten,odd*Bj::Divide()[car][eig],pla);
    if (nin) DXH16(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev,eig,nin-1,ten,odd*Bj::Divide()[car][nin],pla);
    // our terminations 
    DXH07(d1,d2,car,ds,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,pla);
}
void Bj::DealerResults::DH09(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    const int s = 9;
    if (ace)
    {
        const double ace1 = odd * Bj::Divide()[car][ace];
        // combo A ternminations
        Scor(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,ace1,pla,s+11);

        // combo 2A terminations
        if (two) DXH12(d1,d2,car-2,ds+2,ace-1,two-1,thr,fou,fiv,six,sev,eig,nin,ten,ace1*Bj::Divide()[car-1][two],pla);
        // combo 3A terminations
        if (thr) DXH13(d1,d2,car-2,ds+2,ace-1,two,thr-1,fou,fiv,six,sev,eig,nin,ten,ace1*Bj::Divide()[car-1][thr],pla);
        // combo 4A terminations
        if (fou) DXH14(d1,d2,car-2,ds+2,ace-1,two,thr,fou-1,fiv,six,sev,eig,nin,ten,ace1*Bj::Divide()[car-1][fou],pla);
        // combo 5A terminations
        if (fiv) DXH15(d1,d2,car-2,ds+2,ace-1,two,thr,fou,fiv-1,six,sev,eig,nin,ten,ace1*Bj::Divide()[car-1][fiv],pla);
        // combo 6A terminations
        if (six) DXH16(d1,d2,car-2,ds+2,ace-1,two,thr,fou,fiv,six-1,sev,eig,nin,ten,ace1*Bj::Divide()[car-1][six],pla);

        if (ace > 1)
        {
            const double ace2 = ace1 * Bj::Divide()[car-1][ace-1];
            // combo 3AA terminations
            if (thr) DXH14(d1,d2,car-3,ds+3,ace-2,two,thr-1,fou,fiv,six,sev,eig,nin,ten,ace2*Bj::Divide()[car-2][thr],pla);
            // combo 4AA terminations
            if (fou) DXH15(d1,d2,car-3,ds+3,ace-2,two,thr,fou-1,fiv,six,sev,eig,nin,ten,ace2*Bj::Divide()[car-2][fou],pla);
            // combo 5AA terminations
            if (fiv) DXH16(d1,d2,car-3,ds+3,ace-2,two,thr,fou,fiv-1,six,sev,eig,nin,ten,ace2*Bj::Divide()[car-2][fiv],pla);

            if (two)
            {
                const double ace2two1 = ace2 * Bj::Divide()[car-2][two];
                // combo 2AA terminations
                DXH13(d1,d2,car-3,ds+3,ace-2,two-1,thr,fou,fiv,six,sev,eig,nin,ten,ace2two1,pla);
                // combo 2AA3, 2A3A, 23AA, 3AA2, 3A2A, 32AA terminations
                if (thr) DXH16(d1,d2,car-4,ds+4,ace-2,two-1,thr-1,fou,fiv,six,sev,eig,nin,ten,6*ace2two1*Bj::Divide()[car-3][thr],pla);

                if (two > 1)
                {
                    const double ace2two2 = ace2two1 * Bj::Divide()[car-3][two-1];
                    // combo 2AA2, 2A2A, 22AA - terminations
                    DXH15(d1,d2,car-4,ds+4,ace-2,two-2,thr,fou,fiv,six,sev,eig,nin,ten,3*ace2two2,pla);
                }
            }

            if (ace > 2)
            {
                const double ace3 = ace2 * Bj::Divide()[car-2][ace-2];
                /// combo 3AAA
                if (thr) DXH15(d1,d2,car-4,ds+4,ace-3,two,thr-1,fou,fiv,six,sev,eig,nin,ten,ace3*Bj::Divide()[car-3][thr],pla);
                /// combo 4AAA
                if (fou) DXH16(d1,d2,car-4,ds+4,ace-3,two,thr,fou-1,fiv,six,sev,eig,nin,ten,ace3*Bj::Divide()[car-3][fou],pla);

                if (two)
                {
                    const double ace3two1 = ace3 * Bj::Divide()[car-3][two];
                    /// combo 2AAA
                    DXH14(d1,d2,car-4,ds+4,ace-3,two-1,thr,fou,fiv,six,sev,eig,nin,ten,ace3two1,pla);

                    if (two > 1)
                    {
                        const double ace3two2 = ace3two1 * Bj::Divide()[car-4][two-1];
                        // combo 2AAA2, 2AA2A, 2A2AA, 22AAA - terminations
                        DXH16(d1,d2,car-5,ds+5,ace-3,two-2,thr,fou,fiv,six,sev,eig,nin,ten,4*ace3two2,pla);
                    }
                }

                if (ace > 3)
                {
                    const double ace4 = ace3 * Bj::Divide()[car-3][ace-3];
                    /// combo 2AAAA
                    if (two) DXH15(d1,d2,car-5,ds+5,ace-4,two-1,thr,fou,fiv,six,sev,eig,nin,ten,ace4*Bj::Divide()[car-4][two],pla);
                    /// combo 3AAAA
                    if (thr) DXH16(d1,d2,car-5,ds+5,ace-4,two,thr-1,fou,fiv,six,sev,eig,nin,ten,ace4*Bj::Divide()[car-4][thr],pla);

                    if (ace > 4)
                    {
                        const double ace5 = ace4 * Bj::Divide()[car-4][ace-4];
                        /// combo 2AAAAA
                        if (two) DXH16(d1,d2,car-6,ds+6,ace-5,two-1,thr,fou,fiv,six,sev,eig,nin,ten,ace5*Bj::Divide()[car-5][two],pla);
                    }
                }
            }
        }
        if (two)
        {
            const double ace1two1 = ace1 * Bj::Divide()[car-1][two];
            // combo 2A3, 23A, 3A2, 32A terminations
            if (thr) DXH15(d1,d2,car-3,ds+3,ace-1,two-1,thr-1,fou,fiv,six,sev,eig,nin,ten,4*ace1two1*Bj::Divide()[car-2][thr],pla);
            // combo 2A4, 24A, 4A2, 42A terminations
            if (fou) DXH16(d1,d2,car-3,ds+3,ace-1,two-1,thr,fou-1,fiv,six,sev,eig,nin,ten,4*ace1two1*Bj::Divide()[car-2][fou],pla);

            if (two > 1)
            {
                const double ace1two2 = ace1two1 * Bj::Divide()[car-2][two-1];
                // combo 2A2, 22A - terminations
                DXH14(d1,d2,car-3,ds+3,ace-1,two-2,thr,fou,fiv,six,sev,eig,nin,ten,2*ace1two2,pla);
                if (two > 2)
                {
                    const double ace1two3 = ace1two2 * Bj::Divide()[car-3][two-2];
                    // combo 2A22, 22A2, 222A - terminations
                    DXH16(d1,d2,car-4,ds+4,ace-1,two-3,thr,fou,fiv,six,sev,eig,nin,ten,3*ace1two3,pla);
                }
            }
        }
        if (thr)
        {
            const double ace1thr1 = ace1 * Bj::Divide()[car-1][thr];
            if (thr > 1)
            {
                const double ace1thr2 = ace1thr1 * Bj::Divide()[car-2][thr-1];
                // combo 3A3, 33A - terminations
                DXH16(d1,d2,car-3,ds+3,ace-1,two,thr-2,fou,fiv,six,sev,eig,nin,ten,2*ace1thr2,pla);
            }
        }
    }
    if (two)
    {
        const double two1 = odd * Bj::Divide()[car][two];
        // combo 2 ternminations
        DXH11(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,two1,pla);
        // combo 23, 32 terminations
        if (thr) DXH14(d1,d2,car-2,ds+2,ace,two-1,thr-1,fou,fiv,six,sev,eig,nin,ten,two1*2*Bj::Divide()[car-1][thr],pla);
        // combo 24, 42 terminations
        if (fou) DXH15(d1,d2,car-2,ds+2,ace,two-1,thr,fou-1,fiv,six,sev,eig,nin,ten,two1*2*Bj::Divide()[car-1][fou],pla);
        // combo 25, 52 terminations
        if (fiv) DXH16(d1,d2,car-2,ds+2,ace,two-1,thr,fou,fiv-1,six,sev,eig,nin,ten,two1*2*Bj::Divide()[car-1][fiv],pla);

        if (two > 1)
        {
            const double two2 = two1 * Bj::Divide()[car-1][two-1];
            // combo 22 terminations
            DXH13(d1,d2,car-2,ds+2,ace,two-2,thr,fou,fiv,six,sev,eig,nin,ten,two2,pla);
            // combo 223, 232, 322 terminations
            if (thr) DXH16(d1,d2,car-3,ds+3,ace,two-2,thr-1,fou,fiv,six,sev,eig,nin,ten,3*two2*Bj::Divide()[car-2][thr],pla);
            // combo 222 terminations
            if (two > 2) DXH15(d1,d2,car-3,ds+3,ace,two-3,thr,fou,fiv,six,sev,eig,nin,ten,two2*Bj::Divide()[car-2][two-2],pla);
        }
    }
    if (thr)
    {
        const double thr1 = odd * Bj::Divide()[car][thr];
        // combo 3 terminations
        DXH12(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,thr1,pla);
        // combo 34, 43 terminations
        if (fou) DXH16(d1,d2,car-2,ds+2,ace,two,thr-1,fou-1,fiv,six,sev,eig,nin,ten,thr1*2*Bj::Divide()[car-1][fou],pla);
        // combo 33 terminations
        if (thr > 1) DXH15(d1,d2,car-2,ds+2,ace,two,thr-2,fou,fiv,six,sev,eig,nin,ten,thr1*Bj::Divide()[car-1][thr-1],pla);
    }
    if (fou) DXH13(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla);
    if (fiv) DXH14(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla);
    if (six) DXH15(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla);
    if (sev) DXH16(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six,sev-1,eig,nin,ten,odd*Bj::Divide()[car][sev],pla);
    // our terminations 
    DXH09(d1,d2,car,ds,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,pla);
}
void Bj::DealerResults::DH10(const int d1, const int d2, const int car, const int ds, 
							 const int ace, const int two, const int thr, const int fou, const int fiv, 
							 const int six, const int sev, const int eig, const int nin, const int ten, 
							 double odd, const int pla)
{
    const int s = 10;
    if (ace)
    {
        const double ace1 = odd * Bj::Divide()[car][ace];
        // combo A ternminations
        Scor(d1,d2,car-1,ds+1,ace-1,two,thr,fou,fiv,six,sev,eig,nin,ten,ace1,pla,s+11);

        // combo 2A terminations
        if (two) DXH13(d1,d2,car-2,ds+2,ace-1,two-1,thr,fou,fiv,six,sev,eig,nin,ten,ace1*Bj::Divide()[car-1][two],pla);
        // combo 3A terminations
        if (thr) DXH14(d1,d2,car-2,ds+2,ace-1,two,thr-1,fou,fiv,six,sev,eig,nin,ten,ace1*Bj::Divide()[car-1][thr],pla);
        // combo 4A terminations
        if (fou) DXH15(d1,d2,car-2,ds+2,ace-1,two,thr,fou-1,fiv,six,sev,eig,nin,ten,ace1*Bj::Divide()[car-1][fou],pla);
        // combo 5A terminations
        if (fiv) DXH16(d1,d2,car-2,ds+2,ace-1,two,thr,fou,fiv-1,six,sev,eig,nin,ten,ace1*Bj::Divide()[car-1][fiv],pla);

        if (ace > 1)
        {
            const double ace2 = ace1 * Bj::Divide()[car-1][ace-1];
            if (two)
            {
                const double ace2two1 = ace2 * Bj::Divide()[car-2][two];
                // combo 2AA terminations
                DXH14(d1,d2,car-3,ds+3,ace-2,two-1,thr,fou,fiv,six,sev,eig,nin,ten,ace2two1,pla);
                if (two > 1)
                {
                    const double ace2two2 = ace2two1 * Bj::Divide()[car-3][two-1];
                    // combo 2AA2, 2A2A, 22AA - terminations
                    DXH16(d1,d2,car-4,ds+4,ace-2,two-2,thr,fou,fiv,six,sev,eig,nin,ten,3*ace2two2,pla);
                }
            }
            // combo 3AA terminations
            if (thr) DXH15(d1,d2,car-3,ds+3,ace-2,two,thr-1,fou,fiv,six,sev,eig,nin,ten,ace2*Bj::Divide()[car-2][thr],pla);
            // combo 4AA terminations
            if (fou) DXH16(d1,d2,car-3,ds+3,ace-2,two,thr,fou-1,fiv,six,sev,eig,nin,ten,ace2*Bj::Divide()[car-2][fou],pla);

            if (ace > 2)
            {
                const double ace3 = ace2 * Bj::Divide()[car-2][ace-2];
                /// combo 2AAA
                if (two) DXH15(d1,d2,car-4,ds+4,ace-3,two-1,thr,fou,fiv,six,sev,eig,nin,ten,ace3*Bj::Divide()[car-3][two],pla);
                /// combo 3AAA
                if (thr) DXH16(d1,d2,car-4,ds+4,ace-3,two,thr-1,fou,fiv,six,sev,eig,nin,ten,ace3*Bj::Divide()[car-3][thr],pla);
                if (ace > 3)
                {
                    const double ace4 = ace3 * Bj::Divide()[car-3][ace-3];
                    /// combo 2AAAA
                    if (two) DXH16(d1,d2,car-5,ds+5,ace-4,two-1,thr,fou,fiv,six,sev,eig,nin,ten,ace4*Bj::Divide()[car-4][two],pla);
                }
            }
        }
        // combo 2A2, 22A - terminations
        if (two > 1)
        {
            const double odds = 2 * ace1 * Bj::Divide()[car-1][two] * Bj::Divide()[car-2][two-1];
            DXH15(d1,d2,car-3,ds+3,ace-1,two-2,thr,fou,fiv,six,sev,eig,nin,ten,odds,pla);
        }
        // combo 2A3, 23A, 3A2, 32A - terminations
        if (two && thr)
        {
            const double odds = 4 * ace1 * Bj::Divide()[car-1][two] * Bj::Divide()[car-2][thr];
            DXH16(d1,d2,car-3,ds+3,ace-1,two-1,thr-1,fou,fiv,six,sev,eig,nin,ten,odds,pla);
        }
    }
    if (two)
    {
        const double two1 = odd * Bj::Divide()[car][two];
        // combo 2 ternminations
        DXH12(d1,d2,car-1,ds+1,ace,two-1,thr,fou,fiv,six,sev,eig,nin,ten,two1,pla);
        // combo 23, 32 terminations
        if (thr) DXH15(d1,d2,car-2,ds+2,ace,two-1,thr-1,fou,fiv,six,sev,eig,nin,ten,two1*2*Bj::Divide()[car-1][thr],pla);
        // combo 24, 42 terminations
        if (fou) DXH16(d1,d2,car-2,ds+2,ace,two-1,thr,fou-1,fiv,six,sev,eig,nin,ten,two1*2*Bj::Divide()[car-1][fou],pla);

        if (two > 1)
        {
            const double two2 = two1 * Bj::Divide()[car-1][two-1];
            // combo 22 terminations
            DXH14(d1,d2,car-2,ds+2,ace,two-2,thr,fou,fiv,six,sev,eig,nin,ten,two2,pla);
            // combo 222 terminations
            if (two > 2) DXH16(d1,d2,car-3,ds+3,ace,two-3,thr,fou,fiv,six,sev,eig,nin,ten,two2*Bj::Divide()[car-2][two-2],pla);
        }
    }
    if (thr)
    {
        const double thr1 = odd * Bj::Divide()[car][thr];
        // combo 3 terminations
        DXH13(d1,d2,car-1,ds+1,ace,two,thr-1,fou,fiv,six,sev,eig,nin,ten,thr1,pla);
        // combo 33 terminations
        if (thr > 1) DXH16(d1,d2,car-2,ds+2,ace,two,thr-2,fou,fiv,six,sev,eig,nin,ten,thr1*Bj::Divide()[car-1][thr-1],pla);
    }
    if (fou) DXH14(d1,d2,car-1,ds+1,ace,two,thr,fou-1,fiv,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fou],pla);
    if (fiv) DXH15(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv-1,six,sev,eig,nin,ten,odd*Bj::Divide()[car][fiv],pla);
    if (six) DXH16(d1,d2,car-1,ds+1,ace,two,thr,fou,fiv,six-1,sev,eig,nin,ten,odd*Bj::Divide()[car][six],pla);
    // our terminations 
    DXH10(d1,d2,car,ds,ace,two,thr,fou,fiv,six,sev,eig,nin,ten,odd,pla);
}

