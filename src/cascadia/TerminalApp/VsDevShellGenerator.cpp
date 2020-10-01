// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "pch.h"
#include "VsDevShellGenerator.h"
#include "Setup.Configuration.h"
#include "DefaultProfileUtils.h"
#include "VsSetupConfiguration.h"

std::wstring TerminalApp::VsDevShellGenerator::GetProfileName(const VsSetupConfiguration::VsSetupInstance instance) const
{
    std::wstring name{ L"Developer PowerShell for VS " };
    name.append(instance.GetProductLineVersion());

    std::wstring channelName{ instance.GetChannelName() };

    if (channelName != L"Release")
    {
        name.append(L" [" + channelName + L"]");
    }

    return name;
}

std::wstring TerminalApp::VsDevShellGenerator::GetProfileCommandLine(const VsSetupConfiguration::VsSetupInstance instance) const
{
    // The triple-quotes are a PowerShell path escape sequence that can safely be stored in a JSON object.
    // The "SkipAutomaticLocation" parameter will prevent "Enter-VsDevShell" from automatially setting the shell path
    // so the path in the profile will be used instead.
    std::wstring commandLine{ L"powershell.exe -NoExit -Command \"& {" };
    commandLine.append(L"Import-Module \"\"\"" + instance.GetDevShellModulePath() + L"\"\"\";");
    commandLine.append(L"Enter-VsDevShell " + instance.GetInstanceId() + L" -SkipAutomaticLocation");
    commandLine.append(L"}\"");

    OutputDebugString(commandLine.c_str());
    OutputDebugString(L"\n");

    return commandLine;
}
