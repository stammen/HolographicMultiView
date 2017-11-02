// ScreenCaptureApp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <collection.h>  
#include <thread>        
#include <ppltasks.h>

using namespace concurrency;
using namespace Windows::ApplicationModel::AppService;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::System;



[Platform::MTAThread]
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    auto uri = ref new Uri("launcher-uwp:"); // The protocol handled by the launched app
    auto options = ref new LauncherOptions();
    concurrency::task<bool> task(Launcher::LaunchUriAsync(uri, options));
    bool result = task.get();
    return 0;

}

