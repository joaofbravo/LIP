/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Executable: TMVAClassificationApplication                                      *
 *                                                                                *
 * This macro provides a simple example on how to use the trained classifiers     *
 * within an analysis module                                                      *
 **********************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "TROOT.h"
#include "TSystem.h"
#include "TFile.h"
#include "TString.h"
#include "TObjString.h"
#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

using namespace TMVA;


void NewTMVAClassificationApplication( TString myMethodList = "" ) 
{   
	const int pp_flag   = 0; // p-p=1, Pb-Pb=0
	const int test_flag = 1; // choose input folders

	// This loads the library
	TMVA::Tools::Instance();

	// Default MVA methods to be trained + tested (On: 1, Off: 0)
	std::map<std::string,int> Use;

	// ---- Cut optimisation
	Use["Cuts"]            = 0;
	Use["CutsD"]           = 0;
	Use["CutsPCA"]         = 0;
	Use["CutsGA"]          = 0;
	Use["CutsSA"]          = 0;

	// ---- 1-dimensional likelihood ("naive Bayes estimator")
	Use["Likelihood"]      = 0;
	Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
	Use["LikelihoodPCA"]   = 0; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
	Use["LikelihoodKDE"]   = 0;
	Use["LikelihoodMIX"]   = 0;

	// ---- Mutidimensional likelihood and Nearest-Neighbour methods
	Use["PDERS"]           = 0;
	Use["PDERSD"]          = 0;
	Use["PDERSPCA"]        = 0;
	Use["PDEFoam"]         = 0;
	Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
	Use["KNN"]             = 0; // k-nearest neighbour method
	
	// ---- Linear Discriminant Analysis
	Use["LD"]              = 0; // Linear Discriminant identical to Fisher
	Use["Fisher"]          = 0;
	Use["FisherG"]         = 0;
	Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
	Use["HMatrix"]         = 0;
	
	// ---- Function Discriminant analysis
	Use["FDA_GA"]          = 0; // minimisation of user-defined function using Genetics Algorithm
	Use["FDA_SA"]          = 0;
	Use["FDA_MC"]          = 0;
	Use["FDA_MT"]          = 0;
	Use["FDA_GAMT"]        = 0;
	Use["FDA_MCMT"]        = 0;
	
	// ---- Neural Networks (all are feed-forward Multilayer Perceptrons)
	Use["MLP"]             = 0; // Recommended ANN
	Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
	Use["MLPBNN"]          = 0; // Recommended ANN with BFGS training method and bayesian regulator
	Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
	Use["TMlpANN"]         = 0; // ROOT's own ANN
	
	// ---- Support Vector Machine 
	Use["SVM"]             = 0;
	
	// ---- Boosted Decision Trees
	Use["BDT"]             = 1; // uses Adaptive Boost
	Use["BDTG"]            = 0; // uses Gradient Boost
	Use["BDTB"]            = 0; // uses Bagging
	Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
	Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting
	
	// ---- Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
	Use["RuleFit"]         = 0;
	
	Use["Plugin"]          = 0;
	Use["Category"]        = 0;
	Use["SVM_Gauss"]       = 0;
	Use["SVM_Poly"]        = 0;
	Use["SVM_Lin"]         = 0;

//---------------------------------------------------------------

	std::cout << "===> Start NewTMVAClassificationApplication\n" << std::endl;

	// Select methods (don't look at this code - not of interest)
	if (myMethodList != "") {
		for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

			std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
		for (UInt_t i=0; i<mlist.size(); i++) {
			std::string regMethod(mlist[i]);

			if (Use.find(regMethod) == Use.end()) {
				std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
				for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
					std::cout << std::endl;
				return;
			}
			Use[regMethod] = 1;
		}
	}

//---------------------------------------------------------------

	// ---- Create the Reader object

	TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    

	// Create a set of variables and declare them to the reader. The variable
	// names MUST corresponds in name and type to those given in the weight file(s) used

	Float_t out_pt, out_eta, out_ip2d_cllr_pbpu, out_ip2d_cllr_pbpc, out_ip2d_cllr_pcpu;
	Float_t out_abseta, out_phi, out_ip3d_cllr_pbpu, out_ip3d_cllr_pbpc, out_ip3d_cllr_pcpu;
	Float_t out_sv1_m, out_sv1_efc, out_sv1_sig3d, out_sv1_deltaR, out_sv1_normdist;
	Float_t out_sv1_Lxy, out_sv1_L3d, out_jf_m, out_jf_efc, out_jf_dRFlightDir;
	Float_t out_jf_sig3d, out_ip2d_pb, out_ip2d_pc, out_ip2d_pu, out_ip2d_llr;
	Float_t out_jf_nrtkAtVx, out_ip3d_pb, out_ip3d_pc, out_ip3d_pu, out_ip3d_llr;
	Float_t out_jf_pb, out_jf_pc, out_jf_pu, out_jf_llr, out_jf_mUncorr, out_jf_deta;
	Float_t out_jf_dphi, out_jf_phi, out_jf_theta, out_jf_theta_err, out_jf_phi_err;
	Float_t out_JZweight, out_evweight, out_FCalET;

	Int_t out_sv1_ntrkv, out_sv1_n2t, out_jf_nvtx1t, out_jf_n2t, out_jf_nvtx, out_sv1_Nvtx, out_jf_VTXsize, out_JZ, out_centzone, out_truthflav;
	Float_t outfl_sv1_ntrkv, outfl_sv1_n2t, outfl_jf_nvtx1t, outfl_jf_n2t, outfl_jf_nvtx, outfl_sv1_Nvtx, outfl_jf_VTXsize, outfl_JZ, outfl_centzone, outfl_truthflav;

	reader->AddVariable( "out_pt", &out_pt );
	reader->AddVariable( "out_abseta", &out_abseta );

	// reader->AddVariable( "out_ip2d_pb", &out_ip2d_pb );
	// reader->AddVariable( "out_ip2d_pc", &out_ip2d_pc );
	// reader->AddVariable( "out_ip2d_pu", &out_ip2d_pu );
	// reader->AddVariable( "out_ip2d_llr", &out_ip2d_llr );
	reader->AddVariable( "out_ip2d_cllr_pbpu", &out_ip2d_cllr_pbpu );
	reader->AddVariable( "out_ip2d_cllr_pbpc", &out_ip2d_cllr_pbpc );
	reader->AddVariable( "out_ip2d_cllr_pcpu", &out_ip2d_cllr_pcpu );
	
	// reader->AddVariable( "out_ip3d_pb", &out_ip3d_pb );
	// reader->AddVariable( "out_ip3d_pc", &out_ip3d_pc );
	// reader->AddVariable( "out_ip3d_pu", &out_ip3d_pu );
	// reader->AddVariable( "out_ip3d_llr", &out_ip3d_llr );
	reader->AddVariable( "out_ip3d_cllr_pbpu", &out_ip3d_cllr_pbpu );
	reader->AddVariable( "out_ip3d_cllr_pbpc", &out_ip3d_cllr_pbpc );
	reader->AddVariable( "out_ip3d_cllr_pcpu", &out_ip3d_cllr_pcpu );
	
	// reader->AddVariable( "out_sv1_Nvtx", &outfl_sv1_Nvtx );
	reader->AddVariable( "out_sv1_ntrkv", &outfl_sv1_ntrkv );
	reader->AddVariable( "out_sv1_n2t", &outfl_sv1_n2t );
	reader->AddVariable( "out_sv1_m", &out_sv1_m );
	reader->AddVariable( "out_sv1_efc", &out_sv1_efc );
	reader->AddVariable( "out_sv1_sig3d", &out_sv1_sig3d );
	// reader->AddVariable( "out_sv1_normdist", &out_sv1_normdist );
	reader->AddVariable( "out_sv1_deltaR", &out_sv1_deltaR );
	reader->AddVariable( "out_sv1_Lxy", &out_sv1_Lxy);
	reader->AddVariable( "out_sv1_L3d", &out_sv1_L3d );

	// reader->AddVariable( "out_jf_pb", &out_jf_pb );
	// reader->AddVariable( "out_jf_pc", &out_jf_pc );
	// reader->AddVariable( "out_jf_pu", &out_jf_pu );
	reader->AddVariable( "out_jf_llr", &out_jf_llr );
	reader->AddVariable( "out_jf_m", &out_jf_m );
	// reader->AddVariable( "out_jf_mUncorr", &out_jf_mUncorr );
	reader->AddVariable( "out_jf_efc", &out_jf_efc );
	// reader->AddVariable( "out_jf_deta", &out_jf_deta );
	// reader->AddVariable( "out_jf_dphi", &out_jf_dphi );
	reader->AddVariable( "out_jf_dRFlightDir", &out_jf_dRFlightDir );
	reader->AddVariable( "out_jf_ntrkAtVx", &out_jf_nrtkAtVx );
	reader->AddVariable( "out_jf_nvtx", &outfl_jf_nvtx );
	reader->AddVariable( "out_jf_sig3d", &out_jf_sig3d );
	reader->AddVariable( "out_jf_nvtx1t", &outfl_jf_nvtx1t );
	reader->AddVariable( "out_jf_n2t", &outfl_jf_n2t );
	// reader->AddVariable( "out_jf_VTXsize", &outfl_jf_VTXsize );
	// reader->AddVariable( "out_jf_phi", &out_jf_phi );
	// reader->AddVariable( "out_jf_theta", &out_jf_theta );
	// reader->AddVariable( "out_jf_theta_err", &out_jf_theta_err );
	// reader->AddVariable( "out_jf_phi_err", &out_jf_phi_err );

	// Spectator variables declared in the training have to be added to the reader too
	reader->AddSpectator( "out_JZ", &outfl_JZ ); // [0,5]
	reader->AddSpectator( "out_JZweight", &out_JZweight );
	reader->AddSpectator( "out_evweight", &out_evweight );
	// reader->AddSpectator( "out_FCalET", &out_FCalET );
	reader->AddSpectator( "out_centzone", &outfl_centzone ); // {-1} U [1,9]
	reader->AddSpectator( "out_eta", &out_eta );
	reader->AddSpectator( "out_phi", &out_phi );
	reader->AddSpectator( "out_truthflav", &outfl_truthflav );

	// Float_t Category_cat1, Category_cat2, Category_cat3;
	// if (Use["Category"]){
	//  Add artificial spectators for distinguishing categories
	//  reader->AddSpectator( "Category_cat1 := var3<=0",             &Category_cat1 );
	//  reader->AddSpectator( "Category_cat2 := (var3>0)&&(var4<0)",  &Category_cat2 );
	//  reader->AddSpectator( "Category_cat3 := (var3>0)&&(var4>=0)", &Category_cat3 );
	// }

//---------------------------------------------------------------

	// ---- Book the MVA methods

	TString dir    = "weights/";
	TString prefix = "TMVAClassification";

	// Book method(s)
	for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
		if (it->second) {
			TString methodName = TString(it->first) + TString(" method");
			TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
			reader->BookMVA( methodName, weightfile ); 
		}
	}

	// ---- Book output histograms

	TH1::SetDefaultSumw2(); // store sum of squares of weights
	Int_t   nbin          = 100;
	Int_t   nbin_abseta   = 30;
	Int_t   nbin_cent     = 12;
	Int_t   nbin_ip3d     = 140;
	Int_t   nbin_jf       = 115;
	
	Float_t lowlim_pt     = 80000;
	Float_t uplim_pt;
	if (pp_flag) uplim_pt = 700000;	else uplim_pt = 200000;
	Float_t lowlim_eta    = -3;
	Float_t lowlim_abseta = 0;
	Float_t uplim_abseta  = 3;
	Float_t lowlim_phi    = -TMath::Pi();
	Float_t uplim_phi     = TMath::Pi();
	Float_t lowlim_cent   = -1.5;
	Float_t uplim_cent    = 10.5;

	Float_t lowlim_ip3d   = -35;
	Float_t uplim_ip3d    = 105;
	Float_t lowlim_jf     = -105;
	Float_t uplim_jf      = 10;
	Float_t lowlim_bdt    = -0.8;
	Float_t uplim_bdt     = 0.8;

	TH1F *histLk(0), *histLkD(0), *histLkPCA(0), *histLkKDE(0), *histLkMIX(0), *histPD(0), *histPDD(0);
	TH1F *histPDPCA(0), *histPDEFoam(0), *histPDEFoamErr(0), *histPDEFoamSig(0), *histKNN(0), *histHm(0);
	TH1F *histFi(0), *histFiG(0), *histFiB(0), *histLD(0), *histNn(0),*histNnbfgs(0),*histNnbnn(0);
	TH1F *histNnC(0), *histNnT(0), *histBdt(0), *histBdtG(0), *histBdtD(0), *histRf(0), *histSVMG(0);
	TH1F *histSVMP(0), *histSVML(0), *histFDAMT(0), *histFDAGA(0), *histCat(0), *histPBdt(0);

	// User histograms
	TH1F *histSig_pt(0), *histSig_eta(0), *histSig_abseta(0), *histSig_phi(0), *histSig_centzone(0), *histBkg_pt(0), *histBkg_eta(0), *histBkg_abseta(0), *histBkg_phi(0), *histBkg_centzone(0), *histOther_pt(0), *histOther_eta(0), *histOther_abseta(0), *histOther_phi(0), *histOther_centzone(0), *histIP2D(0), *histIP2DSig(0), *histIP2DBkg(0), *histIP2DOther(0), *histIP3D(0), *histIP3DSig(0), *histIP3DBkg(0), *histIP3DOther(0), *histJF(0), *histJFSig(0), *histJFBkg(0), *histJFOther(0), *histBdtSig(0), *histBdtBkg(0), *histBdtOther(0);

	TH2F *hist_pt_vs_eta(0), *histSig_pt_vs_eta(0), *histBkg_pt_vs_eta(0), *histOther_pt_vs_eta(0), *hist_pt_vs_phi(0), *histSig_pt_vs_phi(0), *histBkg_pt_vs_phi(0), *histOther_pt_vs_phi(0), *hist_pt_vs_centzone(0), *histSig_pt_vs_centzone(0), *histBkg_pt_vs_centzone(0), *histOther_pt_vs_centzone(0), *hist_phi_vs_eta(0), *histSig_phi_vs_eta(0), *histBkg_phi_vs_eta(0), *histOther_phi_vs_eta(0), *hist_phi_vs_centzone(0), *histSig_phi_vs_centzone(0), *histBkg_phi_vs_centzone(0), *histOther_phi_vs_centzone(0), *hist_centzone_vs_eta(0), *histSig_centzone_vs_eta(0), *histBkg_centzone_vs_eta(0), *histOther_centzone_vs_eta(0);

	TH2F *histBdt_pt_vs_eval(0), *histBdt_abseta_vs_eval(0), *histBdt_phi_vs_eval(0), *histBdt_centzone_vs_eval(0), *histBdtSig_pt_vs_eval(0), *histBdtSig_abseta_vs_eval(0), *histBdtSig_phi_vs_eval(0), *histBdtSig_centzone_vs_eval(0), *histBdtBkg_pt_vs_eval(0), *histBdtBkg_abseta_vs_eval(0), *histBdtBkg_phi_vs_eval(0), *histBdtBkg_centzone_vs_eval(0), *histBdtOther_pt_vs_eval(0), *histBdtOther_abseta_vs_eval(0), *histBdtOther_phi_vs_eval(0), *histBdtOther_centzone_vs_eval(0);
	TH2F *histIP2D_pt_vs_eval(0), *histIP2D_abseta_vs_eval(0), *histIP2D_phi_vs_eval(0), *histIP2D_centzone_vs_eval(0), *histIP2DSig_pt_vs_eval(0), *histIP2DSig_abseta_vs_eval(0), *histIP2DSig_phi_vs_eval(0), *histIP2DSig_centzone_vs_eval(0), *histIP2DBkg_pt_vs_eval(0), *histIP2DBkg_abseta_vs_eval(0), *histIP2DBkg_phi_vs_eval(0), *histIP2DBkg_centzone_vs_eval(0), *histIP2DOther_pt_vs_eval(0), *histIP2DOther_abseta_vs_eval(0), *histIP2DOther_phi_vs_eval(0), *histIP2DOther_centzone_vs_eval(0);
	TH2F *histIP3D_pt_vs_eval(0), *histIP3D_abseta_vs_eval(0), *histIP3D_phi_vs_eval(0), *histIP3D_centzone_vs_eval(0), *histIP3DSig_pt_vs_eval(0), *histIP3DSig_abseta_vs_eval(0), *histIP3DSig_phi_vs_eval(0), *histIP3DSig_centzone_vs_eval(0), *histIP3DBkg_pt_vs_eval(0), *histIP3DBkg_abseta_vs_eval(0), *histIP3DBkg_phi_vs_eval(0), *histIP3DBkg_centzone_vs_eval(0), *histIP3DOther_pt_vs_eval(0), *histIP3DOther_abseta_vs_eval(0), *histIP3DOther_phi_vs_eval(0), *histIP3DOther_centzone_vs_eval(0);
	TH2F *histJF_pt_vs_eval(0), *histJF_abseta_vs_eval(0), *histJF_phi_vs_eval(0), *histJF_centzone_vs_eval(0), *histJFSig_pt_vs_eval(0), *histJFSig_abseta_vs_eval(0), *histJFSig_phi_vs_eval(0), *histJFSig_centzone_vs_eval(0), *histJFBkg_pt_vs_eval(0), *histJFBkg_abseta_vs_eval(0), *histJFBkg_phi_vs_eval(0), *histJFBkg_centzone_vs_eval(0), *histJFOther_pt_vs_eval(0), *histJFOther_abseta_vs_eval(0), *histJFOther_phi_vs_eval(0), *histJFOther_centzone_vs_eval(0);
	
	TH1F *hist_chosen_pt(0), *hist_chosen_pt_vs_centzone_0_20(0), *hist_chosen_pt_vs_centzone_20_40(0), *hist_chosen_pt_vs_centzone_40_80(0), *hist_notchosen_pt(0), *hist_notchosen_pt_vs_centzone_0_20(0), *hist_notchosen_pt_vs_centzone_20_40(0), *hist_notchosen_pt_vs_centzone_40_80(0);

	if (Use["Likelihood"])    histLk      = new TH1F( "MVA_Likelihood",    "MVA_Likelihood",    nbin, -1, 1 );
	if (Use["LikelihoodD"])   histLkD     = new TH1F( "MVA_LikelihoodD",   "MVA_LikelihoodD",   nbin, -1, 0.9999 );
	if (Use["LikelihoodPCA"]) histLkPCA   = new TH1F( "MVA_LikelihoodPCA", "MVA_LikelihoodPCA", nbin, -1, 1 );
	if (Use["LikelihoodKDE"]) histLkKDE   = new TH1F( "MVA_LikelihoodKDE", "MVA_LikelihoodKDE", nbin,  -0.00001, 0.99999 );
	if (Use["LikelihoodMIX"]) histLkMIX   = new TH1F( "MVA_LikelihoodMIX", "MVA_LikelihoodMIX", nbin,  0, 1 );
	if (Use["PDERS"])         histPD      = new TH1F( "MVA_PDERS",         "MVA_PDERS",         nbin,  0, 1 );
	if (Use["PDERSD"])        histPDD     = new TH1F( "MVA_PDERSD",        "MVA_PDERSD",        nbin,  0, 1 );
	if (Use["PDERSPCA"])      histPDPCA   = new TH1F( "MVA_PDERSPCA",      "MVA_PDERSPCA",      nbin,  0, 1 );
	if (Use["KNN"])           histKNN     = new TH1F( "MVA_KNN",           "MVA_KNN",           nbin,  0, 1 );
	if (Use["HMatrix"])       histHm      = new TH1F( "MVA_HMatrix",       "MVA_HMatrix",       nbin, -0.95, 1.55 );
	if (Use["Fisher"])        histFi      = new TH1F( "MVA_Fisher",        "MVA_Fisher",        nbin, -4, 4 );
	if (Use["FisherG"])       histFiG     = new TH1F( "MVA_FisherG",       "MVA_FisherG",       nbin, -1, 1 );
	if (Use["BoostedFisher"]) histFiB     = new TH1F( "MVA_BoostedFisher", "MVA_BoostedFisher", nbin, -2, 2 );
	if (Use["LD"])            histLD      = new TH1F( "MVA_LD",            "MVA_LD",            nbin, -2, 2 );
	if (Use["MLP"])           histNn      = new TH1F( "MVA_MLP",           "MVA_MLP",           nbin, -1.25, 1.5 );
	if (Use["MLPBFGS"])       histNnbfgs  = new TH1F( "MVA_MLPBFGS",       "MVA_MLPBFGS",       nbin, -1.25, 1.5 );
	if (Use["MLPBNN"])        histNnbnn   = new TH1F( "MVA_MLPBNN",        "MVA_MLPBNN",        nbin, -1.25, 1.5 );
	if (Use["CFMlpANN"])      histNnC     = new TH1F( "MVA_CFMlpANN",      "MVA_CFMlpANN",      nbin,  0, 1 );
	if (Use["TMlpANN"])       histNnT     = new TH1F( "MVA_TMlpANN",       "MVA_TMlpANN",       nbin, -1.3, 1.3 );

//============================ USED ============================

	histSig_pt         = new TH1F( "MVA_SIGNAL_pt",         "MVA_SIGNAL_pt",         nbin,        lowlim_pt,     uplim_pt );
	histSig_eta        = new TH1F( "MVA_SIGNAL_eta",        "MVA_SIGNAL_eta",        nbin_abseta, lowlim_eta,    uplim_abseta );
	histSig_abseta     = new TH1F( "MVA_SIGNAL_abseta",     "MVA_SIGNAL_abseta",     nbin_abseta, lowlim_abseta, uplim_abseta );
	histSig_phi        = new TH1F( "MVA_SIGNAL_phi",        "MVA_SIGNAL_phi",        nbin_abseta, lowlim_phi,    uplim_phi );
	histSig_centzone   = new TH1F( "MVA_SIGNAL_centzone",   "MVA_SIGNAL_centzone",   nbin_cent,   lowlim_cent,   uplim_cent );
	histBkg_pt         = new TH1F( "MVA_Background_pt",     "MVA_Background_pt",     nbin,        lowlim_pt,     uplim_pt );
	histBkg_eta        = new TH1F( "MVA_Background_eta",    "MVA_Background_eta",    nbin_abseta, lowlim_eta,    uplim_abseta );
	histBkg_abseta     = new TH1F( "MVA_Background_abseta", "MVA_Background_abseta", nbin_abseta, lowlim_abseta, uplim_abseta );
	histBkg_phi        = new TH1F( "MVA_Background_phi",    "MVA_Background_phi",    nbin_abseta, lowlim_phi,    uplim_phi );
	histBkg_centzone   = new TH1F( "MVA_Background_centzone", "MVA_Background_centzone", nbin_cent, lowlim_cent, uplim_cent );
	histOther_pt       = new TH1F( "MVA_Other_pt",          "MVA_Other_pt",          nbin,        lowlim_pt,     uplim_pt );
	histOther_eta      = new TH1F( "MVA_Other_eta",         "MVA_Other_eta",         nbin_abseta, lowlim_eta,    uplim_abseta );
	histOther_abseta   = new TH1F( "MVA_Other_abseta",      "MVA_Other_abseta",      nbin_abseta, lowlim_abseta, uplim_abseta );
	histOther_phi      = new TH1F( "MVA_Other_phi",         "MVA_Other_phi",         nbin_abseta, lowlim_phi,    uplim_phi );
	histOther_centzone = new TH1F( "MVA_Other_centzone",    "MVA_Other_centzone",    nbin_cent,   lowlim_cent,   uplim_cent );

	hist_pt_vs_eta            = new TH2F( "pt_vs_eta",             "pt_vs_eta",             nbin_abseta, lowlim_eta,  uplim_abseta, nbin,        lowlim_pt,   uplim_pt );
	histSig_pt_vs_eta         = new TH2F( "Sig_pt_vs_eta",         "Sig_pt_vs_eta",         nbin_abseta, lowlim_eta,  uplim_abseta, nbin,        lowlim_pt,   uplim_pt );
	histBkg_pt_vs_eta         = new TH2F( "Bkg_pt_vs_eta",         "Bkg_pt_vs_eta",         nbin_abseta, lowlim_eta,  uplim_abseta, nbin,        lowlim_pt,   uplim_pt );
	histOther_pt_vs_eta       = new TH2F( "Other_pt_vs_eta",       "Other_pt_vs_eta",       nbin_abseta, lowlim_eta,  uplim_abseta, nbin,        lowlim_pt,   uplim_pt );
	hist_pt_vs_phi            = new TH2F( "pt_vs_phi",             "pt_vs_phi",             nbin_abseta, lowlim_phi,  uplim_phi,    nbin,        lowlim_pt,   uplim_pt );
	histSig_pt_vs_phi         = new TH2F( "Sig_pt_vs_phi",         "Sig_pt_vs_phi",         nbin_abseta, lowlim_phi,  uplim_phi,    nbin,        lowlim_pt,   uplim_pt );
	histBkg_pt_vs_phi         = new TH2F( "Bkg_pt_vs_phi",         "Bkg_pt_vs_phi",         nbin_abseta, lowlim_phi,  uplim_phi,    nbin,        lowlim_pt,   uplim_pt );
	histOther_pt_vs_phi       = new TH2F( "Other_pt_vs_phi",       "Other_pt_vs_phi",       nbin_abseta, lowlim_phi,  uplim_phi,    nbin,        lowlim_pt,   uplim_pt );
	hist_pt_vs_centzone       = new TH2F( "pt_vs_centzone",        "pt_vs_centzone",        nbin_abseta, lowlim_phi,  uplim_phi,    nbin,        lowlim_pt,   uplim_pt );
	histSig_pt_vs_centzone    = new TH2F( "Sig_pt_vs_centzone",    "Sig_pt_vs_centzone",    nbin_cent,   lowlim_cent, uplim_cent,   nbin,        lowlim_pt,   uplim_pt );
	histBkg_pt_vs_centzone    = new TH2F( "Bkg_pt_vs_centzone",    "Bkg_pt_vs_centzone",    nbin_cent,   lowlim_cent, uplim_cent,   nbin,        lowlim_pt,   uplim_pt );
	histOther_pt_vs_centzone  = new TH2F( "Other_pt_vs_centzone",  "Other_pt_vs_centzone",  nbin_cent,   lowlim_cent, uplim_cent,   nbin,        lowlim_pt,   uplim_pt );
	hist_phi_vs_eta           = new TH2F( "phi_vs_eta",            "phi_vs_eta",            nbin_abseta, lowlim_eta,  uplim_abseta, nbin_abseta, lowlim_phi,  uplim_phi );
	histSig_phi_vs_eta        = new TH2F( "Sig_phi_vs_eta",        "Sig_phi_vs_eta",        nbin_abseta, lowlim_eta,  uplim_abseta, nbin_abseta, lowlim_phi,  uplim_phi );
	histBkg_phi_vs_eta        = new TH2F( "Bkg_phi_vs_eta",        "Bkg_phi_vs_eta",        nbin_abseta, lowlim_eta,  uplim_abseta, nbin_abseta, lowlim_phi,  uplim_phi );
	histOther_phi_vs_eta      = new TH2F( "Other_phi_vs_eta",      "Other_phi_vs_eta",      nbin_abseta, lowlim_eta,  uplim_abseta, nbin_abseta, lowlim_phi,  uplim_phi );
	hist_phi_vs_centzone      = new TH2F( "phi_vs_centzone",       "phi_vs_centzone",       nbin_cent,   lowlim_cent, uplim_cent,   nbin_abseta, lowlim_phi,  uplim_phi );
	histSig_phi_vs_centzone   = new TH2F( "Sig_phi_vs_centzone",   "Sig_phi_vs_centzone",   nbin_cent,   lowlim_cent, uplim_cent,   nbin_abseta, lowlim_phi,  uplim_phi );
	histBkg_phi_vs_centzone   = new TH2F( "Bkg_phi_vs_centzone",   "Bkg_phi_vs_centzone",   nbin_cent,   lowlim_cent, uplim_cent,   nbin_abseta, lowlim_phi,  uplim_phi );
	histOther_phi_vs_centzone = new TH2F( "Other_phi_vs_centzone", "Other_phi_vs_centzone", nbin_cent,   lowlim_cent, uplim_cent,   nbin_abseta, lowlim_phi,  uplim_phi );
	hist_centzone_vs_eta      = new TH2F( "centzone_vs_eta",       "centzone_vs_eta",       nbin_abseta, lowlim_eta,  uplim_abseta, nbin_cent,   lowlim_cent, uplim_cent );
	histSig_centzone_vs_eta   = new TH2F( "Sig_centzone_vs_eta",   "Sig_centzone_vs_eta",   nbin_abseta, lowlim_eta,  uplim_abseta, nbin_cent,   lowlim_cent, uplim_cent );
	histBkg_centzone_vs_eta   = new TH2F( "Bkg_centzone_vs_eta",   "Bkg_centzone_vs_eta",   nbin_abseta, lowlim_eta,  uplim_abseta, nbin_cent,   lowlim_cent, uplim_cent );
	histOther_centzone_vs_eta = new TH2F( "Other_centzone_vs_eta", "Other_centzone_vs_eta", nbin_abseta, lowlim_eta,  uplim_abseta, nbin_cent,   lowlim_cent, uplim_cent );

	histIP2D      = new TH1F( "MVA_IP2D",            "MVA_IP2D",            nbin_ip3d, lowlim_ip3d, uplim_ip3d );
	histIP2DSig   = new TH1F( "MVA_IP2D_SIGNAL",     "MVA_IP2D_SIGNAL",     nbin_ip3d, lowlim_ip3d, uplim_ip3d );
	histIP2DBkg   = new TH1F( "MVA_IP2D_Background", "MVA_IP2D_Background", nbin_ip3d, lowlim_ip3d, uplim_ip3d );
	histIP2DOther = new TH1F( "MVA_IP2D_Other",      "MVA_IP2D_Other",      nbin_ip3d, lowlim_ip3d, uplim_ip3d );
	histIP3D      = new TH1F( "MVA_IP3D",            "MVA_IP3D",            nbin_ip3d, lowlim_ip3d, uplim_ip3d );
	histIP3DSig   = new TH1F( "MVA_IP3D_SIGNAL",     "MVA_IP3D_SIGNAL",     nbin_ip3d, lowlim_ip3d, uplim_ip3d );
	histIP3DBkg   = new TH1F( "MVA_IP3D_Background", "MVA_IP3D_Background", nbin_ip3d, lowlim_ip3d, uplim_ip3d );
	histIP3DOther = new TH1F( "MVA_IP3D_Other",      "MVA_IP3D_Other",      nbin_ip3d, lowlim_ip3d, uplim_ip3d );
	histJF        = new TH1F( "MVA_JF",              "MVA_JF",              nbin_jf,   lowlim_jf,   uplim_jf );
	histJFSig     = new TH1F( "MVA_JF_SIGNAL",       "MVA_JF_SIGNAL",       nbin_jf,   lowlim_jf,   uplim_jf );
	histJFBkg     = new TH1F( "MVA_JF_Background",   "MVA_JF_Background",   nbin_jf,   lowlim_jf,   uplim_jf );
	histJFOther   = new TH1F( "MVA_JF_Other",        "MVA_JF_Other",        nbin_jf,   lowlim_jf,   uplim_jf );
	
	histIP2D_pt_vs_eval      = new TH2F( "MVA_IP2D_pt_vs_eval",            "MVA_IP2D_pt_vs_eval",            nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin,  lowlim_pt, uplim_pt );
	histIP2DSig_pt_vs_eval   = new TH2F( "MVA_IP2D_SIGNAL_pt_vs_eval",     "MVA_IP2D_SIGNAL_pt_vs_eval",     nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin,  lowlim_pt, uplim_pt );
	histIP2DBkg_pt_vs_eval   = new TH2F( "MVA_IP2D_Background_pt_vs_eval", "MVA_IP2D_Background_pt_vs_eval", nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin,  lowlim_pt, uplim_pt );
	histIP2DOther_pt_vs_eval = new TH2F( "MVA_IP2D_Other_pt_vs_eval",      "MVA_IP2D_Other_pt_vs_eval",      nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin,  lowlim_pt, uplim_pt );
	histIP3D_pt_vs_eval      = new TH2F( "MVA_IP3D_pt_vs_eval",            "MVA_IP3D_pt_vs_eval",            nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin,  lowlim_pt, uplim_pt );
	histIP3DSig_pt_vs_eval   = new TH2F( "MVA_IP3D_SIGNAL_pt_vs_eval",     "MVA_IP3D_SIGNAL_pt_vs_eval",     nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin,  lowlim_pt, uplim_pt );
	histIP3DBkg_pt_vs_eval   = new TH2F( "MVA_IP3D_Background_pt_vs_eval", "MVA_IP3D_Background_pt_vs_eval", nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin,  lowlim_pt, uplim_pt );
	histIP3DOther_pt_vs_eval = new TH2F( "MVA_IP3D_Other_pt_vs_eval",      "MVA_IP3D_Other_pt_vs_eval",      nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin,  lowlim_pt, uplim_pt );
	histJF_pt_vs_eval        = new TH2F( "MVA_JF_pt_vs_eval",              "MVA_JF_pt_vs_eval",              nbin_jf,   lowlim_jf,   uplim_jf,   nbin,  lowlim_pt, uplim_pt );
	histJFSig_pt_vs_eval     = new TH2F( "MVA_JF_SIGNAL_pt_vs_eval",       "MVA_JF_SIGNAL_pt_vs_eval",       nbin_jf,   lowlim_jf,   uplim_jf,   nbin,  lowlim_pt, uplim_pt );
	histJFBkg_pt_vs_eval     = new TH2F( "MVA_JF_Background_pt_vs_eval",   "MVA_JF_Background_pt_vs_eval",   nbin_jf,   lowlim_jf,   uplim_jf,   nbin,  lowlim_pt, uplim_pt );
	histJFOther_pt_vs_eval   = new TH2F( "MVA_JF_Other_pt_vs_eval",        "MVA_JF_Other_pt_vs_eval",        nbin_jf,   lowlim_jf,   uplim_jf,   nbin,  lowlim_pt, uplim_pt );
	
	histIP2D_abseta_vs_eval      = new TH2F( "MVA_IP2D_abseta_vs_eval",            "MVA_IP2D_abseta_vs_eval",            nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_abseta, uplim_abseta );
	histIP2DSig_abseta_vs_eval   = new TH2F( "MVA_IP2D_SIGNAL_abseta_vs_eval",     "MVA_IP2D_SIGNAL_abseta_vs_eval",     nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_abseta, uplim_abseta );
	histIP2DBkg_abseta_vs_eval   = new TH2F( "MVA_IP2D_Background_abseta_vs_eval", "MVA_IP2D_Background_abseta_vs_eval", nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_abseta, uplim_abseta );
	histIP2DOther_abseta_vs_eval = new TH2F( "MVA_IP2D_Other_abseta_vs_eval",      "MVA_IP2D_Other_abseta_vs_eval",      nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_abseta, uplim_abseta );
	histIP3D_abseta_vs_eval      = new TH2F( "MVA_IP3D_abseta_vs_eval",            "MVA_IP3D_abseta_vs_eval",            nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_abseta, uplim_abseta );
	histIP3DSig_abseta_vs_eval   = new TH2F( "MVA_IP3D_SIGNAL_abseta_vs_eval",     "MVA_IP3D_SIGNAL_abseta_vs_eval",     nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_abseta, uplim_abseta );
	histIP3DBkg_abseta_vs_eval   = new TH2F( "MVA_IP3D_Background_abseta_vs_eval", "MVA_IP3D_Background_abseta_vs_eval", nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_abseta, uplim_abseta );
	histIP3DOther_abseta_vs_eval = new TH2F( "MVA_IP3D_Other_abseta_vs_eval",      "MVA_IP3D_Other_abseta_vs_eval",      nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_abseta, uplim_abseta );
	histJF_abseta_vs_eval        = new TH2F( "MVA_JF_abseta_vs_eval",              "MVA_JF_abseta_vs_eval",              nbin_jf,   lowlim_jf,   uplim_jf,   nbin_abseta, lowlim_abseta, uplim_abseta );
	histJFSig_abseta_vs_eval     = new TH2F( "MVA_JF_SIGNAL_abseta_vs_eval",       "MVA_JF_SIGNAL_abseta_vs_eval",       nbin_jf,   lowlim_jf,   uplim_jf,   nbin_abseta, lowlim_abseta, uplim_abseta );
	histJFBkg_abseta_vs_eval     = new TH2F( "MVA_JF_Background_abseta_vs_eval",   "MVA_JF_Background_abseta_vs_eval",   nbin_jf,   lowlim_jf,   uplim_jf,   nbin_abseta, lowlim_abseta, uplim_abseta );
	histJFOther_abseta_vs_eval   = new TH2F( "MVA_JF_Other_abseta_vs_eval",        "MVA_JF_Other_abseta_vs_eval",        nbin_jf,   lowlim_jf,   uplim_jf,   nbin_abseta, lowlim_abseta, uplim_abseta );
	
	histIP2D_phi_vs_eval      = new TH2F( "MVA_IP2D_phi_vs_eval",            "MVA_IP2D_phi_vs_eval",            nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_phi, uplim_phi );
	histIP2DSig_phi_vs_eval   = new TH2F( "MVA_IP2D_SIGNAL_phi_vs_eval",     "MVA_IP2D_SIGNAL_phi_vs_eval",     nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_phi, uplim_phi );
	histIP2DBkg_phi_vs_eval   = new TH2F( "MVA_IP2D_Background_phi_vs_eval", "MVA_IP2D_Background_phi_vs_eval", nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_phi, uplim_phi );
	histIP2DOther_phi_vs_eval = new TH2F( "MVA_IP2D_Other_phi_vs_eval",      "MVA_IP2D_Other_phi_vs_eval",      nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_phi, uplim_phi );
	histIP3D_phi_vs_eval      = new TH2F( "MVA_IP3D_phi_vs_eval",            "MVA_IP3D_phi_vs_eval",            nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_phi, uplim_phi );
	histIP3DSig_phi_vs_eval   = new TH2F( "MVA_IP3D_SIGNAL_phi_vs_eval",     "MVA_IP3D_SIGNAL_phi_vs_eval",     nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_phi, uplim_phi );
	histIP3DBkg_phi_vs_eval   = new TH2F( "MVA_IP3D_Background_phi_vs_eval", "MVA_IP3D_Background_phi_vs_eval", nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_phi, uplim_phi );
	histIP3DOther_phi_vs_eval = new TH2F( "MVA_IP3D_Other_phi_vs_eval",      "MVA_IP3D_Other_phi_vs_eval",      nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_abseta, lowlim_phi, uplim_phi );
	histJF_phi_vs_eval        = new TH2F( "MVA_JF_phi_vs_eval",              "MVA_JF_phi_vs_eval",              nbin_jf,   lowlim_jf,   uplim_jf,   nbin_abseta, lowlim_phi, uplim_phi );
	histJFSig_phi_vs_eval     = new TH2F( "MVA_JF_SIGNAL_phi_vs_eval",       "MVA_JF_SIGNAL_phi_vs_eval",       nbin_jf,   lowlim_jf,   uplim_jf,   nbin_abseta, lowlim_phi, uplim_phi );
	histJFBkg_phi_vs_eval     = new TH2F( "MVA_JF_Background_phi_vs_eval",   "MVA_JF_Background_phi_vs_eval",   nbin_jf,   lowlim_jf,   uplim_jf,   nbin_abseta, lowlim_phi, uplim_phi );
	histJFOther_phi_vs_eval   = new TH2F( "MVA_JF_Other_phi_vs_eval",        "MVA_JF_Other_phi_vs_eval",        nbin_jf,   lowlim_jf,   uplim_jf,   nbin_abseta, lowlim_phi, uplim_phi );

	histIP2D_centzone_vs_eval      = new TH2F( "MVA_IP2D_centzone_vs_eval",            "MVA_IP2D_centzone_vs_eval",            nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_cent, lowlim_cent, uplim_cent );
	histIP2DSig_centzone_vs_eval   = new TH2F( "MVA_IP2D_SIGNAL_centzone_vs_eval",     "MVA_IP2D_SIGNAL_centzone_vs_eval",     nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_cent, lowlim_cent, uplim_cent );
	histIP2DBkg_centzone_vs_eval   = new TH2F( "MVA_IP2D_Background_centzone_vs_eval", "MVA_IP2D_Background_centzone_vs_eval", nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_cent, lowlim_cent, uplim_cent );
	histIP2DOther_centzone_vs_eval = new TH2F( "MVA_IP2D_Other_centzone_vs_eval",      "MVA_IP2D_Other_centzone_vs_eval",      nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_cent, lowlim_cent, uplim_cent );
	histIP3D_centzone_vs_eval      = new TH2F( "MVA_IP3D_centzone_vs_eval",            "MVA_IP3D_centzone_vs_eval",            nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_cent, lowlim_cent, uplim_cent );
	histIP3DSig_centzone_vs_eval   = new TH2F( "MVA_IP3D_SIGNAL_centzone_vs_eval",     "MVA_IP3D_SIGNAL_centzone_vs_eval",     nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_cent, lowlim_cent, uplim_cent );
	histIP3DBkg_centzone_vs_eval   = new TH2F( "MVA_IP3D_Background_centzone_vs_eval", "MVA_IP3D_Background_centzone_vs_eval", nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_cent, lowlim_cent, uplim_cent );
	histIP3DOther_centzone_vs_eval = new TH2F( "MVA_IP3D_Other_centzone_vs_eval",      "MVA_IP3D_Other_centzone_vs_eval",      nbin_ip3d, lowlim_ip3d, uplim_ip3d, nbin_cent, lowlim_cent, uplim_cent );
	histJF_centzone_vs_eval        = new TH2F( "MVA_JF_centzone_vs_eval",              "MVA_JF_centzone_vs_eval",              nbin_jf,   lowlim_jf,   uplim_jf,   nbin_cent, lowlim_cent, uplim_cent );
	histJFSig_centzone_vs_eval     = new TH2F( "MVA_JF_SIGNAL_centzone_vs_eval",       "MVA_JF_SIGNAL_centzone_vs_eval",       nbin_jf,   lowlim_jf,   uplim_jf,   nbin_cent, lowlim_cent, uplim_cent );
	histJFBkg_centzone_vs_eval     = new TH2F( "MVA_JF_Background_centzone_vs_eval",   "MVA_JF_Background_centzone_vs_eval",   nbin_jf,   lowlim_jf,   uplim_jf,   nbin_cent, lowlim_cent, uplim_cent );
	histJFOther_centzone_vs_eval   = new TH2F( "MVA_JF_Other_centzone_vs_eval",        "MVA_JF_Other_centzone_vs_eval",        nbin_jf,   lowlim_jf,   uplim_jf,   nbin_cent, lowlim_cent, uplim_cent );

	if (Use["BDT"]) {
		histBdt      = new TH1F( "MVA_BDT",            "MVA_BDT",            nbin, lowlim_bdt, uplim_bdt );
		histBdtSig   = new TH1F( "MVA_BDT_SIGNAL",     "MVA_BDT_SIGNAL",     nbin, lowlim_bdt, uplim_bdt );
		histBdtBkg   = new TH1F( "MVA_BDT_Background", "MVA_BDT_Background", nbin, lowlim_bdt, uplim_bdt );
		histBdtOther = new TH1F( "MVA_BDT_Other",      "MVA_BDT_Other",      nbin, lowlim_bdt, uplim_bdt );
		histBdt_pt_vs_eval          = new TH2F( "MVA_BDT_pt_vs_eval",          "MVA_BDT_pt_vs_eval",          nbin, lowlim_bdt, uplim_bdt, nbin,        lowlim_pt,     uplim_pt);
		histBdtSig_pt_vs_eval       = new TH2F( "MVA_BDTSig_pt_vs_eval",       "MVA_BDTSig_pt_vs_eval",       nbin, lowlim_bdt, uplim_bdt, nbin,        lowlim_pt,     uplim_pt);
		histBdtBkg_pt_vs_eval       = new TH2F( "MVA_BDTBkg_pt_vs_eval",       "MVA_BDTBkg_pt_vs_eval",       nbin, lowlim_bdt, uplim_bdt, nbin,        lowlim_pt,     uplim_pt);
		histBdtOther_pt_vs_eval     = new TH2F( "MVA_BDTOther_pt_vs_eval",     "MVA_BDTOther_pt_vs_eval",     nbin, lowlim_bdt, uplim_bdt, nbin,        lowlim_pt,     uplim_pt);
		histBdt_abseta_vs_eval      = new TH2F( "MVA_BDT_abseta_vs_eval",      "MVA_BDT_abseta_vs_eval",      nbin, lowlim_bdt, uplim_bdt, nbin_abseta, lowlim_abseta, uplim_abseta);
		histBdtSig_abseta_vs_eval   = new TH2F( "MVA_BDTSig_abseta_vs_eval",   "MVA_BDTSig_abseta_vs_eval",   nbin, lowlim_bdt, uplim_bdt, nbin_abseta, lowlim_abseta, uplim_abseta);
		histBdtBkg_abseta_vs_eval   = new TH2F( "MVA_BDTBkg_abseta_vs_eval",   "MVA_BDTBkg_abseta_vs_eval",   nbin, lowlim_bdt, uplim_bdt, nbin_abseta, lowlim_abseta, uplim_abseta);
		histBdtOther_abseta_vs_eval = new TH2F( "MVA_BDTOther_abseta_vs_eval", "MVA_BDTOther_abseta_vs_eval", nbin, lowlim_bdt, uplim_bdt, nbin_abseta, lowlim_abseta, uplim_abseta);
		histBdt_phi_vs_eval         = new TH2F( "MVA_BDT_phi_vs_eval",         "MVA_BDT_phi_vs_eval",         nbin, lowlim_bdt, uplim_bdt, nbin_abseta, lowlim_phi,    uplim_phi);
		histBdtSig_phi_vs_eval      = new TH2F( "MVA_BDTSig_phi_vs_eval",      "MVA_BDTSig_phi_vs_eval",      nbin, lowlim_bdt, uplim_bdt, nbin_abseta, lowlim_phi,    uplim_phi);
		histBdtBkg_phi_vs_eval      = new TH2F( "MVA_BDTBkg_phi_vs_eval",      "MVA_BDTBkg_phi_vs_eval",      nbin, lowlim_bdt, uplim_bdt, nbin_abseta, lowlim_phi,    uplim_phi);
		histBdtOther_phi_vs_eval    = new TH2F( "MVA_BDTOther_phi_vs_eval",    "MVA_BDTOther_phi_vs_eval",    nbin, lowlim_bdt, uplim_bdt, nbin_abseta, lowlim_phi,    uplim_phi);
		histBdt_centzone_vs_eval      = new TH2F( "MVA_BDT_centzone_vs_eval",      "MVA_BDT_centzone_vs_eval",      nbin, lowlim_bdt, uplim_bdt, nbin_cent, lowlim_cent, uplim_cent);
		histBdtSig_centzone_vs_eval   = new TH2F( "MVA_BDTSig_centzone_vs_eval",   "MVA_BDTSig_centzone_vs_eval",   nbin, lowlim_bdt, uplim_bdt, nbin_cent, lowlim_cent, uplim_cent);
		histBdtBkg_centzone_vs_eval   = new TH2F( "MVA_BDTBkg_centzone_vs_eval",   "MVA_BDTBkg_centzone_vs_eval",   nbin, lowlim_bdt, uplim_bdt, nbin_cent, lowlim_cent, uplim_cent);
		histBdtOther_centzone_vs_eval = new TH2F( "MVA_BDTOther_centzone_vs_eval", "MVA_BDTOther_centzone_vs_eval", nbin, lowlim_bdt, uplim_bdt, nbin_cent, lowlim_cent, uplim_cent);

		hist_chosen_pt    =  new TH1F( "chosen_pt",    "chosen_pt",    nbin, lowlim_pt, uplim_pt );
		hist_chosen_pt_vs_centzone_0_20     =  new TH1F( "chosen_pt_vs_centzone_0_20",     "chosen_pt_vs_centzone_0_20",     nbin, lowlim_pt, uplim_pt );
		hist_chosen_pt_vs_centzone_20_40    =  new TH1F( "chosen_pt_vs_centzone_20_40",    "chosen_pt_vs_centzone_20_40",    nbin, lowlim_pt, uplim_pt );
		hist_chosen_pt_vs_centzone_40_80    =  new TH1F( "chosen_pt_vs_centzone_40_80",    "chosen_pt_vs_centzone_40_80",    nbin, lowlim_pt, uplim_pt );
		hist_notchosen_pt =  new TH1F( "notchosen_pt", "notchosen_pt", nbin, lowlim_pt, uplim_pt );
		hist_notchosen_pt_vs_centzone_0_20  =  new TH1F( "notchosen_pt_vs_centzone_0_20",  "notchosen_pt_vs_centzone_0_20",  nbin, lowlim_pt, uplim_pt );
		hist_notchosen_pt_vs_centzone_20_40 =  new TH1F( "notchosen_pt_vs_centzone_20_40", "notchosen_pt_vs_centzone_20_40", nbin, lowlim_pt, uplim_pt );
		hist_notchosen_pt_vs_centzone_40_80 =  new TH1F( "notchosen_pt_vs_centzone_40_80", "notchosen_pt_vs_centzone_40_80", nbin, lowlim_pt, uplim_pt );
	}

//===============================================================

	if (Use["BDTD"])      histBdtD  = new TH1F( "MVA_BDTD",      "MVA_BDTD",      nbin, -0.8, 0.8 );
	if (Use["BDTG"])      histBdtG  = new TH1F( "MVA_BDTG",      "MVA_BDTG",      nbin, -1.0, 1.0 );
	if (Use["RuleFit"])   histRf    = new TH1F( "MVA_RuleFit",   "MVA_RuleFit",   nbin, -2.0, 2.0 );
	if (Use["SVM_Gauss"]) histSVMG  = new TH1F( "MVA_SVM_Gauss", "MVA_SVM_Gauss", nbin,  0.0, 1.0 );
	if (Use["SVM_Poly"])  histSVMP  = new TH1F( "MVA_SVM_Poly",  "MVA_SVM_Poly",  nbin,  0.0, 1.0 );
	if (Use["SVM_Lin"])   histSVML  = new TH1F( "MVA_SVM_Lin",   "MVA_SVM_Lin",   nbin,  0.0, 1.0 );
	if (Use["FDA_MT"])    histFDAMT = new TH1F( "MVA_FDA_MT",    "MVA_FDA_MT",    nbin, -2.0, 3.0 );
	if (Use["FDA_GA"])    histFDAGA = new TH1F( "MVA_FDA_GA",    "MVA_FDA_GA",    nbin, -2.0, 3.0 );
	if (Use["Category"])  histCat   = new TH1F( "MVA_Category",  "MVA_Category",  nbin, -2.0, 2.0 );
	if (Use["Plugin"])    histPBdt  = new TH1F( "MVA_PBDT",      "MVA_BDT",       nbin, -0.8, 0.8 );

	// PDEFoam also returns per-event error, fill in histogram, and also fill significance
	if (Use["PDEFoam"]) {
		histPDEFoam    = new TH1F( "MVA_PDEFoam",    "MVA_PDEFoam",              nbin, 0, 1 );
		histPDEFoamErr = new TH1F( "MVA_PDEFoamErr", "MVA_PDEFoam error",        nbin, 0, 1 );
		histPDEFoamSig = new TH1F( "MVA_PDEFoamSig", "MVA_PDEFoam significance", nbin, 0, 10 );
	}

	// Book example histogram for probability (the other methods are done similarly)
	TH1F *probHistFi(0), *rarityHistFi(0);
	if (Use["Fisher"]) {
		probHistFi   = new TH1F( "MVA_Fisher_Proba",  "MVA_Fisher_Proba",  nbin, 0, 1 );
		rarityHistFi = new TH1F( "MVA_Fisher_Rarity", "MVA_Fisher_Rarity", nbin, 0, 1 );
	}

//---------------------------------------------------------------

	// ---- Create the event Tree
	// (it is also possible to use ASCII format as input -> see TMVA Users Guide)

	std::cout << "---- Select signal sample" << std::endl;
	TChain *inputTree = new TChain ("jetdata");

	if (pp_flag) {
		if (test_flag) inputTree->Add("testdata/ttbar/*.root");
		else           inputTree->Add("/lstore/calo/HI/Estagio_verao_2018/BDTntuples/ttbar/*.root");
	} else {
		if (test_flag) {
			inputTree->Add("testdata/PbPb_JZ1_2GeV/*.root");
			inputTree->Add("testdata/PbPb_JZ2_2GeV/*.root");
			inputTree->Add("testdata/PbPb_JZ3_2GeV/*.root");
		} else {
			inputTree->Add("/lstore/calo/HI/Estagio_verao_2018/BDTntuples/HI_full2gev/PbPb_JZ1_2GeV/*.root");
			inputTree->Add("/lstore/calo/HI/Estagio_verao_2018/BDTntuples/HI_full2gev/PbPb_JZ2_2GeV/*.root");
			inputTree->Add("/lstore/calo/HI/Estagio_verao_2018/BDTntuples/HI_full2gev/PbPb_JZ3_2GeV/*.root");
		}
	}

	// Prepare the event tree
	// - here the variable names have to correspond to your tree
	// - you can use the same variables as above which is slightly faster,
	//   but you can also use different ones and copy the values inside the event loop

	inputTree->SetBranchAddress( "out_pt", &out_pt );
	inputTree->SetBranchAddress( "out_abseta", &out_abseta );

	// inputTree->SetBranchAddress( "out_ip2d_pb", &out_ip2d_pb );
	// inputTree->SetBranchAddress( "out_ip2d_pc", &out_ip2d_pc );
	// inputTree->SetBranchAddress( "out_ip2d_pu", &out_ip2d_pu );
	// inputTree->SetBranchAddress( "out_ip2d_llr", &out_ip2d_llr );
	inputTree->SetBranchAddress( "out_ip2d_cllr_pbpu", &out_ip2d_cllr_pbpu );
	inputTree->SetBranchAddress( "out_ip2d_cllr_pbpc", &out_ip2d_cllr_pbpc );
	inputTree->SetBranchAddress( "out_ip2d_cllr_pcpu", &out_ip2d_cllr_pcpu );

	// inputTree->SetBranchAddress( "out_ip3d_pb", &out_ip3d_pb );
	// inputTree->SetBranchAddress( "out_ip3d_pc", &out_ip3d_pc );
	// inputTree->SetBranchAddress( "out_ip3d_pu", &out_ip3d_pu );
	// inputTree->SetBranchAddress( "out_ip3d_llr", &out_ip3d_llr );
	inputTree->SetBranchAddress( "out_ip3d_cllr_pbpu", &out_ip3d_cllr_pbpu );
	inputTree->SetBranchAddress( "out_ip3d_cllr_pbpc", &out_ip3d_cllr_pbpc );
	inputTree->SetBranchAddress( "out_ip3d_cllr_pcpu", &out_ip3d_cllr_pcpu );

	// inputTree->SetBranchAddress( "out_sv1_Nvtx", &out_sv1_Nvtx );
	inputTree->SetBranchAddress( "out_sv1_ntrkv", &out_sv1_ntrkv );
	inputTree->SetBranchAddress( "out_sv1_n2t", &out_sv1_n2t );
	inputTree->SetBranchAddress( "out_sv1_m", &out_sv1_m );
	inputTree->SetBranchAddress( "out_sv1_efc", &out_sv1_efc );
	inputTree->SetBranchAddress( "out_sv1_sig3d", &out_sv1_sig3d );
	// inputTree->SetBranchAddress( "out_sv1_normdist", &out_sv1_normdist );
	inputTree->SetBranchAddress( "out_sv1_deltaR", &out_sv1_deltaR );
	inputTree->SetBranchAddress( "out_sv1_Lxy", &out_sv1_Lxy);
	inputTree->SetBranchAddress( "out_sv1_L3d", &out_sv1_L3d );

	// inputTree->SetBranchAddress( "out_jf_pb", &out_jf_pb );
	// inputTree->SetBranchAddress( "out_jf_pc", &out_jf_pc );
	// inputTree->SetBranchAddress( "out_jf_pu", &out_jf_pu );
	inputTree->SetBranchAddress( "out_jf_llr", &out_jf_llr );
	inputTree->SetBranchAddress( "out_jf_m", &out_jf_m );
	// inputTree->SetBranchAddress( "out_jf_mUncorr", &out_jf_mUncorr );
	inputTree->SetBranchAddress( "out_jf_efc", &out_jf_efc );
	// inputTree->SetBranchAddress( "out_jf_deta", &out_jf_deta );
	// inputTree->SetBranchAddress( "out_jf_dphi", &out_jf_dphi );
	inputTree->SetBranchAddress( "out_jf_dRFlightDir", &out_jf_dRFlightDir );
	inputTree->SetBranchAddress( "out_jf_ntrkAtVx", &out_jf_nrtkAtVx );
	inputTree->SetBranchAddress( "out_jf_nvtx", &out_jf_nvtx );
	inputTree->SetBranchAddress( "out_jf_sig3d", &out_jf_sig3d );
	inputTree->SetBranchAddress( "out_jf_nvtx1t", &out_jf_nvtx1t );
	inputTree->SetBranchAddress( "out_jf_n2t", &out_jf_n2t );
	// inputTree->SetBranchAddress( "out_jf_VTXsize", &out_jf_VTXsize );
	// inputTree->SetBranchAddress( "out_jf_phi", &out_jf_phi );
	// inputTree->SetBranchAddress( "out_jf_theta", &out_jf_theta );
	// inputTree->SetBranchAddress( "out_jf_theta_err", &out_jf_theta_err );
	// inputTree->SetBranchAddress( "out_jf_phi_err", &out_jf_phi_err );

	// Spectator variables
	inputTree->SetBranchAddress( "out_JZ", &out_JZ ); // [0,5]
	inputTree->SetBranchAddress( "out_JZweight", &out_JZweight );
	inputTree->SetBranchAddress( "out_evweight", &out_evweight );
	// inputTree->SetBranchAddress( "out_FCalET", &out_FCalET );
	inputTree->SetBranchAddress( "out_centzone", &out_centzone ); // {-1} U [1,9]
	inputTree->SetBranchAddress( "out_eta", &out_eta );
	inputTree->SetBranchAddress( "out_phi", &out_phi );
	inputTree->SetBranchAddress( "out_truthflav", &out_truthflav );

	// Efficiency calculator for cut method
	Int_t    nSelCutsGA = 0;
	Double_t effS       = 0.7;

//---------------------------------------------------------------

	// ---- Event loop

	Long64_t inputEntries = inputTree->GetEntries();
	std::cout << "---- Processing: " << inputEntries << " events" << std::endl;
	
	// Start stopwatch
	TStopwatch sw;
	sw.Start();

	// Change these according to input flavours
	// out_truthflav: {0=Light, 4=Charm, 5=Bottom}
	Int_t signal_trueflavour = 5;
	Int_t bkg_trueflavour    = 0;
	Int_t other_trueflavour  = 4;

	Float_t evweight      = 1.;
	Int_t zeroweight_evts = 0;
	Int_t total_evts      = 0;
	Int_t total_signal    = 0;
	Int_t aftercut_evts   = 0;
	Int_t aftercut_signal = 0;

	Float_t bdt_select50sig; if (pp_flag) bdt_select50sig = 0.399847; else bdt_select50sig = 0.115386;
	Float_t bdt_select50sig_0_20 = 0.0929022;
	Float_t bdt_select50sig_20_40 = 0.151295;
	Float_t bdt_select50sig_40_80 = 0.168434;

	for (Long64_t ievt=0; ievt<inputEntries; ievt++) {
		if (ievt%100000 == 0) std::cout << "---- ... Processing event: " << ievt << std::endl;

		inputTree->GetEntry(ievt);

		total_evts++;
		if (out_truthflav == signal_trueflavour) total_signal++;

		// Condition to apply general cuts
		if (out_abseta<2.5 && out_pt>100000) { // Falta usar out_centzone

			aftercut_evts++;
			if (out_truthflav == signal_trueflavour) aftercut_signal++;

			// Cast all Integers as Floats ---> EvaluateMVA needs floats !!!
			outfl_sv1_ntrkv = (Float_t) out_sv1_ntrkv; 
			outfl_sv1_n2t   = (Float_t) out_sv1_n2t; 
			outfl_jf_nvtx1t = (Float_t) out_jf_nvtx1t; 
			outfl_jf_n2t    = (Float_t) out_jf_n2t; 
			outfl_jf_nvtx   = (Float_t) out_jf_nvtx;
			outfl_JZ        = (Float_t) out_JZ;
			outfl_centzone  = (Float_t) out_centzone;
			outfl_truthflav = (Float_t) out_truthflav;

			// Event weight used to fill histograms
			if (out_centzone == -1) evweight = 1.;
			else                    evweight = out_JZweight*out_evweight;

			if (evweight < 0.001) zeroweight_evts++;
			// if (ievt%1000 == 0) std::cout << "---- Event weight: " << evweight << std::endl;

			// ---- Return the MVA outputs and fill into histograms

			if (Use["CutsGA"]) {
			// Cuts is a special case: give the desired signal efficiency
				Bool_t passed = reader->EvaluateMVA( "CutsGA method", effS );
				if (passed) nSelCutsGA++;
			}

			if (Use["Likelihood"   ])   histLk    ->Fill( reader->EvaluateMVA( "Likelihood method"    ) );
			if (Use["LikelihoodD"  ])   histLkD   ->Fill( reader->EvaluateMVA( "LikelihoodD method"   ) );
			if (Use["LikelihoodPCA"])   histLkPCA ->Fill( reader->EvaluateMVA( "LikelihoodPCA method" ) );
			if (Use["LikelihoodKDE"])   histLkKDE ->Fill( reader->EvaluateMVA( "LikelihoodKDE method" ) );
			if (Use["LikelihoodMIX"])   histLkMIX ->Fill( reader->EvaluateMVA( "LikelihoodMIX method" ) );
			if (Use["PDERS"        ])   histPD    ->Fill( reader->EvaluateMVA( "PDERS method"         ) );
			if (Use["PDERSD"       ])   histPDD   ->Fill( reader->EvaluateMVA( "PDERSD method"        ) );
			if (Use["PDERSPCA"     ])   histPDPCA ->Fill( reader->EvaluateMVA( "PDERSPCA method"      ) );
			if (Use["KNN"          ])   histKNN   ->Fill( reader->EvaluateMVA( "KNN method"           ) );
			if (Use["HMatrix"      ])   histHm    ->Fill( reader->EvaluateMVA( "HMatrix method"       ) );
			if (Use["Fisher"       ])   histFi    ->Fill( reader->EvaluateMVA( "Fisher method"        ) );
			if (Use["FisherG"      ])   histFiG   ->Fill( reader->EvaluateMVA( "FisherG method"       ) );
			if (Use["BoostedFisher"])   histFiB   ->Fill( reader->EvaluateMVA( "BoostedFisher method" ) );
			if (Use["LD"           ])   histLD    ->Fill( reader->EvaluateMVA( "LD method"            ) );
			if (Use["MLP"          ])   histNn    ->Fill( reader->EvaluateMVA( "MLP method"           ) );
			if (Use["MLPBFGS"      ])   histNnbfgs->Fill( reader->EvaluateMVA( "MLPBFGS method"       ) );
			if (Use["MLPBNN"       ])   histNnbnn ->Fill( reader->EvaluateMVA( "MLPBNN method"        ) );
			if (Use["CFMlpANN"     ])   histNnC   ->Fill( reader->EvaluateMVA( "CFMlpANN method"      ) );
			if (Use["TMlpANN"      ])   histNnT   ->Fill( reader->EvaluateMVA( "TMlpANN method"       ) );

//============================ USED ============================

			histIP2D               ->Fill( out_ip2d_cllr_pbpu,             evweight );
			histIP3D               ->Fill( out_ip3d_cllr_pbpu,             evweight );
			histJF                 ->Fill( out_jf_llr,                     evweight );
			histIP2D_pt_vs_eval    ->Fill( out_ip2d_cllr_pbpu, out_pt,     evweight );
			histIP3D_pt_vs_eval    ->Fill( out_ip3d_cllr_pbpu, out_pt,     evweight );
			histJF_pt_vs_eval      ->Fill( out_jf_llr,         out_pt,     evweight );
			histIP2D_abseta_vs_eval->Fill( out_ip2d_cllr_pbpu, out_abseta, evweight );
			histIP3D_abseta_vs_eval->Fill( out_ip3d_cllr_pbpu, out_abseta, evweight );
			histJF_abseta_vs_eval  ->Fill( out_jf_llr,         out_abseta, evweight );
			histIP2D_phi_vs_eval   ->Fill( out_ip2d_cllr_pbpu, out_phi,    evweight );
			histIP3D_phi_vs_eval   ->Fill( out_ip3d_cllr_pbpu, out_phi,    evweight );
			histJF_phi_vs_eval     ->Fill( out_jf_llr,         out_phi,    evweight );
			if (!pp_flag) histIP2D_centzone_vs_eval->Fill( out_ip2d_cllr_pbpu, out_centzone, evweight );
			if (!pp_flag) histIP3D_centzone_vs_eval->Fill( out_ip3d_cllr_pbpu, out_centzone, evweight );
			if (!pp_flag) histJF_centzone_vs_eval  ->Fill( out_jf_llr,         out_centzone, evweight );

			hist_pt_vs_eta ->Fill( out_eta, out_pt,  evweight );
			hist_pt_vs_phi ->Fill( out_phi, out_pt,  evweight );
			hist_phi_vs_eta->Fill( out_eta, out_phi, evweight );
			if (!pp_flag) hist_pt_vs_centzone ->Fill( out_centzone, out_pt,       evweight );
			if (!pp_flag) hist_phi_vs_centzone->Fill( out_centzone, out_phi,      evweight );
			if (!pp_flag) hist_centzone_vs_eta->Fill( out_eta,      out_centzone, evweight );

			if (out_truthflav == signal_trueflavour) {
				histSig_pt    ->Fill( out_pt,             evweight );
				histSig_eta   ->Fill( out_eta,            evweight );
				histSig_abseta->Fill( out_abseta,         evweight );
				histSig_phi   ->Fill( out_phi,            evweight );
				if (!pp_flag) histSig_centzone->Fill( out_centzone, evweight );
				histIP2DSig   ->Fill( out_ip2d_cllr_pbpu, evweight );
				histIP3DSig   ->Fill( out_ip3d_cllr_pbpu, evweight );
				histJFSig     ->Fill( out_jf_llr,         evweight );
				histIP2DSig_pt_vs_eval    ->Fill( out_ip2d_cllr_pbpu, out_pt,     evweight );
				histIP3DSig_pt_vs_eval    ->Fill( out_ip3d_cllr_pbpu, out_pt,     evweight );
				histJFSig_pt_vs_eval      ->Fill( out_jf_llr,         out_pt,     evweight );
				histIP2DSig_abseta_vs_eval->Fill( out_ip2d_cllr_pbpu, out_abseta, evweight );
				histIP3DSig_abseta_vs_eval->Fill( out_ip3d_cllr_pbpu, out_abseta, evweight );
				histJFSig_abseta_vs_eval  ->Fill( out_jf_llr,         out_abseta, evweight );
				histIP2DSig_phi_vs_eval   ->Fill( out_ip2d_cllr_pbpu, out_phi,    evweight );
				histIP3DSig_phi_vs_eval   ->Fill( out_ip3d_cllr_pbpu, out_phi,    evweight );
				histJFSig_phi_vs_eval     ->Fill( out_jf_llr,         out_phi,    evweight );
				if (!pp_flag) histIP2DSig_centzone_vs_eval->Fill( out_ip2d_cllr_pbpu, out_centzone, evweight );
				if (!pp_flag) histIP3DSig_centzone_vs_eval->Fill( out_ip3d_cllr_pbpu, out_centzone, evweight );
				if (!pp_flag) histJFSig_centzone_vs_eval  ->Fill( out_jf_llr,         out_centzone, evweight );
				histSig_pt_vs_eta         ->Fill( out_eta,            out_pt,     evweight );   
				histSig_pt_vs_phi         ->Fill( out_phi,            out_pt,     evweight ); 
				histSig_phi_vs_eta        ->Fill( out_eta,            out_phi,    evweight );
				if (!pp_flag) histSig_pt_vs_centzone      ->Fill( out_centzone,       out_pt,       evweight );
				if (!pp_flag) histSig_phi_vs_centzone     ->Fill( out_centzone,       out_phi,      evweight );
				if (!pp_flag) histSig_centzone_vs_eta     ->Fill( out_eta,            out_centzone, evweight );
			}

			if (out_truthflav == bkg_trueflavour) {
				histBkg_pt    ->Fill( out_pt,             evweight );
				histBkg_eta   ->Fill( out_eta,            evweight );
				histBkg_abseta->Fill( out_abseta,         evweight );
				histBkg_phi   ->Fill( out_phi,            evweight );
				if (!pp_flag) histBkg_centzone->Fill( out_centzone, evweight );
				histIP2DBkg   ->Fill( out_ip2d_cllr_pbpu, evweight );
				histIP3DBkg   ->Fill( out_ip3d_cllr_pbpu, evweight );
				histJFBkg     ->Fill( out_jf_llr,         evweight );
				histIP2DBkg_pt_vs_eval    ->Fill( out_ip2d_cllr_pbpu, out_pt,     evweight );
				histIP3DBkg_pt_vs_eval    ->Fill( out_ip3d_cllr_pbpu, out_pt,     evweight );
				histJFBkg_pt_vs_eval      ->Fill( out_jf_llr,         out_pt,     evweight );
				histIP2DBkg_abseta_vs_eval->Fill( out_ip2d_cllr_pbpu, out_abseta, evweight );
				histIP3DBkg_abseta_vs_eval->Fill( out_ip3d_cllr_pbpu, out_abseta, evweight );
				histJFBkg_abseta_vs_eval  ->Fill( out_jf_llr,         out_abseta, evweight );
				histIP2DBkg_phi_vs_eval   ->Fill( out_ip2d_cllr_pbpu, out_phi,    evweight );
				histIP3DBkg_phi_vs_eval   ->Fill( out_ip3d_cllr_pbpu, out_phi,    evweight );
				histJFBkg_phi_vs_eval     ->Fill( out_jf_llr,         out_phi,    evweight );
				if (!pp_flag) histIP2DBkg_centzone_vs_eval->Fill( out_ip2d_cllr_pbpu, out_centzone, evweight );
				if (!pp_flag) histIP3DBkg_centzone_vs_eval->Fill( out_ip3d_cllr_pbpu, out_centzone, evweight );
				if (!pp_flag) histJFBkg_centzone_vs_eval  ->Fill( out_jf_llr,         out_centzone, evweight );
				histBkg_pt_vs_eta         ->Fill( out_eta,            out_pt,     evweight ); 
				histBkg_pt_vs_phi         ->Fill( out_phi,            out_pt,     evweight );
				histBkg_phi_vs_eta        ->Fill( out_eta,            out_phi,    evweight );
				if (!pp_flag) histBkg_pt_vs_centzone      ->Fill( out_centzone,       out_pt,       evweight );
				if (!pp_flag) histBkg_phi_vs_centzone     ->Fill( out_centzone,       out_phi,      evweight );
				if (!pp_flag) histBkg_centzone_vs_eta     ->Fill( out_eta,            out_centzone, evweight );
			}

			if (out_truthflav == other_trueflavour) {
				histOther_pt    ->Fill( out_pt,             evweight );
				histOther_eta   ->Fill( out_eta,            evweight );
				histOther_abseta->Fill( out_abseta,         evweight );
				histOther_phi   ->Fill( out_phi,            evweight );
				if (!pp_flag) histOther_centzone->Fill( out_centzone, evweight );
				histIP2DOther   ->Fill( out_ip2d_cllr_pbpu, evweight );
				histIP3DOther   ->Fill( out_ip3d_cllr_pbpu, evweight );
				histJFOther     ->Fill( out_jf_llr,         evweight );
				histIP2DOther_pt_vs_eval    ->Fill( out_ip2d_cllr_pbpu, out_pt,     evweight );
				histIP3DOther_pt_vs_eval    ->Fill( out_ip3d_cllr_pbpu, out_pt,     evweight );
				histJFOther_pt_vs_eval      ->Fill( out_jf_llr,         out_pt,     evweight );
				histIP2DOther_abseta_vs_eval->Fill( out_ip2d_cllr_pbpu, out_abseta, evweight );
				histIP3DOther_abseta_vs_eval->Fill( out_ip3d_cllr_pbpu, out_abseta, evweight );
				histJFOther_abseta_vs_eval  ->Fill( out_jf_llr,         out_abseta, evweight );
				histIP2DOther_phi_vs_eval   ->Fill( out_ip2d_cllr_pbpu, out_phi,    evweight );
				histIP3DOther_phi_vs_eval   ->Fill( out_ip3d_cllr_pbpu, out_phi,    evweight );
				histJFOther_phi_vs_eval     ->Fill( out_jf_llr,         out_phi,    evweight );
				if (!pp_flag) histIP2DOther_centzone_vs_eval->Fill( out_ip2d_cllr_pbpu, out_centzone, evweight );
				if (!pp_flag) histIP3DOther_centzone_vs_eval->Fill( out_ip3d_cllr_pbpu, out_centzone, evweight );
				if (!pp_flag) histJFOther_centzone_vs_eval  ->Fill( out_jf_llr,         out_centzone, evweight );  
				histOther_pt_vs_eta         ->Fill( out_eta,            out_pt,     evweight );
				histOther_pt_vs_phi         ->Fill( out_phi,            out_pt,     evweight );
				histOther_phi_vs_eta        ->Fill( out_eta,            out_phi,    evweight );
				if (!pp_flag) histOther_pt_vs_centzone      ->Fill( out_centzone,       out_pt,       evweight );
				if (!pp_flag) histOther_phi_vs_centzone     ->Fill( out_centzone,       out_phi,      evweight );
				if (!pp_flag) histOther_centzone_vs_eta     ->Fill( out_eta,            out_centzone, evweight );
			}

			if (Use["BDT"          ]) {
				Float_t bdt_method = reader->EvaluateMVA( "BDT method" );

				histBdt               ->Fill( bdt_method,             evweight );
				histBdt_pt_vs_eval    ->Fill( bdt_method, out_pt,     evweight );
				histBdt_abseta_vs_eval->Fill( bdt_method, out_abseta, evweight );
				histBdt_phi_vs_eval   ->Fill( bdt_method, out_phi,    evweight );
				if (!pp_flag) histBdt_centzone_vs_eval->Fill( bdt_method, out_centzone, evweight );
				
				if (bdt_method>=bdt_select50sig)
					hist_chosen_pt->Fill( out_pt, evweight );
				if (bdt_method<bdt_select50sig)
					hist_notchosen_pt->Fill( out_pt, evweight );
				if (!pp_flag) {
					if (bdt_method>=bdt_select50sig_0_20  && (out_centzone==1 || out_centzone==2))
						hist_chosen_pt_vs_centzone_0_20->Fill( out_pt, evweight );
					if (bdt_method<bdt_select50sig_0_20   && (out_centzone==1 || out_centzone==2))
						hist_notchosen_pt_vs_centzone_0_20->Fill( out_pt, evweight );
					if (bdt_method>=bdt_select50sig_20_40 && (out_centzone==3 || out_centzone==4))
						hist_chosen_pt_vs_centzone_20_40->Fill( out_pt, evweight );
					if (bdt_method<bdt_select50sig_20_40  && (out_centzone==3 || out_centzone==4))
						hist_notchosen_pt_vs_centzone_20_40->Fill( out_pt, evweight );
					if (bdt_method>=bdt_select50sig_40_80 && (out_centzone==5 || out_centzone==6 || out_centzone==7 || out_centzone==8))
						hist_chosen_pt_vs_centzone_40_80->Fill( out_pt, evweight );
					if (bdt_method<bdt_select50sig_40_80  && (out_centzone==5 || out_centzone==6 || out_centzone==7 || out_centzone==8))
						hist_notchosen_pt_vs_centzone_40_80->Fill( out_pt, evweight );
				}

				if (out_truthflav == signal_trueflavour)  {
					histBdtSig               ->Fill( bdt_method,             evweight );
					histBdtSig_pt_vs_eval    ->Fill( bdt_method, out_pt,     evweight );
					histBdtSig_abseta_vs_eval->Fill( bdt_method, out_abseta, evweight );
					histBdtSig_phi_vs_eval   ->Fill( bdt_method, out_phi,    evweight );
					if (!pp_flag) histBdtSig_centzone_vs_eval->Fill( bdt_method, out_centzone, evweight );
				}

				if (out_truthflav == bkg_trueflavour) {
					histBdtBkg               ->Fill( bdt_method,             evweight );
					histBdtBkg_pt_vs_eval    ->Fill( bdt_method, out_pt,     evweight );
					histBdtBkg_abseta_vs_eval->Fill( bdt_method, out_abseta, evweight );
					histBdtBkg_phi_vs_eval   ->Fill( bdt_method, out_phi,    evweight );
					if (!pp_flag) histBdtBkg_centzone_vs_eval->Fill( bdt_method, out_centzone, evweight );
				}

				if (out_truthflav == other_trueflavour) {
					histBdtOther               ->Fill( bdt_method,             evweight );
					histBdtOther_pt_vs_eval    ->Fill( bdt_method, out_pt,     evweight );
					histBdtOther_abseta_vs_eval->Fill( bdt_method, out_abseta, evweight );
					histBdtOther_phi_vs_eval   ->Fill( bdt_method, out_phi,    evweight );
					if (!pp_flag) histBdtOther_centzone_vs_eval->Fill( bdt_method, out_centzone, evweight );
				}
			}

//===============================================================

			if (Use["BDTD"         ])   histBdtD   ->Fill( reader->EvaluateMVA( "BDTD method"          ) );
			if (Use["BDTG"         ])   histBdtG   ->Fill( reader->EvaluateMVA( "BDTG method"          ) );
			if (Use["RuleFit"      ])   histRf     ->Fill( reader->EvaluateMVA( "RuleFit method"       ) );
			if (Use["SVM_Gauss"    ])   histSVMG   ->Fill( reader->EvaluateMVA( "SVM_Gauss method"     ) );
			if (Use["SVM_Poly"     ])   histSVMP   ->Fill( reader->EvaluateMVA( "SVM_Poly method"      ) );
			if (Use["SVM_Lin"      ])   histSVML   ->Fill( reader->EvaluateMVA( "SVM_Lin method"       ) );
			if (Use["FDA_MT"       ])   histFDAMT  ->Fill( reader->EvaluateMVA( "FDA_MT method"        ) );
			if (Use["FDA_GA"       ])   histFDAGA  ->Fill( reader->EvaluateMVA( "FDA_GA method"        ) );
			if (Use["Category"     ])   histCat    ->Fill( reader->EvaluateMVA( "Category method"      ) );
			if (Use["Plugin"       ])   histPBdt   ->Fill( reader->EvaluateMVA( "P_BDT method"         ) );

			// Retrieve also per-event error
			if (Use["PDEFoam"]) {
				Double_t val = reader->EvaluateMVA( "PDEFoam method" );
				Double_t err = reader->GetMVAError();
				histPDEFoam   ->Fill( val );
				histPDEFoamErr->Fill( err );         
				if (err>1.e-50) histPDEFoamSig->Fill( val/err );
			}         

			// Retrieve probability instead of MVA output
			if (Use["Fisher"])   {
				probHistFi  ->Fill( reader->GetProba ( "Fisher method" ) );
				rarityHistFi->Fill( reader->GetRarity( "Fisher method" ) );
			}
		}
	}

	// Get elapsed time
	sw.Stop();
	std::cout << "\n---- Zero weight events: " << 100.*zeroweight_evts/inputEntries << "%" << std::endl;
	std::cout << "\n---- Total event nº: " << total_evts   << std::endl;
	std::cout << "---- Total signal nº: "  << total_signal << std::endl;
	std::cout << "---- Signal: "           << 100.*total_signal/total_evts << "%" << std::endl;
	std::cout << "\n---- After cut events nº: " << aftercut_evts   << std::endl;
	std::cout << "---- After cut signal nº: "   << aftercut_signal << std::endl;
	std::cout << "---- After cut signal: "      << 100.*aftercut_signal/aftercut_evts << "%" << std::endl;
	std::cout << "\n---- End of event loop: "; sw.Print();

//---------------------------------------------------------------

	// Get efficiency for cuts classifier
	if (Use["CutsGA"]) std::cout << "---- Efficiency for CutsGA method: " << double(nSelCutsGA)/inputEntries << " (for a required signal efficiency of " << effS << ")" << std::endl;

	if (Use["CutsGA"]) {
		// test: retrieve cuts for particular signal efficiency
		// CINT ignores dynamic_casts so we have to use a cuts-specific Reader function to acces the pointer  
		TMVA::MethodCuts* mcuts = reader->FindCutsMVA( "CutsGA method" ) ;

		if (mcuts) {
			std::vector<Double_t> cutsMin;
			std::vector<Double_t> cutsMax;
			mcuts->GetCuts( 0.7, cutsMin, cutsMax );
			std::cout << "---- -------------------------------------------------------------" << std::endl;
			std::cout << "---- Retrieve cut values for signal efficiency of 0.7 from Reader" << std::endl;
			for (UInt_t ivar=0; ivar<cutsMin.size(); ivar++) {
				std::cout << "... Cut: " << cutsMin[ivar]<< " < \"" << mcuts->GetInputVar(ivar) << "\" <= " 
				<< cutsMax[ivar] << std::endl;
			}
			std::cout << "---- -------------------------------------------------------------" << std::endl;
		}
	}

//---------------------------------------------------------------

	// ---- Write histograms

	TString outfileName( "rootfiles/TMVAapplied.root" );
	TFile *outputFile = new TFile( outfileName, "RECREATE" );

	histSig_pt        ->Write();
	histBkg_pt        ->Write();
	histOther_pt      ->Write();
	histSig_eta       ->Write();
	histBkg_eta       ->Write();
	histOther_eta     ->Write();
	histSig_abseta    ->Write();
	histBkg_abseta    ->Write();
	histOther_abseta  ->Write();
	histSig_phi       ->Write();
	histBkg_phi       ->Write();
	histOther_phi     ->Write();
	histSig_centzone  ->Write();
	histBkg_centzone  ->Write();
	histOther_centzone->Write();
	histIP2D          ->Write();
	histIP2DSig       ->Write(); 
	histIP2DBkg       ->Write();
	histIP2DOther     ->Write();
	histIP3D          ->Write();
	histIP3DSig       ->Write(); 
	histIP3DBkg       ->Write();
	histIP3DOther     ->Write();
	histJF            ->Write();
	histJFSig         ->Write(); 
	histJFBkg         ->Write();
	histJFOther       ->Write();
	histIP2D_pt_vs_eval         ->Write();
	histIP2DSig_pt_vs_eval      ->Write();
	histIP2DBkg_pt_vs_eval      ->Write();
	histIP2DOther_pt_vs_eval    ->Write();
	histIP3D_pt_vs_eval         ->Write();
	histIP3DSig_pt_vs_eval      ->Write();
	histIP3DBkg_pt_vs_eval      ->Write();
	histIP3DOther_pt_vs_eval    ->Write();
	histJF_pt_vs_eval           ->Write();
	histJFSig_pt_vs_eval        ->Write();
	histJFBkg_pt_vs_eval        ->Write();
	histJFOther_pt_vs_eval      ->Write();
	histIP2D_abseta_vs_eval     ->Write();
	histIP2DSig_abseta_vs_eval  ->Write();
	histIP2DBkg_abseta_vs_eval  ->Write();
	histIP2DOther_abseta_vs_eval->Write();
	histIP3D_abseta_vs_eval     ->Write();
	histIP3DSig_abseta_vs_eval  ->Write();
	histIP3DBkg_abseta_vs_eval  ->Write();
	histIP3DOther_abseta_vs_eval->Write();
	histJF_abseta_vs_eval       ->Write();
	histJFSig_abseta_vs_eval    ->Write();
	histJFBkg_abseta_vs_eval    ->Write();
	histJFOther_abseta_vs_eval  ->Write();
	histIP2D_phi_vs_eval        ->Write();
	histIP2DSig_phi_vs_eval     ->Write();
	histIP2DBkg_phi_vs_eval     ->Write();
	histIP2DOther_phi_vs_eval   ->Write();
	histIP3D_phi_vs_eval        ->Write();
	histIP3DSig_phi_vs_eval     ->Write();
	histIP3DBkg_phi_vs_eval     ->Write();
	histIP3DOther_phi_vs_eval   ->Write();
	histJF_phi_vs_eval          ->Write();
	histJFSig_phi_vs_eval       ->Write();
	histJFBkg_phi_vs_eval       ->Write();
	histJFOther_phi_vs_eval     ->Write();
	histIP2D_centzone_vs_eval     ->Write();
	histIP2DSig_centzone_vs_eval  ->Write();
	histIP2DBkg_centzone_vs_eval  ->Write();
	histIP2DOther_centzone_vs_eval->Write();
	histIP3D_centzone_vs_eval     ->Write();
	histIP3DSig_centzone_vs_eval  ->Write();
	histIP3DBkg_centzone_vs_eval  ->Write();
	histIP3DOther_centzone_vs_eval->Write();
	histJF_centzone_vs_eval       ->Write();
	histJFSig_centzone_vs_eval    ->Write();
	histJFBkg_centzone_vs_eval    ->Write();
	histJFOther_centzone_vs_eval  ->Write();
	hist_pt_vs_eta           ->Write();                                                                        
	hist_pt_vs_phi           ->Write();
	hist_pt_vs_centzone      ->Write(); 
	hist_phi_vs_eta          ->Write(); 
	hist_phi_vs_centzone     ->Write(); 
	hist_centzone_vs_eta     ->Write(); 
	histSig_pt_vs_eta        ->Write();   
	histSig_pt_vs_phi        ->Write(); 
	histSig_pt_vs_centzone   ->Write();
	histSig_phi_vs_eta       ->Write();
	histSig_phi_vs_centzone  ->Write();
	histSig_centzone_vs_eta  ->Write();
	histBkg_pt_vs_eta        ->Write();
	histBkg_pt_vs_phi        ->Write();
	histBkg_pt_vs_centzone   ->Write();
	histBkg_phi_vs_eta       ->Write();
	histBkg_phi_vs_centzone  ->Write();
	histBkg_centzone_vs_eta  ->Write();
	histOther_pt_vs_eta      ->Write();
	histOther_pt_vs_phi      ->Write();
	histOther_pt_vs_centzone ->Write();
	histOther_phi_vs_eta     ->Write();
	histOther_phi_vs_centzone->Write();
	histOther_centzone_vs_eta->Write();
	hist_chosen_pt                     ->Write();
	hist_chosen_pt_vs_centzone_0_20    ->Write();
	hist_chosen_pt_vs_centzone_20_40   ->Write();
	hist_chosen_pt_vs_centzone_40_80   ->Write();
	hist_notchosen_pt                  ->Write();
	hist_notchosen_pt_vs_centzone_0_20 ->Write();
	hist_notchosen_pt_vs_centzone_20_40->Write();
	hist_notchosen_pt_vs_centzone_40_80->Write();

	if (Use["Likelihood"   ])   histLk     ->Write();
	if (Use["LikelihoodD"  ])   histLkD    ->Write();
	if (Use["LikelihoodPCA"])   histLkPCA  ->Write();
	if (Use["LikelihoodKDE"])   histLkKDE  ->Write();
	if (Use["LikelihoodMIX"])   histLkMIX  ->Write();
	if (Use["PDERS"        ])   histPD     ->Write();
	if (Use["PDERSD"       ])   histPDD    ->Write();
	if (Use["PDERSPCA"     ])   histPDPCA  ->Write();
	if (Use["KNN"          ])   histKNN    ->Write();
	if (Use["HMatrix"      ])   histHm     ->Write();
	if (Use["Fisher"       ])   histFi     ->Write();
	if (Use["FisherG"      ])   histFiG    ->Write();
	if (Use["BoostedFisher"])   histFiB    ->Write();
	if (Use["LD"           ])   histLD     ->Write();
	if (Use["MLP"          ])   histNn     ->Write();
	if (Use["MLPBFGS"      ])   histNnbfgs ->Write();
	if (Use["MLPBNN"       ])   histNnbnn  ->Write();
	if (Use["CFMlpANN"     ])   histNnC    ->Write();
	if (Use["TMlpANN"      ])   histNnT    ->Write();
	if (Use["BDT"          ]) {
		histBdt                      ->Write();
		histBdtSig                   ->Write(); 
		histBdtBkg                   ->Write();
		histBdtOther                 ->Write();
		histBdt_pt_vs_eval           ->Write();
		histBdt_abseta_vs_eval       ->Write();
		histBdt_phi_vs_eval          ->Write();
		histBdtSig_pt_vs_eval        ->Write();
		histBdtSig_abseta_vs_eval    ->Write();
		histBdtSig_phi_vs_eval       ->Write();
		histBdtBkg_pt_vs_eval        ->Write();
		histBdtBkg_abseta_vs_eval    ->Write();
		histBdtBkg_phi_vs_eval       ->Write();
		histBdtOther_pt_vs_eval      ->Write();
		histBdtOther_abseta_vs_eval  ->Write();
		histBdtOther_phi_vs_eval     ->Write();
		histBdt_centzone_vs_eval     ->Write();
		histBdtSig_centzone_vs_eval  ->Write();
		histBdtBkg_centzone_vs_eval  ->Write();
		histBdtOther_centzone_vs_eval->Write();
	}
	if (Use["BDTD"         ])   histBdtD   ->Write();
	if (Use["BDTG"         ])   histBdtG   ->Write(); 
	if (Use["RuleFit"      ])   histRf     ->Write();
	if (Use["SVM_Gauss"    ])   histSVMG   ->Write();
	if (Use["SVM_Poly"     ])   histSVMP   ->Write();
	if (Use["SVM_Lin"      ])   histSVML   ->Write();
	if (Use["FDA_MT"       ])   histFDAMT  ->Write();
	if (Use["FDA_GA"       ])   histFDAGA  ->Write();
	if (Use["Category"     ])   histCat    ->Write();
	if (Use["Plugin"       ])   histPBdt   ->Write();

	// Write also error and significance histos
	if (Use["PDEFoam"]) {
		histPDEFoam->Write();
		histPDEFoamErr->Write();
		histPDEFoamSig->Write();
	}

	// Write also probability hists
	if (Use["Fisher"]) {
		if (probHistFi != 0)   probHistFi->Write();
		if (rarityHistFi != 0) rarityHistFi->Write();
	}

//---------------------------------------------------------------

	outputFile->Close();

	std::cout << "===> Wrote root file: " << outfileName << " containing MVA output histograms" << std::endl;
	std::cout << "===> NewTMVAClassificationApplication is done!\n" << std::endl;

	delete inputTree;
	delete outputFile;
	delete reader;
} 


int main( int argc, char** argv )
{
	// Select methods (don't look at this code - not of interest)
	TString methodList; 
	for (int i=1; i<argc; i++) {
		TString regMethod(argv[i]);
		if(regMethod=="-b" || regMethod=="--batch") continue;
		if (!methodList.IsNull()) methodList += TString(","); 
		methodList += regMethod;
	}
	NewTMVAClassificationApplication(methodList); 
	return 0;
}
