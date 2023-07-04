#include <Windows.h>
#include "dialog.h"

namespace fkkt {
	void Dialog::showMsg(String msg, String title) const
	{
		MessageBoxW(
			NULL,
			msg,
			title,
			MB_OK
		);
	}
}
