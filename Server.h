#pragma once

#include <QThread>
#include "civetweb.h"

class Server : public QObject {

Q_OBJECT

public:
    explicit Server();

    ~Server();

public slots:

    void startServer();

    void requestStop();

private:
    struct mg_context *ctx;

    int static queryHandler(struct mg_connection *conn, void *cbdata);

    int static imgHandler(struct mg_connection *conn, void *cbdata);

};
