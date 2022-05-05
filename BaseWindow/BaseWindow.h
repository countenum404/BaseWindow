#ifndef UNICODE
#define UNICODE
#endif 
#pragma once
#include <Windows.h>
#include <string>

class BaseWindow
{
public:

	//ctor
	BaseWindow() : hWnd(NULL),
		CLASS_NAME(L"Application"), Height(600), Width(800),
		hInstance(NULL)
	{

	}
	BaseWindow(const int& width, const int& height, std::string& Title);

	//dtor
	~BaseWindow();

	//User usage functions
	void Show();
	BOOL Create(const int& width, const int& height, std::string& Title);

	//Define at the child class application 
	virtual LRESULT EventHandle(UINT Msg, WPARAM wParam, LPARAM lParam) = 0;
protected:

	HWND hWnd;
	WNDCLASS wc;
	MSG msg;
	HINSTANCE hInstance;
	LPCWSTR CLASS_NAME;
	int Height;
	int Width;

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
};
