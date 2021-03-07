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

        private void button1_Click(object sender, EventArgs e)
        {
            s_httpClient.GetStringAsync("http://www.baidu.com").ContinueWith(
                downloadTask =>
                {
                    button1.Text = downloadTask.Result;
                },
                // 如果不指定contenxt的话，的确会报
                // System.InvalidOperationException: 'The calling thread cannot access this object because a different thread owns it.'
                TaskScheduler.FromCurrentSynchronizationContext() 
            );
        }
    }
}