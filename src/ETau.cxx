
#include <stdio.h>

//#include <StdHepIter.h>
#include <IOIMPL/LCFactory.h>
#include <IO/LCReader.h>
#include <EVENT/LCEvent.h>
#include <lcio.h>
#include "IMPL/LCEventImpl.h"
#include "IMPL/MCParticleImpl.h"
#include "IMPL/ReconstructedParticleImpl.h"
#include "IMPL/LCRunHeaderImpl.h"
#include "UTIL/LCStdHepRdr.h"
#include "UTIL/LCTOOLS.h"
#include "marlin/DataSourceProcessor.h"
#include "marlin/ProcessorMgr.h"

#include <TLorentzVector.h>
#include <TGraph.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TH2D.h>
#include <exception>
#include <TLegend.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TFile.h>
#include <TTree.h>

using namespace lcio;

#include <dirent.h>
static bool endsWith(const std::string& str, const std::string& suffix)
{
            return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}

std::vector<std::string> files(char const *path, char const *ext) {
   std::vector<std::string> result;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if(endsWith(ent->d_name, ext)) {
                result.push_back(std::string(path) + "/"+ ent->d_name);
            } 
        }
        closedir (dir);
    } else {
        throw "someting wrong!\n";
    }
    return result;
}

double Rho(double const *p) {
    return sqrt(p[0]*p[0] + p[1]*p[1] + p[2]*p[2]);
}
double Dot(double const *p1, double const *p2) {
    return p1[0]*p2[0] + p1[1]*p2[1] + p1[2]*p2[2];
}

double Angle(double const *p1, double const *p2) {

    double rho1 = Rho(p1);
    double rho2 = Rho(p2);

    double costheta = Dot(p1, p2)/(rho1*rho2);
    if(costheta < -1) {
        costheta = -1;
    } else if(costheta > 1) {
        costheta = 1;
    }
    double theta = acos(costheta);
    return theta;
}

using namespace std;

bool BeforeECal(double const *r) {
    //return true;
    double rho = sqrt(r[0]*r[0] + r[1]*r[1]);
    if(rho < 1800/2 && fabs(r[2]) < 2300/2) {
        return true;
    }
    return false;
}

bool BeforeECal2(double const *r) {
    double rho = sqrt(r[0]*r[0] + r[1]*r[1]);
    if(rho < 2000 && fabs(r[2]) < 2500) {
        return true;
    }
    return false;
}

void CollectBS2(double *rx, double *ry, double *rz, double *en, int &n, int nmax, MCParticle *elec, int pdg) {

    if(!elec || abs(elec->getPDG()) != pdg) return;
    if(!BeforeECal2(elec->getEndpoint())) {
        return;
    }
    for(int d = 0; d < (int)elec->getDaughters().size(); ++d) {
        MCParticle *dau = elec->getDaughters()[d];
        if(abs(dau->getPDG()) == 22) { // gamma and before Ecal
            //printf("%d %f %f %f\n", dau->getPDG(), dau->getVertex()[0], dau->getVertex()[1], dau->getVertex()[2]);
            if(BeforeECal2(dau->getVertex())) {
                if(n < nmax-1) {
                    en[n] = dau->getEnergy();  
                    rx[n] = dau->getVertex()[0];
                    ry[n] = dau->getVertex()[1];
                    rz[n] = dau->getVertex()[2];
                    //printf("photon %f %f %f\n", dau->getVertex()[0], dau->getVertex()[1], dau->getVertex()[2]);
                    n += 1;
                }
            }
        } else if(abs(dau->getPDG()) == pdg && BeforeECal2(dau->getVertex())) {
            CollectBS2(rx, ry, rz, en, n, nmax, dau, pdg);
            //printf("electr %f %f %f\n", dau->getVertex()[0], dau->getVertex()[1], dau->getVertex()[2]);
        }
    }

}


MCParticle *CollectFSR(double fsr[], MCParticle *part, double pdg, int level = 0) {

    MCParticle *ret = part;
    //printf("%d %f -> %g \n", level, Rho(part->getVertex()), Rho(part->getEndpoint()));
    if (Rho(part->getEndpoint()) > 0) {
        return part;
    }
    for (int d = 0; d < (int)part->getDaughters().size(); ++d)
    {
        MCParticle *dau = part->getDaughters()[d];
        if (abs(dau->getPDG()) == 22)
        {
            //printf("%d %f\n", level, dau->getEnergy());
            fsr[0] += dau->getEnergy();
            fsr[1] += dau->getMomentum()[0];
            fsr[2] += dau->getMomentum()[1];
            fsr[3] += dau->getMomentum()[2];
        }
        else if (abs(dau->getPDG()) == pdg && dau->getGeneratorStatus() != 0)
        {
            ret = CollectFSR(fsr, dau, pdg, level + 1);
        }
    }
    return ret;
}

void CollectBS(double *bs, double &n, MCParticle *elec, int pdg, int level = 0) {

    //printf("%d~~ %f -> %f\n", level, Rho(elec->getVertex()), Rho(elec->getEndpoint()));
    level += 1;
    if(!elec) return;
    if(!BeforeECal(elec->getVertex())) return;
    bool subElec = BeforeECal(elec->getEndpoint());

    for(int d = 0; d < (int)elec->getDaughters().size(); ++d) {
        MCParticle *dau = elec->getDaughters()[d];
        if(abs(dau->getPDG()) == 22) { // gamma and before Ecal
            if (BeforeECal(dau->getVertex()))
            {
                n += 1;
                bs[0] += dau->getEnergy();
                bs[1] += dau->getMomentum()[0];
                bs[2] += dau->getMomentum()[1];
                bs[3] += dau->getMomentum()[2];
            }
        } else if(subElec && abs(dau->getPDG()) == pdg && BeforeECal(dau->getVertex())) {
            CollectBS(bs, n, dau, pdg, level);
        }
    }

}



MCParticle *GetRealParticle(MCParticle *mcp) {
    if(!mcp) return mcp;
    int pdg = mcp->getPDG();
    if(mcp->getDaughters().size()==1 && mcp->getDaughters()[0]->getPDG() == pdg) mcp = mcp->getDaughters()[0];
    if(mcp->getDaughters().size()==1 && mcp->getDaughters()[0]->getPDG() == pdg) mcp = mcp->getDaughters()[0];
    if(mcp->getDaughters().size()==1 && mcp->getDaughters()[0]->getPDG() == 94) {
        mcp = mcp->getDaughters()[0]; // pdg94
        for (int i = 0; i < (int)mcp->getDaughters().size(); ++i)
        {
            if (mcp->getDaughters()[i]->getPDG() == pdg)
            {
                mcp = mcp->getDaughters()[i];
                break;
            }
        }
    }
    return mcp;
}
void Read(std::string rf, std::vector<std::string> const &files) {

    TFile root(rf.c_str(), "RECREATE");
    TTree tree("evts", "evts");

    // Monte Carlo Truth
    double idx = 0;
    double P1[4]; // original electron
    double P2[4];
    double FSR1[4];
    double FSR2[4];
    double ISR1[4];
    double ISR2[4];
    double P1F[4]; // electron in track
    double P2F[4];
    double P1BS[4];  // photon of bremsstrahlung
    double P2BS[4];


    int32_t NMC_PsBS;
    double RxMC_PsBS[100];
    double RyMC_PsBS[100];
    double RzMC_PsBS[100];
    double EMC_PsBS[100];

    double EMC_Ps;
    double MMC_Ps;
 
    double NMC_P1BS;
    double NMC_P2BS;

    double EMC_cms;
    double EMC_H;
    double EMC_totForSmear;
    double N_PDG94;


    // reconstruction
    double E_tot;
    double M_tot;
    double E_Ps;   // electrons
    double M_Ps;   // electrons



    tree.Branch("id", &idx, "id/D");
    tree.Branch("P1", P1, "P1[4]/D");
    tree.Branch("P2", P2, "P2[4]/D");
    tree.Branch("FSR1", FSR1, "FSR1[4]/D");
    tree.Branch("FSR2", FSR2, "FSR2[4]/D");
    tree.Branch("ISR1", ISR1, "ISR1[4]/D");
    tree.Branch("ISR2", ISR2, "ISR2[4]/D");
    tree.Branch("P1F", P1F, "P1F[4]/D");
    tree.Branch("P2F", P2F, "P2F[4]/D");
    tree.Branch("P1BS", P1BS, "P1BS[4]/D");
    tree.Branch("P2BS", P2BS, "P2BS[4]/D");

    tree.Branch("NMC_PsBS", &NMC_PsBS, "NMC_PsBS/I");
    tree.Branch("RxMC_PsBS", &RxMC_PsBS, "RxMC_PsBS[NMC_PsBS]/D");
    tree.Branch("RyMC_PsBS", &RyMC_PsBS, "RyMC_PsBS[NMC_PsBS]/D");
    tree.Branch("RzMC_PsBS", &RzMC_PsBS, "RzMC_PsBS[NMC_PsBS]/D");
    tree.Branch("EMC_PsBS", &EMC_PsBS, "EMC_PsBS[NMC_PsBS]/D");

    tree.Branch("EMC_Ps", &EMC_Ps, "EMC_Ps/D");
    tree.Branch("MMC_Ps", &MMC_Ps, "MMC_Ps/D");
    tree.Branch("NMC_P1BS", &NMC_P1BS, "NMC_P1BS/D");
    tree.Branch("NMC_P2BS", &NMC_P2BS, "NMC_P2BS/D");

    tree.Branch("EMC_H", &EMC_H, "EMC_H/D");
    tree.Branch("EMC_cms", &EMC_cms, "EMC_cms/D");
    tree.Branch("EMC_totForSmear", &EMC_totForSmear, "EMC_totForSmear/D");



    tree.Branch("E_tot", &E_tot, "E_tot/D");
    tree.Branch("M_tot", &M_tot, "M_tot/D");
    tree.Branch("E_Ps", &E_Ps, "E_Ps/D");
    tree.Branch("M_Ps", &M_Ps, "M_Ps/D");

    double nevt = 0;
    double pdg94 = 0;
    double nisr = 0;
    printf("%d files\n", (int)files.size());
    bool arbor = true;
    for (int f = 0; f < (int)files.size(); ++f)
    {
        LCReader *lcReader = LCFactory::getInstance()->createLCReader();
        lcReader->open(files[f]);
        for(LCEvent *evt; (evt = lcReader->readNextEvent()); )
        {
            //printf("index %d\n", (int)idx);
            //if(idx > 100) break;
            for(int i = 0; i < 4; ++i) P1[i] = 0;
            for(int i = 0; i < 4; ++i) P2[i] = 0;
            for(int i = 0; i < 4; ++i) FSR1[i] = 0;
            for(int i = 0; i < 4; ++i) FSR2[i] = 0;
            for(int i = 0; i < 4; ++i) ISR1[i] = 0;
            for(int i = 0; i < 4; ++i) ISR2[i] = 0;
            for(int i = 0; i < 4; ++i) P1F[i] = 0;
            for(int i = 0; i < 4; ++i) P2F[i] = 0;
            for(int i = 0; i < 4; ++i) P1BS[i] = 0;
            for(int i = 0; i < 4; ++i) P2BS[i] = 0;

            NMC_P1BS = 0;
            NMC_P2BS = 0;
            NMC_PsBS = 0;

            EMC_Ps = 0;
            MMC_Ps = 0;

            EMC_H = 0;
            EMC_cms = 0;
            EMC_totForSmear = 0;
            N_PDG94 = 0;

            E_tot = 0;
            M_tot = 0;  
            E_Ps = 0;
            M_Ps = 0;

            LCCollection *mccol = evt->getCollection("MCParticle");
            for (int i = 0; i < (int)mccol->getNumberOfElements(); ++i)
            {
                MCParticle *mcp = (MCParticle *)mccol->getElementAt(i);
                int pdg = mcp->getPDG();

                if (pdg == 94)
                {
                    pdg94 += 1;
                }

                if (i < 10 && mcp->getParents().size() == 0)
                {

                    if (pdg == 11 || pdg == 13)
                    {

                        MCParticle *rmcp = GetRealParticle(mcp);                      
                        P1[0] = rmcp->getEnergy();
                        for(int i = 1; i < 4; ++i) P1[i] = rmcp->getMomentum()[i-1];

                        rmcp = CollectFSR(FSR1, rmcp, abs(pdg));
                        P1F[0] = rmcp->getEnergy();
                        for(int i = 1; i < 4; ++i) P1F[i] = rmcp->getMomentum()[i-1];

                        if(fabs(FSR1[0] + P1F[0] - P1[0])>0.5) {
                            printf("%f %f %f %f ~~\n", idx, FSR1[0], P1F[0], P1[0]);
                        }
                        CollectBS(P1BS, NMC_P1BS, rmcp, abs(pdg));
                        //CollectBS2(RxMC_PsBS, RyMC_PsBS, RzMC_PsBS, EMC_PsBS, NMC_PsBS, 20, rmcp, abs(pdg));
                    }
                    else if (pdg == -11 || pdg == -13)
                    {
                        MCParticle *rmcp = GetRealParticle(mcp);
                        P2[0] = rmcp->getEnergy();
                        for (int i = 1; i < 4; ++i) P2[i] = rmcp->getMomentum()[i-1];

                        rmcp = CollectFSR(FSR2, rmcp, abs(pdg));
                        P2F[0] = rmcp->getEnergy();
                        for(int i = 1; i < 4; ++i) P2F[i] = rmcp->getMomentum()[i-1];

                        CollectBS(P2BS, NMC_P2BS, rmcp, abs(pdg));
                        //CollectBS2(RxMC_PsBS, RyMC_PsBS, RzMC_PsBS, EMC_PsBS, NMC_PsBS , 20, rmcp, abs(pdg));
                    }
                    else if (pdg == 22 && i == 0)
                    {
                        ISR1[0] = mcp->getEnergy();
                        for (int i = 1; i < 4; ++i) ISR1[i] = mcp->getMomentum()[i-1];
                    }
                    else if (pdg == 22 && i == 1)
                    {
                        ISR2[0] = mcp->getEnergy();
                        for (int i = 1; i < 4; ++i) ISR2[i] = mcp->getMomentum()[i-1];
                    }
                    else if (pdg == 25)
                    {
                        EMC_H = mcp->getEnergy();
                        //for (int i = 1; i < 4; ++i) ISR2[i] = mcp->getMomentum()[i-1];
                    }

                    EMC_cms += mcp->getEnergy();
                }
            } // for elements

            EMC_Ps = P1[0]+P2[0];
            MMC_Ps = TLorentzVector(P1[1]+P2[1], P1[2]+P2[2], P1[3]+P2[3], P1[0]+P2[0]).M();
            EMC_totForSmear = P1F[0] + P2F[0] + FSR1[0] + FSR2[0] + ISR1[0] + ISR2[0];

            if (arbor)
            {
                try
                {
                    LCCollection *abcol = evt->getCollection("ArborPFOs");
                    for (int i = 0; i < (int)mccol->getNumberOfElements(); ++i)
                    {
                        ReconstructedParticle *abp = (ReconstructedParticle *)abcol->getElementAt(i);
                        int pdg = abp->getType();
                        if (abs(pdg) == 11 || abs(pdg) == 13)
                        { // parton electron
                            E_Ps += abp->getEnergy();
                        }

                        printf("%d %f\n", i, abp->getEnergy());
                        E_tot += abp->getEnergy();
                    } // for elements
                }
                catch (...)
                {
                    arbor = false;
                    // Dan is developing ...
                }
            }

            nevt += 1;
            nisr += NMC_P1BS;
            nisr += NMC_P2BS;
            //if(NMC_P1BS) printf("1: %f %f\n", NMC_P1BS, EMC_P1BS);
            //if(NMC_P2BS) printf("2: %f %f\n", NMC_P2BS, EMC_P2BS);

            tree.Fill();
            idx++;
        }
        lcReader->close();
    }
    printf("pdg94/evt %f\n", pdg94/nevt);
    root.Write();
    root.Close();
}





void SetStyle() {
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetCanvasDefH(600);
    gStyle->SetCanvasDefW(600);
    gStyle->SetLabelSize(0.04,"xyz");
    gStyle->SetTitleSize(0.05,"xyz");
    gStyle->SetTitleOffset(1.2,"yz");
    gStyle->SetTitleOffset(1.2,"x");

    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadTopMargin(0.05);
    gStyle->SetPadRightMargin(0.05);
    gStyle->SetPadLeftMargin(0.15);

} 

struct Book {

    int fN;
    std::string fName;
    Book(char const *fileName) {
        fName = fileName;
        fN = 0;
    }

    void Add(TCanvas &cvs) {
        if(fN == 0) cvs.Print((fName + ".pdf(").c_str());
        else cvs.Print((fName + ".pdf").c_str());
        fN += 1;
    }

    ~Book() {
        TCanvas cvs;
        TH1D h;
        h.SetTitle(fName.c_str());
        cvs.Print((fName + ".pdf)").c_str());
    }
};




std::vector<std::string> at_most(std::vector<std::string> vs, size_t n) {
    if(vs.size() > n) vs.resize(n);
    return vs;
}

int main(int argc, char *argv[]) {

    SetStyle();
    if(argc == 3) {   
        std::vector<std::string> src;
        src.push_back(argv[1]);
        Read(argv[2], src);
    } else {
        Read("eeH.root", at_most(files("/cefs/data/FullSim/CEPC240/CEPC_v4/higgs/E240.Pe1e1h_X.e0.p0.whizard195", ".slcio"), 1));
        Read("mumuH.root", at_most(files("/cefs/data/FullSim/CEPC240/CEPC_v4/higgs/E240.Pe2e2h_X.e0.p0.whizard195", ".slcio"), 1));
    }


    return 0;
}
