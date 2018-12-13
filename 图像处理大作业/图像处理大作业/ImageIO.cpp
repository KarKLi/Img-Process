#include "ImageIO.hpp"
using namespace Gdiplus;
OPENFILENAME IO::ofn = { 0 };

IO::IO(HWND hwnd, std::string name)
{
	err_code = 0;
	ParentHwnd = hwnd;
	try
	{
		Image = imread(name);
		if (Image.data == NULL)
			throw "Open Image file failed!";
	}
	catch (char *e)
	{
		_STL_ASSERT(NULL, e);
	}

}
IO::IO(const IO& obj)
{
	this->Image = obj.Image;
	this->Imgname = obj.Imgname;
	this->ofn = obj.ofn;
	this->err_code = obj.err_code;
	this->ParentHwnd = obj.ParentHwnd;
	wcscpy(this->wImgname, obj.wImgname);
}
void IO::wideCharToMultiByte(std::string &str, wchar_t * pWCStrKey)
{
	int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
	char* pCStrKey = new char[pSize + 1];
	WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
	pCStrKey[pSize] = '\0';
	str = pCStrKey;

}
void IO::OpenImage()
{
	wchar_t fpath[100] = { 0 };
//Initalize the struct ofn
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = ParentHwnd;
	ofn.lpstrFilter = L"*.*\0*.*\0\0";
	ofn.lpstrInitialDir = L"./";
	ofn.lpstrFile = fpath;
	ofn.nMaxFile = sizeof(fpath) / sizeof(*fpath);
	ofn.nFilterIndex = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
	if (!GetOpenFileName(&ofn))
	{
		err_code = 1;//Didn't choose file
	}
	else
	{
		wcscpy(wImgname, fpath);
		wideCharToMultiByte(Imgname, fpath);
		Image = imread(Imgname);
		try
		{
			if (Image.data == NULL)
				throw "Open Image file failed!";
		}
		catch (char *e)
		{
			_STL_ASSERT(NULL, e);
			err_code = 2;//No such file or directory or image broken
		}
	}
//loading end
}
void IO::ShowImage(HDC hdc)
{
	RECT rect;
	GetWindowRect(ParentHwnd, &rect);
	Gdiplus::Image img(wImgname);
	if (img.GetLastStatus() != Status::Ok)
	{
		MessageBox(ParentHwnd, L"º”‘ÿÕº∆¨ ß∞‹!", L"Ã· æ", MB_OK);
		err_code = 2;//No such file or directory or image broken
	}
	uint width = img.GetWidth();
	uint height = img.GetHeight();
	Gdiplus::Graphics graphics(hdc);
	graphics.DrawImage(&img, 0, 0, width, height);
	InvalidateRect(ParentHwnd, NULL, TRUE);
	drawed = true;
}