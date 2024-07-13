#include <windows.h>
#include <stdio.h>

HINSTANCE hInst;
HFONT hFont;

LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	static HWND h_btn;
	static HWND hwnd_distance;
    static HWND hwnd_consumption;
    static HWND hwnd_price;
    static HWND hwnd_result;
	
	switch(Message) {
		case WM_CREATE: {
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG) CreateSolidBrush(RGB(68, 0, 102)));

            hwnd_distance = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 50, 100, 20, hWnd, NULL, NULL, NULL);             
            hwnd_consumption = CreateWindow("EDIT", "",  WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 80, 100, 20, hWnd, NULL, NULL, NULL);         
            hwnd_price = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 110, 100, 20, hWnd, NULL, NULL, NULL);
            CreateWindow("BUTTON", "Calculate", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 200, 145, 100, 40, hWnd, (HMENU)1, NULL, NULL);
            hwnd_result = CreateWindow("STATIC", "", WS_VISIBLE | WS_CHILD, 200, 200, 100, 20, hWnd, NULL, NULL, NULL);
			
			break;
		}
		
		case WM_COMMAND: {
			if (LOWORD(wParam) == 1) {
				char size_distance[10];
                char size_conssumption[10];
                char size_price[10];

                GetWindowText(hwnd_distance, size_distance, sizeof(size_distance));
                float distance = atof(size_distance);

                GetWindowText(hwnd_consumption, size_conssumption, sizeof(size_conssumption));
                float consumption = atof(size_conssumption);

                GetWindowText(hwnd_price, size_price, sizeof(size_price));
                float price = atof(size_price);

                float cost = (distance / 100) * consumption * price;

                char result[50];
                sprintf(result, "%.2f", cost);
                SetWindowText(hwnd_result, result);
				
				if (cost <= 0) {
					MessageBox(hWnd, "Error vaules", "error", MB_ICONERROR | MB_OK);
				}
			}
			break;	
		}
		
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			SetTextColor(hdc, RGB(255,255,255));
			SetBkColor(hdc, RGB(68, 0, 102));
			
            TextOut(hdc, 40, 50, "distanse:", 10);
            TextOut(hdc, 40, 80, "consumption:", 13);
            TextOut(hdc, 40, 110, "price:", 7);
            TextOut(hdc, 40, 200, "cost:", 5);
			
			EndPaint(hWnd, &ps);
			
			break;	
		}
		
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		
		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd; 
	MSG msg;

	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc;
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	wc.hbrBackground = (HBRUSH)SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG) CreateSolidBrush(RGB(8, 37, 103)));
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass",
	                      "Calculate:",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		380,
		300,
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}