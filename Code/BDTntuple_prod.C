// Rui Pereira 16/17/20-Jul-2018


// calcLLR adapted from BTagging code

float calcLLR(float numerator, float denominator) {
  float val = 0.;
  if(numerator<=0.) {
    val = -30.;
  } else if(denominator<=0.) {
    val = +100.;
  } else {
    val = log(numerator/denominator);
  }
  return val;
}


// main script

int BDTntuple_prod(int flav, char* evfile, char* evchain_name, char* evdir, char* outdir, int ishi) {

  cout << "BDT ntuple production called" << endl;
  cout << "flav = " << flav << endl;
  cout << "evfile = " << evfile << endl;
  cout << "evchain_name = " << evchain_name << endl;
  cout << "evdir = " << evdir << endl;
  cout << "outdir = " << outdir << endl;
  cout << "ishi = " << ishi << endl;

  ///////////////////////////////////
  // EVENT WEIGHT REFERENCE FILE
  ///////////////////////////////////

  TFile* weightfile = new TFile("/home/t3atlas/pereira/work_dir/angerami_weights/Powheg.reweight.root","READ");
  TH3* h3_pT_y_phi_rw = (TH3*) weightfile->Get("h3_pT_y_phi_rw");

  ///////////////////////////////////
  // CENTRALITY ZONE DATA
  ///////////////////////////////////

  float fcal_cent10 = 2.98931;
  float fcal_cent20 = 2.04651;
  float fcal_cent30 = 1.36875;
  float fcal_cent40 = 0.87541;
  float fcal_cent50 = 0.525092;
  float fcal_cent60 = 0.289595;
  float fcal_cent70 = 0.14414;
  float fcal_cent80 = 0.063719;

  ///////////////////////////////////
  // INPUT VARIABLES (by event)
  ///////////////////////////////////

  // centrality info
  float FCalET;

  // basic jet info
  int njets;
  vector<float> *jet_pt = nullptr;
  vector<float> *jet_eta = nullptr;
  vector<float> *jet_phi = nullptr;

  // IP2D info
  vector<float> *jet_ip2d_pb = nullptr;
  vector<float> *jet_ip2d_pc = nullptr;
  vector<float> *jet_ip2d_pu = nullptr;
  vector<float> *jet_ip2d_llr = nullptr;

  // IP3D info
  vector<float> *jet_ip3d_pb = nullptr;
  vector<float> *jet_ip3d_pc = nullptr;
  vector<float> *jet_ip3d_pu = nullptr;
  vector<float> *jet_ip3d_llr = nullptr;

  // SV1 info
  vector<int> *jet_sv1_Nvtx = nullptr;
  vector<int> *jet_sv1_ntrkv = nullptr;
  vector<int> *jet_sv1_n2t = nullptr;
  vector<float> *jet_sv1_m = nullptr;
  vector<float> *jet_sv1_efc = nullptr;
  vector<float> *jet_sv1_sig3d = nullptr;
  vector<float> *jet_sv1_normdist = nullptr;
  vector<float> *jet_sv1_deltaR = nullptr;
  vector<float> *jet_sv1_Lxy = nullptr;
  vector<float> *jet_sv1_L3d = nullptr;
 
  // JetFitter info
  vector<float> *jet_jf_pb = nullptr;
  vector<float> *jet_jf_pc = nullptr;
  vector<float> *jet_jf_pu = nullptr;
  vector<float> *jet_jf_llr = nullptr;
  vector<float> *jet_jf_m = nullptr;
  vector<float> *jet_jf_mUncorr = nullptr;
  vector<float> *jet_jf_efc = nullptr;
  vector<float> *jet_jf_deta = nullptr;
  vector<float> *jet_jf_dphi = nullptr;
  vector<float> *jet_jf_dRFlightDir = nullptr;
  vector<float> *jet_jf_ntrkAtVx = nullptr;
  vector<int> *jet_jf_nvtx = nullptr;
  vector<float> *jet_jf_sig3d = nullptr;
  vector<int> *jet_jf_nvtx1t = nullptr;
  vector<int> *jet_jf_n2t = nullptr;
  vector<int> *jet_jf_VTXsize = nullptr;
  vector<float> *jet_jf_phi = nullptr;
  vector<float> *jet_jf_theta = nullptr;
  vector<float> *jet_jf_theta_err = nullptr;
  vector<float> *jet_jf_phi_err = nullptr;

  // truth jet info
  int ntruthjets;
  vector<float> *truthjet_pt = nullptr;
  vector<float> *truthjet_eta = nullptr;
  vector<float> *truthjet_phi = nullptr;

  // truth flavour info
  vector<int> *jet_truthflav = nullptr;


  /////////////////////////
  // INPUT CHAIN, TREE
  /////////////////////////

  // input directory
  //char* evdir = "/lstore/calo/HI/Estagio_verao_2018/ntuples_ttbar/ttbar";
  //char* evfile = "user.pereira.14588627.Akt4EMTo._000006.root";

  // input chain
  //TChain* evchain = new TChain("bTag_AntiKt4EMTopoJets");
  TChain* evchain = new TChain(evchain_name);
  evchain->Add(Form("%s/%s",evdir,evfile));

  evchain->SetBranchStatus("*",0);

  // centrality info
  evchain->SetBranchStatus("FCalET",1);               evchain->SetBranchAddress("FCalET",&FCalET);

  // basic jet info
  evchain->SetBranchStatus("njets",1);               evchain->SetBranchAddress("njets",&njets);
  evchain->SetBranchStatus("jet_pt",1);              evchain->SetBranchAddress("jet_pt",&jet_pt);
  evchain->SetBranchStatus("jet_eta",1);             evchain->SetBranchAddress("jet_eta",&jet_eta);
  evchain->SetBranchStatus("jet_phi",1);             evchain->SetBranchAddress("jet_phi",&jet_phi);

  // IP2D info
  evchain->SetBranchStatus("jet_ip2d_pb",1);         evchain->SetBranchAddress("jet_ip2d_pb",&jet_ip2d_pb);
  evchain->SetBranchStatus("jet_ip2d_pc",1);         evchain->SetBranchAddress("jet_ip2d_pc",&jet_ip2d_pc);
  evchain->SetBranchStatus("jet_ip2d_pu",1);         evchain->SetBranchAddress("jet_ip2d_pu",&jet_ip2d_pu);
  evchain->SetBranchStatus("jet_ip2d_llr",1);        evchain->SetBranchAddress("jet_ip2d_llr",&jet_ip2d_llr);

  // IP3D info
  evchain->SetBranchStatus("jet_ip3d_pb",1);         evchain->SetBranchAddress("jet_ip3d_pb",&jet_ip3d_pb);
  evchain->SetBranchStatus("jet_ip3d_pc",1);         evchain->SetBranchAddress("jet_ip3d_pc",&jet_ip3d_pc);
  evchain->SetBranchStatus("jet_ip3d_pu",1);         evchain->SetBranchAddress("jet_ip3d_pu",&jet_ip3d_pu);
  evchain->SetBranchStatus("jet_ip3d_llr",1);        evchain->SetBranchAddress("jet_ip3d_llr",&jet_ip3d_llr);

  // SV1 info
  evchain->SetBranchStatus("jet_sv1_Nvtx",1);        evchain->SetBranchAddress("jet_sv1_Nvtx",&jet_sv1_Nvtx);
  evchain->SetBranchStatus("jet_sv1_ntrkv",1);       evchain->SetBranchAddress("jet_sv1_ntrkv",&jet_sv1_ntrkv);
  evchain->SetBranchStatus("jet_sv1_n2t",1);         evchain->SetBranchAddress("jet_sv1_n2t",&jet_sv1_n2t);
  evchain->SetBranchStatus("jet_sv1_m",1);           evchain->SetBranchAddress("jet_sv1_m",&jet_sv1_m);
  evchain->SetBranchStatus("jet_sv1_efc",1);         evchain->SetBranchAddress("jet_sv1_efc",&jet_sv1_efc);
  evchain->SetBranchStatus("jet_sv1_sig3d",1);       evchain->SetBranchAddress("jet_sv1_sig3d",&jet_sv1_sig3d);
  evchain->SetBranchStatus("jet_sv1_normdist",1);    evchain->SetBranchAddress("jet_sv1_normdist",&jet_sv1_normdist);
  evchain->SetBranchStatus("jet_sv1_deltaR",1);      evchain->SetBranchAddress("jet_sv1_deltaR",&jet_sv1_deltaR);
  evchain->SetBranchStatus("jet_sv1_Lxy",1);         evchain->SetBranchAddress("jet_sv1_Lxy",&jet_sv1_Lxy);
  evchain->SetBranchStatus("jet_sv1_L3d",1);         evchain->SetBranchAddress("jet_sv1_L3d",&jet_sv1_L3d);

  // JetFitter info
  evchain->SetBranchStatus("jet_jf_pb",1);           evchain->SetBranchAddress("jet_jf_pb",&jet_jf_pb);
  evchain->SetBranchStatus("jet_jf_pc",1);           evchain->SetBranchAddress("jet_jf_pc",&jet_jf_pc);
  evchain->SetBranchStatus("jet_jf_pu",1);           evchain->SetBranchAddress("jet_jf_pu",&jet_jf_pu);
  evchain->SetBranchStatus("jet_jf_llr",1);          evchain->SetBranchAddress("jet_jf_llr",&jet_jf_llr);
  evchain->SetBranchStatus("jet_jf_m",1);            evchain->SetBranchAddress("jet_jf_m",&jet_jf_m);
  evchain->SetBranchStatus("jet_jf_mUncorr",1);      evchain->SetBranchAddress("jet_jf_mUncorr",&jet_jf_mUncorr);
  evchain->SetBranchStatus("jet_jf_efc",1);          evchain->SetBranchAddress("jet_jf_efc",&jet_jf_efc);
  evchain->SetBranchStatus("jet_jf_deta",1);         evchain->SetBranchAddress("jet_jf_deta",&jet_jf_deta);
  evchain->SetBranchStatus("jet_jf_dphi",1);         evchain->SetBranchAddress("jet_jf_dphi",&jet_jf_dphi);
  evchain->SetBranchStatus("jet_jf_dRFlightDir",1);  evchain->SetBranchAddress("jet_jf_dRFlightDir",&jet_jf_dRFlightDir);
  evchain->SetBranchStatus("jet_jf_ntrkAtVx",1);     evchain->SetBranchAddress("jet_jf_ntrkAtVx",&jet_jf_ntrkAtVx);
  evchain->SetBranchStatus("jet_jf_nvtx",1);         evchain->SetBranchAddress("jet_jf_nvtx",&jet_jf_nvtx);
  evchain->SetBranchStatus("jet_jf_sig3d",1);        evchain->SetBranchAddress("jet_jf_sig3d",&jet_jf_sig3d);
  evchain->SetBranchStatus("jet_jf_nvtx1t",1);       evchain->SetBranchAddress("jet_jf_nvtx1t",&jet_jf_nvtx1t);
  evchain->SetBranchStatus("jet_jf_n2t",1);          evchain->SetBranchAddress("jet_jf_n2t",&jet_jf_n2t);
  evchain->SetBranchStatus("jet_jf_VTXsize",1);      evchain->SetBranchAddress("jet_jf_VTXsize",&jet_jf_VTXsize);
  evchain->SetBranchStatus("jet_jf_phi",1);          evchain->SetBranchAddress("jet_jf_phi",&jet_jf_phi);
  evchain->SetBranchStatus("jet_jf_theta",1);        evchain->SetBranchAddress("jet_jf_theta",&jet_jf_theta);
  evchain->SetBranchStatus("jet_jf_theta_err",1);    evchain->SetBranchAddress("jet_jf_theta_err",&jet_jf_theta_err);
  evchain->SetBranchStatus("jet_jf_phi_err",1);      evchain->SetBranchAddress("jet_jf_phi_err",&jet_jf_phi_err);

  // truth jet info
  evchain->SetBranchStatus("ntruthjets",1);          evchain->SetBranchAddress("ntruthjets",&ntruthjets);
  evchain->SetBranchStatus("truthjet_pt",1);         evchain->SetBranchAddress("truthjet_pt",&truthjet_pt);
  evchain->SetBranchStatus("truthjet_eta",1);        evchain->SetBranchAddress("truthjet_eta",&truthjet_eta);
  evchain->SetBranchStatus("truthjet_phi",1);        evchain->SetBranchAddress("truthjet_phi",&truthjet_phi);

  // truth flavour info
  evchain->SetBranchStatus("jet_truthflav",1);       evchain->SetBranchAddress("jet_truthflav",&jet_truthflav);

  int nev = evchain->GetEntries();

  ////////////////////////////
  // OUTPUT VARIABLES, FILE
  // Variables with (*) are used in the official ATLAS BDT
  ////////////////////////////

  // reweighting info
  int out_JZ;                   // JZ region (1-5 for PbPb, 0 for pp)
  float out_JZweight;           // weight associated to JZ region (set to 0 if pp)
  float out_evweight;           // event reweighting, from leading truth jet's pT-eta-phi

  // centrality info
  float out_FCalET;             // energy deposition in forward calorimeter (set to 0 if pp)
  int out_centzone;             // centrality region inferred from energy dep (1-9 for PbPb, -1 for pp)

  // basic jet info
  float out_pt;                 // (*) jet pT
  float out_eta;                //     jet eta
  float out_abseta;             // (*) jet |eta|
  float out_phi;                //     jet phi

  // IP2D info
  float out_ip2d_pb;            //     IP2D probability density of being b jet
  float out_ip2d_pc;            //     IP2D probability density of being c jet
  float out_ip2d_pu;            //     IP2D probability density of being light flavour jet
  float out_ip2d_llr;           //     IP2D log likelihood ratio (b/light) from official ntuple (main IP2D result, ~same as next)
  float out_ip2d_cllr_pbpu;     // (*) IP2D log likelihood ratio (b/light) from pb/pu
  float out_ip2d_cllr_pbpc;     // (*) IP2D log likelihood ratio (b/c) from pb/pc
  float out_ip2d_cllr_pcpu;     // (*) IP2D log likelihood ratio (c/light) from pc/pu

  // IP3D info
  float out_ip3d_pb;            //     IP3D probability density of being b jet
  float out_ip3d_pc;            //     IP3D probability density of being c jet
  float out_ip3d_pu;            //     IP3D probability density of being light flavour jet
  float out_ip3d_llr;           //     IP3D log likelihood ratio (b/light) from official ntuple (main IP3D result, ~same as next)
  float out_ip3d_cllr_pbpu;     // (*) IP3D log likelihood ratio (b/light) from pb/pu
  float out_ip3d_cllr_pbpc;     // (*) IP3D log likelihood ratio (b/c) from pb/pc
  float out_ip3d_cllr_pcpu;     // (*) IP3D log likelihood ratio (c/light) from pc/pu

  // SV1 info
  int out_sv1_Nvtx;             //     SV1 number of secondary vertices (0=no vertex, 1=there is a vertex)
  int out_sv1_ntrkv;            // (*) SV1 number of tracks associated to vertex (-1 if no vertex)
  int out_sv1_n2t;              // (*) SV1 number of 2-track vertices
  float out_sv1_m;              // (*) SV1 secondary vertex invariant mass
  float out_sv1_efc;            // (*) SV1 secondary vertex energy fraction (SV tracks / all jet tracks)
  float out_sv1_sig3d;          // (*) SV1 significance of distance between secondary and primary vertex (same as next)
  float out_sv1_normdist;       //     SV1 significance of distance between secondary and primary vertex (same as previous)
  float out_sv1_deltaR;         // (*) SV1 deltaR between jet direction and secondary-ptimary vertex line
  float out_sv1_Lxy;            // (*) SV1 2D distance between secondary and primary vertex
  float out_sv1_L3d;            // (*) SV1 3D distance between secondary and primary vertex
 
  // JetFitter info
  float out_jf_pb;              //     JetFitter probability density of being b jet
  float out_jf_pc;              //     JetFitter probability density of being c jet
  float out_jf_pu;              //     JetFitter probability density of being light flavour jet
  float out_jf_llr;             // (x) JetFitter log likelihood ratio (b/light) from official ntuple (main JetFitter result)
  float out_jf_m;               // (*) JetFitter decay chain invariant mass
  float out_jf_mUncorr;         //     JetFitter decay chain invariant mass, uncorrected
  float out_jf_efc;             // (*) JetFitter decay chain energy fracion (DC particles / all jet particles)
  float out_jf_deta;            //     JetFitter deltaEta btw jet and mom sum of all tracks associated with displaced vertices rec by JetFitter
  float out_jf_dphi;            //     JetFitter deltaPhi btw jet and mom sum of all tracks associated with displaced vertices rec by JetFitter
  float out_jf_dRFlightDir;     // (*) JetFitter deltaR between rec b-hadron flight path and jet axis
  float out_jf_ntrkAtVx;        // (*) JetFitter number of tracks at vertex
  int out_jf_nvtx;              // (*) JetFitter number of vertices
  float out_jf_sig3d;           // (*) JetFitter 3D flight length significance
  int out_jf_nvtx1t;            // (*) JetFitter number of single tracks
  int out_jf_n2t;               // (*) JetFitter number of 2-track pairs
  int out_jf_VTXsize;           //     JetFitter size of vertex track list
  float out_jf_phi;             //     JetFitter flight direction of decay chain phi
  float out_jf_theta;           //     JetFitter flight direction of decay chain theta
  float out_jf_theta_err;       //     JetFitter flight direction of decay chain theta error
  float out_jf_phi_err;         //     JetFitter flight direction of decay chain theta error

  // truth flavour info
  int out_truthflav;            // truth flavour of jet (0=light, 4=charm, 5=bottom, 15=tau)

  // output directory
  //char* outdir = "/lstore/calo/HI/pereira/BDTntuples";
  char* outfile;
  if(flav==-1) {
    outfile = Form("%s/BDTdataALL_%s",outdir,evfile);
  }
  else {
    outfile = Form("%s/BDTdata%d_%s",outdir,flav,evfile);
  }

  // output file and tree

  TFile* jetdatafile = new TFile(outfile,"RECREATE");
  TTree* jetdatatree = new TTree("jetdata","Jet data tree");

  // reweighting info
  jetdatatree->Branch("out_JZ",             &out_JZ,             "out_JZ/I");
  jetdatatree->Branch("out_JZweight",       &out_JZweight,       "out_JZweight/F");
  jetdatatree->Branch("out_evweight",       &out_evweight,       "out_evweight/F");

  // centrality info
  jetdatatree->Branch("out_FCalET",         &out_FCalET,         "out_FCalET/F");
  jetdatatree->Branch("out_centzone",       &out_centzone,       "out_centzone/I");

  // basic jet info
  jetdatatree->Branch("out_pt",             &out_pt,             "out_pt/F");
  jetdatatree->Branch("out_eta",            &out_eta,            "out_eta/F");
  jetdatatree->Branch("out_abseta",         &out_abseta,         "out_abseta/F");
  jetdatatree->Branch("out_phi",            &out_phi,            "out_phi/F");
                                          
  // IP2D info
  jetdatatree->Branch("out_ip2d_pb",        &out_ip2d_pb,        "out_ip2d_pb/F");
  jetdatatree->Branch("out_ip2d_pc",        &out_ip2d_pc,        "out_ip2d_pc/F");
  jetdatatree->Branch("out_ip2d_pu",        &out_ip2d_pu,        "out_ip2d_pu/F");
  jetdatatree->Branch("out_ip2d_llr",       &out_ip2d_llr,       "out_ip2d_llr/F");
  jetdatatree->Branch("out_ip2d_cllr_pbpu", &out_ip2d_cllr_pbpu, "out_ip2d_cllr_pbpu/F");
  jetdatatree->Branch("out_ip2d_cllr_pbpc", &out_ip2d_cllr_pbpc, "out_ip2d_cllr_pbpc/F");
  jetdatatree->Branch("out_ip2d_cllr_pcpu", &out_ip2d_cllr_pcpu, "out_ip2d_cllr_pcpu/F");
                                          
  // IP3D info
  jetdatatree->Branch("out_ip3d_pb",        &out_ip3d_pb,        "out_ip3d_pb/F");
  jetdatatree->Branch("out_ip3d_pc",        &out_ip3d_pc,        "out_ip3d_pc/F");
  jetdatatree->Branch("out_ip3d_pu",        &out_ip3d_pu,        "out_ip3d_pu/F");
  jetdatatree->Branch("out_ip3d_llr",       &out_ip3d_llr,       "out_ip3d_llr/F");
  jetdatatree->Branch("out_ip3d_cllr_pbpu", &out_ip3d_cllr_pbpu, "out_ip3d_cllr_pbpu/F");
  jetdatatree->Branch("out_ip3d_cllr_pbpc", &out_ip3d_cllr_pbpc, "out_ip3d_cllr_pbpc/F");
  jetdatatree->Branch("out_ip3d_cllr_pcpu", &out_ip3d_cllr_pcpu, "out_ip3d_cllr_pcpu/F");
                                          
  // SV1 info
  jetdatatree->Branch("out_sv1_Nvtx",       &out_sv1_Nvtx,       "out_sv1_Nvtx/I");
  jetdatatree->Branch("out_sv1_ntrkv",      &out_sv1_ntrkv,      "out_sv1_ntrkv/I");
  jetdatatree->Branch("out_sv1_n2t",        &out_sv1_n2t,        "out_sv1_n2t/I");
  jetdatatree->Branch("out_sv1_m",          &out_sv1_m,          "out_sv1_m/F");
  jetdatatree->Branch("out_sv1_efc",        &out_sv1_efc,        "out_sv1_efc/F");
  jetdatatree->Branch("out_sv1_sig3d",      &out_sv1_sig3d,      "out_sv1_sig3d/F");
  jetdatatree->Branch("out_sv1_normdist",   &out_sv1_normdist,   "out_sv1_normdist/F");
  jetdatatree->Branch("out_sv1_deltaR",     &out_sv1_deltaR,     "out_sv1_deltaR/F");
  jetdatatree->Branch("out_sv1_Lxy",        &out_sv1_Lxy,        "out_sv1_Lxy/F");
  jetdatatree->Branch("out_sv1_L3d",        &out_sv1_L3d,        "out_sv1_L3d/F");
                                          
  // JetFitter info
  jetdatatree->Branch("out_jf_pb",          &out_jf_pb,          "out_jf_pb/F");
  jetdatatree->Branch("out_jf_pc",          &out_jf_pc,          "out_jf_pc/F");
  jetdatatree->Branch("out_jf_pu",          &out_jf_pu,          "out_jf_pu/F");
  jetdatatree->Branch("out_jf_llr",         &out_jf_llr,         "out_jf_llr/F");
  jetdatatree->Branch("out_jf_m",           &out_jf_m,           "out_jf_m/F");
  jetdatatree->Branch("out_jf_mUncorr",     &out_jf_mUncorr,     "out_jf_mUncorr/F");
  jetdatatree->Branch("out_jf_efc",         &out_jf_efc,         "out_jf_efc/F");
  jetdatatree->Branch("out_jf_deta",        &out_jf_deta,        "out_jf_deta/F");
  jetdatatree->Branch("out_jf_dphi",        &out_jf_dphi,        "out_jf_dphi/F");
  jetdatatree->Branch("out_jf_dRFlightDir", &out_jf_dRFlightDir, "out_jf_dRFlightDir/F");
  jetdatatree->Branch("out_jf_ntrkAtVx",    &out_jf_ntrkAtVx,    "out_jf_ntrkAtVx/F");
  jetdatatree->Branch("out_jf_nvtx",        &out_jf_nvtx,        "out_jf_nvtx/I");
  jetdatatree->Branch("out_jf_sig3d",       &out_jf_sig3d,       "out_jf_sig3d/F");
  jetdatatree->Branch("out_jf_nvtx1t",      &out_jf_nvtx1t,      "out_jf_nvtx1t/I");
  jetdatatree->Branch("out_jf_n2t",         &out_jf_n2t,         "out_jf_n2t/I");
  jetdatatree->Branch("out_jf_VTXsize",     &out_jf_VTXsize,     "out_jf_VTXsize/I");
  jetdatatree->Branch("out_jf_phi",         &out_jf_phi,         "out_jf_phi/F");
  jetdatatree->Branch("out_jf_theta",       &out_jf_theta,       "out_jf_theta/F");
  jetdatatree->Branch("out_jf_theta_err",   &out_jf_theta_err,   "out_jf_theta_err/F");
  jetdatatree->Branch("out_jf_phi_err",     &out_jf_phi_err,     "out_jf_phi_err/F");
                                          
  // truth flavour info
  jetdatatree->Branch("out_truthflav",      &out_truthflav,      "out_truthflav/I");

  /////////////////////////
  // PROCESSING CYCLE
  /////////////////////////

  for(int i=0;i<nev;i++) {  // cycle over events

    if(((i+1)%100)==0) cout << ".";
    if(((i+1)%5000)==0 || i+1==nev) cout << " " << i+1 << endl;

    evchain->GetEntry(i);
    //cout << "njets = " << njets << endl;
    //cout << "pt values: ";


    // calculate event weight according to A. Angerami's method

    int simzone = 0;
    float evweight = 0.;
    float JZweight = 0.;

    if(ishi==1) {

      float sjmax_pt = 0.;
      float sjmax_eta = 0.;
      float sjmax_phi = 0.;

      for(int i=0;i<ntruthjets;i++) {
       	float sj_pt = 0.001*(*truthjet_pt)[i];
      	if(sj_pt>sjmax_pt) {
      	  sjmax_pt = sj_pt;
      	  sjmax_eta = (*truthjet_eta)[i];
      	  sjmax_phi = (*truthjet_phi)[i];
      	}
      }

      // find jet weight from A. Angerami's table

      double sum_jet_weights[6]={1,
				 3.428918e+08,
				 4.656080e+06,
				 5.805497e+04,
				 7.924295e+02,
				 1.764195e+01};

      if(sjmax_pt>=20. && sjmax_pt<60.) simzone = 1;
      if(sjmax_pt>=60. && sjmax_pt<160.) simzone = 2;
      if(sjmax_pt>=160. && sjmax_pt<400.) simzone = 3;
      if(sjmax_pt>=400. && sjmax_pt<800.) simzone = 4;
      if(sjmax_pt>=800. && sjmax_pt<1300.) simzone = 5;

      int xb = h3_pT_y_phi_rw->GetXaxis()->FindBin(sjmax_pt);
      int yb = h3_pT_y_phi_rw->GetYaxis()->FindBin(sjmax_eta);
      int zb = h3_pT_y_phi_rw->GetZaxis()->FindBin(sjmax_phi);
      evweight = h3_pT_y_phi_rw->GetBinContent(xb,yb,zb)/sum_jet_weights[simzone];

      // JZ weight

      // Zone  x-sec(nb)  filter eff    evs   |   res                                                                    
      //-------------------------------------------------                                                                
      //  1    1.2794e+8   1.5857e-3  5960780 | 3.403e-2                                                                 
      //  2    1.9648e+7   1.2948e-4  5856854 | 4.344e-4                                                                 
      //  3    5.7613e+5   4.2129e-5  5913566 | 4.104e-6                                                                 
      //  4    4.1522e+4   2.8563e-6  5887243 | 2.015e-8                                                                 
      //  5    8.4338e+2   5.9854e-7  5902078 | 8.553e-11                                                                

      if(simzone==1) JZweight = 1.2794e8*1.5857e-3;
      if(simzone==2) JZweight = 1.9648e7*1.2948e-4;
      if(simzone==3) JZweight = 5.7613e5*4.2129e-5;
      if(simzone==4) JZweight = 4.1522e4*2.8563e-6;
      if(simzone==5) JZweight = 8.4338e2*5.9854e-7;

    }

    // end of event weight calculation

    // calo data collection

    int calo_centzone = -1;

    if(ishi==1) {

      if(FCalET>0.) calo_centzone = 9;
      if(FCalET>fcal_cent80) calo_centzone = 8;
      if(FCalET>fcal_cent70) calo_centzone = 7;
      if(FCalET>fcal_cent60) calo_centzone = 6;
      if(FCalET>fcal_cent50) calo_centzone = 5;
      if(FCalET>fcal_cent40) calo_centzone = 4;
      if(FCalET>fcal_cent30) calo_centzone = 3;
      if(FCalET>fcal_cent20) calo_centzone = 2;
      if(FCalET>fcal_cent10) calo_centzone = 1;

    }

    // end of calo data collection


    for(int j=0;j<njets;j++) {  // cycle over jets

      // FLAVOUR TEST
      if(flav!=-1 && flav!=(*jet_truthflav)[j]) continue;

      // FILL OUTPUT DATA

      // reweighting info
      out_JZ = simzone;
      out_JZweight = JZweight;
      out_evweight = evweight;

      // centrality info
      out_FCalET = FCalET;
      out_centzone = calo_centzone;

      // basic jet info
      out_pt = (*jet_pt)[j];
      out_eta = (*jet_eta)[j];
      out_abseta = abs((*jet_eta)[j]);
      out_phi = (*jet_phi)[j];

      // IP2D info
      out_ip2d_pb = (*jet_ip2d_pb)[j];
      out_ip2d_pc = (*jet_ip2d_pc)[j];
      out_ip2d_pu = (*jet_ip2d_pu)[j];
      out_ip2d_llr = (*jet_ip2d_llr)[j];
      out_ip2d_cllr_pbpu = calcLLR(out_ip2d_pb,out_ip2d_pu);
      out_ip2d_cllr_pbpc = calcLLR(out_ip2d_pb,out_ip2d_pc);
      out_ip2d_cllr_pcpu = calcLLR(out_ip2d_pc,out_ip2d_pu);

      // IP3D info
      out_ip3d_pb = (*jet_ip3d_pb)[j];
      out_ip3d_pc = (*jet_ip3d_pc)[j];
      out_ip3d_pu = (*jet_ip3d_pu)[j];
      out_ip3d_llr = (*jet_ip3d_llr)[j];
      out_ip3d_cllr_pbpu = calcLLR(out_ip3d_pb,out_ip3d_pu);
      out_ip3d_cllr_pbpc = calcLLR(out_ip3d_pb,out_ip3d_pc);
      out_ip3d_cllr_pcpu = calcLLR(out_ip3d_pc,out_ip3d_pu);

      // SV1 info
      out_sv1_Nvtx = (*jet_sv1_Nvtx)[j];
      out_sv1_ntrkv = (*jet_sv1_ntrkv)[j];
      out_sv1_n2t = (*jet_sv1_n2t)[j];
      out_sv1_m = (*jet_sv1_m)[j];
      out_sv1_efc = (*jet_sv1_efc)[j];
      out_sv1_sig3d = (*jet_sv1_sig3d)[j];
      out_sv1_normdist = (*jet_sv1_normdist)[j];
      out_sv1_deltaR = (*jet_sv1_deltaR)[j];
      out_sv1_Lxy = (*jet_sv1_Lxy)[j];
      out_sv1_L3d = (*jet_sv1_L3d)[j];

      if(out_sv1_Nvtx==0) {  // protection against NaN
        out_sv1_deltaR = -1;
        out_sv1_Lxy = -1;
        out_sv1_L3d = -1;
      }

      /*
      cout << "sv1 data: ";
      cout << (*jet_sv1_Nvtx)[j] << " ";
      cout << (*jet_sv1_ntrkv)[j] << " ";
      cout << (*jet_sv1_n2t)[j] << " ";
      cout << (*jet_sv1_m)[j] << " ";
      cout << (*jet_sv1_efc)[j] << " ";
      cout << (*jet_sv1_sig3d)[j] << " ";
      cout << (*jet_sv1_normdist)[j] << " ";
      cout << (*jet_sv1_deltaR)[j] << " ";
      cout << (*jet_sv1_Lxy)[j] << " ";
      cout << (*jet_sv1_L3d)[j] << endl;
      //getchar(); 
      */

      // JetFitter info
      out_jf_pb = (*jet_jf_pb)[j];
      out_jf_pc = (*jet_jf_pc)[j];
      out_jf_pu = (*jet_jf_pu)[j];
      out_jf_llr = (*jet_jf_llr)[j];
      out_jf_m = (*jet_jf_m)[j];
      out_jf_mUncorr = (*jet_jf_mUncorr)[j];
      out_jf_efc = (*jet_jf_efc)[j];
      out_jf_deta = (*jet_jf_deta)[j];
      out_jf_dphi = (*jet_jf_dphi)[j];
      out_jf_dRFlightDir = (*jet_jf_dRFlightDir)[j];
      out_jf_ntrkAtVx = (*jet_jf_ntrkAtVx)[j];
      out_jf_nvtx = (*jet_jf_nvtx)[j];
      out_jf_sig3d = (*jet_jf_sig3d)[j];
      out_jf_nvtx1t = (*jet_jf_nvtx1t)[j];
      out_jf_n2t = (*jet_jf_n2t)[j];
      out_jf_VTXsize = (*jet_jf_VTXsize)[j];
      out_jf_phi = (*jet_jf_phi)[j];
      out_jf_theta = (*jet_jf_theta)[j];
      out_jf_theta_err = (*jet_jf_theta_err)[j];
      out_jf_phi_err = (*jet_jf_phi_err)[j];

      // truth flavour info
      out_truthflav = (*jet_truthflav)[j];

      // fill tree
      jetdatafile->cd();
      jetdatatree->Fill();

      //cout << (*jet_pt)[j] << " ";

    }

    //cout << endl;
    //getchar();

  }

  // write output file
  jetdatafile->Write();

  return 0;

}
