#include "platform/platform.h"

#if CVUL_PLAT_WIN

#include <Windows.h>
#include <windowsx.h>
#include <stdlib.h>

#include "core/logging.h"

static f64 clock_freq;
static LARGE_INTEGER start_time;

typedef struct internal_state
{
    HINSTANCE h_instance;
    HWND hwnd;
} internal_state;

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);

b8 platform_startup(platform_state* p_state, const char* app_name,
                    i32 x, i32 y, i32 width, i32 height)
{
    p_state->internal_state = malloc(sizeof(internal_state));
    internal_state* state = (internal_state*)p_state->internal_state;

    state->h_instance = GetModuleHandleA(0);

    HICON icon = LoadIcon(state->h_instance, IDI_APPLICATION);

    // what if we. had classes.
    WNDCLASSA wc;
    memset(&wc, 0, sizeof(wc));
    wc.style = 0x008;
    wc.lpfnWndProc = win32_process_message;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = state->h_instance;
    wc.hIcon = icon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszClassName = "CVUL_WINDOW_CLASS";

    if (!RegisterClassA(&wc))
    {
        MessageBoxA(0, "Windows registration has failed", "ERROR", MB_ICONEXCLAMATION | MB_OK);
        return FALSE;
    }

    u32 client_x = x, client_y = y;
    u32 client_width = width, client_height = height;

    u32 window_x = client_x, window_y = client_y;
    u32 window_width = client_width, window_height = client_height;

    u32 window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
    u32 window_ex_style = WS_EX_APPWINDOW;

    window_style |= WS_MAXIMIZEBOX;
    window_style |= WS_MINIMIZEBOX;
    window_style |= WS_THICKFRAME;

    RECT border_rect = {0, 0, 0, 0};
    AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);

    window_x += border_rect.left;
    window_y += border_rect.top;

    window_width += border_rect.right - border_rect.left;
    window_height += border_rect.bottom - border_rect.top;

    HWND handle = CreateWindowExA(
        window_ex_style, "CVUL_WINDOW_CLASS", app_name,
        window_style, window_x, window_y,
        window_width, window_height, 0, 0,
        state->h_instance, 0);
    
    if (handle == 0)
    {
        MessageBoxA(NULL, "Window creation has failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        CVUL_FATAL("Window creation has failed!");
        return FALSE;
    }
    else
    {
        state->hwnd = handle;
    }

    // TODO: don't hardcode these values
    // if the window doesn't need input, disable first flag
    // if minimized at init, SW_MINIMIZE : SW_SHOWMINNOACTIVE
    // if maximized at init, SW_SHOWMAXIMIZED : SW_MAXIMIZE
    b32 activate = 1;
    i32 show_window_command_flags = activate ? SW_SHOW : SW_SHOWNOACTIVATE;
    ShowWindow(state->hwnd, show_window_command_flags);

    // set up start time
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    clock_freq = 1.0 / (f64)frequency.QuadPart;
    QueryPerformanceCounter(&start_time);


    return TRUE;
}

void platform_shutdown(platform_state* p_state)
{
    internal_state *state = (internal_state*)p_state->internal_state;

    if (state->hwnd)
    {
        DestroyWindow(state->hwnd);
        state->hwnd = 0;
    }
}

b8 platform_pump_messages(platform_state* p_state)
{
    MSG message;
    while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }

    return TRUE;
}

void *platform_alloc(u64 size, b8 aligned) 
{
    return malloc(size);
}

void platform_free(void *block, b8 aligned) 
{
    free(block);
}

void *platform_zero_memory(void *block, u64 size) 
{
    return memset(block, 0, size);
}

void *platform_copy_memory(void *dest, const void *source, u64 size) 
{
    return memcpy(dest, source, size);
}

void *platform_set_memory(void *dest, i32 value, u64 size) 
{
    return memset(dest, value, size);
}

void platform_console_write(const char *message, u8 color) 
{
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // see core/logging.h for info
    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[color]);

    OutputDebugStringA(message);

    u64 length = strlen(message);
    LPDWORD number_written = 0;
    WriteConsoleA(console_handle, message, (DWORD)length, number_written, 0);
    SetConsoleTextAttribute(console_handle, levels[5]);
}

void platform_console_write_err(const char *message, u8 color) 
{
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
    // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[color]);
    OutputDebugStringA(message);
    u64 length = strlen(message);
    LPDWORD number_written = 0;
    WriteConsoleA(console_handle, message, (DWORD)length, number_written, 0);
    SetConsoleTextAttribute(console_handle, levels[5]);
}

f64 platform_get_abstime()
{
    LARGE_INTEGER current_time;
    QueryPerformanceCounter(&current_time);
    return (f64)current_time.QuadPart * clock_freq;
}

void platform_sleep(u64 ms)
{
    Sleep(ms);
}

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
    switch (msg) 
    {
        case WM_ERASEBKGND:
            // The app will delete the background.
            return 1;
        case WM_CLOSE:
            // TODO: Event to close the application
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_SIZE:
        {
            //RECT r;
            //GetClientRect(hwnd, &r);
            //u32 width = r.right - r.left;
            //u32 height = r.bottom - r.top;

            // TODO: Event to resize window
        } break;

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            // TODO: User input
            // b8 keypress = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
        } break;

        case WM_MOUSEMOVE:
        {
            // TODO: Mouse input
            //i32 x_pos = GET_X_LPARAM(l_param);
            //i32 y_pos = GET_Y_LPARAM(l_param);
        } break;

        case WM_MOUSEWHEEL:
        {
        //     TODO: mouse wheel input
        //     i32 z_delta = GET_WHEEL_DELTA_WPARAM(w_param);
        //     if (z_delta != 0)
        //     {
        //         // OS independent delta value
        //         z_delta = (z_delta < 0) ? -1 : 1;
        //     }
        } break;

        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP: 
        {
            //b8 pressed = msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN;
            // TODO: mouse button input.
        } break;
    }

    return DefWindowProcA(hwnd, msg, w_param, l_param);
}

#endif