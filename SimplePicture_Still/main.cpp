/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2020, Raspberry Pi (Trading) Ltd.
 *
 * rpicam_still.cpp - libcamera stills capture app.
 */
#include <chrono>
#include <poll.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <sys/stat.h>

#include <chrono>

#include "core/frame_info.hpp"
#include "core/rpicam_app.hpp"
#include "core/still_options.hpp"

#include "output/output.hpp"

#include "image/image.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;
using libcamera::Stream;

// RPiCamStillApp inherits from RPiCamApp
// RPiCam app == base class
class RPiCamStillApp : public RPiCamApp
{
public:
    // Constructor that initializes RPiCamApp base class with make_unique_ptr<StillOptions>
    // Constructor provided explicitly within RPiCamStillApp
    RPiCamStillApp() : RPiCamApp(std::make_unique<StillOptions>()) {}

    // options.get() used to access the pointer std::unique_ptr<StillOptions> member variable options_
    // Then uses static_cast to cast the pointer to a StillOptions*

    StillOptions *GetOptions() const { return static_cast<StillOptions *>(options_.get()); }
};
int main()
{
    RPiCamStillApp app;
    StillOptions const *options = app.GetOptions();

    unsigned int still_flags = RPiCamApp::FLAG_STILL_NONE;
    still_flags |= RPiCamApp::FLAG_STILL_RGB;
    app.OpenCamera();

    app.ConfigureViewfinder(); // Errored out here
    app.StartCamera();
    bool want_capture = options->immediate;

    printf("Program Ended\r\n");
    return 0;
}
