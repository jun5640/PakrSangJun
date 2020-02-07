#pragma once
#pragma warning(disable:4996)

#include "SingletonBase.h"
#include "CommonFeature.h"

#include <string>
#include <sstream>
#include <atlstr.h>
#include <vector>


using namespace std;

class FileManager : public SingletonBase<FileManager>
{
private:

	string tileData;
	TCHAR buf[1000000];
	vector<string> v_stringTileData;
	TCHAR temp[10];

public:
	void Save(HWND hWnd)
	{
		StringToTCHAR(tileData);

		OPENFILENAME OFN;
		char lpstrFile[MAX_PATH] = "";
		char lpstrPath[MAX_PATH] = "";

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = hWnd;
		OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 256;
		GetCurrentDirectory(MAX_PATH, lpstrPath);
		OFN.lpstrInitialDir = lpstrPath;

		if (GetSaveFileName(&OFN) == 0)
		{
			DWORD err = CommDlgExtendedError();
			return;
		}

		HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		DWORD writeB;

		WriteFile(hFile, buf, sizeof(buf), &writeB, NULL);

		//MessageBox(hWnd, "¼º°ø", "Save", MB_OK);

		CloseHandle(hFile);
	}

	void Load(HWND hWnd, MapToolTile tile[19][19],LPCSTR path)
	{
		TCHAR tcbuf[1000000];


		HANDLE hFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		
		DWORD readB;

		ReadFile(hFile, tcbuf, sizeof(tcbuf), &readB, NULL);
		tileData = TCHARToString(tcbuf);
		DataToTile(tile);
	    //MessageBox(hWnd, tcbuf, "Load", MB_OK);

		CloseHandle(hFile);
	}

	void Load(HWND hWnd, MapToolTile tile[19][19])
	{
		StringToTCHAR(tileData);

		OPENFILENAME OFN;
		char lpstrFile[MAX_PATH] = "";
		char lpstrPath[MAX_PATH] = "";

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = hWnd;
		OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 256;
		GetCurrentDirectory(MAX_PATH, lpstrPath);
		OFN.lpstrInitialDir = lpstrPath;

		if (GetSaveFileName(&OFN) == 0)
		{
			DWORD err = CommDlgExtendedError();
			return;
		}


		TCHAR tcbuf[99500];

		HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		DWORD readB;

		ReadFile(hFile, tcbuf, sizeof(tcbuf), &readB, NULL);
		tileData = TCHARToString(tcbuf);
		DataToTile(tile);

		CloseHandle(hFile);

	}

	void TileToData(MapToolTile tile[19][19])
	{
		tileData = "";

		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				tileData += TileToData(tile[i][j]);
			}
		}
	}

	string TileToData(MapToolTile tile)
	{
		string result = "";

		if (tile.IsSet)
		{
			result += "1";
		}
		else
		{
			result += "0";
		}

		result += ",";

		result += to_string(tile.position.x);

		result += ",";

		result += to_string(tile.position.y);

		result += ",";

		result += to_string(tile.tileinfo.GetWidth());

		result += ",";

		result += to_string(tile.tileinfo.GetHeight());

		result += ",";

		if (tile.tileinfo.GetIsDestory())
		{
			result += "1";
		}
		else
		{
			result += "0";
		}

		result += ",";


		if (tile.tileinfo.GetIsMove())
		{
			result += "1";
		}
		else
		{
			result += "0";
		}

		result += ",";

		if (tile.tileinfo.GetIsFloor())
		{
			result += "1";
		}
		else
		{
			result += "0";
		}

		result += ",";

		if (tile.tileinfo.GetIsTop())
		{
			result += "1";
		}
		else
		{
			result += "0";
		}

		result += ",";

		result += to_string(tile.tileinfo.GetScrWidth());

		result += ",";

		result += to_string(tile.tileinfo.GetScrHeight());

		result += ",";

		if (tile.tileinfo.GetImagePath() == nullptr)
		{
			result += " ";
		}
		else
		{
			result += TCHARToString(tile.tileinfo.GetImagePath());
		}


		result += ",";

		return result;
	}


	int IntDataToTile(MapToolTile& tile,int count)
	{
		string result = "";

		if (v_stringTileData[count] == "1")
		{
			tile.IsSet = true;
		}
		else
		{
			tile.IsSet = false;
		}
		
		count++;

		tile.position.x = StringToInt(v_stringTileData[count]);

		count++;

		tile.position.y = StringToInt(v_stringTileData[count]);

		count++;
	
		tile.tileinfo.SetWidth(StringToInt(v_stringTileData[count]));

		count++;

		tile.tileinfo.SetHeight(StringToInt(v_stringTileData[count]));

		count++;


		if (v_stringTileData[count] == "1")
		{
			tile.tileinfo.SetIsDestory(true);
		}
		else
		{
			tile.tileinfo.SetIsDestory(false);
		}
		
		count++;

		if (v_stringTileData[count] == "1")
		{
			tile.tileinfo.SetIsMove(true);
		}
		else
		{
			tile.tileinfo.SetIsMove(false);
		}

		count++;


		if (v_stringTileData[count] == "1")
		{
			tile.tileinfo.SetIsFloor(true);
		}
		else
		{
			tile.tileinfo.SetIsFloor(false);
		}

		count++;


		if (v_stringTileData[count] == "1")
		{
			tile.tileinfo.SetIsTop(true);
		}
		else
		{
			tile.tileinfo.SetIsTop(false);
		}

		count++;
	
		tile.tileinfo.SetScrWidth(StringToInt(v_stringTileData[count]));
	
		count++;

		tile.tileinfo.SetScrHeight(StringToInt(v_stringTileData[count]));

		count++;

		
		tile.tileinfo.SetImagePath((TCHAR*)v_stringTileData[count].c_str());

		count++;

		return count;
	}

	void DataToTile(MapToolTile tile[19][19])
	{
		stringstream s_stream(tileData);
		string token;
		v_stringTileData.clear();


		while (std::getline(s_stream, token,','))
		{
			v_stringTileData.push_back(token);
		}
		int count = 0;
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				count = IntDataToTile(tile[i][j],count);
			}
		}
	}

	void StringToTCHAR(string& s)
	{
		_tcscpy_s(buf, CA2T(s.c_str()));
	}

	

	int StringToInt(string &s)
	{
		
		_tcscpy_s(temp, CA2T(s.c_str()));

		return atoi(temp);
	}

	std::string TCHARToString(const TCHAR* ptsz)
	{
		if (ptsz == nullptr) return " ";

		return string(ptsz);
	}
};

