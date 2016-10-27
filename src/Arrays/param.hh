// -----------------------------------------------------------------------
// param.hh: Definition of the Param class
// -----------------------------------------------------------------------

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
    Internet email: enrico.diteodoro@unibo.it
-----------------------------------------------------------------------*/

#ifndef PARAM_HH_
#define PARAM_HH_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Param				 /// Class to store general parameters for main program.
{
public:
     
    Param();								/// Default constructor.
    Param(const Param& p);					/// Copy constructor.
    Param& operator= (const Param& p);		/// Assignement operator =.
    virtual ~Param() {};					/// Default destructor.
    void  defaultValues();					/// Default values for constructor.
    
	/// Inline functions to access private member:
	
    string 	getImageFile () {return imageFile;};	
    string	getImageList () {return imageList;};
    string  getImage (int i) {return images[i];};	
    int  	getListSize () {return images.size();};		
    void   	setImageFile (std::string fname) {imageFile = fname;}; 	    
    void	setImage (std::string fname) {images.push_back(fname);};
    string	getOutfolder () {return outFolder;};
    void	setOutfolder (std::string fold) {outFolder=fold;};  
    bool   	isVerbose () {return verbose;};
    void   	setVerbosity (bool f) {verbose=f;};
    bool    getShowbar () {return showbar;};
    void    setShowbar (bool f) {showbar=f;};
    
    float 	getBeamFWHM() {return beamFWHM;};
    void	setBeamFWHM(float val) {beamFWHM=val;};
    bool	getCheckCh () {return checkChannels;};
    void 	setCheckCh (bool flag) {checkChannels=flag;};
    
    bool   	getFlagRobustStats () {return flagRobustStats;};
    void   	setFlagRobustStats (bool flag) {flagRobustStats=flag;};
    
    void    setSearch (bool Search) {flagSearch=Search;};
    bool	getSearch () {return flagSearch;};
    void   	setSearchType (std::string s) {searchType=s;};
    string 	getSearchType () {return searchType;};  			
    float  	getCut () {return snrCut;};
    void   	setCut (float c) {snrCut=c;};
    float  	getThreshold () {return threshold;};
    void   	setThreshold (float f) {threshold=f;};
    bool   	getFlagUserThreshold () {return flagUserThreshold;};
    void   	setFlagUserThreshold (bool b) {flagUserThreshold=b;};
    bool   	getFlagAdjacent () {return flagAdjacent;};
    void   	setFlagAdjacent (bool flag) {flagAdjacent=flag;};
    float  	getThreshS () {return threshSpatial;};
    void   	setThreshS (float t) {threshSpatial=t;};
    float  	getThreshV () {return threshVelocity;};
    void   	setThreshV (float t) {threshVelocity=t;};
    int    	getMinChannels () {return minChannels;};
    void   	setMinChannels (int n) {minChannels=n;};
    int 	getMinVoxels () {return minVoxels;};
    void   	setMinVoxels (unsigned int n) {minVoxels=n;};
    int 	getMinPix () {return minPix;};
    void   	setMinPix (int m) {minPix=m;};	 
    int 	getMaxChannels () {return maxChannels;};
    void 	setMaxChannels (int m) {maxChannels=m;};
    float   getMaxAngSize () {return maxAngSize;};
    void    setMaxAngSize (float f) {maxAngSize=f;};
    bool   	getRejectBeforeMerge () {return RejectBeforeMerge;};
    void   	setRejectBeforeMerge (bool flag) {RejectBeforeMerge=flag;};
    bool   	getTwoStageMerging () {return TwoStageMerging;};
    void   	setTwoStageMerging (bool flag) {TwoStageMerging=flag;};
    bool	getFlagGrowth(){return flagGrowth;};
    void	setFlagGrowth(bool flag){flagGrowth=flag;};
    float	getGrowthCut(){return growthCut;};
    void	setGrowthCut(float c){growthCut=c;};
    float	getGrowthThreshold(){return growthThreshold;};
    void	setGrowthThreshold(float f){growthThreshold=f;};
    bool	getFlagUserGrowthThreshold(){return flagUserGrowthT;};
    void	setFlagUserGrowthThreshold(bool b){flagUserGrowthT=b;};
    int     getThreads () {return threads;};
    bool    getFlagDebug() {return debug;}
    
    void	setGlobProf (bool flag) {globprof = flag;};
    bool 	getGlobProf () {return globprof;};
    void   	setTotalMap (bool flag) {totalmap = flag;};
    bool   	getTotalMap () {return totalmap;};
    void   	setVelMap (bool flag) {velocitymap = flag;};
    bool   	getVelMap () {return velocitymap;};
    void   	setDispMap (bool flag) {dispersionmap = flag;};
    bool   	getDispMap () {return dispersionmap;};
    void   	setBlankCube (bool flag) {useBlankCube = flag;};
    bool   	getBlankCube () {return useBlankCube;};
    bool   	getMaps() {return (globprof || totalmap || velocitymap || dispersionmap);};
    void 	setBlankCut (float f) {blankCut=f;};
    float	getBlankCut() {return blankCut;};  
    
    bool	getFlagRing () {return flagRing;};
    void 	setFlagRing (bool b) {flagRing = b;};
    bool	isInteractive () {return interactive;};
    void 	setInteractive (bool b) {interactive = b;};
    int		getNrings () {return nrings;};
    void 	setNrings (int n) {nrings = n;};
    
    bool 	getflagGalFit () {return flagGalFit;};
    void    setflagGalFit (bool GalFit) {flagGalFit=GalFit;};
    bool 	getflagGalMod () {return flagGalMod;};
    void    setflagGalMod (bool GalMod) {flagGalMod=GalMod;};
    int		getBOX	(int i) {return BOX[i];};
    void    setBOX (int dim, int index) {BOX[index]=dim;};
	int		getNRADII () {return NRADII;};
    void    setNRADII (int numRadii) {NRADII=numRadii;};
    string  getRADII () {return RADII;};
    void    setRADII (string radiiString) {RADII=radiiString;};
    string	getXPOS () {return XPOS;};
    void    setXPOS (string xposString) {XPOS=xposString;};
    string	getYPOS () {return YPOS;};
    void    setYPOS (string yposString) {YPOS=yposString;};
    double	getRADSEP () {return RADSEP;};
    void    setRADSEP (double radsep) {RADSEP=radsep;};
    string	getVSYS () {return VSYS;};
    void    setVSYS (string vSysString) {VSYS=vSysString;};
    string	getVROT () {return VROT;};
    void    setVROT (string vRotString) {VROT=vRotString;};
    string	getVDISP () {return VDISP;};
    void    setVDISP (string vDispString) {VDISP=vDispString;};
    string	getINC () {return INC;};
    void    setINC (string IncString) {INC=IncString;};
    float	getDELTAINC () {return DELTAINC;};
    void    setDELTAINC (float deltaInc) {DELTAINC=deltaInc;};
    string	getPHI () {return PHI;};
    void    setPHI (string PhiString) {PHI=PhiString;};
    float	getDELTAPHI () {return DELTAPHI;};
    void    setDELTAPHI (float deltaPhi) {DELTAPHI=deltaPhi;};
    string	getZ0 () {return Z0;};
    void    setZ0 (string z0String) {Z0=z0String;};
    string	getDENS () {return DENS;};
    void    setDENS (string densString) {DENS=densString;};
    int		getCDENS () {return CDENS;};
    void    setCDENS (int cDens) {CDENS=cDens;};
    int		getLTYPE () {return LTYPE;};
    void    setLTYPE (int lType) {LTYPE=lType;};
    int		getFTYPE () {return FTYPE;};
    void    setFTYPE (int fType) {FTYPE=fType;};
    int		getWFUNC () {return WFUNC;};
    void    setWFUNC (int wFunc) {WFUNC=wFunc;};
    int		getNV () {return NV;};
    void    setNV (int nv) {NV=nv;};
    double	getTOL () {return TOL;}
    void    setTOL (double tollerance) {TOL=tollerance;};
    string	getMASK() {return MASK;}
    void    setMASK(string maskSring) {MASK=maskSring;};
    bool	getSM () {return SM;}
    void	setSM	(bool a) {SM=a;}
    void	setSIDE (string a) {SIDE=a;}
    string  getSIDE() {return SIDE;}
    bool	getTwoStage () {return TwoStage;}
    void	setTwoStage (bool b) {TwoStage=b;}
    bool	getflagErrors() {return flagErrors;}
    void    setflagErrors (bool flag) {flagErrors=flag;};
    string 	getPOLYN () {return POLYN;}
    void    setPOLYN(string polynSring) {POLYN=polynSring;};
    string  getFREE () {return FREE;}
    void    setFREE(string freeSring) {FREE=freeSring;};
    double	getDistance () {return distance;}
    void    setDistance (double dist) {distance=dist;};
    int		getBweight () {return BWEIGHT;}
    void    setBweight (int bWeight) {BWEIGHT=bWeight;};
    string  getNORM () {return NORM;}
    void    setNORM(string normString) {NORM=normString;};
    int     getStartRad() {return startRAD;}
    void    setStartRad(int startRad) {startRAD=startRad;};
    double  getRedshift() {return redshift;}
    void    setRedshift(double redShift) {redshift=redShift;};
    double  getRestwave() {return restwave;}
    void    setRestwave(double restWave) {restwave=restWave;};
    size_t  getNlines () {return nlines;}


    bool	getflagSpace () {return flagSpace;}
    void    setflagSpace (bool flag) {flagSpace=flag;};
    string  getP1 () {return P1;}
    void    setP1 (string P1String) {P1=P1String;};
    string  getP2 () {return P2;}
    void    setP2 (string P2String) {P2=P2String;};
    float	getP1p (int i) {return P1p[i];}
    void    setP1p (int index, float P1value) {P1p[index]=P1value;};
    float	getP2p (int i) {return P2p[i];}
    void    setP2p (int index, float P2value) {P2p[index]=P2value;};

    bool	getflagSmooth () {return flagSmooth;}
    void    setflagSmooth (bool flag) {flagSmooth=flag;};
    double	getBmaj	() {return bmaj;}
    void    setBmaj(double Bmaj) {bmaj=Bmaj;};
    double	getBmin	() {return bmin;}
    void    setBmin(double Bmin) {bmin=Bmin;};
    double	getBpa	() {return bpa;}
    void    setBpa(double Bpa) {bpa=Bpa;};
    double	getOBmaj	() {return obmaj;}
    void    setOBmaj(double OBmaj) {obmaj=OBmaj;};
    double	getOBmin	() {return obmin;}
    void    setOBmin(double OBmin) {obmin=OBmin;};
    double	getOBpa	() {return obpa;}
    void    setOBpa(double OBpa) {obpa=OBpa;};
    bool	getflagFFT () {return flagFFT;}
    void	setflagFFT (bool f) {flagFFT=f;}
    float 	getLinear () {return linear;}
    void    setLinear(float value) {linear=value;};
    float 	getFactor () {return factor;}
    void    setFactor(float value) {factor=value;};
    float   getScaleFactor () {return scalefactor;}
    void 	setScaleFactor (float value) {scalefactor=value;}
    bool	getflagReduce() {return flagReduce;}
    void    setflagReduce(bool flag) {flagReduce=flag;};
    string  getSmoothOut () {return smo_out;}
    void    setSmoothOut(string SmoothOutString) {smo_out=SmoothOutString;};

    bool    getFlagSlitfit () {return flagSlitfit;}
    void    setFlagSlitfit(bool flag) {flagSlitfit=flag;};
    string  getWavefile () {return wavefile;}
    void    setWavefile(string WaveFile) {wavefile=WaveFile;};
    string  getIvarfile () {return ivarfile;}
    void    setIvarfile(string IvarFile) {ivarfile=IvarFile;};
    string  getLine() {return linetofit;}
    void    setLine(string LineToFit) {linetofit=LineToFit;};

    bool    getFlagPV() {return flagPV;}
    void    setFlagPV(bool flag) {flagPV=flag;};
    float   getXPOS_PV() {return XPOS_PV;}
    void    setXPOS_PV(float value) {XPOS_PV=value;};
    float   getYPOS_PV() {return YPOS_PV;}
    void    setYPOS_PV(float value) {YPOS_PV=value;};
    float   getPA_PV() {return PA_PV;}
    void    setPA_PV(float value) {PA_PV=value;};
    
    /// Utility functions:
    
    bool 	getopts(int argc, char **argv);  	/// Parse the command line parameters correctly. 
    int  	readParams(string paramfile); 	/// Read in parameters from a disk file.
    bool 	checkPars();	 					/// Check the parameter list for inconsistencies. 
    void 	printDefaults (ostream& theStream=cout);	/// Print on screen the defaults values.
    void 	createTemplate();					/// Create a template input file for Galfit.
    
    friend ostream& operator<< (ostream& theStream, Param& par);
    
    friend class Image;
  
private:
    string          imageFile;          ///< The image to be analysed.
    string          imageList;          ///< A file with list of images to be analized.
    vector<string>  images;             ///< A vector with single images in the list.
    string          outFolder;          ///< Folder where saving output files.
    bool            verbose;            ///< Is verbosity activated?
    bool            showbar;            ///< Show progress bar?
    bool            checkChannels;      ///< Checking for bad channels in the cube?
    float           beamFWHM;           ///< Beam to adopt if any information in header.
    bool            flagRobustStats;    ///< Whether to use robust statistics.
    
    bool            flagSearch;         ///< Should search for sources in cube?
    string          searchType;         ///< "Spectral" or "Spatial" search?
    float           snrCut;             ///< Signal to Noise for detection when sigma-clipping.
    float           threshold;          ///< What the threshold is (when sigma-clipping).
    bool            flagUserThreshold;  ///< Whether the user has defined a threshold of their own.
    bool            flagAdjacent;       ///< Use the adjacent criterion for objects merger?
    float           threshSpatial;      ///< Maximum spatial separation between objects.
    float           threshVelocity;     ///< Maximum channels separation between objects.
    int             minChannels;        ///< Minimum channels to make an object.
    bool            RejectBeforeMerge;  ///< Whether to reject sources before merging.
    bool            TwoStageMerging;    ///< Whether to do a partial merge during search.
    int             minVoxels;          ///< Minimum voxels required in an object.
    int             minPix;             ///< Minimum pixels required in an object.
    int             maxChannels;        ///< Maximum channels to accept an object.
    float           maxAngSize;         ///< Maximum angular size in the object in arcmin.
    bool            flagGrowth;         ///< Are we growing objects once they are found?
    float           growthCut;          ///< The SNR that we are growing objects down to.
    bool            flagUserGrowthT;    ///< Whether the user has manually defined a threshold
    float           growthThreshold;    ///< The threshold for growing objects down to
    
    bool            globprof;           ///< Whether the user wants the global profile.
    bool            totalmap;           ///< Whether the user wants the total HI map.
    bool            velocitymap;        ///< Whether the user wants the velocity field.
    bool            dispersionmap;      ///< Whether the user wants the velocity dispersion field.
    bool            useBlankCube;       ///< Using a blanked cube for extracting maps?
    float           blankCut;           ///< SNR clipping cut for blanked area.

    bool            flagRing;           ///< Do you want to fit a tilted ring model?
    bool            interactive;        ///< Do you want interactive mode during fit?
    int             nrings;             ///< How many rings for fitting?
	
    bool            flagGalFit;
    bool            flagGalMod;
    int             BOX[6];             ///< A box in RA-DEC-VELO. Not used anymore!
    int             NRADII;             ///< Number of rings for Galfit.
    string          RADII;              ///< A list of radii
    string          XPOS;               ///< X center of the galaxy (pixel).
    string          YPOS;               ///< Y center of the galaxy (pixel).
    double          RADSEP;             ///< Separation between rings (arcs).
    string          VSYS;               ///< Systemic velocity (km/s).
    string          VROT;               ///< Circular velocity (km/s).
    string          VDISP;              ///< Rotation velocity (km/s).
    string          INC;                ///< Inclination angle (degrees).
    float           DELTAINC;           ///< Inclination angle variation (degrees).
    string          PHI;                ///< Position angle from north anti-clockwise.
    float           DELTAPHI;           ///< Position angle variation (degrees).
    string          Z0;                 ///< Height scale of the disk (arcs).
    string          DENS;               ///< Column density of gas (atoms/cm2).
    int             CDENS;              ///< Surface density of clouds in the plane of ring (1e20).
    int             LTYPE;              ///< Layer type along z.
    int             FTYPE;              ///< Type of function to be minimized;
    int             WFUNC;              ///< Weighting function.
    int             NV;                 ///< Number of subclouds per profile.
    double          TOL;                ///< Tolerance for minimization.
    string          MASK;///< Type of mask to use: SEARCH, SMOOTH, THRESHOLD, NEGATIVE or NONE.
    bool            SM;
    string          NORM;               ///< Normalization type: LOCAL, AZIM or NONE.
    string          FREE;               ///< Free parameters.
    string          SIDE;               ///< Approaching(A), Receding(R), Both(B), Single(S)
    bool            TwoStage;
    bool            flagErrors;         ///< Whether estimating errors.
    string          POLYN;              ///< Degree of polynomials fitting INC e PA.
    int             BWEIGHT;            ///< Power of the weighting function for Blank pixels.
    int             startRAD;           ///< Starting radius
    float           distance;           ///< Distance of the galaxy to convert arcs to kpc.
    double          redshift;           ///< Redshift of the galaxy.
    double          restwave;           ///< Rest wavelength
    size_t          nlines;             ///< Number of lines

    bool            flagSpace;
    string          P1;
    string          P2;
    float           P1p[3];
    float           P2p[3];

    bool            flagSmooth;
    double          bmaj;               ///< Beam of the smoothed array (arcs).
    double          bmin;               ///< Beam of the smoothed array (arcs).
    double          bpa;                ///< Beam of the smoothed array (deg).
    double          obmaj;              ///< Beam of the original array.
    double          obmin;
    double          obpa;
    bool            flagFFT;            ///< Using FFT for convolution?
    float           linear;             ///< Linear resolution to be achieved.
    float           factor;             ///< The newbeam is a factor of the old.
    float           scalefactor;
    bool            flagReduce;
    string          smo_out;            ///< Output file.

    bool            flagSlitfit;        ///< Fitting a 3D model to a slit observation.
    string          wavefile;           ///< Fitsfile containing the wavelegths.
    string          ivarfile;           ///< Fitsfile containing the inverse-variance or a value.
    string          linetofit;          ///< Line to fit: Ha, Hb, OIII etc...


    bool            flagPV;                 ///< Extracting a position-velocity diagram.
    float           XPOS_PV;
    float           YPOS_PV;
    float           PA_PV;

    int             threads;
    bool            debug;
};


  /// Write out info on a parameter to e.g. the results file.
void recordParameters(ostream& theStream, string paramName, string paramDesc, string paramValue);

  /// A macro to handle streamed output to recordParameters.
#define recordParam(outstream,string1,string2,instream)      	 \
	do {                                                       	 \
		ostringstream oss;		                                 \
		oss<<instream;                                           \
		recordParameters(outstream,string1,string2,oss.str());   \
	} while(0)


void helpscreen(ostream& Str=cout);

#endif
