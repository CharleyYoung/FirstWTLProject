#pragma once
class CMyWindow : public CFrameWindowImpl<CMyWindow>
{
public:
	DECLARE_FRAME_WND_CLASS(_T("First WTL window"), IDR_MAINFRAME);

	BEGIN_MSG_MAP_EX(CMyWindow)
		MSG_WM_CREATE(OnCreate)//定义一个窗口创建的消息映射
		MSG_WM_DESTROY(OnDestroy)//定义一个窗口销毁的消息映射
		MSG_WM_TIMER(OnTimer)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMyWindow>)
	END_MSG_MAP()

	/*
	OnCreate函数负责在窗口创建的时候设定一个计时器，该计时器每1000毫秒触发一次
	*/
	LRESULT OnCreate(LPCREATESTRUCT lParam) {
		SetTimer(1, 1000);
		SetMsgHandled(false);
		return 0;
	}

	/*
	OnDestroy函数负责在窗口销毁的时候销毁计时器
	*/
	void OnDestroy() {
		KillTimer(1);
		SetMsgHandled(false);
	}

	/*
	OnTimer函数负责在每次计时器触发之后重新绘画窗口
	*/
	void OnTimer(UINT uTimerID)
	{
		if (1 != uTimerID)
			SetMsgHandled(false);
		else
			RedrawWindow();
	}

	/*
	OnEraseBkgnd函数负责在每次OnTimer函数绘画窗口之后在指定位置显示时间
	*/
	LRESULT OnEraseBkgnd(HDC hdc)
	{
		CDCHandle dc(hdc);
		CRect rc;
		SYSTEMTIME st;
		CString sTime;

		// Get our window's client area.
		GetClientRect(rc);

		// Build the string to show in the window.
		GetLocalTime(&st);
		sTime.Format(_T("The time is %d:%02d:%02d"),
			st.wHour, st.wMinute, st.wSecond);

		// Set up the DC and draw the text.
		dc.SaveDC();

		dc.SetBkColor(RGB(255, 255, 255));
		dc.SetTextColor(RGB(0, 0, 0));
		dc.ExtTextOut(0, 0, ETO_OPAQUE, rc, sTime,
			sTime.GetLength(), NULL);

		// Restore the DC.
		dc.RestoreDC(-1);
		return 1; // We erased the background (ExtTextOut did it)
	}
};