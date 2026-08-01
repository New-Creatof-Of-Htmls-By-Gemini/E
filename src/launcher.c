/*
 * Generic Jackbox launcher.
 *
 * At build time, define TARGET_EXE to the filename of the real game
 * executable that sits in the same folder as this launcher, e.g.:
 *
 *   gcc -mwindows -DTARGET_EXE="\"Drawful 2.exe\"" launcher.c -o "Drawful 2 (Custom Server).exe" -lshell32
 *
 * The launcher finds its own directory, builds the full path to
 * TARGET_EXE next to it, and starts it with the -jbg.config argument
 * pointing at the custom ecast server.
 */

#include <windows.h>
#include <shellapi.h>
#include <string.h>
#include <stdio.h>

#ifndef TARGET_EXE
#define TARGET_EXE "game.exe"
#endif

#ifndef SERVER_ARG
#define SERVER_ARG "-jbg.config serverUrl=https://jb-ecast.klucva.ru"
#endif

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd) {
    char selfPath[MAX_PATH];
    char targetPath[MAX_PATH];
    char errMsg[MAX_PATH + 256];

    (void)hInst; (void)hPrevInst; (void)lpCmdLine; (void)nShowCmd;

    if (GetModuleFileNameA(NULL, selfPath, MAX_PATH) == 0) {
        MessageBoxA(NULL, "Could not determine launcher location.", "Launch failed", MB_OK | MB_ICONERROR);
        return 1;
    }

    char *lastSlash = strrchr(selfPath, '\\');
    if (lastSlash) {
        *(lastSlash + 1) = '\0';
    } else {
        selfPath[0] = '\0';
    }

    snprintf(targetPath, sizeof(targetPath), "%s%s", selfPath, TARGET_EXE);

    HINSTANCE result = ShellExecuteA(NULL, "open", targetPath, SERVER_ARG, selfPath, SW_SHOWNORMAL);

    if ((INT_PTR)result <= 32) {
        snprintf(errMsg, sizeof(errMsg),
                 "Could not start:\n%s\n\nMake sure it's in the same folder as this launcher.",
                 targetPath);
        MessageBoxA(NULL, errMsg, "Launch failed", MB_OK | MB_ICONERROR);
        return 1;
    }

    return 0;
}
