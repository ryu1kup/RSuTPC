{
  TCanvas* c1 = new TCanvas("c1", "c1", 1200, 900);
  TTree* tree1 = (TTree*)(TFile::Open("../output/RSuTPC_G4p10.root"))->Get("events");
  TH1F* hist1 = new TH1F("hist1", "", 1000, 0, 200);
  tree1->Draw("edep >> hist1", "upper && lower");
  hist1->SetTitle("RSuTPC setup;energy deposit in target [keV];a.u.");
  c1->Modified();
  c1->SaveAs("RSuTPC.png");

  TTree* tree2 = (TTree*)(TFile::Open("../output/WuTPC_G4p10.root"))->Get("events");
  TH1F* hist2 = new TH1F("hist2", "", 1000, 0, 200);
  tree2->Draw("edep >> hist2", "upper && lower");
  hist2->SetTitle("WuTPC setup;energy deposit in target [keV];a.u.");
  c1->Modified();
  c1->SaveAs("WuTPC.png");
}
