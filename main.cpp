﻿// Detect memory leaks (for Debug and MSVC)
#if defined(_MSC_VER) && !defined(NDEBUG) && !defined(_CRTDBG_MAP_ALLOC)
    #define _CRTDBG_MAP_ALLOC
    #include <crtdbg.h>
#endif

#include "sound.h"
#include <cstdio>
#include <cstring>
#include <cassert>
#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#include <strsafe.h>

inline WORD get_lang_id(void)
{
    return PRIMARYLANGID(LANGIDFROMLCID(GetThreadLocale()));
}

// localization
LPCTSTR get_text(INT id)
{
#ifdef JAPAN
    if (get_lang_id() == LANG_JAPANESE) // Japone for Japone
    {
        switch (id)
        {
        case 0: return TEXT("cmd_sing バージョン 0.3 by 片山博文MZ");
        case 1:
            return TEXT("使い方: cmd_sing [オプション] 文字列\n")
                   TEXT("\n")
                   TEXT("オプション:\n")
                   TEXT("  -save_as_wav  出力.wav      WAVファイルとして保存。\n")
                   TEXT("  -help                       このメッセージを表示する。\n")
                   TEXT("  -version                    バージョン情報を表示する。\n")
                   TEXT("\n")
                   TEXT("ReadMe.txt もご覧下さい。");
        case 2: return TEXT("エラー: オプション -save_as_wav は引数が必要です。\n");
        case 3: return TEXT("エラー: 「%ls」は、無効なオプションです。\n");
        case 4: return TEXT("エラー: 引数が多すぎます。\n");
        case 5: return TEXT("エラー: vsk_sound_initが失敗しました。\n");
        case 6: return TEXT("エラー: 演奏する文字列が未指定です。\n");
        case 7: return TEXT("エラー: ファイル「%ls」が開けません。\n");
        }
    }
    else // The others are Let's la English
#endif
    {
        switch (id)
        {
        case 0: return TEXT("cmd_sing version 0.3 by katahiromz");
        case 1:
            return TEXT("Usage: cmd_sing [Options] string\n")
                   TEXT("\n")
                   TEXT("Options:\n")
                   TEXT("  -save_as_wav  output.wav    Save as WAV file.\n")
                   TEXT("  -help                       Display this message.\n")
                   TEXT("  -version                    Display version info.\n")
                   TEXT("\n")
                   TEXT("See also ReadMe.txt.");
        case 2: return TEXT("ERROR: Option -save_as_wav needs an operand.\n");
        case 3: return TEXT("ERROR: '%ls' is an invalid option.\n");
        case 4: return TEXT("ERROR: Too many arguments.\n");
        case 5: return TEXT("ERROR: vsk_sound_init failed.\n");
        case 6: return TEXT("ERROR: No string to play specified.\n");
        case 7: return TEXT("ERROR: Unable to open file '%ls'.\n");
        }
    }

    assert(0);
    return nullptr;
}

void version(void)
{
    _putts(get_text(0));
}

void usage(void)
{
    _putts(get_text(1));
}

struct CMD_SING
{
    std::wstring m_str_to_play;
    std::wstring m_output_file;

    int parse_cmd_line(int argc, wchar_t **argv);
    int run();
};

int CMD_SING::parse_cmd_line(int argc, wchar_t **argv)
{
    if (argc <= 1)
    {
        usage();
        return 1;
    }

    for (int iarg = 1; iarg < argc; ++iarg)
    {
        LPWSTR arg = argv[iarg];

        if (_wcsicmp(arg, L"-help") == 0 || _wcsicmp(arg, L"--help") == 0)
        {
            usage();
            return 1;
        }

        if (_wcsicmp(arg, L"-version") == 0 || _wcsicmp(arg, L"--version") == 0)
        {
            version();
            return 1;
        }

        if (_wcsicmp(arg, L"-save_as_wav") == 0 || _wcsicmp(arg, L"--save_as_wav") == 0)
        {
            if (iarg + 1 < argc)
            {
                m_output_file = argv[++iarg];
                continue;
            }
            else
            {
                _ftprintf(stderr, get_text(2));
                return 1;
            }
        }

        if (arg[0] == '-')
        {
            TCHAR text[256];
            StringCchPrintf(text, _countof(text), get_text(3), arg);
            _ftprintf(stderr, TEXT("%s"), text);
            return 1;
        }

        if (m_str_to_play.empty())
        {
            m_str_to_play = arg;
            continue;
        }

        _ftprintf(stderr, get_text(4));
        return 1;
    }

    if (m_str_to_play.empty())
    {
        _ftprintf(stderr, get_text(6));
        return 1;
    }

    return 0;
}

int wmain(int argc, wchar_t **argv)
{
    CMD_SING sing;
    if (int ret = sing.parse_cmd_line(argc, argv))
        return ret;

    if (!vsk_sound_init())
    {
        _ftprintf(stderr, get_text(5));
        return 1;
    }

    if (sing.m_output_file.size())
    {
        if (!vsk_sound_cmd_sing_save(sing.m_str_to_play.c_str(), sing.m_output_file.c_str()))
        {
            _ftprintf(stderr, get_text(7));
        }
        vsk_sound_exit();
        return 0;
    }

    vsk_sound_cmd_sing(sing.m_str_to_play.c_str());
    vsk_sound_wait(-1);
    vsk_sound_exit();

    return 0;
}

#include <clocale>

int main(void)
{
    // Unicode console output support
    std::setlocale(LC_ALL, "");

    int argc;
    LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    int ret = wmain(argc, argv);
    LocalFree(argv);

    // Detect handle leaks (for Debug)
#if (_WIN32_WINNT >= 0x0500) && !defined(NDEBUG)
    TCHAR szText[MAX_PATH];
    wnsprintf(szText, _countof(szText), TEXT("GDI Objects: %ld, User Objects: %ld\n"),
              GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS),
              GetGuiResources(GetCurrentProcess(), GR_USEROBJECTS));
    OutputDebugString(szText);
#endif

    // Detect memory leaks (for Debug and MSVC)
#if defined(_MSC_VER) && !defined(NDEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    return ret;
}