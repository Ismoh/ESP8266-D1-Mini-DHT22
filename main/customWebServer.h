#ifndef CUSTOMWEBSERVER_H
#define CUSTOMWEBSERVER_H

#ifndef CREDENTIALS_H
#include "credentials.h"
#endif

class CustomWebServer
{
public:
    /// @brief Set up WebServer.
    void setup();

    /// @brief Loop until ESP died.
    void loop();
};

#endif