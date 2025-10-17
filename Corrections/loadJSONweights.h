double AnaScript::LoadAvgGenWeights(TString campaign, TString fullsamplename) {

  string thisdir = filesystem::canonical(filesystem::path(__FILE__)).parent_path().string();
  string jsonfilename = "genwtdata_" + string(campaign.Data()) + ".json";
  string jsonfilepath = (filesystem::path(thisdir) / "AvgGenWeights" / jsonfilename).string();
  string full = fullsamplename.Data();
  size_t divider = full.find('_');

  double wt = 1.0;

  // Idiot-proofing:
  ifstream f(jsonfilepath);
  if (!f.is_open()) cout<<"\033[31m[Error] LoadAvgGenWeights : Cannot open file "<<jsonfilepath<<"\033[0m"<<endl;
  json j; try { f >> j; } catch (const json::parse_error &e) { cout<<"\033[31m[Error] LoadAvgGenWeights : JSON parse error in "<<jsonfilepath<<"\033[0m"<<endl; }
  if (divider == string::npos)  cout<<"\033[31m[Error] LoadAvgGenWeights : Sample name "<<full<< " does not contain '_'.\033[0m"<<endl;

  // Searching in JSON:
  string sample = full.substr(0, divider);
  string subsample = full.substr(divider + 1);
  if (j.contains(sample)) {
    json jsub = j[sample];
    if (jsub.contains(subsample)) wt = jsub[subsample].get<double>();
    else cout << "\033[31m[Warning] LoadAvgGenWeights : "<<sample<<" + "<<subsample<<" not found."<< jsonfilepath<<"\033[0m"<<endl;
  }
  
  return wt;
}

double AnaScript::LoadLumiWeights(TString campaign, TString fullsamplename) {

  string thisdir = filesystem::canonical(filesystem::path(__FILE__)).parent_path().string();
  string jsonfilename = "lumidata_" + string(campaign.Data()) + ".json";
  string jsonfilepath = (filesystem::path(thisdir) / "LumiJsons" / jsonfilename).string();
  string full = fullsamplename.Data();
  size_t divider = full.find('_');

  // Idiot-proofing:
  ifstream f(jsonfilepath);
  if (!f.is_open()) cout<<"\033[31m[Error] LoadLumiWeights : Cannot open file "<<jsonfilepath<<"\033[0m"<<endl;
  json j; try { f >> j; } catch (const json::parse_error &e) { cout<<"\033[31m[Error] LoadLumiWeights : JSON parse error in "<<jsonfilepath<<"\033[0m"<<endl; }
  if (divider == string::npos)  cout<<"\033[31m[Error] LoadLumiWeights : Sample name "<<full<< " does not contain '_'.\033[0m"<<endl;

  // Searching in JSON:
  string sample    = full.substr(0, divider);
  string subsample = full.substr(divider + 1);
  double mclumi = -1.0; double datalumi = 1.0;
  if (j.contains(sample)) {
    json jsub = j[sample];
    if (jsub.contains(subsample)) mclumi =  jsub[subsample].get<double>();
    else cout << "\033[31m[Warning] LoadLumiWeights : "<<sample<<" + "<<subsample<<" not found."<< jsonfilepath<<"\033[0m"<<endl;
  }

  if      (campaign == "2016preVFP_UL")    datalumi = 19692.0;
  else if (campaign == "2016postVFP_UL")   datalumi = 16227.0;
  else if (campaign == "2017_UL")          datalumi = 41480.0;
  else if (campaign == "2018_UL")          datalumi = 59830.0;
  else if (campaign == "Run3Summer22")     datalumi =  7980.4;
  else if (campaign == "Run3Summer22EE")   datalumi = 26671.7;
  else if (campaign == "Run3Summer23")     datalumi = 17794.0;
  else if (campaign == "Run3Summer23BPix") datalumi =  9451.0;
    
  double lumisf = datalumi/mclumi;
  if(lumisf>0) return lumisf; // can't be negative
  return 1.0;
}
