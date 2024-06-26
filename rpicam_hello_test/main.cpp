#include <chrono>
#include "core/rpicam_app.hpp"
#include "core/options.hpp"

using namespace std::placeholders;

// The main event loop for the application.

static void event_loop(RPiCamApp &app)
{
    // app.GetOptions() is a pointer?
    // Options *GetOptions() const { return options_.get(); }
    // Options is a struct that can be found in options.hpp
    // So I'm guessing that since we're
    Options const *options = app.GetOptions();

    app.OpenCamera();
    app.ConfigureViewfinder();
    app.StartCamera();

    auto start_time = std::chrono::high_resolution_clock::now();

    for (unsigned int count = 0;; count++)
    {
        // Msg == Another struct
        RPiCamApp::Msg msg = app.Wait();
        if (msg.type == RPiCamApp::MsgType::Timeout)
        {
            LOG_ERROR("ERROR: Device timeout detected, attempting a restart!!!");
            app.StopCamera();
            app.StartCamera();
            continue;
        }
        if (msg.type == RPiCamApp::MsgType::Quit)
            return;
        else if (msg.type != RPiCamApp::MsgType::RequestComplete)
            throw std::runtime_error("unrecognised message!");

        LOG(2, "Viewfinder frame " << count);
        auto now = std::chrono::high_resolution_clock::now();
        // options->timeout.value == 5000 ms
        // 
        
        if (options->timeout && (now - start_time) > options->timeout.value)
        {
            std::string timeout_value = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(options->timeout.value).count());
            std::cout << "Timeout value: " << timeout_value << " ms" << std::endl;
            return;
        }
        CompletedRequestPtr &completed_request = std::get<CompletedRequestPtr>(msg.payload);
        app.ShowPreview(completed_request, app.ViewfinderStream());
    }
}

int main(int argc, char *argv[])
{
    try
    {
        RPiCamApp app;
        Options *options = app.GetOptions();
        if (options->Parse(argc, argv))
        {
            if (options->verbose >= 2)
                options->Print();

            event_loop(app);
        }
    }
    catch (std::exception const &e)
    {
        LOG_ERROR("ERROR: *** " << e.what() << " ***");
        return -1;
    }
    return 0;
}