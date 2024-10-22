#ifndef ATM_GUI_H
#define ATM_GUI_H

#include <wx/wx.h>
#include "ATMBackend.h"

// Define the main application class
class ATMApp : public wxApp {
public:
    virtual bool OnInit();
};

// Define the main frame for the application
class ATMFrame : public wxFrame {
public:
    ATMFrame(const wxString& title);

private:
    void OnLogin(wxCommandEvent& event);
    void OnEnroll(wxCommandEvent& event);
    void OnWithdraw(wxCommandEvent& event);
    void OnDeposit(wxCommandEvent& event);
    void OnChangePIN(wxCommandEvent& event);
    void OnTransactionStatement(wxCommandEvent& event);

    void UpdateAccountDisplay();

    wxTextCtrl* usernameInput;
    wxTextCtrl* acctNumInput;
    wxTextCtrl* pinInput;
    wxTextCtrl* amountInput;
    wxTextCtrl* transactionHistoryDisplay;

    ATMAccount* currentAccount;
    std::vector<ATMAccount> accounts;

    wxDECLARE_EVENT_TABLE();
};

#endif // ATM_GUI_H
#pragma once
