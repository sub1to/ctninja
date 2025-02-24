/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
*/

#ifndef _CTNINJA_DEF_H_
#define _CTNINJA_DEF_H_

#include <Windows.h>
#include <winternl.h>



// Extended/undocumented structs
typedef struct _PEB_LDR_DATA_EX {
    uint32_t		Length;
	uint8_t			Initialized;
	void*			SsHandle;
	LIST_ENTRY		InLoadOrderModuleList;
	LIST_ENTRY		InMemoryOrderModuleList;
	LIST_ENTRY		InInitializationOrderModuleList;
} PEB_LDR_DATA_EX, *PPEB_LDR_DATA_EX;

typedef struct _LDR_MODULE {
    LIST_ENTRY		InLoadOrderModuleList;
	LIST_ENTRY		InMemoryOrderModuleList;
	LIST_ENTRY		InInitializationOrderModuleList;
	void*			BaseAddress;
	void*			EntryPoint;
	uint32_t		SizeOfImage;
	UNICODE_STRING	FullDllName;
	UNICODE_STRING	BaseDllName;
	uint32_t		Flags;
	int16_t			LoadCount;
	int16_t			TlsIndex;
	LIST_ENTRY		HashTableEntry;
	int32_t			TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

#ifndef PROCESSENTRY32
typedef struct tagPROCESSENTRY32
{
    DWORD   dwSize;
    DWORD   cntUsage;
    DWORD   th32ProcessID;          // this process
    ULONG_PTR th32DefaultHeapID;
    DWORD   th32ModuleID;           // associated exe
    DWORD   cntThreads;
    DWORD   th32ParentProcessID;    // this process's parent process
    LONG    pcPriClassBase;         // Base priority of process's threads
    DWORD   dwFlags;
    CHAR    szExeFile[MAX_PATH];    // Path
} PROCESSENTRY32, *LPPROCESSENTRY32;
#endif





//
// START ntdll.dll
//
typedef NTSTATUS (NTAPI *fpNtWow64ReadVirtualMemory64)(
     HANDLE ProcessHandle,
     PVOID64 BaseAddress,
     PVOID Buffer,
     ULONG64 Size,
     PULONG64 NumberOfBytesRead
     );

typedef NTSTATUS (NTAPI *fpNtWow64QueryInformationProcess64)(
     HANDLE ProcessHandle,
     ULONG ProcessInformationClass,
     PVOID ProcessInformation,
     ULONG ProcessInformationLength,
     PULONG ReturnLength
     );

typedef NTSTATUS (NTAPI *fpNtQeurySystemInformation)(
     ULONG SystemInformationClass,  // SYSTEM_INFORMATION_CLASS / SYSTEM_INFORMATION_CLASS_EXTENDED
     PVOID SystemInformation,
     ULONG SystemInformationLength,
     PULONG ReturnLength
     );

typedef NTSTATUS (NTAPI *fpNtReadVirtualMemory)(
     HANDLE ProcessHandle, 
     PVOID BaseAddress, 
     PVOID Buffer, 
     SIZE_T NumberOfBytesToRead, 
     PSIZE_T NumberOfBytesRead
     );

typedef int (__cdecl* fpvsprintf_s)(
     char *buffer,
     size_t numberOfElements,
     const char *format,
     va_list argptr
     );

typedef int (__cdecl* fpvswprintf_s)(
     wchar_t *buffer,
     size_t numberOfElements,
     const wchar_t *format,
     va_list argptr
     );

typedef int (__cdecl* fp_vsnprintf)(
     char *buffer,
     size_t count,
     const char *format,
     va_list argptr
     );

typedef size_t (*fpstrlen)(
     const char* str
     );

typedef int (__cdecl* fpmemcmp)(
    const void *Buf1,
    const void *Buf2,
    size_t      Size
    );

typedef LRESULT (WINAPI* fpNtdllDefWindowProc_W)(
    HWND   hWnd,
    UINT   Msg,
    WPARAM wParam,
    LPARAM lParam
    );

typedef void* (__cdecl* fpmemset)(
    void*  _Dst,
    int    _Val,
    size_t _Size
    );
//
// END ntdll.dll
//




//
// START kernel32.dll
//
typedef HMODULE (WINAPI* fpLoadLibraryA)(
    LPCSTR lpLibFileName
    );

typedef HANDLE  (WINAPI*  fpCreateThread)(
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    SIZE_T dwStackSize,
    LPTHREAD_START_ROUTINE lpStartAddress,
    LPVOID lpParameter,
    DWORD dwCreationFlags,
    LPDWORD lpThreadId
    );

typedef BOOL (WINAPI* fpVirtualProtect)(
    LPVOID lpAddress,
    SIZE_T dwSize,
    DWORD flNewProtect,
    PDWORD lpflOldProtect
    );

typedef DWORD (WINAPI* fpWaitForSingleObject)(
    HANDLE hHandle,
    DWORD dwMilliseconds
    );

typedef BOOL (WINAPI* fpCloseHandle)(
    HANDLE hObject
    );

typedef VOID (WINAPI* fpSleep)(
    DWORD dwMilliseconds
    );

typedef HANDLE (WINAPI* fpCreateFileA)(
    LPCSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    );

typedef DWORD (WINAPI* fpGetLastError)(
    VOID
    );

typedef BOOL (WINAPI* fpWaitNamedPipeA)(
    LPCSTR lpNamedPipeName,
    DWORD nTimeOut
    );

typedef BOOL (WINAPI* fpGetOverlappedResult)(
    HANDLE hFile,
    LPOVERLAPPED lpOverlapped,
    LPDWORD lpNumberOfBytesTransferred,
    BOOL bWait
    );

typedef HANDLE (WINAPI* fpCreateEventA)(
    LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL bManualReset,
    BOOL bInitialState,
    LPCSTR lpName
    );

typedef BOOL (WINAPI* fpReadFile)(
    HANDLE hFile,
    LPVOID lpBuffer,
    DWORD nNumberOfBytesToRead,
    LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
    );

typedef int (__cdecl* fpsprintf)(
    char* buffer,
    const char* format,
    ...
    );

typedef errno_t (__cdecl* fpstrcpy_s)(
    char*       _Destination,
    rsize_t     _SizeInBytes,
    char const* _Source
    );

typedef BOOL (WINAPI* fpCreateProcessA)(
    LPCSTR                lpApplicationName,
    LPSTR                 lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL                  bInheritHandles,
    DWORD                 dwCreationFlags,
    LPVOID                lpEnvironment,
    LPCSTR                lpCurrentDirectory,
    LPSTARTUPINFOA        lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
    );

typedef HANDLE (WINAPI* fpCreateToolhelp32Snapshot)(
    DWORD dwFlags,
    DWORD th32ProcessID
    );

typedef BOOL (WINAPI* fpProcess32First)(
    HANDLE           hSnapshot,
    LPPROCESSENTRY32 lppe
    );

typedef BOOL (WINAPI* fpProcess32Next)(
    HANDLE           hSnapshot,
    LPPROCESSENTRY32 lppe
    );

typedef HANDLE (WINAPI* fpOpenProcess)(
    DWORD dwDesiredAccess,
    BOOL  bInheritHandle,
    DWORD dwProcessId
    );

typedef HANDLE (__stdcall* fpFindFirstFileA)(
  LPCSTR             lpFileName,
  LPWIN32_FIND_DATAA lpFindFileData
);

typedef BOOL (__stdcall* fpFindNextFileA)(
  HANDLE             hFindFile,
  LPWIN32_FIND_DATAA lpFindFileData
);

typedef BOOL (__stdcall* fpFindClose)(
  HANDLE hFindFile
);

typedef DWORD (WINAPI* fpGetModuleFileNameA)(
  HMODULE hModule,
  LPSTR lpFilename,
  DWORD nSize
);

typedef BOOL (WINAPI* fpDeviceIoControl)(
    HANDLE       hDevice,
    DWORD        dwIoControlCode,
    LPVOID       lpInBuffer,
    DWORD        nInBufferSize,
    LPVOID       lpOutBuffer,
    DWORD        nOutBufferSize,
    LPDWORD      lpBytesReturned,
    LPOVERLAPPED lpOverlapped
    );

typedef HMODULE (WINAPI* fpGetModuleHandleA)(
    LPCSTR lpModuleName
    );

typedef int (WINAPI* fpGetLocaleInfoA)(
    LCID  Locale,
    LCTYPE LCType,
    LPSTR lpLCData,
    int   cchData
    );

typedef BOOL (WINAPI* fpQueryPerformanceCounter)(
    LARGE_INTEGER* lpPerformanceCount
    );

typedef BOOL (WINAPI* fpQueryPerformanceFrequency)(
    LARGE_INTEGER* lpFrequency
    );

typedef BOOL (WINAPI* fpFreeLibrary)(
    HMODULE hLibModule
    );

typedef int (WINAPI* fpMultiByteToWideChar)(
    UINT   CodePage,
    DWORD  dwFlags,
    LPCCH  lpMultiByteStr,
    int    cbMultiByte,
    LPWSTR lpWideCharStr,
    int    cchWideChar
    );

typedef int (WINAPI* fpWideCharToMultiByte)(
    UINT   CodePage,
    DWORD  dwFlags,
    LPCWCH lpWideCharStr,
    int    cchWideChar,
    LPSTR  lpMultiByteStr,
    int    cbMultiByte,
    LPCCH  lpDefaultChar,
    LPBOOL lpUsedDefaultChar
    );
//
// END kernel32.dll
//




//
// START ucrtbase.dll
//
typedef FILE* (__cdecl* fp_fsopen)(
    char const* _FileName,
    char const* _Mode,
    int         _ShFlag
    );

typedef size_t (__cdecl* fpfwrite)(
    void const* _Buffer,
    size_t      _ElementSize,
    size_t      _ElementCount,
    FILE*       _Stream
    );

typedef int (__cdecl* fpfflush)(
    FILE* _Stream
    );

typedef int (__cdecl* fpfclose)(
    FILE* _Stream
    );

typedef size_t (__cdecl* fpstrftime)(
    char *Buf,
    size_t SizeInBytes,
    const char *Format,
    const struct tm *Tm
    );

typedef errno_t (__cdecl* fp_localtime64_s)(
    struct tm *Tm,
    const __time64_t *Time
    );

typedef FILE* (__cdecl* fpfopen)(
    const char *filename,
    const char *mode
    );

typedef size_t (__cdecl* fpfwrite)(
    const void *buffer,
    size_t size,
    size_t count,
    FILE *stream
    );

typedef int (__cdecl* fpfclose)(
    FILE *stream
    );

typedef size_t (__cdecl* fpfread)(
    void *buffer,
    size_t size,
    size_t count,
    FILE *stream
    );

typedef int (__cdecl* fpfseek)(
    FILE *stream,
    long offset,
    int origin
    );

typedef int (__cdecl* fp_fseeki64)(
    FILE *stream,
    __int64 offset,
    int origin
    );

typedef long (__cdecl* fpftell)(
    FILE *stream
    );

typedef __int64 (__cdecl* fp_ftelli64)(
    FILE *stream
    );

typedef void (__cdecl* fprewind)(
    FILE *stream
    );

typedef int (__cdecl* fpremove)(
    const char* path
    );

typedef float (__cdecl* fpsqrtf)(
    float _Xx
    );

typedef void (__cdecl* fpsrand)(
    unsigned int _Seed
    );

typedef int (__cdecl* fprand)(
    void
    );

typedef __int64 (__fastcall* fp__stdio_common_vsprintf_s)(
    __int64 flags,
    char* dest,
    size_t destSize,
    const char* format,
    _locale_t locale,
    va_list args
    );

typedef __int64 (__fastcall* fp__stdio_common_vswprintf_s)(
    __int64 flags,
    wchar_t* dest,
    size_t destSizeInWords,
    const wchar_t* format,
    _locale_t locale,
    va_list args
    );
//
// END ucrtbase.dll
//



//
// START kernelbase.dll
//
typedef __time64_t (__cdecl* fp_time64)(
    __time64_t* Time
    );

typedef DWORD (WINAPI *fpGetModuleFileNameExA)(
    HANDLE  hProcess,
    HMODULE hModule,
    LPSTR   lpFilename,
    DWORD   nSize
    );
//
// END kernelbase.dll
//




//
// START msvcrt.dll
//
typedef int (__cdecl* fpvprintf_s)(
    char const* const _Format,
    va_list           _ArgList
    );

typedef int (__cdecl* fpvwprintf_s)(
    const wchar_t *format,
    va_list argptr
    );
//
// END msvcrt.dll
//




//
// START user32.dll
//
typedef BOOL (WINAPI* fpGetCursorPos)(
    LPPOINT lpPoint
    );

typedef BOOL (WINAPI* fpGetPhysicalCursorPos)(
    LPPOINT lpPoint
    );

typedef HDC (WINAPI* fpGetDC)(
    HWND hWnd
    );

typedef int (WINAPI* fpReleaseDC)(
    HWND hWnd,
    HDC hDC
    );

typedef void (WINAPI* fpPostQuitMessage)(
    int nExitCode
    );

typedef ATOM (WINAPI* fpRegisterClassExA)(
    const WNDCLASSEXA *lpwcx
    );

typedef ATOM (WINAPI* fpRegisterClassExW)(
    const WNDCLASSEXW *lpwcx
    );

typedef BOOL (WINAPI* fpUnregisterClassA)(
    LPCSTR    lpClassName,
    HINSTANCE hInstance
    );

typedef BOOL (WINAPI* fpUnregisterClassW)(
    LPCWSTR   lpClassName,
    HINSTANCE hInstance
    );

typedef HWND (WINAPI* fpCreateWindowExA)(
    DWORD      dwExStyle,
    LPCSTR     lpClassName,
    LPCSTR     lpWindowName,
    DWORD      dwStyle,
    int        X,
    int        Y,
    int        nWidth,
    int        nHeight,
    HWND       hWndParent,
    HMENU      hMenu,
    HINSTANCE  hInstance,
    LPVOID     lpParam
    );

typedef HWND (WINAPI* fpCreateWindowExW)(
    DWORD      dwExStyle,
    LPCWSTR    lpClassName,
    LPCWSTR    lpWindowName,
    DWORD      dwStyle,
    int        X,
    int        Y,
    int        nWidth,
    int        nHeight,
    HWND       hWndParent,
    HMENU      hMenu,
    HINSTANCE  hInstance,
    LPVOID     lpParam
    );

typedef BOOL (WINAPI* fpSetWindowDisplayAffinity)(
    HWND  hWnd,
    DWORD dwAffinity
    );

typedef LONG (WINAPI* fpSetWindowLongA)(
    HWND hWnd,
    int  nIndex,
    LONG dwNewLong
    );

typedef LONG (WINAPI* fpSetWindowLongW)(
    HWND hWnd,
    int  nIndex,
    LONG dwNewLong
    );

typedef BOOL (WINAPI* fpShowWindow)(
    HWND hWnd,
    int  nCmdShow
    );

typedef BOOL (WINAPI* fpUpdateWindow)(
    HWND hWnd
    );

typedef BOOL (WINAPI* fpDestroyWindow)(
    HWND hWnd
    );

typedef SHORT (WINAPI* fpGetAsyncKeyState)(
    int vKey
    );

typedef HWND (WINAPI* fpSetFocus)(
    HWND hWnd
    );

typedef BOOL (WINAPI* fpSetForegroundWindow)(
    HWND hWnd
    );

typedef HWND (WINAPI* fpSetActiveWindow)(
    HWND hWnd
    );

typedef HWND (WINAPI* fpFindWindowA)(
    LPCSTR lpClassName,
    LPCSTR lpWindowName
    );

typedef HWND (WINAPI* fpFindWindowW)(
    LPCWSTR lpClassName,
    LPCWSTR lpWindowName
    );

typedef BOOL (WINAPI* fpPeekMessageA)(
    LPMSG lpMsg,
    HWND  hWnd,
    UINT  wMsgFilterMin,
    UINT  wMsgFilterMax,
    UINT  wRemoveMsg
    );

typedef BOOL (WINAPI* fpPeekMessageW)(
    LPMSG lpMsg,
    HWND  hWnd,
    UINT  wMsgFilterMin,
    UINT  wMsgFilterMax,
    UINT  wRemoveMsg
    );

typedef BOOL (WINAPI* fpTranslateMessage)(
    const MSG *lpMsg
    );

typedef LRESULT (WINAPI* fpDispatchMessageA)(
    const MSG *lpMsg
    );

typedef LRESULT (WINAPI* fpDispatchMessageW)(
    const MSG *lpMsg
    );

typedef HKL (WINAPI* fpGetKeyboardLayout)(
    DWORD idThread
    );

typedef SHORT (WINAPI* fpVkKeyScanExW)(
    WCHAR ch,
    HKL   dwhkl
    );

typedef UINT (WINAPI* fpMapVirtualKeyW)(
    UINT uCode,
    UINT uMapType
    );

typedef UINT (WINAPI* fpMapVirtualKeyExW)(
    UINT uCode,
    UINT uMapType,
    HKL  dwhkl
    );

typedef int (WINAPI* fpGetSystemMetrics)(
    int nIndex
    );

typedef HCURSOR (WINAPI* fpSetCursor)(
    HCURSOR hCursor
    );

typedef HCURSOR (WINAPI* fpGetCursor)(
    void
    );

typedef HCURSOR (WINAPI* fpLoadCursorA)(
    HINSTANCE hInstance,
    LPCSTR    lpCursorName
    );

typedef HCURSOR (WINAPI* fpLoadCursorW)(
    HINSTANCE hInstance,
    LPCWSTR   lpCursorName
    );

typedef SHORT (WINAPI* fpGetKeyState)(
    int nVirtKey
    );

typedef BOOL (WINAPI* fpGetKeyboardState)(
    PBYTE lpKeyState
    );

typedef BOOL (WINAPI* fpSetKeyboardState)(
    LPBYTE lpKeyState
    );

typedef HWND (WINAPI* fpGetForegroundWindow)(
    void
    );

typedef BOOL (WINAPI* fpClientToScreen)(
    HWND    hWnd,
    LPPOINT lpPoint
    );

typedef BOOL (WINAPI* fpScreenToClient)(
    HWND    hWnd,
    LPPOINT lpPoint
    );

typedef BOOL (WINAPI* fpSetCursorPos)(
    int X,
    int Y
    );

typedef BOOL (WINAPI* fpSetPhysicalCursorPos)(
    int X,
    int Y
    );

typedef BOOL (WINAPI* fpGetClientRect)(
    HWND  hWnd,
    LPRECT lpRect
    );

typedef BOOL (WINAPI* fpGetWindowRect)(
    HWND  hWnd,
    LPRECT lpRect
    );

typedef BOOL (WINAPI* fpAdjustWindowRect)(
    LPRECT lpRect,
    DWORD  dwStyle,
    BOOL   bMenu
    );

typedef BOOL (WINAPI* fpAdjustWindowRectEx)(
    LPRECT lpRect,
    DWORD  dwStyle,
    BOOL   bMenu,
    DWORD  dwExStyle
    );

typedef LPARAM (WINAPI* fpGetMessageExtraInfo)(
    void
    );

typedef BOOL (WINAPI* fpTrackMouseEvent)(
    LPTRACKMOUSEEVENT lpEventTrack
    );

typedef HWND (WINAPI* fpGetCapture)(
    void
    );

typedef HWND (WINAPI* fpSetCapture)(
    HWND hWnd
    );

typedef BOOL (WINAPI* fpReleaseCapture)(
    void
    );

typedef BOOL (WINAPI* fpIsWindowUnicode)(
    HWND hWnd
    );

typedef BOOL (WINAPI* fpEnableWindow)(
    HWND hWnd,
    BOOL bEnable
    );

typedef BOOL (WINAPI* fpIsWindowEnabled)(
    HWND hWnd
    );

typedef BOOL (WINAPI* fpSetProcessDPIAware)(
    void
    );

typedef HMONITOR (WINAPI* fpMonitorFromWindow)(
    HWND  hwnd,
    DWORD dwFlags
    );
//
// END user32.dll
//




//
// START Gdi32.dll
//
typedef HBITMAP (WINAPI* fpCreateBitmap)(
    int        nWidth,
    int        nHeight,
    UINT       nPlanes,
    UINT       nBitCount,
    const VOID *lpBits
    );

typedef HBITMAP (WINAPI* fpCreateBitmapIndirect)(
    const BITMAP *pbm
    );

typedef HBRUSH (WINAPI* fpCreateBrushIndirect)(
    const LOGBRUSH *plbrush
    );

typedef HBITMAP (WINAPI* fpCreateCompatibleBitmap)(
    HDC hdc,
    int cx,
    int cy
    );

typedef HBITMAP (WINAPI* fpCreateDiscardableBitmap)(
    HDC hdc,
    int cx,
    int cy
    );

typedef HDC (WINAPI* fpCreateCompatibleDC)(
    HDC hdc
    );

typedef HGDIOBJ (WINAPI* fpSelectObject)(
    HDC     hdc,
    HGDIOBJ h
    );

typedef BOOL (WINAPI* fpBitBlt)(
    HDC hdc,
    int x,
    int y,
    int cx,
    int cy,
    HDC hdcSrc,
    int x1,
    int y1,
    DWORD rop
    );

typedef int (WINAPI* fpGetDIBits)(
    HDC hdc,
    HBITMAP hbm,
    UINT start,
    UINT cLines,
    LPVOID lpvBits,
    LPBITMAPINFO lpbmi,
    UINT usage
    );

typedef BOOL (WINAPI* fpDeleteObject)(
    HGDIOBJ ho
    );

typedef BOOL (WINAPI* fpDeleteDC)(
    HDC hdc
    );

typedef int (WINAPI* fpGetDeviceCaps)(
    HDC hdc,
    int index
    );

typedef HRGN (WINAPI* fpCreateRectRgn)(
    int x1,
    int y1,
    int x2,
    int y2
    );
//
// END Gdi32.dll
//




//
// START Advapi32.dll
//
typedef SC_HANDLE (WINAPI* fpOpenSCManagerA)(
    LPCSTR lpMachineName,
    LPCSTR lpDatabaseName,
    DWORD  dwDesiredAccess
    );

typedef SC_HANDLE (WINAPI* fpOpenSCManagerW)(
    LPCWSTR lpMachineName,
    LPCWSTR lpDatabaseName,
    DWORD   dwDesiredAccess
    );

typedef SC_HANDLE (WINAPI* fpOpenServiceA)(
    SC_HANDLE hSCManager,
    LPCSTR    lpServiceName,
    DWORD     dwDesiredAccess
    );

typedef SC_HANDLE (WINAPI* fpOpenServiceW)(
    SC_HANDLE hSCManager,
    LPCWSTR   lpServiceName,
    DWORD     dwDesiredAccess
    );

typedef BOOL (WINAPI* fpQueryServiceStatusEx)(
    SC_HANDLE      hService,
    SC_STATUS_TYPE InfoLevel,
    LPBYTE         lpBuffer,
    DWORD          cbBufSize,
    LPDWORD        pcbBytesNeeded
    );

typedef BOOL (WINAPI* fpControlService)(
    SC_HANDLE       hService,
    DWORD           dwControl,
    LPSERVICE_STATUS lpServiceStatus
    );

typedef SC_HANDLE (WINAPI* fpCreateServiceA)(
    SC_HANDLE hSCManager,
    LPCSTR    lpServiceName,
    LPCSTR    lpDisplayName,
    DWORD     dwDesiredAccess,
    DWORD     dwServiceType,
    DWORD     dwStartType,
    DWORD     dwErrorControl,
    LPCSTR    lpBinaryPathName,
    LPCSTR    lpLoadOrderGroup,
    LPDWORD   lpdwTagId,
    LPCSTR    lpDependencies,
    LPCSTR    lpServiceStartName,
    LPCSTR    lpPassword
    );

typedef SC_HANDLE (WINAPI* fpCreateServiceW)(
    SC_HANDLE hSCManager,
    LPCWSTR   lpServiceName,
    LPCWSTR   lpDisplayName,
    DWORD     dwDesiredAccess,
    DWORD     dwServiceType,
    DWORD     dwStartType,
    DWORD     dwErrorControl,
    LPCWSTR   lpBinaryPathName,
    LPCWSTR   lpLoadOrderGroup,
    LPDWORD   lpdwTagId,
    LPCWSTR   lpDependencies,
    LPCWSTR   lpServiceStartName,
    LPCWSTR   lpPassword
    );

typedef BOOL (WINAPI* fpDeleteService)(
    SC_HANDLE hService
    );

typedef BOOL (WINAPI* fpCloseServiceHandle)(
    SC_HANDLE hSCObject
    );

typedef BOOL (WINAPI* fpChangeServiceConfigA)(
    SC_HANDLE hService,
    DWORD     dwServiceType,
    DWORD     dwStartType,
    DWORD     dwErrorControl,
    LPCSTR    lpBinaryPathName,
    LPCSTR    lpLoadOrderGroup,
    LPDWORD   lpdwTagId,
    LPCSTR    lpDependencies,
    LPCSTR    lpServiceStartName,
    LPCSTR    lpPassword,
    LPCSTR    lpDisplayName
    );

typedef BOOL (WINAPI* fpChangeServiceConfigW)(
    SC_HANDLE hService,
    DWORD     dwServiceType,
    DWORD     dwStartType,
    DWORD     dwErrorControl,
    LPCWSTR   lpBinaryPathName,
    LPCWSTR   lpLoadOrderGroup,
    LPDWORD   lpdwTagId,
    LPCWSTR   lpDependencies,
    LPCWSTR   lpServiceStartName,
    LPCWSTR   lpPassword,
    LPCWSTR   lpDisplayName
    );

typedef BOOL (WINAPI* fpChangeServiceConfig2A)(
    SC_HANDLE hService,
    DWORD     dwInfoLevel,
    LPVOID    lpInfo
    );

typedef BOOL (WINAPI* fpChangeServiceConfig2W)(
    SC_HANDLE hService,
    DWORD     dwInfoLevel,
    LPVOID    lpInfo
    );

typedef BOOL (WINAPI* fpStartServiceA)(
    SC_HANDLE hService,
    DWORD     dwNumServiceArgs,
    LPCSTR    *lpServiceArgVectors
    );

typedef BOOL (WINAPI* fpStartServiceW)(
    SC_HANDLE hService,
    DWORD     dwNumServiceArgs,
    LPCWSTR   *lpServiceArgVectors
    );
//
// END Advapi32.dll
//




//
// START ole32.dll
//
typedef HRESULT (__stdcall* fpCoInitialize)(
    LPVOID lpReserved
    );
//
// END ole32.dll
//




//
// START combase.dll
//
typedef HRESULT (__stdcall* fpCoCreateInstance)(
    REFCLSID  rclsid,
    LPVOID    pUnkOuter,   // LPUNKNOWN
    DWORD     dwClsContext,
    REFIID    riid,
    LPVOID    *ppv
    );
//
// END combase.dll
//


//
// START dwmapi.dll
//
typedef HRESULT (WINAPI* fpDwmExtendFrameIntoClientArea)(
    HWND           hWnd,
    const MARGINS *pMarInset
    );

typedef HRESULT (WINAPI* fpDwmIsCompositionEnabled)(
    BOOL* pfEnabled
    );

typedef HRESULT (WINAPI* fpDwmGetColorizationColor)(
    DWORD* pcrColorization,
    BOOL*  pfOpaqueBlend
    );

typedef HRESULT (WINAPI* fpDwmEnableBlurBehindWindow)(
    HWND hWnd,
    const DWM_BLURBEHIND* pBlurBehind
    );
//
// END dwmapi.dll
//


//
// START d3d9.dll
//
typedef IDirect3D9* (WINAPI* fpDirect3DCreate9)(
    UINT SDKVersion
    );
//
// END d3d9.dll
//




// Extended enums
typedef enum SYSTEM_INFORMATION_CLASS_EXTENDED
{
     //SystemBasicInformation = 0,
     SystemProcessorInformation = 1,
     //SystemPerformanceInformation = 2,
     //SystemTimeOfDayInformation = 3,
     SystemPathInformation = 4,
     //SystemProcessInformation = 5,
     SystemCallCountInformation = 6,
     SystemDeviceInformation = 7,
     //SystemProcessorPerformanceInformation = 8,
     SystemFlagsInformation = 9,
     SystemCallTimeInformation = 10,
     SystemModuleInformation = 11,
     SystemLocksInformation = 12,
     SystemStackTraceInformation = 13,
     SystemPagedPoolInformation = 14,
     SystemNonPagedPoolInformation = 15,
     SystemHandleInformation = 16,
     SystemObjectInformation = 17,
     SystemPageFileInformation = 18,
     SystemVdmInstemulInformation = 19,
     SystemVdmBopInformation = 20,
     SystemFileCacheInformation = 21,
     SystemPoolTagInformation = 22,
     //SystemInterruptInformation = 23,
     SystemDpcBehaviorInformation = 24,
     SystemFullMemoryInformation = 25,
     SystemLoadGdiDriverInformation = 26,
     SystemUnloadGdiDriverInformation = 27,
     SystemTimeAdjustmentInformation = 28,
     SystemSummaryMemoryInformation = 29,
     SystemMirrorMemoryInformation = 30,
     SystemPerformanceTraceInformation = 31,
     SystemObsolete0 = 32,
     //SystemExceptionInformation = 33,
     SystemCrashDumpStateInformation = 34,
     SystemKernelDebuggerInformation = 35,
     SystemContextSwitchInformation = 36,
     //SystemRegistryQuotaInformation = 37,
     SystemExtendServiceTableInformation = 38,
     SystemPrioritySeperation = 39,
     SystemVerifierAddDriverInformation = 40,
     SystemVerifierRemoveDriverInformation = 41,
     SystemProcessorIdleInformation = 42,
     SystemLegacyDriverInformation = 43,
     SystemCurrentTimeZoneInformation = 44,
     //SystemLookasideInformation = 45,
     SystemTimeSlipNotification = 46,
     SystemSessionCreate = 47,
     SystemSessionDetach = 48,
     SystemSessionInformation = 49,
     SystemRangeStartInformation = 50,
     SystemVerifierInformation = 51,
     SystemVerifierThunkExtend = 52,
     SystemSessionProcessInformation = 53,
     SystemLoadGdiDriverInSystemSpace = 54,
     SystemNumaProcessorMap = 55,
     SystemPrefetcherInformation = 56,
     SystemExtendedProcessInformation = 57,
     SystemRecommendedSharedDataAlignment = 58,
     SystemComPlusPackage = 59,
     SystemNumaAvailableMemory = 60,
     SystemProcessorPowerInformation = 61,
     SystemEmulationBasicInformation = 62,
     SystemEmulationProcessorInformation = 63,
     SystemExtendedHandleInformation = 64,
     SystemLostDelayedWriteInformation = 65,
     SystemBigPoolInformation = 66,
     SystemSessionPoolTagInformation = 67,
     SystemSessionMappedViewInformation = 68,
     SystemHotpatchInformation = 69,
     SystemObjectSecurityMode = 70,
     SystemWatchdogTimerHandler = 71,
     SystemWatchdogTimerInformation = 72,
     SystemLogicalProcessorInformation = 73,
     SystemWow64SharedInformationObsolete = 74,
     SystemRegisterFirmwareTableInformationHandler = 75,
     SystemFirmwareTableInformation = 76,
     SystemModuleInformationEx = 77,
     SystemVerifierTriageInformation = 78,
     SystemSuperfetchInformation = 79,
     SystemMemoryListInformation = 80,
     SystemFileCacheInformationEx = 81,
     SystemThreadPriorityClientIdInformation = 82,
     SystemProcessorIdleCycleTimeInformation = 83,
     SystemVerifierCancellationInformation = 84,
     SystemProcessorPowerInformationEx = 85,
     SystemRefTraceInformation = 86,
     SystemSpecialPoolInformation = 87,
     SystemProcessIdInformation = 88,
     SystemErrorPortInformation = 89,
     SystemBootEnvironmentInformation = 90,
     SystemHypervisorInformation = 91,
     SystemVerifierInformationEx = 92,
     SystemTimeZoneInformation = 93,
     SystemImageFileExecutionOptionsInformation = 94,
     SystemCoverageInformation = 95,
     SystemPrefetchPatchInformation = 96,
     SystemVerifierFaultsInformation = 97,
     SystemSystemPartitionInformation = 98,
     SystemSystemDiskInformation = 99,
     SystemProcessorPerformanceDistribution = 100,
     SystemNumaProximityNodeInformation = 101,
     SystemDynamicTimeZoneInformation = 102,
     //SystemCodeIntegrityInformation = 103,
     SystemProcessorMicrocodeUpdateInformation = 104,
     SystemProcessorBrandString = 105,
     SystemVirtualAddressInformation = 106,
     SystemLogicalProcessorAndGroupInformation = 107,
     SystemProcessorCycleTimeInformation = 108,
     SystemStoreInformation = 109,
     SystemRegistryAppendString = 110,
     SystemAitSamplingValue = 111,
     SystemVhdBootInformation = 112,
     SystemCpuQuotaInformation = 113,
     SystemNativeBasicInformation = 114,
     SystemErrorPortTimeouts = 115,
     SystemLowPriorityIoInformation = 116,
     SystemBootEntropyInformation = 117,
     SystemVerifierCountersInformation = 118,
     SystemPagedPoolInformationEx = 119,
     SystemSystemPtesInformationEx = 120,
     SystemNodeDistanceInformation = 121,
     SystemAcpiAuditInformation = 122,
     SystemBasicPerformanceInformation = 123,
     SystemQueryPerformanceCounterInformation = 124,
     SystemSessionBigPoolInformation = 125,
     SystemBootGraphicsInformation = 126,
     SystemScrubPhysicalMemoryInformation = 127,
     SystemBadPageInformation = 128,
     SystemProcessorProfileControlArea = 129,
     SystemCombinePhysicalMemoryInformation = 130,
     SystemEntropyInterruptTimingInformation = 131,
     SystemConsoleInformation = 132,
     SystemPlatformBinaryInformation = 133,
     //SystemPolicyInformation = 134,
     SystemHypervisorProcessorCountInformation = 135,
     SystemDeviceDataInformation = 136,
     SystemDeviceDataEnumerationInformation = 137,
     SystemMemoryTopologyInformation = 138,
     SystemMemoryChannelInformation = 139,
     SystemBootLogoInformation = 140,
     SystemProcessorPerformanceInformationEx = 141,
     SystemSpare0 = 142,
     SystemSecureBootPolicyInformation = 143,
     SystemPageFileInformationEx = 144,
     SystemSecureBootInformation = 145,
     SystemEntropyInterruptTimingRawInformation = 146,
     SystemPortableWorkspaceEfiLauncherInformation = 147,
     SystemFullProcessInformation = 148,
     SystemKernelDebuggerInformationEx = 149,
     SystemBootMetadataInformation = 150,
     SystemSoftRebootInformation = 151,
     SystemElamCertificateInformation = 152,
     SystemOfflineDumpConfigInformation = 153,
     SystemProcessorFeaturesInformation = 154,
     SystemRegistryReconciliationInformation = 155,
     SystemEdidInformation = 156,
     SystemManufacturingInformation = 157,
     SystemEnergyEstimationConfigInformation = 158,
     SystemHypervisorDetailInformation = 159,
     SystemProcessorCycleStatsInformation = 160,
     SystemVmGenerationCountInformation = 161,
     SystemTrustedPlatformModuleInformation = 162,
     SystemKernelDebuggerFlags = 163,
     SystemCodeIntegrityPolicyInformation = 164,
     SystemIsolatedUserModeInformation = 165,
     SystemHardwareSecurityTestInterfaceResultsInformation = 166,
     SystemSingleModuleInformation = 167,
     SystemAllowedCpuSetsInformation = 168,
     SystemVsmProtectionInformation = 169,
     SystemInterruptCpuSetsInformation = 170,
     SystemSecureBootPolicyFullInformation = 171,
     SystemCodeIntegrityPolicyFullInformation = 172,
     SystemAffinitizedInterruptProcessorInformation = 173,
     SystemRootSiloInformation = 174,
     SystemCpuSetInformation = 175,
     SystemCpuSetTagInformation = 176,
     SystemWin32WerStartCallout = 177,
     SystemSecureKernelProfileInformation = 178,
     SystemCodeIntegrityPlatformManifestInformation = 179,
     SystemInterruptSteeringInformation = 180,
     SystemSupportedProcessorArchitectures = 181,
     SystemMemoryUsageInformation = 182,
     SystemCodeIntegrityCertificateInformation = 183,
     SystemPhysicalMemoryInformation = 184,
     SystemControlFlowTransition = 185,
     SystemKernelDebuggingAllowed = 186,
     SystemActivityModerationExeState = 187,
     SystemActivityModerationUserSettings = 188,
     SystemCodeIntegrityPoliciesFullInformation = 189,
     SystemCodeIntegrityUnlockInformation = 190,
     SystemIntegrityQuotaInformation = 191,
     SystemFlushInformation = 192,
     SystemProcessorIdleMaskInformation = 193,
     SystemSecureDumpEncryptionInformation = 194,
     SystemWriteConstraintInformation = 195,
     SystemKernelVaShadowInformation = 196,
     SystemHypervisorSharedPageInformation = 197,
     SystemFirmwareBootPerformanceInformation = 198,
     SystemCodeIntegrityVerificationInformation = 199,
     SystemFirmwarePartitionInformation = 200,
     SystemSpeculationControlInformation = 201,
     SystemDmaGuardPolicyInformation = 202,
     SystemEnclaveLaunchControlInformation = 203,
     SystemWorkloadAllowedCpuSetsInformation = 204,
     SystemCodeIntegrityUnlockModeInformation = 205,
     SystemLeapSecondInformation = 206,
     SystemFlags2Information = 207,
    MaxSystemInfoClass = 208,
} FULL_SYSTEM_INFORMATION_CLASS;

#endif
