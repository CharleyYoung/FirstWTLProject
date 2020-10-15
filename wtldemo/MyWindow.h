#pragma once
class CMyWindow : public CFrameWindowImpl<CMyWindow>
{
public:
	DECLARE_FRAME_WND_CLASS(_T("First WTL window"), IDR_MAINFRAME);

	BEGIN_MSG_MAP_EX(CMyWindow)
		MSG_WM_CREATE(OnCreate)//����һ�����ڴ�������Ϣӳ��
		MSG_WM_DESTROY(OnDestroy)//����һ���������ٵ���Ϣӳ��
		MSG_WM_TIMER(OnTimer)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMyWindow>)
	END_MSG_MAP()

	/*
	OnCreate���������ڴ��ڴ�����ʱ���趨һ����ʱ�����ü�ʱ��ÿ1000���봥��һ��
	*/
	LRESULT OnCreate(LPCREATESTRUCT lParam) {
		SetTimer(1, 1000);
		SetMsgHandled(false);
		return 0;
	}

	/*
	OnDestroy���������ڴ������ٵ�ʱ�����ټ�ʱ��
	*/
	void OnDestroy() {
		KillTimer(1);
		SetMsgHandled(false);
	}

	/*
	OnTimer����������ÿ�μ�ʱ������֮�����»滭����
	*/
	void OnTimer(UINT uTimerID)
	{
		if (1 != uTimerID)
			SetMsgHandled(false);
		else
			RedrawWindow();
	}

	/*
	OnEraseBkgnd����������ÿ��OnTimer�����滭����֮����ָ��λ����ʾʱ��
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