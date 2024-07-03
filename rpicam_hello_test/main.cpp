#include <chrono>
#include "core/rpicam_app.hpp"
#include "core/options.hpp"

using namespace std::placeholders;

// The main event loop for the application.

static void event_loop(RPiCamApp &app)
{
    /*
        Notes about the following line of code : Options const *options = app.GetOptions();
            - 'options' --> pointer to 'Options' object
                - Has access to the 'Options' object
                - And everything that's returned by app.GetOptions()
            - 'app' --> Object that's an instance from the 'RPiCamApp' class
        Example : If options has member variable 'timeout' and method 'Print()'

        // Access a member variable
        if (options->timeout && (now - start_time) > options->timeout.value)
        {
            std::string timeout_value = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(options->timeout.value).count());
            std::cout << "Timeout value: " << timeout_value << " ms" << std::endl;
            return;
        }

        // Call a method
        options->Print();

        Options *GetOptions() const { return options_.get(); }
            - Can be found in rpicam_jpeg.cpp --> right click *GetOptions() -->  Go to definition --> rpicam_app.hpp
    */
    Options const *options = app.GetOptions();

    app.OpenCamera();
    app.ConfigureViewfinder();
    app.StartCamera();

    auto start_time = std::chrono::high_resolution_clock::now();

    for (unsigned int count = 0;; count++)
    {
        // Msg == Another struct
        /*
            Notes about app.Wait()
                - Uses a mutex to 'pause' the program
                - Once message available
                    - Pops message from queue and returns it
            Useage in RPiCamApp
                - Used to handle incomingg messages that might indicate different events such as
                    - Completion of request
                    - Timeout
                    - Quit signal
                    - 'Msg' struct defines the type/payload of these messages
        */
        // RpiCamApp::Msg --> RpiCamApp = The class | Msg = A struct within RpiCamApp class
        RPiCamApp::Msg msg = app.Wait();

        /*
            Notes about MsgType::Timeout
                - MsgType is an enum class
                - Has three values
                    - RequestComplete
                    - Timeout
                    - Quit
        */
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

        // If the program reaches 5000 ms, exit here
        /*
            Clarifying the AND operator
                - if statement evaluated from LEFT to RIGHT
                - options->timeout
                    - Ensures that a valid pointer converts to TRUE while any nullptr converts to FALSE
        */
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