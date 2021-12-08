﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;

namespace D3DWPFExample
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

    public class D3DHwndHost : HwndHost
    {
        protected IntPtr Hwnd { get; private set; }
        protected bool HwndInitialized { get; private set; }

        private const string WindowClass = "HwndWrapper";

        public D3DHwndHost()
        {
            Loaded += OnLoaded;
            Unloaded += OnUnloaded;
        }

        private void OnLoaded(object sender, RoutedEventArgs routedEventArgs)
        {
            Initialize();
            HwndInitialized = true;

            Loaded -= OnLoaded;

            CompositionTarget.Rendering += OnCompositionTargetRendering;
        }

        private void OnUnloaded(object sender, RoutedEventArgs routedEventArgs)
        {

            CompositionTarget.Rendering -= OnCompositionTargetRendering;

            Uninitialize();
            HwndInitialized = false;

            Unloaded -= OnUnloaded;

            Dispose();
        }

        private void OnCompositionTargetRendering(object sender, EventArgs eventArgs)
        {
            D3DDLL.RenderFrame();
        }

        protected void Initialize()
        {
            D3DDLL.InitD3D(Hwnd, 320, 240);
        }
        protected void Uninitialize() { }
        protected void Resized() { }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            var wndClass = new NativeMethods.WndClassEx();
            wndClass.cbSize = (uint)Marshal.SizeOf(wndClass);
            wndClass.hInstance = NativeMethods.GetModuleHandle(null);
            wndClass.lpfnWndProc = NativeMethods.DefaultWindowProc;
            wndClass.lpszClassName = WindowClass;
            wndClass.hCursor = NativeMethods.LoadCursor(IntPtr.Zero, NativeMethods.IDC_ARROW);
            NativeMethods.RegisterClassEx(ref wndClass);

            Hwnd = NativeMethods.CreateWindowEx(
                0, WindowClass, "", NativeMethods.WS_CHILD | NativeMethods.WS_VISIBLE,
                0, 0, (int)Width, (int)Height, hwndParent.Handle, IntPtr.Zero, IntPtr.Zero, 0);

            return new HandleRef(this, Hwnd);
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            NativeMethods.DestroyWindow(hwnd.Handle);
            Hwnd = IntPtr.Zero;
        }

        protected override void OnRenderSizeChanged(SizeChangedInfo sizeInfo)
        {
            UpdateWindowPos();

            base.OnRenderSizeChanged(sizeInfo);

            if (HwndInitialized)
                Resized();
        }

        protected override IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            switch (msg)
            {
                case NativeMethods.WM_LBUTTONDOWN:
                    RaiseMouseEvent(MouseButton.Left, Mouse.MouseDownEvent);
                    break;

                case NativeMethods.WM_LBUTTONUP:
                    RaiseMouseEvent(MouseButton.Left, Mouse.MouseUpEvent);
                    break;

                case NativeMethods.WM_RBUTTONDOWN:
                    RaiseMouseEvent(MouseButton.Right, Mouse.MouseDownEvent);
                    break;

                case NativeMethods.WM_RBUTTONUP:
                    RaiseMouseEvent(MouseButton.Right, Mouse.MouseUpEvent);
                    break;
            }

            return base.WndProc(hwnd, msg, wParam, lParam, ref handled);
        }

        private void RaiseMouseEvent(MouseButton button, RoutedEvent @event)
        {
            RaiseEvent(new MouseButtonEventArgs(Mouse.PrimaryDevice, 0, button)
            {
                RoutedEvent = @event,
                Source = this,
            });
        }

        protected override void Dispose(bool disposing)
        {
            //throw new NotImplementedException();
        }
    }

    internal class NativeMethods
    {
        // ReSharper disable InconsistentNaming
        public const int WS_CHILD = 0x40000000;
        public const int WS_VISIBLE = 0x10000000;

        public const int WM_LBUTTONDOWN = 0x0201;
        public const int WM_LBUTTONUP = 0x0202;
        public const int WM_RBUTTONDOWN = 0x0204;
        public const int WM_RBUTTONUP = 0x0205;

        public const int IDC_ARROW = 32512;

        [StructLayout(LayoutKind.Sequential)]
        public struct WndClassEx
        {
            public uint cbSize;
            public uint style;
            [MarshalAs(UnmanagedType.FunctionPtr)]
            public WndProc lpfnWndProc;
            public int cbClsExtra;
            public int cbWndExtra;
            public IntPtr hInstance;
            public IntPtr hIcon;
            public IntPtr hCursor;
            public IntPtr hbrBackground;
            public string lpszMenuName;
            public string lpszClassName;
            public IntPtr hIconSm;
        }

        [DllImport("user32.dll")]
        public static extern IntPtr DefWindowProc(IntPtr hWnd, uint uMsg, IntPtr wParam, IntPtr lParam);

        public delegate IntPtr WndProc(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam);

        public static readonly WndProc DefaultWindowProc = DefWindowProc;

        [DllImport("user32.dll", EntryPoint = "CreateWindowEx", CharSet = CharSet.Auto)]
        public static extern IntPtr CreateWindowEx(
            int exStyle,
            string className,
            string windowName,
            int style,
            int x, int y,
            int width, int height,
            IntPtr hwndParent,
            IntPtr hMenu,
            IntPtr hInstance,
            [MarshalAs(UnmanagedType.AsAny)] object pvParam);

        [DllImport("user32.dll", EntryPoint = "DestroyWindow", CharSet = CharSet.Auto)]
        public static extern bool DestroyWindow(IntPtr hwnd);

        [DllImport("kernel32.dll")]
        public static extern IntPtr GetModuleHandle(string module);

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.U2)]
        public static extern short RegisterClassEx([In] ref WndClassEx lpwcx);

        [DllImport("user32.dll")]
        public static extern IntPtr LoadCursor(IntPtr hInstance, int lpCursorName);
        // ReSharper restore InconsistentNaming
    }
}
