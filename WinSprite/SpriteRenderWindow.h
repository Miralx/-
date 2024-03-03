#pragma once
#include<string>
#include<Windows.h>


namespace SpriteFrameWork       //利用命名空间防止冲突
{

	class SpriteRenderWindow    
	{
	private:
		HINSTANCE m_hIns;    //窗口的句柄
		unsigned int m_width, m_height;      //窗口大小
		COLORREF m_TransparentKeyColor;   //透明色
		HWND m_hWnd;  
		bool m_leftpress = false;
		//bool m_KeepTop = true;
		int m_mouseX;
		int m_mouseY;
		int cur_dir;    //当前方向
		int distance;   //当前方向上还可以移动的次数，一次两个像素， 每次刷新屏幕移动一次

	public:
		SpriteRenderWindow(HINSTANCE hInstance = NULL, unsigned int width = 300, unsigned int height = 300, COLORREF keycolor = RGB(0, 0, 0));
		~SpriteRenderWindow();
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		void setCurDir(int dir);
		void setDistance(int dist);
		int getDistance();
		int getCurDir();

		int Loop();

	private:
		ATOM MyRegisterClass(std::wstring classname);
		BOOL InitInstance(std::wstring classname, std::wstring title);

	protected:
		//事件处理函数
		void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
		void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
		void OnLMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
		BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
		//void OnRButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
		//void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void OnPaint(HWND hWnd);
		void UpdateFrame(HDC hdc);

	};

}