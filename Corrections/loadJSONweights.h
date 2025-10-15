double AnaScript::LoadAvgGenWeights(TString campaign, TString fullsamplename) {

  string thisdir = std::filesystem::path(__FILE__).parent_path().string();
  string jsonfilename = "genwtdata_" + string(campaign.Data()) + ".json";
  string jsonfilepath = thisdir + "/AvgGenWeights/" + jsonfilename;
  string full = fullsamplename.Data();
  size_t divider = full.find('_');

  // Idiot-proofing:
  ifstream f(jsonfilepath);
  if (!f.is_open()) {
    cout << "\033[33m[Error] LoadAvgGenWeights : Cannot open file "<< jsonfilepath << ". Returning default weight 1.\033[0m" << endl;
    return 1.0;
  }
  json j;
  try { f >> j; }
  catch (json::parse_error &e) {
    cout << "\033[33m[Error] LoadAvgGenWeights : JSON parse error in file "<< jsonfilepath << ": " << e.what() << ". Returning default weight 1.\033[0m" << endl;
    return 1.0;
  }
  if (divider == string::npos) {
    cout << "\033[33m[Error] LoadAvgGenWeights : Sample name "<< full << " does not contain '_'. Returning default weight 1.\033[0m" << endl;
    return 1.0;
  }

  // Searching in JSON:
  string sample = full.substr(0, divider);
  string subsample = full.substr(divider + 1);
  if (j.contains(sample)) {
    json jsub = j[sample];
    if (jsub.contains(subsample)) return jsub[subsample].get<double>();
  }

  // Fallback:
  cout << "\033[33m[Warning] LoadAvgGenWeights : Sample "
       << sample << "+" << subsample << " not found in " << jsonfilepath
       << ". Returning default weight 1.\033[0m" << endl;
  return 1.0;
}

double AnaScript::LoadLumiWeights(TString campaign, TString fullsamplename) {

  string thisdir = std::filesystem::path(__FILE__).parent_path().string();
  string jsonfilename = "lumidata_" + string(campaign.Data()) + ".json";
  string jsonfilepath = thisdir + "/LumiJsons/" + jsonfilename;
  string full = fullsamplename.Data();
  size_t divider = full.find('_');

  // Idiot-proofing:
  ifstream f(jsonfilepath);
  if (!f.is_open()) {
    cout << "\033[33m[Error] LoadLumiWeights : Cannot open file "<< jsonfilepath << ". Returning default weight 1.\033[0m" << endl;
    return 1.0;
  }
  json j;
  try { f >> j; }
  catch (json::parse_error &e) {
    cout << "\033[33m[Error] LoadLumiWeights : JSON parse error in file "<< jsonfilepath << ": " << e.what() << ". Returning default weight 1.\033[0m" << endl;
    return 1.0;
  }
  if (divider == string::npos) {
    cout << "\033[33m[Error] LoadLumiWeights : Sample name "<< full << " does not contain '_'. Returning default weight 1.\033[0m" << endl;
    return 1.0;
  }

  // Searching in JSON:
  string sample    = full.substr(0, divider);
  string subsample = full.substr(divider + 1);
  double mclumi = -1.0; double datalumi = 1.0;
  if (j.contains(sample)) {
    json jsub = j[sample];
    if (jsub.contains(subsample)) mclumi =  jsub[subsample].get<double>();
  }

  if (campaign == "2016preVFP_UL")         datalumi = 19692;
  else if (campaign == "2016postVFP_UL")   datalumi = 16227;
  else if (campaign == "2017_UL")          datalumi = 41480;
  else if (campaign == "2018_UL")          datalumi = 59830;
  else if (campaign == "Run3Summer22")     datalumi = 7980.4;
  else if (campaign == "Run3Summer22EE")   datalumi = 26671.7;
  else if (campaign == "Run3Summer23")     datalumi = 17794.0;
  else if (campaign == "Run3Summer23BPix") datalumi = 9451.0;

  double lumisf = datalumi/mclumi;
  if(lumisf>0) return lumisf; // can't be negative

  // Fallback:
  cout << "\033[33m[Warning] LoadLumiWeights : Sample "
       << sample << "+" << subsample << " not found in " << jsonfilepath
       << ". Returning default weight 1.\033[0m" << endl;
  return 1.0;
}
