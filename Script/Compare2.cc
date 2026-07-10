void Compare2()
{

    int energy[41] = {10  ,12  ,16  ,20  ,25  ,32  ,49  ,50  ,63  ,80  
                    ,100 ,120 ,160 ,200 ,250 ,320 ,490 ,500 ,630 ,800 
                    ,1000,1200,1600,2000,2500,3200,4900,5000,6300,8000 
                    ,10000,12000,16000,20000,25000,32000,49000,50000,63000,80000 
                    ,100000};
    double Energy[41] ={0};
    double Ratio[41] = {0};
    double Ratio_Meson[41] = {0};
    double Ratio_PiKaon[41] = {0};
    double Ratio_Paul[41] = {0};
    double Ratio_G4[41]  = {0};
    double Ratio_G4NEW[41]  = {0};


    double Paul[41] = { 0.1047   , 0.097465 , 0.0903725, 0.0842575, 0.07878  , 0.07443  ,
                   0.07056  , 0.0670775, 0.064135 , 0.06161  , 0.0595825, 0.05796  ,
                   0.056615 , 0.055525 , 0.0546475, 0.0538575, 0.05335  , 0.0529325,
                   0.052575 , 0.0523   , 0.052085 , 0.052015 , 0.0519725, 0.0520275,
                   0.05197  , 0.0520675, 0.0523225, 0.052495 , 0.0525175, 0.052765 ,
                   0.052995 , 0.052995 , 0.052995, 0.052995, 0.052995, 0.052995, 
                   0.052995 , 0.052995 , 0.052995, 0.052995, 0.052995};

    for (int ii = 0; ii <41 ; ii++)
    {
        auto file = TFile::Open(Form("/Users/xiongzheng/software/Hadr03/Root2/Proton_BGO_%dGeV.root",energy[ii]));
        auto h1   = (TH1D*)file->Get("1");
        auto h2   = (TH1D*)file->Get("2");
        auto h3   = (TH1D*)file->Get("3");
        auto h4   = (TH1D*)file->Get("4");
        auto h5   = (TH1D*)file->Get("5");
        auto h6   = (TH1D*)file->Get("6");
        auto h7   = (TH1D*)file->Get("7");
        auto h8   = (TH1D*)file->Get("8");
        
        auto c1 = new TCanvas("c1","c1",1200,900);
        c1->cd();
        gPad->SetGrid(1,1);
        gStyle->SetOptStat(0);
        h2->SetLineColor(kBlue);h2->SetLineWidth(2);
        h3->SetLineColor(kRed);h3->SetLineWidth(2);
        h4->SetLineColor(kOrange-3);h4->SetLineWidth(2);
        h5->SetLineColor(kMagenta);h5->SetLineWidth(2);
        h6->SetLineColor(kMagenta);h6->SetLineWidth(2);
        h7->SetLineColor(kCyan);h7->SetLineWidth(2);
        h8->SetLineColor(kGreen);h8->SetLineWidth(2);
        gPad->SetLogy(1); 
        // h2->GetXaxis()->SetLimits(    );
        h2->Draw("hist");
        h3->Draw("histsame");
        h4->Draw("histsame");
        h6->Draw("histsame");
        h7->Draw("histsame");
        // h5->Draw("histsame");
        // cout << "h4 " << h4->Integral() << endl;
        // cout << "h3 " << h4->Integral() << endl;
        cout << " h4 / h2 = "<<  1- h4->Integral() / h2->Integral() << endl;
        
        Energy[ii] = pow(10,0.1*ii+1);

        cout << Energy[ii] << endl;
        Ratio[ii]        = 1 - h4->Integral() / h2->Integral();
        Ratio_Meson[ii]  = 1 - h6->Integral() / h2->Integral();
        Ratio_PiKaon[ii] = 1 - h7->Integral() / h2->Integral();
        Ratio_Paul[ii]  = 1 - Paul[ii];
        Ratio_G4NEW[ii] = Ratio[ii]       / Ratio_Meson[ii];
        Ratio_G4[ii]    = Ratio_Meson[ii] / Ratio_Paul[ii];

        auto lg1 = new TLegend(0.38,0.68,0.78,0.88);
        lg1->AddEntry(h2,"most energetic secondary","l");
        lg1->AddEntry(h3,"most energetic secondary && ==primary","l");
        lg1->AddEntry(h4,"most energetic secondary && ==primary && QE","l");
        lg1->AddEntry(h6,"most energetic secondary && ==primary && No meson","l");
        lg1->AddEntry(h7,"most energetic secondary && ==primary && No pion kaon","l");
        lg1->Draw();
        c1->SaveAs(Form("/Users/xiongzheng/software/Hadr03/Script/Proton2_BGO_%dGeV.pdf",energy[ii]));
    } 

    auto c2 = new TCanvas("c2","c2",2700,900);
    auto gr1 = new TGraph(41,Energy,Ratio);
    auto gr2 = new TGraph(41,Energy,Ratio_Meson);
    auto gr3 = new TGraph(41,Energy,Ratio_PiKaon);
    auto gr4 = new TGraph(41,Energy,Ratio_Paul);
    auto gr5 = new TGraph(41,Energy,Ratio_G4);
    auto gr6 = new TGraph(41,Energy,Ratio_G4NEW);


    c2->Divide(3,1);
    c2->cd(1);
    gPad->SetLogx(1);
    gPad->SetGrid(1,1);
    gr1->GetYaxis()->SetRangeUser(0.89,0.95);
    gr1->GetXaxis()->SetLimits(9e0,2e5);
    gr1->SetMarkerStyle(20);

    gr2->SetLineColor(kMagenta);
    gr2->SetMarkerColor(kMagenta);
    gr2->SetMarkerStyle(21);

    gr3->SetLineStyle(9);
    gr3->SetLineColor(kRed);
    gr3->SetMarkerColor(kRed);
    gr3->SetMarkerStyle(22);

    gr4->SetLineColor(kBlue);
    gr4->SetMarkerColor(kBlue);
    gr4->SetMarkerStyle(23);

    gr5->SetMarkerStyle(20);    
    gr6->SetMarkerStyle(20);

    gr1->SetTitle("; Energy (GeV) ;Correction Factor ");
    gr1->Draw("ALP");
    gr2->Draw("PLSAME");
    gr3->Draw("PLSAME");
    gr4->Draw("PLSAME");
    
    gr1->SetName("QE_Truth_G4_11");
    gr2->SetName("Meson_G4_11");
    gr3->SetName("PiKaon_G4_11");
    gr4->SetName("PiKaon_G4_10");

    auto lg1 = new TLegend(0.58,0.12,0.88,0.38);
    lg1->AddEntry(gr1,"QE truth Geant4.11","lp");
    lg1->AddEntry(gr2,"Meson  Geant4.11","lp"); 
    lg1->AddEntry(gr3,"PiKaon Geant4.11 ","lp"); 
    lg1->AddEntry(gr4,"PiKaon Geant4.10","lp"); 
    lg1->Draw();
    
    c2->cd(2);
    gPad->SetLogx(1);
    gPad->SetGrid(1,1);
    gr5->SetTitle("Correction Factor: PiKaon Geant4.11/Geant4.10;Energy (GeV);Ratio");
    gr5->Draw("ALP");
    gr5->SetName("Ratio_G4_11_10");

    c2->cd(3);
    gPad->SetLogx(1);
    gPad->SetGrid(1,1);
    gr6->SetTitle("Correction Factor: QE Geant4.11/Meson Geant4.11;Energy (GeV);Ratio");
    gr6->Draw("ALP");
    gr6->SetName("Ratio_QE_Meson_G4_11");

    c2->SaveAs("/Users/xiongzheng/software/Hadr03/Script/Proton2_Correction.pdf");

    auto file = TFile::Open("/Users/xiongzheng/software/Hadr03/Script/Proton2_Correction.root","RECREATE");
    gr1->Write();
    gr2->Write();
    gr3->Write();
    gr4->Write();
    gr5->Write();
    gr6->Write();


    c2->Write();
    file->cd();

}