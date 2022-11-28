#define _GNU_SOURCE 1
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <pthread.h>

#include "bass_defines.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

void *main_loop() {
    sleep(8);
    int (*setconf)(int, int) = dlsym(RTLD_DEFAULT, "BASS_SetConfig");
    int (*getconf)(int) = dlsym(RTLD_DEFAULT, "BASS_GetConfig");
    printf("Testing bass patch, loc: %p\n", setconf);
    if (setconf == NULL) return NULL;
    int (*bass_init)(int, int, int, void *, const void *) = dlsym(RTLD_DEFAULT, "BASS_Init");
    int (*getdevice)(void) = dlsym(RTLD_DEFAULT, "BASS_GetDevice");
    int (*geterror)(void) = dlsym(RTLD_DEFAULT, "BASS_ErrorGetCode");
    printf("BASS patch loaded, pid: %i\n", getpid());

    int period = 2;
    int buffer = 4;

    while (1) {
        printf("Current values are period = %d, buffer = %d\n",
                getconf(BASS_CONFIG_DEV_PERIOD), getconf(BASS_CONFIG_DEV_BUFFER));
        printf("Applying bass patch with period = %d, buffer = %d\n", period, buffer);
        setconf(BASS_CONFIG_DEV_PERIOD, period);
        setconf(BASS_CONFIG_DEV_BUFFER, buffer);
        int result = bass_init(getdevice(), 44100, 128, NULL, NULL);
        if (!result) {
            printf("Bass error: %i\n", geterror());
        } else {
            printf("No error\n");
        }
        printf("Period: ");
        scanf("%d", &period);
        period = max(period, 1);
        printf("Buflen: ");
        scanf("%d", &buffer);
        buffer = max(buffer, period);
    }
}

void __attribute__((constructor)) entry_point() {
    pthread_t t_id;
    pthread_create(&t_id, NULL, main_loop, NULL);
}