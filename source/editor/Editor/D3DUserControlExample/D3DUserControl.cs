using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace D3DUserControlExample
{
    public class D3DDLL
    {
        [DllImport("D3DDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void InitD3D(IntPtr window, int Width, int Height);

        [DllImport("D3DDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RenderFrame();

        [DllImport("D3DDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void CleanD3D();
    }

    //add from new item-> window forms-> user control
    class D3DUserControl : UserControl
    {
        public D3DUserControl()
        {
            this.InitializeComponent();
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            D3DDLL.RenderFrame();
        }

        protected override void OnResize(EventArgs e)
        {
        }


        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // D3DUserControl
            // 
            this.Name = "D3DUserControl";
            this.Load += new System.EventHandler(this.D3DUserControl_Load);
            this.ResumeLayout(false);

        }
        private void D3DUserControl_Load(object sender, EventArgs e)
        {
            D3DDLL.InitD3D(this.Handle, this.Width, this.Height);
        }

        protected override void Dispose(bool disposing)
        {
            //throw new NotImplementedException();
        }

        protected override void WndProc(ref System.Windows.Forms.Message m)
        {
            base.WndProc(ref m);
            //throw new NotImplementedException();
        }
    }
}
