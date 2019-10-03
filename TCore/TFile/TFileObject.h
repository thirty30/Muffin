//基础文件对象
#pragma once

namespace TCore
{
	namespace TFile
	{
		class T_DLL_EXPORT CFileObject
		{
		private:
			FILE* m_pFile;
			tbool m_bCanRead;
			tbool m_bCanWrite;
		public:
			CFileObject()
				: m_pFile(NULL)
				, m_bCanRead(false)
				, m_bCanWrite(false)
			{}
			~CFileObject() {}
			//打开文件
			tbool open(const tcchar* a_pFileName, EFileMode a_eMode);

			//得到当前文件指针位置
			n32 getPosition();

			//设置当前文件指针的位置
			n32 seek(n32 a_nOffset, ESeekOrigin a_eSeekOrigin);

			//读取限定长度的数据
			tbool readBuffer(tcchar* a_oBuffer, n32 a_nLen);

			//读取文件一行
			tcchar* readLine(tcchar* a_oBuffer, n32 a_nLen);

			//读取一个字符
			tcchar readChar();

			//写入限定长度的数据
			tbool writeBuffer(const tcchar* a_oBuffer, n32 a_nLen);

			//写入一行数据
			tbool writeLine(const tcchar* a_buffer);

			//写一个字符
			tbool writeChar(tcchar a_buffer);

			//得到文件总长度
			n32 getFileSize();

			//将缓冲区的数据写到文件
			void flush();

			tbool canRead()
			{
				return (m_pFile != NULL && m_bCanRead == true);
			}

			tbool canWrite()
			{
				return (m_pFile != NULL && m_bCanWrite == true);
			}

			//关闭文件
			void close();

			//////////////////////////////////////////////////////////////////////////
		};
	}
}

