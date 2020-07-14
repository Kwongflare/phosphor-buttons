#include <sdbusplus/bus.hpp>

#include <iostream>

int main()
{
    boost::asio::io_context io;
    auto conn = std::make_shared<sdbusplus::asio::connection>(io);

    int ready = 0;
    while (!ready)
    {
        auto readyMsg = conn->new_method_call(
            "xyz.openbmc_project.asio-test", "/xyz/openbmc_project/test",
            "xyz.openbmc_project.test", "VoidFunctionReturnsInt");
        try
        {
            message intMsg = conn->call(readyMsg);
            intMsg.read(ready);
        }
        catch (sdbusplus::exception::SdBusError& e)
        {
            ready = 0;
            // pause to give the server a chance to start up
            usleep(10000);
        }
    }
    std::cout << "ready received\n";
    return 0;
}
