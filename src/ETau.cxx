
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

using namespace std;

bool BeforeECal(double const *r) {
    double rho = sqrt(r[0]*r[0] + r[1]*r[1]);
    if(rho < 1800/2 && fabs(r[2]) < 2300/2) {
        return true;
    }
    return false;
}

void CollectBS(double &e, double &n, double &eElec, MCParticle *elec) {

    if(!elec || abs(elec->getPDG()) != 11) return;
    if(!BeforeECal(elec->getEndpoint())) {
        eElec = elec->getEnergy();
        return;
    }
    for(int d = 0; d < (int)elec->getDaughters().size(); ++d) {
        MCParticle *dau = elec->getDaughters()[d];
        if(abs(dau->getPDG()) == 22) { // gamma and before Ecal
            //printf("%d %f %f %f\n", dau->getPDG(), dau->getVertex()[0], dau->getVertex()[1], dau->getVertex()[2]);
            if(BeforeECal(dau->getVertex())) {
                n += 1;
                e += dau->getEnergy();
            }
        } else if(abs(dau->getPDG()) == 11 && BeforeECal(dau->getVertex())) {
            CollectBS(e, n, eElec, dau);
        }

    }

}

void Read(std::string rf, std::vector<std::string> const &files) {

    TFile root(rf.c_str(), "RECREATE");
    TTree tree("evts", "evts");

    double EMC_P1;
    double EMC_P2;
    double EMC_P1F;
    double EMC_P2F;

    double EMC_P1BS;
    double NMC_P1BS;
    double EMC_P2BS;
    double NMC_P2BS;
    
    double EMC_tot;
    double EMC_Ps;
    double EMC_totForSmear;

    double EMC_ISR1;
    double EMC_ISR2;
    double EMC_FSR;

    double PxMC_Ps;
    double PyMC_Ps;
    double PzMC_Ps;
    double MMC_Ps;

    double E_tot;
    double M_tot;
    double E_Ps;   // electrons
    double M_Ps;   // electrons
    double N_PDG94;



    tree.Branch("EMC_P1", &EMC_P1, "EMC_P1/D");
    tree.Branch("EMC_P2", &EMC_P2, "EMC_P2/D");

    // =

    tree.Branch("EMC_P1BS", &EMC_P1BS, "EMC_P1BS/D");
    tree.Branch("EMC_P2BS", &EMC_P2BS, "EMC_P2BS/D");
    tree.Branch("NMC_P1BS", &NMC_P1BS, "NMC_P1BS/D");
    tree.Branch("NMC_P2BS", &NMC_P2BS, "NMC_P2BS/D");

    // +

    tree.Branch("EMC_P1F", &EMC_P1F, "EMC_P1F/D");
    tree.Branch("EMC_P2F", &EMC_P2F, "EMC_P2F/D");


    tree.Branch("EMC_FSR", &EMC_FSR, "EMC_FSR/D");
    tree.Branch("EMC_ISR1", &EMC_ISR1, "EMC_ISR1/D");
    tree.Branch("EMC_ISR2", &EMC_ISR2, "EMC_ISR2/D");

    tree.Branch("EMC_tot", &EMC_tot, "EMC_tot/D");
    tree.Branch("EMC_Ps", &EMC_Ps, "EMC_Ps/D");
    tree.Branch("MMC_Ps", &MMC_Ps, "MMC_Ps/D");

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
            
            NMC_P1BS = 0;
            EMC_P1BS = 0;
            NMC_P2BS = 0;
            EMC_P2BS = 0;            
            EMC_tot = 0;
            
            EMC_Ps = 0;
            MMC_Ps = 0;
            PxMC_Ps = 0;
            PyMC_Ps = 0;
            PzMC_Ps = 0;

            EMC_P1 = 0;
            EMC_P2 = 0;
            EMC_P1F = 0;
            EMC_P2F = 0;
            EMC_FSR = 0;
            EMC_ISR1 = 0;
            EMC_ISR2 = 0;

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

                if (pdg == 11 && mcp->getParents().size() == 1 && mcp->getParents()[0]->getPDG() == 94)
                {
                    EMC_P1 = mcp->getEnergy();
                    CollectBS(EMC_P1BS, NMC_P1BS, EMC_P1F, mcp);
                }
                else if (pdg == -11 && mcp->getParents().size() == 1 && mcp->getParents()[0]->getPDG() == 94)
                {
                    EMC_P2 = mcp->getEnergy();
                    CollectBS(EMC_P2BS, NMC_P2BS, EMC_P2F, mcp);
                }
                
                if (mcp->getPDG() == 94)
                {
                    N_PDG94 += 1;
                    pdg94 += 1;
                }

                if (i < 10 && mcp->getParents().size() == 0)
                {
                    if (abs(pdg) == 11)
                    {
                        EMC_Ps += mcp->getEnergy();
                        PxMC_Ps += mcp->getMomentum()[0];
                        PyMC_Ps += mcp->getMomentum()[1];
                        PzMC_Ps += mcp->getMomentum()[2];
                        MMC_Ps = sqrt(EMC_Ps*EMC_Ps - PxMC_Ps*PxMC_Ps - PyMC_Ps*PyMC_Ps - PzMC_Ps*PzMC_Ps);
                    }
                    if(pdg == 22 && i == 0) {
                        EMC_ISR1 = mcp->getEnergy();
                    } else if(i == 1 && pdg == 22) {
                        EMC_ISR2 = mcp->getEnergy();                            
                    }
                    if(pdg == 22 && i >= 2) {
                        EMC_FSR += mcp->getEnergy();
                    }

                    EMC_tot += mcp->getEnergy();
                }
            } // for elements

            if (!N_PDG94)
            {
                for (int i = 0; i < (int)mccol->getNumberOfElements(); ++i)
                {
                    MCParticle *mcp = (MCParticle *)mccol->getElementAt(i);
                    int pdg = mcp->getPDG();
                    if (pdg == 11 && mcp->getParents().size() == 0)
                    {
                        EMC_P1 = mcp->getEnergy();
                        CollectBS(EMC_P1BS, NMC_P1BS, EMC_P1F, mcp);
                    }
                    else if (pdg == -11 && mcp->getParents().size() == 0)
                    {
                        EMC_P2 = mcp->getEnergy();
                        CollectBS(EMC_P2BS, NMC_P2BS, EMC_P2F, mcp);
                    }
                } // for elements
            }

            EMC_totForSmear = EMC_ISR1 + EMC_ISR2 + EMC_FSR + EMC_P1BS + EMC_P2BS + EMC_P1F + EMC_P2F;

            if (arbor)
            {
                try
                {
                    LCCollection *abcol = evt->getCollection("ArborPFOs");
                    for (int i = 0; i < (int)mccol->getNumberOfElements(); ++i)
                    {
                        ReconstructedParticle *abp = (ReconstructedParticle *)abcol->getElementAt(i);
                        int pdg = abp->getType();
                        if (abs(pdg) == 11)
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

int main() {

    SetStyle();

    Read("result.root", at_most(files("/cefs/higgs/liangh/ETau/reco", ".slcio"), 5));


    return 0;
}
