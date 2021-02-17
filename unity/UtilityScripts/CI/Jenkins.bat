@REM 由于windows系统的eol为CRLF，所以这个文件也必须为CRLF
@REM 构建脚本参考链接 
@REM https://docs.unity3d.com/Manual/CommandLineArguments.html
@REM https://docs.unity3d.com/Manual/BuildSettings.html

@REM 获取命令行传参  
@REM Jenkins工作目录, 构建Number， Unity执行程序路径， 仓库路径  
set Jenkins_Workspace=%1%
set Jenkins_Build_Number=%2%
set Unity_Bin=%3%
set Repo_Path=%4%

@REM 设置一些方法名
set Build_Method_Android=TPS.Editor.Build.BuildScript.BuildAndroid
set XLua_Clear_Method=CSObjectWrapEditor.Generator.ClearAll
set XLua_Gen_Method=CSObjectWrapEditor.Generator.GenAll

set Build_log_File=%Jenkins_Workspace%\Log\BuildLog_%Jenkins_Build_Number%.log


@REM 写入一些信息给到文件提供给C#侧读取  
set JenkinsEnv_File=%Jenkins_Workspace%\JenkinsEnv.txt
set Build_Result_File=%Jenkins_Workspace%\BuildResult.txt

echo %Jenkins_Build_Number% > %JenkinsEnv_File%
del /s /q %Build_Result_File%

@REM --- 开始构建 ---

@REM Lua
@REM %Unity_Bin% -quit -batchmode -projectPath %Repo_Path%  -executeMethod %XLua_Clear_Method%
@REM %Unity_Bin% -quit -batchmode -projectPath %Repo_Path%  -executeMethod %XLua_Gen_Method%

@REM 直接删除文件夹更快, 并且Gen的函数在C#代码中调用更快
rmdir /s /q "%Repo_Path%\Assets\XLua\Gen"

@REM build
%Unity_Bin% -quit -batchmode -logFile %Build_log_File%  -projectPath %Repo_Path%  -executeMethod %Build_Method_Android%
del /s /q %JenkinsEnv_File%

if not %errorlevel%==0 ( goto fail ) else ( goto success )
:fail
echo Build APK Fail
exit -1

:success
@REM 根据写入到文件的校验码判断是否编译成功  
set /p Build_Result=<"%Build_Result_File%"
if not %Build_Result%==1 ( goto fail ) else ( echo Build APK Success )

