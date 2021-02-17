using System;
using System.Collections.Generic;
using System.IO;
using UnityEditor;
using UnityEngine;

namespace TPS.Editor.Build
{
    public class BuildScript
    {
        [MenuItem("TPS_Editor/Build/BuildAndroid")]
        public static void BuildAndroid()
        {
            _GenLuaWrapper();

            var androidBuildOption = new BuildPlayerOptions();
            androidBuildOption.target = BuildTarget.Android;
            androidBuildOption.targetGroup = BuildTargetGroup.Android;
            androidBuildOption.locationPathName = _GetAndroidApkName("TPS");
            androidBuildOption.scenes = _GetScenesFromBuildSettings();

            androidBuildOption.options = BuildOptions.Development;
            androidBuildOption.options |= BuildOptions.CompressWithLz4;

            //切换平台
            EditorUserBuildSettings.SwitchActiveBuildTarget(BuildTargetGroup.Android, BuildTarget.Android);

            var report = BuildPipeline.BuildPlayer(androidBuildOption);
            WriteBuildResultToJenkinsFile(report.summary.result);
            Debug.Log($"Build report: {report}");
        }

        [MenuItem("TPS_Editor/Build/BuildIOS")]
        public static void BuildIOS()
        {
            // TODO:
            throw new NotImplementedException("还没实现IOS的构建");
        }

        private static string[] _GetScenesFromBuildSettings()
        {
            List<string> levels = new List<string>();
            for (int i = 0; i < EditorBuildSettings.scenes.Length; ++i)
            {
                if (EditorBuildSettings.scenes[i].enabled)
                {
                    levels.Add(EditorBuildSettings.scenes[i].path);
                }
            }

            return levels.ToArray();
        }

        /// <summary>
        /// 由于暂时无法直接build apk包，于是先构建成gradle中间包，再由流水线从gradle构建apk
        /// </summary>
        /// <see cref="https://discuss.gradle.org/t/com-android-builder-internal-aapt-v2-aapt2internalexception-aapt2-aapt2-3-4-0-5326820-windows-daemon-daemon-startup-failed/33584"/>
        /// <returns></returns>
        private static string _GetAndroidGradleOutputDir()
        {
            var env = GetJenkinsEnv();
            var dir = $"{env.Workspace}/Pkg/GradleTemp";

            if (Directory.Exists(dir))
            {
                Directory.Delete(dir);
            }
            return dir;
        }

        private static string _GetAndroidApkName(string name)
        {
            var env = GetJenkinsEnv();
            return $"{env.Workspace}/Pkg/{name}_{env.BuildNumber}_android.apk";
        }

        /// <summary>
        /// 生成lua代码
        /// 删除lua代码的操作在C#代码层面调用会报错, 改为写在了bat脚本中直接删除文件夹
        /// </summary>
        private static void _GenLuaWrapper()
        {
            XLua.DelegateBridge.Gen_Flag = true;
            CSObjectWrapEditor.Generator.GenAll();
        }

        # region Jenkins 环境处理相关

        /// <summary>
        /// 用于从Jenkins中读取一些数据，以及将构建结果写到jenkins
        /// </summary>
        private static JenkinsEnv? m_JenkinsEnv;

        private struct JenkinsEnv
        {
            /// <summary>
            /// 文件名
            /// </summary>
            public const string JenkinsEnvFile = "JenkinsEnv.txt";

            public const string ResultFile = "BuildResult.txt";

            /// <summary>
            /// jenkins workspace
            /// </summary>
            public string Workspace;

            /// <summary>
            /// 流水线构建号
            /// </summary>
            public int BuildNumber;
        }

        /// <summary>
        /// 流水线构建时将jenkins的一些相关信息写到文件，这里读取出来使用
        /// </summary>
        /// <returns></returns>
        private static JenkinsEnv GetJenkinsEnv()
        {
            if (m_JenkinsEnv != null)
            {
                return m_JenkinsEnv.Value;
            }

            var env = new JenkinsEnv();

            // 获取workspace的方法有一些trick，但也没有更好的获取方式了
            env.Workspace = Application.dataPath + "/../../";

            var jenkinsEnvFile = Path.Combine(env.Workspace, JenkinsEnv.JenkinsEnvFile);
            if (File.Exists(jenkinsEnvFile))
            {
                var envStrs = File.ReadAllLines(jenkinsEnvFile);
                if (false == int.TryParse(envStrs[0], out env.BuildNumber))
                {
                    env.BuildNumber = (int)((DateTimeOffset)DateTime.Now).ToUnixTimeSeconds();
                }
            }
            else
            {
                env.BuildNumber = (int)((DateTimeOffset)DateTime.Now).ToUnixTimeSeconds();
            }

            m_JenkinsEnv = env;

            return m_JenkinsEnv.Value;
        }

        /// <summary>
        /// 把构建结果写到文件
        /// </summary>
        private static void WriteBuildResultToJenkinsFile(UnityEditor.Build.Reporting.BuildResult result)
        {
            var env = GetJenkinsEnv();
            File.WriteAllText($"{env.Workspace}/{JenkinsEnv.ResultFile}", ((int)result).ToString());
        }

        #endregion
    }
}