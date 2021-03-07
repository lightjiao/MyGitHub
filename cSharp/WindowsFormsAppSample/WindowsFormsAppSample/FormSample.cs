using System;
using System.Net.Http;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsAppSample
{
    public partial class FormSample : Form
    {
        public FormSample()
        {
            InitializeComponent();
        }

        private static readonly HttpClient s_httpClient = new HttpClient();

        private async void button1_Click(object sender, EventArgs e)
        {
            //s_httpClient.GetStringAsync("http://www.baidu.com").ContinueWith(
            //    downloadTask =>
            //    {
            //        button1.Text = downloadTask.Result;
            //    },
            //    // 如果不指定contenxt的话，的确会报
            //    // System.InvalidOperationException: 'The calling thread cannot access this object because a different thread owns it.'
            //    TaskScheduler.FromCurrentSynchronizationContext() 
            //);

            // 直接使用await来优雅的实现
            // 但如果加了configureAwait(false)，反而会报错，原因和上面一样，执行到了完全不同的线程去了
            var text = await s_httpClient.GetStringAsync("http://www.baidu.com");// .ConfigureAwait(false);
            button1.Text = text;
        }
    }
}