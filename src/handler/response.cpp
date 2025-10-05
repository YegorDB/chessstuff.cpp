#include "handler.h"

Handler::Response::Response(Status status) : status(status) {};

bool Handler::Response::isOk() {
    return status == Status::OK;
};
