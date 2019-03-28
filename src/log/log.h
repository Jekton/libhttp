
#if defined(DEBUG)

#include <stdarg.h>

#define LOGD(tag, msg, ...) do {          \
  printf("[%s] %s: " msg "\n",            \
         tag,                             \
         __func__,                        \
         ##__VA_ARGS__);                  \
} while (0)

#define LOGI(tag, msg, ...) do {          \
  printf("[%s] %s: " msg "\n",            \
         tag,                             \
         __func__,                        \
         ##__VA_ARGS__);                  \
} while (0)

#else

#define LOGD(tag, msg, ...) do {          \
} while (0)

#define LOGI(tag, msg, ...) do {          \
} while (0)

#endif

#define LOGE(tag, msg, ...) do {          \
  fprintf(stderr, "[%s] %s: " msg "\n",   \
         tag,                             \
         __func__,                        \
         ##__VA_ARGS__);                  \
} while (0)
