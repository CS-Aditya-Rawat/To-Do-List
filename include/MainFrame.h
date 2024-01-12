#pragma once
#include <wx/wx.h>

class MainFrame:public wxFrame{
public:
  MainFrame(const wxString& title);
private:
  void CreateControls();
  void BindEventHandlers();
  void RestoreSavedTasks();

  void OnAddButtonClick(wxCommandEvent& evt);
  void OnClearButtonClick(wxCommandEvent& evt);
  void OnListKeyDown(wxKeyEvent& evt);
  void OnWindowClose(wxCloseEvent& evt);
  
  //TODO: Add Combo of CTRL+Enter to add new Task
  void OnAddButtonPress(wxCommandEvent& evt);   

  void AddTaskFromInput();
  void DeleteSelectedTask();
  void MoveSelectedTask(int offset);
  void SwapTasks(int i, int j);

  wxPanel* panel;
  wxStaticText* headerText;
  wxTextCtrl* inputField;
  wxButton* addButton;
  wxCheckListBox* checkListBox;
  wxButton* clearButton;
};
