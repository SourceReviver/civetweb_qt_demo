#include "Server.h"
#include "Dictionary.h"
#include "ImageGenerator.h"

#include <QDebug>
#include <QBuffer>

Server::Server() {
    mg_init_library(0);
    ctx = nullptr;
}

void Server::startServer() {

    if (ctx) {
        qDebug() << "Server ctx already exist, will not start a new one";
        return;
    }

    struct mg_callbacks callbacks{};
    const char *options[] = {
            "listening_ports",
            "8888,8884",
            0
    };
    ctx = mg_start(&callbacks, 0, options);

    qDebug() << "New Server Started with port: " << mg_get_option(ctx, "listening_ports");

    mg_set_request_handler(ctx, "/query", Server::queryHandler, 0);
    mg_set_request_handler(ctx, "/img", Server::imgHandler, 0);
}

void Server::requestStop() {
    if (ctx) {
        mg_stop(ctx); // will also free ctx
        ctx = nullptr;
    }
    qDebug() << "Server Stopped";
}

int Server::queryHandler(struct mg_connection *conn, void *cbdata) {

    const struct mg_request_info *ri = mg_get_request_info(conn);

    QString responseTemp = R"(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>title</title>
</head>
<body>
  <p>%1</p>
  <img src="http://localhost:8888/img">
</body>
</html>
)";

    QString word = QString::fromStdString(ri->local_uri).split("/").last();
    std::string result = responseTemp.arg(Dict::getWordMeaning(word)).toStdString();

    const char *msg = result.c_str();
    auto len = result.length();
    mg_send_http_ok(conn, "text/html", len);

    mg_write(conn, msg, len);

    return 200;
}

int Server::imgHandler(struct mg_connection *conn, void *cbdata) {

    QImage img = getSomeImage();
    QByteArray imgbytes;
    QBuffer buffer(&imgbytes);
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer, "PNG");

    mg_send_http_ok(conn, "image/png", imgbytes.length());
    mg_write(conn, imgbytes, imgbytes.length());

    return 0;
}

Server::~Server() {
    requestStop();
}

