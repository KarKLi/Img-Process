#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <commdlg.h>
#include <comdef.h>
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
#include "highgui.hpp"

using namespace std;
using namespace cv;

typedef unsigned int uint;

class IO
{
private:
	Mat Image;
	string Imgname;
	wchar_t wImgname[100] = { 0 };
	static OPENFILENAME ofn;
	uint err_code;
	HWND ParentHwnd;

	void wideCharToMultiByte(std::string &str, wchar_t * pWCStrKey);
public:
	bool drawed;
	IO(HWND hwnd) :Image(),Imgname(""),err_code(0),ParentHwnd(hwnd) {}
	IO(HWND hwnd, std::string name);
	IO(const IO& obj);

	uint GetErrorCode()const { return err_code; }
	const char *GetImageName()const { return Imgname.c_str(); }
	void OpenImage();
	void ShowImage(HDC hdc);
};
