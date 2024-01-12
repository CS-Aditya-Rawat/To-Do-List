#include "MainFrame.h"
#include <wx/wx.h>
#include <string>
#include <vector>
#include "Task.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
  CreateControls();
  BindEventHandlers();
  RestoreSavedTasks();
}

void MainFrame::CreateControls() {
  wxFont headerFont(wxFontInfo(wxSize(0, 36)).Bold());
  wxFont mainFont(wxFontInfo(wxSize(0, 24)));

  panel = new wxPanel(this);
  panel->SetFont(mainFont);

  headerText = new wxStaticText(panel, wxID_ANY, "To-Do Lists", wxPoint(0, 22),
                                wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
  headerText->SetFont(headerFont);

  inputField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 80), wxSize(495, 35), 
                              wxTE_PROCESS_ENTER);
  addButton = new wxButton(panel,  wxID_ANY, "Add", wxPoint(600, 80), wxSize(100, 35));
  checkListBox = new wxCheckListBox(panel, wxID_ANY, wxPoint(100, 120), wxSize(600, 400));
  clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(100, 525), wxSize(100, 35));
}

void MainFrame::BindEventHandlers()
{
  addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClick, this);
  inputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnAddButtonPress, this);
  checkListBox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this);
  clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClick, this);
  this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClose, this);
}

void MainFrame::OnListKeyDown(wxKeyEvent& evt)
{
  switch(evt.GetKeyCode()){
    case WXK_DELETE:
      DeleteSelectedTask();
      break;
    case WXK_UP:
      MoveSelectedTask(-1);
      break;
    case WXK_DOWN:
      MoveSelectedTask(1);
      break;
  }
}

void MainFrame::OnAddButtonClick(wxCommandEvent& evt)
{
  AddTaskFromInput();
}

void MainFrame::OnAddButtonPress(wxCommandEvent& evt)
{
  AddTaskFromInput();
}

void MainFrame::AddTaskFromInput()
{
  wxString description = inputField->GetValue();
  if (!description.IsEmpty()){
    checkListBox->Insert(description, checkListBox->GetCount());
    inputField->Clear();
  }
  inputField->SetFocus();
}

void MainFrame::DeleteSelectedTask()
{
  int selectedIndex = checkListBox->GetSelection();
  if (selectedIndex == wxNOT_FOUND){
    return;
  }
  checkListBox->Delete(selectedIndex);
}

void MainFrame::MoveSelectedTask(int offset)
{
  int selectedIndex = checkListBox->GetSelection();
  if (selectedIndex == wxNOT_FOUND){
    return;
  }
  int newIndex = selectedIndex + offset;

  if (newIndex >= 0 && newIndex < checkListBox->GetCount()){
    SwapTasks(selectedIndex, newIndex);
    checkListBox->SetSelection(newIndex, true);
  }
}

void MainFrame::SwapTasks(int i, int j)
{
  Task taskI{checkListBox->GetString(i).ToStdString(), checkListBox->IsChecked(i)};
  Task taskJ{checkListBox->GetString(j).ToStdString(), checkListBox->IsChecked(j)};
  
  checkListBox->SetString(i, taskJ.description);
  checkListBox->Check(i, taskJ.done);
  
  checkListBox->SetString(j, taskI.description);
  checkListBox->Check(j, taskI.done);
}

void MainFrame::OnClearButtonClick(wxCommandEvent& evt)
{
  if (checkListBox->IsEmpty()){
    return;
  }
  wxMessageDialog dialog(this, "Are you sure you want to clear all tasks ?", "Clear", 
                         wxYES_NO | wxCANCEL);
  int result = dialog.ShowModal();

  if (result == wxID_YES){
    checkListBox->Clear();
  }
}

void MainFrame::OnWindowClose(wxCloseEvent& evt)
{
  std::vector<Task> tasks;
  for(int i=0; i<checkListBox->GetCount(); i++){
    Task task;
    task.description = checkListBox->GetString(i);
    task.done = checkListBox->IsChecked(i);
    tasks.push_back(task);
  } 
  saveTasksToFile(tasks, "tasks.txt");
  evt.Skip();
}

void MainFrame::RestoreSavedTasks()
{
  std::vector<Task> tasks = loadTasksFromFile("tasks.txt");
  for (const Task& task: tasks){
    int index = checkListBox->GetCount();
    checkListBox->Insert(task.description, index);
    checkListBox->Check(index, task.done);
  }
}
