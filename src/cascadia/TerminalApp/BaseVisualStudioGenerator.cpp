// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "pch.h"
#include "BaseVisualStudioGenerator.h"
#include "DefaultProfileUtils.h"

std::vector<winrt::TerminalApp::Profile> TerminalApp::BaseVisualStudioGenerator::GenerateProfiles()
{
    std::vector<winrt::TerminalApp::Profile> profiles;

    // There's no point in enumerating valid Visual Studio instances more than once,
    // so cache them for use by both Visual Studio profile generators.
    if (!BaseVisualStudioGenerator::hasQueried)
    {
        instances = VsSetupConfiguration::QueryInstances();
        hasQueried = true;
    }

    for (auto const& instance : BaseVisualStudioGenerator::instances)
    {
        try
        {
            if (!IsInstanceValid(instance))
                continue;

            auto DevShell{ CreateDefaultProfile(GetProfileName(instance)) };
            DevShell.Commandline(GetProfileCommandLine(instance));
            DevShell.StartingDirectory(instance.GetInstallationPath());
            DevShell.IconPath(GetProfileIconPath());

            profiles.emplace_back(DevShell);
        }
        catch (const wil::ResultException&)
        {
            continue;
        }
    }

    return profiles;
}
