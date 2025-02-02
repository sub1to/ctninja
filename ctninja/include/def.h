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






// ntdll functions
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
    //SYSTEM_INFORMATION_CLASS SystemInformationClass,
    ULONG SystemInformationClass,
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





// Kernel32 functions
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






// ucrtbase functions
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





// kernelbase functions
typedef __time64_t (__cdecl* fp_time64)(
    __time64_t* Time
    );

typedef DWORD (WINAPI *fpGetModuleFileNameExA)(
    HANDLE  hProcess,
    HMODULE hModule,
    LPSTR   lpFilename,
    DWORD   nSize
    );




// msvcrt functions 
typedef int (__cdecl* fpvprintf_s)(
    char const* const _Format,
    va_list           _ArgList
    );

typedef int (__cdecl* fpvwprintf_s)(
    const wchar_t *format,
    va_list argptr
    );








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
