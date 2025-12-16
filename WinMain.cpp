#include "originApp.h"
#include "BoxApp.h"
#include "ShapesApp.h"
#include "commonType.h"

#include <shellapi.h> // for CommandLineToArgvW
#include <wchar.h>    // for wcscmp

using namespace DirectX;

struct cmdLineInfo
{
	/*
	choose a instance to run
	0:initialize app
	*/
	int runInstanceIndex = -1;
	int geoType = 0;
};

bool processCmdLine(cmdLineInfo& cmd_line_info)
{
	int argc;
	wchar_t** argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (argv == NULL) {
		MessageBox(nullptr, L"cmdLine error", L"Error", MB_OK);
		return false;
	}

	for (int i = 1; i < argc; ++i) {
		if (wcscmp(argv[i], L"-ins") == 0 && i + 1 < argc) {
			cmd_line_info.runInstanceIndex = _wtoi(argv[i + 1]);
			i++;
		}
		else if (wcscmp(argv[i], L"-geoType") == 0 && i + 1 < argc)
		{
			cmd_line_info.geoType = _wtoi(argv[i + 1]);
			i++;
		}
	}

	LocalFree(argv);

	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	cmdLineInfo m_cmd_line_info;

	if (!processCmdLine(m_cmd_line_info)) return 1;

	try
	{
		if (m_cmd_line_info.runInstanceIndex == 0)
		{
			InitDirect3DApp theApp(hInstance);
			if (!theApp.Initialize()) return 0;

			return theApp.Run();
		}
		else if (m_cmd_line_info.runInstanceIndex == 1)
		{
			BoxApp theApp(hInstance);
			theApp.SetVSPath(L"Shaders\\colorBA.hlsl");
			theApp.SetPSPath(L"Shaders\\colorBA.hlsl");

			if (m_cmd_line_info.geoType == 0)
			{
				theApp.SetGeoType(geoType::box);
			}
			else if (m_cmd_line_info.geoType == 1)
			{
				theApp.SetGeoType(geoType::pyramid);
			}

			if (!theApp.Initialize()) return 0;

			return theApp.Run();
		}
		else if (m_cmd_line_info.runInstanceIndex == 2)
		{
			ShapesApp theApp(hInstance);
			theApp.SetVSPath(L"Shaders\\colorShapes.hlsl");
			theApp.SetPSPath(L"Shaders\\colorShapes.hlsl");

			if (!theApp.Initialize()) return 0;

			return theApp.Run();
		}
	}
	catch (DxException& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}

	return 0;
}