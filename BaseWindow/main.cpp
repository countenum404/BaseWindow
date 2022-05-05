#include "BaseWindow.h"
#include <string>

class MainWindow :
	public BaseWindow
{
public:
	virtual LRESULT EventHandle(UINT Msg, WPARAM wParam, LPARAM lParam) override
	{
		if (Msg == WM_DESTROY)
		{
			PostQuitMessage(0);
		}
		return DefWindowProc(this->hWnd, Msg, wParam, lParam);
	}
};



int main()
{
	MainWindow win;
	std::string title = "Application";
	win.Create(600, 800, title);
	win.Show();
	return 0;
}