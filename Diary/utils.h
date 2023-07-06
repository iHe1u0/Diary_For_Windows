#pragma once
#include <string>
#include <Windows.h>

namespace fkkt {
	class Utils
	{
	public:
		static LPCWSTR StringToLPCWSTR(const std::string& source)
		{
			size_t m_htSize = source.length();
			int m_wLen = ::MultiByteToWideChar(CP_UTF8,
				0,
				source.c_str(),
				-1,
				NULL,
				0);
			wchar_t* m_hovertreeBuffer = new wchar_t[m_wLen + 1];
			memset(m_hovertreeBuffer, 0, (m_wLen + 1) * sizeof(wchar_t));
			MultiByteToWideChar(CP_ACP, 0, source.c_str(), m_htSize, (LPWSTR)m_hovertreeBuffer, m_wLen);
			return m_hovertreeBuffer;
		}
	};
}

