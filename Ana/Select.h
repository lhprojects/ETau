#pragma once
#include "Basics.h"

// return True if pass all selection
bool Select(V4 e1, V4 e2, double Ecms)
{

    double en = (e1 + e2).E();
    double px = (e1 + e2).Px();
    double py = (e1 + e2).Py();
    double pz = (e1 + e2).Pz();
    if (e1[0] == 0)
        return false;
    if (e2[0] == 0)
        return false;
    if (sqrt(px * px + py * py) < 20)
        return false;
    TLorentzVector v4(px, py, pz, en);
    TLorentzVector inc(0, 0, 0, Ecms);
    if (v4.M() < 80 || v4.M() > 100)
        return false;
    if ((inc - v4).M() < 120 && (inc - v4).M() > 150)
        return false;

    double phi = e1.DeltaPhi(e2);
    if (phi > 175)
        return false;

    return true;
}

