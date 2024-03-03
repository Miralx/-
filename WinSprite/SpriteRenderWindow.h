#pragma once
#include<string>
#include<Windows.h>


namespace SpriteFrameWork       //���������ռ��ֹ��ͻ
{

	class SpriteRenderWindow    
	{
	private:
		HINSTANCE m_hIns;    //���ڵľ��
		unsigned int m_width, m_height;      //���ڴ�С
		COLORREF m_TransparentKeyColor;   //͸��ɫ
		HWND m_hWnd;  
		bool m_leftpress = false;
		//bool m_KeepTop = true;
		int m_mouseX;
		int m_mouseY;
		int cur_dir;    //��ǰ����
		int distance;   //��ǰ�����ϻ������ƶ��Ĵ�����һ���������أ� ÿ��ˢ����Ļ�ƶ�һ��

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
		//�¼�������
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