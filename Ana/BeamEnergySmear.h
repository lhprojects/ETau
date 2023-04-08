#pragma once
#include "Basics.h"

double const sqrts_sigma1 = 1.34E-3;
double const sqrts_sigma2 = 1.34E-3;

V4 SmearEnergySpread(V4 const &v4, double Ecms, Rand const &rnd)
{
    double const en_ = v4.E();
    double const px = v4.Px();
    double const py = v4.Py();
    double const pz_ = v4.Pz();

    double const delta1 = sqrts_sigma1 * rnd.r1;
    double const delta2 = sqrts_sigma2 * rnd.r2;
    double const beta = (delta1 - delta2) / 2;
    double en = en_ + beta * pz_;
    double pz = pz_ + beta * en_;
    en += 0.5 * (delta1 + delta2) * Ecms;

    return V4(px, py, pz, en);
}

