
project(vEngineEditor CSharp)
include(CSharpUtilities)

add_executable(${PROJECT_NAME}
    App.config
    App.xaml
    App.xaml.cs
    MainWindow.xaml
    MainWindow.xaml.cs
    D3DHwndHost.cs

    Properties/AssemblyInfo.cs
    Properties/Resources.Designer.cs
    Properties/Resources.resx
    Properties/Settings.Designer.cs
    Properties/Settings.settings
)
csharp_set_designer_cs_properties(
    Properties/AssemblyInfo.cs
    Properties/Resources.Designer.cs
    Properties/Resources.resx
    Properties/Settings.Designer.cs
    Properties/Settings.settings
)

csharp_set_xaml_cs_properties(
    App.xaml
    App.xaml.cs
    MainWindow.xaml
    MainWindow.xaml.cs
)

set_property(SOURCE App.xaml PROPERTY VS_XAML_TYPE "ApplicationDefinition")

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_REFERENCES
    "Microsoft.CSharp"
    "PresentationCore"
    "PresentationFramework"
    "System"
    "System.Core"
    "System.Data"
    "System.Data.DataSetExtensions"
    # "System.Net.Http"
    "System.Xaml"
    "System.Xml"
    "System.Xml.Linq"
    "WindowsBase"
)