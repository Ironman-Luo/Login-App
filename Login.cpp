// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <winuser.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "filemanager.h"
#include <commctrl.h>

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Windows Desktop Login Application");

//Init Database
FileManager file_management = FileManager("database.csv");

//Initialization for all text boxes
_In_ HINSTANCE hInst;
_In_ int nCmd;
HWND textBox1;
HWND textBox2;
HWND textBox3;
HWND textBox4;
HWND loginBox1;
HWND newUserButton;
HWND guide1;
HWND guide2;
HWND guide3;
HWND IDBox;
HWND passwordBox;
HWND passwordBox2;
HWND emailBox;
HWND dateOfBirthBox;
HWND backButton;
HWND userNameBox;
HWND confirmRegistrationButton;
HWND hwndDlg;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
std::string GetTextFromBox(HWND box);
std::string GetTextFromDateBox(HWND box);
int CALLBACK WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR     lpCmdLine,
   _In_ int       nCmdShow
)
{
   //read csv file initially
   file_management.read_csv();
   //register for class
   WNDCLASSEX wcex;

   wcex.cbSize = sizeof(WNDCLASSEX);
   wcex.style          = CS_HREDRAW | CS_VREDRAW;
   wcex.lpfnWndProc    = WndProc;
   wcex.cbClsExtra     = 0;
   wcex.cbWndExtra     = 0;
   wcex.hInstance      = hInstance;
   wcex.hIcon          = LoadIcon(hInstance, IDI_APPLICATION);
   wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
   wcex.lpszMenuName   = NULL;
   wcex.lpszClassName  = szWindowClass;
   wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);


   if (!RegisterClassEx(&wcex))
   {
      MessageBox(NULL,
         _T("Call to RegisterClassEx failed!"),
         _T("Windows Desktop Guided Tour"),
         NULL);

      return 1;
   }

   // Store instance handle in our global variable
   hInst = hInstance;
   nCmd = nCmdShow;
   // The parameters to CreateWindow explained:
   // szWindowClass: the name of the application
   // szTitle: the text that appears in the title bar
   // WS_OVERLAPPEDWINDOW: the type of window to create
   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
   // 500, 100: initial size (width, length)
   // NULL: the parent of this window
   // NULL: this application does not have a menu bar
   // hInstance: the first parameter from WinMain
   // NULL: not used in this application
   HWND hWnd = CreateWindow(
      szWindowClass,
      szTitle,
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      600, 400,
      NULL,
      NULL,
      hInstance,
      NULL
   );
   if (!hWnd)
   {
      MessageBox(NULL,
         _T("Call to CreateWindow failed!"),
         _T("Windows Desktop Guided Tour"),
         NULL);

      return 1;
   }

   // The parameters to ShowWindow explained:
   // hWnd: the value returned from CreateWindow
   // nCmdShow: the fourth parameter from WinMain
   ShowWindow(hWnd,
      nCmdShow);
   ShowWindow(hwndDlg, SW_HIDE);
   UpdateWindow(hWnd);

   // Main message loop:
   MSG msg;
   while (GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }

   return (int) msg.wParam;
}
 
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   PAINTSTRUCT ps;
   HDC hdc;
   TCHAR greeting[] = _T("Hello, Please enter your ID below!");
   TCHAR ID[] = _T("ID: ");
   TCHAR Password[] = _T("Password: ");


   switch (message)
   {
   //Initialization for all windows and buttons. Hide some of the windows in registration page.
   case WM_CREATE: 
   {
       guide1 = CreateWindow(TEXT("STATIC"), TEXT("Hello, Please login to your Account!"), WS_VISIBLE | WS_CHILD,
           130, 80, 300, 20, hWnd, (HMENU)NULL, NULL, NULL);
       guide2 = CreateWindow(TEXT("STATIC"), TEXT("Please register your information below!"), WS_VISIBLE | WS_CHILD,
           130, 80, 300, 20, hWnd, (HMENU)NULL, NULL, NULL);
       IDBox = CreateWindow(TEXT("STATIC"), TEXT("ID: "), WS_VISIBLE | WS_CHILD,
           100, 120, 130, 25, hWnd, (HMENU)NULL, NULL, NULL);
       userNameBox = CreateWindow(TEXT("STATIC"), TEXT("UserName:"), WS_VISIBLE | WS_CHILD,
           100, 120, 130, 25, hWnd, (HMENU)NULL, NULL, NULL);
       passwordBox = CreateWindow(TEXT("STATIC"), TEXT("Password:"), WS_VISIBLE | WS_CHILD,
           100, 145, 130, 25, hWnd, (HMENU)NULL, NULL, NULL);
       passwordBox2 = CreateWindow(TEXT("STATIC"), TEXT("Comfirm Password:"), WS_VISIBLE | WS_CHILD,
           100, 170, 130, 25, hWnd, (HMENU)NULL, NULL, NULL);
       emailBox = CreateWindow(TEXT("STATIC"), TEXT("Email:"), WS_VISIBLE | WS_CHILD,
           100, 195, 130, 25, hWnd, (HMENU)NULL, NULL, NULL);
       guide3 = CreateWindow(TEXT("STATIC"), TEXT("Date of Birth:"), WS_VISIBLE | WS_CHILD,
           100, 220, 130, 25, hWnd, (HMENU)NULL, NULL, NULL);
       textBox1 = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER,
           230, 120, 200, 25, hWnd, (HMENU)NULL, NULL, NULL);
       textBox2 = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER,
           230, 145, 200, 25, hWnd, (HMENU)NULL, NULL, NULL);
       textBox3 = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER,
           230, 170, 200, 25, hWnd, (HMENU)NULL, NULL, NULL);
       textBox4 = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER,
           230, 195, 200, 25, hWnd, (HMENU)NULL, NULL, NULL);
       dateOfBirthBox = CreateWindowEx(WS_EX_ACCEPTFILES, DATETIMEPICK_CLASS, TEXT("DateTime"), WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHOWNONE,
           230, 220, 200, 25, hWnd, NULL, NULL, NULL);
       loginBox1 = CreateWindow(TEXT("BUTTON"), TEXT("Login"), WS_VISIBLE | WS_CHILD,
           230, 180, 80, 20, hWnd, (HMENU)1, NULL, NULL);
       confirmRegistrationButton = CreateWindow(TEXT("BUTTON"), TEXT("Register"), WS_VISIBLE | WS_CHILD,
           230, 250, 80, 20, hWnd, (HMENU)4, NULL, NULL);       
       newUserButton = CreateWindow(TEXT("BUTTON"), TEXT("New User?"), WS_VISIBLE | WS_CHILD,
           500, 300, 80, 20, hWnd, (HMENU)2, NULL, NULL);
       backButton = CreateWindow(TEXT("BUTTON"), TEXT("Back"), WS_VISIBLE | WS_CHILD,
           10, 300, 80, 20, hWnd, (HMENU)3, NULL, NULL);

       ShowWindow(backButton, SW_HIDE);
       ShowWindow(textBox3, SW_HIDE);
       ShowWindow(textBox4, SW_HIDE);
       ShowWindow(dateOfBirthBox, SW_HIDE);
       ShowWindow(emailBox, SW_HIDE);
       ShowWindow(userNameBox, SW_HIDE);
       ShowWindow(passwordBox2, SW_HIDE);
       ShowWindow(guide2, SW_HIDE);
       ShowWindow(guide3, SW_HIDE);
       ShowWindow(confirmRegistrationButton, SW_HIDE);
       break;
   }
   case WM_COMMAND:
   {
       switch (LOWORD(wParam)) {
       //If Login button is clicked
       case 1:{
           std::string login_id = GetTextFromBox(textBox1);
           std::string login_password = GetTextFromBox(textBox2);
           if (file_management.getNumberOfRows() == 0)  MessageBox(hWnd, _T("Login ID not found! Login Failed!"), _T("ERROR"), MB_ICONSTOP);
           //login information is correct
           else if (file_management.check_user(login_id, login_password)) {
               MessageBox(hWnd, _T("Login Successful!"), _T("Logged in"), MB_ICONINFORMATION);
           }
           //login information is not correct
           else { 
                if (file_management.get_password_from_id(login_id) == "") //login ID is wrong
                    MessageBox(hWnd, _T("Login ID not found! Login Failed!"), _T("ERROR"), MB_ICONSTOP);
                else MessageBox(hWnd, _T("Password Wrong! Login Failed!"), _T("ERROR"), MB_ICONSTOP); //password is wrong
           }
           break;
       }
       //switch view to new user's view
       case 2: {
           ShowWindow(loginBox1, SW_HIDE);
           ShowWindow(guide1, SW_HIDE);
           ShowWindow(newUserButton, SW_HIDE);
           ShowWindow(backButton, SW_SHOW);
           ShowWindow(textBox3, SW_SHOW);
           ShowWindow(textBox4, SW_SHOW);
           ShowWindow(dateOfBirthBox, SW_SHOW);
           ShowWindow(emailBox, SW_SHOW);
           ShowWindow(userNameBox, SW_SHOW);
           ShowWindow(passwordBox2, SW_SHOW);
           ShowWindow(hwndDlg, SW_SHOW);
           ShowWindow(guide2, SW_SHOW);
           ShowWindow(guide3, SW_SHOW);
           ShowWindow(confirmRegistrationButton, SW_SHOW);
           SendMessageW(textBox1, WM_SETTEXT, FALSE, NULL);
           SendMessageW(textBox2, WM_SETTEXT, FALSE, NULL);
           break;

       }
       //Back from new user page to login page
       case 3: {
           ShowWindow(backButton, SW_HIDE);
           ShowWindow(newUserButton, SW_SHOW);
           ShowWindow(textBox3, SW_HIDE);
           ShowWindow(textBox4, SW_HIDE);
           ShowWindow(dateOfBirthBox, SW_HIDE);
           ShowWindow(emailBox, SW_HIDE);
           ShowWindow(userNameBox, SW_HIDE);
           ShowWindow(guide1, SW_SHOW);
           ShowWindow(loginBox1, SW_SHOW);
           ShowWindow(passwordBox2, SW_HIDE);
           ShowWindow(guide2, SW_HIDE);
           ShowWindow(guide3, SW_HIDE);
           ShowWindow(confirmRegistrationButton, SW_HIDE);
           SendMessageW(textBox1, WM_SETTEXT, FALSE, NULL);
           SendMessageW(textBox2, WM_SETTEXT, FALSE, NULL);
           SendMessageW(textBox3, WM_SETTEXT, FALSE, NULL);
           SendMessageW(textBox4, WM_SETTEXT, FALSE, NULL);
           break;
       }
       //register for new user
       case 4: {
           std::string new_username = GetTextFromBox(textBox1);
           std::string new_password = GetTextFromBox(textBox2);
           std::string confirm_password = GetTextFromBox(textBox3);
           std::string new_email = GetTextFromBox(textBox4);
           std::string new_DOB = GetTextFromDateBox(dateOfBirthBox);
           if (new_username == "" || new_password == "" || confirm_password == "" || new_email == "") {
               MessageBox(hWnd, _T("Please fill in all blanks!"), _T("Registration Failed"), MB_ICONSTOP);
           }
           else if (new_password.compare(confirm_password) != 0) {
               MessageBox(hWnd, _T("Passwords Not Match!"), _T("Registration Failed"), MB_ICONSTOP);
               SendMessageW(textBox2, WM_SETTEXT, FALSE, NULL);
               SendMessageW(textBox3, WM_SETTEXT, FALSE, NULL);
           }
           else if (new_username.find(" ") != std::string::npos) {
               MessageBox(hWnd, _T("Username Must Not Contain Space!"), _T("Registration Failed"), MB_ICONSTOP);
               SendMessageW(textBox1, WM_SETTEXT, FALSE, NULL);
           }
           else if (new_password.find(" ") != std::string::npos) {
               MessageBox(hWnd, _T("Passwords Must Not Contain Space!"), _T("Registration Failed"), MB_ICONSTOP);
               SendMessageW(textBox2, WM_SETTEXT, FALSE, NULL);
               SendMessageW(textBox3, WM_SETTEXT, FALSE, NULL);
           }
           else {
               //insert into database correspondingly and change to login page
               std::vector<string> new_data = { new_username, new_password, new_email,new_DOB};
               int new_id = file_management.new_user_insert(new_data);
               wstring new_message = _T("You ID is ") + std::to_wstring(new_id) + _T("!, Please save this for future logins!");
               MessageBox(hWnd, new_message.data(), _T("Registration Successful"), MB_ICONINFORMATION);
               ShowWindow(backButton, SW_HIDE);
               ShowWindow(newUserButton, SW_SHOW);
               ShowWindow(textBox3, SW_HIDE);
               ShowWindow(textBox4, SW_HIDE);
               ShowWindow(dateOfBirthBox, SW_HIDE);
               ShowWindow(emailBox, SW_HIDE);
               ShowWindow(userNameBox, SW_HIDE);
               ShowWindow(guide1, SW_SHOW);
               ShowWindow(loginBox1, SW_SHOW);
               ShowWindow(passwordBox2, SW_HIDE);
               ShowWindow(guide2, SW_HIDE);
               ShowWindow(guide3, SW_HIDE);
               ShowWindow(confirmRegistrationButton, SW_HIDE);
               SendMessageW(textBox1, WM_SETTEXT, FALSE, NULL);
               SendMessageW(textBox2, WM_SETTEXT, FALSE, NULL);
               SendMessageW(textBox3, WM_SETTEXT, FALSE, NULL);
               SendMessageW(textBox4, WM_SETTEXT, FALSE, NULL);
           }
           break;
       }
       }
       break;
   }
   case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);

      // Here your application is laid out.
      // For this introduction, we just print out "Hello, Windows desktop!"
      // in the top left corner.
      break;
   case WM_DESTROY:
       file_management.update_csv();
       PostQuitMessage(0);
       break;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
      break;
   }

   return 0;
}
//get text from a edit box
std::string GetTextFromBox(HWND box) {
    std::wstring text;
    int potential_length = GetWindowTextLengthW(box) + 1;
    text.resize(potential_length);
    int final_length = GetWindowText(box, &text[0], potential_length);
    text.resize(final_length);
    std::string result = std::string(text.begin(), text.end());
    return result;
}

//get date information from a date box
std::string GetTextFromDateBox(HWND box)
{
    SYSTEMTIME st{};
    DateTime_GetSystemtime(box, &st);
    TCHAR buf[100]{};
    wsprintf(buf, L"%d-%d-%d", st.wYear, st.wMonth, st.wDay);
    wstring result(&buf[0]);
    return std::string(result.begin(),result.end());
}