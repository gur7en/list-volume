#include <stdio.h>
#include <wchar.h>

#include <fileapi.h>
#include <windows.h>

enum error_codes {
    success,
    get_drives_list_fail,
    low_memory
};

int main()
{
    DWORD buf_size;
    buf_size = GetLogicalDriveStringsW(0, 0);
    if (buf_size == 0)
        return get_drives_list_fail;

    buf_size *= sizeof(WCHAR);

    LPWSTR buffer = malloc(buf_size + sizeof(WCHAR));
    if (buffer == NULL)
        return low_memory;

    if (0 == GetLogicalDriveStringsW(buf_size, buffer))
        return get_drives_list_fail;

    LPWSTR curdrv = buffer;
    while (*curdrv) {
        if (GetVolumeInformationW(curdrv, 0, 0, 0, 0, 0, 0, 0))
            curdrv += wprintf(L"%s\n", curdrv);
        else
            curdrv += wcslen(curdrv) + 1;
    };

    return success;
}