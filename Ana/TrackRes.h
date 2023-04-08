#pragma once
#include "Basics.h"
#include <stddef.h>

double const TrackerR0 = 1.8;
double const TrackerZ0 = 4.7;

struct TrackRes
{
    double pars[6];
    double R;
    double Z;
    
    TrackRes(double R = TrackerR0,
    double Z = TrackerZ0) : R(R), Z(Z)
    {

        double lpars[] = { -6.53193064e+00, -1.70098932e-01, 7.13246936e-02,
            9.86062092e-04,
            -4.67288223e-04, 1.10435253e-05 };
        for (size_t i = 0; i < sizeof(lpars) / sizeof(double); ++i) {
            pars[i] = lpars[i];
        }
    }

    double res(V4 const& trk) const
    {
        if(1) {
            double const costhetac = cos(atan(2 * R / Z));
            double const sinthetac = sqrt(1 - costhetac * costhetac);
            double const xc = costhetac;
            double const xc2 = xc * xc;

            double const pt = trk.Pt();
            double const logpt = log(pt);
            double const b0 = pars[0] + logpt * pars[1] + logpt * logpt * pars[2];
            double const b1 = pars[3] + logpt * pars[4] + logpt * logpt * pars[5];

            double const costheta = trk.CosTheta();
            double const sintheta = sin(trk.Theta());
            double x = fabs(costheta);
            x = std::max(1E-6, x);
            double const x2 = x*x;
            double r = (fabs(x) < xc) ? R : sintheta / x *  (Z/2);
            r = std::max(1E-6, r);
            double res = (exp(b0) + b1 * x2) * Sqr(TrackerR0 / r);
            //printf("res: %f\n", res);
            return res;
        }
    }

    V4 smear(V4 const & from, double r) const
    {
        return from * (1 + res(from) * r);
    }
};
