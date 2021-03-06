/////////////////////////////////////////////
// bbarolo.hh: Contains BB core function
/////////////////////////////////////////////

/*-----------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published by the
 Free Software Foundation; either version 2 of the License, or (at your
 option) any later version.

 BBarolo is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 for more details.

 You should have received a copy of the GNU General Public License
 along with BBarolo; if not, write to the Free Software Foundation,
 Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA

 Correspondence concerning BBarolo may be directed to:
    Internet email: enrico.diteodoro@gmail.com
-----------------------------------------------------------------------*/


#ifndef BBAROLO_H_
#define BBAROLO_H_

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sys/stat.h>
#include <param.hh>
#include <cube.hh>
#include <stats.hh>
#include <moment.hh>
#include <ringmodel.hh>
#include <smooth3D.hh>
#include <galfit.hh>
#include <galwind.hh>
#include <ellprof.hh>
#include <spacepar.hh>
#include <utils.hh>


bool BBcore (Param *par) {

    // Interface for all BBarolo's tasks

    Cube<float> *c = new Cube<float>;
    c->saveParam(*par);

    if (!c->readCube(par->getImageFile())) {
        std::cout << par->getImageFile() << " is not a readable FITS file!\n";
        delete c;
        return false;
    }

    std::string outfolder = c->pars().getOutfolder();
    if (outfolder=="") {
       std::string path = get_currentpath();
            outfolder = path+"/output/"+c->Head().Obname()+"/";
            c->pars().setOutfolder(outfolder);
    }
    mkdirp(outfolder.c_str());
    
    if (par->getCheckCh()) c->CheckChannels();
    
    // Smoothing utility ------------------------------------------
    if (par->getflagSmooth()) {
        Smooth3D<float> *sm = new Smooth3D<float>;
        sm->cubesmooth(c);
        sm->fitswrite();
        delete sm;
    }
    // --------------------------------------------------------------


    // Source finding utility --------------------------------------
    if (par->getflagSearch()) {;
        c->Search();
        c->plotDetections();
        std::ofstream detout((outfolder+"detections.txt").c_str());
        c->printDetections(detout);
    }
    // --------------------------------------------------------------
        

    // 3D Cube Fitting task -----------------------------------------
    if (par->getflagGalFit()) {
        Model::Galfit<float> *fit = new Model::Galfit<float>(c);
        int status = 0;
        fit->galfit(&status);
        if (par->getParGF().TWOSTAGE) fit->SecondStage(&status);
        if (par->getFlagDebug()) fit->writeModel("BOTH",par->getFlagPlots());
        else fit->writeModel(par->getParGF().NORM,par->getFlagPlots());
        delete fit;
    }
    // --------------------------------------------------------------

    
    // Cube Model task -----------------------------------------------
    if (par->getflagGalMod()) {
        Model::Galfit<float> *fit = new Model::Galfit<float>(c);
        if (par->getFlagDebug()) fit->writeModel("BOTH",false);
        else fit->writeModel(par->getParGF().NORM,false);
        delete fit;
    }
    //----------------------------------------------------------------

    
    // Full parameter space task --------------------------------------
    if (par->getflagSpace()) {
        Spacepar<float> *sp = new Spacepar<float>(c);
        sp->calculate();
        sp->plotAll_Python();
        delete sp;
    }
    //----------------------------------------------------------------


    // GalWind task --------------------------------------
    if (par->getParGW().flagGALWIND) {
        GalWind<float> *w = new GalWind<float>(c);   
        w->compute();
        w->smooth();
        w->writeFITS();
        w->writeMomentMaps();
        w->writePV();
        delete w;
    }
    //----------------------------------------------------------------
        

    // 2D tilted-ring fitting task -----------------------------------
    if (par->getFlagRing()) {
        Ringmodel *trmod = new Ringmodel(c);
        trmod->ringfit();
        std::string fout = c->pars().getOutfolder()+c->Head().Name()+"_2dtrm.txt";
        std::ofstream fileo(fout.c_str());
        trmod->printfinal(fileo);
        fileo.close();
        trmod->printfinal(std::cout);
        trmod->writeModel(c->pars().getOutfolder()+c->Head().Name()+"_2d_mod.fits");
        delete trmod;
    }
    //-----------------------------------------------------------------


    // Moment maps task -----------------------------------------------
    if (par->getMaps()) {
        MomentMap<float> map;
        map.input(c);
        std::string s = outfolder+c->Head().Name();
        bool masking = par->getMASK()=="NONE" ? false : true;
        if (par->getMassDensMap()) {
            map.HIMassDensityMap(masking);
            map.fitswrite_2d((s+"map_massdens.fits").c_str());
        }
        if (par->getTotalMap()) {
            map.ZeroMoment(masking);
            map.fitswrite_2d((s+"map_0th.fits").c_str());
        }
        if (par->getVelMap()) {
            map.FirstMoment(masking);
            map.fitswrite_2d((s+"map_1st.fits").c_str());
        }
        if (par->getDispMap()) {
            map.SecondMoment(masking);
            map.fitswrite_2d((s+"map_2nd.fits").c_str());
        }
        if (par->getRMSMap()) {
            map.RMSMap();
            map.fitswrite_2d((s+"map_RMS.fits").c_str());
        }
        if (par->getGlobProf()) {
            Image2D<float> spectrum;
            spectrum.extractGlobalSpectrum(c);
            std::string specfname = c->pars().getOutfolder()+"spectrum.txt";
            std::ofstream specfile; specfile.open(specfname.c_str());
            for (int i=0; i<c->DimZ(); i++) 
                specfile << c->getZphys(i) << " " << spectrum.Array(i) << std::endl;
        }
    }
    //-----------------------------------------------------------------
        

    // PVs extraction task --------------------------------------------
    if (par->getFlagPV()) {
        float xpos = par->getXPOS_PV();
        float ypos = par->getYPOS_PV();
        float ang = par->getPA_PV();
        std::string s = outfolder+c->Head().Name();
        Image2D<float> *pv = PositionVelocity(c,xpos,ypos,ang);
        pv->fitswrite_2d((s+"pv_"+to_string(ang,0)+".fits").c_str());
        delete pv;
    }
    //-----------------------------------------------------------------
        
        
    // Repixeling task ------------------------------------------------
    if (par->getflagReduce() && !par->getflagSmooth()) {
        std::string name = c->pars().getOutfolder()+c->Head().Name()+"_red.fits";
        Cube<float> *red = c->Reduce(floor(c->pars().getFactor()));
        red->fitswrite_3d(name.c_str(),true);
        delete red;
    }
    //-----------------------------------------------------------------


    // Kinematics fitting to slit data --------------------------------
    if (par->getFlagSlitfit()) {
        Model::Galfit<float> *sfit = new Model::Galfit<float>;
        sfit->slit_init(c);
        int status = 0;
        sfit->galfit(&status);
        if (par->getParGF().TWOSTAGE) {
            sfit->SecondStage(&status);
            sfit->writeModel_slit();
        }
        else sfit->writeModel_slit();
    }
    //-----------------------------------------------------------------


    // Radial profile ------------------------------------------------
    if (par->getFlagEllProf()) {
        Tasks::Ellprof<float> *ell = new Tasks::Ellprof<float>(c);
        ell->RadialProfile();
        std::string fout = c->pars().getOutfolder()+c->Head().Name()+"_densprof.txt";
        std::ofstream fileo(fout.c_str());
        ell->printProfile(fileo,ell->getNseg()-1);
        ell->printProfile(std::cout,ell->getNseg()-1);
        ell->writeMap(c->pars().getOutfolder()+c->Head().Name()+"_densmap.fits");
        fileo.close();
        delete ell;
    }
    //-----------------------------------------------------------------

    delete c;

    return true;
}



#endif
