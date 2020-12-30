#include <tmuxWin.h>

#include <unistd.h>
#include <limits.h>
#include <errno.h>

#include <string>
#include <exception>
#include <system_error>
#include <algorithm>

namespace tmuxWin {
    std::string get_exe_path()
    {
        std::string buf(PATH_MAX, '\0');

        errno = 0;
        if ((readlink("/proc/self/exe", &buf[0], PATH_MAX)) == -1) {
            throw std::system_error(errno, std::system_category(),
                                    "failed to obtain the executable path");
        }

        return buf;
    }
}

extern "C" {
    int GetExeFilePath(char *buf, size_t bufsize)
    {
        std::string exe_path{};
        try {
            exe_path = tmuxWin::get_exe_path();
        } catch (std::system_error e) {
            return e.code().value();
        }

        size_t minsize = std::min(exe_path.size(), bufsize);

        try {
            std::copy_n(exe_path.begin(), minsize, buf);
        } catch (std::bad_alloc)
        {
            return ENOMEM;
        }

        return 0;
    }

}
