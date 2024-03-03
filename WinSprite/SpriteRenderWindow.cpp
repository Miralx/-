#include"SpriteRenderWindow.h"
#include<windowsx.h>
#include"SpriteUtils.h"
#include<thread>
#include <cstdlib>  // 包含随机数生成器所需的头文件
#include <ctime>    // 包含时间函数所需的头文件



namespace SpriteFrameWork
{
    // Global Variables:
    HINSTANCE g_hInst = NULL;                                // current instance

    int tempCurDir = 0;

    //HBITMAP gCurrentBitMap = NULL;    //图片缓存指针
    //std::thread* t1 = NULL;
    //bool bQuit = false;

	SpriteRenderWindow::SpriteRenderWindow(HINSTANCE hInstance, unsigned int width, unsigned int height, COLORREF keycolor)
	{

		if (hInstance)
			m_hIns = hInstance;
		else
			m_hIns = GetModuleHandle(NULL);   //win api获得模型句柄

		m_width = width;
		m_height = height;
		m_TransparentKeyColor = keycolor;
        distance = 0;
        cur_dir = 0;

        std::wstring classname = L"SpriteRenderWindow";
        std::wstring title = L"Sprite1.0";

        MyRegisterClass(classname);

        InitInstance(classname, title);

	}

    SpriteRenderWindow::~SpriteRenderWindow()
    {

    }

    LRESULT CALLBACK SpriteRenderWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)   //首先把lParam转换为自己的spritewindow实例
    {

        SpriteRenderWindow* pSpriteWindow = nullptr;

        if (message == WM_CREATE) {
            pSpriteWindow = (SpriteRenderWindow*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            pSpriteWindow->m_hWnd = hWnd;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pSpriteWindow);
        }
        else {
            pSpriteWindow = (SpriteRenderWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        }

        if (!pSpriteWindow) return DefWindowProc(hWnd, message, wParam, lParam);

        tempCurDir = pSpriteWindow->getCurDir();   //?要不要？

        switch (message)
        {
        /*case WM_CREATE:       //调用createwindow 第一个触发的事件   做一些初始化任务
        {
            SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST);
            SetLayeredWindowAttributes(hWnd, pSpriteWindow->m_TransparentKeyColor, 255, LWA_COLORKEY);  //设置透明色
            SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

            SetTimer(hWnd, 1, 20, NULL);   //时间间隔20ms

            std::thread* t1 = new std::thread([&]() {

                const char* files[] = { "1_0.bmp", "1_1.bmp", "1_2.bmp", "1_3.bmp" };
                int i = 0;

                while (!bQuit)
                {
                    //std::this_thread::sleep_for(std::chrono::seconds(1));   //刷新率1s
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));   // 暂停100毫秒，即0.1秒

                    int index = i % 4;     //切换帧的index

                    std::string testfile = SpriteFrameWork::Utils::GetRootDir() + "\\split_images1\\" + files[index];

                    gCurrentBitMap = (HBITMAP)LoadImageA(g_hInst, testfile.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

                    ::InvalidateRect(pSpriteWindow->m_hWnd, NULL, TRUE);
                    UpdateWindow(pSpriteWindow->m_hWnd);    //强制窗口刷新

                    i++;
                }

                });
            break;
        }*/

            HANDLE_MSG(hWnd, WM_CREATE, pSpriteWindow->OnCreate);
            HANDLE_MSG(hWnd, WM_LBUTTONDOWN, pSpriteWindow->OnLButtonDown);
            HANDLE_MSG(hWnd, WM_LBUTTONUP, pSpriteWindow->OnLButtonUp);
            HANDLE_MSG(hWnd, WM_MOUSEMOVE, pSpriteWindow->OnLMouseMove);
            //HANDLE_MSG(hWnd, WM_RBUTTONUP, pSpriteWindow->OnRButtonUp);
            HANDLE_MSG(hWnd, WM_PAINT, pSpriteWindow->OnPaint);

        //case WM_LBUTTONDOWN:     //响应鼠标事件
        //    break;

        //case WM_LBUTTONUP:
        //    break;

        //case WM_MOUSEMOVE:
        //    break;

        //case WM_RBUTTONUP:
        //    break;

        case WM_TIMER:
        {
            // 获取窗口位置和大小
            RECT rect;
            GetWindowRect(hWnd, &rect);
            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;

            int newX, newY;

            //到达边界，或者“时间用完”，需要改变方向
            if (rect.left - 2 <= 0 || rect.right + 2 >= GetSystemMetrics(SM_CXSCREEN) || pSpriteWindow->getDistance() == 0) {
                srand(time(NULL));
                int dir = rand() % 3 - 1;
                tempCurDir = dir;    //实在不会传参给OnCreate了，用全局变量
                pSpriteWindow->setCurDir(dir);
                int dist = rand() % GetSystemMetrics(SM_CXSCREEN) / 2;
                pSpriteWindow->setDistance(dist);
            }
            else {   //移动次数减一
                pSpriteWindow->setDistance(pSpriteWindow->getDistance() - 1);
            }

            // 计算新的位置，是否要改变方向，每次移动两个像素
            if (pSpriteWindow->cur_dir == -1) {    //左
                newX = rect.left - 2;
                newY = rect.top;
            }
            else if(pSpriteWindow->cur_dir == 1){    //右
                newX = rect.left + 2;
                newY = rect.top;
            }
            else {    //静止
                newX = rect.left;
                newY = rect.top;
            }

            // 移动窗口
            MoveWindow(hWnd, newX, newY, width, height, TRUE);
            //这里使用的是 MoveWindow 函数，它可以同时改变窗口的位置和大小。如果只想改变位置，可以使用 SetWindowPos 函数。
            break;
        }

        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        //case WM_PAINT:
        //{
        //    PAINTSTRUCT ps;
        //    HDC hdc = BeginPaint(hWnd, &ps);
        //    // TODO: Add any drawing code that uses hdc here...
        //    EndPaint(hWnd, &ps);
        //}
        //break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);        //处理常用消息
        }
        return 0;
    }

    ATOM SpriteRenderWindow::MyRegisterClass(std::wstring classname)
    {
        WNDCLASSEXW wcex;

        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = m_hIns;
        wcex.hIcon = NULL;
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = classname.c_str();
        wcex.hIconSm = NULL;

        return RegisterClassExW(&wcex);
    }

    BOOL SpriteRenderWindow::InitInstance(std::wstring classname, std::wstring title)
    {
        extern HINSTANCE g_hInst;
        g_hInst = m_hIns; // Store instance handle in our global variable

        //HWND hWnd = CreateWindowW(classname.c_str(), title.c_str(), /*WS_OVERLAPPEDWINDOW |*/ WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP,     //窗口形式
        //    0, 0, m_width, m_height, nullptr, nullptr, m_hIns, this);     //起始坐标   宽高
        int screen_width = GetSystemMetrics(SM_CXSCREEN);
        int screen_height = GetSystemMetrics(SM_CYSCREEN);
        HWND hWnd = CreateWindowW(classname.c_str(), title.c_str(), WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP,
            screen_width - 100, screen_height - 100, m_width, m_height, nullptr, nullptr, m_hIns, this);


        if (!hWnd)
        {
            m_hWnd = NULL;
            return FALSE;
        }

        m_hWnd = hWnd;

        ShowWindow(hWnd, SW_SHOW);
        UpdateWindow(hWnd);

        return TRUE;
    }

    int SpriteRenderWindow::Loop()
    {
        MSG msg;

        while (GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);   //dispatchmessageW?
        }

        return 0;
    }

    void SpriteRenderWindow::OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
    {
        if (!fDoubleClick) {    //判断如果不是双点
            SetCapture(hwnd);    //捕获鼠标值
            m_leftpress = TRUE;
            m_mouseX = x;
            m_mouseY = y;
        }
    }

    void SpriteRenderWindow::OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags) 
    {
        if (m_leftpress) {    //判断如果已经是按下状态， 现在按上了 
            SetCapture(hwnd);    //捕获鼠标值
            m_leftpress = FALSE;
            m_mouseX = 0;    //设为0  初始化    按下->移动->释放
            m_mouseY = 0;
            ReleaseCapture();   //释放鼠标捕获
        }
    }

    void SpriteRenderWindow::OnLMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
    {
        if (m_leftpress) {   //鼠标按下并在移动
            RECT winRect = { 0 };
            GetWindowRect(hwnd, &winRect);    //获得窗口矩形
            int cx = winRect.left + (x - m_mouseX);    //原坐标加偏移量
            int cy = winRect.top + (y - m_mouseY);
            MoveWindow(hwnd, cx, cy, winRect.right - winRect.left, winRect.bottom - winRect.top, TRUE);
        }
    }

    HBITMAP gCurrentBitMap = NULL;    //图片缓存指针
    std::thread* t1 = NULL;
    bool bQuit = false;

    BOOL SpriteRenderWindow::OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct) 
    {
        SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST);  
        SetLayeredWindowAttributes(hWnd, m_TransparentKeyColor, 255, LWA_COLORKEY);  //设置透明色
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

        SetTimer(hWnd, 1, 20, NULL);   //时间间隔20ms

        std::thread* t1 = new std::thread([&]() {

            const char* left_files[] = { "1_0.bmp", "1_1.bmp", "1_2.bmp", "1_3.bmp" };
            const char* right_files[] = { "2_0.bmp", "2_1.bmp", "2_2.bmp", "2_3.bmp" };
            const char* stop_files[] = { "0_0.bmp", "0_0.bmp", "0_0.bmp", "0_0.bmp" };
            int i = 0;

            while (!bQuit)
            {
                //std::this_thread::sleep_for(std::chrono::seconds(1));   //刷新率1s
                std::this_thread::sleep_for(std::chrono::milliseconds(100));   // 暂停100毫秒，即0.1秒

                int index = i % 4;     //切换帧的index

                std::string testfile;
                if (tempCurDir == -1) {
                    testfile = SpriteFrameWork::Utils::GetRootDir() + "\\split_images1\\" + left_files[index];
                }
                else if (tempCurDir == 1) {
                    testfile = SpriteFrameWork::Utils::GetRootDir() + "\\split_images1\\" + right_files[index];
                }
                else {
                    testfile = SpriteFrameWork::Utils::GetRootDir() + "\\split_images1\\" + stop_files[index];
                }

                gCurrentBitMap = (HBITMAP)LoadImageA(g_hInst, testfile.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

                ::InvalidateRect(m_hWnd, NULL, TRUE);
                UpdateWindow(m_hWnd);    //强制窗口刷新

                i++;
            }

        });

        return TRUE;
    }

    void SpriteRenderWindow::OnPaint(HWND hWnd)
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT rc;

        GetClientRect(hWnd, &rc);  //获得除了标题栏的部分
        HBRUSH brush = CreateSolidBrush(m_TransparentKeyColor);  //刷成透明色
        FillRect(hdc, &rc, brush);
        DeleteObject(brush);

        UpdateFrame(hdc);    //更新帧

        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }

    //HBITMAP gCurrentBitMap = NULL;    //图片缓存指针

    void SpriteRenderWindow::UpdateFrame(HDC hdc)
    {

        //std::string testfile = "C:\\Users\\PC\\Desktop\\dog\\split_images1\\1_0.bmp";    // ..\\Debug\\actors\\son\\act1\\25.bmp
        //std::string testfile = SpriteFrameWork::Utils::GetRootDir() + "\\split_images1\\1_0.bmp";
        //std::string testfile = "./dog\\dog2.bmp";

        //gCurrentBitMap = (HBITMAP)LoadImageA(g_hInst, testfile.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (gCurrentBitMap == NULL) return;

        BITMAP bm = { 0 };
        GetObject(gCurrentBitMap, sizeof(bm), &bm);   

        HDC hMemdc = CreateCompatibleDC(hdc);    

        HBITMAP hBitmapOld = (HBITMAP)SelectObject(hMemdc, gCurrentBitMap);
        BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hMemdc, 0, 0, SRCCOPY);
        SelectObject(hMemdc, hBitmapOld);

        DeleteObject(gCurrentBitMap);

        gCurrentBitMap = NULL;

        DeleteDC(hMemdc);

    }

    void SpriteRenderWindow::setCurDir(int dir)
    {
        cur_dir = dir;
    }

    void SpriteRenderWindow::setDistance(int dist)
    {
        distance = dist;
    }

    int SpriteRenderWindow::getCurDir()
    {
        return cur_dir;
    }

    int SpriteRenderWindow::getDistance()
    {
        return distance;
    }
}
