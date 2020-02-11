#if __INTELLISENSE__
typedef unsigned int __SIZE_TYPE__;
typedef unsigned long __PTRDIFF_TYPE__;
#define __attribute__(q)
#define __builtin_strcmp(a,b) 0
#define __builtin_strlen(a) 0
#define __builtin_memcpy(a,b) 0
#define __builtin_va_list void*
#define __builtin_va_start(a,b)
#define __extension__
#endif

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <stdio.h>
#include <switch.h>
#include <string.h>
#include <dirent.h>
#include <iostream>

void printBanner() {
	printf("SaveTransmitter 0.0.1\n");
	printf("by CFHeadphase\n\n");
}

int main(int argc, char** argv) {
	consoleInit(NULL);
	printBanner();

	// dirent defines
	DIR* dir;
	struct dirent* ent;

	printf("Printing directory listing...\n\n");

	dir = opendir(""); //Open current-working-directory.
	// check if directory exists...
	int folders = 0, files = 0;

	if (dir == NULL) {
		printf("Failed to open dir.\n");
	} else {
		// while ent has remaining directories
		while ((ent = readdir(dir))) {
			printf("name: %s", ent->d_name);

			// type - 4 = folder, 8 = file
			if (ent->d_type == 4) {
				printf(" type: folder\n");
				folders++;
			} else {
				printf(" type: file\n");
				files++;
			}
		}
		closedir(dir);
		printf("\nDone enumerating.\n");
	}

	printf("\nCounted %i files and %i directories.\n\n", files, folders);

	printf("Press + to exit.");

	// Main loop
	while (appletMainLoop()) {
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_PLUS) break; // break in order to return to hbmenu

		consoleUpdate(NULL);
	}

	consoleExit(NULL);
	return 0;
}