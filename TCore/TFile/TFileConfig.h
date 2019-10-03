//基础文件对象
#pragma once

namespace TCore
{
	namespace TFile
	{
#define LINE_MAX_LEN 1024
		class T_DLL_EXPORT CTConfigByCfg
		{
		private:
			CFileObject m_file;
			hash_map<tstring, tstring> m_hMap;
			tbool analysis();

		public:
			CTConfigByCfg()
			{
				m_hMap.clear();
			}

			tbool Init(const tcchar* a_sFileName)
			{
				m_file.open(a_sFileName, E_FILE_B_READ);
				return analysis();
			}

			tstring getValue(const tcchar* a_sKey);
			n32 getN32(const tcchar* a_sKey);
			f32 getF32(const tcchar* a_sKey);

			~CTConfigByCfg()
			{
				m_file.close();
				m_hMap.clear();
			}

		};
	}
}

