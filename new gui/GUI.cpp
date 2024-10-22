#include "ATM_GUI.h"
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/msgdlg.h>

// Main application initialization
IMPLEMENT_APP(ATMApp)

bool ATMApp::OnInit() {
    ATMFrame* frame = new ATMFrame("ATM System");
    frame->Show(true);
    return true;
}

// Frame constructor
ATMFrame::ATMFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title), currentAccount(nullptr) {
    // Create GUI components
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Username:"), 0, wxALL, 5);
    usernameInput = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(usernameInput, 0, wxEXPAND | wxALL, 5);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Account Number:"), 0, wxALL, 5);
    acctNumInput = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(acctNumInput, 0, wxEXPAND | wxALL, 5);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "PIN:"), 0, wxALL, 5);
    pinInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    sizer->Add(pinInput, 0, wxEXPAND | wxALL, 5);

    wxButton* loginButton = new wxButton(panel, wxID_ANY, "Login");
    sizer->Add(loginButton, 0, wxALL, 5);
    loginButton->Bind(wxEVT_BUTTON, &ATMFrame::OnLogin, this);

    wxButton* enrollButton = new wxButton(panel, wxID_ANY, "Enroll");
    sizer->Add(enrollButton, 0, wxALL, 5);
    enrollButton->Bind(wxEVT_BUTTON, &ATMFrame::OnEnroll, this);

    wxButton* withdrawButton = new wxButton(panel, wxID_ANY, "Withdraw");
    sizer->Add(withdrawButton, 0, wxALL, 5);
    withdrawButton->Bind(wxEVT_BUTTON, &ATMFrame::OnWithdraw, this);

    wxButton* depositButton = new wxButton(panel, wxID_ANY, "Deposit");
    sizer->Add(depositButton, 0, wxALL, 5);
    depositButton->Bind(wxEVT_BUTTON, &ATMFrame::OnDeposit, this);

    wxButton* changePINButton = new wxButton(panel, wxID_ANY, "Change PIN");
    sizer->Add(changePINButton, 0, wxALL, 5);
    changePINButton->Bind(wxEVT_BUTTON, &ATMFrame::OnChangePIN, this);

    wxButton* transactionButton = new wxButton(panel, wxID_ANY, "Transaction Statement");
    sizer->Add(transactionButton, 0, wxALL, 5);
    transactionButton->Bind(wxEVT_BUTTON, &ATMFrame::OnTransactionStatement, this);

    transactionHistoryDisplay = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
    sizer->Add(transactionHistoryDisplay, 1, wxEXPAND | wxALL, 5);

    panel->SetSizer(sizer);
    LoadAccounts(); // Load existing accounts
}

// Load accounts from the file
void ATMFrame::LoadAccounts() {
    std::ifstream inFile("atmAccounts.txt");
    if (!inFile.is_open()) return;

    ATMAccount account;
    while (std::getline(inFile, account.acctNum) &&
        std::getline(inFile, account.acctName) &&
        std::getline(inFile, account.midName) &&
        std::getline(inFile, account.surname) &&
        std::getline(inFile, account.suffix) &&
        std::getline(inFile, account.username) &&
        std::getline(inFile, account.bday) &&
        std::getline(inFile, account.contactNum) &&
        std::getline(inFile, account.emerContactNum) &&
        inFile >> account.balance &&
        inFile.ignore() &&
        std::getline(inFile, account.pinCode) &&
        std::getline(inFile, account.acctType)) {
        accounts.push_back(account);
    }
    inFile.close();
}

// Update account display after an action
void ATMFrame::UpdateAccountDisplay() {
    if (currentAccount) {
        transactionHistoryDisplay->Clear();
        for (const auto& transaction : currentAccount->transacHistory) {
            transactionHistoryDisplay->AppendText(transaction + "\n");
        }
    }
}

// Handle login button
void ATMFrame::OnLogin(wxCommandEvent& event) {
    std::string username = usernameInput->GetValue().ToStdString();
    std::string acctNum = acctNumInput->GetValue().ToStdString();
    std::string pin = pinInput->GetValue().ToStdString();

    currentAccount = login(accounts, username, acctNum, pin);
    if (currentAccount) {
        wxMessageBox("Login successful!", "Success", wxOK | wxICON_INFORMATION);
        UpdateAccountDisplay();
    }
    else {
        wxMessageBox("Login failed. Check your credentials.", "Error", wxOK | wxICON_ERROR);
    }
}

// Handle enroll button
void ATMFrame::OnEnroll(wxCommandEvent& event) {
    // Implement enrollment logic
}

// Handle withdraw button
void ATMFrame::OnWithdraw(wxCommandEvent& event) {
    // Implement withdraw logic
}

// Handle deposit button
void ATMFrame::OnDeposit(wxCommandEvent& event) {
    // Implement deposit logic
}

// Handle change PIN button
void ATMFrame::OnChangePIN(wxCommandEvent& event) {
    // Implement change PIN logic
}

// Handle transaction statement button
void ATMFrame::OnTransactionStatement(wxCommandEvent& event) {
    // Implement transaction statement logic
}

wxBEGIN_EVENT_TABLE(ATMFrame, wxFrame)
// Add event table entries here
wxEND_EVENT_TABLE()
