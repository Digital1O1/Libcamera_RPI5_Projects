#include <chrono>
#include <poll.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <sys/stat.h>

#include <chrono>

#include "frame_info.hpp"
#include "core/rpicam_app.hpp"
#include "core/still_options.hpp"

#include "output/output.hpp"

#include "image/image.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;
using libcamera::Stream;

int main()
{
    printf("test\r\n");
    return 0;
}