// Virtual Assisntant GUI in C++

#include <Windows.h>
#include <stdlib.h>
#include <Python.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define SUBMIT_BUTTON 4

// Globals
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);
void WebCrawler();

HMENU hMenu;
HWND hJobTitle, hLocation, hOut;

// Main function
int main(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	WNDCLASS wc = { 0 };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	// Window parameters
	CreateWindowW(L"myWindowClass", L"Virtual Assistant", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	// Listening loop for the window
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

// Initialize window functionality
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND:
		// Header menus
		switch (wp) {
		case FILE_MENU_NEW:
			MessageBeep(MB_ICONINFORMATION);
			break;
		case FILE_MENU_EXIT:
			DestroyWindow(hWnd);
			break;
		case SUBMIT_BUTTON:
			wchar_t jobTitle[100], location[100], out[500];

			GetWindowText(hJobTitle, jobTitle, 100);
			GetWindowText(hLocation, location, 100);
			GetWindowText(hOut, out, 500);

			// Text box output
			wcscat_s(out, L"Searching for ");
			wcscat_s(out, jobTitle);
			wcscat_s(out, L" positions in ");
			wcscat_s(out, location);
			wcscat_s(out, L".");

			SetWindowText(hOut, out);

			// Check user input for webcrawler request
			if (wcscmp(jobTitle, L"run webcrawler") == 0) {
				WebCrawler();
			}
			break;
		}
		break;
	case WM_CREATE:
		AddMenus(hWnd);
		AddControls(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

// Function to add header meanus to a window
void AddMenus(HWND hWnd) {
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();

	// "File" header menu
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"New");
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Open");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");

	// "File" -> "Open" submenu
	AppendMenu(hSubMenu, MF_STRING, NULL, L"Submenu Item");

	// "Help" header menu
	AppendMenu(hMenu, MF_STRING, 2, L"Help");

	SetMenu(hWnd, hMenu);
}

// Function to add controls to a window
void AddControls(HWND hWnd) {
	// Job Title
	CreateWindowW(L"Static", L"Job Title: ", WS_VISIBLE | WS_CHILD, 100, 50, 98, 38, hWnd, NULL, NULL, NULL);
	hJobTitle = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 50, 98, 38, hWnd, NULL, NULL, NULL);

	// Location
	CreateWindowW(L"Static", L"Location: ", WS_VISIBLE | WS_CHILD, 100, 90, 98, 38, hWnd, NULL, NULL, NULL);
	hLocation = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 90, 98, 38, hWnd, NULL, NULL, NULL);

	// Submit button
	CreateWindowW(L"Button", L"Submit", WS_VISIBLE | WS_CHILD, 150, 130, 98, 38, hWnd, (HMENU)SUBMIT_BUTTON, NULL, NULL);

	// Text box output
	hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 200, 300, 200, hWnd, NULL, NULL, NULL);
}

// Function to execute webcrawler Python script
void WebCrawler() {
	// Create a function to write variable data to a file for the Python script to read

	FILE* fp;

	// Change local path variables for Python execution
	const char* fModulePath = "C:\\Users\\Chris\\source\\repos\\Python\\webCrawler\\";
	const char* fLibPath = "C:\\Users\\Chris\\source\\repos\\Python\\webCrawler\\venv\\Lib\\site-packages\\";
	const char* fMainPath = "C:\\Users\\Chris\\source\\repos\\Python\\webCrawler\\main.py";

	// Initialize the python instance
	Py_Initialize();

	// Set paths for Python modules and libraries
	PyObject* sysPath = PySys_GetObject((char*)"path");
	PyList_Append(sysPath, PyUnicode_FromString(fModulePath));
	PyList_Append(sysPath, PyUnicode_FromString(fLibPath));

	// Open and run main Python script
	fp = _Py_fopen(fMainPath, "r");

	PyRun_SimpleFile(fp, fMainPath);

	// Close the python instance
	Py_Finalize();
}