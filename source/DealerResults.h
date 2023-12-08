#ifndef DEALER_RESULTS_H
#define DEALER_RESULTS_H

#include "cards.h"
#include "DealerOdds.h"
#include "Wlt.h"

namespace Bj
{
    class DealerResults
    {
    public:

        DealerResults(bool aHitSoft17 = false);

        ~DealerResults();

        void Print();

        Wlt WinLoss(const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, const bool aNatural, const bool aIgnoreDealerBj);

        // DealerOdds Odds(const int deck);

        void Results(const int d1,const int d2, const int car, 
                     const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, 
                     double odd, const int sum);

    private:

        void DS12(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DS13(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DS14(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DS15(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DS16(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DS17(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);

        void DH04(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DH05(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DH06(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DH07(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DXH07(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DH08(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DXH08(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DH09(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DXH09(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DH10(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DXH10(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DH11(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DXH11(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DH12(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DXH12(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DH13(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DXH13(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DH14(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DXH14(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DH15(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DXH15(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);
        void DXH16(const int d1, const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla);


    private:
        void Scor(const int d1,const int d2, const int car, const int ds, const int ace, const int two, const int thr, const int fou, const int fiv, const int six, const int sev, const int eig, const int nin, const int ten, double odd, const int pla, const int sum);

        bool mDealerHitsS17;

        DealerOdds mOdds;
    };
}
#endif


/*
      if (ace) 
      {
         const double ace1 = odd * double(ace)/car;

         if (ace > 1)
         {
            const double ace2 = ace1 * double(ace-1)/(car-1);

            if (ace > 2)
            {
               const double ace3 = ace2 * double(ace-2)/(car-2);

               if (ace > 3)
               {
                  const double ace4 = ace3 * double(ace-3)/(car-3);

                  if (ace > 4)
                  {
                     const double ace5 = ace4 * double(ace-4)/(car-4);

                     if (ace > 5)
                     {
                        const double ace6 = ace5 * double(ace-5)/(car-5);
                        
                        if (ace > 6)
                        {
                           const double ace7 = ace6 * double(ace-6)/(car-6);

                           if (ace > 7)
                           {
                              const double ace8 = ace7 * double(ace-7)/(car-7);

                           }
                        }
                     }
                  }
               }
            }
         }
*/